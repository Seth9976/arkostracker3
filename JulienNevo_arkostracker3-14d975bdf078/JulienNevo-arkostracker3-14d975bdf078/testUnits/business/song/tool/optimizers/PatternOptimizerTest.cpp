#include <BinaryData.h>

#include "../../../../catch.hpp"

#include "../../../../../source/business/instrument/GenericInstrumentGenerator.h"
#include "../../../../../source/business/song/tool/optimizers/PatternOptimizer.h"
#include "../../../../../source/import/loader/SongLoader.h"
#include "../../../../helper/SongTestHelper.h"
#include "../../../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("PatternOptimizer, all the same tracks content if height cut, plus some unused, tracks are equals after normalization", "[PatternOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());           // 2.
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());              // 3.

    SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 1,
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                                       Pattern({ 7, 8, 9 }, 1, 1),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                           { 12,  Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 127, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                           { 12,  Cell::build(12, 2, CellEffects({
                                                                                                                         { Effect::arpeggioTable, 2 },
                                                                                                                         { Effect::arpeggioTable, 2 }
                                                                                                                 })) },
                                                                           { 120, Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 5 }})) },
                                                                   }),
                                       // Track 3. Unused.
                                       TrackTestHelper::buildTrack({
                                                                           { 0,  Cell::build(12, 2, CellEffects({{ Effect::pitchTable, 3 }})) },
                                                                           { 5,  Cell::build(10, 2) },
                                                                           { 28, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 1 }})) },
                                                                           { 30, Cell::build(20, 2, CellEffects({{ Effect::pitchTable, 2 }})) },
                                                                   }),
                                       // Track 4. Unused.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 5. Unused.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 6. Unused
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 7
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 64, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 8.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 65, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                                       // Track 9.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                           { 66, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 15, SpecialCell::buildSpecialCell(2) }, // Will be optimized away.
                                                                          }),
                                       // Speed Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 5,  SpecialCell::buildSpecialCell(1) }, // Idem.
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
                                                                                  { 17, SpecialCell::buildSpecialCell(2) }, // Idem.
                                                                                  { 20, SpecialCell::buildSpecialCell(2) }, // Idem.
                                                                                  { 64, SpecialCell::buildSpecialCell(10) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 5,  SpecialCell::buildSpecialCell(6) }, // NOT optimized away.
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                          }),
                                       // Event Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 5,  SpecialCell::buildSpecialCell(6) }, // NOT optimized away.
                                                                                  { 11, SpecialCell::buildSpecialCell(9) },
                                                                                  { 64, SpecialCell::buildSpecialCell(1) },
                                                                          }),
                               }
    );


    // When.
    PatternOptimizer patternOptimizer(*originalSong, { originalSong->getFirstSubsongId() });
    const auto newSong = patternOptimizer.optimize(true, true);

    const auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());           // 2.
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());              // 3.

    SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 1,
                               {
                                       Position(0, 64),
                                       Position(0, 64),
                               },
                               {
                                       Pattern({ 0, 0, 0 }, 0, 0),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                           { 12, Cell::build(12, 2, CellEffects({{ Effect::arpeggioTable, 2 }})) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(1) },
                                                                                  { 10, SpecialCell::buildSpecialCell(2) },
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

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("PatternOptimizer, all subsongs, instruments are not duplicated", "[PatternOptimizer]")
{
        // Given.
        juce::MemoryInputStream inputStream(BinaryData::At3_6subsongs_xml, static_cast<size_t>(BinaryData::At3_6subsongs_xmlSize), false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE((loadResult != nullptr));
        REQUIRE((loadResult->errorReport != nullptr));
        REQUIRE(loadResult->errorReport->isOk());
        auto originalSong = std::move(loadResult->song);

        const auto subsongIds = originalSong->getSubsongIds();

        // When.
        PatternOptimizer patternOptimizer(*originalSong, subsongIds);
        const auto song = patternOptimizer.optimize(false, true);
        REQUIRE((song != nullptr));

        // Then.
        REQUIRE((song->getInstrumentCount() == 2));
        REQUIRE((song->getConstExpressionHandler(true).getCount() == 1));
        REQUIRE((song->getConstExpressionHandler(false).getCount() == 1));
}

TEST_CASE("PatternOptimizer, initial speed is the same as speed events", "[PatternOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                                       Position(2, 32),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                                       Pattern({ 3, 4, 5 }, 1, 1),
                                       Pattern({ 6, 7, 8 }, 2, 2),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 3.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 4.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 5.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 6.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 7
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 8.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 9.
                                       TrackTestHelper::buildTrack({
                                                                           { 1,  Cell::build(10, 1) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 2,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 10, SpecialCell::buildSpecialCell(6) },
                                                                                  { 100, SpecialCell::buildSpecialCell(2) }, // Will be optimized away.
                                                                          }),
                                       // Speed Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 4,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 64,  SpecialCell::buildSpecialCell(1) }, // Will be optimized away.
                                                                          }),
                                       // Speed Track 2.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 6,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 16,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 32,  SpecialCell::buildSpecialCell(2) }, // Will be optimized away.
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       // Event Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );

    // When.
    PatternOptimizer patternOptimizer(*originalSong, { originalSong->getFirstSubsongId() });
    const auto newSong = patternOptimizer.optimize(true, true);

    const auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                                       Position(2, 32),
                               },
                               {
                                       Pattern({ 0, 0, 0 }, 0, 0),
                                       Pattern({ 0, 1, 1 }, 0, 0),
                                       Pattern({ 2, 0, 0 }, 0, 1),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildEmptySpecialTrack(),

                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("PatternOptimizer, initial speed is the not same as speed events, so overridden", "[PatternOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    SongTestHelper::addSubsong(*originalSong, 1, 2, 0, 2,       // Not the right initial speed.
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                                       Position(2, 32),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                                       Pattern({ 3, 4, 5 }, 1, 1),
                                       Pattern({ 6, 7, 8 }, 2, 2),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 3.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 4.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 5.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 6.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 7
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 8.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 9.
                                       TrackTestHelper::buildTrack({
                                                                           { 1,  Cell::build(10, 1) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 0,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 10, SpecialCell::buildSpecialCell(6) },
                                                                                  { 100, SpecialCell::buildSpecialCell(2) }, // Will be optimized away.
                                                                          }),
                                       // Speed Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 4,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 64,  SpecialCell::buildSpecialCell(1) }, // Will be optimized away.
                                                                          }),
                                       // Speed Track 2.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 6,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 16,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 32,  SpecialCell::buildSpecialCell(2) }, // Will be optimized away.
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       // Event Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );

    // When.
    PatternOptimizer patternOptimizer(*originalSong, { originalSong->getFirstSubsongId() });
    const auto newSong = patternOptimizer.optimize(true, true);

    const auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                                       Position(2, 32),
                               },
                               {
                                       Pattern({ 0, 0, 0 }, 0, 0),
                                       Pattern({ 0, 1, 1 }, 0, 0),
                                       Pattern({ 2, 0, 0 }, 0, 1),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildEmptySpecialTrack(),

                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("PatternOptimizer, initial speed is the not same as speed events, but not overridden because only set on second row", "[PatternOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    SongTestHelper::addSubsong(*originalSong, 1, 2, 0, 2,       // Not the right initial speed.
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                                       Position(2, 32),
                               },
                               {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                                       Pattern({ 3, 4, 5 }, 1, 1),
                                       Pattern({ 6, 7, 8 }, 2, 2),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 3.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,   Cell::build(10, 1) },
                                                                   }),
                                       // Track 4.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 5.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 6.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 7
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 8.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 9.
                                       TrackTestHelper::buildTrack({
                                                                           { 1,  Cell::build(10, 1) },
                                                                   }),
                               },
                               {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 1,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 10, SpecialCell::buildSpecialCell(6) },
                                                                                  { 100, SpecialCell::buildSpecialCell(2) }, // Will be optimized away.
                                                                          }),
                                       // Speed Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 4,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 64,  SpecialCell::buildSpecialCell(1) }, // Will be optimized away.
                                                                          }),
                                       // Speed Track 2.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 6,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 16,  SpecialCell::buildSpecialCell(6) },
                                                                                  { 32,  SpecialCell::buildSpecialCell(2) }, // Will be optimized away.
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       // Event Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );

    // When.
    PatternOptimizer patternOptimizer(*originalSong, { originalSong->getFirstSubsongId() });
    const auto newSong = patternOptimizer.optimize(true, true);

    const auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());   // 1.

    SongTestHelper::addSubsong(*expectedSong, 1, 2, 0, 2,
                               {
                                       Position(0, 64),
                                       Position(1, 64),
                                       Position(2, 32),
                               },
                               {
                                       Pattern({ 0, 0, 0 }, 0, 0),
                                       Pattern({ 0, 1, 1 }, 1, 0),
                                       Pattern({ 2, 0, 0 }, 2, 1),
                               },
                               {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({
                                                                           { 5,  Cell::build(10, 1) },
                                                                   }),
                                       // Track 1.
                                       TrackTestHelper::buildEmptyTrack(),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({
                                                                           { 6,  Cell::build(10, 1) },
                                                                   }),
                               },
                               {
                                       // No change!
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 1,  SpecialCell::buildSpecialCell(6) },
                                                                          }),
                                       // Speed Track 1.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 4,  SpecialCell::buildSpecialCell(6) },
                                                                          }),
                                       // Speed Track 2.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 6,  SpecialCell::buildSpecialCell(6) },
                                                                          }),
                               },
                               {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({
                                                                                  { 3,  SpecialCell::buildSpecialCell(2) },
                                                                          }),
                                       TrackTestHelper::buildEmptySpecialTrack(),
                               }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

}   // namespace arkostracker
