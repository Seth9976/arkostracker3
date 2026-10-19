#include "StringUtil.h"

namespace disark
{

const juce::String StringUtil::hexAddressEditorRestrictionString = "0123456789abcdefABCDEF"; // NOLINT(cert-err58-cpp, *-statically-constructed-objects)
const juce::String StringUtil::integerNumbers = "0123456789";                                // NOLINT(cert-err58-cpp, *-statically-constructed-objects)
const juce::String StringUtil::integerNumbersSigned = "0123456789-";                         // NOLINT(cert-err58-cpp, *-statically-constructed-objects)

int StringUtil::stringNumberToNumber(const juce::String& string) noexcept
{
    // Empty string? This is an error.
    if (string.isEmpty()) {
        return -1;
    }

    auto start = 0;
    auto hexadecimal = false;

    // Detects the hexadecimal symbol, and skips it if found.
    for (const juce::String hexSymbol : { "&", "#", "$", "0x", "0X" }) {
        if (string.startsWith(hexSymbol)) {
            start = hexSymbol.length();
            hexadecimal = true;
            break;
        }
    }

    // Still some chars left?
    if (start >= string.length()) {
        return -1;
    }

    // Extracts the number.
    if (hexadecimal) {
        // It must only contain hexadecimal values (JUCE ignores the rest... Error prone).
        const auto substring = string.substring(start);     // Removes the hex symbol.

        const juce::StringRef stringRef(hexAddressEditorRestrictionString);
        return substring.containsOnly(stringRef) ? substring.getHexValue32() : -1;
    }

    // It must only contain numbers.
    const juce::StringRef stringRef(integerNumbers);
    return string.containsOnly(stringRef) ? string.getIntValue() : -1;
}

int StringUtil::stringToInt(const juce::String& string, bool& success) noexcept
{
    success = false;

    // Not empty?
    const auto newString = string.trim();
    if (newString.isEmpty()) {
        return 0;
    }

    if (newString.containsOnly(integerNumbersSigned)) {
        success = true;
        return string.getIntValue();
    }

    // Some chars are not valid.
    return 0;
}

std::vector<juce::String> StringUtil::split(const juce::String& input, const juce::String& separator) noexcept
{
    // The separator is empty? If yes, returns the input.
    if (separator.isEmpty()) {
        return { input };
    }

    std::vector<juce::String> results;

    const auto size = input.length();

    auto startIndex = 0;

    // Searches for the next separator in the input String.
    auto continueBrowsing = true;
    while (continueBrowsing) {
        const auto separatorIndex = input.indexOf(startIndex, separator);
        if (separatorIndex >= 0) {
            // A separator has been found. The previous substring is a String to extract.
            auto oneSplit = input.substring(startIndex, separatorIndex);
            results.push_back(oneSplit);

            // Moves past the separator and continues.
            startIndex = separatorIndex + separator.length();
        } else {
            continueBrowsing = false;
        }
    }

    // When all is done, is there a split not included?
    if (startIndex < size) {
        const auto oneSplit = input.substring(startIndex, size);
        results.push_back(oneSplit);
    }

    return results;
}

}    // namespace disark
