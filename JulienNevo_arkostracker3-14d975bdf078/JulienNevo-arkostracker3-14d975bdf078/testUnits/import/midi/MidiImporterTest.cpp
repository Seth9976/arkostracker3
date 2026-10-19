#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/import/midi/MidiImporter.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker 
{

static void checkInstrumentShortSound(const Instrument& instrument)
{
    REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
    const auto& psgPart = instrument.getConstPsgPart();
    REQUIRE(psgPart.getMainLoopRef() == Loop(14, 14, false));

    auto index = 0;
    for (auto volume = 15; volume > 0; --volume) {      // No need to reach 0.
        REQUIRE(psgPart.getCellRefConst(index) == PsgInstrumentCell::buildSoftwareCell(volume));
        ++index;
    }
    REQUIRE(psgPart.getLength() == index);
}

static void checkInstrumentEmpty(const Instrument& instrument)
{
    REQUIRE(instrument.getName() == "Empty");
    REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
    const auto& psgPart = instrument.getConstPsgPart();
    REQUIRE(psgPart.getMainLoopRef() == Loop(0, 0, true));
    REQUIRE(psgPart.getLength() == 1);
}

TEST_CASE("Midi Import, wrong file", "[MidiImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::Kangaroo__Alienall_128, BinaryData::Kangaroo__Alienall_128Size, false);

    // Parses.
    MidiImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "mid"));
}

TEST_CASE("Midi Import, midi0", "[MidiImporter]")
{
    // Loads a song with a MIDI0 format.
    juce::MemoryInputStream inputStream(BinaryData::FourNotesMidi0_mid, BinaryData::FourNotesMidi0_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));

    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE_FALSE(report->isOk());
    REQUIRE(report->getErrorCount() == 1);      // No need to parse the song further once the MIDI format 0 is found.
    REQUIRE(report->getLine(0).getLevel() == ReportLevel::error);
    REQUIRE(report->getLine(0).getText().contains("Midi format 0 is forbidden"));
    REQUIRE(song == nullptr);
}

TEST_CASE("Midi Import, SimpleNotes file", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::SimpleNotes_mid, BinaryData::SimpleNotes_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 1, 2, 3 });      // Skips the conductor track.
    MidiConfiguration midiConfiguration(240, 10, false, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);

    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 2);
        REQUIRE(subsong.getLoopStartPosition() == 0);
        REQUIRE(subsong.getEndPosition() == 1);
        {
            auto position = subsong.getPosition(0);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getHeight() == 64);
            REQUIRE(position.getMarkerName() == Position::firstMarkerName);
        }
        {
            auto position = subsong.getPosition(1);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 64);
            REQUIRE(position.getMarkerName() == juce::String());
        }

        // Checks the Patterns.
        REQUIRE(subsong.getPatternCount() == 2);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 3);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 5);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 1);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 1);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Tracks.
        // Position 0.
        // Track 0.
        {
            const auto& track = subsong.getTrackRefFromIndex(0);

            Cell cell1 = Cell(Note::buildNote(48), 1);
            Cell cell2 = Cell(Note::buildNote(60), 1);
            TrackTestHelper::containsOnly(track, {
                    { 0, cell1 },
                    { 8, cell1 },
                    { 16, cell2 },
                    { 24, cell2 },
                    { 32, cell1 },
                    { 40, cell1 },
                    { 48, cell2 },
                    { 56, cell2 },
            });
        }
        // Track 1 and 2 are empty.
        REQUIRE(subsong.getTrackRefFromIndex(1).isEmpty());
        REQUIRE(subsong.getTrackRefFromIndex(2).isEmpty());

        // Position 1.
        // Track 3.
        {
            const auto& track = subsong.getTrackRefFromIndex(3);

            Cell cell1 = Cell(Note::buildNote(48), 1);
            Cell cell2 = Cell(Note::buildNote(60), 1);
            TrackTestHelper::containsOnly(track, {
                    { 0, cell1 },
                    { 8, cell1 },
                    { 16, cell2 },
                    { 24, cell2 },
            });
        }
        // Track 4 and 5 are empty.
        REQUIRE(subsong.getTrackRefFromIndex(4).isEmpty());
        REQUIRE(subsong.getTrackRefFromIndex(5).isEmpty());
    });

    // Checks the Arpeggios. Only the empty one.
    {
        const auto& expressionHandler = song->getExpressionHandler(true);
        REQUIRE(expressionHandler.getCount() == 1);
        const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getValue(0) == 0);
    }
    // Checks the Pitches. Only the empty one.
    {
        const auto& expressionHandler = song->getExpressionHandler(false);
        REQUIRE(expressionHandler.getCount() == 1);
        const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getValue(0) == 0);
    }

    // Checks the Instruments.
    REQUIRE(song->getInstrumentCount() == 2);
    {
        // Instrument 0 (empty).
        song->performOnConstInstrument(song->getInstrumentId(0).getValue(), [](const Instrument& instrument) {
            checkInstrumentEmpty(instrument);
        });

        // Instrument 1.
        song->performOnConstInstrument(song->getInstrumentId(1).getValue(), [](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Acoustic Grand Piano");
            checkInstrumentShortSound(instrument);
        });
    }
}

