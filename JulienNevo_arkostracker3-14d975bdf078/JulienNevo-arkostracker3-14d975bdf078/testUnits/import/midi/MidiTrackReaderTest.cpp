#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/import/midi/MidiTrackReader.h"

namespace arkostracker 
{

static std::unique_ptr<juce::MidiFile> loadMidiFile(const void* data, const size_t size)
{
    // Loads the midi file.
    juce::MidiFile midiFile;
    juce::MemoryInputStream memoryInputStream(data, size, false);
    const auto success = midiFile.readFrom(memoryInputStream);
    REQUIRE(success);

    // Should be a Tick format, not SMTP!
    auto timeFormat = midiFile.getTimeFormat();
    REQUIRE(timeFormat > 0);

    return std::make_unique<juce::MidiFile>(midiFile);
}

TEST_CASE("Midi Track Reader, trackWithNotesLessAccuracy", "[MidiTrackReader]")
{
    // Loads the midi file.
    auto midiFile = loadMidiFile(BinaryData::ThreeChannelsWithEachItsProgram_mid, BinaryData::ThreeChannelsWithEachItsProgram_midSize);

    // Still explores the first track, but with a lower resolution: there should be less notes.
    constexpr auto ppq = 480;
    auto* midiSequence = midiFile->getTrack(1);      // Track 0 is "conductor".
    REQUIRE(midiSequence != nullptr);

    MidiTrackReader midiTrackReader(midiFile->getTimeFormat(), ppq, 10, true);
    auto cellIndexToCell = midiTrackReader.readMidiTrack(*midiSequence);

    REQUIRE(!cellIndexToCell.empty());
    REQUIRE(cellIndexToCell.size() < 49);
}

TEST_CASE("Midi Track Reader, trackWithNotesAndProgramChange", "[MidiTrackReader]")
{
    // Loads the midi file.
    auto midiFile = loadMidiFile(BinaryData::ThreeChannelsWithEachItsProgram_mid, BinaryData::ThreeChannelsWithEachItsProgram_midSize);

    // Explores the first track.
    constexpr auto ppq = 120;        // 960 / 8.
    auto* midiSequence = midiFile->getTrack(1);      // Track 0 is "conductor".
    REQUIRE(midiSequence != nullptr);

    MidiTrackReader midiTrackReader(midiFile->getTimeFormat(), ppq, 10, true);
    auto cellIndexToCell = midiTrackReader.readMidiTrack(*midiSequence);

    REQUIRE(cellIndexToCell.size() == 48);

    static const std::vector<std::vector<int>> cellIndexAndNoteAndInstruments =
            {
                    // Bar 0: four notes every 8 lines.
                    {0,     40, 1},
                    {8,     41, 1},
                    {16,    42, 1},
                    {24,    43, 1},

                    // Bar 1: 4 notes every 4 lines.
                    {32,   44, 1},
                    {36,   45, 1},
                    {40,   46, 1},
                    {44,   47, 1},
                    // Then: 8 notes every 2 lines. Change of Instrument.
                    {48,   48, 2},
                    {50,   49, 2},
                    {52,   50, 2},
                    {54,   51, 2},
                    {56,   52, 2},
                    {58,   53, 2},
                    {60,   54, 2},
                    {62,   55, 2},
                    // Bar 2: 16 notes every line.
                    {64,   36, 2},
                    {65,   37, 2},
                    {66,   38, 2},
                    {67,   39, 2},
                    {68,   40, 2},
                    {69,   41, 2},
                    {70,   42, 2},
                    {71,   43, 2},
                    {72,   44, 2},
                    {73,   45, 2},
                    {74,   46, 2},
                    {75,   47, 2},
                    {76,   48, 2},
                    {77,   49, 2},
                    {78,   50, 2},
                    {79,   51, 2}
            };

    auto indexInVector = 0;          // Only for debugging.
    for (auto cellIndexAndNoteAndInstrument : cellIndexAndNoteAndInstruments) {
        const auto cellIndex = cellIndexAndNoteAndInstrument.at(0);
        const auto noteIndex = cellIndexAndNoteAndInstrument.at(1);
        const auto instrumentIndex = cellIndexAndNoteAndInstrument.at(2);

        Cell cell = cellIndexToCell.find(cellIndex)->second;
        REQUIRE(cell.getNote().isPresent());
        REQUIRE(cell.getNote().getValue().getNote() == noteIndex);
        REQUIRE(cell.getInstrument().isPresent());
        REQUIRE(cell.getInstrument().getValue() == instrumentIndex);

        ++indexInVector;
    }
}

TEST_CASE("Midi Track Reader, buildRawPatternHeights_Simple4_4", "[MidiTrackReader]")
{
    MidiTrackReader midiTrackReader(960, 120, 10, true);
    midiTrackReader.setLastCellIndex(16 * 4 - 1);

    auto patternHeightsAndSignatureHeights = midiTrackReader.buildRawPatternHeights();

    // Checks.
    decltype(patternHeightsAndSignatureHeights) expected = { {16, 16}, {16, 16}, {16, 16}, {16, 16} };
    REQUIRE(patternHeightsAndSignatureHeights == expected);
}

TEST_CASE("Midi Track Reader, buildPatternHeights_Simple4_4Remaining", "[MidiTrackReader]")
{
    MidiTrackReader midiTrackReader(960, 120, 10, true);
    midiTrackReader.setLastCellIndex(16 * 4 - 5);     // The same pattern height should be used.

    auto patternHeights = midiTrackReader.buildPatternHeights();
    // Checks.
    decltype(patternHeights) expected = { 64 };
    REQUIRE(patternHeights == expected);
}

TEST_CASE("Midi Track Reader, buildPatternHeights_Simple3_4", "[MidiTrackReader]")
{
    MidiTrackReader midiTrackReader(960, 120, 10, true);
    midiTrackReader.addCellIndexToTimeSignature(0, { 3, 4 });
    midiTrackReader.setLastCellIndex(12 * 8 - 5);     // The same pattern height should be used.

    auto patternHeights = midiTrackReader.buildPatternHeights();
    // Checks.
    decltype(patternHeights) expected = { 48, 48 };
    REQUIRE(patternHeights == expected);
}

TEST_CASE("Midi Track Reader, buildPatternHeights_Simple3_4__4_4", "[MidiTrackReader]")
{
    MidiTrackReader midiTrackReader(960, 120, 10, true);
    midiTrackReader.addCellIndexToTimeSignature(0, { 3, 4 });
    midiTrackReader.addCellIndexToTimeSignature(12 * 8, { 4, 4 });
    midiTrackReader.setLastCellIndex(12 * 8 + 16 * 4 - 5);     // The same pattern height should be used.

    auto patternHeights = midiTrackReader.buildPatternHeights();
    // Checks.
    decltype(patternHeights) expected = { 48, 48, 64 };
    REQUIRE(patternHeights == expected);
}

}   // namespace arkostracker

