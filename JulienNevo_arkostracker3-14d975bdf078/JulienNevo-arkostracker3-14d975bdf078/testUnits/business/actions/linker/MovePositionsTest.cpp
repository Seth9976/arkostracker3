#include "../../../catch.hpp"

#include "../../../../source/business/actions/linker/MovePositions.h"
#include "../../../../source/song/Song.h"
#include "../../../controllers/SongControllerForTest.h"

namespace arkostracker
{

TEST_CASE("MovePositions, simple move forward", "[MovePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    auto originalLength = 0;
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.addPosition(Position(2));
        subsong.setLoopAndEndStartPosition(0, 1);
        originalLength = subsong.getLength();
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0 };
    constexpr auto destinationPosition = 1;
    constexpr auto insertAfter = true;
    MovePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE(actionResult);

    // Then.
    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 1));
        REQUIRE((subsong.getLength() == originalLength));
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 1));
        REQUIRE((subsong.getLength() == originalLength));
    });
}

TEST_CASE("MovePositions, simple move forward of 2 positions at the end", "[MovePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    auto originalLength = 0;
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.addPosition(Position(2));
        subsong.setLoopAndEndStartPosition(0, 2);
        originalLength = subsong.getLength();
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0, 1 };
    constexpr auto destinationPosition = 2;
    constexpr auto insertAfter = true;
    MovePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE(actionResult);

    // Then.
    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 2));
        REQUIRE((subsong.getLength() == originalLength));
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 2));
        REQUIRE((subsong.getLength() == originalLength));
    });
}

/** There was a crash. */
TEST_CASE("MovePositions, move first and last at the end", "[MovePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    auto originalLength = 0;
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.addPosition(Position(2));
        subsong.addPosition(Position(3));
        subsong.setLoopAndEndStartPosition(0, 3);
        originalLength = subsong.getLength();
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0, 3 };
    constexpr auto destinationPosition = 3;
    constexpr auto insertAfter = true;
    MovePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE(actionResult);

    // Then.
    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 3));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 3));
        REQUIRE((subsong.getLength() == originalLength));
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 3));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 3));
        REQUIRE((subsong.getLength() == originalLength));
    });
}

/** The loop start was breaking. */
TEST_CASE("MovePositions, move all on second position", "[MovePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.addPosition(Position(2));
        subsong.addPosition(Position(3));
        subsong.setLoopAndEndStartPosition(0, 3);
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0, 1, 2, 3 };
    constexpr auto destinationPosition = 1;
    constexpr auto insertAfter = true;
    MovePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE_FALSE(actionResult);
}

}   // namespace arkostracker
