#pragma once

#include <juce_core/juce_core.h>

namespace disark
{

/** Utility class for Streams. */
class StreamUtil
{
public:
    /** Prevents instantiation. */
    StreamUtil() = delete;

    /**
     * Extracts Strings from the given InputStream. Return carriage are not present in the extracted Strings.
     * @param inputStream the Input Stream to read.
     * @return the Strings.
     */
    static std::vector<juce::String> extractFrom(juce::InputStream& inputStream) noexcept;
};

}    // namespace disark