/** Only to made sure the default configuration is well read. */
TEST_CASE("Midi Import, SimpleNotes file, default configuration", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::SimpleNotes_mid, BinaryData::SimpleNotes_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Uses the Midi Import Configuration.
    ImportConfiguration importConfiguration;

    auto result = importer.loadSong(inputStream, importConfiguration);
    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);
}

TEST_CASE("Midi Import, three Tracks with Program Change", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::ThreeChannelsWithEachItsProgram_mid, BinaryData::ThreeChannelsWithEachItsProgram_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 1, 2, 3 });      // Skips the conductor track.
    MidiConfiguration midiConfiguration(120, 10, false, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);

    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 2);
        {
            auto position = subsong.getPosition(0);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getHeight() == 64);
        }
        {
            auto position = subsong.getPosition(1);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 64);
        }

        // Checks the Patterns.
        REQUIRE(subsong.getPatternCount() == 2);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 3);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 5);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 1);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 1);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Tracks.
        // Position 0.
        // Track 0.
        {
            const auto& track = subsong.getTrackRefFromIndex(0);
            constexpr auto instr1 = 1;
            constexpr auto instr2 = 2;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(40), instr1) },
                    { 8, Cell(Note::buildNote(41), instr1) },
                    { 16, Cell(Note::buildNote(42), instr1) },
                    { 24, Cell(Note::buildNote(43), instr1) },
                    { 32, Cell(Note::buildNote(44), instr1) },
                    { 36, Cell(Note::buildNote(45), instr1) },
                    { 40, Cell(Note::buildNote(46), instr1) },
                    { 44, Cell(Note::buildNote(47), instr1) },

                    { 48, Cell(Note::buildNote(48), instr2) },
                    { 50, Cell(Note::buildNote(49), instr2) },
                    { 52, Cell(Note::buildNote(50), instr2) },
                    { 54, Cell(Note::buildNote(51), instr2) },
                    { 56, Cell(Note::buildNote(52), instr2) },
                    { 58, Cell(Note::buildNote(53), instr2) },
                    { 60, Cell(Note::buildNote(54), instr2) },
                    { 62, Cell(Note::buildNote(55), instr2) },
            }));
        }
        // Track 1.
        {
            const auto& track = subsong.getTrackRefFromIndex(1);
            constexpr auto instrumentIndex = 3;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(30), instrumentIndex) },
                    { 32, Cell(Note::buildNote(31), instrumentIndex) },
            }));
        }
        // Track 2. No Program Change, so assume it is instrument 4 because PC 0 has never been met before.
        {
            const auto& track = subsong.getTrackRefFromIndex(2);
            constexpr auto instrumentIndex = 4;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(100), instrumentIndex) },
                    { 16, Cell(Note::buildNote(100), instrumentIndex) },
                    { 32, Cell(Note::buildNote(100), instrumentIndex) },
                    { 40, Cell(Note::buildNote(100), instrumentIndex) },
                    { 48, Cell(Note::buildNote(100), instrumentIndex) },
            }));
        }

        // Position 1.
        // Track 3.
        {
            const auto& track = subsong.getTrackRefFromIndex(3);
            constexpr auto instrumentIndex = 2;
            std::map<int, Cell> indexToCell;
            for (auto index = 0; index <= 31; ++index) {
                indexToCell.insert({ index, Cell(Note::buildNote(36 + index), instrumentIndex) });
            }

            REQUIRE(TrackTestHelper::containsOnly(track, indexToCell));
        }
        // Track 4.
        {
            const auto& track = subsong.getTrackRefFromIndex(4);
            constexpr auto instrumentIndex = 3;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(32), instrumentIndex) }
            }));
        }
        // Track 5 is empty.
        REQUIRE(subsong.getTrackRefFromIndex(5).isEmpty());
    });

    // Checks the Arpeggios. Only the empty one.
    {
        const auto& expressionHandler = song->getExpressionHandler(true);
        REQUIRE(expressionHandler.getCount() == 1);
        const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getValue(0) == 0);
    }
    // Checks the Pitches. Only the empty one.
    {
        const auto& expressionHandler = song->getExpressionHandler(false);
        REQUIRE(expressionHandler.getCount() == 1);
        const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getValue(0) == 0);
    }

    // Checks the Instruments.
    REQUIRE(song->getInstrumentCount() == 5);
    {
        // Instrument 0 (empty).
        song->performOnConstInstrument(song->getInstrumentId(0).getValue(), [](const Instrument& instrument) {
            checkInstrumentEmpty(instrument);
        });
        // Instrument 1.
        song->performOnConstInstrument(song->getInstrumentId(1).getValue(), [](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Electric Piano 1");
            checkInstrumentShortSound(instrument);
        });
        // Instrument 2.
        song->performOnConstInstrument(song->getInstrumentId(2).getValue(), [](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Electric Piano 2");
            checkInstrumentShortSound(instrument);
        });
        // Instrument 3.
        song->performOnConstInstrument(song->getInstrumentId(3).getValue(), [](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Electric Grand Piano");
            checkInstrumentShortSound(instrument);
        });
        // Instrument 4.
        song->performOnConstInstrument(song->getInstrumentId(4).getValue(), [](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Acoustic Grand Piano");
            checkInstrumentShortSound(instrument);
        });
    }
}

