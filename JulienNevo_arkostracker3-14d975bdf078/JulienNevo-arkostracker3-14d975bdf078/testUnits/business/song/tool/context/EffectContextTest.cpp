#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/builder/SongBuilder.h"
#include "../../../../../source/import/loader/SongLoader.h"
#include "../../../../../source/song/CellLocationInPosition.h"
#include "../../../../../source/song/Song.h"
#include "../../../../controllers/SongControllerForTest.h"
#include "EffectContextHelper.h"

namespace arkostracker
{

/** Two different patterns on three positions. Even though the pos 1 and 2 have the same patterns, the context is different. */
TEST_CASE("EffectContext, several positions", "[EffectContext]")
{
    // Given.
    SongBuilder songBuilder;

    // Creates a few expressions.
    for (auto isArpeggio : { false, true }) {
        for (auto expressionIndex = 1; expressionIndex < 5; ++expressionIndex) {
            const auto baseTitle = isArpeggio ? juce::String("arp") : "pitch";
            songBuilder.startNewExpression(isArpeggio, expressionIndex, baseTitle + juce::String(expressionIndex));
            songBuilder.addCurrentExpressionValue(expressionIndex);     // As a filler...
            songBuilder.setCurrentExpressionLoop(0, 0);
            songBuilder.finishCurrentExpression();
        }
    }

    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.setMetadata("title", 6);
    subsongBuilder.addPsg(Psg());
    {
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(0);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(1);
        subsongBuilder.finishCurrentPosition();
        subsongBuilder.startNewPosition();
        subsongBuilder.setCurrentPositionPatternIndex(1);
        subsongBuilder.finishCurrentPosition();

        subsongBuilder.setLoop(0, 2);
    }

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 1);
    subsongBuilder.setCurrentPatternTrackIndex(2, 2);
    subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
    subsongBuilder.finishCurrentPattern();

    subsongBuilder.startNewPattern(1);
    subsongBuilder.setCurrentPatternTrackIndex(0, 3);
    subsongBuilder.setCurrentPatternTrackIndex(1, 4);
    subsongBuilder.setCurrentPatternTrackIndex(2, 5);
    subsongBuilder.setCurrentPatternSpeedTrackIndex(0);
    subsongBuilder.finishCurrentPattern();

