#include "../../catch.hpp"

#include "../../../source/export/SongExportResult.h"
#include "../../../source/export/akm/process/AkmSequenceEncoder.h"

namespace arkostracker 
{
static constexpr auto valueNoteAndEffects = 12U;                                  // Value indicating there is a note, and there are effects.

static constexpr auto valueNoNoteMaybeEffects = valueNoteAndEffects + 1U;                     // Value indicating there is no note. There may be effects.
static constexpr auto valueNewEscapeNote = valueNoNoteMaybeEffects + 1U;                      // Value indicating the note must be escaped.
static constexpr auto valueSameEscapeNote = valueNewEscapeNote + 1U;                          // Value indicating the note is the same (it is an escape note).

static constexpr auto waitFlagsNewWait = 0b11U;
static constexpr auto instrumentFlagsSameEscape = 0b00U;                          // The same escape instrument (so NOT primary or secondary!)
static constexpr auto instrumentFlagsPrimary = 0b01U;
static constexpr auto instrumentFlagsSecondary = 0b10U;
static constexpr auto instrumentFlagsNewInstrument = 0b11U;                       // New, but still NOT primary or secondary!

static constexpr auto waitFlagsPrimary = 0b01U;
static constexpr auto waitFlagsSecondary = 0b10U;
static constexpr auto waitFlagsSameEscape = 0b00U;                                // The same escape wait (so NOT primary or secondary!)

//const static unsigned int effectNumberResetWithInvertedVolume = 0U;         // Number of effect for reset with inverted volume.
static constexpr auto effectNumberVolume = 1U;                          // Number of effect for volume.
/*const static unsigned int effectNumberPitchUpDown = 2U;                     // Number of effect for (fast)pitch up/down.
const static unsigned int effectNumberArpeggioTableEffect = 3U;             // Number of effect for arpeggio table.
const static unsigned int effectNumberPitchTableEffect = 4U;                // Number of effect for pitch table.
const static unsigned int effectNumberForceInstrumentSpeedEffect = 5U;      // Number of effect for Force instrument speed.
const static unsigned int effectNumberForceArpeggioSpeedEffect = 6U;        // Number of effect for Force arpeggio speed.
const static unsigned int effectNumberForcePitchSpeedEffect = 7U;           // Number of effect for Force pitch speed.*/

TEST_CASE("AkmSequenceEncoder, one note, primary instr, refNote0, end track wait", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(40, 0));

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 0,           // Start instrument in tracks.
                                                                 4,           // Start wait in tracks.
                                                                 { 40 }       // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // Reference note, primary instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == ((waitFlagsNewWait << 6U) | (instrumentFlagsPrimary << 4U) | 0U)));
    // Escape wait value.
    REQUIRE((dataAndComments.at(index++).first == 127U));
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, one note with unknown effect, unknown effect alone, must be ignored", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(40, 0, CellEffects(
        { { Effect::volumeOut, 5} }         // It should be ignored.
    )));
    track.setCell(10, Cell({ }, { }, CellEffects(
        { { Effect::volumeIn, 5} }         // It should be ignored.
    )));

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 0,           // Start instrument in tracks.
                                                                 4,           // Start wait in tracks.
                                                                 { 40 }       // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // Reference note, primary instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == ((waitFlagsNewWait << 6U) | (instrumentFlagsPrimary << 4U) | 0U)));
    // Escape wait value.
    REQUIRE((dataAndComments.at(index++).first == 127U));
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, one note, secondary instr, refNote1, end track wait", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(40, 1));

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 0,           // Start instrument in tracks.
                                                                 4,           // Start wait in tracks.
                                                                 { 20, 40 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // Reference note, secondary instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == ((waitFlagsNewWait << 6U) | (instrumentFlagsSecondary << 4U) | 1U)));
    // Escape wait value.
    REQUIRE((dataAndComments.at(index++).first == 127U));
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, two notes, primary and escape instr, refNote5, primary wait, end track wait", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(45, 1));
    track.setCell(1, Cell::build(70, 2));

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 1, 5,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 0,           // Start instrument in tracks.
                                                                 4,           // Start wait in tracks.
                                                                 { 20, 40, 70, 30, 41, 45, 99, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // Reference note, primary instrument, primary wait.
    REQUIRE((dataAndComments.at(index++).first == (5U | (instrumentFlagsPrimary << 4U) | (waitFlagsPrimary << 6U))));
    // Reference note, primary instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (2U | (instrumentFlagsNewInstrument << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 2U));        // Escape instrument.
    REQUIRE((dataAndComments.at(index++).first == 127U));      // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, three notes, escape instr and secondary and escape instr, ref notes, primary secondary wait, end track wait", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(30, 10));      // Wait 1.
    track.setCell(2, Cell::build(40, 5));      // Wait 2.
    track.setCell(5, Cell::build(50, 10));      // Wait: end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 50, 5,       // Primary/secondary instruments.
                                                                 2, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 0,           // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 70, 30, 41, 40, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // Reference note, escape instrument, secondary wait.
    REQUIRE((dataAndComments.at(index++).first == (1U | (instrumentFlagsNewInstrument << 4U) | (waitFlagsSecondary << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 10U));        // Escape instrument.
    // Reference note, secondary instrument, primary wait.
    REQUIRE((dataAndComments.at(index++).first == (3U | (instrumentFlagsSecondary << 4U) | (waitFlagsPrimary << 6U))));
    // Reference note, same escape instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (5U | (instrumentFlagsSameEscape << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 127U));      // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, four notes, escape instr and same, ref notes, escape and primary wait, end track wait", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(30, 9));      // Wait 10.
    track.setCell(11, Cell::build(40, 5));      // Wait 2.
    track.setCell(14, Cell::build(50, 6));      // Wait 10.
    track.setCell(25, Cell::build(30, 9));      // Wait: end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 5, 6,        // Primary/secondary instruments.
                                                                 2, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 0,           // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 70, 30, 41, 40, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // Reference note, escape instrument, escape wait.
    REQUIRE((dataAndComments.at(index++).first == (1U | (instrumentFlagsNewInstrument << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 9U));        // Escape instrument.
    REQUIRE((dataAndComments.at(index++).first == 10U));        // Escape wait.
    // Reference note, primary instrument, primary wait.
    REQUIRE((dataAndComments.at(index++).first == (3U | (instrumentFlagsPrimary << 4U) | (waitFlagsPrimary << 6U))));
    // Reference note, secondary instrument, same escape wait.
    REQUIRE((dataAndComments.at(index++).first == (5U | (instrumentFlagsSecondary << 4U) | (waitFlagsSameEscape << 6U))));
    // Reference note, same escape instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (1U | (instrumentFlagsSameEscape << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 127U));      // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, four notes, escape and primary notes", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(31, 0));      // Wait 1.
    track.setCell(2, Cell::build(40, 0));      // Wait 1.
    track.setCell(4, Cell::build(31, 1));      // Wait 1.
    track.setCell(6, Cell::build(32, 1));      // Wait: end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 50,          // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 70, 30, 41, 40, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 1: New escape note, primary instrument, secondary wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsPrimary << 4U) | (waitFlagsSecondary << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 31U));       // New escape note.
    // 2: Reference note, primary instrument, secondary wait.
    REQUIRE((dataAndComments.at(index++).first == (3U | (instrumentFlagsPrimary << 4U) | (waitFlagsSecondary << 6U))));
    // 3: Same escape note, secondary instrument, secondary wait.
    REQUIRE((dataAndComments.at(index++).first == (valueSameEscapeNote | (instrumentFlagsSecondary << 4U) | (waitFlagsSecondary << 6U))));
    // 4: New escape note, secondary instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsSecondary << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 32U));       // New escape note.
    REQUIRE((dataAndComments.at(index++).first == 127U));      // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, three notes, start with several empty cells, escape wait", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(10, Cell::build(40, 0));      // 1 + Wait: 9.
    track.setCell(20, Cell::build(41, 0));      // 2 + Wait: 6.
    track.setCell(27, Cell::build(33, 1));      // 3 + Wait: end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 50,          // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 40, 70, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Empty note, no effect, escape wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0U << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 9U));        // New wait.
    // 1: Reference note, primary instrument, same escape wait.
    REQUIRE((dataAndComments.at(index++).first == (0U | (instrumentFlagsPrimary << 4U) | (waitFlagsSameEscape << 6U))));
    // 2: Reference note, primary instrument, new escape wait.
    REQUIRE((dataAndComments.at(index++).first == (3U | (instrumentFlagsPrimary << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 6U));
    // 3: New escape note, secondary instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsSecondary << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 33U));       // New escape note.
    REQUIRE((dataAndComments.at(index++).first == 127U));      // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, three notes, start with one empty cell", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(1, Cell::build(10, 3));      // 1 + Wait: end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 50,          // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 40, 70, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Empty note, no effect, primary wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0U << 4U) | (waitFlagsPrimary << 6U))));
    // 1: Escape note, escape instrument, same escape wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsNewInstrument << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 10U));           // Escape note.
    REQUIRE((dataAndComments.at(index++).first == 3U));            // Escape instrument.
    REQUIRE((dataAndComments.at(index++).first == 127U));          // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, start with two empty cells", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(2, Cell::build(10, 3));      // 1 + Wait: end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 50,          // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 40, 70, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Empty note, no effect, secondary wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0U << 6U) | (waitFlagsSecondary << 6U))));
    // 1: Escape note, escape instrument, same escape wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsNewInstrument << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 10U));           // Escape note.
    REQUIRE((dataAndComments.at(index++).first == 3U));            // Escape instrument.
    REQUIRE((dataAndComments.at(index++).first == 127U));          // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, end on 127", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(127, Cell::build(100, 3));        // 1 + Wait: none needed (use same escape as a convention).

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 50,          // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 40, 70, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Empty note, no effect, escape wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0U << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 126U));
    // 1: Reference note, escape instrument, no wait (because line 127), but encoded as same escape wait.
    REQUIRE((dataAndComments.at(index++).first == (6U | (instrumentFlagsNewInstrument << 4U) | (waitFlagsSameEscape << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 3U));            // Escape instrument.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, use default escape instrument", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(2, Cell::build(40, 3));        // 1 + Wait 0.
    track.setCell(3, Cell::build(70, 1));        // 2 + Wait 1.
    track.setCell(5, Cell::build(71, 3));        // 3 + Wait end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 3,           // Start instrument in tracks.
                                                                 40,          // Start wait in tracks.
                                                                 { 40, 70, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Empty note, no effect, primary wait.
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0U << 4U) | (waitFlagsSecondary << 6U))));
    // 1: Reference note, same escape instrument (default), primary wait.
    REQUIRE((dataAndComments.at(index++).first == (0U | (instrumentFlagsSameEscape << 4U) | (waitFlagsPrimary << 6U))));
    // 2: Reference note, secondary instrument, secondary wait.
    REQUIRE((dataAndComments.at(index++).first == (1U | (instrumentFlagsSecondary << 4U) | (waitFlagsSecondary << 6U))));
    // 3: New escape note, same escape instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsSameEscape << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 71U));           // Escape note.
    REQUIRE((dataAndComments.at(index++).first == 127U));          // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, use default escape wait", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(10, Cell::build(40, 3));        // 1 + Wait 0.
    track.setCell(11, Cell::build(70, 1));        // 1 + Wait 9.
    track.setCell(21, Cell::build(71, 3));        // 3 + Wait end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 39,          // Start note in tracks.
                                                                 3,           // Start instrument in tracks.
                                                                 9,          // Start wait in tracks.
                                                                 { 40, 70, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Empty note, no effect, same escape wait (default).
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0U << 4U) | (waitFlagsSameEscape << 6U))));
    // 1: Reference note, same escape instrument (default), primary wait.
    REQUIRE((dataAndComments.at(index++).first == (0U | (instrumentFlagsSameEscape << 4U) | (waitFlagsPrimary << 6U))));
    // 2: Reference note, secondary instrument, same escape wait.
    REQUIRE((dataAndComments.at(index++).first == (1U | (instrumentFlagsSecondary << 4U) | (waitFlagsSameEscape << 6U))));
    // 3: New escape note, same escape instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsSameEscape << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 71U));           // Escape note.
    REQUIRE((dataAndComments.at(index++).first == 127U));          // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, use default escape note", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(10, Cell::build(10, 3));        // 1 + Wait 0.
    track.setCell(11, Cell::build(10, 1));        // 1 + Wait 9.
    track.setCell(21, Cell::build(71, 3));        // 3 + Wait end of track.

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 0, 1,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 10,          // Start note in tracks.
                                                                 3,           // Start instrument in tracks.
                                                                 9,          // Start wait in tracks.
                                                                 { 40, 70, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Empty note, no effect, same escape wait (default).
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0U << 4U) | (waitFlagsSameEscape << 6U))));
    // 1: Same escape note, same escape instrument (default), primary wait.
    REQUIRE((dataAndComments.at(index++).first == (valueSameEscapeNote | (instrumentFlagsSameEscape << 4U) | (waitFlagsPrimary << 6U))));
    // 2: Same escape note, secondary instrument, same escape wait.
    REQUIRE((dataAndComments.at(index++).first == (valueSameEscapeNote | (instrumentFlagsSecondary << 4U) | (waitFlagsSameEscape << 6U))));
    // 3: New escape note, same escape instrument, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (valueNewEscapeNote | (instrumentFlagsSameEscape << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 71U));           // Escape note.
    REQUIRE((dataAndComments.at(index++).first == 127U));          // Escape wait value.
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, note with volume effect", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    track.setCell(0, Cell::build(40, 1, CellEffects({{ Effect::volume, 10 }})));    // Stupid warning. NOLINT(clion-misra-cpp2008-5-2-4)

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 1, 0,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 41,          // Start note in tracks.
                                                                 3,           // Start instrument in tracks.
                                                                 9,          // Start wait in tracks.
                                                                 { 70, 40, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // 0: Reference note 0, Effect, new escape wait (end of track).
    // First, the "effect with note" flag.
    REQUIRE((dataAndComments.at(index++).first == valueNoteAndEffects));
    // Then, the reference note, primary instrument, new escape wait (end of track). No effect flag, already set in the byte before.
    REQUIRE((dataAndComments.at(index++).first == (1U | (instrumentFlagsPrimary << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 127U));          // Escape wait value.
    REQUIRE((dataAndComments.at(index++).first == ((effectNumberVolume << 1U) | ((15U - 10U) << 4U))));
    REQUIRE((dataAndComments.size() == index));
}

TEST_CASE("AkmSequenceEncoder, volume effect only", "[AkmSequenceEncoder]")
{
    // Given.
    SongExportResult songExportResult;

    Track track;
    Cell cell;
    cell.addEffect(Effect::volume, 3);
    track.setCell(0, cell);

    // When.
    const auto dataAndComments = AkmSequenceEncoder::encodeTrack(songExportResult, track, false,
                                                                 1, 0,        // Primary/secondary instruments.
                                                                 0, 1,        // Primary/secondary waits.
                                                                 41,          // Start note in tracks.
                                                                 3,           // Start instrument in tracks.
                                                                 9,          // Start wait in tracks.
                                                                 { 70, 40, 30, 41, 45, 50, 100 }   // Most used note indexes.
    );

    // Then.
    size_t index = 0U;
    // No note but effect, effect flag, new escape wait (end of track).
    REQUIRE((dataAndComments.at(index++).first == (valueNoNoteMaybeEffects | (0b01U << 4U) | (waitFlagsNewWait << 6U))));
    REQUIRE((dataAndComments.at(index++).first == 127U));          // Escape wait value.
    // Volume effect, with inverted value.
    REQUIRE((dataAndComments.at(index++).first == ((effectNumberVolume << 1U) | ((15U - 3U) << 4U))));
    REQUIRE((dataAndComments.size() == index));
}

}   // namespace arkostracker
