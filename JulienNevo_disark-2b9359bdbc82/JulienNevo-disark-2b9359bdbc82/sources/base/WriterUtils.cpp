#include "WriterUtils.h"

#include "ExportConfiguration.h"

namespace disark
{

void WriterUtils::writeString(juce::OutputStream& outputStream, const juce::String& text) noexcept
{
    outputStream.writeText(text, false, false, nullptr);
    outputStream.writeText(outputStream.getNewLineString(), false, false, nullptr);
}

juce::String WriterUtils::getHexStringFromNumber(const ExportConfiguration& configuration, int number) noexcept
{
    jassert(number >= 0);
    return getStringForNumber(configuration, number, configuration.isEncode16BitNumberAsHex(), false);
}

juce::String WriterUtils::getLabelForDeclaration(const ExportConfiguration& configuration, const juce::String& label, bool isExternal, bool skipPostFix) noexcept
{
    if (isExternal) {
        return configuration.getExternalLabelPrefix() + label + (skipPostFix ? "" : configuration.getExternalLabelPostfix());
    }
    return configuration.getLabelPrefix() + label + (skipPostFix ? "" : configuration.getLabelPostfix());
}

juce::String WriterUtils::getLabelDeclarationWithoutValue(const ExportConfiguration& configuration, const juce::String& labelDeclaration) noexcept
{
    return labelDeclaration + " " + configuration.getEquMnemonic() + configuration.getMnemonicPostfix();
}

juce::String WriterUtils::getStringForDecimalNumber(const ExportConfiguration& configuration, int number, bool addPlusSymbolIfPositive) noexcept
{
    return getStringForNumber(configuration, number, false, addPlusSymbolIfPositive);
}

juce::String WriterUtils::getStringForHexadecimalNumber(const ExportConfiguration& configuration, int number, bool addPlusSymbolIfPositive) noexcept
{
    return getStringForNumber(configuration, number, true, addPlusSymbolIfPositive);
}

juce::String WriterUtils::getStringForNumber(const ExportConfiguration& configuration, int number, bool showAsHex, bool addPlusSymbolIfPositive) noexcept
{
    // Shows the sign first.
    juce::String result;
    if ((number >= 0) && addPlusSymbolIfPositive) {
        result += "+";
    } else if (number < 0) {
        result += "-";
        number = -number;       // Displayed the sign NOW, not after!
    }

    if (showAsHex) {
        result += configuration.getPreHexSymbol() + juce::String::toHexString(number) + configuration.getPostHexSymbol();
    } else {
        result += configuration.getPreDecimalSymbol() + juce::String(number) + configuration.getPostDecimalSymbol();
    }

    return result;
}

}    // namespace disark
