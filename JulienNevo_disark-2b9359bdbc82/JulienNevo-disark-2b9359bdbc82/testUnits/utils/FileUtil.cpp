#include "FileUtil.h"

namespace disark
{

void FileUtil::saveMemoryBlockToFile(const juce::String& fileToCreate, const juce::MemoryBlock& memoryBlockToSave) noexcept
{
    juce::File file(fileToCreate);
    (void)file.deleteFile();

    juce::FileOutputStream outputStream(file);
    outputStream.write(memoryBlockToSave.getData(), memoryBlockToSave.getSize());
}

}    // namespace disark
