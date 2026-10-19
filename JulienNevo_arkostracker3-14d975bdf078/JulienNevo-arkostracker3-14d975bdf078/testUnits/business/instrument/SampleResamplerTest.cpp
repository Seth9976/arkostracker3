#include "../../catch.hpp"

#include "../../../source/business/instrument/SampleResampler.h"
#include "../../../source/utils/MemoryBlockUtil.h"

namespace arkostracker
{

TEST_CASE("SampleResampler, no change", "[SampleResampler]")
{
    // Given.
    constexpr auto amplificationRatio = 1.0F;
    constexpr auto sampleFrequencyHz = 8000;
    constexpr auto digidrumNote = PsgValues::digidrumNote;
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );
    const auto inputLoop = Loop(0, 9, true);

    const auto inputSample = std::make_shared<Sample>(inputSampleData);
    SamplePart inputSamplePart(
        inputSample,
        inputLoop,
        amplificationRatio,
        sampleFrequencyHz,
        digidrumNote
    );

    // When.
    const auto newSamplePart = SampleResampler::resample(inputSamplePart);

    // Then.
    REQUIRE(juce::exactlyEqual(newSamplePart.getAmplificationRatio(), amplificationRatio));
    REQUIRE(newSamplePart.getDigidrumNote() == PsgValues::digidrumNote);
    REQUIRE(newSamplePart.getFrequencyHz() == sampleFrequencyHz);
    REQUIRE(newSamplePart.getLoop() == inputLoop);
    REQUIRE(newSamplePart.getSample()->getData() == inputSampleData);
}

TEST_CASE("SampleResampler, double faster", "[SampleResampler]")
{
    // Given.
    constexpr auto amplificationRatio = 1.0F;
    constexpr auto sampleFrequencyHz = 8000;
    constexpr auto inputDigidrumNote = PsgValues::digidrumNote + 12;
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );
    const auto inputLoop = Loop(2, 9, true);

    const auto inputSample = std::make_shared<Sample>(inputSampleData);
    SamplePart inputSamplePart(
        inputSample,
        inputLoop,
        amplificationRatio,
        sampleFrequencyHz,
        inputDigidrumNote
    );

    // When.
    const auto newSamplePart = SampleResampler::resample(inputSamplePart);

    // Then.
    REQUIRE(juce::exactlyEqual(newSamplePart.getAmplificationRatio(), amplificationRatio));
    REQUIRE(newSamplePart.getDigidrumNote() == PsgValues::digidrumNote);
    REQUIRE(newSamplePart.getFrequencyHz() == sampleFrequencyHz);
    REQUIRE(newSamplePart.getLoop() == Loop(1, 4, true));
    REQUIRE(newSamplePart.getSample()->getData() == MemoryBlockUtil::fromVector(
        { 1, 3, 5, 7, 9 }
    ));
}

TEST_CASE("SampleResampler, double faster, odd loop start", "[SampleResampler]")
{
    // Given.
    constexpr auto amplificationRatio = 1.0F;
    constexpr auto sampleFrequencyHz = 8000;
    constexpr auto inputDigidrumNote = PsgValues::digidrumNote + 12;
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );
    const auto inputLoop = Loop(3, 9, true);

    const auto inputSample = std::make_shared<Sample>(inputSampleData);
    SamplePart inputSamplePart(
        inputSample,
        inputLoop,
        amplificationRatio,
        sampleFrequencyHz,
        inputDigidrumNote
    );

    // When.
    const auto newSamplePart = SampleResampler::resample(inputSamplePart);

    // Then.
    REQUIRE(juce::exactlyEqual(newSamplePart.getAmplificationRatio(), amplificationRatio));
    REQUIRE(newSamplePart.getDigidrumNote() == PsgValues::digidrumNote);
    REQUIRE(newSamplePart.getFrequencyHz() == sampleFrequencyHz);
    REQUIRE(newSamplePart.getLoop() == Loop(1, 4, true));
    REQUIRE(newSamplePart.getSample()->getData() == MemoryBlockUtil::fromVector(
        { 1, 3, 5, 7, 9 }
    ));
}

TEST_CASE("SampleResampler, double slower", "[SampleResampler]")
{
    // Given.
    constexpr auto amplificationRatio = 1.0F;
    constexpr auto sampleFrequencyHz = 8000;
    constexpr auto inputDigidrumNote = PsgValues::digidrumNote - 12;
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );
    const auto inputLoop = Loop(3, 9, false);

    const auto inputSample = std::make_shared<Sample>(inputSampleData);
    SamplePart inputSamplePart(
        inputSample,
        inputLoop,
        amplificationRatio,
        sampleFrequencyHz,
        inputDigidrumNote
    );

    // When.
    const auto newSamplePart = SampleResampler::resample(inputSamplePart);

    // Then.
    REQUIRE(juce::exactlyEqual(newSamplePart.getAmplificationRatio(), amplificationRatio));
    REQUIRE(newSamplePart.getDigidrumNote() == PsgValues::digidrumNote);
    REQUIRE(newSamplePart.getFrequencyHz() == sampleFrequencyHz);
    REQUIRE(newSamplePart.getLoop() == Loop(6, 19, false));
    REQUIRE(newSamplePart.getSample()->getData() == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10 }
    ));
}

