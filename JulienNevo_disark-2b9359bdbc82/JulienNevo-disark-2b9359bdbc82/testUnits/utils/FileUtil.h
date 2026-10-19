#pragma once

#include <memory>

#include <juce_core/juce_core.h>

namespace disark
{

/**
 * Utility class for Files.
 */
class FileUtil
{
public:
    /** No instantiation possible. */
    FileUtil() = delete;

    /**
     * Saves the content of a MemoryBlock to a file.
     * @param fileToCreate the file. If existing, it is overwritten.
     * @param memoryBlockToSave the MemoryBlock to save.
     */
    static void saveMemoryBlockToFile(const juce::String& fileToCreate, const juce::MemoryBlock& memoryBlockToSave) noexcept;
};

}    // namespace disark
