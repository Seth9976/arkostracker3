#pragma once

#include <juce_core/juce_core.h>

namespace disark
{

class ExportConfiguration;

/**
 * Various utility method generate the source.
 */
class WriterUtils
{
public:
    /** Prevents instantiation. */
    WriterUtils() = delete;

    /** Writes a String to the OutputStream, with a return carriage. */
    static void writeString(juce::OutputStream& outputStream, const juce::String& text) noexcept;

    /**
     * Returns a hexadecimal String from the given number, using the configuration for the symbol.
     * @param configuration the export configuration.
     * @param number the number. Must be positive.
     * @return the String.
     */
    static juce::String getHexStringFromNumber(const ExportConfiguration& configuration, int number) noexcept;

    /**
     * Returns a label for declaration, that is, with a possible prefix and postfix.
     * @param configuration the export configuration.
     * @param label the raw label.
     * @param isExternal true if the label is external (marked so that assemblers like SDCC can read it from C). They may have a special syntax.
     * @param skipPostFix true to skip the postfix (useful in some case for SDCC, for EQU (=)).
     * @return the label, modified or not.
     */
    static juce::String getLabelForDeclaration(const ExportConfiguration& configuration, const juce::String& label, bool isExternal, bool skipPostFix) noexcept;

    /**
     * Returns a label declaration, such as ("label equ "). The value behind is not written.
     * @param configuration the export configuration.
     * @param labelDeclaration the label declaration (with a possible prefix and postfix). Use the getLabelDeclaration to generate it.
     * @return the label declaration, without value.
     */
    static juce::String getLabelDeclarationWithoutValue(const ExportConfiguration& configuration, const juce::String& labelDeclaration) noexcept;

    /**
     * Returns a String to display, for a decimal number, possibly signed, with a possible prefix and postfix.
     * @param configuration the export configuration.
     * @param number the number, possibly signed.
     * @param addPlusSymbolIfPositive if true, a "+" symbol is added if the value is positive (useful for offsets).
     * @return the String to display.
     */
    static juce::String getStringForDecimalNumber(const ExportConfiguration& configuration, int number, bool addPlusSymbolIfPositive) noexcept;

    /**
     * Returns a String to display, for an hexadecimal number, possibly signed, with a possible prefix and postfix.
     * @param configuration the export configuration.
     * @param number the number, possibly signed.
     * @param addPlusSymbolIfPositive if true, a "+" symbol is added if the value is positive (useful for offsets).
     * @return the String to display.
     */
    static juce::String getStringForHexadecimalNumber(const ExportConfiguration& configuration, int number, bool addPlusSymbolIfPositive) noexcept;

    /**
     * Returns a String to display, for an decimal/hexadecimal number, possibly signed, with a possible prefix and postfix.
     * @param configuration the export configuration.
     * @param number the number, possibly signed.
     * @param showAsHex true to show as hexadecimal, false for decimal.
     * @param addPlusSymbolIfPositive if true, a "+" symbol is added if the value is positive (useful for offsets).
     * @return the String to display.
     */
    static juce::String getStringForNumber(const ExportConfiguration& configuration, int number, bool showAsHex, bool addPlusSymbolIfPositive) noexcept;
};

}    // namespace disark
