#include "../../../catch.hpp"

#include <juce_core/juce_core.h>

#include "../../../../source/business/instrument/GenericInstrumentGenerator.h"
#include "../../../../source/business/song/tool/MergeSongProcess.h"
#include "../../../helper/SongTestHelper.h"
#include "../../../helper/TrackTestHelper.h"

namespace arkostracker
{

TEST_CASE("MergeSongProcess, simple", "[MergeSongProcess]")
{
    // Given.
    auto originalSong = Song("song", "me", "you", "comment", false);
    originalSong.addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong.addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    auto emptyArp = Expression(true, "Empty", true);
    originalSong.getExpressionHandler(true).addExpression(emptyArp);

    auto arp1 = Expression(true, "arp1", true);
    arp1.addValue(3);
    arp1.addValue(7);
    arp1.setLoopStartAndEnd(0, 2);
    originalSong.getExpressionHandler(true).addExpression(arp1);

    {
        auto arp2 = Expression(true, "arp2", true);             // Unused.
        arp2.addValue(4);
        arp2.addValue(7);
        arp2.setLoopStartAndEnd(0, 2);
        originalSong.getExpressionHandler(true).addExpression(arp2);
    }

    auto emptyPitch = Expression(false, "Empty", true);
    originalSong.getExpressionHandler(false).addExpression(emptyPitch);

    auto pitch1 = Expression(false, "pitch1", true);
    pitch1.addValue(1);
    pitch1.addValue(2);
    pitch1.addValue(3);
    pitch1.setLoopStartAndEnd(0, 3);
    originalSong.getExpressionHandler(false).addExpression(pitch1);

    {
        auto pitch2 = Expression(false, "pitch2", true);                // Unused.
        pitch2.addValue(10);
        pitch2.addValue(20);
        pitch2.addValue(30);
        pitch2.setLoopStartAndEnd(1, 3);
        originalSong.getExpressionHandler(false).addExpression(pitch2);
    }

    SongTestHelper::addSubsong(originalSong, 1, 6, 0, 1,
                               {
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                           { 12,  Cell::build(12, 1,
                                                                                   CellEffects({{ Effect::arpeggioTable, 1 }})) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                           { 13, Cell::build(12, 1,
                                                                                   CellEffects({{ Effect::pitchTable, 1 }})) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 10,   Cell::build(10, 0) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 15, SpecialCell::buildSpecialCell(3) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 5,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                               }
    );

    // ====================================================================

    auto songToMerge = Song("songToMerge", "me2", "you2", "comment2", false);
        
    songToMerge.addInstrument(Instrument::buildEmptyPsgInstrument());
    songToMerge.addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());   // 1. Unused
    songToMerge.addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume("other"));   // 2. Same as above.

    songToMerge.getExpressionHandler(true).addExpression(emptyArp);
    songToMerge.getExpressionHandler(false).addExpression(emptyPitch);

    auto arp2 = Expression(true, "arp2 doppelganger", true);
    arp2.addValue(4);
    arp2.addValue(7);
    arp2.setLoopStartAndEnd(0, 2);
    songToMerge.getExpressionHandler(true).addExpression(arp2);

    {
        auto arpUnused = Expression(true, "arp unused", true);        // 2 - Unused.
        arpUnused.addValue(40);
        arpUnused.addValue(70);
        arpUnused.setLoopStartAndEnd(0, 2);
        songToMerge.getExpressionHandler(true).addExpression(arpUnused);
    }

    {
        auto pitchUnused = Expression(false, "pitch unused", true);           // 1 - Unused.
        pitchUnused.addValue(9);
        pitchUnused.addValue(9);
        pitchUnused.addValue(9);
        pitchUnused.setLoopStartAndEnd(0, 3);
        songToMerge.getExpressionHandler(false).addExpression(pitchUnused);
    }

    auto pitch5 = Expression(false, "pitch5", true);                       // 2 - new
    pitch5.addValue(19);
    pitch5.addValue(18);
    pitch5.addValue(17);
    pitch5.setLoopStartAndEnd(0, 3);
    songToMerge.getExpressionHandler(false).addExpression(pitch5);

    {
        auto pitch1b = Expression(false, "pitch1 doppel", true);            // 3 - Same as Pitch 1 on subsong 0.
        pitch1b.addValue(1);
        pitch1b.addValue(2);
        pitch1b.addValue(3);
        pitch1b.setLoopStartAndEnd(0, 3);
        songToMerge.getExpressionHandler(false).addExpression(pitch1b);
    }

    SongTestHelper::addSubsong(songToMerge, 1, 3, 0, 1,
                               {
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 2, 1, 0 }, 0, 0),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 2) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 10, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 2 }})) },
                                                                           { 11, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 3 }})) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 8,  Cell::build(12, 2, CellEffects({
                                                                                                                         { Effect::arpeggioTable, 1 },
                                                                                                                 })) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 15, SpecialCell::buildSpecialCell(3) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 5,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                               }
    );

    // When.
    const auto mergedSong = MergeSongProcess::merge(originalSong, songToMerge);

    // Then.
    REQUIRE((mergedSong != nullptr));

    // Checks the instruments.
    REQUIRE((mergedSong->getSubsongCount() == 2));
    mergedSong->performOnConstInstruments([&] (const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE((instruments.size() == 2));
        REQUIRE((instruments.at(0)->isMusicallyEqualTo(*GenericInstrumentGenerator::generateInstrumentForEmpty())));
        REQUIRE((instruments.at(1)->isMusicallyEqualTo(*GenericInstrumentGenerator::generateInstrumentForDecreasingVolume())));
    });

    // Checks the arpeggios.
    const auto& arpeggioHandler = mergedSong->getExpressionHandler(true);
    REQUIRE((arpeggioHandler.getCount() == 3));
    REQUIRE((arpeggioHandler.getExpressionCopy(arpeggioHandler.getId(0).getValue()) == Expression(true, "Empty", true)));
    REQUIRE((arpeggioHandler.getExpressionCopy(arpeggioHandler.getId(1).getValue()) == arp1));
    REQUIRE((arpeggioHandler.getExpressionCopy(arpeggioHandler.getId(2).getValue()) == arp2));

    // Checks the pitches.
    const auto& pitchHandler = mergedSong->getExpressionHandler(false);
    REQUIRE((pitchHandler.getCount() == 3));
    REQUIRE((pitchHandler.getExpressionCopy(pitchHandler.getId(0).getValue()) == Expression(false, "Empty", true)));
    REQUIRE((pitchHandler.getExpressionCopy(pitchHandler.getId(1).getValue()) == pitch1));
    REQUIRE((pitchHandler.getExpressionCopy(pitchHandler.getId(2).getValue()) == pitch5));

    // Checks the subsong 0.
    const auto expectedSubsong0 = SongTestHelper::createSubsong(1, 6, 0, 1,
                               {
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                           { 12,  Cell::build(12, 1,
                                                                                   CellEffects({{ Effect::arpeggioTable, 1 }})) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                           { 13, Cell::build(12, 1,
                                                                                   CellEffects({{ Effect::pitchTable, 1 }})) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 10,   Cell::build(10, 0) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 15, SpecialCell::buildSpecialCell(3) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 5,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                               }
    );

    mergedSong->performOnConstSubsong(mergedSong->getSubsongIds().at(0), [&] (const Subsong& subsong) {
        REQUIRE((subsong.isMusicallyEqual(*expectedSubsong0)));
    });

    // Checks the subsong 1.
    const auto expectedSubsong1 = SongTestHelper::createSubsong(1, 3, 0, 1,
                               {
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 2, 1, 0 }, 0, 0),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 10, Cell::build(12, 1, CellEffects({{ Effect::pitchTable, 2 }})) },
                                                                           { 11, Cell::build(12, 1, CellEffects({{ Effect::pitchTable, 1 }})) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 8,  Cell::build(12, 1, CellEffects({
                                                                                                                         { Effect::arpeggioTable, 2 },
                                                                                                                 })) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 15, SpecialCell::buildSpecialCell(3) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 5,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                               }
    );

    mergedSong->performOnConstSubsong(mergedSong->getSubsongIds().at(1), [&] (const Subsong& subsong) {
        REQUIRE((subsong.isMusicallyEqual(*expectedSubsong1)));
    });
}

}   // namespace arkostracker
