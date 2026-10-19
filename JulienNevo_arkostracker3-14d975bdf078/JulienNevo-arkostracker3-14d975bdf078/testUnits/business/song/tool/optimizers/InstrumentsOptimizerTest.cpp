#include "../../../../catch.hpp"

#include "../../../../../source/business/instrument/GenericInstrumentGenerator.h"
#include "../../../../../source/business/song/tool/optimizers/InstrumentsOptimizer.h"
#include "../../../../helper/SongTestHelper.h"
#include "../../../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("InstrumentsOptimizer, no optimization", "[InstrumentsOptimizer]")
{
    // Given.
    const auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForBassDrum());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                       {
                                                               Position(0),
                                                               Position(1),
                                                       },
                                                       {
                                                               Pattern({ 1, 0, 0 }, 0, 0),
                                                               Pattern({ 2, 0, 0 }, 0, 0),
                                                       },
                                                       {
                                                               // Track 0.
                                                               TrackTestHelper::buildEmptyTrack(),
                                                               // Track 1.
                                                               TrackTestHelper::buildTrack({
                                                                                                   { 5,  Cell::build(10, 1) },
                                                                                                   { 10, Cell::build(12, 2) },
                                                                                           }),
                                                               // Track 2.
                                                               TrackTestHelper::buildTrack({
                                                                                                   { 5,  Cell::build(10, 2) },
                                                                                                   { 10, Cell::build(12, 3) },
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
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, false, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));
    REQUIRE(SongTestHelper::areSongMusicallyEqual(*originalSong, *newSong));
}

TEST_CASE("InstrumentsOptimizer, same instruments, optimized", "[InstrumentsOptimizer]")
{
    // Given.
    // Instrument 1, 2, 3 are the same, they are optimized.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                       {
                                                               Position(0),
                                                               Position(1),
                                                       },
                                                       {
                                                               Pattern({ 1, 0, 0 }, 0, 0),
                                                               Pattern({ 2, 0, 0 }, 0, 0),
                                                       },
                                                       {
                                                               // Track 0.
                                                               TrackTestHelper::buildEmptyTrack(),
                                                               // Track 1.
                                                               TrackTestHelper::buildTrack({
                                                                                                   { 5,  Cell::build(10, 1) },
                                                                                                   { 10, Cell::build(12, 2) },
                                                                                           }),
                                                               // Track 2.
                                                               TrackTestHelper::buildTrack({
                                                                                                   { 5,  Cell::build(10, 2) },
                                                                                                   { 10, Cell::build(12, 3) },
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
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, false, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 0, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
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

TEST_CASE("InstrumentsOptimizer, different instruments but the same only optimized", "[InstrumentsOptimizer]")
{
    // Given.
    // Instrument 1, 2, 3 are the same, they are optimized.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    auto instr2 = GenericInstrumentGenerator::generateInstrumentForDecreasingVolume();
    // Adds some junk at the end. It will be optimized.
    instr2->getPsgPart().addCell(PsgInstrumentCell::buildSoftwareCell(10));
    instr2->getPsgPart().addCell(PsgInstrumentCell::buildSoftwareCell(10));
    instr2->getPsgPart().addCell(PsgInstrumentCell::buildSoftwareCell(10));
    originalSong->addInstrument(std::move(instr2));
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 0, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 2) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 2) },
                                                                                                         { 10, Cell::build(12, 3) },
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
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, false, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 0 }, 0, 0),
                                                                     Pattern({ 2, 0, 0 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 5,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
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

TEST_CASE("InstrumentsOptimizer, more instruments optimized", "[InstrumentsOptimizer]")
{
    // Given.
    // Instrument 1, 3, 5 are the same, idem for 2 and 4 but they are unused.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 1
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());                            // 2
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 3
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());                            // 4
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 5

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 3) },
                                                                                                         { 12,  Cell::build(19, 3) },
                                                                                                         { 15, Cell::build(5, 2) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 5) },
                                                                                                         { 10, Cell::build(12, 5) },
                                                                                                         { 12,  Cell::build(19, 5) },
                                                                                                         { 15, Cell::build(5, 4) },
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
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, false, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 2) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 2) },
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

