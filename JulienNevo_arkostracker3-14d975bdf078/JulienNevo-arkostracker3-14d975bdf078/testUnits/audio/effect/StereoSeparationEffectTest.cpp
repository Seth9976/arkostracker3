#include "../../catch.hpp"

#include "../../../source/audio/effect/StereoSeparationEffect.h"

namespace arkostracker
{

TEST_CASE("StereoSeparationEffect, full separation, left and right to 1", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(1.0);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 1.0F);
    buffer.setSample(1, 0, 1.0F);

    buffer.setSample(0, 1, 0.5F);
    buffer.setSample(1, 1, 0.5F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 1.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 1.0F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.5F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.5F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}

TEST_CASE("StereoSeparationEffect, full separation, left to 1 and right to 0", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(1.0);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 1.0F);
    buffer.setSample(1, 0, 0.0F);

    buffer.setSample(0, 1, 0.5F);
    buffer.setSample(1, 1, 0.0F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 1.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 0.0F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.5F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.0F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}

TEST_CASE("StereoSeparationEffect, full separation, left to 0 and right to 1", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(1.0);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 0.0F);
    buffer.setSample(1, 0, 1.0F);

    buffer.setSample(0, 1, 0.0F);
    buffer.setSample(1, 1, 0.5F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 1.0F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.5F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}


// ==================================================================

TEST_CASE("StereoSeparationEffect, mono, left and right to 1", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(0.0);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 1.0F);
    buffer.setSample(1, 0, 1.0F);

    buffer.setSample(0, 1, 0.5F);
    buffer.setSample(1, 1, 0.5F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 1.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 1.0F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.5F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.5F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}

TEST_CASE("StereoSeparationEffect, mono, left to 1 and right to 0", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(0.0);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 1.0F);
    buffer.setSample(1, 0, 0.0F);

    buffer.setSample(0, 1, 0.5F);
    buffer.setSample(1, 1, 0.0F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 0.5F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 0.5F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.25F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.25F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}

TEST_CASE("StereoSeparationEffect, mono, left to 0 and right to 1", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(0.0);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 0.0F);
    buffer.setSample(1, 0, 1.0F);

    buffer.setSample(0, 1, 0.0F);
    buffer.setSample(1, 1, 0.5F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 0.5F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 0.5F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.25F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.25F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}


// ==================================================================

TEST_CASE("StereoSeparationEffect, 0.5 separation, left and right to 1", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(0.5);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 1.0F);
    buffer.setSample(1, 0, 1.0F);

    buffer.setSample(0, 1, 0.5F);
    buffer.setSample(1, 1, 0.5F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 1.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 1.0F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.5F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.5F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}

TEST_CASE("StereoSeparationEffect, 0.5 separation, left to 1 and right to 0", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(0.5);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 1.0F);
    buffer.setSample(1, 0, 0.0F);

    buffer.setSample(0, 1, 0.5F);
    buffer.setSample(1, 1, 0.0F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 0.75F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 0.25F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.375F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.125F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}

TEST_CASE("StereoSeparationEffect, 0.5 separation, left to 0 and right to 1", "[StereoSeparationEffect]")
{
    // Given.
    auto effect = std::make_unique<StereoSeparationEffect>();
    effect->setEnabled(true);
    effect->setSeparation(0.5);

    juce::AudioBuffer<float> buffer(2, 3);
    const juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);

    buffer.setSample(0, 0, 0.0F);
    buffer.setSample(1, 0, 1.0F);

    buffer.setSample(0, 1, 0.0F);
    buffer.setSample(1, 1, 0.5F);

    buffer.setSample(0, 2, 0.0F);
    buffer.setSample(1, 2, 0.0F);

    // When.
    effect->BaseEffect::processBuffer(audioSourceChannelInfo);

    // Then.
    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 0), 0.25F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 0), 0.75F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 1), 0.125F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 1), 0.375F));

    REQUIRE(juce::exactlyEqual(buffer.getSample(0, 2), 0.0F));
    REQUIRE(juce::exactlyEqual(buffer.getSample(1, 2), 0.0F));
}

}   // namespace arkostracker
