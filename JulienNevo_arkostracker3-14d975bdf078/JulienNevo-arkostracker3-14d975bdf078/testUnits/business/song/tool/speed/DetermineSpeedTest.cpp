#include "../../../../catch.hpp"

#include <BinaryData.h>

#include "../../../../../source/business/song/tool/builder/SongBuilder.h"
#include "../../../../../source/business/song/tool/speed/DetermineSpeed.h"
#include "../../../../../source/import/loader/SongLoader.h"
#include "../../../../../source/song/Song.h"

namespace arkostracker 
{

TEST_CASE("DetermineSpeed, unknown subsong", "[DetermineSpeed]")
{
    // Given.
    const auto song = Song::buildDefaultSong();
    const Location location(Id(), 0, 0);

    // When.
    const auto result = DetermineSpeed::determineSpeed(*song, location);

    // Then.
    REQUIRE((result == 6));
}

TEST_CASE("DetermineSpeed, one empty pattern", "[DetermineSpeed]")
{
    // Given.
    SongBuilder songBuilder;

    constexpr auto initialSpeed = 8;

    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.setMetadata("title", initialSpeed);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.finishCurrentPosition();
        subsongBuilder.setLoop(0, 0);
    }

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
    subsongBuilder.finishCurrentPattern();

    subsongBuilder.startNewSpeedTrack(0);
    subsongBuilder.finishCurrentSpeedTrack();

    songBuilder.finishCurrentSubsong();

    auto result = songBuilder.buildSong();
    auto report = std::move(result.second);
    REQUIRE(report->isOk());
    auto song = std::move(result.first);
    REQUIRE((song != nullptr));

    // When/then.
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 0)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 30)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 63)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 127)) == initialSpeed));
}

TEST_CASE("DetermineSpeed, one pattern with changing speed", "[DetermineSpeed]")
{
    // Given.
    SongBuilder songBuilder;

    constexpr auto initialSpeed = 8;

    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.setMetadata("title", initialSpeed);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.finishCurrentPosition();
        subsongBuilder.setLoop(0, 0);
    }

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
    subsongBuilder.finishCurrentPattern();

    subsongBuilder.startNewSpeedTrack(0);
    subsongBuilder.setCurrentSpeedTrackValue(5, 0xf);
    subsongBuilder.setCurrentSpeedTrackValue(12, 0x1);
    subsongBuilder.setCurrentSpeedTrackValue(18, 0xff);
    subsongBuilder.finishCurrentSpeedTrack();

    songBuilder.finishCurrentSubsong();

    auto result = songBuilder.buildSong();
    auto report = std::move(result.second);
    REQUIRE(report->isOk());
    auto song = std::move(result.first);
    REQUIRE((song != nullptr));

    // When/then.
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 0)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 1)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 4)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 5)) == 0xf));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 11)) == 0xf));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 12)) == 0x1));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 17)) == 0x1));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 18)) == 0xff));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 30)) == 0xff));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 60)) == 0xff));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 127)) == 0xff));
}

TEST_CASE("DetermineSpeed, two patterns with changing speed, one is out of the pattern", "[DetermineSpeed]")
{
    // Given.
    SongBuilder songBuilder;

    constexpr auto initialSpeed = 8;

    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.setMetadata("title", initialSpeed);
    subsongBuilder.addPsg(Psg());

    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(0);
    subsongBuilder.setCurrentPositionHeight(64);
    subsongBuilder.finishCurrentPosition();

    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(1);
    subsongBuilder.setCurrentPositionHeight(64);
    subsongBuilder.finishCurrentPosition();
    subsongBuilder.setLoop(0, 1);

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
    subsongBuilder.finishCurrentPattern();

    subsongBuilder.startNewPattern(1);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.setCurrentPatternSpeedTrackIndex(1);
    subsongBuilder.finishCurrentPattern();

    subsongBuilder.startNewSpeedTrack(0);
    subsongBuilder.setCurrentSpeedTrackValue(64, 0x18);
    subsongBuilder.finishCurrentSpeedTrack();

    subsongBuilder.startNewSpeedTrack(1);
    subsongBuilder.setCurrentSpeedTrackValue(10, 5);
    subsongBuilder.finishCurrentSpeedTrack();

    songBuilder.finishCurrentSubsong();

    auto result = songBuilder.buildSong();
    auto report = std::move(result.second);
    REQUIRE(report->isOk());
    auto song = std::move(result.first);
    REQUIRE((song != nullptr));

    // When/then.
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 0)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 1)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 30)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 63)) == initialSpeed));

    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 1, 0)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 1, 9)) == initialSpeed));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 1, 10)) == 5));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 1, 63)) == 5));
}

TEST_CASE("DetermineSpeed, dia end", "[DetermineSpeed]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__DemoIzArt__End_Part_sks, BinaryData::Targhan__DemoIzArt__End_Part_sksSize, false);

    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "aks", false, nullptr);
    jassert(result != nullptr);
    jassert(result->errorReport != nullptr);
    jassert(result->errorReport->isOk());
    const auto song = std::move(result->song);

    // When/then.
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0, 0)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 1, 0)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x14, 0)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x14, 0x3e)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x14, 0x3f)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x14, 0x40)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x15, 0)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x16, 0)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x17, 0)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x18, 0)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x19, 0)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x1a, 0)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x1a, 0x3d)) == 4));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x1a, 0x3e)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x1b, 0)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x1c, 0)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x33, 0)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x34, 0)) == 9));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x36, 0)) == 8));
    REQUIRE((DetermineSpeed::determineSpeed(*song, Location(subsongId, 0x37, 0)) == 8));
}

}   // namespace arkostracker
