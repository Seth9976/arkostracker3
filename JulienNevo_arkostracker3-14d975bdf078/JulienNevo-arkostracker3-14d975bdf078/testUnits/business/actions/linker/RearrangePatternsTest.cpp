#include "../../../catch.hpp"

#include "../../../../source/business/actions/linker/RearrangePatterns.h"
#include "../../../../source/song/Song.h"
#include "../../../controllers/SongControllerForTest.h"

namespace arkostracker
{

TEST_CASE("RearrangePatterns, keep unused", "[RearrangePatterns]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // 0, 1, 2, 3, 4, 5, 6, 7, 8
        // Patterns to have, in order:
        // 3, 1, 1, 1, 5, 2, 0, 0, [0

        const Position position0(3);
        const Position position1(1);
        const Position position2(1);
        const Position position3(1);
        const Position position4(5);          // Pattern 4 is unused.
        const Position position5(2);
        const Position position6(0);
        const Position position7(0);
        const Position position8(0);

        subsong.setPosition(0, position0);  // Position 0 already exists.
        subsong.addPosition(position1);
        subsong.addPosition(position2);
        subsong.addPosition(position3);
        subsong.addPosition(position4);
        subsong.addPosition(position5);
        subsong.addPosition(position6);
        subsong.addPosition(position7);
        subsong.addPosition(position8);
        subsong.setLoopAndEndStartPosition(0, 8);

        // Creates the patterns.
        subsong.setPattern(0, Pattern({ 0, 1, 2 }, 0, 0)); // Pattern 0 already exists.
        subsong.addPattern(Pattern({ 3, 4, 5 }, 0, 0));             // 1
        subsong.addPattern(Pattern({ 6, 7, 8 }, 0, 0));
        subsong.addPattern(Pattern({ 9, 10, 11 }, 0, 0));           // 3
        subsong.addPattern(Pattern({ 12, 13, 14 }, 0, 0));          // 4, unused.
        subsong.addPattern(Pattern({ 15, 16, 17 }, 0, 0));          // 5
        subsong.addPattern(Pattern({ 18, 19, 20 }, 0, 0));          // 6, unused.
    });

    SongControllerForTest songController(std::move(baseSong));

    RearrangePatterns action(songController, subsongId, false);

    // When.
    const auto actionResult = action.perform();
    REQUIRE((actionResult));

    // Then.
    // 0, 1, 2, 3, 4, 5, 6, 7, 8
    // 3, 1, 1, 1, 5, 2, 0, 0, [0
    // Patterns should be in order:
    // 0, 1, 1, 1, 2, 3, 4, 4, [4

    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 3));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 4));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 4));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 4));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 8));
        REQUIRE((subsong.getLength() == 9));

        REQUIRE((subsong.getPatternCount() == 7));

        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 9));            // Was pattern 3.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 10));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 11));
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));            // Was pattern 1.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(2);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(3);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(4);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 15));            // Was pattern 5.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 16));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 17));
        }
        {
            const auto& pattern = subsong.getPatternRef(5);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 6));            // Was pattern 2.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 7));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 8));
        }
        {
            const auto& pattern = subsong.getPatternRef(6);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));            // Was pattern 0.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(7);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(8);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternFromIndex(5);            // Unused.
            REQUIRE((pattern.getCurrentTrackIndex(0) == 12));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 13));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 14));
        }
        {
            const auto& pattern = subsong.getPatternFromIndex(6);            // Unused.
            REQUIRE((pattern.getCurrentTrackIndex(0) == 18));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 19));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 20));
        }
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;

        // Then. Back to normal.
        // 0, 1, 2, 3, 4, 5, 6, 7, 8
        // 3, 1, 1, 1, 5, 2, 0, 0, [0
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 3));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 5));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 8));
        REQUIRE((subsong.getLength() == 9));

        REQUIRE((subsong.getPatternCount() == 7));

        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 9));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 10));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 11));
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(2);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(3);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(4);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 15));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 16));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 17));
        }
        {
            const auto& pattern = subsong.getPatternRef(5);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 6));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 7));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 8));
        }
        {
            const auto& pattern = subsong.getPatternRef(6);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(7);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(8);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
    });
}

