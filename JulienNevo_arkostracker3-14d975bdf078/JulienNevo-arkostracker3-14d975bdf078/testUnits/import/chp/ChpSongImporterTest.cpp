#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/import/chp/ChpSongImporter.h"
#include "../../../source/song/subsong/SubsongConstants.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("CHP import, wrong file", "[ChpSongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::At2AllEffects_aks, BinaryData::At2AllEffects_aksSize, false);

    // Parses.
    const ChpSongImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "chp"));
}

TEST_CASE("CHP import, format ok", "[ChpSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::simple_chp, BinaryData::simple_chpSize, false);

    // Parses.
    const ChpSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "chp"));
}

class Helper
{
public:
    static void testSong(const void* musicData, size_t musicSize)
    {
        // Loads a song.
        juce::MemoryInputStream inputStream(musicData, musicSize, false);

        // Parses.
        ChpSongImporter importer;
        REQUIRE(importer.doesFormatMatch(inputStream, "chp"));
        inputStream.setPosition(0);
        auto result = importer.loadSong(inputStream, ImportConfiguration());

        REQUIRE((result != nullptr));
        auto& song = result->song;
        auto& report = result->errorReport;
        REQUIRE((report != nullptr));
        REQUIRE(report->isOk());
        REQUIRE((report->getWarningCount() == 0));
        REQUIRE((song != nullptr));

        REQUIRE((song->getSubsongCount() == 1));
    }
};

TEST_CASE("CHP import, load songs", "[ChpSongImporter]")
{
    // Simply loads the songs, making sure the export went fine.
    Helper::testSong(BinaryData::simple_chp, BinaryData::simple_chpSize);
    Helper::testSong(BinaryData::ABADIA1_CHP, BinaryData::ABADIA1_CHPSize);
    Helper::testSong(BinaryData::ADDAMSF0_CHP, BinaryData::ADDAMSF0_CHPSize);
    Helper::testSong(BinaryData::ARKANOID_CHP, BinaryData::ARKANOID_CHPSize);
    Helper::testSong(BinaryData::ARKOID2A_CHP, BinaryData::ARKOID2A_CHPSize);
    Helper::testSong(BinaryData::bactron_chp, BinaryData::bactron_chpSize);
    Helper::testSong(BinaryData::burninr1_chp, BinaryData::burninr1_chpSize);
    Helper::testSong(BinaryData::JSW1_CHP, BinaryData::JSW1_CHPSize);
    Helper::testSong(BinaryData::THUNCATS_CHP, BinaryData::THUNCATS_CHPSize);
    Helper::testSong(BinaryData::THANATOS_CHP, BinaryData::THANATOS_CHPSize);
}

TEST_CASE("CHP import, load songs with linker problem", "[ChpSongImporter]")
{
    Helper::testSong(BinaryData::AMAUROTH_CHP, BinaryData::AMAUROTH_CHPSize);
    Helper::testSong(BinaryData::BOMBUZAL_CHP, BinaryData::BOMBUZAL_CHPSize);
    Helper::testSong(BinaryData::CHIMERA2_CHP, BinaryData::CHIMERA2_CHPSize);
}

