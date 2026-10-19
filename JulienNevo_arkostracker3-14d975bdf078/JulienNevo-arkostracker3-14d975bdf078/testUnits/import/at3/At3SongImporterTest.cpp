#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/import/at3/At3SongImporter.h"
#include "../common/CheckHarmlessGrenade.h"
#include "../common/CheckSarkboteur.h"

namespace arkostracker 
{

TEST_CASE("AT3 Import, wrong file", "[At3SongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::Kangaroo__Alienall_128, static_cast<size_t>(BinaryData::Kangaroo__Alienall_128Size), false);

    // Parses.
    const At3SongImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "aks"));
}

TEST_CASE("AT3 Import, right file", "[At3SongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::AT3HarmlessGrenade_xml, static_cast<size_t>(BinaryData::AT3HarmlessGrenade_xmlSize), false);

    // Parses.
    const At3SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
}

TEST_CASE("AT3 Import, load song ok, harmless grenade", "[At3SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::AT3HarmlessGrenade_xml, static_cast<size_t>(BinaryData::AT3HarmlessGrenade_xmlSize), false);

    // Parses.
    At3SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE((result != nullptr));
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE((report != nullptr));
    REQUIRE(report->isOk());
    REQUIRE((report->getWarningCount() == 0));
    REQUIRE((song != nullptr));

    // Checks the Song.
    CheckHarmlessGrenade::check(*song);
}

TEST_CASE("AT3 Import, sarkboteur", "[At3SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At3Sarkboteur_xml, static_cast<size_t>(BinaryData::At3Sarkboteur_xmlSize), false);

    // Parses.
    At3SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE((result != nullptr));
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE((report != nullptr));
    REQUIRE(report->isOk());
    REQUIRE((report->getWarningCount() == 0));
    REQUIRE((song != nullptr));

    // Checks the Song.
    CheckSarkboteur::check(*song, true);
}

TEST_CASE("AT3 Import, read only", "[At3SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At3HocusPocusShorterWithReadOnly_xml, BinaryData::At3HocusPocusShorterWithReadOnly_xmlSize, false);

    // Parses.
    At3SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE((result != nullptr));
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE((report != nullptr));
    REQUIRE(report->isOk());
    REQUIRE((report->getWarningCount() == 0));
    REQUIRE((song != nullptr));

    // Checks the Song.
    // Position 0, pattern 0. Tracks: 0, 1, 72.     Speed/event track: 0, 0.
    // Position 1, pattern 1. Tracks: 73, 74, 2.    4, 2.
    // Position 2, pattern 2. Tracks: 75, 4, 5.     5, 3.
    // Position 3, pattern 3. Tracks: 76, 71, 3.    6, 4.
    // Position 4, pattern 4. Tracks: 6, 8, 7.      7, 5.
    // Position 5, pattern 5. Tracks: 11, 10, 40.   1, 6.
    // Position 6, pattern 6. Tracks: 77, 78, 14.   8, 7.
    // Position 7, pattern 7. Tracks: 18, 19, 13.   9, 8.
    // Position 8, pattern 8. Tracks: 66, 80, 81.   10, 9.

    // Read-only flags for the 3 channels, plus the 2 special Tracks.
    const std::vector trackToReadOnly = {
        true, false, true, true, true,                  // Position 0.
        false, false, false, false, false,
        false, true, true, true, false,
        false, false, false, false, true,
        true, false, true, false, false,
        false, false, false, false, false,              // Position 5.
        false, false, false, false, false,
        false, false, true, false, false,
        false, false, false, true, true,
    };
    auto index = 0U;
    constexpr auto length = 9;

    song->performOnSubsong(song->getFirstSubsongId(), [&](Subsong& subsong) {
        REQUIRE((subsong.getLength() == length));
        for (auto positionIndex = 0; positionIndex < length; ++ positionIndex) {
            const auto position = subsong.getPosition(positionIndex);
            const auto pattern = subsong.getPatternFromIndex(position.getPatternIndex());
            for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
                const auto trackIndex = pattern.getCurrentTrackIndex(channelIndex);
                const auto readOnly = subsong.getTrackRefFromIndex(trackIndex).isReadOnly();

                REQUIRE((trackToReadOnly.at(index++) == readOnly));
            }

            const auto speedTrackIndex = pattern.getCurrentSpecialTrackIndex(true);
            REQUIRE((trackToReadOnly.at(index++) == subsong.getSpecialTrackRefFromIndex(speedTrackIndex, true).isReadOnly()));

            const auto eventTrackIndex = pattern.getCurrentSpecialTrackIndex(false);
            REQUIRE((trackToReadOnly.at(index++) == subsong.getSpecialTrackRefFromIndex(eventTrackIndex, false).isReadOnly()));
        }
    });

    REQUIRE((index == length * 5));
}

TEST_CASE("AT3 Import, Track colors", "[At3SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At3TrackColors_xml, static_cast<size_t>(BinaryData::At3TrackColors_xmlSize), false);

    // Parses.
    At3SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE((result != nullptr));
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE((report != nullptr));
    REQUIRE(report->isOk());
    REQUIRE((report->getWarningCount() == 0));
    REQUIRE((song != nullptr));

    // Checks the Song.
    song->performOnSubsong(song->getFirstSubsongId(), [&] (Subsong& subsong) {
        {
            const auto& track = subsong.getTrackRefFromIndex(0);
            REQUIRE((track.getName() == "bob"));
            REQUIRE((track.getColor() == 4291579984));
        }
        {
            const auto& track = subsong.getTrackRefFromIndex(1);
            REQUIRE((track.getName() == "bobette"));
            REQUIRE((track.getColor() == OptionalValue<juce::uint32>()));
        }
        {
            const auto& track = subsong.getTrackRefFromIndex(4);
            REQUIRE((track.getName() == ""));
            REQUIRE((track.getColor() == 4290493248));
        }
        {
            const auto& track = subsong.getTrackRefFromIndex(5);
            REQUIRE((track.getName() == "ettttt"));
            REQUIRE((track.getColor() == 4292706525));
        }
    });
}

}   // namespace arkostracker