TEST_CASE("InstrumentsOptimizer, don't keep samples, sample instruments in notes and event tracks. The event tracks must not be modified", "[InstrumentsOptimizer]")
{
    // Given.
    const juce::MemoryBlock memoryBlock1(60, true);
    auto sample1 = std::make_shared<Sample>(memoryBlock1);
    auto sampleInstrument1 = std::make_unique<Instrument>("s1", InstrumentType::sampleInstrument, PsgPart(),
                                        SamplePart(sample1, Loop(0, 10, true)));
    const juce::MemoryBlock memoryBlock2(80, true);
    auto sample2 = std::make_shared<Sample>(memoryBlock2);
    auto sampleInstrument2 = std::make_unique<Instrument>("s2", InstrumentType::sampleInstrument, PsgPart(),
                                        SamplePart(sample2, Loop(10, 20)));

    // Instrument 3 and 5 are the samples.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 1
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());                            // 2
    originalSong->addInstrument(std::move(sampleInstrument1));                                                      // 3
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForSingleBeep());                       // 4
    originalSong->addInstrument(std::move(sampleInstrument2));                                                      // 5

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 2) },
                                                                                                         { 12,  Cell::build(19, 3) },
                                                                                                         { 15, Cell::build(5, 4) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 4) },
                                                                                                         { 10, Cell::build(12, 5) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 2) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 1, SpecialCell::buildSpecialCell(2) },
                                                                                                                { 2, SpecialCell::buildSpecialCell(3) },
                                                                                                                { 3, SpecialCell::buildSpecialCell(4) },
                                                                                                                { 4, SpecialCell::buildSpecialCell(5) },
                                                                                                        }),
                                                             }
    );

    // When.
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, false, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForSingleBeep());                       // 4

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 2) },
                                                                                                         //{ 12,  Cell::build(19, 3) },
                                                                                                         { 15, Cell::build(5, 3) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 3) },
                                                                                                         //{ 10, Cell::build(12, 5) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 2) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 1, SpecialCell::buildSpecialCell(2) },
                                                                                                                { 2, SpecialCell::buildSpecialCell(3) },
                                                                                                                { 3, SpecialCell::buildSpecialCell(4) },
                                                                                                                { 4, SpecialCell::buildSpecialCell(5) },
                                                                                                        }),
                                                             }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("InstrumentsOptimizer, keep samples, sample instruments in notes and event tracks are modified (no clash in event original tracks).", "[InstrumentsOptimizer]")
{
    // Given.
    const juce::MemoryBlock memoryBlock1(60, true);
    auto sample1 = std::make_shared<Sample>(memoryBlock1);
    auto originalSampleInstrument1 = std::make_unique<Instrument>("s1", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample1, Loop(0, 10, true)));
    const juce::MemoryBlock memoryBlock2(80, true);
    auto sample2 = std::make_shared<Sample>(memoryBlock2);
    auto originalSampleInstrument2 = std::make_unique<Instrument>("s2", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample2, Loop(10, 20)));
    const juce::MemoryBlock memoryBlock3(100, true);
    auto sample3 = std::make_shared<Sample>(memoryBlock3);
    auto originalSampleInstrument3 = std::make_unique<Instrument>("s3", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample3, Loop(20, 30)));

    // Instrument 3, 5, 6 are the samples.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 1
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());                            // 2, unused.
    originalSong->addInstrument(std::move(originalSampleInstrument1));                                                      // 3
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForSingleBeep());                       // 4
    originalSong->addInstrument(std::move(originalSampleInstrument2));                                                      // 5, unused.
    originalSong->addInstrument(std::move(originalSampleInstrument3));                                                      // 6

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 3) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 4) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 6) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 4) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(10) },
                                                                                                                { 1, SpecialCell::buildSpecialCell(3) },  // Spl
                                                                                                                { 2, SpecialCell::buildSpecialCell(6) },  // Spl
                                                                                                                { 3, SpecialCell::buildSpecialCell(7) },
                                                                                                                { 4, SpecialCell::buildSpecialCell(10) },
                                                                                                        }),
                                                             }
    );

    // When.
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, true, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    auto expectedSampleInstrument1 = std::make_unique<Instrument>("s1", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample1, Loop(0, 10, true)));
    auto expectedSampleInstrument3 = std::make_unique<Instrument>("s3", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample3, Loop(20, 30)));

    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 1
    //expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());                            // 2, unused.
    expectedSong->addInstrument(std::move(expectedSampleInstrument1));                                                      // 2, was 3.
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForSingleBeep());                       // 3, was 4.
    //expectedSong->addInstrument(std::move(sampleInstrument2));                                                      // 5, unused.
    expectedSong->addInstrument(std::move(expectedSampleInstrument3));                                                      // 4, was 6.

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 2) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 3) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 4) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 3) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(10) },
                                                                                                                { 1, SpecialCell::buildSpecialCell(2) },  // Spl
                                                                                                                { 2, SpecialCell::buildSpecialCell(4) },  // Spl
                                                                                                                { 3, SpecialCell::buildSpecialCell(7) },
                                                                                                                { 4, SpecialCell::buildSpecialCell(10) },
                                                                                                        }),
                                                             }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("InstrumentsOptimizer, sample exports. No samples are used in the tracks, but events are used, the samples must be kept.", "[InstrumentsOptimizer]")
{
    // No change at all because no instrument is unused (even though the sample instruments are only declared in the Event Tracks).

    // Given.
    const juce::MemoryBlock memoryBlock1(60, true);
    auto sample1 = std::make_shared<Sample>(memoryBlock1);
    auto originalSampleInstrument1 = std::make_unique<Instrument>("s1", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample1, Loop(0, 10, true)));
    const juce::MemoryBlock memoryBlock2(80, true);
    auto sample2 = std::make_shared<Sample>(memoryBlock2);
    auto originalSampleInstrument2 = std::make_unique<Instrument>("s2", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample2, Loop(10, 20)));
    const juce::MemoryBlock memoryBlock3(100, true);
    auto sample3 = std::make_shared<Sample>(memoryBlock3);
    auto originalSampleInstrument3 = std::make_unique<Instrument>("s3", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample3, Loop(20, 30)));

    // Instrument 3, 5, 6 are the samples.
    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 1
    originalSong->addInstrument(std::move(originalSampleInstrument1));                                                // 2 spl
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForSingleBeep());                       // 3
    originalSong->addInstrument(std::move(originalSampleInstrument2));                                                // 4 spl
    originalSong->addInstrument(std::move(originalSampleInstrument3));                                                // 5 spl

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 3) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 3) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 3) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 1) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(5) },  // Spl
                                                                                                                { 1, SpecialCell::buildSpecialCell(4) },  // Spl
                                                                                                                { 2, SpecialCell::buildSpecialCell(2) },  // Spl
                                                                                                                { 3, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 4, SpecialCell::buildSpecialCell(10) },
                                                                                                        }),
                                                             }
    );

    // When.
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, true, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    auto expectedSampleInstrument1 = std::make_unique<Instrument>("s1", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample1, Loop(0, 10, true)));
    auto expectedSampleInstrument2 = std::make_unique<Instrument>("s2", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample2, Loop(10, 20)));
    auto expectedSampleInstrument3 = std::make_unique<Instrument>("s3", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample3, Loop(20, 30)));

    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 1
    expectedSong->addInstrument(std::move(expectedSampleInstrument1));                                                // 2
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForSingleBeep());                       // 3
    expectedSong->addInstrument(std::move(expectedSampleInstrument2));                                                // 4
    expectedSong->addInstrument(std::move(expectedSampleInstrument3));                                                // 5

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 0),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 3) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 3) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 3) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 1) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(5) },  // Spl
                                                                                                                { 1, SpecialCell::buildSpecialCell(4) },  // Spl
                                                                                                                { 2, SpecialCell::buildSpecialCell(2) },  // Spl
                                                                                                                { 3, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 4, SpecialCell::buildSpecialCell(10) },
                                                                                                        }),
                                                             }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}

