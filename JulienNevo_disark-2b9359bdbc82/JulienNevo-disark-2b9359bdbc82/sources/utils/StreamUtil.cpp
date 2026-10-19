#include "StreamUtil.h"

namespace disark
{

std::vector<juce::String> StreamUtil::extractFrom(juce::InputStream& inputStream) noexcept
{
    std::vector<juce::String> strings;

    // Reads the Strings, as much as we can.
    while (!inputStream.isExhausted()) {
        const auto readString = inputStream.readNextLine();
        strings.emplace_back(readString);
    }

    return strings;
}

}    // namespace disark
