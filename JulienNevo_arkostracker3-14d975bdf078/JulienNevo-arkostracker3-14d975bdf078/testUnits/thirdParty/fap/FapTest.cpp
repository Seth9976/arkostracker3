#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/utils/FileUtil.h"
#include "../../../source/utils/MemoryBlockUtil.h"

#include "../../thirdParty/fap/FapCrunch.h"

namespace arkostracker
{

class Util
{
public:
    static void work(const char* inputData, const size_t inputDataSize, const char* expectedData, const size_t expectedDataSize)
    {
        // Given.
        const juce::MemoryBlock ymMemoryBlock(inputData, inputDataSize);
        // Creates a temp file with the content.
        const auto inputFile = juce::File::createTempFile("ym");
        FileUtil::saveMemoryBlockToFile(inputFile, ymMemoryBlock);
        const auto tempFolder = juce::File::getSpecialLocation(juce::File::tempDirectory);
        const auto outputFile = juce::File(tempFolder.getFullPathName() + juce::File::getSeparatorChar() + "fapTempAt3.fap");

        // When.
        const std::vector arguments = {
            inputFile.getFullPathName().toStdString(),
            outputFile.getFullPathName().toStdString(),
        };

        // With thanks from https://stackoverflow.com/a/39883532.
        std::vector<char*> argv;
        argv.push_back(nullptr);        // A dummy value for the program name.
        for (const auto& arg : arguments) {
            argv.push_back(const_cast<char*>(arg.data()));              // NOLINT(*-pro-type-const-cast)
        }
        argv.push_back(nullptr);        // End of the list.

        const auto result = fapCrunch(static_cast<int>(argv.size() - 1), argv.data());

        // Then.
        (void)inputFile.deleteFile();

        const auto inputFileStream = std::make_unique<juce::FileInputStream>(outputFile);
        REQUIRE(inputFileStream->openedOk());
        const auto generatedOutputMemoryBlock = MemoryBlockUtil::fromInputStream(*inputFileStream);

        // Cleans the whole before an error can occur.
        (void)outputFile.deleteFile();
        REQUIRE((result == 0));

        const juce::MemoryBlock expectedFapResult(expectedData, expectedDataSize);

        const auto success = MemoryBlockUtil::compare(generatedOutputMemoryBlock, expectedFapResult);

        REQUIRE(success);
    }
};

TEST_CASE("Fap, harmless grenade", "[Fap]")
{
    Util::work(
        BinaryData::FapHarmlessGrenade_ym, BinaryData::FapHarmlessGrenade_ymSize,
        BinaryData::FapHarmlessGrenade_fap, BinaryData::FapHarmlessGrenade_fapSize
    );
}

TEST_CASE("Fap, fractal", "[Fap]")
{
    Util::work(
        BinaryData::FapUltraSydFractal_ym, BinaryData::FapUltraSydFractal_ymSize,
        BinaryData::FapUltraSydFractal_fap, BinaryData::FapUltraSydFractal_fapSize
    );
}

}   // namespace arkostracker