TEST_CASE("CHP import, test song", "[ChpSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::test_chp, BinaryData::test_chpSize, false);

    // Parses.
    ChpSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "chp"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE((result != nullptr));
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE((report != nullptr));
    REQUIRE(report->isOk());
    REQUIRE((report->getWarningCount() == 0));
    REQUIRE((song != nullptr));

    // Checks the Song.
    REQUIRE((song->getTitle() == "Song title"));
    REQUIRE((song->getSubsongCount() == 1));
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE((song->getAuthor() == ""));
    REQUIRE((song->getComposer() == ""));
    REQUIRE((song->getComments() == "Description"));
    const auto subsongMetadata = song->getSubsongMetadata(subsongId);
    const auto psgCount = song->getPsgCount(subsongId);
    REQUIRE((subsongMetadata.getDigiChannel() == 1));
    REQUIRE(juce::exactlyEqual(subsongMetadata.getReplayFrequencyHz(), 50.0F));
    REQUIRE((subsongMetadata.getInitialSpeed() == 6));
    REQUIRE((subsongMetadata.getName() == SubsongConstants::defaultFirstSubsongName));
    REQUIRE((psgCount == 1));
    REQUIRE((subsongMetadata.getHighlightSpacing() == 4));
    REQUIRE((subsongMetadata.getSecondaryHighlight() == 4));
    REQUIRE((subsongMetadata.getLoopStartPosition() == 1));
    REQUIRE((subsongMetadata.getEndPosition() == 1));

    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        const auto psgs = subsong.getPsgs();
        REQUIRE((psgs.size() == 1));
        REQUIRE((psgs.at(0) == Psg(PsgType::ay, 1000000, 440.0F, 8000, PsgMixingOutput::ABC)));

        // Checks the Patterns.
        REQUIRE((subsong.getPatternCount() == 2));
        {
            const auto& pattern = subsong.getPatternFromIndex(0);
            REQUIRE((pattern.getChannelCount() == 3));
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 3));
            REQUIRE((pattern.getCurrentSpecialTrackIndex(true) == 0));
            REQUIRE((pattern.getCurrentSpecialTrackIndex(false) == 0));
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternFromIndex(1);
            REQUIRE((pattern.getChannelCount() == 3));
            REQUIRE((pattern.getCurrentTrackIndex(0) == 2));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
            REQUIRE((pattern.getCurrentSpecialTrackIndex(true) == 1));
            REQUIRE((pattern.getCurrentSpecialTrackIndex(false) == 1));
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Positions.
        {
            const auto& position = subsong.getPosition(0);
            REQUIRE((position.getPatternIndex() == 0));
            REQUIRE((position.getHeight() == 32));
            REQUIRE((position.getTransposition(0) == 0));
            REQUIRE((position.getTransposition(1) == 0));
            REQUIRE((position.getTransposition(2) == 0));
            REQUIRE((position.getMarkerName() == Position::firstMarkerName));
        }
        {
            const auto& position = subsong.getPosition(1);
            REQUIRE((position.getPatternIndex() == 1));
            REQUIRE((position.getHeight() == 29));
            REQUIRE((position.getTransposition(0) == 0));
            REQUIRE((position.getTransposition(1) == 3));
            REQUIRE((position.getTransposition(2) == 7));
        }

        // Checks the Tracks.
        {
            // Position 0, channel 0.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(0);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0, Cell::build((12 * 4) + 0, 1) },
                    { 1, Cell::build((12 * 4) + 2, 1) },
                    { 2, Cell::build((12 * 4) + 4, 1) },
                    { 3, Cell::build((12 * 4) + 5, 1) },
                    { 4, Cell::build((12 * 4) + 7, 1) },
                    { 5, Cell::build((12 * 4) + 5, 1) },
                    { 6, Cell::build((12 * 4) + 4, 1) },
                    { 7, Cell::build((12 * 4) + 2, 1) },
                    { 8, Cell::build((12 * 4) + 0, 1) },
            });
            REQUIRE(success);
        }
        {
            // Position 0, channel 1.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(1);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0, Cell::buildRst() },
                    { 11, Cell::build((12 * 5) + 0, 2) },
                    { 12, Cell::build((12 * 5) + 2, 2) },
                    { 13, Cell::build((12 * 5) + 4, 2) },
                    { 14, Cell::build((12 * 5) + 5, 2) },
                    { 15, Cell::build((12 * 5) + 7, 2) },
                    { 16, Cell::build((12 * 5) + 5, 2) },
                    { 17, Cell::build((12 * 5) + 4, 2) },
                    { 18, Cell::build((12 * 5) + 2, 2) },
                    { 19, Cell::build((12 * 5) + 0, 2) },
                    { 21, Cell::buildRst() },
            });
            REQUIRE(success);
        }
        {
            // Position 0, channel 2.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(2);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0, Cell::buildRst() },
                    { 0x15, Cell::build((12 * 4) + 4, 3) },
                    { 0x19, Cell(Note::buildNote((12 * 4) + 9), OptionalInt(), CellEffects({{ Effect::pitchGlide, 0x200 }})) },
                    { 0x1c, Cell(Note::buildNote((12 * 5) + 0), OptionalInt(), CellEffects({{ Effect::pitchGlide, 0x200 }})) },
                    { 0x1f, Cell::buildRst() },
            });
            REQUIRE(success);
        }

        // Position 1, channel 0-1-2.
        for (auto channelIndex = 0; channelIndex <= 2; ++channelIndex) {
            const auto patternIndex = subsong.getPosition(1).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(channelIndex);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0,   Cell::buildRst() },
                    { 0x2, Cell::build((12 * 4) + 5, 3) },
                    { 0x5, Cell::build((12 * 4) + 7, 3) },
                    { 0x8, Cell::build((12 * 4) + 9, 3) },
            });
            REQUIRE(success);
        }
    });

    // Checks the Instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE((instruments.size() == 4));

        {
            // Instrument 1. Decreasing sound.
            const auto& instrument = instruments.at(1);
            REQUIRE((instrument->getName() == "Piano"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0x47, 0x47, false)));
            REQUIRE(psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(2).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(0x10).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc)));
            REQUIRE(psgPart.getCellRefConst(0x20).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x9)));
            REQUIRE(psgPart.getCellRefConst(0x30).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x5)));
            REQUIRE(psgPart.getCellRefConst(0x40).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x2)));
            REQUIRE(psgPart.getCellRefConst(0x47).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x1)));
            REQUIRE((psgPart.getLength() == 0x48));
        }

        {
            // Instrument 2.
            const auto& instrument = instruments.at(2);
            REQUIRE((instrument->getName() == "Bidule"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0xd, 0xd, false)));
            REQUIRE(psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xe, 0, 7, 0)));
            REQUIRE(psgPart.getCellRefConst(2).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(0x5).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xa, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(0xa).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x4, 0, 7, 0)));
            REQUIRE(psgPart.getCellRefConst(0x13).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x0, 0, 0, 0)));
            REQUIRE((psgPart.getLength() == 0xe));
        }

        {
            // Instrument 3.
            const auto& instrument = instruments.at(3);
            REQUIRE((instrument->getName() == "Machin"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0, 2, true)));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 0)));
            REQUIRE((psgPart.getLength() == cellIndex));
        }
    });
}

