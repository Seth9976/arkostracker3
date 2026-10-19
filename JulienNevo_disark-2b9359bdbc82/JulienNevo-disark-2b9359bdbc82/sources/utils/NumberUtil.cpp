#include "NumberUtil.h"

namespace disark
{

const std::array<juce::String, 16U> NumberUtil::digitToHexadecimalString = { // NOLINT(cert-err58-cpp, *-statically-constructed-objects)
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F"
};


juce::String NumberUtil::toHexFourDigits(const int originalNumber) noexcept
{
    const auto number = (originalNumber < 0) ? static_cast<unsigned int>(-originalNumber) : static_cast<const unsigned int>(originalNumber);

    const auto firstDigit = number & 15U;
    const auto secondDigit = (number >> 4U) & 15U;
    const auto thirdDigit = (number >> 8U) & 15U;
    const auto fourthDigit = (number >> 12U) & 15U;

    auto str(digitToHexadecimalString[static_cast<size_t>(fourthDigit)]);
    str.append(digitToHexadecimalString[static_cast<size_t>(thirdDigit)], 1U);
    str.append(digitToHexadecimalString[static_cast<size_t>(secondDigit)], 1U);
    str.append(digitToHexadecimalString[static_cast<size_t>(firstDigit)], 1U);
    return str;
}

}    // namespace disark
