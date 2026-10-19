#include "CommandLineToolTestHelper.h"

#include <BinaryData.h>

#include "../../source/utils/FileUtil.h"

namespace arkostracker
{

std::pair<juce::String, juce::File> CommandLineToolTestHelper::createTempMusicFile()
{
    const auto inputFile = juce::File::createTempFile("tmp");

    const juce::MemoryBlock inputData(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize);
    const auto generateInputDataSuccess = FileUtil::saveMemoryBlockToFile(inputFile, inputData);
    if (!generateInputDataSuccess) {
        jassert(generateInputDataSuccess);
        return { };
    }

    return { inputFile.getFullPathName(), inputFile };
}

std::pair<juce::String, juce::File> CommandLineToolTestHelper::createTempFile()
{
    const auto file = juce::File::createTempFile("tmp");
    return { file.getFullPathName(), file };
}

void CommandLineToolTestHelper::deleteFile(const juce::File& file)
{
    if (file.existsAsFile()) {
        (void)file.deleteFile();
    }
}

}   // namespace arkostracker