    // Position 1 (tracks 0-1-2).
    // ============================
    // Track 0.
    {
        constexpr auto trackIndex = 0;
        subsongBuilder.setCellOnTrack(trackIndex, 10, Cell::build(40, 1, CellEffects({
            { Effect::volume, 14 },
            { Effect::pitchTable, 1 },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 20, Cell::build(41, 1, CellEffects({
            { Effect::pitchTable, 2 },
        })));
    }

    // Track 2.
    {
        constexpr auto trackIndex = 2;
        subsongBuilder.setCellOnTrack(trackIndex, 1, Cell::build(42, 1, CellEffects({
            { Effect::arpeggioTable, 1 },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 9, Cell::build(42, 1, CellEffects({
            { Effect::arpeggioTable, 2 },
            { Effect::volume, 12 },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 12, Cell({ }, {}, CellEffects({
            { Effect::volumeOut, 0x0080 },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 15, Cell::build(43, 1, CellEffects({
            { Effect::pitchTable, 2 },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 18, Cell({ }, {}, CellEffects({
            { Effect::pitchTable, 1 },
            { Effect::arpeggio3Notes, 0x37 },
        })));

        subsongBuilder.setCellOnTrack(trackIndex, 20, Cell({ }, {}, CellEffects({
            { Effect::reset, 8 },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 24, Cell({ }, {}, CellEffects({
            { Effect::arpeggio4Notes, 0x18f },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 28, Cell({ }, {}, CellEffects({
            { Effect::arpeggio3Notes, 0 },
            { Effect::volumeIn, 0x0100 },
        })));

        // Use of illegal pitch/arp.
        // → generates assertions. Comment to ease the testing.
        subsongBuilder.setCellOnTrack(trackIndex, 32, Cell({ }, {}, CellEffects({
            { Effect::arpeggioTable, 50 },
            { Effect::pitchTable, 51 },
        })));
    }

    // Position 1 (tracks 3-4-5).
    // ============================
    // Track 3.
    {
        constexpr auto trackIndex = 3;
        subsongBuilder.setCellOnTrack(trackIndex, 30, Cell::build(40, 1, CellEffects({
            { Effect::pitchTable, 0 },
        })));
        subsongBuilder.setCellOnTrack(trackIndex, 32, Cell({ }, { }, CellEffects({
            { Effect::volume, 10 },
        })));
    }
    // Track 4.
    {
        constexpr auto trackIndex = 4;
        subsongBuilder.setCellOnTrack(trackIndex, 20, Cell::build(40, 1, CellEffects({
            { Effect::volumeOut, 0x008 },
        })));
    }

    songBuilder.finishCurrentSubsong();

    auto [uniqueSong, report] = songBuilder.buildSong();
    REQUIRE(report->isOk());
    REQUIRE((uniqueSong != nullptr));

    // When.
    const auto subsongId = uniqueSong->getFirstSubsongId();
    std::shared_ptr song = std::move(uniqueSong);
    SongControllerForTest songController(std::move(song));

    EffectContextTest effectContextTest(songController);

    // Parses the song.
    effectContextTest.buildContext();

    const auto pitchId0 = effectContextTest.getPitchId(0);
    const auto pitchId1 = effectContextTest.getPitchId(1);
    const auto pitchId2 = effectContextTest.getPitchId(2);
    const auto arpId0 = effectContextTest.getArpeggioId(0);
    const auto arpId1 = effectContextTest.getArpeggioId(1);
    const auto arpId2 = effectContextTest.getArpeggioId(2);
    auto arpeggio037 = Expression::buildArpeggio("Inline Arpeggio", true);
    arpeggio037.addValue(3);
    arpeggio037.addValue(7);
    arpeggio037.setLoop(Loop(0, 2, true));
    auto arpeggio018f = Expression::buildArpeggio("Inline Arpeggio", true);
    arpeggio018f.addValue(1);
    arpeggio018f.addValue(8);
    arpeggio018f.addValue(0xf);
    arpeggio018f.setLoop(Loop(0, 3, true));

    const LineContext defaultLineContext(pitchId0, arpId0, 15);
    auto channel0LineContext = defaultLineContext;
    auto channel1LineContext = channel0LineContext;
    auto channel2LineContext = channel0LineContext;

    // Then.
    auto positionIndex = 0;

    // Position 0.
    // =============================
    // Channel 0.
    {
        constexpr auto channelIndex = 0;
        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == channel0LineContext));
        const auto context9 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 9, channelIndex));
        REQUIRE((context9 == channel0LineContext));

        // 10. New pitch and volume.
        const auto context10 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 10, channelIndex));
        channel0LineContext = channel0LineContext.withPitchId(pitchId1).withVolume(14);
        REQUIRE((context10 == channel0LineContext));

        const auto context11 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 11, channelIndex));
        REQUIRE((context11 == channel0LineContext));
        const auto context19 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 19, channelIndex));
        REQUIRE((context19 == channel0LineContext));

        // 20. New pitch.
        const auto context20 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 20, channelIndex));
        channel0LineContext = channel0LineContext.withPitchId(pitchId2);
        REQUIRE((context20 == channel0LineContext));

        const auto context21 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 21, channelIndex));
        REQUIRE((context21 == channel0LineContext));

        const auto context127 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 127, channelIndex));
        REQUIRE((context127 == channel0LineContext));
    }

    // Channel 1.
    {
        constexpr auto channelIndex = 1;
        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == channel1LineContext));
        const auto context127 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 127, channelIndex));
        REQUIRE((context127 == channel1LineContext));
    }

    // Channel 2.
    {
        constexpr auto channelIndex = 2;
        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == channel2LineContext));

