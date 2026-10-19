#include "MemoryBlockUtil.h"

namespace disark
{

std::vector<juce::String> MemoryBlockUtil::extractStrings(const juce::MemoryBlock& memoryBlock) noexcept
{
    std::vector<juce::String> readLines;

    // Reads and stores the lines as long as we can read the MemoryBlock.
    juce::MemoryInputStream memoryInputStream(memoryBlock, false);
    while (!memoryInputStream.isExhausted()) {
        const auto readString = memoryInputStream.readNextLine();
        readLines.push_back(readString);
    }

    return readLines;
}

juce::MemoryBlock MemoryBlockUtil::fromVector(const std::vector<unsigned char>& inputChars) noexcept
{
    juce::MemoryBlock result;

    unsigned char array[1];

    // Not optimized at all, who cares?
    for (auto c : inputChars) {
        array[0] = c;
        result.append(&array, 1);
    }

    return result;
}

juce::MemoryBlock MemoryBlockUtil::fromStrings(const std::vector<juce::String>& strings) noexcept
{
    juce::MemoryBlock memoryBlock;

    for (const auto& string : strings) {
        auto stringWithRc = string + juce::NewLine::getDefault();
        memoryBlock.append(stringWithRc.toUTF8(), static_cast<size_t>(stringWithRc.length()));
    }

    return memoryBlock;
}

juce::MemoryBlock MemoryBlockUtil::fromString(const juce::String& string) noexcept
{
    return { string.toUTF8(), static_cast<size_t>(string.length()) };
}

std::vector<unsigned char> MemoryBlockUtil::toVector(const juce::MemoryBlock& memoryBlock) noexcept
{
    const auto size = memoryBlock.getSize();

    std::vector<unsigned char> result;
    result.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        result.push_back(static_cast<unsigned char>(memoryBlock[i]));
    }

    return result;
}

bool MemoryBlockUtil::compare(const juce::MemoryBlock& memoryBlock1, const juce::MemoryBlock& memoryBlock2) noexcept
{
    const int size = (int)memoryBlock1.getSize();
    if (size != (int)memoryBlock2.getSize()) {
        jassertfalse;       // Useful for debugging.
        return false;
    }

    // Compares each byte.
    for (auto i = 0; i < size; ++i) {
        const auto val1 = memoryBlock1[i];
        const auto val2 = memoryBlock2[i];
        if (val1 != val2) {
            jassertfalse;       // Useful for debugging.
            return false;
        }
    }

    return true;
}

}    // namespace disark
