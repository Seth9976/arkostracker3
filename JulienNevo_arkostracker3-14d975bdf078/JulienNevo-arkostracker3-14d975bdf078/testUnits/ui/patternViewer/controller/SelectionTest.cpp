#include "../../../catch.hpp"

#include "../../../../source/ui/patternViewer/controller/Selection.h"

namespace arkostracker 
{

/** Tests the Selection class. */

TEST_CASE("BuildForTrack, selection empty", "[Selection]")
{
    // Given.
    Selection selection;

    // When/then.
    REQUIRE(selection.extractForTrack(0) == Selection());
    REQUIRE(selection.extractForTrack(1) == Selection());
    REQUIRE(selection.extractForTrack(2) == Selection());
    REQUIRE(selection.extractForTrack(10) == Selection());
}

TEST_CASE("BuildForTrack for channel 0, from a selection with three whole tracks", "[Selection]")
{
    // Given.
    constexpr auto startLine = 3;
    constexpr auto endLine = 10;
    const Selection selection(startLine, CursorLocation::onTrack(0, CellCursorRank::first),
                        endLine, CursorLocation::onTrack(2, CellCursorRank::last), false, false);

    // When
    auto newSelection = selection.extractForTrack(0);

    // Then.
    REQUIRE(newSelection == Selection(startLine, CursorLocation::onTrack(0, CellCursorRank::first), endLine, CursorLocation::onTrack(0, CellCursorRank::last), false, false));
}

TEST_CASE("BuildForTrack for channel 1, from a selection with three whole tracks", "[Selection]")
{
    // Given.
    constexpr auto startLine = 2;
    constexpr auto endLine = 4;
    Selection selection(startLine, CursorLocation::onTrack(0, CellCursorRank::first),
                        endLine, CursorLocation::onTrack(2, CellCursorRank::last), false, false);

    // When
    auto newSelection = selection.extractForTrack(1);

    // Then.
    REQUIRE(newSelection == Selection(startLine, CursorLocation::onTrack(1, CellCursorRank::first), endLine, CursorLocation::onTrack(1, CellCursorRank::last), false, false));
}

TEST_CASE("BuildForTrack for channel 2, from a selection with three whole tracks", "[Selection]")
{
    // Given.
    constexpr auto startLine = 6;
    constexpr auto endLine = 3;
    Selection selection(startLine, CursorLocation::onTrack(0, CellCursorRank::first),
                        endLine, CursorLocation::onTrack(2, CellCursorRank::last), false, false);

    // When
    auto newSelection = selection.extractForTrack(2);

    // Then.
    REQUIRE(newSelection == Selection(startLine, CursorLocation::onTrack(2, CellCursorRank::first), endLine, CursorLocation::onTrack(2, CellCursorRank::last), false, false));
}

TEST_CASE("BuildForTrack for channel 0, a selection of 2 tracks, partial start", "[Selection]")
{
    // Given.
    constexpr auto startLine = 0;
    constexpr auto endLine = 10;
    Selection selection(startLine, CursorLocation::onTrack(0, CellCursorRank::cursorOnInstrumentDigit1),
                        endLine, CursorLocation::onTrack(1, CellCursorRank::first), false, false);

    // When
    auto newSelection = selection.extractForTrack(0);

    // Then.
    REQUIRE(newSelection == Selection(startLine, CursorLocation::onTrack(0, CellCursorRank::cursorOnInstrumentDigit1),
                                      endLine, CursorLocation::onTrack(0, CellCursorRank::last), false, false));
}

TEST_CASE("BuildForTrack for channel 1, from a selection of 2 tracks, partial end", "[Selection]")
{
    // Given.
    constexpr auto startLine = 1;
    constexpr auto endLine = 1;
    Selection selection(startLine, CursorLocation::onTrack(0, CellCursorRank::cursorOnInstrumentDigit1),
                        endLine, CursorLocation::onTrack(1, CellCursorRank::cursorOnEffect2Digit2), false, false);

    // When
    auto newSelection = selection.extractForTrack(1);

    // Then.
    REQUIRE(newSelection == Selection(startLine, CursorLocation::onTrack(1, CellCursorRank::first),
                                      endLine, CursorLocation::onTrack(1, CellCursorRank::cursorOnEffect2Digit2), false, false));
}

TEST_CASE("BuildForTrack for channel 1, from a selection of this track, partial", "[Selection]")
{
    // Given.
    constexpr auto startLine = 1;
    constexpr auto endLine = 7;
    Selection selection(startLine, CursorLocation::onTrack(1, CellCursorRank::cursorOnEffect1Number),
                        endLine, CursorLocation::onTrack(1, CellCursorRank::cursorOnEffect2Digit3), false, false);

    // When
    auto newSelection = selection.extractForTrack(1);

    // Then.
    REQUIRE(newSelection == Selection(startLine, CursorLocation::onTrack(1, CellCursorRank::cursorOnEffect1Number),
                                      endLine, CursorLocation::onTrack(1, CellCursorRank::cursorOnEffect2Digit3), false, false));
}

TEST_CASE("BuildForTrack for channel 1, from a selection of this track, full", "[Selection]")
{
    // Given.
    constexpr auto startLine = 1;
    constexpr auto endLine = 7;
    Selection selection(startLine, CursorLocation::onTrack(1, CellCursorRank::first),
                        endLine, CursorLocation::onTrack(1, CellCursorRank::last), false, false);

    // When
    auto newSelection = selection.extractForTrack(1);

    // Then.
    REQUIRE(newSelection == Selection(startLine, CursorLocation::onTrack(1, CellCursorRank::first),
                                      endLine, CursorLocation::onTrack(1, CellCursorRank::last), false, false));
}

TEST_CASE("BuildForTrack for channel 2, from a selection of track 0 and 1 (partial)", "[Selection]")
{
    // Given.
    constexpr auto startLine = 1;
    constexpr auto endLine = 7;
    Selection selection(startLine, CursorLocation::onTrack(0, CellCursorRank::cursorOnNote),
                        endLine, CursorLocation::onTrack(1, CellCursorRank::cursorOnEffect2Number), false, false);

    // When
    auto newSelection = selection.extractForTrack(2);

    // Then.
    REQUIRE(newSelection.isEmpty());
}


}   // namespace arkostracker

