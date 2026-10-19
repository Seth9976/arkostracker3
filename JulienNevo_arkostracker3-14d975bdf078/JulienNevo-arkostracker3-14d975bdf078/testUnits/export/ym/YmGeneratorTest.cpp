#include "../../catch.hpp"

#include <juce_core/juce_core.h>

#include <BinaryData.h>

#include "../../../source/export/ym/YmExporter.h"
#include "../../../source/export/ym/YmGenerator.h"
#include "../../../source/reader/ym/YmReader.h"
#include "../../../source/song/psg/PsgFrequency.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../helper/SongTestHelper.h"

namespace arkostracker
{

TEST_CASE("YmGenerator, YM6 shouldn't change", "[YmGenerator]")
{
    // Given.
    const auto inputYm = juce::MemoryBlock(BinaryData::ym6InterleavedAganamemnon_ym, BinaryData::ym6InterleavedAganamemnon_ymSize);
    juce::MemoryOutputStream outputStream;

    // When.
    YmGenerator ymGenerator(inputYm, outputStream, PsgFrequency::psgFrequencyCPC);
    const auto success = ymGenerator.convert();

    // Then.
    REQUIRE(success);
    REQUIRE(MemoryBlockUtil::compare(inputYm, outputStream.getMemoryBlock()));
}

TEST_CASE("YmGenerator, YM6 2Mhz convert to 1", "[YmGenerator]")
{
    // Given.
    // IMPORTANT: the glide effects has been removed, else the conversion would fail because the ratio wouldn't be the same.
    const auto agana2Mhz = SongTestHelper::loadSong(BinaryData::At3AganamemnonShortNoPitches2Mhz_aks, BinaryData::At3AganamemnonShortNoPitches2Mhz_aksSize);
    YmExporter encoder2Mhz(agana2Mhz, agana2Mhz->getFirstSubsongId(), 0, false, false);
    const auto& [success2Mhz, inputYm2Mhz] = encoder2Mhz.performTask();
    REQUIRE(success2Mhz);
    REQUIRE((inputYm2Mhz != nullptr));

    const auto agana1Mhz = SongTestHelper::loadSong(BinaryData::At3AganamemnonShortNoPitches1Mhz_aks, BinaryData::At3AganamemnonShortNoPitches1Mhz_aksSize);
    YmExporter encoder1Mhz(agana1Mhz, agana1Mhz->getFirstSubsongId(), 0, false, false);
    const auto& [success1Mhz, expectedYm1Mhz] = encoder1Mhz.performTask();
    REQUIRE(success1Mhz);
    REQUIRE((expectedYm1Mhz != nullptr));

    // When.
    juce::MemoryOutputStream outputStream;
    YmGenerator ymGenerator(inputYm2Mhz->getMemoryBlock(), outputStream, PsgFrequency::psgFrequencyCPC);
    const auto success = ymGenerator.convert();

    const auto outputYm1Mhz = outputStream.getMemoryBlock();

    // Then.
    REQUIRE(success);
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/cpc/tests/outputYm.ym", outputYm1Mhz);   // Useful for testing.

    //REQUIRE(MemoryBlockUtil::compare(expectedYm1Mhz, outputStream.getMemoryBlock(), 1, 0));

    auto misExpectedYm1Mhz = juce::MemoryInputStream(expectedYm1Mhz->getMemoryBlock(), false);
    YmReader ymReaderExpectedYm1Mhz(misExpectedYm1Mhz);
    REQUIRE(ymReaderExpectedYm1Mhz.checkFormat());
    REQUIRE(ymReaderExpectedYm1Mhz.prepare());

    const auto iterationCount = ymReaderExpectedYm1Mhz.getIterationCount();
    auto misOutputYm1Mhz = juce::MemoryInputStream(outputYm1Mhz, false);
    YmReader ymReaderOutputYm1Mhz(misOutputYm1Mhz);
    REQUIRE(ymReaderOutputYm1Mhz.checkFormat());
    REQUIRE(ymReaderOutputYm1Mhz.prepare());

    REQUIRE((iterationCount > 1));
    REQUIRE((iterationCount == ymReaderOutputYm1Mhz.getIterationCount()));

    for (auto iterationIndex = 0; iterationIndex < iterationCount; ++iterationIndex) {
        const auto& [expectedRegs, success1] = ymReaderExpectedYm1Mhz.getRegisters(0, iterationIndex);
        const auto& [outputRegs, success2] = ymReaderOutputYm1Mhz.getRegisters(0, iterationIndex);
        REQUIRE(success1);
        REQUIRE(success2);

        constexpr auto toleranceSoftwarePeriod = 2;
        constexpr auto toleranceHardwarePeriod = 3; // The soft+hard actually makes it harder to test.

        const auto expectedPeriod0 = expectedRegs.getSoftwarePeriod(0);
        const auto expectedPeriod1 = expectedRegs.getSoftwarePeriod(1);
        const auto expectedPeriod2 = expectedRegs.getSoftwarePeriod(2);
        const auto expectedHardwarePeriod = expectedRegs.getHardwarePeriod();
        const auto expectedNoise = expectedRegs.getNoise();
        const auto expectedIsHardwareEnveloperUsed = expectedRegs.isHardwareVolume(0) || expectedRegs.isHardwareVolume(1) || expectedRegs.isHardwareVolume(2);
        const auto outputPeriod0 = outputRegs.getSoftwarePeriod(0);
        const auto outputPeriod1 = outputRegs.getSoftwarePeriod(1);
        const auto outputPeriod2 = outputRegs.getSoftwarePeriod(2);
        const auto outputHardwarePeriod = outputRegs.getHardwarePeriod();
        const auto outputNoise = outputRegs.getNoise();
        const auto outputIsHardwareEnveloperUsed = outputRegs.isHardwareVolume(0) || outputRegs.isHardwareVolume(1) || outputRegs.isHardwareVolume(2);

        if (std::abs(expectedPeriod0 - outputPeriod0) > toleranceSoftwarePeriod) {
            if ((expectedPeriod0 == 1440) && (outputPeriod0 == 1424)) {
                // Ok, because Hard To Soft, more approximation.
            } else {
                FAIL("Period 0 incorrect. Expecting " + juce::String(expectedPeriod0) + " but was " + juce::String(outputPeriod0) + ", frame index " + juce::String(iterationIndex));
            }
        }
        if (std::abs(expectedPeriod1 - outputPeriod1) > toleranceSoftwarePeriod) {
            FAIL("Period 1 incorrect. Expecting " + juce::String(expectedPeriod1) + " but was " + juce::String(outputPeriod1) + ", frame index " + juce::String(iterationIndex));
        }
        if (std::abs(expectedPeriod2 - outputPeriod2) > toleranceSoftwarePeriod) {
            FAIL("Period 2 incorrect. Expecting " + juce::String(expectedPeriod2) + " but was " + juce::String(outputPeriod2) + ", frame index " + juce::String(iterationIndex));
        }

        if (std::abs(expectedHardwarePeriod - outputHardwarePeriod) > toleranceHardwarePeriod) {
            if ((!expectedIsHardwareEnveloperUsed && !outputIsHardwareEnveloperUsed)    // Ignore the non-divided unused data.
                // This is Soft+hard, divided where it shouldn't (but we can't know that from the raw YM).
                || (iterationIndex == 2833)
                || (iterationIndex == 3217)
            ) {
                // Ok.
            } else {
                FAIL("Hardware period incorrect. Expecting " + juce::String(expectedHardwarePeriod) + " but was " + juce::String(outputHardwarePeriod) + ", frame index " + juce::String(iterationIndex));
            }
        }

        if (std::abs(expectedNoise - outputNoise) > toleranceSoftwarePeriod) {
            FAIL("Noise incorrect");
        }

        if (std::abs(expectedRegs.getVolume(0) - outputRegs.getVolume(0)) > 0) {
            FAIL("Volume 0 incorrect");
        }
        if (std::abs(expectedRegs.getVolume(1) - outputRegs.getVolume(1)) > 0) {
            FAIL("Volume 1 incorrect");
        }
        if (std::abs(expectedRegs.getVolume(2) - outputRegs.getVolume(2)) > 0) {
            FAIL("Volume 2 incorrect");
        }

        if (std::abs(expectedRegs.getMixer() - outputRegs.getMixer()) > 0) {
            FAIL("Mixer incorrect");
        }
    }
}

}   // namespace arkostracker
