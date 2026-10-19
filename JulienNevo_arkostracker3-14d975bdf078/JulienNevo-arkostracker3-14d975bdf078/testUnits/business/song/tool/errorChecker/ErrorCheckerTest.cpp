#include "../../../../catch.hpp"

#include "BinaryData.h"

#include "../../../../../source/business/song/tool/errorChecker/ErrorChecker.h"
#include "../../../../../source/business/song/tool/frameCounter/FrameCounter.h"
#include "../../../../../source/ui/patternViewer/controller/EffectErrorHelper.h"
#include "../../../../../source/utils/CollectionUtil.h"
#include "../../../../helper/SongTestHelper.h"
#include "../../../../helper/TrackTestHelper.h"

namespace arkostracker
{

class TestMethods
{
public:
    static void checkError(const std::vector<std::pair<CellLocationInPosition, juce::String>>& results, const Id& subsongId,
        const int positionIndex, const int lineIndex, const int channelIndex, const EffectError expectedError)
    {
    REQUIRE(CollectionUtil::contains(results,
        std::make_pair(CellLocationInPosition(subsongId, positionIndex, lineIndex, channelIndex),
            EffectErrorHelper::effectErrorToDisplayableString(expectedError))));
    }
};

// ============================================================


TEST_CASE("ErrorChecker, no error", "[ErrorChecker]")
{
    // Given.
    const auto song = SongTestHelper::loadSong(BinaryData::At3BoulesBits_aks, BinaryData::At3BoulesBits_aksSize);
    REQUIRE((song != nullptr));

    // When.
    const auto results = ErrorChecker::findErrors(*song);

    // Then.
    REQUIRE(results.empty());
}

TEST_CASE("ErrorChecker, one error", "[ErrorChecker]")
{
    // Given.
    const auto song = SongTestHelper::loadSong(BinaryData::At3BoulesBits_aks, BinaryData::At3BoulesBits_aksSize);
    REQUIRE((song != nullptr));
    const auto subsongId1 = song->getFirstSubsongId();

    const auto location1 = CellLocationInPosition(subsongId1, 1, 12, 2);
    TrackTestHelper::setCell(*song, location1,
        Cell(Note::buildNote(12), 1, CellEffects({
            { Effect::reset, 0 },
            { Effect::volume, 10 },
        })));

    // When.
    const auto results = ErrorChecker::findErrors(*song);

    // Then.
    REQUIRE((results.size() == 1));
    REQUIRE((results.at(0).first == location1));
}

TEST_CASE("ErrorChecker, two subsongs", "[ErrorChecker]")
{
    // Given.
    const auto song = SongTestHelper::loadSong(BinaryData::At3ErrorSong2Subsongs_aks, BinaryData::At3ErrorSong2Subsongs_aksSize);
    REQUIRE((song != nullptr));
    const auto subsongIds = song->getSubsongIds();
    const auto& subsong1 = subsongIds.at(0);
    const auto& subsong2 = subsongIds.at(1);

    // When.
    const auto results = ErrorChecker::findErrors(*song);

    // Then.
    REQUIRE((results.size() == 30));
    TestMethods::checkError(results, subsong1, 0, 3, 0, EffectError::pitchAndGlide0WithNewInstrumentIsUseless);
    TestMethods::checkError(results, subsong1, 0, 4, 0, EffectError::pitchAndGlide0WithNewInstrumentIsUseless);
    TestMethods::checkError(results, subsong1, 0, 5, 0, EffectError::volumeMustBeCombinedWithReset);
    TestMethods::checkError(results, subsong1, 0, 6, 0, EffectError::tooManyVolumeEffects);

    TestMethods::checkError(results, subsong1, 0, 0xa, 2, EffectError::pitchGlideAfterResetIsMeaningless);
    TestMethods::checkError(results, subsong1, 0, 0xc, 2, EffectError::pitchGlideWithInstrumentIsForbidden);
    TestMethods::checkError(results, subsong1, 0, 0xe, 2, EffectError::pitchAndGlide0WithNewInstrumentIsUseless);
    TestMethods::checkError(results, subsong1, 0, 0x10, 2, EffectError::pitchGlide0WithNoteIsUseless);

    TestMethods::checkError(results, subsong1, 2, 0x5, 1, EffectError::removeEffectBeforeReset); // Twice.
    TestMethods::checkError(results, subsong1, 2, 0x9, 1, EffectError::tooManyArpeggioEffects);
    TestMethods::checkError(results, subsong1, 2, 0xb, 1, EffectError::tooManyForceArpeggioSpeedEffects);
    TestMethods::checkError(results, subsong1, 2, 0xd, 1, EffectError::tooManyPitchTableEffects);

    TestMethods::checkError(results, subsong1, 2, 0x11, 2, EffectError::tooManyForceInstrumentSpeedEffects);

    TestMethods::checkError(results, subsong1, 2, 0x16, 0, EffectError::tooManyForcePitchTableSpeedEffects);

    TestMethods::checkError(results, subsong1, 2, 0x18, 1, EffectError::tooManyResetEffects);
    TestMethods::checkError(results, subsong1, 2, 0x1b, 1, EffectError::tooManyVolumeEffects);
    TestMethods::checkError(results, subsong1, 2, 0x1f, 1, EffectError::tooManyVolumeSlideEffects);
    TestMethods::checkError(results, subsong1, 2, 0x20, 1, EffectError::tooManyVolumeSlideEffects);
    TestMethods::checkError(results, subsong1, 2, 0x21, 1, EffectError::tooManyVolumeSlideEffects);
    TestMethods::checkError(results, subsong1, 2, 0x24, 1, EffectError::pitchTableHidingForceSpeed);
    TestMethods::checkError(results, subsong1, 2, 0x26, 1, EffectError::arpeggioTableOrDirectHidingForceSpeed);
    TestMethods::checkError(results, subsong1, 2, 0x29, 2, EffectError::uselessEffectStopAfterReset);
    TestMethods::checkError(results, subsong1, 2, 0x2d, 0, EffectError::volumeHidingVolumeSlide);
    TestMethods::checkError(results, subsong1, 2, 0x2e, 0, EffectError::volumeHidingVolumeSlide);
    TestMethods::checkError(results, subsong1, 2, 0x31, 1, EffectError::volumeMustBeCombinedWithReset);

    TestMethods::checkError(results, subsong2, 2, 0x10, 1, EffectError::pitchGlideWithInstrumentIsForbidden);
    TestMethods::checkError(results, subsong2, 2, 0x12, 1, EffectError::tooManyResetEffects);
    TestMethods::checkError(results, subsong2, 2, 0x13, 1, EffectError::pitchAndGlide0WithNewInstrumentIsUseless);
    TestMethods::checkError(results, subsong2, 2, 0x13, 1, EffectError::tooManyPitchEffects);
}

}   // namespace arkostracker
