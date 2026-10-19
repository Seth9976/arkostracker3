#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/optimizers/TrackOptimizer.h"
#include "../../../../helper/TrackTestHelper.h"

namespace arkostracker
{

TEST_CASE("TrackOptimizer, same set volume", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::volume, 0xf }, } )) },
        { 10, Cell({}, {}, CellEffects({ { Effect::volume, 0xf }, } )) },           // Same, so optimized.
        { 20, Cell({}, {}, CellEffects({ { Effect::volume, 0xf }, } )) },           // Same, so optimized.
        { 30, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::volume, 0xf }, } )) },           // Same, so optimized.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::volume, 0xf }, } )) },
        { 30, Cell(Note::buildNote(12), 1) },
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, pitch up invalidation", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchUp, 0x10 }, } )) },
        { 3, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x10 }, } )) },      // Same, can be optimized because alone.
        { 5, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x10 }, } )) },      // Same, can be optimized because alone.
        { 6, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x20 }, } )) },
        { 7, Cell(Note::buildNote(10), 1, CellEffects({ { Effect::pitchUp, 0x20 }, } )) },      // Same, but note, so cannot be optimized.
        { 8, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x20 }, } )) },      // Same, optimized.
        { 10, Cell(Note::buildNote(10), 1)},
        { 12, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x0 }, } )) },      // No pitch already, so can be optimized.
        { 13, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x10 }, } )) },
        { 14, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x10 }, } )) },     // Optimized.
        { 15, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x0 }, } )) },
        { 16, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x0 }, } )) },      // Optimized.
        { 20, Cell(Note::buildNote(10), 1, CellEffects({ { Effect::pitchUp, 0x0 }, } )) },      // Considered an error, removed by normalizer.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchUp, 0x10 }, } )) },
        { 6, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x20 }, } )) },
        { 7, Cell(Note::buildNote(10), 1, CellEffects({ { Effect::pitchUp, 0x20 }, } )) },      // Same, but note, so cannot be optimized.
        { 10, Cell(Note::buildNote(10), 1) },
        { 13, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x10 }, } )) },
        { 15, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x0 }, } )) },
        { 20, Cell(Note::buildNote(10), 1) },
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, pitches invalidation and reset", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchDown, 0x10 }, } )) },
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchDown, 0x10 }, } )) },      // Can not be optimized because on note.
        { 3, Cell({}, {}, CellEffects({ { Effect::pitchDown, 0x10 }, } )) },            // Optimized.
        { 4, Cell({}, {}, CellEffects({ { Effect::pitchGlide, 0x10 }, } )) },           // Different effect, not optimized.
        { 5, Cell({}, {}, CellEffects({ { Effect::pitchDown, 0x10 }, } )) },            // Invalidated by glide, so not optimized.

        { 6, Cell({}, {}, CellEffects({ { Effect::fastPitchDown, 0x0 }, } )) },
        { 7, Cell({}, {}, CellEffects({ { Effect::fastPitchDown, 0x0 }, } )) },         // Optimized because same.
        { 8, Cell({}, {}, CellEffects({ { Effect::fastPitchUp, 0x0 }, } )) },           // Optimized because all pitches are 0 when one is.
        { 9, Cell({}, {}, CellEffects({ { Effect::pitchGlide, 0x0 }, } )) },            // Idem.
        { 10, Cell({}, {}, CellEffects({ { Effect::pitchUp, 0x0 }, } )) },              // Idem.
        { 11, Cell({}, {}, CellEffects({ { Effect::pitchDown, 0x0 }, } )) },            // Idem.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchDown, 0x10 }, } )) },
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchDown, 0x10 }, } )) },      // Can not be optimized because on note.
        { 4, Cell({}, {}, CellEffects({ { Effect::pitchGlide, 0x10 }, } )) },           // Different effect, not optimized.
        { 5, Cell({}, {}, CellEffects({ { Effect::pitchDown, 0x10 }, } )) },            // Invalidated by glide, so not optimized.

        { 6, Cell({}, {}, CellEffects({ { Effect::fastPitchDown, 0x0 }, } )) },
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, volume set, in, out", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::volume, 0xc }, } )) },
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::volume, 0xd }, } )) },
        { 2, Cell({}, {}, CellEffects({ { Effect::volume, 0xd }, } )) },            // Optimized.
        { 4, Cell(Note::buildNote(12), 2, CellEffects({ { Effect::volume, 0xd }, } )) },        // Optimized.

        { 6, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x2 }, } )) },
        { 7, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x2 }, } )) },     // Optimized.
        { 9, Cell({}, {}, CellEffects({ { Effect::volume, 0xd }, } )) },        // Even though same, cannot be optimized because invalidated by Out.
        { 10, Cell({}, {}, CellEffects({ { Effect::volumeIn, 0x2 }, } )) },     // Same, but invalidated by Set Volume.
        { 11, Cell({}, {}, CellEffects({ { Effect::volumeIn, 0x1 }, } )) },
        { 12, Cell({}, {}, CellEffects({ { Effect::volumeIn, 0x1 }, } )) },     // Optimized.
        { 13, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x1 }, } )) },
        { 14, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x0 }, } )) },
        { 15, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x0 }, } )) },    // Optimized.
        { 16, Cell({}, {}, CellEffects({ { Effect::volumeIn, 0x0 }, } )) },     // Optimized because volume Out also set In to 0.

        { 17, Cell({}, {}, CellEffects({ { Effect::volume, 0xf }, } )) },
        { 18, Cell({}, {}, CellEffects({ { Effect::volumeIn, 0x0 }, } )) },     // Optimized because Set Volume also set In/Out to 0.
        { 19, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x0 }, } )) },    // Optimized because Set Volume also set In/Out to 0.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::volume, 0xc }, } )) },
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::volume, 0xd }, } )) },
        { 4, Cell(Note::buildNote(12), 2) },

        { 6, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x2 }, } )) },
        { 9, Cell({}, {}, CellEffects({ { Effect::volume, 0xd }, } )) },        // Even though same, cannot be optimized because invalidated by Out.
        { 10, Cell({}, {}, CellEffects({ { Effect::volumeIn, 0x2 }, } )) },     // Same, but invalidated by Set Volume.
        { 11, Cell({}, {}, CellEffects({ { Effect::volumeIn, 0x1 }, } )) },
        { 13, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x1 }, } )) },
        { 14, Cell({}, {}, CellEffects({ { Effect::volumeOut, 0x0 }, } )) },

        { 17, Cell({}, {}, CellEffects({ { Effect::volume, 0xf }, } )) },
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, instrument speed", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },            // Nothing to do with it.
        { 2, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },  // Not optimized because note.
        { 3, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },          // Optimized because same.
        { 4, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x2 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x2 }, } )) },          // Nothing to do with it.
        { 6, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x2 }, } )) },          // Optimized because same.
        { 7, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },

        { 10, Cell(Note::buildNote(12), 10) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceInstrumentSpeed, 0x0 }, } )) },  // Not optimized because note.
        { 12, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x0 }, } )) },         // Optimized.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },
        { 2, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },
        { 4, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x2 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x2 }, } )) },
        { 7, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },

        { 10, Cell(Note::buildNote(12), 10) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceInstrumentSpeed, 0x0 }, } )) },  // Not optimized because note.
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, arp speed", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },            // Nothing to do with it.
        { 2, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },  // Not optimized because note.
        { 3, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },          // Optimized because same.
        { 4, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x2 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x2 }, } )) },          // Nothing to do with it.
        { 6, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x2 }, } )) },          // Optimized because same.
        { 7, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },

        { 10, Cell(Note::buildNote(12), 10) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceArpeggioSpeed, 0x0 }, } )) },  // Not optimized because note.
        { 12, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x0 }, } )) },         // Optimized.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x1 }, } )) },
        { 2, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },
        { 4, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x2 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x2 }, } )) },
        { 7, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },

        { 10, Cell(Note::buildNote(12), 10) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forceArpeggioSpeed, 0x0 }, } )) },  // Not optimized because note.
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, pitch speed", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },            // Nothing to do with it.
        { 2, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },  // Not optimized because note.
        { 3, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },          // Optimized because same.
        { 4, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x2 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x2 }, } )) },          // Nothing to do with it.
        { 6, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x2 }, } )) },          // Optimized because same.
        { 7, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },

        { 10, Cell(Note::buildNote(12), 10) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forcePitchTableSpeed, 0x0 }, } )) },  // Not optimized because note.
        { 12, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x0 }, } )) },         // Optimized.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },
        { 2, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },
        { 4, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x2 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x2 }, } )) },
        { 7, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },

        { 10, Cell(Note::buildNote(12), 10) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::forcePitchTableSpeed, 0x0 }, } )) },  // Not optimized because note.
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, arpeggios", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },         // Optimized because already stopped.
        { 2, Cell({}, {}, CellEffects({ { Effect::arpeggio3Notes, 0x0 }, } )) },        // Optimized because already stopped.
        { 3, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x0 }, } )) },        // Optimized because already stopped.

        { 4, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 5, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 6, Cell({}, {}, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 7, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },
        { 8, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },
        { 9, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },
        { 10, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },

        { 11, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x0 }, } )) },
        { 12, Cell({}, {}, CellEffects({ { Effect::arpeggio3Notes, 0x0 }, } )) },       // Optimized because already stopped.
        { 13, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },        // Optimized because already stopped.

        { 15, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
        { 16, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
        { 17, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
        { 18, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },
        { 19, Cell({}, {}, CellEffects({ { Effect::arpeggio3Notes, 0x0 }, } )) },        // Optimized because already stopped.
        { 20, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },         // Optimized because already stopped.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },

        { 4, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 5, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 6, Cell({}, {}, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 7, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },
        { 8, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },
        { 9, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },
        { 10, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x37c }, } )) },

        { 11, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x0 }, } )) },

        { 15, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
        { 16, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
        { 17, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
        { 18, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, pitch table", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },         // Alien.
        { 2, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },        // Optimized because already stopped.
        { 3, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },        // Optimized because already stopped.
        { 4, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x1 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 6, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },        // Optimized because already stopped.

        { 10, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },  // Optimized because already stopped.
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 12, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 13, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 14, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 15, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 16, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x47 }, } )) },
        { 17, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 18, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },        // Optimized because already stopped.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 1, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },         // Alien.
        { 4, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x1 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },

        { 10, Cell(Note::buildNote(12), 1) },           // Optimized.
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 12, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 13, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 14, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
        { 15, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x45 }, } )) },
        { 16, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x47 }, } )) },
        { 17, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, reset", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },
        { 2, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },                // Optimized.
        { 3, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.
        { 4, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x1 }, } )) },
        { 5, Cell({}, {}, CellEffects({ { Effect::reset, 0x1 }, } )) },                     // Optimized.
        { 6, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x1 }, } )) },     // Optimized.
        { 7, Cell({}, {}, CellEffects({ { Effect::volume, 0xf }, } )) },

        { 8, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchDown, 0x0 }, } )) },     // Optimized.
        { 9, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 10, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchUp, 0x0 }, } )) },     // Optimized.
        { 11, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 12, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::fastPitchUp, 0x0 }, } )) },     // Optimized.
        { 13, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 14, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::fastPitchDown, 0x0 }, } )) },     // Optimized.
        { 15, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 16, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchGlide, 0x0 }, } )) },     // Optimized.
        { 17, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 18, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::volumeIn, 0x0 }, } )) },     // Optimized.
        { 19, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 20, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::volumeOut, 0x0 }, } )) },     // Optimized.
        { 21, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 22, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x0 }, } )) },     // Optimized.
        { 23, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 24, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio3Notes, 0x0 }, } )) },     // Optimized.
        { 25, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 26, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggio4Notes, 0x0 }, } )) },     // Optimized.
        { 27, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 28, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x0 }, } )) },     // Optimized.
        { 29, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },     // Optimized.

        { 30, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x1 }, } )) },
        { 32, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },

        { 33, Cell({}, {}, CellEffects({ { Effect::fastPitchDown, 0x123 }, } )) },
        { 34, Cell({}, {}, CellEffects({ { Effect::reset, 0x0 }, } )) },

        { 35, Cell({}, {}, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 36, Cell({}, {}, CellEffects({ { Effect::reset, 0x0 }, } )) },

        { 35, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x379 }, } )) },
        { 36, Cell({}, {}, CellEffects({ { Effect::reset, 0x0 }, } )) },
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 1, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },
        { 3, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 4, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x1 }, } )) },
        { 6, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 7, Cell({}, {}, CellEffects({ { Effect::volume, 0xf }, } )) },
        { 8, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 9, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 10, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 11, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 12, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 13, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 14, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 15, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 16, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 17, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 18, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 19, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 20, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 21, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 22, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 23, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 24, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 25, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 26, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 27, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 28, Cell(Note::buildNote(12), 1) },     // Optimized.
        { 29, Cell(Note::buildNote(12), 1) },     // Optimized.

        { 30, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x1 }, } )) },
        { 32, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::reset, 0x0 }, } )) },

        { 33, Cell({}, {}, CellEffects({ { Effect::fastPitchDown, 0x123 }, } )) },
        { 34, Cell({}, {}, CellEffects({ { Effect::reset, 0x0 }, } )) },

        { 35, Cell({}, {}, CellEffects({ { Effect::arpeggio3Notes, 0x37 }, } )) },
        { 36, Cell({}, {}, CellEffects({ { Effect::reset, 0x0 }, } )) },

        { 35, Cell({}, {}, CellEffects({ { Effect::arpeggio4Notes, 0x379 }, } )) },
        { 36, Cell({}, {}, CellEffects({ { Effect::reset, 0x0 }, } )) },
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