TEST_CASE("Midi Import, time signature 3/4", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::TimeSignature3_4_mid, BinaryData::TimeSignature3_4_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 1, 2, 3 });      // Skips the conductor track.
    MidiConfiguration midiConfiguration(120, 10, false, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);

    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 2);
        {
            auto position = subsong.getPosition(0);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getHeight() == 48);
        }
        {
            auto position = subsong.getPosition(1);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 48);
        }

        // Checks the Patterns
        REQUIRE(subsong.getPatternCount() == 2);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 3);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 5);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 1);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 1);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Tracks.
        // Position 0.
        {
            const auto& track = subsong.getTrackRefFromIndex(0);
            constexpr auto instr1 = 1;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(51), instr1) },
                    { 4, Cell(Note::buildNote(56), instr1) },
                    { 8, Cell(Note::buildNote(60), instr1) },
                    { 12, Cell(Note::buildNote(51), instr1) },
                    { 16, Cell(Note::buildNote(56), instr1) },
                    { 20, Cell(Note::buildNote(60), instr1) },
                    { 24, Cell(Note::buildNote(51), instr1) },
                    { 28, Cell(Note::buildNote(56), instr1) },
                    { 32, Cell(Note::buildNote(60), instr1) },
                    { 36, Cell(Note::buildNote(51), instr1) },
                    { 40, Cell(Note::buildNote(56), instr1) },
                    { 44, Cell(Note::buildNote(60), instr1) },
            }));
            REQUIRE(subsong.getTrackRefFromIndex(1).isEmpty());
            REQUIRE(subsong.getTrackRefFromIndex(2).isEmpty());
        }
        // Position 1.
        {
            const auto& track = subsong.getTrackRefFromIndex(3);
            constexpr auto instr1 = 1;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(46), instr1) },
                    { 4, Cell(Note::buildNote(51), instr1) },
                    { 8, Cell(Note::buildNote(56), instr1) },
                    { 12, Cell(Note::buildNote(46), instr1) },
                    { 16, Cell(Note::buildNote(51), instr1) },
                    { 20, Cell(Note::buildNote(56), instr1) },
                    { 24, Cell(Note::buildNote(46), instr1) },
                    { 28, Cell(Note::buildNote(51), instr1) },
                    { 32, Cell(Note::buildNote(56), instr1) },
                    { 36, Cell(Note::buildNote(46), instr1) },
                    { 40, Cell(Note::buildNote(51), instr1) },
                    { 44, Cell(Note::buildNote(56), instr1) },
            }));
            REQUIRE(subsong.getTrackRefFromIndex(4).isEmpty());
            REQUIRE(subsong.getTrackRefFromIndex(5).isEmpty());
        }
    });

    // Checks the Arpeggios. Only the empty one.
    {
        const auto& expressionHandler = song->getExpressionHandler(true);
        REQUIRE(expressionHandler.getCount() == 1);
        const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getValue(0) == 0);
    }
    // Checks the Pitches. Only the empty one.
    {
        const auto& expressionHandler = song->getExpressionHandler(false);
        REQUIRE(expressionHandler.getCount() == 1);
        const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getValue(0) == 0);
    }

    // Checks the Instruments.
    REQUIRE(song->getInstrumentCount() == 2);
    {
        // Instrument 0 (empty).
        song->performOnConstInstrument(song->getInstrumentId(0).getValue(), [](const Instrument& instrument) {
            checkInstrumentEmpty(instrument);
        });

        // Instrument 1.
        song->performOnConstInstrument(song->getInstrumentId(1).getValue(), [](const Instrument& instrument) {
            REQUIRE(instrument.getName() == "Acoustic Guitar (steel)");
            checkInstrumentShortSound(instrument);
        });
    }
}

