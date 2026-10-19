#pragma once

#include <juce_core/juce_core.h>

namespace disark
{

/** Constants for the command line. */
class CommandLineConstants
{
public:
    static const juce::String stringShortOptionTag;                                   // The "-" meaning "short option".
    static const juce::String stringLongOptionTag;                                    // The "--" meaning "long option".
};

}    // namespace disark
