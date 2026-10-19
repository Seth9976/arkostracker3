#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/builder/PatternUnoptimizer.h"
#include "../../../../../source/song/subsong/Pattern.h"
#include "../../../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("unoptimize, nothing to do", "[PatternUnoptimizer]")
{
    // Given.
    std::map<int, Pattern> indexToPattern = {
            { 0, Pattern({ 0, 1, 2 }, 0, 0) },
    };

    // Fills as many Tracks as necessary.
    std::map<int, Track> indexToTrack;
    for (auto trackIndex = 0; trackIndex <= 2; ++trackIndex) {
        indexToTrack.insert(std::make_pair(trackIndex, TrackTestHelper::buildTestTrack(trackIndex)));        // The note is the track index, handy for debugging.
    }

    // The same for Special Tracks.
    std::map<int, SpecialTrack> indexToSpeedTrack;
    indexToSpeedTrack.insert(std::make_pair(0, TrackTestHelper::buildTestSpecialTrack(1)));         // Because 0 means "no value".

    std::map<int, SpecialTrack> indexToEventTrack;
    indexToEventTrack.insert(std::make_pair(0, TrackTestHelper::buildTestSpecialTrack(1)));

    // When.
    PatternUnoptimizer::unoptimize(indexToPattern, indexToTrack, indexToSpeedTrack, indexToEventTrack);

    // Then.
    // Checks the Patterns.
    const std::map<int, Pattern> expectedIndexToPattern = {
            { 0, Pattern({ 0, 1, 2 }, 0, 0) },
    };
    REQUIRE(indexToPattern == expectedIndexToPattern);

    // Checks the Tracks.
    {
        REQUIRE(indexToTrack.size() == 3);
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(0), 0));
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(1), 1));
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(2), 2));
    }

    // Checks the Speed Tracks.
    {
        REQUIRE(indexToSpeedTrack.size() == 1);
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToSpeedTrack.at(0), 0 + 1));
    }

    // Checks the Event Tracks.
    {
        REQUIRE(indexToEventTrack.size() == 1);
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToEventTrack.at(0), 0 + 1));
    }
}

TEST_CASE("unoptimize, nominal", "[PatternUnoptimizer]")
{
    // Given.
    std::map<int, Pattern> indexToPattern = {
            { 0, Pattern({ 0, 1, 2 }, 0, 0) },
            { 1, Pattern({ 2, 2, 2 }, 0, 0) },
            { 2, Pattern({ 0, 1, 2 }, 1, 0) },
    };

    // Fills as many Tracks as necessary.
    std::map<int, Track> indexToTrack;
    for (auto trackIndex = 0; trackIndex <= 2; ++trackIndex) {
        indexToTrack.insert(std::make_pair(trackIndex, TrackTestHelper::buildTestTrack(trackIndex)));        // The note is the track index, handy for debugging.
    }

    // The same for Special Tracks.
    std::map<int, SpecialTrack> indexToSpeedTrack;
    indexToSpeedTrack.insert(std::make_pair(0, TrackTestHelper::buildTestSpecialTrack(1)));         // Because 0 means "no value".
    indexToSpeedTrack.insert(std::make_pair(1, TrackTestHelper::buildTestSpecialTrack(2)));

    std::map<int, SpecialTrack> indexToEventTrack;
    indexToEventTrack.insert(std::make_pair(0, TrackTestHelper::buildTestSpecialTrack(1)));

    // When.
    PatternUnoptimizer::unoptimize(indexToPattern, indexToTrack, indexToSpeedTrack, indexToEventTrack);

    // Then.
    // Checks the Patterns.
    const std::map<int, Pattern> expectedIndexToPattern = {
            { 0, Pattern({ 0, 1, 2 }, 0, 0) },
            { 1, Pattern({ 3, 4, 5 }, 2, 1) },
            { 2, Pattern({ 6, 7, 8 }, 1, 2) },
    };
    REQUIRE(indexToPattern == expectedIndexToPattern);

    // Checks the Tracks.
    {
        REQUIRE(indexToTrack.size() == 9);
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(0), 0));
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(1), 1));
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(2), 2));
        // These others are duplications.
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(3), 2));        // Copies of Track 2.
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(4), 2));
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(5), 2));

        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(6), 0));
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(7), 1));
        REQUIRE(TrackTestHelper::checkTestTrack(indexToTrack.at(8), 2));
    }

    // Checks the Speed Tracks.
    {
        REQUIRE(indexToSpeedTrack.size() == 3);
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToSpeedTrack.at(0), 0 + 1));
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToSpeedTrack.at(1), 1 + 1));
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToSpeedTrack.at(2), 0 + 1));
    }

    // Checks the Event Tracks.
    {
        REQUIRE(indexToEventTrack.size() == 3);
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToEventTrack.at(0), 0 + 1));
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToEventTrack.at(1), 0 + 1));
        REQUIRE(TrackTestHelper::checkTestSpecialTrack(indexToEventTrack.at(2), 0 + 1));
    }
}

}   // namespace arkostracker

