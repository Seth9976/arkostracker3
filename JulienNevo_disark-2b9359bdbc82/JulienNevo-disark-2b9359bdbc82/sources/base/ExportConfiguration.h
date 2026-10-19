#pragma once

#include <juce_core/juce_core.h>

namespace disark
{

/**
 * Configures the source when exporting.
 */
class ExportConfiguration
{
public:
    /** Constructor with default values. */
    ExportConfiguration() noexcept;

    /** Builder to use the default configuration, but with comments and/or generated labels. */
    static ExportConfiguration buildWithCommentsAndGeneratedLabels(bool withComments = true, bool withGeneratedLabels = true) noexcept;

    juce::String getMnemonicPostfix() const noexcept;
    juce::String getDeclareByteMnemonic() const noexcept;
    juce::String getDeclareWordMnemonic() const noexcept;
    juce::String getPreDecimalSymbol() const noexcept;
    juce::String getPostDecimalSymbol() const noexcept;
    juce::String getPreHexSymbol() const noexcept;
    juce::String getPostHexSymbol() const noexcept;
    juce::String getEquMnemonic() const noexcept;
    juce::String getCurrentAddressSymbol() const noexcept;
    void setCurrentAddressSymbol(const juce::String& symbol) noexcept;
    juce::String getCommentSymbol() const noexcept;
    /** @return the "tabulation" to use when there is no label. */
    juce::String getTabulation() const noexcept;
    juce::String getGeneratedBaseLabel() const noexcept;
    juce::String getLabelPrefix() const noexcept;
    juce::String getLabelPostfix() const noexcept;
    juce::String getExternalLabelPrefix() const noexcept;
    juce::String getExternalLabelPostfix() const noexcept;
    juce::String getOrgMnemonic() const noexcept;
    void setEquMnemonic(const juce::String& mnemonic) noexcept;

    /** @return true if the Org must be generated. */
    bool isGenerateOrg() const noexcept;
    /**
     * Asks to generate an Org or not.
     * @param generateOrg true to generate an Org.
     */
    void setGenerateOrg(bool generateOrg) noexcept;

    /** Sets the prefix of the decimal symbol. May be empty. */
    void setDecimalPrefix(const juce::String& decimalPrefix) noexcept;
    /** Sets the postfix of the decimal symbol. May be empty. */
    void setDecimalPostfix(const juce::String& decimalPostfix) noexcept;

    /** Sets the prefix of the hex symbol. May be empty. */
    void setHexadecimalPrefix(const juce::String& hexadecimalPrefix) noexcept;
    /** Sets the postfix of the hex symbol. May be empty. */
    void setHexadecimalPostfix(const juce::String& hexadecimalPostfix) noexcept;

    /** @return true if undocumented opcodes must be encoded as "db". */
    bool isUndocumentedOpcodesAsBytes() const noexcept;
    /**
     * Indicates whether undocumented opcodes must be encoded as "db".
     * @param undocumentedOpcodesAsBytes true if undocumented opcodes must be encoded as "db".
     */
    void setUndocumentedOpcodesAsBytes(bool undocumentedOpcodesAsBytes) noexcept;

    /**
     * Sets how to encode the 8-bit numbers.
     * @param encode8BitNumberAsHex true to encode in hex, false to decimal.
     */
    void setEncode8BitNumberAsHex(bool encode8BitNumberAsHex) noexcept;
    /**
     * Sets how to encode the 16-bit numbers.
     * @param encode16BitNumberAsHex true to encode in hex, false to decimal.
     */
    void setEncode16BitNumberAsHex(bool encode16BitNumberAsHex) noexcept;

    /** Indicates whether to generate labels. */
    void setGenerateLabels(bool generateLabels) noexcept;

    /** Sets the base for the generated labels, used to generate all labels. Should not be empty, else the source might be unreadable. */
    void setGeneratedBaseLabel(const juce::String& generatedLabelPrefix) noexcept;

    /** @return true if 8-bit values are encoded as hexadecimal, false as decimal. */
    bool isEncode8BitNumberAsHex() const noexcept;
    /** @return true if 16-bit values are encoded as hexadecimal, false as decimal. */
    bool isEncode16BitNumberAsHex() const noexcept;