/** This comes from the TU's song "At2ForceArpeggioSpeedChannel1.aks" */
TEST_CASE("TrackOptimizer, arp and speed", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0x0, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
        { 0x3, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x1 }, } )) },
        { 0x6, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x0 }, } )) },
        { 0x9, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x4 }, } )) },
        { 0xc, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x10 }, } )) },
        { 0xf, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x2 }, } )) },
        { 0x12, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x0 }, } )) },
        { 0x14, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x2 }, } )) },
        { 0x16, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x0 }, } )) },

        { 0x17, Cell(Note::buildNote(12), 1) },
        { 0x19, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x0 }, } )) },
        { 0x1a, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x2 }, } )) },
        { 0x1c, Cell({}, {}, CellEffects({ { Effect::forceArpeggioSpeed, 0x5 }, } )) },

        { 0x1e, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::arpeggioTable, 0x2 }, { Effect::forceArpeggioSpeed, 0x0 } } )) },
        { 0x21, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x1 }, { Effect::forceArpeggioSpeed, 0x6 } } )) },
        { 0x24, Cell({}, {}, CellEffects({ { Effect::arpeggioTable, 0x1 }, } )) },
    });

    // No change.
    const auto expectedTrack = track;

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

/** Adapted from above. */
TEST_CASE("TrackOptimizer, pitch table and speed", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0x0, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x1 }, } )) },
        { 0x3, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x1 }, } )) },
        { 0x6, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x0 }, } )) },
        { 0x9, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x4 }, } )) },
        { 0xc, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x10 }, } )) },
        { 0xf, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x2 }, } )) },
        { 0x12, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x0 }, } )) },
        { 0x14, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x2 }, } )) },
        { 0x16, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x0 }, } )) },

        { 0x17, Cell(Note::buildNote(12), 1) },
        { 0x19, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x0 }, } )) },
        { 0x1a, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x2 }, } )) },
        { 0x1c, Cell({}, {}, CellEffects({ { Effect::forcePitchTableSpeed, 0x5 }, } )) },

        { 0x1e, Cell(Note::buildNote(12), 1, CellEffects({ { Effect::pitchTable, 0x2 }, { Effect::forcePitchTableSpeed, 0x0 } } )) },
        { 0x21, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x1 }, { Effect::forcePitchTableSpeed, 0x6 } } )) },
        { 0x24, Cell({}, {}, CellEffects({ { Effect::pitchTable, 0x1 }, } )) },
    });

    // No change.
    const auto expectedTrack = track;

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

