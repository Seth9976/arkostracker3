#include "../../catch.hpp"

#include "../../../source/business/link/LinkedTrackHelper.h"

namespace arkostracker
{

TEST_CASE("findNamedTracks, none", "[LinkedTrackHelper]")
{
    // Given.
    const auto song = Song::buildDefaultSong(true);
    const auto subsongId = song->getFirstSubsongId();
    song->performOnSubsong(subsongId, [&] (Subsong& subsong) {
        // Pattern 0 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track());
            const auto track1Index = subsong.addTrack(Track());
            const auto track2Index = subsong.addTrack(Track());
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("speed1"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("event1"));

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track());
            const auto track1Index = subsong.addTrack(Track());
            const auto track2Index = subsong.addTrack(Track());
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
    });

    // When.
    const auto result = LinkedTrackHelper::findNamedTracks(*song, subsongId, 0, 0);

    // Then.
    REQUIRE(result.empty());
}

TEST_CASE("findNamedTracks, named tracks present, not the target one", "[LinkedTrackHelper]")
{
    // Given.
    auto song = Song("testSong", "test", "test", "comments");
    auto localSubsong = std::make_unique<Subsong>("subsong0", 6, 50.0F, 0, 4, 4, 0, 2,
        std::vector { Psg::buildForCpc() }, SidPlayerCapability::buildForCpc(), false);
    const auto subsongId = localSubsong->getId();
    song.addSubsong(std::move(localSubsong));
    song.performOnSubsong(subsongId, [&] (Subsong& subsong) {
        // Pattern 0 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt0c0"));
            const auto track1Index = subsong.addTrack(Track());
            const auto track2Index = subsong.addTrack(Track("patt0c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track());
            const auto track1Index = subsong.addTrack(Track("patt1c1"));
            const auto track2Index = subsong.addTrack(Track("patt1c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        const auto endIndex = subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.setLoopAndEndStartPosition(0, endIndex);
    });

    // When.
    const auto result = LinkedTrackHelper::findNamedTracks(song, subsongId, 1, 0); // Target is not named, no exclusion.

    const auto expected = std::vector {
        LinkedTrackHelper::SearchResult("patt0c0", {
            TrackLocation(0, 0),
            TrackLocation(2, 0),
        }),
        LinkedTrackHelper::SearchResult("patt0c2", {
            TrackLocation(0, 2),
            TrackLocation(2, 2),
        }),
        LinkedTrackHelper::SearchResult("patt1c1", {
            TrackLocation(1, 1),
        }),
        LinkedTrackHelper::SearchResult("patt1c2", {
            TrackLocation(1, 2),
        }),
    };

    // Then.
    REQUIRE((result == expected));
}

TEST_CASE("findNamedTracks, named tracks present, target is excluded", "[LinkedTrackHelper]")
{
    // Given.
    auto song = Song("testSong", "test", "test", "comments");
    auto localSubsong = std::make_unique<Subsong>("subsong0", 6, 50.0F, 0, 4, 4, 0, 2,
        std::vector { Psg::buildForCpc() }, SidPlayerCapability::buildForCpc(), false);
    const auto subsongId = localSubsong->getId();
    song.addSubsong(std::move(localSubsong));
    song.performOnSubsong(subsongId, [&] (Subsong& subsong) {
        // Pattern 0 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt0c0"));
            const auto track1Index = subsong.addTrack(Track());
            const auto track2Index = subsong.addTrack(Track("patt0c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track());
            const auto track1Index = subsong.addTrack(Track("patt1c1"));
            const auto track2Index = subsong.addTrack(Track("patt1c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        const auto endIndex = subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.setLoopAndEndStartPosition(0, endIndex);
    });

    // When.
    const auto result = LinkedTrackHelper::findNamedTracks(song, subsongId, 0, 0);

    const auto expected = std::vector {
        LinkedTrackHelper::SearchResult("patt0c2", {
            TrackLocation(0, 2),
            TrackLocation(2, 2),
        }),
        LinkedTrackHelper::SearchResult("patt1c1", {
            TrackLocation(1, 1),
        }),
        LinkedTrackHelper::SearchResult("patt1c2", {
            TrackLocation(1, 2),
        }),
    };

    // Then.
    REQUIRE((result == expected));
}



// =============================================================================


TEST_CASE("findLinkedTracks, found, target is excluded", "[LinkedTrackHelper]")
{
    // Given.
    auto song = Song("testSong", "test", "test", "comments");
    auto localSubsong = std::make_unique<Subsong>("subsong0", 6, 50.0F, 0, 4, 4, 0, 2,
        std::vector { Psg::buildForCpc() }, SidPlayerCapability::buildForCpc(), false);
    const auto subsongId = localSubsong->getId();
    song.addSubsong(std::move(localSubsong));
    song.performOnSubsong(subsongId, [&] (Subsong& subsong) {
        // Pattern 0 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt0c0"));
            const auto track1Index = subsong.addTrack(Track("patt0c1"));
            const auto track2Index = subsong.addTrack(Track("patt0c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index, 4),         // Linked.
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index, 4),         // Linked.
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt1c0"));
            const auto track1Index = subsong.addTrack(Track("patt1c1"));                // LINKED TO.
            const auto track2Index = subsong.addTrack(Track("patt1c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),                        // LINKED TO.
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index, 4),    // Linked.
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        const auto endIndex = subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.setLoopAndEndStartPosition(0, endIndex);
    });

    // When.
    const auto result = LinkedTrackHelper::findLinkedTracks(song, subsongId, 0, 0);

    const auto expected = std::vector {
        LinkedTrackHelper::SearchResult("patt1c1", {
            // position 0, channel 0 excluded.
            TrackLocation(0, 2),
            TrackLocation(1, 1),    // The Linked To is here.
            TrackLocation(1, 2),
            TrackLocation(2, 0),    // Not excluded, not the target.
            TrackLocation(2, 2),
        }),
    };

    // Then.
    REQUIRE((result == expected));
}



// =============================================================================


TEST_CASE("findLinkedToTracks, with results", "[LinkedTrackHelper]")
{
    // Given.
    auto song = Song("testSong", "test", "test", "comments");
    auto localSubsong = std::make_unique<Subsong>("subsong0", 6, 50.0F, 0, 4, 4, 0, 2,
        std::vector { Psg::buildForCpc() }, SidPlayerCapability::buildForCpc(), false);
    const auto subsongId = localSubsong->getId();
    song.addSubsong(std::move(localSubsong));
    song.performOnSubsong(subsongId, [&] (Subsong& subsong) {
        // Pattern 0 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt0c0"));
            const auto track1Index = subsong.addTrack(Track("patt0c1"));
            const auto track2Index = subsong.addTrack(Track("patt0c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index, 4),         // Linked.
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index, 4),         // Linked.
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt1c0"));
            const auto track1Index = subsong.addTrack(Track("patt1c1"));                // LINKED TO.
            const auto track2Index = subsong.addTrack(Track("patt1c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),                        // LINKED TO.
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index, 4),    // Linked.
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        const auto endIndex = subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.setLoopAndEndStartPosition(0, endIndex);
    });

    // When.
    const auto result = LinkedTrackHelper::findLinkedToTracks(song, subsongId, 1, 1);

    const auto expected = std::vector {
        LinkedTrackHelper::SearchResult("patt1c1", {
            TrackLocation(0, 0),
            TrackLocation(0, 2),
            // Excluded: TrackLocation(1, 1),
            TrackLocation(1, 2),
            TrackLocation(2, 0),
            TrackLocation(2, 2),
        }),
    };

    // Then.
    REQUIRE((result == expected));
}

TEST_CASE("findLinkedToTracks, no result", "[LinkedTrackHelper]")
{
    // Given.
    auto song = Song("testSong", "test", "test", "comments");
    auto localSubsong = std::make_unique<Subsong>("subsong0", 6, 50.0F, 0, 4, 4, 0, 2,
        std::vector { Psg::buildForCpc() }, SidPlayerCapability::buildForCpc(), false);
    const auto subsongId = localSubsong->getId();
    song.addSubsong(std::move(localSubsong));
    song.performOnSubsong(subsongId, [&] (Subsong& subsong) {
        // Pattern 0 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt0c0"));
            const auto track1Index = subsong.addTrack(Track("patt0c1"));
            const auto track2Index = subsong.addTrack(Track("patt0c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt1c0"));
            const auto track1Index = subsong.addTrack(Track("patt1c1"));
            const auto track2Index = subsong.addTrack(Track("patt1c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack());
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack());

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }
                )
            );
        }

        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        const auto endIndex = subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.setLoopAndEndStartPosition(0, endIndex);
    });

    // When.
    const auto result = LinkedTrackHelper::findLinkedToTracks(song, subsongId, 2, 1);

    // Then.
    REQUIRE(result.empty());
}

}   // namespace arkostracker
