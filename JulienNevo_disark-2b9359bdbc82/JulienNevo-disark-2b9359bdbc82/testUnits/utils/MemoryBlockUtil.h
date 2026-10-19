#pragma once

#include <juce_core/juce_core.h>

namespace disark
{

/** Utility class to extract easily data from a MemoryBlock. */
class MemoryBlockUtil
{
public:
    /** Prevents instantiation. */
    MemoryBlockUtil() = delete;

    /**
     * Extracts Strings from the given MemoryBlock. The return carriages are not added to the read lines.
     * @param memoryBlock the data to read.
     * @return the lines.
     */
    static std::vector<juce::String> extractStrings(const juce::MemoryBlock& memoryBlock) noexcept;

    /**
     * Generates a MemoryBlock from a vector of chars. Not optimized, only for test units.
     * @param inputChars the vector to read.
     * @return the generated MemoryBlock.
     */
    static juce::MemoryBlock fromVector(const std::vector<unsigned char>& inputChars) noexcept;

    /**
     * Creates a MemoryBlock from the given Strings. Return carriages don't need to be added.
     * @param string the Strings.
     * @return the MemoryBlock.
     */
    static juce::MemoryBlock fromStrings(const std::vector<juce::String>& strings) noexcept;

    /**
     * Creates a MemoryBlock from the given String. No return carriage is added.
     * @param string the String.
     * @return the MemoryBlock.
     */
    static juce::MemoryBlock fromString(const juce::String& string) noexcept;

    /**
     * Extracts a list of unsigned char from the MemoryBlock. This is only useful for debugging or test units.
     * @param memoryBlock the MemoryBlock to convert.
     * @return the vector.
     */
    static std::vector<unsigned char> toVector(const juce::MemoryBlock& memoryBlock) noexcept;

    /**
     * Compares the two given MemoryBlocks. This is useful on debug to know exactly on which index the
     * MemoryBlocks differs, else one should simply use the equal method of the MemoryBlocks.
     * @param memoryBlock1 the first MemoryBlock.
     * @param memoryBlock2 the second MemoryBlock.
     * @return true if they are equal.
     */
    static bool compare(const juce::MemoryBlock& memoryBlock1, const juce::MemoryBlock& memoryBlock2) noexcept;
};

}    // namespace disark
