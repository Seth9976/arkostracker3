#include "../../../catch.hpp"

#include "../../../../source/business/actions/linker/ClonePositions.h"
#include "../../../../source/song/Song.h"
#include "../../../controllers/SongControllerForTest.h"
#include "../../../helper/TrackTestHelper.h"

namespace arkostracker
{

TEST_CASE("ClonePositions, clone position 0 to the end", "[ClonePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    auto originalLength = 0;
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.setLoopAndEndStartPosition(0, 1);
        originalLength = subsong.getLength();

        subsong.addPattern(Pattern({ 3, 4, 5 }, 1, 1));

        // Fills the Track 0, 1, 2, creates Track 3, 4, 5 and Special Tracks 1.
        subsong.setCell(0, 0, 0, Cell::build(0, 1));
        subsong.setCell(0, 0, 1, Cell::build(1, 1));
        subsong.setCell(0, 0, 2, Cell::build(2, 1));
        subsong.addTrack(TrackTestHelper::buildTestTrack(3));
        subsong.addTrack(TrackTestHelper::buildTestTrack(4));
        subsong.addTrack(TrackTestHelper::buildTestTrack(5));
        subsong.addSpecialTrack(true, TrackTestHelper::buildTestSpecialTrack(1));
        subsong.addSpecialTrack(false, TrackTestHelper::buildTestSpecialTrack(1));
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0 };
    constexpr auto destinationPosition = 1;
    constexpr auto insertAfter = true;
    ClonePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE(actionResult);

    // Then.
    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 2));
        REQUIRE((subsong.getLength() == (originalLength + 1)));

        REQUIRE((subsong.getTrackCount() == 9));
        REQUIRE((subsong.getSpecialTrackCount(true) == 3));
        REQUIRE((subsong.getSpecialTrackCount(false) == 3));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0),   0)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2),   2)));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0),   3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1),   4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2),   5)));
        // Position 2, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 0),   0)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 2),   2)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true),   0)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false),   0)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true),   1)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false),   1)));
        // Position 2, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, true),   0)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, false),   0)));
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 1));
        REQUIRE((subsong.getLength() == originalLength));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0),   0)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2),   2)));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0),   3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1),   4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2),   5)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true),   0)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false),   0)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true),   1)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false),   1)));

        REQUIRE((subsong.getTrackCount() == 6));
        REQUIRE((subsong.getSpecialTrackCount(true) == 2));
        REQUIRE((subsong.getSpecialTrackCount(false) == 2));
    });
}

TEST_CASE("ClonePositions, clone position 0 just after", "[ClonePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    auto originalLength = 0;
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.setLoopAndEndStartPosition(0, 1);
        originalLength = subsong.getLength();

        subsong.addPattern(Pattern({ 3, 4, 5 }, 1, 1));

        // Fills the Track 0, 1, 2, creates Track 3, 4, 5 and Special Tracks 1.
        subsong.setCell(0, 0, 0, Cell::build(0, 1));
        subsong.setCell(0, 0, 1, Cell::build(1, 1));
        subsong.setCell(0, 0, 2, Cell::build(2, 1));
        subsong.addTrack(TrackTestHelper::buildTestTrack(3));
        subsong.addTrack(TrackTestHelper::buildTestTrack(4));
        subsong.addTrack(TrackTestHelper::buildTestTrack(5));
        subsong.addSpecialTrack(true, TrackTestHelper::buildTestSpecialTrack(1));
        subsong.addSpecialTrack(false, TrackTestHelper::buildTestSpecialTrack(1));
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0 };
    constexpr auto destinationPosition = 1;
    constexpr auto insertAfter = false;
    ClonePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE(actionResult);

    // Then.
    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 2));
        REQUIRE((subsong.getLength() == (originalLength + 1)));

        REQUIRE((subsong.getTrackCount() == 9));
        REQUIRE((subsong.getSpecialTrackCount(true) == 3));
        REQUIRE((subsong.getSpecialTrackCount(false) == 3));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0),   0)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2),   2)));
        // Position 1, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0),   0)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2),   2)));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 0),   3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 1),   4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 2),   5)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true),   0)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false),   0)));
        // Position 1, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true),   0)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false),   0)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, true),   1)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, false),   1)));
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 1));
        REQUIRE((subsong.getLength() == originalLength));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0),   0)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2),   2)));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0),   3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1),   4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2),   5)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true),   0)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false),   0)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true),   1)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false),   1)));

        REQUIRE((subsong.getTrackCount() == 6));
        REQUIRE((subsong.getSpecialTrackCount(true) == 2));
        REQUIRE((subsong.getSpecialTrackCount(false) == 2));
    });
}

