#pragma once

#include <juce_core/juce_core.h>

namespace disark
{

/** Utility class for Strings. */
class StringUtil
{
public:

    /**
     * Tries to convert a String (maybe hex) which contain a positive number, to a number
     * @param string the String. May start with &, # or 0x. But may be decimal.
     * @return the result, or -1 if failed.
     */
    static int stringNumberToNumber(const juce::String& string) noexcept;

    /**
     * Converts a String to an integer.
     * @param string the String to parse.
     * @param success filled with true if success, false if failure.
     */
    static int stringToInt(const juce::String& string, bool& success) noexcept;

    /** Splits the given String into several ones, when the given separator is found. */
    static std::vector<juce::String> split(const juce::String& input, const juce::String& separator) noexcept;

private:
    static const juce::String hexAddressEditorRestrictionString;          // The String of the allowed characters in the Hex Address editor.
    static const juce::String integerNumbers;                             // Integer number restriction.
    static const juce::String integerNumbersSigned;                       // Integer number restriction, with the minus sign.
};

}    // namespace disark