TEST_CASE("Midi Import, tempo change ratio 4", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::TempoChange_mid, BinaryData::TempoChange_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 1, 2, 3 });      // Skips the conductor track.
    MidiConfiguration midiConfiguration(960 / 4, 10, false, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);
    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 4);
        REQUIRE(subsong.getLoopStartPosition() == 0);
        REQUIRE(subsong.getEndPosition() == 3);
        {
            auto position = subsong.getPosition(0);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getHeight() == 64);
        }
        {
            auto position = subsong.getPosition(1);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 64);
        }
        {
            auto position = subsong.getPosition(2);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 2);
            REQUIRE(position.getHeight() == 64);
        }
        {
            auto position = subsong.getPosition(3);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 3);
            REQUIRE(position.getHeight() == 64);
        }

        // Checks the Patterns
        REQUIRE(subsong.getPatternCount() == 4);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 3);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 5);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 1);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 1);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(2);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 6);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 7);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 8);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 2);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(3);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 9);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 10);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 11);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 3);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 3);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Tracks. They are all the same, in a Pattern.
        for (auto patternIndex = 0; patternIndex < 4; ++patternIndex) {
            const auto& track = subsong.getTrackRefFromIndex(patternIndex * 3 + 0);
            constexpr auto instr1 = 1;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(36), instr1) },
                    { 16, Cell(Note::buildNote(37), instr1) },
                    { 32, Cell(Note::buildNote(38), instr1) },
                    { 48, Cell(Note::buildNote(39), instr1) },
            }));
            REQUIRE(subsong.getTrackRefFromIndex(patternIndex * 3 + 1).isEmpty());
            REQUIRE(subsong.getTrackRefFromIndex(patternIndex * 3 + 2).isEmpty());
        }

        // Checks the Speed Tracks.
        REQUIRE(subsong.getSpecialTrackCount(true) == 4);
        std::vector speeds = { 6, 5, 4, 8 };
        for (auto speedTrackIndex = 0; speedTrackIndex < 4; ++speedTrackIndex) {
            const auto& speedTrack = subsong.getSpecialTrackRefFromIndex(speedTrackIndex, true);
            REQUIRE(TrackTestHelper::containsOnly(speedTrack, {
                    { 0, speeds.at(static_cast<size_t>(speedTrackIndex)) }
            }));
        }

        // Checks the Event Tracks.
        REQUIRE(subsong.getSpecialTrackCount(false) == 4);
        REQUIRE(subsong.getSpecialTrackRefFromIndex(0, false).isEmpty());
        REQUIRE(subsong.getSpecialTrackRefFromIndex(1, false).isEmpty());
        REQUIRE(subsong.getSpecialTrackRefFromIndex(2, false).isEmpty());
        REQUIRE(subsong.getSpecialTrackRefFromIndex(3, false).isEmpty());

    });
}

