#include "../../catch.hpp"

#include "../../../source/export/samples/SampleEncoder.h"
#include "../../../source/export/samples/SampleEncoderFlags.h"
#include "../../../source/utils/MemoryBlockUtil.h"

namespace arkostracker
{

class TestTool
{

public:
    /**
     * Creates a sample with a unique value.
     * @param length how many samples in the sample.
     * @param value the value to encode.
     * @return the sample.
     */
    static juce::MemoryBlock createSample(const int length, const unsigned char value)
    {
        juce::MemoryBlock memoryBlock(static_cast<size_t>(length), false);
        memoryBlock.fillWith(value);

        return memoryBlock;
    }

    static void checkVector(const std::vector<unsigned char>& samples, const int startIndex, const int lastIndex, const int value)
    {
        for (auto i = startIndex; i <= lastIndex; ++i) {
            REQUIRE(samples.at((size_t)i) == value);
        }
    }
};

TEST_CASE("SampleEncoder, 8 bits", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 255);
}

TEST_CASE("SampleEncoder, 4 bits", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 16, 0, 0, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 15);
}

TEST_CASE("SampleEncoder, 4 bits, multiplicator limit", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 16, 0, 0, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 200);

    const auto result = sampleEncoder.convert(samples, 2.0F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 15);
}

TEST_CASE("SampleEncoder, 8 bits, multiplicator 0.5, upper bound", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 255);

    const auto result = sampleEncoder.convert(samples, 0.5F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 191);
}

TEST_CASE("SampleEncoder, 8 bits, multiplicator 0.5, lower bound", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 0);

    const auto result = sampleEncoder.convert(samples, 0.5F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 64);
}

TEST_CASE("SampleEncoder, 8 bits, multiplicator 2, upper bound", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 132);

    const auto result = sampleEncoder.convert(samples, 2.0F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 136);
}

TEST_CASE("SampleEncoder, 8 bits, multiplicator 2, lower bound", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 123);

    const auto result = sampleEncoder.convert(samples, 2.0F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 118);
}

TEST_CASE("SampleEncoder, 4 bits, fade out inside sample to middle", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 16, 0, 0, 10,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);

    const auto samples = TestTool::createSample(10, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 9);

    REQUIRE(result != nullptr);
    const std::vector<unsigned char> expected = { 15, 14, 13, 12, 11, 11, 10, 9, 8, 8 };
    REQUIRE(*result == expected);
}

TEST_CASE("SampleEncoder, 4 bits, fade out inside sample to middle with offset", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 16, 128, 0, 10,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);

    const auto samples = TestTool::createSample(10, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 9);

    REQUIRE(result != nullptr);
    const std::vector<unsigned char> expected = { 128 + 15, 128 + 14, 128 + 13, 128 + 12, 128 + 11, 128 + 11, 128 + 10, 128 + 9, 128 + 8, 128 + 8 };
    REQUIRE(*result == expected);
}

TEST_CASE("SampleEncoder, 4 bits, fade out inside sample to lowest", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 16, 0, 0, 10,
        true, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);

    const auto samples = TestTool::createSample(10, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 9);

    REQUIRE(result != nullptr);
    const std::vector<unsigned char> expected = { 15, 13, 11, 9, 8, 6, 4, 3, 1, 0 };
    REQUIRE(*result == expected);
}

TEST_CASE("SampleEncoder, 4 bits, fade out inside sample to lowest with offset", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 16, 128, 0, 10,
        true, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);

    const auto samples = TestTool::createSample(10, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 9);

    REQUIRE(result != nullptr);
    const std::vector<unsigned char> expected = { 128 + 15, 128 + 13, 128 + 11, 128 + 9, 128 + 8, 128 + 6, 128 + 4, 128 + 3, 128 + 1, 128 + 0 };
    REQUIRE(*result == expected);
}

TEST_CASE("SampleEncoder, padding", "[SampleEncoder]")
{
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 200, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 300);
    TestTool::checkVector(*result, 0, 99, 255);
    TestTool::checkVector(*result, 100, 299, 128);
}

TEST_CASE("SampleEncoder, padding for loop", "[SampleEncoder]")
{
    constexpr auto sampleSize = 100;
    constexpr auto paddingLength = 10;
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, paddingLength, 0,
        false, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    auto samples = TestTool::createSample(sampleSize, 255);
    // Changes the first bytes, so that we can check if the padding is correctly done.
    for (auto i = 0; i < paddingLength; ++i) {
        samples[i] = static_cast<char>(i * 10);
    }

    const auto result = sampleEncoder.convert(samples, 1.0F, true, 0, sampleSize - 1); // Looping!

    // The padding is present, made of the beginning of the sample, because the sample is looping.
    REQUIRE(result != nullptr);
    REQUIRE(result->size() == (sampleSize + paddingLength));
    TestTool::checkVector(*result, paddingLength, sampleSize - 1, 255);       // Skips the first bytes, they are different.
    // Checks the padding.
    for (auto i = 0; i < paddingLength; ++i) {
        REQUIRE(result->at(static_cast<size_t>(i + sampleSize)) == static_cast<unsigned char>(i * 10));
    }
}