TEST_CASE("InstrumentsOptimizer, sample exports, some instrs and samples are not used, making event tracks clash.", "[InstrumentsOptimizer]")
{
    // Given.
    const juce::MemoryBlock memoryBlock1(60, true);
    auto sample1 = std::make_shared<Sample>(memoryBlock1);
    auto originalSampleInstrument1 = std::make_unique<Instrument>("s1", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample1, Loop(0, 10, true)));
    const juce::MemoryBlock memoryBlock2(80, true);
    auto sample2 = std::make_shared<Sample>(memoryBlock2);
    auto originalSampleInstrument2 = std::make_unique<Instrument>("s2", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample2, Loop(10, 20)));

    auto originalSong = SongTestHelper::createSong();
    originalSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());       // 1
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForSingleBeep());                       // 2, unused
    originalSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForHihat());                            // 3, unused
    originalSong->addInstrument(std::move(originalSampleInstrument1));                                                // 4 spl, unused
    originalSong->addInstrument(std::move(originalSampleInstrument2));                                                // 5 spl

    const auto originalSubsong0 = SongTestHelper::addSubsong(*originalSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 1),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 1) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 5) },
                                                                                                         { 10, Cell::build(12, 5) },
                                                                                                         { 12,  Cell::build(19, 5) },
                                                                                                         { 15, Cell::build(5, 1) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 1, SpecialCell::buildSpecialCell(2) },
                                                                                                                { 2, SpecialCell::buildSpecialCell(3) },
                                                                                                        }),
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 21, SpecialCell::buildSpecialCell(5) },
                                                                                                                { 32, SpecialCell::buildSpecialCell(5) },
                                                                                                        }),
                                                             }
    );

    // When.
    InstrumentsOptimizer instrumentsOptimizer(*originalSong, true, true, true);
    const auto newSong = instrumentsOptimizer.optimize();

    // Then.
    REQUIRE((newSong != nullptr));

    auto expectedSong = SongTestHelper::createSong();
    auto expectedSampleInstrument2 = std::make_unique<Instrument>("s2", InstrumentType::sampleInstrument, PsgPart(),
                                                                  SamplePart(sample2, Loop(10, 20)));

    expectedSong->addInstrument(Instrument::buildEmptyPsgInstrument());
    expectedSong->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume());        // 1
    expectedSong->addInstrument(std::move(expectedSampleInstrument2));                                                // 2 spl, was 5

    const auto expectedSubsong0 = SongTestHelper::addSubsong(*expectedSong, 1, 6, 0, 2,
                                                             {
                                                                     Position(0),
                                                                     Position(1),
                                                             },
                                                             {
                                                                     Pattern({ 1, 0, 1 }, 0, 0),
                                                                     Pattern({ 1, 2, 2 }, 0, 1),
                                                             },
                                                             {
                                                                     // Track 0.
                                                                     TrackTestHelper::buildEmptyTrack(),
                                                                     // Track 1.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 1) },
                                                                                                         { 10, Cell::build(12, 1) },
                                                                                                         { 12,  Cell::build(19, 1) },
                                                                                                         { 15, Cell::build(5, 1) },
                                                                                                 }),
                                                                     // Track 2.
                                                                     TrackTestHelper::buildTrack({
                                                                                                         { 1,  Cell::build(10, 2) },
                                                                                                         { 10, Cell::build(12, 2) },
                                                                                                         { 12,  Cell::build(19, 2) },
                                                                                                         { 15, Cell::build(5, 1) },
                                                                                                 }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 20, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             },
                                                             {
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 0, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 1, SpecialCell::buildSpecialCell(2) },
                                                                                                                { 2, SpecialCell::buildSpecialCell(3) },
                                                                                                        }),
                                                                     TrackTestHelper::buildSpecialTrack({
                                                                                                                { 10, SpecialCell::buildSpecialCell(1) },
                                                                                                                { 21, SpecialCell::buildSpecialCell(2) },
                                                                                                                { 32, SpecialCell::buildSpecialCell(2) },
                                                                                                        }),
                                                             }
    );

    REQUIRE(SongTestHelper::areSongMusicallyEqual(*expectedSong, *newSong));
}


}   // namespace arkostracker