        const auto context1 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 1, channelIndex));
        channel2LineContext = channel2LineContext.withArpeggioId(arpId1);
        REQUIRE((context1 == channel2LineContext));
        const auto context2 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 2, channelIndex));
        REQUIRE((context2 == channel2LineContext));

        const auto context9 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 9, channelIndex));
        channel2LineContext = channel2LineContext.withArpeggioId(arpId2).withVolume(12);
        REQUIRE((context9 == channel2LineContext));

        const auto context12 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 12, channelIndex));
        channel2LineContext = channel2LineContext.withVolume(12);
        REQUIRE((context12 == channel2LineContext));
        const auto context13 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 13, channelIndex));
        channel2LineContext = channel2LineContext.withVolume(9);
        REQUIRE((context13 == channel2LineContext));
        const auto context14 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 14, channelIndex));
        channel2LineContext = channel2LineContext.withVolume(6);
        REQUIRE((context14 == channel2LineContext));

        const auto context15 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 15, channelIndex));
        channel2LineContext = channel2LineContext.withPitchId(pitchId2).withVolume(3);
        REQUIRE((context15 == channel2LineContext));
        const auto context16 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 16, channelIndex));
        REQUIRE((context16 == channel2LineContext));

        const auto context18 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 18, channelIndex));
        channel2LineContext = channel2LineContext.withPitchId(pitchId1).withArpeggioId({ }).withArpeggioInline(arpeggio037);
        REQUIRE((context18 == channel2LineContext));

        const auto context20 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 20, channelIndex));
        channel2LineContext = channel2LineContext.withPitchId(pitchId0).withArpeggioId(arpId0).withArpeggioInline({ }).withVolume(7);
        REQUIRE((context20 == channel2LineContext));

        const auto context24 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 24, channelIndex));
        channel2LineContext = channel2LineContext.withArpeggioId({ }).withArpeggioInline(arpeggio018f);
        REQUIRE((context24 == channel2LineContext));

        const auto context28 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 28, channelIndex));
        channel2LineContext = channel2LineContext.withArpeggioId(arpId0).withArpeggioInline({ });
        REQUIRE((context28 == channel2LineContext));

        // Volume rising.
        const auto context29 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 29, channelIndex));
        channel2LineContext = channel2LineContext.withVolume(13);
        REQUIRE((context29 == channel2LineContext));
        const auto context30 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 30, channelIndex));
        channel2LineContext = channel2LineContext.withVolume(15);
        REQUIRE((context30 == channel2LineContext));

        const auto context127 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 127, channelIndex));
        REQUIRE((context30 == channel2LineContext));
    }

    // Position 1.
    // =============================
    positionIndex = 1;
    // Channel 0.
    {
        // No change for now, still pitch 2.
        REQUIRE((channel0LineContext.getPitchId() == pitchId2));
        REQUIRE((channel0LineContext.getArpeggioId() == arpId0));
        REQUIRE((channel0LineContext.getArpeggioInline().isAbsent()));
        REQUIRE((channel0LineContext.getVolume() == FpFloat(14)));

        constexpr auto channelIndex = 0;

        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == channel0LineContext));
        const auto context20 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 20, channelIndex));
        REQUIRE((context20 == channel0LineContext));
        const auto context29 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 29, channelIndex));
        REQUIRE((context29 == channel0LineContext));

        const auto context30 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 30, channelIndex));
        channel0LineContext = channel0LineContext.withPitchId(pitchId0);
        REQUIRE((context30 == channel0LineContext));

        const auto context32 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 32, channelIndex));
        channel0LineContext = channel0LineContext.withVolume(10);
        REQUIRE((context32 == channel0LineContext));

        const auto context127 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 127, channelIndex));
        REQUIRE((context127 == channel0LineContext));
    }
    // Channel 1.
    {
        constexpr auto channelIndex = 1;

        // No change for now, still volume 15.
        REQUIRE((channel1LineContext.getPitchId() == pitchId0));
        REQUIRE((channel1LineContext.getArpeggioId() == arpId0));
        REQUIRE((channel1LineContext.getArpeggioInline().isAbsent()));
        REQUIRE((channel1LineContext.getVolume() == FpFloat(15)));

        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == channel1LineContext));
        const auto context19 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 19, channelIndex));
        REQUIRE((context19 == channel1LineContext));

        // Volume out slowly.
        const auto context20 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 20, channelIndex));
        REQUIRE((context20 == channel1LineContext));

        const auto context21 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 21, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(14, 0xd0);
        REQUIRE((context21 == channel1LineContext));

        const auto context24 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 24, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(14, 0x40);
        REQUIRE((context24 == channel1LineContext));

        const auto context40 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 40, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(11, 0x40);
        REQUIRE((context40 == channel1LineContext));
        const auto context41 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 41, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(11, 0x10);
        REQUIRE((context41 == channel1LineContext));

        const auto context63 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 63, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(6, 0xf0);
        REQUIRE((context63 == channel1LineContext));
    }
    // Channel 2.
    {
        constexpr auto channelIndex = 2;

        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == defaultLineContext));
        const auto context63 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 63, channelIndex));
        REQUIRE((context63 == defaultLineContext));
    }

    // Position 2.
    // =============================
    positionIndex = 2;
    // Channel 0.
    {
        // No change for now, still pitch 0 and volume 10.
        REQUIRE((channel0LineContext.getPitchId() == pitchId0));
        REQUIRE((channel0LineContext.getArpeggioId() == arpId0));
        REQUIRE((channel0LineContext.getArpeggioInline().isAbsent()));
        REQUIRE((channel0LineContext.getVolume() == FpFloat(10)));

        constexpr auto channelIndex = 0;

        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == channel0LineContext));
        const auto context20 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 20, channelIndex));
        REQUIRE((context20 == channel0LineContext));
        const auto context29 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 29, channelIndex));
        REQUIRE((context29 == channel0LineContext));

        const auto context30 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 30, channelIndex));
        REQUIRE((context30 == channel0LineContext));

        const auto context32 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 32, channelIndex));
        REQUIRE((context32 == channel0LineContext));

        const auto context127 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 127, channelIndex));
        REQUIRE((context127 == channel0LineContext));
    }

    // Channel 1.
    {
        constexpr auto channelIndex = 1;
        REQUIRE((channel1LineContext.getPitchId() == pitchId0));
        REQUIRE((channel1LineContext.getArpeggioId() == arpId0));
        REQUIRE((channel1LineContext.getArpeggioInline().isAbsent()));

        // The volume continues to go down.
        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(6, 0xc0);
        REQUIRE((context0 == channel1LineContext));

        const auto context1 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 1, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(6, 0x90);
        REQUIRE((context1 == channel1LineContext));

        const auto context10 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 10, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(4, 0xe0);
        REQUIRE((context10 == channel1LineContext));

        const auto context20 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 20, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(3, 0x0);
        REQUIRE((context20 == channel1LineContext));

        const auto context30 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 30, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(1, 0x20);
        REQUIRE((context30 == channel1LineContext));

        const auto context40 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 40, channelIndex));
        channel1LineContext = channel1LineContext.withVolume(0, 0x0);
        REQUIRE((context40 == channel1LineContext));

        const auto context64 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 63, channelIndex));
        REQUIRE((context64 == channel1LineContext));
    }
    // Channel 2.
    {
        constexpr auto channelIndex = 2;

        const auto context0 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 0, channelIndex));
        REQUIRE((context0 == defaultLineContext));
        const auto context63 = effectContextTest.determineContext(CellLocationInPosition(subsongId, positionIndex, 63, channelIndex));
        REQUIRE((context63 == defaultLineContext));
    }
}

}   // namespace arkostracker