/** Adapted from At2GlideUpAndDownShort.aks. */
TEST_CASE("TrackOptimizer, glide and legato", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0x0, Cell(Note::buildNote(12), 1) },
        { 0x1, Cell(Note::buildNote(14), {}, CellEffects({ { Effect::pitchGlide, 0x200 }, } )) },
        { 0x2, Cell(Note::buildNote(12), {}, CellEffects({ { Effect::pitchGlide, 0x200 }, } )) },
    });

    // No change.
    const auto expectedTrack = track;

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

TEST_CASE("TrackOptimizer, instrument speed and legato", "[TrackOptimizer]")
{
    // Given.
    auto track = TrackTestHelper::buildTrack({
        { 0x0, Cell(Note::buildNote(12), 1) },
        { 0x1, Cell(Note::buildNote(14), {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x0 }, } )) },
        { 0x2, Cell(Note::buildNote(12), {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x0 }, } )) },       // Same, optimized.
    });

    const auto expectedTrack = TrackTestHelper::buildTrack({
        { 0x0, Cell(Note::buildNote(12), 1) },
        { 0x1, Cell(Note::buildNote(14), {}, CellEffects({ { Effect::forceInstrumentSpeed, 0x0 }, } )) },
        { 0x2, Cell(Note::buildNote(12), {}) },       // Same, optimized.
    });

    // When.
    TrackOptimizer::optimizeTrack(track);

    // Then.
    REQUIRE((track == expectedTrack));
}

}       // namespace arkostracker