TEST_CASE("SampleResampler, one semi-tone faster", "[SampleResampler]")
{
    // Given.
    constexpr auto amplificationRatio = 0.5F;
    constexpr auto sampleFrequencyHz = 8000;
    constexpr auto inputDigidrumNote = PsgValues::digidrumNote + 1;
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );
    const auto inputLoop = Loop(3, 19, false);

    const auto inputSample = std::make_shared<Sample>(inputSampleData);
    SamplePart inputSamplePart(
        inputSample,
        inputLoop,
        amplificationRatio,
        sampleFrequencyHz,
        inputDigidrumNote
    );

    // When.
    const auto newSamplePart = SampleResampler::resample(inputSamplePart);

    // Then.
    REQUIRE(juce::exactlyEqual(newSamplePart.getAmplificationRatio(), amplificationRatio));
    REQUIRE(newSamplePart.getDigidrumNote() == PsgValues::digidrumNote);
    REQUIRE(newSamplePart.getFrequencyHz() == sampleFrequencyHz);
    REQUIRE(newSamplePart.getLoop() == Loop(2, 18, false));
    REQUIRE(newSamplePart.getSample()->getData() == MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, half octave faster", "[SampleResampler]")
{
    // Given.
    constexpr auto amplificationRatio = 0.5F;
    constexpr auto sampleFrequencyHz = 8000;
    constexpr auto inputDigidrumNote = PsgValues::digidrumNote + 6;
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );
    const auto inputLoop = Loop(3, 19, false);

    const auto inputSample = std::make_shared<Sample>(inputSampleData);
    SamplePart inputSamplePart(
        inputSample,
        inputLoop,
        amplificationRatio,
        sampleFrequencyHz,
        inputDigidrumNote
    );

    // When.
    const auto newSamplePart = SampleResampler::resample(inputSamplePart);

    // Then.
    REQUIRE(juce::exactlyEqual(newSamplePart.getAmplificationRatio(), amplificationRatio));
    REQUIRE(newSamplePart.getDigidrumNote() == PsgValues::digidrumNote);
    REQUIRE(newSamplePart.getFrequencyHz() == sampleFrequencyHz);
    REQUIRE(newSamplePart.getLoop() == Loop(2, 14, false));
    REQUIRE(newSamplePart.getSample()->getData() == MemoryBlockUtil::fromVector(
        { 1, 2, 3, 5, 6, 8, 9, 10, 12, 13, 15, 16, 17, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, half octave slower", "[SampleResampler]")
{
    // Given.
    constexpr auto amplificationRatio = 0.5F;
    constexpr auto sampleFrequencyHz = 8000;
    constexpr auto inputDigidrumNote = PsgValues::digidrumNote - 6;
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );
    const auto inputLoop = Loop(18, 19, true);

    const auto inputSample = std::make_shared<Sample>(inputSampleData);
    SamplePart inputSamplePart(
        inputSample,
        inputLoop,
        amplificationRatio,
        sampleFrequencyHz,
        inputDigidrumNote
    );

    // When.
    const auto newSamplePart = SampleResampler::resample(inputSamplePart);

    // Then.
    REQUIRE(juce::exactlyEqual(newSamplePart.getAmplificationRatio(), amplificationRatio));
    REQUIRE(newSamplePart.getDigidrumNote() == PsgValues::digidrumNote);
    REQUIRE(newSamplePart.getFrequencyHz() == sampleFrequencyHz);
    REQUIRE(newSamplePart.getLoop() == Loop(25, 28, true));
    REQUIRE(newSamplePart.getSample()->getData() == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 3, 3, 4, 5, 5, 6, 7, 8, 8, 9, 10, 10, 11, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 19, 20, 20 }
    ));
}

// -------------------------------------------------

TEST_CASE("SampleResampler, cents 0", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, 0.0);

    // Then.
    REQUIRE(juce::exactlyEqual(step, 1.0));
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    ));
}

TEST_CASE("SampleResampler, cents 12", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, 12.0);

    // Then.
    REQUIRE(juce::exactlyEqual(step, 2.0));
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 3, 5, 7, 9 }
    ));
}

TEST_CASE("SampleResampler, cents almost 12", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, 11.998);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 2, 4, 6, 8, 10 }
    ));
}

TEST_CASE("SampleResampler, cents 1", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, 1.0);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, cents 1.50", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, 1.5);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, cents 2", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, 2.0);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 20 }
    ));
}

TEST_CASE("SampleResampler, cents -1", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, -1.0);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 17, 18, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, cents -1.20", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, -1.20);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 14, 15, 16, 17, 18, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, cents -1.90", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, -1.90);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 18, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, cents -2", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, -2.0);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 10, 11, 12, 13, 14, 15, 16, 17, 17, 18, 19, 20 }
    ));
}

TEST_CASE("SampleResampler, cents -2,5", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, -2.5);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 11, 12, 13, 13, 14, 15, 16, 17, 18, 19, 20, 20 }
    ));
}

TEST_CASE("SampleResampler, cents -12", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote, -12.0);

    // Then.
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10 }
    ));
}

// =================================================================

TEST_CASE("SampleResampler, cents 6 plus other note 6", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote + 6,
        6.0);

    // Then.
    REQUIRE(juce::exactlyEqual(step, 2.0));
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
        { 1, 3, 5, 7, 9 }
    ));
}

TEST_CASE("SampleResampler, cents 6 plus other note -6", "[SampleResampler]")
{
    // Given.
    const auto inputSampleData = MemoryBlockUtil::fromVector(
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    );

    // When.
    const auto& [resampledData, step] = SampleResampler::resample(inputSampleData, inputSampleData.getSize(), PsgValues::digidrumNote - 6,
        6.0);

    // Then.
    REQUIRE(juce::exactlyEqual(step, 1.0));
    REQUIRE(resampledData == MemoryBlockUtil::fromVector(
{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    ));
}

} // namespace arkostracker