TEST_CASE("Midi Import, tempo change ratio 2", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::TempoChange_mid, BinaryData::TempoChange_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 1, 2, 3 });      // Skips the conductor track.
    MidiConfiguration midiConfiguration(960 / 2, 10, false, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);
    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 2);
        {
            auto position = subsong.getPosition(0);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getHeight() == 64);
        }
        {
            auto position = subsong.getPosition(1);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 64);
        }

        // Checks the Patterns
        REQUIRE(subsong.getPatternCount() == 2);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 3);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 5);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 1);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 1);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Tracks. They are all the same, in a Pattern.
        for (auto patternIndex = 0; patternIndex < 2; ++patternIndex) {
            const auto& track = subsong.getTrackRefFromIndex(patternIndex * 3 + 0);
            constexpr auto instr1 = 1;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0, Cell(Note::buildNote(36), instr1) },
                    { 8, Cell(Note::buildNote(37), instr1) },
                    { 16, Cell(Note::buildNote(38), instr1) },
                    { 24, Cell(Note::buildNote(39), instr1) },
                    { 32, Cell(Note::buildNote(36), instr1) },
                    { 40, Cell(Note::buildNote(37), instr1) },
                    { 48, Cell(Note::buildNote(38), instr1) },
                    { 56, Cell(Note::buildNote(39), instr1) },
            }));
            REQUIRE(subsong.getTrackRefFromIndex(patternIndex * 3 + 1).isEmpty());
            REQUIRE(subsong.getTrackRefFromIndex(patternIndex * 3 + 2).isEmpty());
        }

        // Checks the Speed Tracks.
        REQUIRE(subsong.getSpecialTrackCount(true) == 2);
        std::vector speeds = { 13, 9, 8, 15 };
        auto speedIndex = 0;
        for (auto speedTrackIndex = 0; speedTrackIndex < 2; ++speedTrackIndex) {
            const auto& speedTrack = subsong.getSpecialTrackRefFromIndex(speedTrackIndex, true);
            REQUIRE(TrackTestHelper::containsOnly(speedTrack, {
                    { 0, speeds.at(static_cast<size_t>(speedIndex)) },
                    { 32, speeds.at(static_cast<size_t>(speedIndex + 1)) },
            }));

            speedIndex += 2;
        }

        // Checks the Event Tracks.
        REQUIRE(subsong.getSpecialTrackCount(false) == 2);
        REQUIRE(subsong.getSpecialTrackRefFromIndex(0, false).isEmpty());
        REQUIRE(subsong.getSpecialTrackRefFromIndex(1, false).isEmpty());

    });
}

TEST_CASE("Midi Import, volume change", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::VolumeChange_mid, BinaryData::VolumeChange_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 1, 2, 3 });      // Skips the conductor track.
    MidiConfiguration midiConfiguration(960, 10, true, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);
    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 1);
        {
            auto position = subsong.getPosition(0);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getHeight() == 64);
        }

        // Checks the Patterns
        REQUIRE(subsong.getPatternCount() == 1);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Tracks. They are all the same, in a Pattern.
        const auto& track = subsong.getTrackRefFromIndex(0);
        constexpr auto instr = 1;
        REQUIRE(TrackTestHelper::containsOnly(track, {
                { 0, Cell(Note::buildNote(40), instr, CellEffects({{ Effect::volume, 0xf }})) },
                { 1, Cell(Note::buildNote(39), instr) },
                { 2, Cell(Note::buildNote(38), instr, CellEffects({{ Effect::volume, 0xe }})) },
                { 3, Cell(Note::buildNote(37), instr) },
                { 4, Cell(Note::buildNote(36), instr) },
                { 5, Cell(Note::buildNote(35), instr) },
                { 6, Cell(Note::buildNote(34), instr, CellEffects({{ Effect::volume, 0xd }})) },
                { 7, Cell(Note::buildNote(33), instr) },
                { 8, Cell(Note::buildNote(32), instr, CellEffects({{ Effect::volume, 0xb }})) },
                { 9, Cell(Note::buildNote(31), instr) },
                { 10, Cell(Note::buildNote(30), instr, CellEffects({{ Effect::volume, 0x8 }})) },
                { 11, Cell(Note::buildNote(29), instr) },
                { 12, Cell(Note::buildNote(28), instr, CellEffects({{ Effect::volume, 0x1 }})) },
                { 13, Cell(Note::buildNote(27), instr) },
        }));
        REQUIRE(subsong.getTrackRefFromIndex(1).isEmpty());
        REQUIRE(subsong.getTrackRefFromIndex(2).isEmpty());

        // Checks the Speed Tracks.
        REQUIRE(subsong.getSpecialTrackCount(true) == 1);
        REQUIRE(subsong.getSpecialTrackRefFromIndex(0, true).isEmpty());

        // Checks the Event Tracks.
        REQUIRE(subsong.getSpecialTrackCount(false) == 1);
        REQUIRE(subsong.getSpecialTrackRefFromIndex(0, false).isEmpty());
    });

    REQUIRE(song->getInstrumentCount() == 2);
}

