#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/builder/SongBuilder.h"
#include "../../../../../source/business/song/tool/songStripper/SongStripper.h"
#include "../../../../../source/business/song/tool/songStripper/SubsongsAndPsgs.h"
#include "../../../../../source/song/Song.h"

namespace arkostracker 
{

TEST_CASE("SongStripper, two subsongs, remove first", "[SongStripper]")
{
    // Given.
    SongBuilder songBuilder;

    // Subsong 0.
    {
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
        subsongBuilder.setLoop(0, 2);
        songBuilder.finishCurrentSubsong();
    }

    // Subsong 1.
    {
        auto& subsongBuilder = songBuilder.startNewSubsong(1);
        subsongBuilder.addPsg(Psg());
        {
            subsongBuilder.startNewPattern(0);
            subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
            subsongBuilder.setCurrentPatternTrackIndex(0, 0);
            subsongBuilder.setCurrentPatternTrackIndex(1, 1);
            subsongBuilder.setCurrentPatternTrackIndex(2, 2);
            subsongBuilder.finishCurrentPattern();
        }
        // Positions.
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
        subsongBuilder.setMetadata("title2", 20);
        subsongBuilder.setLoop(0, 1);
        songBuilder.finishCurrentSubsong();
    }

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    const auto subsong0Id = song->getSubsongNamesAndIds()[0].second;
    const auto subsong1Id = song->getSubsongNamesAndIds()[1].second;

    // When.
    SubsongsAndPsgs subsongsAndPsgsToKeep(*song, { subsong1Id });
    const auto newSong = SongStripper::split(*song, subsongsAndPsgsToKeep);

    // Then.
    REQUIRE(newSong != nullptr);
    REQUIRE(newSong->getSubsongCount() == 1);
    REQUIRE(newSong->getFirstSubsongId() == subsong1Id);
    newSong->performOnConstSubsong(subsong1Id, [&](const Subsong& subsong) {
        const auto& psgs = subsong.getPsgRefs();
        REQUIRE(psgs.size() == 1);
        const auto psg0 = psgs.at(0);
        REQUIRE(psg0.getPsgFrequency() == PsgFrequency::psgFrequencyCPC);
        REQUIRE(psg0.getPsgMixingOutput() == PsgMixingOutput::ABC);
        REQUIRE(juce::exactlyEqual(psg0.getReferenceFrequency(), PsgFrequency::defaultReferenceFrequencyHz));
        REQUIRE(psg0.getSamplePlayerFrequency() == PsgFrequency::defaultSamplePlayerFrequencyHz);

        // Checks the Patterns.
        REQUIRE(subsong.getPatternCount() == 1);
        REQUIRE(subsong.getEndPosition() == 1);
        REQUIRE(subsong.getLength() == 3);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).getUsedTrackIndex() == 0);
            REQUIRE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).getUsedTrackIndex() == 0);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
        }
    });
}

