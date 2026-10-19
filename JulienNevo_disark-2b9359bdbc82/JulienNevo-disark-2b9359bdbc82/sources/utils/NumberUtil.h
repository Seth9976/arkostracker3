#pragma once

#include <array>

#include <juce_core/juce_core.h>

namespace disark
{

/** Utility class about numbers. */
class NumberUtil
{
public:
    /** Prevents instantiation. */
    NumberUtil() = delete;

    /**
     * Converts a number to four hexadecimal digits. If negative, the positive value is used.
     * @param number the number to convert. Only the less significant digits is used.
     * @return four hexadecimal digits, in upper-case.
     */
    static juce::String toHexFourDigits(int number) noexcept;

private:
    static const std::array<juce::String, 16U> digitToHexadecimalString;   // Links a digit to a one-char hexadecimal String.
};

}    // namespace disark
