#include "../../../../catch.hpp"

#include "../../../../../source/business/instrument/GenericInstrumentGenerator.h"
#include "../../../../../source/business/song/tool/optimizers/ExpressionsOptimizer.h"
#include "../../../../helper/SongTestHelper.h"
#include "../../../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("ExpressionsOptimizer, simple, nothing optimized", "[ExpressionsOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    auto& arpeggioHandler = originalSong->getExpressionHandler(true);
    arpeggioHandler.addExpression(Expression(true));
    arpeggioHandler.addExpression(Expression::build("a1", true, { 0, 3, 7 }));
    arpeggioHandler.addExpression(Expression::build("a2", true, { 0, 4, 7, 12 }));

    auto& pitchHandler = originalSong->getExpressionHandler(false);
    pitchHandler.addExpression(Expression(false));
    pitchHandler.addExpression(Expression::build("p1", false, { 12, 5, -5 }));
    pitchHandler.addExpression(Expression::build("p2", false, { -10, 0, 10, 40, 0 }));
    pitchHandler.addExpression(Expression::build("p3", false, { -10, 1, 10, 40, 0 }));

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 3, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 } }))},
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 1 } }))},
                                                                                                 }),
                                                                     // Track 3.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 0, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 3 } }))},
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 28, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 } }))},
                                                                                                         { 30, Cell::build(20, 2, CellEffects({{ Effect::pitchTable, 2 } }))},
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             }
    );

    // When.
    ExpressionsOptimizer expressionsOptimizer(*originalSong, true);
    const auto newSong = expressionsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));
    REQUIRE(SongTestHelper::areSongMusicallyEqual(*originalSong, *newSong));
}