    /** True to set the address in the comments. */
    void setGenerateAddressesInComments(bool generateAddressesInComments) noexcept;

    /** @return true to generate the address of each instruction in the comments. */
    bool isGenerateAddressesInComments() const noexcept;
    /** @return true to generate labels from referenced addresses. */
    bool isGenerateLabels() const noexcept;

    /** Sets the prefix to write before each label declaration (".") for example. */
    void setLabelPrefix(const juce::String& labelPrefix) noexcept;
    /** Sets the postfix to write after each label declaration (":") for example. */
    void setLabelPostfix(const juce::String& labelPostfix) noexcept;

    void setDeclareByteMnemonic(const juce::String& mnemonic) noexcept;
    void setDeclareWordMnemonic(const juce::String& mnemonic) noexcept;
    void setOrgMnemonic(const juce::String& mnemonic) noexcept;

    bool isSdccRelativeRegisterSyntaxUsed() const noexcept;
    void setSdccRelativeRegisterSyntax(bool useSdccSyntax) noexcept;

    bool isRstAsIndex() const noexcept;
    void setRstAsIndex(bool useRstAsIndex) noexcept;

    juce::String getImmediateDataDeclarationSymbol() const noexcept;
    void setImmediateDataDeclarationSymbol(juce::String symbol) noexcept;

    /** Vasm does not accept a SET instruction if a label is before, it considers it a macro. True to force a return carriage. */
    bool isNoLabelBeforeSetInstruction() const noexcept;
    /**
     * Indicates whether to prevent a SET instruction to be on the same line as a label (Vasm corner case).
     * @param newState true to add a return carriage before a SET instruction, if a label is there too.
     */
    void setNoLabelBeforeSetInstruction(bool newState) noexcept;

    bool isGenerateExternalLabels() const noexcept;
    void setGenerateExternalLabels(bool generateExternalLabels) noexcept;

    /** @return true to remove postfixes after a label with EQU is used. This is useful for SDCC to have code like "myLabel = 0x4000". */
    bool isNoPostFixAfterLabelWithEqu() const noexcept;
    void setNoPostFixAfterLabelWithEqu(bool noPostFixAfterLabelWithEqu) noexcept;

private:
    juce::String declareByteMnemonic;
    juce::String declareWordMnemonic;
    juce::String decimalPrefix;
    juce::String decimalPostfix;
    juce::String hexadecimalPrefix;
    juce::String hexadecimalPostfix;
    juce::String tabulation;
    juce::String mnemonicPostfix;
    juce::String commentSymbol;
    juce::String orgMnemonic;
    bool generateOrg;
    bool encode8BitNumberAsHex;                                             // True to encode 8-bit values as hexadecimal, false as decimal.
    bool encode16BitNumberAsHex;                                            // True to encode 16-bit values as hexadecimal, false as decimal.
    bool generateAddressesInComments;
    bool generateLabels;                                                    // True to generate labels from referenced addresses.
    juce::String generatedBaseLabel;
    juce::String labelPrefix;
    juce::String labelPostfix;
    bool undocumentedOpcodesAsBytes;                                        // True if undocumented opcodes must be encoded as "db".
    bool sdccRelativeRegisterSyntax;                                        // True to use the strange SDCC syntax for IX/IY ("ld l,test+0(ix)" instead of "ld l,(ix + test+0)").
    bool rstAsIndex;                                                        // True to use RST 7 instead of RST #38 for example.
    juce::String immediateDataDeclarationSymbol;                            // Symbol to add to indicate the data is an immediate. Empty in most case, but SDCC : ld a,"#test + 5", or "ld a,#5".
    juce::String currentAddressSymbol;
    bool noLabelBeforeSetInstruction;                                       // Vasm does not accept a SET instruction if a label is before, it considers it a macro. True to force a return carriage.
    bool generateExternalLabels;                                            // True to allow the generation of external labels, such as the ones used by SDCC.
    juce::String equMnemonic;
    bool noPostFixAfterLabelWithEqu;                                        // True to bypass the postfix for labels, useful for SDCC.
};

}    // namespace disark