TEST_CASE("ClonePositions, clone position 0 just after, with linked and linked-to tracks, linked special tracks", "[ClonePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    auto originalLength = 0;
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.setLoopAndEndStartPosition(0, 1);
        originalLength = subsong.getLength();

        subsong.addPattern(Pattern({ 3, 4, 5 }, 1, 1));

        // Fills the Track 0, 1, 2, creates Track 3, 4, 5 and Special Tracks 1.
        subsong.setCell(0, 0, 0, Cell::build(0, 1));
        subsong.setCell(0, 0, 1, Cell::build(1, 1));
        subsong.setCell(0, 0, 2, Cell::build(2, 1));
        // Specials Tracks 0 will not be used, as pattern 0 Special tracks will be linked to the ones from pattern 1.
        subsong.setSpecialCell(true, 0, 0, SpecialCell::buildSpecialCell(1));
        subsong.setSpecialCell(false, 0, 0, SpecialCell::buildSpecialCell(2));
        subsong.addTrack(TrackTestHelper::buildTestTrack(3));
        subsong.addTrack(TrackTestHelper::buildTestTrack(4));
        subsong.addTrack(TrackTestHelper::buildTestTrack(5));
        subsong.addSpecialTrack(true, TrackTestHelper::buildTestSpecialTrack(9));
        subsong.addSpecialTrack(false, TrackTestHelper::buildTestSpecialTrack(10));

        // Links track 2 to track 0 (both in pattern 0).
        auto pattern0 = subsong.getPatternRef(0);
        pattern0.setTrackIndex(2, Pattern::TrackIndexAndLinkedTrackIndex(2, 0));
        // Links special tracks 0 of pattern 0 to the special tracks 1 of pattern 1.
        pattern0.setSpecialTrackIndex(true, 0, 1);
        pattern0.setSpecialTrackIndex(false, 0, 1);
        subsong.setPattern(0, pattern0);

        // Modifies track 0, track 2 should reflect the change.
        subsong.setCell(0, 0, 0, Cell::build(40, 1));
        // Idem for the special tracks, changing the p1 special tracks, as they are linked.
        subsong.setSpecialCell(true, 1, 0, SpecialCell::buildSpecialCell(50));
        subsong.setSpecialCell(false, 1, 0, SpecialCell::buildSpecialCell(60));
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0 };
    constexpr auto destinationPosition = 1;
    constexpr auto insertAfter = false;
    ClonePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE(actionResult);

    // Then.
    const auto song = songController.getSong();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 2));
        REQUIRE((subsong.getLength() == (originalLength + 1)));

        REQUIRE((subsong.getTrackCount() == 9));
        REQUIRE((subsong.getSpecialTrackCount(true) == 3));
        REQUIRE((subsong.getSpecialTrackCount(false) == 3));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0), 40)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1), 1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2), 40)));
        // Position 1, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0), 40)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1), 1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2), 40)));
        // The duplicated position (pattern 2) has linked tracks.
        const auto& pattern2 = subsong.getPatternFromIndex(2);
        const auto p2ChannelIndex0 = pattern2.getTrackIndexAndLinkedTrackIndex(0);
        REQUIRE((p2ChannelIndex0.isLinked()));
        REQUIRE((p2ChannelIndex0.getUsedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex0.getLinkedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex0.getUnlinkedTrackIndex() == 6));
        const auto p2ChannelIndex1 = pattern2.getTrackIndexAndLinkedTrackIndex(1);
        REQUIRE_FALSE((p2ChannelIndex1.isLinked()));
        REQUIRE((p2ChannelIndex1.getUsedTrackIndex() == 7));
        REQUIRE((p2ChannelIndex1.getLinkedTrackIndex().isAbsent()));
        REQUIRE((p2ChannelIndex1.getUnlinkedTrackIndex() == 7));
        const auto p2ChannelIndex2 = pattern2.getTrackIndexAndLinkedTrackIndex(2);
        REQUIRE((p2ChannelIndex2.isLinked()));
        REQUIRE((p2ChannelIndex2.getUsedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex2.getLinkedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex2.getUnlinkedTrackIndex() == 8));
        // Special tracks.
        const auto p2SpeedTrackIndexes = pattern2.getSpecialTrackIndexAndLinkedTrackIndex(true);
        REQUIRE((p2SpeedTrackIndexes.isLinked()));
        REQUIRE((p2SpeedTrackIndexes.getUsedTrackIndex() == 1));
        REQUIRE((p2SpeedTrackIndexes.getLinkedTrackIndex() == 1));
        REQUIRE((p2SpeedTrackIndexes.getUnlinkedTrackIndex() == 2));
        const auto p2EventTrackIndexes = pattern2.getSpecialTrackIndexAndLinkedTrackIndex(false);
        REQUIRE((p2EventTrackIndexes.isLinked()));
        REQUIRE((p2EventTrackIndexes.getUsedTrackIndex() == 1));
        REQUIRE((p2EventTrackIndexes.getLinkedTrackIndex() == 1));
        REQUIRE((p2EventTrackIndexes.getUnlinkedTrackIndex() == 2));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 0), 3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 1), 4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 2), 5)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true),  50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false),60)));
        // Position 1, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true), 50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false), 60)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, true), 50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, false), 60)));
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 1));
        REQUIRE((subsong.getLength() == originalLength));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0),   40)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2),   40)));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0),   3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1),   4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2),   5)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true), 50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false), 60)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true), 50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false), 60)));

        REQUIRE((subsong.getTrackCount() == 6));
        REQUIRE((subsong.getSpecialTrackCount(true) == 2));
        REQUIRE((subsong.getSpecialTrackCount(false) == 2));
    });
}