TEST_CASE("SampleEncoder, padding for loop, useless data", "[SampleEncoder]")
{
    // 8 bit samples.
    constexpr auto sampleSize = 100;
    constexpr auto paddingLength = 10;
    constexpr auto loopIndex = 20;
    constexpr auto endIndex = 40;
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, paddingLength, 0,
        false, false);    // The user asks to keep all the data... We don't care!
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    auto samples = TestTool::createSample(sampleSize, 255);
    // Changes the first bytes of the loop, so that we can check if the padding is correctly done.
    for (auto i = loopIndex; i < (loopIndex + paddingLength); ++i) {
        samples[i] = static_cast<char>(i);
    }

    const auto result = sampleEncoder.convert(samples, 1.0f, true, loopIndex, endIndex);       // Looping!

    // The padding is present, made of the beginning of the looping section.
    REQUIRE(result != nullptr);
    REQUIRE(result->size() == (endIndex + 1 + paddingLength));           // The useless part is removed.
    TestTool::checkVector(*result, 0, loopIndex - 1, 255);                     // Checks before the looping section.
    // Checks the padding.
    auto val = loopIndex;
    for (auto i = (endIndex + 1); i < (endIndex + 1 + paddingLength); ++i) {
        REQUIRE(result->at(static_cast<size_t>(i)) == static_cast<unsigned char>(val));
        ++val;
    }
}

TEST_CASE("SampleEncoder, padding to lowest value", "[SampleEncoder]")
{
    // 8 bit samples.
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 200,
        0, true, false);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 255);

    const auto result = sampleEncoder.convert(samples, 1.0f, false, 0, 99);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == (200 + 100));
    TestTool::checkVector(*result, 0, 99, 255);
    TestTool::checkVector(*result, 100, 299, 0);      // Padding to lowest value.
}

TEST_CASE("SampleEncoder, end index", "[SampleEncoder]")
{
    // 8 bit samples.
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0,
        0, false, true);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(100, 255);

    // Only the 0-49 will be encoded.
    const auto result = sampleEncoder.convert(samples, 1.0F, false, 0, 49);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 50);
    TestTool::checkVector(*result, 0, 49, 255);
}

TEST_CASE("SampleEncoder, end index for looping", "[SampleEncoder]")
{
    // 8 bit samples, there is no padding.
    constexpr auto size = 100;
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0,
        0, false, true);
    const SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(size, 255);

    const auto result = sampleEncoder.convert(samples, 1.0F, true, 0, size - 1);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == 100);
    TestTool::checkVector(*result, 0, 99, 255);
}

TEST_CASE("SampleEncoder, 8 bits, fade out to zero", "[SampleEncoder]")
{
    // 8 bit samples with a decay.
    constexpr auto size = 256;
    constexpr auto fadeOutLength = 55;
    SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0, fadeOutLength, true, false);
    SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(size, 255);

    auto result = sampleEncoder.convert(samples, 1.0F, false, 0, size - 1);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == size);
    TestTool::checkVector(*result, 0, 199, 255);
    // Checks the fade-out.
    auto previousValue = 255;
    for (auto i = size - fadeOutLength; i < size; ++i) {
        const auto value = result->at(static_cast<size_t>(i));
        REQUIRE(value < previousValue);

        previousValue = value;
    }
    REQUIRE(result->at(size - 1) == 0);
}

TEST_CASE("SampleEncoder, 8 bits, fade out to middle", "[SampleEncoder]")
{
    // 8 bit samples with a decay.
    constexpr auto size = 256;
    constexpr auto fadeOutLength = 55;
    const SampleEncoderFlags sampleEncoderFlags(true, 256, 0, 0, fadeOutLength,
        false, false);
    SampleEncoder sampleEncoder(sampleEncoderFlags);
    const auto samples = TestTool::createSample(size, 255);

    auto result = sampleEncoder.convert(samples, 1.0F, false, 0, size - 1);

    REQUIRE(result != nullptr);
    REQUIRE(result->size() == size);
    TestTool::checkVector(*result, 0, 199, 255);
    // Checks the fade-out.
    auto previousValue = 255;
    for (auto i = size - fadeOutLength; i < size; ++i) {
        const int value = result->at(static_cast<size_t>(i));
        REQUIRE(value < previousValue);

        previousValue = value;
    }
    REQUIRE(result->at(size - 1) == 128);
}

}   // namespace arkostracker
