#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/builder/TrailingEffectContext.h"

namespace arkostracker 
{

TEST_CASE("declareEffect, none and no context", "[TrailingEffectContext]")
{
    TrailingEffectContext context;

    // Given/when.
    const auto resultCellEffect = context.declareEffect(TrailingEffect::noEffect, 0);

    // Then.
    REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
    REQUIRE(resultCellEffect.second == 0);
}

TEST_CASE("declareEffect, no context, pitch, then stop it, then pitch again", "[TrailingEffectContext]")
{
    TrailingEffectContext context;

    // Pitch up.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 50);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 50);
    }

    // Pitch up again. Same value, so not encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 50);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Pitch up again with another value, so encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 80);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 80);
    }

    // No effect. This stops the pitch.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::noEffect, 0);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Pitch up again with same value, but as it was stopped, so encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 80);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 80);
    }

    // A note. This invalidates the pitch.
    context.declareNote();

    // Pitch again, same value, but was invalidated, so encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 80);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 80);
    }
}

TEST_CASE("declareEffect, pitch up then down, must be encoded even if same value", "[TrailingEffectContext]")
{
    TrailingEffectContext context;

    // Pitch up.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 50);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 50);
    }

    // Pitch up again. Same value, so not encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 50);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Pitch down. Same value, but different effect, so encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchDown, 50);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchDown);
        REQUIRE(resultCellEffect.second == 50);
    }

    // Pitch down. Same value, so not encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchDown, 50);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Pitch up again. Same value, but old effect, so encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::pitchUp, 50);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 50);
    }

    // No effect. This stops the pitch.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::noEffect, 0);
        REQUIRE(resultCellEffect.first == TrailingEffect::pitchUp);
        REQUIRE(resultCellEffect.second == 0);
    }
}

TEST_CASE("declareEffect, no context, volume several times", "[TrailingEffectContext]")
{
    TrailingEffectContext context;

    // No effect.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::noEffect, 0);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Volume.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 15);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 15);
    }
    // Same volume. Optimization, nothing is encoded.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 15);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Volume 14.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 14);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 14);
    }
    // Volume 1.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 1);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 1);
    }
    // Note.
    context.declareNote();

    // Volume 1, no change so optimized.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 1);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }
    // Volume 14.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 14);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 14);
    }
}

TEST_CASE("declareEffect, reset", "[TrailingEffectContext]")
{
    TrailingEffectContext context;

    // No effect.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::noEffect, 0);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Volume.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 10);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 10);
    }

    // Reset.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::reset, 0);
        REQUIRE(resultCellEffect.first == TrailingEffect::reset);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Same volume. Encoded because Reset before.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 10);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 10);
    }
}

TEST_CASE("declareEffect, same volume, optimize", "[TrailingEffectContext]")
{
    TrailingEffectContext context;

    // Volume.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 10);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 10);
    }

    // Same volume, optimized.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 10);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Same volume, new volume.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 15);
        REQUIRE(resultCellEffect.first == TrailingEffect::volume);
        REQUIRE(resultCellEffect.second == 15);
    }

    // Same volume, optimized.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::volume, 15);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }
}

TEST_CASE("declareEffect, same arpeggio table, optimize", "[TrailingEffectContext]")
{
    TrailingEffectContext context;

    // Arpeggio table.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::arpeggioTable, 1);
        REQUIRE(resultCellEffect.first == TrailingEffect::arpeggioTable);
        REQUIRE(resultCellEffect.second == 1);
    }

    // Same value, optimized.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::arpeggioTable, 1);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }

    // Same volume, new volume.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::arpeggioTable, 5);
        REQUIRE(resultCellEffect.first == TrailingEffect::arpeggioTable);
        REQUIRE(resultCellEffect.second == 5);
    }

    // Same volume, optimized.
    {
        const auto resultCellEffect = context.declareEffect(TrailingEffect::arpeggioTable, 5);
        REQUIRE(resultCellEffect.first == TrailingEffect::noEffect);
        REQUIRE(resultCellEffect.second == 0);
    }
}


}   // namespace arkostracker