TEST_CASE("CHP import, all instruments", "[ChpSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::AllSounds_chp, BinaryData::AllSounds_chpSize, false);

    // Parses.
    ChpSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "chp"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE((result != nullptr));
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE((report != nullptr));
    REQUIRE(report->isOk());
    REQUIRE((report->getWarningCount() == 0));
    REQUIRE((song != nullptr));

    // Checks the instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE((instruments.size() == 0x17));

        {
            // Instrument 1. Decreasing sound.
            const auto& instrument = instruments.at(1);
            REQUIRE((instrument->getName() == "Piano"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0xd5, 0xd5, false)));
            REQUIRE(psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(2).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(0x20).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd)));
            REQUIRE(psgPart.getCellRefConst(0x40).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb)));
            REQUIRE(psgPart.getCellRefConst(0x60).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x9)));
            REQUIRE(psgPart.getCellRefConst(0x80).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x6)));
            REQUIRE(psgPart.getCellRefConst(0xa0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x4)));
            REQUIRE(psgPart.getCellRefConst(0xd5).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x1)));
            REQUIRE((psgPart.getLength() == 0xd6));
        }

        {
            // Instrument 0x11. One volume down.
            const auto& instrument = instruments.at(0x11);
            REQUIRE((instrument->getName() == "Deflektor bass"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0x1, 0x1, true)));
            REQUIRE(psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb)));
            REQUIRE((psgPart.getLength() == 0x2));
        }

        {
            // Instrument 0x12. One volume up.
            const auto& instrument = instruments.at(0x12);
            REQUIRE((instrument->getName() == "Volume up once"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0x1, 0x1, true)));
            REQUIRE(psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x0)));
            REQUIRE(psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x5)));
            REQUIRE((psgPart.getLength() == 0x2));
        }

        {
            // Instrument 0x13. Commando bass, noise once and looping one special arp.
            const auto& instrument = instruments.at(0x13);
            REQUIRE((instrument->getName() == "One noise and looping once arp"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0x1, 0x1, true)));
            REQUIRE(psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 4, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, -1)));
            REQUIRE((psgPart.getLength() == 0x2));
        }

        {
            // Instrument 0x14. Fernandez drum pitch down.
            const auto& instrument = instruments.at(0x14);
            REQUIRE((instrument->getName() == "Fernandez drum pitch down"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0xa, 0xa, false)));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd, 0, 0, 0, -0x6)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc, 0, 0, 0, -0xc)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -0x12)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xa, 0, 0, 0, -0x18)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 0, -0x1e)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x7, 0, 0, 0, -0x24)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x6, 0, 0, 0, -0x2a)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x5, 0, 0, 0, -0x30)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x3, 0, 0, 0, -0x36)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x2, 0, 0, 0, -0x3c)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x1, 0, 0, 0, -0x42)));
            REQUIRE((psgPart.getLength() == cellIndex));
        }

        {
            // Instrument 0x15. Fernandez Drop.
            const auto& instrument = instruments.at(0x15);
            REQUIRE((instrument->getName() == "Fernandez Drop"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0x1f, 0x1f, false)));
            REQUIRE(psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -0x4)));
            REQUIRE(psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -0x8)));
            REQUIRE(psgPart.getCellRefConst(2).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -0xc)));
            REQUIRE(psgPart.getCellRefConst(0x10).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -0x44)));
            REQUIRE(psgPart.getCellRefConst(0x1f).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -0x80)));
            REQUIRE((psgPart.getLength() == 0x20));
        }

        {
            // Instrument 0x16. Fernandez flat vib.
            const auto& instrument = instruments.at(0x16);
            REQUIRE((instrument->getName() == "Fernandez vib"));
            REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE((psgPart.getSpeed() == 0));
            REQUIRE((psgPart.getMainLoop() == Loop(0x0, 0x7, true)));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0, -1)));
            REQUIRE((psgPart.getLength() == cellIndex));
        }
    });
}

}   // namespace arkostracker