TEST_CASE("RearrangePatterns, deleted unused", "[RearrangePatterns]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // 0, 1, 2, 3, 4, 5, 6, 7, 8
        // Patterns to have, in order:
        // 3, 1, 1, 1, 5, 2, 0, 0, [0

        const Position position0(3);
        const Position position1(1);
        const Position position2(1);
        const Position position3(1);
        const Position position4(5);          // Pattern 4 is unused.
        const Position position5(2);
        const Position position6(0);
        const Position position7(0);
        const Position position8(0);

        subsong.setPosition(0, position0);  // Position 0 already exists.
        subsong.addPosition(position1);
        subsong.addPosition(position2);
        subsong.addPosition(position3);
        subsong.addPosition(position4);
        subsong.addPosition(position5);
        subsong.addPosition(position6);
        subsong.addPosition(position7);
        subsong.addPosition(position8);
        subsong.setLoopAndEndStartPosition(0, 8);

        // Creates the patterns.
        subsong.setPattern(0, Pattern({ 0, 1, 2 }, 0, 0)); // Pattern 0 already exists.
        subsong.addPattern(Pattern({ 3, 4, 5 }, 0, 0));             // 1
        subsong.addPattern(Pattern({ 6, 7, 8 }, 0, 0));
        subsong.addPattern(Pattern({ 9, 10, 11 }, 0, 0));           // 3
        subsong.addPattern(Pattern({ 12, 13, 14 }, 0, 0));          // 4, unused.
        subsong.addPattern(Pattern({ 15, 16, 17 }, 0, 0));          // 5
        subsong.addPattern(Pattern({ 18, 19, 20 }, 0, 0));          // 6, unused.
    });

    SongControllerForTest songController(std::move(baseSong));

    RearrangePatterns action(songController, subsongId, true);

    // When.
    const auto actionResult = action.perform();
    REQUIRE((actionResult));

    // Then.
    // 0, 1, 2, 3, 4, 5, 6, 7, 8
    // 3, 1, 1, 1, 5, 2, 0, 0, [0
    // Patterns should be in order:
    // 0, 1, 1, 1, 2, 3, 4, 4, [4

    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 3));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 4));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 4));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 4));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 8));
        REQUIRE((subsong.getLength() == 9));

        REQUIRE((subsong.getPatternCount() == 5));

        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 9));            // Was pattern 3.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 10));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 11));
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));            // Was pattern 1.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(2);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(3);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(4);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 15));            // Was pattern 5.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 16));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 17));
        }
        {
            const auto& pattern = subsong.getPatternRef(5);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 6));            // Was pattern 2.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 7));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 8));
        }
        {
            const auto& pattern = subsong.getPatternRef(6);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));            // Was pattern 0.
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(7);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(8);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;

        // Then. Back to normal.
        // 0, 1, 2, 3, 4, 5, 6, 7, 8
        // 3, 1, 1, 1, 5, 2, 0, 0, [0
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 3));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 5));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 8));
        REQUIRE((subsong.getLength() == 9));

        REQUIRE((subsong.getPatternCount() == 7));

        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 9));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 10));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 11));
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(2);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(3);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 3));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 4));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 5));
        }
        {
            const auto& pattern = subsong.getPatternRef(4);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 15));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 16));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 17));
        }
        {
            const auto& pattern = subsong.getPatternRef(5);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 6));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 7));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 8));
        }
        {
            const auto& pattern = subsong.getPatternRef(6);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(7);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
        {
            const auto& pattern = subsong.getPatternRef(8);
            REQUIRE((pattern.getCurrentTrackIndex(0) == 0));
            REQUIRE((pattern.getCurrentTrackIndex(1) == 1));
            REQUIRE((pattern.getCurrentTrackIndex(2) == 2));
        }
    });
}

}   // namespace arkostracker
