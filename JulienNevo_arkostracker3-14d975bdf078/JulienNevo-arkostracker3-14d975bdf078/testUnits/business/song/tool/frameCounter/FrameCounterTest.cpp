#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/builder/SongBuilder.h"
#include "../../../../../source/business/song/tool/frameCounter/FrameCounter.h"

namespace arkostracker 
{

TEST_CASE("FrameCounter, one empty pattern", "[FrameCounter]")
{
    // Given.
    auto song = Song::buildDefaultSong();
    const auto subsongId = song->getFirstSubsongId();

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, subsongId);

    // Then.
    REQUIRE(counter == (6 * 64));
    REQUIRE(upToCounter == (6 * 64));
    REQUIRE(loopCounter == 0);
}

TEST_CASE("FrameCounter, one pattern with two speed changes", "[FrameCounter]")
{
    // Given.
    auto song = Song::buildDefaultSong();
    song->performOnSubsong(song->getFirstSubsongId(), [&](Subsong& subsong) noexcept {
        subsong.setCellFromSpecialTrackIndex(true, 0, 0, SpecialCell::buildSpecialCell(4));
        subsong.setCellFromSpecialTrackIndex(true, 0, 10, SpecialCell::buildSpecialCell(3));
        subsong.setCellFromSpecialTrackIndex(true, 0, 63, SpecialCell::buildSpecialCell(20));
    });

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, song->getFirstSubsongId());

    // Then.
    constexpr auto expected = (10 * 4 + 53 * 3 + 20);
    REQUIRE(counter == expected);
    REQUIRE(upToCounter == expected);
    REQUIRE(loopCounter == 0);
}

TEST_CASE("FrameCounter, one pattern with one unused speed change", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions. Several unused ones.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(20);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(20);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(20);
        subsongBuilder.finishCurrentPosition();
    }
    // Speed Tracks.
    {
        subsongBuilder.startNewSpeedTrack(0);
        subsongBuilder.setCurrentSpeedTrackValue(10, 2);
        subsongBuilder.setCurrentSpeedTrackValue(30, 10);
        subsongBuilder.finishCurrentSpeedTrack();
    }
    subsongBuilder.setMetadata("title", 20);
    subsongBuilder.setLoop(0, 0);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, song->getFirstSubsongId());

    // Then.
    constexpr auto expected = (10 * 20 + 10 * 2);
    REQUIRE(counter == expected);
    REQUIRE(upToCounter == expected);
    REQUIRE(loopCounter == 0);
}

TEST_CASE("FrameCounter, several empty patterns, with loop", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();

        subsongBuilder.startNewPattern(1);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(1);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(60);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(1);
        subsongBuilder.setCurrentPositionHeight(62);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(48);
        subsongBuilder.finishCurrentPosition();
    }
    subsongBuilder.setLoop(1, 2);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, song->getFirstSubsongId());

    // Then.
    constexpr auto expected = (60 * 6 + 62 * 6 + 48 * 6);
    constexpr auto expectedLoop = 60 * 6;
    REQUIRE(counter == expected);
    REQUIRE(upToCounter == expected);
    REQUIRE(loopCounter == expectedLoop);
}

TEST_CASE("FrameCounter, several patterns, with loop", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();

        subsongBuilder.startNewPattern(1);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(1);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();

        subsongBuilder.startNewPattern(2);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(2);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(1);
        subsongBuilder.setCurrentPositionHeight(30);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(20);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(2);
        subsongBuilder.setCurrentPositionHeight(128);
        subsongBuilder.finishCurrentPosition();
    }
    // Speed Tracks.
    {
        subsongBuilder.startNewSpeedTrack(0);
        subsongBuilder.setCurrentSpeedTrackValue(15, 6);
        subsongBuilder.setCurrentSpeedTrackValue(30, 10);
        subsongBuilder.finishCurrentSpeedTrack();

        subsongBuilder.startNewSpeedTrack(2);
        subsongBuilder.setCurrentSpeedTrackValue(1, 4);
        subsongBuilder.setCurrentSpeedTrackValue(2, 7);
        subsongBuilder.setCurrentSpeedTrackValue(127, 1);
        subsongBuilder.finishCurrentSpeedTrack();
    }
    subsongBuilder.setMetadata("title", 8);
    subsongBuilder.setLoop(2, 3);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, song->getFirstSubsongId());

    // Then.
    constexpr auto position0 = 15 * 8 + 15 * 6 + 34 * 10;       // Height = 64.
    constexpr auto position1 = 30 * 10;                         // Height = 30.
    constexpr auto position2 = 15 * 10 + 5 * 6;                 // Height = 20.
    constexpr auto position3 = 1 * 6 + 1 * 4 + 125 * 7 + 1 * 1; // Height = 128.
    constexpr auto expected = position0 + position1 + position2 + position3;
    constexpr auto expectedLoop = position0 + position1;
    REQUIRE(counter == expected);
    REQUIRE(upToCounter == expected);
    REQUIRE(loopCounter == expectedLoop);
}



