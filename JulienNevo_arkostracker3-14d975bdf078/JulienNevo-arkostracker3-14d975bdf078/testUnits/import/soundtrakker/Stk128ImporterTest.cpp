#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/import/soundtrakker/Stk128Importer.h"
#include "../../../source/song/subsong/SubsongConstants.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("Wrong extension", "[Stk128Importer]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::Kangaroo__Alienall_128, BinaryData::Kangaroo__Alienall_128Size, false);

    // Parses.
    const Stk128Importer importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "129"));
}

/** Could be wayyy more elaborate. */
TEST_CASE("Song import, alienall", "[Stk128Importer]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::Kangaroo__Alienall_128, BinaryData::Kangaroo__Alienall_128Size, false);

    // Parses.
    Stk128Importer importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "128"));
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "ALIENALL");
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted with Arkos Tracker.");
    REQUIRE(song->getSubsongCount() == 1);

    // Checks the Arpeggios.
    {
        const auto& expressionHandler = song->getExpressionHandler(true);
        REQUIRE(expressionHandler.getCount() == 17);

        REQUIRE(expressionHandler.getName(expressionHandler.find(0).getValue()) == "Empty");
        {
            const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(1).getValue());
            REQUIRE(expression.getName() == "Arpeggio 1");
            REQUIRE(expression.isArpeggio());
            REQUIRE(expression.getSpeed() == 0);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLength() == 32);
            REQUIRE(expression.getLoopStart() == 0);
            REQUIRE(expression.getEnd() == 31);
            std::vector expectedValues = {
                    0, 0, -5, -5, -8, -8,
                    0, 0, -5, -5, -8, -8,
                    0, 0, -5, -5, -8, -8,
                    0, 0, -5, -5, -8, -8,
                    0, 0, -5, -5, -8, -8,
                    0, 0
            };
            for (auto cellIndex = 0; cellIndex < 31; ++cellIndex) {
                REQUIRE(expression.getValue(cellIndex) == expectedValues.at(static_cast<size_t>(cellIndex)));
            }
        }

        {
            const auto expression = expressionHandler.getExpressionCopy(expressionHandler.find(2).getValue());
            REQUIRE(expression.getName() == "Arpeggio 2");
            REQUIRE(expression.isArpeggio());
            REQUIRE(expression.getSpeed() == 0);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLength() == 32);
            REQUIRE(expression.getLoopStart() == 0);
            REQUIRE(expression.getEnd() == 31);
            std::vector expectedValues = {
                    0, 0, -4, -4, -7, -7,
                    0, 0, -4, -4, -7, -7,
                    0, 0, -4, -4, -7, -7,
                    0, 0, -4, -4, -7, -7,
                    0, 0, -4, -4, -7, -7,
                    0, 0
            };
            for (auto cellIndex = 0; cellIndex < 31; ++cellIndex) {
                REQUIRE(expression.getValue(cellIndex) == expectedValues.at(static_cast<size_t>(cellIndex)));
            }
        }

        REQUIRE(expressionHandler.getNameFromIndex(16) == "Arpeggio 16");
    }
}

/** Could wayyy more elaborate. */
TEST_CASE("Song import, heppe", "[Stk128Importer]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::Kangaroo__Heppe2_128, BinaryData::Kangaroo__Heppe2_128Size, false);

    // Parses.
    Stk128Importer importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "128"));
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "HEPPE");
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted with Arkos Tracker.");
    REQUIRE(song->getSubsongCount() == 1);

    song->performOnConstSubsong(song->getFirstSubsongId(), [&](const Subsong& subsong) {
        REQUIRE(subsong.getName() == SubsongConstants::defaultFirstSubsongName);
        const auto metadata = subsong.getMetadata();
        const auto psgCount = subsong.getPsgCount();
        REQUIRE((metadata.getInitialSpeed() == 3));
        REQUIRE((psgCount == 1));
    });
}

