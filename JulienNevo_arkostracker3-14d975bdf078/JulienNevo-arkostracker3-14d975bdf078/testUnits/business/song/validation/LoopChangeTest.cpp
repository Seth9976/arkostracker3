#include "../../../catch.hpp"

#include "../../../../source/business/model/Loop.h"
#include "../../../../source/business/song/validation/LoopChange.h"

namespace arkostracker 
{

TEST_CASE("remove inside full loop, at first", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(0, 10, true);
    constexpr auto originalLength = 11;
    constexpr auto removeIndex = 0;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 0);
    REQUIRE(result.getEndIndex() == 9);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove inside loop, at first", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 10, true);
    constexpr auto originalLength = 11;
    constexpr auto removeIndex = 4;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 9);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove inside loop, in middle", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 10, true);
    constexpr auto originalLength = 11;
    constexpr auto removeIndex = 7;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 9);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove inside loop, at end", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 10, true);
    constexpr auto originalLength = 14;
    constexpr auto removeIndex = 10;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 9);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove before loop", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 7, true);
    constexpr auto originalLength = 10;
    constexpr auto removeIndex = 3;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 6);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove after loop", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 7, true);
    constexpr auto originalLength = 10;
    constexpr auto removeIndex = 8;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 7);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove inside loop, width 2, before", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 5, false);
    constexpr auto originalLength = 10;
    constexpr auto removeIndex = 2;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 4);
    REQUIRE(result.isLooping() == false);
}

TEST_CASE("remove inside loop, width 2, inside", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 5, true);
    constexpr auto originalLength = 10;
    constexpr auto removeIndex = 4;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 4);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove inside loop, width 2, end", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 5, true);
    constexpr auto originalLength = 10;
    constexpr auto removeIndex = 5;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 4);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove inside loop, width 1, before", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 4, false);
    constexpr auto originalLength = 10;
    constexpr auto removeIndex = 1;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 3);
    REQUIRE(result.isLooping() == false);
}

TEST_CASE("remove inside loop, width 1, inside", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 4, false);
    constexpr auto originalLength = 10;
    constexpr auto removeIndex = 4;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 4);
    REQUIRE(result.isLooping() == false);
}

TEST_CASE("remove inside loop, width 1, end shift", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 4, true);
    constexpr auto originalLength = 5;
    constexpr auto removeIndex = 4;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 3);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove inside loop, width 2, end shift", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(4, 5, true);
    constexpr auto originalLength = 6;
    constexpr auto removeIndex = 5;

    // When.
    const auto result = LoopChange::remove(removeIndex, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 4);
    REQUIRE(result.isLooping() == true);
}


// =======================================================================

TEST_CASE("remove multiple", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, true);
    constexpr auto originalLength = 15;

    // When.
    const auto result = LoopChange::remove({ 0, 1, 5, 11 }, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 1);
    REQUIRE(result.getEndIndex() == 7);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("remove multiple, 2", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 7, false);
    constexpr auto originalLength = 15;

    // When.
    const auto result = LoopChange::remove({ 6, 7, 8 }, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 5);
    REQUIRE(result.isLooping() == false);
}

TEST_CASE("remove multiple, any order", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, true);
    constexpr auto originalLength = 15;

    // When.
    const auto result = LoopChange::remove({ 12, 0, 11, 5, 1 }, originalLoop, originalLength);

    // Then.
    REQUIRE(result.getStartIndex() == 1);
    REQUIRE(result.getEndIndex() == 7);
    REQUIRE(result.isLooping() == true);
}


// =======================================================================

TEST_CASE("insert before", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, true);
    constexpr auto insertIndex = 0;

    // When.
    const auto result = LoopChange::insert(insertIndex, originalLoop);

    // Then.
    REQUIRE(result.getStartIndex() == 4);
    REQUIRE(result.getEndIndex() == 11);
    REQUIRE(result.isLooping() == true);
}

TEST_CASE("insert inside first", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, false);
    constexpr auto insertIndex = 3;

    // When.
    const auto result = LoopChange::insert(insertIndex, originalLoop);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 11);
    REQUIRE(result.isLooping() == false);
}

TEST_CASE("insert inside", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, false);
    constexpr auto insertIndex = 6;

    // When.
    const auto result = LoopChange::insert(insertIndex, originalLoop);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 11);
    REQUIRE(result.isLooping() == false);
}

TEST_CASE("insert end", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, false);
    constexpr auto insertIndex = 10;

    // When.
    const auto result = LoopChange::insert(insertIndex, originalLoop);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 11);
    REQUIRE(result.isLooping() == false);
}

TEST_CASE("insert after", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, true);
    constexpr auto insertIndex = 11;

    // When.
    const auto result = LoopChange::insert(insertIndex, originalLoop);

    // Then.
    REQUIRE(result.getStartIndex() == 3);
    REQUIRE(result.getEndIndex() == 10);
    REQUIRE(result.isLooping() == true);
}

// =======================================================================

TEST_CASE("insert multiple", "[LoopChange]")
{
    // Given.
    const Loop originalLoop(3, 10, true);

    // When.
    const auto result = LoopChange::insert({ 0, 2, 3, 7, 10, 11, 12, 15, 100 }, originalLoop);

    // Then.
    REQUIRE(result.getStartIndex() == 5);
    REQUIRE(result.getEndIndex() == 15);
    REQUIRE(result.isLooping() == true);
}

}   // namespace arkostracker