TEST_CASE("Midi Import, lastPatternHeightCrash", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::PulkoMidiCrash_mid, BinaryData::PulkoMidiCrash_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 1, 2, 3, 4, 5, 6 });      // Skips the conductor track.
    MidiConfiguration midiConfiguration(24, 10, false, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);
    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 2);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 12);
        for (auto positionIndex = 0; positionIndex < 12; ++positionIndex) {
            auto position = subsong.getPosition(positionIndex);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == positionIndex);
            REQUIRE(position.getHeight() == 0x30);
        }
    });

    REQUIRE(song->getInstrumentCount() == 7);
}

TEST_CASE("Midi Import, noConductorTrack", "[MidiImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::Crownland__intro_mid, BinaryData::Crownland__intro_midSize, false);

    // Parses.
    MidiImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mid"));
    inputStream.setPosition(0);

    // Builds a Midi Import Configuration.
    ChannelMixerKeeper channelMixerKeeper;
    channelMixerKeeper.addTracksToKeep({ 0, 1, 2 });
    MidiConfiguration midiConfiguration(120, 10, false, channelMixerKeeper);

    ImportConfiguration importConfiguration(nullptr, &midiConfiguration);

    auto result = importer.loadSong(inputStream, importConfiguration);
    REQUIRE(result != nullptr);
    auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Untitled");
    REQUIRE(song->getAuthor() == "Unknown");
    REQUIRE(song->getComposer() == "Unknown");
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getPsgCount(subsongId) == 1);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        // Checks the Linker.
        REQUIRE(subsong.getLength() == 9);
        for (auto positionIndex = 0; positionIndex < 9; ++positionIndex) {
            auto position = subsong.getPosition(positionIndex);
            REQUIRE(!position.isTranspositionUsed());
            REQUIRE(position.getPatternIndex() == positionIndex);
            REQUIRE(position.getHeight() == 64);
        }

        // Checks SOME Tracks.
        // Position 0.
        {
            const auto& track = subsong.getTrackRefFromIndex(0);
            constexpr auto instr = 1;
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },
                    { 0x2, Cell(Note::buildNote(TrackTestHelper::noteA2), instr) },
                    { 0x4, Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },
                    { 0xa, Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },
                    { 0xc, Cell(Note::buildNote(TrackTestHelper::noteA2), instr) },
                    { 0xe, Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },

                    { 0x12, Cell(Note::buildNote(TrackTestHelper::noteDs3), instr) },
                    { 0x16, Cell(Note::buildNote(TrackTestHelper::noteE3), instr) },
                    { 0x1a, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                    { 0x1e, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                    { 0x20, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                    { 0x23, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                    { 0x26, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                    { 0x28, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                    { 0x2e, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                    { 0x30, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                    { 0x33, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                    { 0x36, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                    { 0x38, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                    { 0x3c, Cell(Note::buildNote(TrackTestHelper::noteE3), instr) },
            }));
            REQUIRE(subsong.getTrackRefFromIndex(1).isEmpty());
            REQUIRE(subsong.getTrackRefFromIndex(2).isEmpty());
        }
        // Position 1.
        {
            {
                const auto& track = subsong.getTrackRefFromIndex(3);
                constexpr auto instr = 1;
                REQUIRE(TrackTestHelper::containsOnly(track, {
                        { 0x0,  Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },
                        { 0x2,  Cell(Note::buildNote(TrackTestHelper::noteA2), instr) },
                        { 0x4,  Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },
                        { 0xa,  Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },
                        { 0xc,  Cell(Note::buildNote(TrackTestHelper::noteA2), instr) },
                        { 0xe,  Cell(Note::buildNote(TrackTestHelper::noteB2), instr) },
                        { 0x12, Cell(Note::buildNote(TrackTestHelper::noteDs3), instr) },
                        { 0x16, Cell(Note::buildNote(TrackTestHelper::noteE3), instr) },
                        { 0x1a, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                        { 0x1e, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                        { 0x20, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                        { 0x23, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                        { 0x26, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                        { 0x28, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                        { 0x2e, Cell(Note::buildNote(TrackTestHelper::noteA3), instr) },
                        { 0x30, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                        { 0x33, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                        { 0x36, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                        { 0x38, Cell(Note::buildNote(TrackTestHelper::noteFs3), instr) },
                        { 0x3c, Cell(Note::buildNote(TrackTestHelper::noteE3), instr) },
                }));
            }
            {
                const auto& track = subsong.getTrackRefFromIndex(4);
                constexpr auto instr = 2;
                REQUIRE(TrackTestHelper::containsOnly(track, {
                        { 0x0,  Cell(Note::buildNote(TrackTestHelper::noteB5), instr) },
                        { 0x2,  Cell(Note::buildNote(TrackTestHelper::noteDs6), instr) },
                        { 0x4,  Cell(Note::buildNote(TrackTestHelper::noteE6), instr) },
                        { 0x6,  Cell(Note::buildNote(TrackTestHelper::noteFs6), instr) },

                        { 0x12, Cell(Note::buildNote(TrackTestHelper::noteA6), instr) },
                        { 0x14, Cell(Note::buildNote(TrackTestHelper::noteFs6), instr) },
                        { 0x16, Cell(Note::buildNote(TrackTestHelper::noteE6), instr) },

                        { 0x1a, Cell(Note::buildNote(TrackTestHelper::noteFs6), instr) },
                        { 0x1c, Cell(Note::buildNote(TrackTestHelper::noteE6), instr) },
                        { 0x1e, Cell(Note::buildNote(TrackTestHelper::noteDs6), instr) },

                        { 0x22, Cell(Note::buildNote(TrackTestHelper::noteB5), instr) },

                        { 0x26, Cell(Note::buildNote(TrackTestHelper::noteA5), instr) },
                        { 0x28, Cell(Note::buildNote(TrackTestHelper::noteB5), instr) },
                        { 0x2a, Cell(Note::buildNote(TrackTestHelper::noteFs6), instr) },
                        { 0x2c, Cell(Note::buildNote(TrackTestHelper::noteE6), instr) },
                        { 0x2e, Cell(Note::buildNote(TrackTestHelper::noteDs6), instr) },

                        { 0x32, Cell(Note::buildNote(TrackTestHelper::noteB5), instr) },
                        { 0x36, Cell(Note::buildNote(TrackTestHelper::noteA5), instr) },
                        { 0x38, Cell(Note::buildNote(TrackTestHelper::noteB5), instr) },
                }));
            }
        }
    });

    REQUIRE(song->getInstrumentCount() == 5);
}


static std::unique_ptr<juce::MidiFile> loadMidiFile_MidiImporterTest(const void* data, const size_t size)
{
    // Loads the midi file.
    juce::MidiFile midiFile;
    juce::MemoryInputStream memoryInputStream(data, size, false);
    auto success = midiFile.readFrom(memoryInputStream);
    REQUIRE(success);

    // Should be a Tick format, not SMTP!
    int timeFormat = midiFile.getTimeFormat();
    REQUIRE(timeFormat > 0);

    return std::make_unique<juce::MidiFile>(midiFile);
}

static void findUsedTracks(const void* data, size_t size, int expectedTrackCount, const std::set<int>& expectedTrackIndexUsed)
{
    // Loads the midi file.
    auto midiFile = loadMidiFile_MidiImporterTest(data, size);

    // How many tracks are detected, how many have notes?
    auto result = MidiImporter::findTrackCount(*midiFile);
    REQUIRE(result.first == expectedTrackCount);
    REQUIRE(result.second == expectedTrackIndexUsed);
}

TEST_CASE("Midi Import, findUsedTracks simple example", "[MidiImporter]")
{
    // There is a conductor track.
    findUsedTracks(BinaryData::SimpleExample_mid, BinaryData::SimpleExample_midSize, 4, std::set { 1, 2, 3 });
}

TEST_CASE("Midi Import, findUsedTracks Hospital", "[MidiImporter]")
{
    // There is a conductor track.
    findUsedTracks(BinaryData::Hospital_Music_3_V1_3_mid, BinaryData::Hospital_Music_3_V1_3_midSize, 10, std::set { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
}

}   // namespace arkostracker