TEST_CASE("SongStripper, one subsong of 4 channels, remove second and fourth PSG", "[SongStripper]")
{
    // Given.
    SongBuilder songBuilder;

    // Subsong 0.
    {
        auto& subsongBuilder = songBuilder.startNewSubsong(0);
        subsongBuilder.addPsg(Psg());
        subsongBuilder.addPsg(Psg(PsgType::ym, 2000000, 450, 1234, PsgMixingOutput::ACB));
        subsongBuilder.addPsg(Psg(PsgType::ym, 3000000, 550, 2234, PsgMixingOutput::BAC));
        subsongBuilder.addPsg(Psg(PsgType::ym, 4000000, 650, 3234, PsgMixingOutput::BCA));
        {
            subsongBuilder.startNewPattern(0);
            subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
            subsongBuilder.setCurrentPatternTrackIndex(0, 0);
            subsongBuilder.setCurrentPatternTrackIndex(0, 11);
            subsongBuilder.setCurrentPatternTrackIndex(1, 10);
            subsongBuilder.setCurrentPatternTrackIndex(2, 9);
            subsongBuilder.setCurrentPatternTrackIndex(3, 8);
            subsongBuilder.setCurrentPatternTrackIndex(4, 7);
            subsongBuilder.setCurrentPatternTrackIndex(5, 6);
            subsongBuilder.setCurrentPatternTrackIndex(6, 5);
            subsongBuilder.setCurrentPatternTrackIndex(7, 4);
            subsongBuilder.setCurrentPatternTrackIndex(8, 3);
            subsongBuilder.setCurrentPatternTrackIndex(9, 2);
            subsongBuilder.setCurrentPatternTrackIndex(10, 1);
            subsongBuilder.setCurrentPatternTrackIndex(11, 0);
            subsongBuilder.finishCurrentPattern();
        }
        // Positions.
        {
            subsongBuilder.startNewPosition();
            subsongBuilder.setCurrentPositionPatternIndex(0);
            subsongBuilder.setCurrentPositionHeight(20);
            subsongBuilder.setCurrentPositionTransposition(0, 10);
            subsongBuilder.setCurrentPositionTransposition(1, 11);
            subsongBuilder.setCurrentPositionTransposition(2, 12);
            subsongBuilder.setCurrentPositionTransposition(3, 13);
            subsongBuilder.setCurrentPositionTransposition(4, 14);
            subsongBuilder.setCurrentPositionTransposition(5, 15);
            subsongBuilder.setCurrentPositionTransposition(6, 16);
            subsongBuilder.setCurrentPositionTransposition(7, 17);
            subsongBuilder.setCurrentPositionTransposition(8, 18);
            subsongBuilder.setCurrentPositionTransposition(9, 19);
            subsongBuilder.setCurrentPositionTransposition(10, 20);
            subsongBuilder.setCurrentPositionTransposition(11, 21);
            subsongBuilder.finishCurrentPosition();

            subsongBuilder.startNewPosition();
            subsongBuilder.setCurrentPositionPatternIndex(0);
            subsongBuilder.setCurrentPositionHeight(21);
            subsongBuilder.finishCurrentPosition();

            subsongBuilder.startNewPosition();
            subsongBuilder.setCurrentPositionPatternIndex(0);
            subsongBuilder.setCurrentPositionHeight(22);
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
        subsongBuilder.setLoop(0, 2);
        songBuilder.finishCurrentSubsong();
    }

    auto builderResult = songBuilder.buildSong();
    REQUIRE(builderResult.second->isOk());
    auto song = std::move(builderResult.first);

    const auto subsong0Id = song->getSubsongNamesAndIds()[0].second;

    // When.
    SubsongsAndPsgs subsongsAndPsgsToKeep(*song, { });
    subsongsAndPsgsToKeep.addSubsongAndPsgs(subsong0Id, { 0, 2 });
    const auto newSong = SongStripper::split(*song, subsongsAndPsgsToKeep);

    // Then.
    REQUIRE(newSong != nullptr);
    REQUIRE(newSong->getSubsongCount() == 1);
    REQUIRE(newSong->getFirstSubsongId() == subsong0Id);
    newSong->performOnConstSubsong(subsong0Id, [&](const Subsong& subsong) {
        const auto& psgs = subsong.getPsgRefs();
        REQUIRE(psgs.size() == 2);
        {
            const auto psg = psgs.at(0);
            REQUIRE(psg.getPsgFrequency() == PsgFrequency::psgFrequencyCPC);
            REQUIRE(psg.getPsgMixingOutput() == PsgMixingOutput::ABC);
            REQUIRE(juce::exactlyEqual(psg.getReferenceFrequency(), PsgFrequency::defaultReferenceFrequencyHz));
            REQUIRE(psg.getSamplePlayerFrequency() == PsgFrequency::defaultSamplePlayerFrequencyHz);
        }
        {
            const auto psg = psgs.at(1);
            REQUIRE(psg.getPsgFrequency() == 3000000);
            REQUIRE(psg.getPsgMixingOutput() == PsgMixingOutput::BAC);
            REQUIRE(juce::exactlyEqual(psg.getReferenceFrequency(), 550.0F));
            REQUIRE(psg.getSamplePlayerFrequency() == 2234);
        }

        // Checks the Positions.
        REQUIRE(subsong.getLoopStartPosition() == 0);
        REQUIRE(subsong.getEndPosition() == 2);
        REQUIRE(subsong.getLength() == 3);
        {
            const auto& position = subsong.getPositionRef(0);
            REQUIRE(position.getHeight() == 20);
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getTransposition(0) == 10);
            REQUIRE(position.getTransposition(1) == 11);
            REQUIRE(position.getTransposition(2) == 12);
            REQUIRE(position.getTransposition(3) == 16);
            REQUIRE(position.getTransposition(4) == 17);
            REQUIRE(position.getTransposition(5) == 18);
        }

        // Checks the Patterns.
        REQUIRE(subsong.getPatternCount() == 1);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 6);
            REQUIRE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).getUsedTrackIndex() == 0);
            REQUIRE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).getUsedTrackIndex() == 0);
            REQUIRE(pattern.getTrackIndexAndLinkedTrackIndex(0).getUsedTrackIndex() == 11);
            REQUIRE(pattern.getTrackIndexAndLinkedTrackIndex(1).getUsedTrackIndex() == 10);
            REQUIRE(pattern.getTrackIndexAndLinkedTrackIndex(2).getUsedTrackIndex() == 9);
            REQUIRE(pattern.getTrackIndexAndLinkedTrackIndex(3).getUsedTrackIndex() == 5);
            REQUIRE(pattern.getTrackIndexAndLinkedTrackIndex(4).getUsedTrackIndex() == 4);
            REQUIRE(pattern.getTrackIndexAndLinkedTrackIndex(5).getUsedTrackIndex() == 3);
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(3).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(4).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(5).isLinked());
        }

    });
}


}   // namespace arkostracker

