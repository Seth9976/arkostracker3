#include "../../catch.hpp"

#include "../../../source/business/link/LinkedSpecialTrackHelper.h"

namespace arkostracker
{

TEST_CASE("findNamedSpecialTracks, none", "[LinkedSpecialTrackHelper]")
{
    // Given.
    const auto song = Song::buildDefaultSong(true);
    const auto subsongId = song->getFirstSubsongId();
    song->performOnSubsong(subsongId, [&] (Subsong& subsong) {
        // Pattern 0 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("aa"));
            const auto track1Index = subsong.addTrack(Track("bb"));
            const auto track2Index = subsong.addTrack(Track("cc"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack(""));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack(""));

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
            const auto track0Index = subsong.addTrack(Track("dd"));
            const auto track1Index = subsong.addTrack(Track("ee"));
            const auto track2Index = subsong.addTrack(Track("ff"));
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
    const auto resultSpeed = LinkedSpecialTrackHelper::findNamedSpecialTracks(*song, subsongId, 0, true);
    const auto resultEvent = LinkedSpecialTrackHelper::findNamedSpecialTracks(*song, subsongId, 0, false);

    // Then.
    REQUIRE(resultSpeed.empty());
    REQUIRE(resultEvent.empty());
}

TEST_CASE("findNamedSpecialTracks, named Special tracks present, not the target one", "[LinkedSpecialTrackHelper]")
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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt0sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt0ev"));

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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt1sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt1ev"));

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
    const auto result = LinkedSpecialTrackHelper::findNamedSpecialTracks(song, subsongId, 1, true); // Target is not named, no exclusion.

    const auto expected = std::vector {
        LinkedSpecialTrackHelper::SearchResult("patt0sp", {
            SpecialTrackLocation(true, 0),
            SpecialTrackLocation(true, 2),
        }),
    };

    // Then.
    REQUIRE((result == expected));
}

TEST_CASE("findNamedSpecialTracks, named tracks present, target is excluded", "[LinkedSpecialTrackHelper]")
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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt0sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt0ev"));

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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt1sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt1ev"));

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
        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        const auto endIndex = subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.setLoopAndEndStartPosition(0, endIndex);
    });

    // When.
    const auto result = LinkedSpecialTrackHelper::findNamedSpecialTracks(song, subsongId, 0, false);

    const auto expected = std::vector {
        LinkedSpecialTrackHelper::SearchResult("patt1ev", {
            SpecialTrackLocation(false, 1),
            SpecialTrackLocation(false, 3),
        }),
    };

    // Then.
    REQUIRE((result == expected));
}


// =============================================================================


TEST_CASE("findLinkedSpecialTracks, found, target is excluded", "[LinkedSpecialTrackHelper]")
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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt0sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt0ev"));

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index, 4),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index, 4),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex, 1) },         // Linked.
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex, 1) }         // Linked.
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt1c0"));
            const auto track1Index = subsong.addTrack(Track("patt1c1"));
            const auto track2Index = subsong.addTrack(Track("patt1c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt1sp"));        // LINKED TO.
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt1ev"));       // LINKED TO.

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index, 4),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex) },                    // LINKED TO.
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex) }                     // LINKED TO.
                )
            );
        }

        subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.addPosition(Position(1, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        const auto endIndex = subsong.addPosition(Position(0, 64, juce::String(), LookAndFeelConstants::defaultPatternColor, { }));
        subsong.setLoopAndEndStartPosition(0, endIndex);
    });

    // When.
    const auto resultSpeed = LinkedSpecialTrackHelper::findLinkedSpecialTracks(song, subsongId, 0, true);
    const auto resultEvent = LinkedSpecialTrackHelper::findLinkedSpecialTracks(song, subsongId, 0, false);

    const auto expectedSpeed = std::vector {
        LinkedSpecialTrackHelper::SearchResult("patt1sp", {
            // position 0 excluded.
            SpecialTrackLocation(true, 1),    // The Linked To is here.
            SpecialTrackLocation(true, 2),    // Not excluded, not the target.
        }),
    };

    const auto expectedEvent = std::vector {
        LinkedSpecialTrackHelper::SearchResult("patt1ev", {
            // position 0 excluded.
            SpecialTrackLocation(false, 1),    // The Linked To is here.
            SpecialTrackLocation(false, 2),    // Not excluded, not the target.
        }),
    };

    // Then.
    REQUIRE((resultSpeed == expectedSpeed));
    REQUIRE((resultEvent == expectedEvent));
}


// =============================================================================

TEST_CASE("findLinkedToSpecialTracks, with results", "[LinkedSpecialTrackHelper]")
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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt0sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt0ev"));

            subsong.addPattern(Pattern(
                    {
                        Pattern::TrackIndexAndLinkedTrackIndex(track0Index, 4),
                        Pattern::TrackIndexAndLinkedTrackIndex(track1Index),
                        Pattern::TrackIndexAndLinkedTrackIndex(track2Index, 4),
                    },
                    { Pattern::TrackIndexAndLinkedTrackIndex(speedTrackIndex, 1) },         // Linked.
                    { Pattern::TrackIndexAndLinkedTrackIndex(eventTrackIndex, 1) }         // Linked.
                )
            );
        }

        // Pattern 1 and its Tracks.
        {
            const auto track0Index = subsong.addTrack(Track("patt1c0"));
            const auto track1Index = subsong.addTrack(Track("patt1c1"));
            const auto track2Index = subsong.addTrack(Track("patt1c2"));
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt1sp"));                // LINKED TO.
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt1ev"));               // LINKED TO.

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
    const auto resultSpeed = LinkedSpecialTrackHelper::findLinkedToSpecialTracks(song, subsongId, 1, true);
    const auto resultEvent = LinkedSpecialTrackHelper::findLinkedToSpecialTracks(song, subsongId, 1, false);

    const auto expectedSpeed = std::vector {
        LinkedSpecialTrackHelper::SearchResult("patt1sp", {
            SpecialTrackLocation(true, 0),
            SpecialTrackLocation(true, 2),
            // Excluded: TrackLocation(1),
        }),
    };
    const auto expectedEvent = std::vector {
        LinkedSpecialTrackHelper::SearchResult("patt1ev", {
            SpecialTrackLocation(false, 0),
            SpecialTrackLocation(false, 2),
            // Excluded: TrackLocation(1),
        }),
    };

    // Then.
    REQUIRE((resultSpeed == expectedSpeed));
    REQUIRE((resultEvent == expectedEvent));
}

TEST_CASE("findLinkedToSpecialTracks, no result", "[LinkedTrackSpecialHelper]")
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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt0sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt0ev"));

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
            const auto speedTrackIndex = subsong.addSpecialTrack(true, SpecialTrack("patt1sp"));
            const auto eventTrackIndex = subsong.addSpecialTrack(false, SpecialTrack("patt1ev"));

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
    const auto resultSpeed = LinkedSpecialTrackHelper::findLinkedToSpecialTracks(song, subsongId, 2, true);
    const auto resultEvent = LinkedSpecialTrackHelper::findLinkedToSpecialTracks(song, subsongId, 2, false);

    // Then.
    REQUIRE(resultSpeed.empty());
    REQUIRE(resultEvent.empty());
}

}   // namespace arkostracker
