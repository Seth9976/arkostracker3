#pragma once

#include <juce_core/juce_core.h>

namespace arkostracker
{

class CommandLineToolTestHelper
{
public:
    static std::pair<juce::String, juce::File> createTempMusicFile();
    static std::pair<juce::String, juce::File> createTempFile();

    static void deleteFile(const juce::File& file);
};

}   // namespace arkostracker
