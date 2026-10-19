// This file is only useful to declare this once.
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

int main(int argc, char* argv[])                // NOLINT(*-avoid-c-arrays,clion-misra-cpp2008-3-1-3)
{
    // We start the message loop to prevent some assertions from JUCE.
    // See forum.juce.com/t/using-catch2-but-need-a-messageloop/41380
    const auto gui = juce::ScopedJuceInitialiser_GUI { };
    return Catch::Session().run(argc, argv);
}