// ===============================================================

TEST_CASE("FrameCounter, empty patterns, with upTo, at the beginning", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(30);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(48);
        subsongBuilder.finishCurrentPosition();
    }
    subsongBuilder.setLoop(0, 2);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    const OptionalValue upToLocation = Location(song->getFirstSubsongId(), 0, 0);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, song->getFirstSubsongId(), upToLocation);

    // Then.
    constexpr auto expectedAll = (64 * 6 + 30 * 6 + 48 * 6);
    constexpr auto expectedUpTo = 0;
    REQUIRE(counter == expectedAll);
    REQUIRE(upToCounter == expectedUpTo);
    REQUIRE(loopCounter == 0);
}

TEST_CASE("FrameCounter, empty patterns, with upTo middle of first position", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(30);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(48);
        subsongBuilder.finishCurrentPosition();
    }
    subsongBuilder.setLoop(0, 2);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    const OptionalValue upToLocation = Location(song->getFirstSubsongId(), 0, 32);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, song->getFirstSubsongId(), upToLocation);

    // Then.
    constexpr auto expectedAll = (64 * 6 + 30 * 6 + 48 * 6);
    constexpr auto expectedUpTo = (32 * 6);
    REQUIRE(counter == expectedAll);
    REQUIRE(upToCounter == expectedUpTo);
    REQUIRE(loopCounter == 0);
}

TEST_CASE("FrameCounter, empty patterns, with upTo start of second position", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(30);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(48);
        subsongBuilder.finishCurrentPosition();
    }
    subsongBuilder.setLoop(0, 2);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    const auto subsongId = song->getFirstSubsongId();
    const OptionalValue upToLocation = Location(subsongId, 1, 0);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, subsongId, upToLocation);

    // Then.
    constexpr auto expectedAll = (64 * 6 + 30 * 6 + 48 * 6);
    constexpr auto expectedUpTo = (64 * 6);
    REQUIRE(counter == expectedAll);
    REQUIRE(upToCounter == expectedUpTo);
    REQUIRE(loopCounter == 0);
}

TEST_CASE("FrameCounter, empty patterns, upTo can never be reached", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(30);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(48);
        subsongBuilder.finishCurrentPosition();
    }
    subsongBuilder.setLoop(0, 2);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    const auto subsongId = song->getFirstSubsongId();
    const OptionalValue upToLocation = Location(subsongId, 10, 0);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, subsongId, upToLocation);

    // Then.
    constexpr auto expectedAll = (64 * 6 + 30 * 6 + 48 * 6);
    constexpr auto expectedUpTo = expectedAll;
    REQUIRE(counter == expectedAll);
    REQUIRE(upToCounter == expectedUpTo);
    REQUIRE(loopCounter == 0);
}

TEST_CASE("FrameCounter, several empty patterns, with upTo middle of the last position", "[FrameCounter]")
{
    // Given.
    SongBuilder songBuilder;
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPattern(0);
        subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
        subsongBuilder.setCurrentPatternTrackIndex(0, 0);
        subsongBuilder.setCurrentPatternTrackIndex(1, 0);
        subsongBuilder.setCurrentPatternTrackIndex(2, 0);
        subsongBuilder.finishCurrentPattern();
    }
    // Positions.
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.setCurrentPositionHeight(64);
        subsongBuilder.finishCurrentPosition();
    }
    subsongBuilder.setLoop(0, 5);
    songBuilder.finishCurrentSubsong();

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    const auto subsongId = song->getFirstSubsongId();
    const OptionalValue upToLocation = Location(subsongId, 5, 32);

    // When.
    const auto [counter, upToCounter, loopCounter] = FrameCounter::count(*song, subsongId, upToLocation);

    // Then.
    constexpr auto expectedAll = (64 * 6 * 6);
    constexpr auto expectedUpTo = (64 * 6 * 5 + 32 * 6);
    REQUIRE(counter == expectedAll);
    REQUIRE(upToCounter == expectedUpTo);
    REQUIRE(loopCounter == 0);
}

}   // namespace arkostracker
