#include "SymbolImporter.h"

#include "../utils/StreamUtil.h"
#include "../utils/StringUtil.h"

namespace disark
{

SymbolImporter::SymbolImporter(juce::InputStream& pInputStream) noexcept :
    inputStream(pInputStream)
{
}

std::pair<std::vector<LabelAndAddress>, juce::String> SymbolImporter::import(const int labelIndex, const int addressIndex) const noexcept
{
    std::vector<LabelAndAddress> labelsAndAddresses;

    // Sanity check of the indexes.
    if ((labelIndex == addressIndex) || (labelIndex < 0) || (addressIndex < 0)) {
        return { labelsAndAddresses, "The label and address positions are not valid (must be different and positive)." };
    }

    // Reads all the Strings from the Input Stream, and browses them.
    juce::String error;
    const auto strings = StreamUtil::extractFrom(inputStream);
    auto linePosition = 1;
    for (const auto& readString : strings) {
        // Empty Strings are ignored.
        auto string = readString.trim();
        if (string.isEmpty()) {
            continue;
        }

        // Parses the String.
        auto labelAndAddressOrError = parseString(string, labelIndex, addressIndex, linePosition);
        // Error?
        error = labelAndAddressOrError.second;
        if (error.isNotEmpty()) {
            break;
        }

        // No error. Stores the label and address.
        labelsAndAddresses.emplace_back(labelAndAddressOrError.first);

        ++linePosition;
    }

    // No error.
    return { labelsAndAddresses, error };
}

std::pair<LabelAndAddress, juce::String> SymbolImporter::parseString(const juce::String& string, const int labelIndex, const int addressIndex, const int linePosition) noexcept
{
    const auto splits = StringUtil::split(string, " ");
    const auto maxIndex = (labelIndex > addressIndex) ? labelIndex : addressIndex;

    // Are the line big enough to contain the label or address?
    if (maxIndex >= static_cast<int>(splits.size())) {
        return { LabelAndAddress::buildError(), translate("Line is not big enough to hold the label and address, in line " + juce::String(linePosition) + ".") };
    }
    // Removes the possible "." at the start and ":" at the end... Actually, everywhere! Simpler.
    const auto label = splits.at(static_cast<size_t>(labelIndex)).removeCharacters(".:");

    // Can the address be well parsed?
    const auto& addressToParse = splits.at(static_cast<size_t>(addressIndex));
    auto address = StringUtil::stringNumberToNumber(addressToParse);
    if (address < 0) {
        return { LabelAndAddress::buildError(), juce::translate("Address could not be parsed: ") + addressToParse +
            juce::translate(". It can be decimal, or starts with #, &, $ or 0x, for hexadecimal.") };
    }

    // Success.
    return { { label, address}, juce::String() };
}

}    // namespace disark