TEST_CASE("ClonePositions, clone position 0 just after, with linked-to special tracks", "[ClonePositions]")
{
    // Given.
    std::shared_ptr baseSong = Song::buildDefaultSong(true);
    const auto subsongId = baseSong->getFirstSubsongId();
    auto originalLength = 0;
    baseSong->performOnSubsong(subsongId, [&](Subsong& subsong) {
        // Position 0 already exists.
        subsong.addPosition(Position(1));
        subsong.setLoopAndEndStartPosition(0, 1);
        originalLength = subsong.getLength();

        subsong.addPattern(Pattern({ 3, 4, 5 }, 1, 1));

        // Fills the Track 0, 1, 2, creates Track 3, 4, 5 and Special Tracks 1.
        subsong.setCell(0, 0, 0, Cell::build(0, 1));
        subsong.setCell(0, 0, 1, Cell::build(1, 1));
        subsong.setCell(0, 0, 2, Cell::build(2, 1));
        // Specials Tracks 0 are linked to by position 1.
        subsong.setSpecialCell(true, 0, 0, SpecialCell::buildSpecialCell(1));
        subsong.setSpecialCell(false, 0, 0, SpecialCell::buildSpecialCell(2));
        subsong.addTrack(TrackTestHelper::buildTestTrack(3));
        subsong.addTrack(TrackTestHelper::buildTestTrack(4));
        subsong.addTrack(TrackTestHelper::buildTestTrack(5));
        subsong.addSpecialTrack(true, TrackTestHelper::buildTestSpecialTrack(9));
        subsong.addSpecialTrack(false, TrackTestHelper::buildTestSpecialTrack(10));

        // Links track 2 to track 0 (both in pattern 0).
        auto pattern0 = subsong.getPatternRef(0);
        pattern0.setTrackIndex(2, Pattern::TrackIndexAndLinkedTrackIndex(2, 0));
        subsong.setPattern(0, pattern0);
        // Links special tracks 1 of pattern 1 to the special tracks 0 of pattern 0. Thus the special tracks of pattern 0 becomes "linked-to".
        auto pattern1 = subsong.getPatternRef(1);
        pattern1.setSpecialTrackIndex(true, 1, 0);
        pattern1.setSpecialTrackIndex(false, 1, 0);
        subsong.setPattern(1, pattern1);

        // Modifies track 0, track 2 should reflect the change.
        subsong.setCell(0, 0, 0, Cell::build(40, 1));
        // Idem for the special tracks, changing the p0 special tracks, as they are linked.
        subsong.setSpecialCell(true, 0, 0, SpecialCell::buildSpecialCell(50));
        subsong.setSpecialCell(false, 0, 0, SpecialCell::buildSpecialCell(60));
    });

    SongControllerForTest songController(std::move(baseSong));

    const auto positions = std::set { 0 };
    constexpr auto destinationPosition = 1;
    constexpr auto insertAfter = false;
    ClonePositions action(songController, subsongId, positions, destinationPosition, insertAfter);

    // When.
    const auto actionResult = action.perform();
    REQUIRE(actionResult);

    // Then.
    const auto song = songController.getSong();
    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 2));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 2));
        REQUIRE((subsong.getLength() == (originalLength + 1)));

        REQUIRE((subsong.getTrackCount() == 9));
        REQUIRE((subsong.getSpecialTrackCount(true) == 3));
        REQUIRE((subsong.getSpecialTrackCount(false) == 3));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0), 40)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1), 1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2), 40)));
        // Position 1, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0), 40)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1), 1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2), 40)));
        // The duplicated position (pattern 2) has linked tracks.
        const auto& pattern2 = subsong.getPatternFromIndex(2);
        const auto p2ChannelIndex0 = pattern2.getTrackIndexAndLinkedTrackIndex(0);
        REQUIRE((p2ChannelIndex0.isLinked()));
        REQUIRE((p2ChannelIndex0.getUsedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex0.getLinkedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex0.getUnlinkedTrackIndex() == 6));
        const auto p2ChannelIndex1 = pattern2.getTrackIndexAndLinkedTrackIndex(1);
        REQUIRE_FALSE((p2ChannelIndex1.isLinked()));
        REQUIRE((p2ChannelIndex1.getUsedTrackIndex() == 7));
        REQUIRE((p2ChannelIndex1.getLinkedTrackIndex().isAbsent()));
        REQUIRE((p2ChannelIndex1.getUnlinkedTrackIndex() == 7));
        const auto p2ChannelIndex2 = pattern2.getTrackIndexAndLinkedTrackIndex(2);
        REQUIRE((p2ChannelIndex2.isLinked()));
        REQUIRE((p2ChannelIndex2.getUsedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex2.getLinkedTrackIndex() == 0));
        REQUIRE((p2ChannelIndex2.getUnlinkedTrackIndex() == 8));
        // Special tracks.
        const auto p2SpeedTrackIndexes = pattern2.getSpecialTrackIndexAndLinkedTrackIndex(true);
        REQUIRE((p2SpeedTrackIndexes.isLinked()));
        REQUIRE((p2SpeedTrackIndexes.getUsedTrackIndex() == 0));
        REQUIRE((p2SpeedTrackIndexes.getLinkedTrackIndex() == 0));
        REQUIRE((p2SpeedTrackIndexes.getUnlinkedTrackIndex() == 2));
        const auto p2EventTrackIndexes = pattern2.getSpecialTrackIndexAndLinkedTrackIndex(false);
        REQUIRE((p2EventTrackIndexes.isLinked()));
        REQUIRE((p2EventTrackIndexes.getUsedTrackIndex() == 0));
        REQUIRE((p2EventTrackIndexes.getLinkedTrackIndex() == 0));
        REQUIRE((p2EventTrackIndexes.getUnlinkedTrackIndex() == 2));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 0), 3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 1), 4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(2, 2), 5)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true),  50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false),60)));
        // Position 1, duplication of position 0.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true), 50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false), 60)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, true), 50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(2, false), 60)));
        // The underlying special tracks of position 2 are empty.
        REQUIRE((subsong.getSpecialTrackRefFromIndex(2, true).isEmpty()));
        REQUIRE((subsong.getSpecialTrackRefFromIndex(2, false).isEmpty()));
    });

    // Undo.
    action.undo();
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        auto positionIndex = 0;
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 0));
        REQUIRE((subsong.getPosition(positionIndex++).getPatternIndex() == 1));
        REQUIRE((subsong.getLoopStartPosition() == 0));
        REQUIRE((subsong.getEndPosition() == 1));
        REQUIRE((subsong.getLength() == originalLength));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 0),   40)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 1),   1)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(0, 2),   40)));

        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 0),   3)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 1),   4)));
        REQUIRE((TrackTestHelper::checkTestTrack(subsong.getConstTrackRefFromPosition(1, 2),   5)));

        // Special tracks.
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, true), 50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(0, false),   60)));

        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, true),   50)));
        REQUIRE((TrackTestHelper::checkTestSpecialTrack(subsong.getSpecialTrackRefFromPosition(1, false),   60)));

        REQUIRE((subsong.getTrackCount() == 6));
        REQUIRE((subsong.getSpecialTrackCount(true) == 2));
        REQUIRE((subsong.getSpecialTrackCount(false) == 2));
    });
}

}   // namespace arkostracker