TEST_CASE("ExpressionsOptimizer, same expression, optimized", "[ExpressionsOptimizer]")
{
    // Given.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    {
        auto& arpeggioHandler = originalSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));
        arpeggioHandler.addExpression(Expression::build("a1", true, { 0, 0, 3, 3, 7, 7 }));
        auto arp2 = Expression::build("a2", true, { 0, 4, 7, 12, 15, 16, 17 });
        arp2.setLoopStartAndEnd(0, 3);
        arpeggioHandler.addExpression(arp2);

        auto& pitchHandler = originalSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
        auto pitch1 = Expression::build("p1", false, { 12, 5, -5, 9, 9, 9 });
        pitch1.setLoopStartAndEnd(0, 2);
        pitchHandler.addExpression(pitch1);
        auto pitch2 = Expression::build("p2", false, { -10, 0, 10, 40, 0 });
        pitch2.setLoopStartAndEnd(1, 1);
        pitchHandler.addExpression(pitch2);
        auto pitch3 = Expression::build("p3", false, { -10, 1, 10, 40, 0 });
        pitch3.setLoopStartAndEnd(2, 3);
        pitchHandler.addExpression(pitch3);
    }

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 3, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 } }))},
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 1 } }))},
                                                                                                 }),
                                                                     // Track 3.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 0, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 3 } }))},
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 28, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 } }))},
                                                                                                         { 30, Cell::build(20, 2, CellEffects({{ Effect::pitchTable, 2 } }))},
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             }
    );

    // When.
    ExpressionsOptimizer expressionsOptimizer(*originalSong, true);
    const auto newSong = expressionsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    {
        auto& arpeggioHandler = expectedSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));
        auto arp1 = Expression::build("a1", true, { 0, 3, 7, });
        arp1.setSpeed(1);
        arpeggioHandler.addExpression(arp1);
        auto arp2 = Expression::build("a2", true, { 0, 4, 7, 12 });
        arp2.setLoopStartAndEnd(0, 3);
        arpeggioHandler.addExpression(arp2);

        auto& pitchHandler = expectedSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
        auto pitch1 = Expression::build("p1", false, { 12, 5, -5 });
        pitch1.setLoopStartAndEnd(0, 2);
        pitchHandler.addExpression(pitch1);
        auto pitch2 = Expression::build("p2", false, { -10, 0 });
        pitch2.setLoopStartAndEnd(1, 1);
        pitchHandler.addExpression(pitch2);
        auto pitch3 = Expression::build("p3", false, { -10, 1, 10, 40 });
        pitch3.setLoopStartAndEnd(2, 3);
        pitchHandler.addExpression(pitch3);
    }

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 3, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 } }))},
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 1 } }))},
                                                                                                 }),
                                                                     // Track 3.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 0, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 3 } }))},
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 28, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 } }))},
                                                                                                         { 30, Cell::build(20, 2, CellEffects({{ Effect::pitchTable, 2 } }))},
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             }
    );
    
    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("ExpressionsOptimizer, after optimization, doubles are optimized, also unused ones.", "[ExpressionsOptimizer]")
{
    // Given.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    {
        auto& arpeggioHandler = originalSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));
        arpeggioHandler.addExpression(Expression::build("a1", true, { 0, 0, 3, 3, 7, 7 }));
        auto arp2 = Expression::build("a2", true, { 0, 3, 7 }, 1);
        arpeggioHandler.addExpression(arp2);
        auto arp3 = Expression::build("a3", true, { 0, 8, 7 });     // A3 not used.
        arpeggioHandler.addExpression(arp3);

        auto& pitchHandler = originalSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
        auto pitch1 = Expression::build("p1", false, { 12, 5, -5 });
        pitch1.setLoopStartAndEnd(0, 2);
        pitchHandler.addExpression(pitch1);
        auto pitch2 = Expression::build("p2", false, { 12, 5, -5, 9, 9, 9 });
        pitch2.setLoopStartAndEnd(0, 2);
        pitchHandler.addExpression(pitch2);
        auto pitch3 = Expression::build("p3", false, { 12, 5, -5 });        // P3 not optimized.
        pitch3.setLoopStartAndEnd(0, 2);
        pitch3.setSpeed(4);
        pitchHandler.addExpression(pitch3);
        auto pitch4 = Expression::build("p4", false, { 0, 5 });        // P4 not used.
        pitchHandler.addExpression(pitch4);
    }

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 3, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 } }))},
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 3 } }))},
                                                                                                 }),
                                                                     // Track 3.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 0, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 2 } }))},
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 28, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 } }))},
                                                                                                         { 30, Cell(CellEffects({{ Effect::pitchTable, 1 } }))},
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             }
    );

    // When.
    ExpressionsOptimizer expressionsOptimizer(*originalSong, true);
    const auto newSong = expressionsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    {
        auto& arpeggioHandler = expectedSong->getExpressionHandler(true);
        arpeggioHandler.addExpression(Expression(true));
        auto arp1 = Expression::build("a1", true, { 0, 3, 7 }, 1);          // 2 -> 1.
        arpeggioHandler.addExpression(arp1);

        auto& pitchHandler = expectedSong->getExpressionHandler(false);
        pitchHandler.addExpression(Expression(false));
        auto pitch1 = Expression::build("p1", false, { 12, 5, -5 });        // 2 -> 1.
        pitch1.setLoopStartAndEnd(0, 2);
        pitchHandler.addExpression(pitch1);
        auto pitch3 = Expression::build("p3", false, { 12, 5, -5 });        // P3 not optimized. 3 -> 2.
        pitch3.setLoopStartAndEnd(0, 2);
        pitch3.setSpeed(4);
        pitchHandler.addExpression(pitch3);
    }

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 3, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 } }))},
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 12, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 2 } }))},
                                                                                                 }),
                                                                     // Track 3.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 0, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 1 } }))},
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 28, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 } }))},
                                                                                                         { 30, Cell(CellEffects({{ Effect::pitchTable, 1 } }))},
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             },
                                                             {
                                                                     TrackTestHelper::buildEmptySpecialTrack()
                                                             }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

}   // namespace arkostracker