/** Could wayyy more elaborate. */
TEST_CASE("Song import, deep space", "[Stk128Importer]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__Deep_Space_Resonance_128, BinaryData::Targhan__Deep_Space_Resonance_128Size, false);

    // Parses.
    Stk128Importer importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "128"));
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "RESONANC");
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted with Arkos Tracker.");
    REQUIRE(song->getSubsongCount() == 1);

    song->performOnConstSubsong(song->getFirstSubsongId(), [&](const Subsong& subsong) {
        REQUIRE(subsong.getName() == SubsongConstants::defaultFirstSubsongName);
        const auto metadata = subsong.getMetadata();
        const auto psgCount = subsong.getPsgCount();
        REQUIRE((metadata.getInitialSpeed() == 7));        // Funny, 7 at first, but then 6 in the Speed Track.
        REQUIRE((psgCount == 1));
        REQUIRE(juce::exactlyEqual(metadata.getReplayFrequencyHz(), 50.0F));
        REQUIRE((metadata.getDigiChannel() == 1));
        REQUIRE((metadata.getLoopStartPosition() == 0));
        constexpr auto endPosition = 35;
        REQUIRE((metadata.getEndPosition() == endPosition));
        REQUIRE((metadata.getName() == SubsongConstants::defaultFirstSubsongName));
        REQUIRE((metadata.getHighlightSpacing() == 4));
        REQUIRE((metadata.getSecondaryHighlight() == 4));

        // Checks the Positions.
        for (auto positionIndex = 0; positionIndex <= endPosition; ++positionIndex) {
            const auto expectedHeight = (positionIndex == 0x17) ? 32 : 64;      // One pattern is smaller.
            const auto& position = subsong.getPositionRef(positionIndex);
            REQUIRE(position.getHeight() == expectedHeight);
            REQUIRE(position.getMarkerName() == ((positionIndex == 0) ? Position::firstMarkerName : ""));
        }

        // Makes sure the Patterns only related to the Tracks only once.
        constexpr auto patternCount = 32;       // 30 but 2 are missing, so 2 more created.
        {
            std::set<int> browsedTrackIndexes;
            std::set<int> browsedSpeedTrackIndexes;
            std::set<int> browsedEventTrackIndexes;

            for (auto patternIndex = 0; patternIndex < patternCount; ++patternIndex) {
                const auto pattern = subsong.getPatternFromIndex(patternIndex);
                jassert(pattern.getChannelCount() == 3);
                for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
                    const auto trackIndex = pattern.getCurrentTrackIndex(channelIndex);
                    // The track must NOT exist!
                    REQUIRE(browsedTrackIndexes.find(trackIndex) == browsedTrackIndexes.cend());
                    browsedTrackIndexes.insert(trackIndex);
                }
                // The same for the Special Tracks.
                const auto speedTrackIndex = pattern.getCurrentSpecialTrackIndex(true);
                const auto eventTrackIndex = pattern.getCurrentSpecialTrackIndex(false);
                REQUIRE(browsedSpeedTrackIndexes.find(speedTrackIndex) == browsedSpeedTrackIndexes.cend());
                REQUIRE(browsedEventTrackIndexes.find(eventTrackIndex) == browsedEventTrackIndexes.cend());
                browsedSpeedTrackIndexes.insert(speedTrackIndex);
                browsedEventTrackIndexes.insert(eventTrackIndex);
            }
        }

        // Checks the Patterns.
        REQUIRE(subsong.getPatternCount() == patternCount);
        REQUIRE(subsong.getPatternRef(0).getCurrentSpecialTrackIndex(true) == 1);
        REQUIRE(subsong.getPatternRef(1).getCurrentSpecialTrackIndex(true) == 0);
        REQUIRE(subsong.getPatternRef(8).getCurrentSpecialTrackIndex(true) == 2);
        REQUIRE(subsong.getPatternRef(10).getCurrentSpecialTrackIndex(true) == 3);

        // Checks the Event Tracks.
        REQUIRE(subsong.getSpecialTrackCount(false) == patternCount);
        {
            const auto& specialTrack = subsong.getSpecialTrackRefFromPosition(0, false);
            REQUIRE(specialTrack.isEmpty());
        }

        // Checks the Speed Tracks.
        REQUIRE(subsong.getSpecialTrackCount(true) == patternCount);
        {
            const auto& specialTrack = subsong.getSpecialTrackRefFromIndex(1, true);
            REQUIRE(TrackTestHelper::containsOnly(specialTrack, {
                    { 1, 6 },
            }));
        }
        {
            const auto& specialTrack = subsong.getSpecialTrackRefFromIndex(0, true);
            REQUIRE(specialTrack.isEmpty());
        }
        {
            const auto& specialTrack = subsong.getSpecialTrackRefFromIndex(2, true);
            REQUIRE(TrackTestHelper::containsOnly(specialTrack, {
                    { 1, 6 },
            }));
        }
        {
            const auto& specialTrack = subsong.getSpecialTrackRefFromIndex(3, true);
            REQUIRE(TrackTestHelper::containsOnly(specialTrack, {
                    { 0, 6 },
            }));
        }
        {
            const auto& specialTrack = subsong.getSpecialTrackRefFromIndex(4, true);
            REQUIRE(TrackTestHelper::containsOnly(specialTrack, {
                    { 0, 3 },
            }));
        }
    });
}

TEST_CASE("Song import, resonance, with amsdos header", "[Stk128Importer]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::ResonanceWithHeader_128, BinaryData::ResonanceWithHeader_128Size, false);

    // Parses.
    Stk128Importer importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "128"));
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    REQUIRE(song->getTitle() == "RESONANC");
}

}   // namespace arkostracker
