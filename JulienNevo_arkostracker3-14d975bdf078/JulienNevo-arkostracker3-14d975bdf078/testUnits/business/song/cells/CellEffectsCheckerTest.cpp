#include "../../../catch.hpp"

#include "../../../../source/business/song/cells/CellEffectsChecker.h"
#include "../../../../source/song/cells/CellEffects.h"

namespace arkostracker 
{

TEST_CASE("checkEffects, no effect, no error", "[CellEffectsChecker]")
{
    const CellEffects effectsToCheck;

    REQUIRE(CellEffectsChecker::checkEffects(effectsToCheck, false, false).empty());
}

TEST_CASE("checkEffects, one effect, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect(Effect::reset));

    REQUIRE(CellEffectsChecker::checkEffects(effectsToCheck, false, false).empty());
}

TEST_CASE("checkEffects, same volume effect, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::volume, 0xf));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::volume, 0x4));

    REQUIRE((CellEffectsChecker::checkEffects(effectsToCheck, false, false) == std::unordered_map<int, EffectError> {
            { 3, EffectError::tooManyVolumeEffects }
    }));
}

TEST_CASE("checkEffects, volume and in, ok", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::volume, 0xf));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::volumeIn, 0x4));

    REQUIRE(CellEffectsChecker::checkEffects(effectsToCheck, false, false).empty());
}

TEST_CASE("checkEffects, volume and in and out, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::volume, 0xf));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::volumeIn, 0x4));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::volumeOut, 0x8));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 3, EffectError::tooManyVolumeSlideEffects },
    }));}

TEST_CASE("checkEffects, same pitch three times, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::pitchDown, 0xf));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::pitchUp, 0x4));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0x4));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 1, EffectError::tooManyPitchEffects },
            { 3, EffectError::tooManyPitchEffects },
    }));
}

TEST_CASE("checkEffects, volume before reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::volume, 0xf));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::reset, 0x4));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 0, EffectError::removeEffectBeforeReset },
    }));
}

TEST_CASE("checkEffects, effect before reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::volume, 0xf));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::noEffect, 0x4));      // Shouldn't happen, but...
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::arpeggio3Notes, 0x4));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 0, EffectError::removeEffectBeforeReset },
            { 2, EffectError::removeEffectBeforeReset },
    }));
}

TEST_CASE("checkEffects, effect before reset, other effects, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0xf));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::forceInstrumentSpeed, 0x4));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 0, EffectError::removeEffectBeforeReset },
            { 1, EffectError::removeEffectBeforeReset },
    }));
}

TEST_CASE("checkEffects, arp at 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::arpeggioTable, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 3, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, arp3 at 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::arpeggio3Notes, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 2, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, arp4 at 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::arpeggio4Notes, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 3, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, pitch table and glide at 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::pitchTable, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 1, EffectError::uselessEffectStopAfterReset },
            { 2, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, pitch up at 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::pitchUp, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 3, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, pitch down at not 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::pitchDown, 0x1));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, pitch up at not 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::pitchUp, 0x1));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, fast pitch down at not 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::fastPitchDown, 0x1));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, fast pitch up at not 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::fastPitchUp, 0x1));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, arp3 at not 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::arpeggio3Notes, 0x037));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, speeds at 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::forceInstrumentSpeed, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::forceArpeggioSpeed, 0x0));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::forcePitchTableSpeed, 0x0));
    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 1, EffectError::uselessEffectStopAfterReset },
            { 2, EffectError::uselessEffectStopAfterReset },
            { 3, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, speeds at not 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::forceInstrumentSpeed, 0x1));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::forceArpeggioSpeed, 0x02));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::forcePitchTableSpeed, 0x03));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, volume hiding volume slide, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::volumeOut, 0x10));
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::arpeggioTable, 0x0)); // To add entropy.
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::volume, 0x3));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 3, EffectError::volumeHidingVolumeSlide },
    }));
}

TEST_CASE("checkEffects, set volume after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(3, CellEffect::buildFromLogicalValue(Effect::volume, 0x3));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 3, EffectError::volumeMustBeCombinedWithReset },
    }));
}

TEST_CASE("checkEffects, set volume out 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::volumeOut, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 2, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, set volume in 0 after reset, error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::volumeIn, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
            { 2, EffectError::uselessEffectStopAfterReset },
    }));
}

TEST_CASE("checkEffects, set volume out other than 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::volumeOut, 0x1));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, set volume in other than 0 after reset, no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::volumeOut, 0x1));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result.empty()));
}

TEST_CASE("checkEffects, glide after a reset is meaningless", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::reset, 0x0));
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0x1));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, false, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
        { 2, EffectError::pitchGlideAfterResetIsMeaningless },
    }));
}

TEST_CASE("checkEffects, pitch 0 with note and instrument is useless", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::pitchUp, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, true, true);
    REQUIRE((result == std::unordered_map<int, EffectError> {
        { 1, EffectError::pitchAndGlide0WithNewInstrumentIsUseless },
    }));
}

TEST_CASE("checkEffects, glide 0 with note and instrument is an error", "[CellEffectsChecker]")
{
    // This is tested before the value test, so the error is actually the glide error, not the value 0 being useless.
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, true, true);
    REQUIRE((result == std::unordered_map<int, EffectError> {
        { 2, EffectError::pitchGlideWithInstrumentIsForbidden },
    }));
}

TEST_CASE("checkEffects, glide with note and instrument is an error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0x30));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, true, true);
    REQUIRE((result == std::unordered_map<int, EffectError> {
        { 2, EffectError::pitchGlideWithInstrumentIsForbidden },
    }));
}

TEST_CASE("checkEffects, glide with note but without instrument is fine", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(2, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0x30));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, true, false);
    REQUIRE(result.empty());
}

TEST_CASE("checkEffects, glide 0 with note but without instrument is useless", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(0, CellEffect::buildFromLogicalValue(Effect::pitchGlide, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, true, false);
    REQUIRE((result == std::unordered_map<int, EffectError> {
        { 0, EffectError::pitchGlide0WithNoteIsUseless },
    }));
}

TEST_CASE("checkEffects, pitch 0 but note without instrument, so no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::pitchDown, 0x0));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, true, false);
    REQUIRE(result.empty());
}

TEST_CASE("checkEffects, pitch but note and instrument, but value is not 0, so no error", "[CellEffectsChecker]")
{
    CellEffects effectsToCheck;
    effectsToCheck.setEffect(1, CellEffect::buildFromLogicalValue(Effect::pitchDown, 0x12));

    const auto result = CellEffectsChecker::checkEffects(effectsToCheck, true, true);
    REQUIRE(result.empty());
}

}   // namespace arkostracker
