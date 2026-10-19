#include "ExportConfiguration.h"

namespace disark
{

ExportConfiguration::ExportConfiguration() noexcept :
    declareByteMnemonic("db"),
    declareWordMnemonic("dw"),
    decimalPrefix(""),
    decimalPostfix(""),
    hexadecimalPrefix("#"),
    hexadecimalPostfix(""),
    tabulation("    "),
    mnemonicPostfix(" "),
    commentSymbol(";"),
    orgMnemonic("org"),
    generateOrg(false),
    encode8BitNumberAsHex(true),
    encode16BitNumberAsHex(true),
    generateAddressesInComments(false),
    generateLabels(false),
    generatedBaseLabel("lab"),
    labelPrefix(""),
    labelPostfix(""),
    undocumentedOpcodesAsBytes(false),
    sdccRelativeRegisterSyntax(false),
    rstAsIndex(false),
    immediateDataDeclarationSymbol(""),
    currentAddressSymbol("$"),
    noLabelBeforeSetInstruction(false),
    generateExternalLabels(false),
    equMnemonic("equ"),
    noPostFixAfterLabelWithEqu(false)
{
}

ExportConfiguration ExportConfiguration::buildWithCommentsAndGeneratedLabels(bool withComments, bool withGeneratedLabels) noexcept
{
    ExportConfiguration exportConfiguration;

    exportConfiguration.generateAddressesInComments = withComments;
    exportConfiguration.generateLabels = withGeneratedLabels;

    return exportConfiguration;
}

juce::String ExportConfiguration::getMnemonicPostfix() const noexcept
{
    return mnemonicPostfix;
}

bool ExportConfiguration::isEncode8BitNumberAsHex() const noexcept
{
    return encode8BitNumberAsHex;
}

bool ExportConfiguration::isEncode16BitNumberAsHex() const noexcept
{
    return encode16BitNumberAsHex;
}

juce::String ExportConfiguration::getDeclareByteMnemonic() const noexcept
{
    return declareByteMnemonic;
}

juce::String ExportConfiguration::getDeclareWordMnemonic() const noexcept
{
    return declareWordMnemonic;
}

juce::String ExportConfiguration::getTabulation() const noexcept
{
    return "    ";
}

juce::String ExportConfiguration::getPreDecimalSymbol() const noexcept
{
    return decimalPrefix;
}

juce::String ExportConfiguration::getPostDecimalSymbol() const noexcept
{
    return decimalPostfix;
}

juce::String ExportConfiguration::getPreHexSymbol() const noexcept
{
    return hexadecimalPrefix;
}

juce::String ExportConfiguration::getPostHexSymbol() const noexcept
{
    return hexadecimalPostfix;
}

juce::String ExportConfiguration::getEquMnemonic() const noexcept
{
    return equMnemonic;
}

void ExportConfiguration::setEquMnemonic(const juce::String& mnemonic) noexcept
{
    equMnemonic = mnemonic;
}

juce::String ExportConfiguration::getCurrentAddressSymbol() const noexcept
{
    return currentAddressSymbol;
}

void ExportConfiguration::setCurrentAddressSymbol(const juce::String& symbol) noexcept
{
    currentAddressSymbol = symbol;
}

bool ExportConfiguration::isGenerateAddressesInComments() const noexcept
{
    return generateAddressesInComments;
}

juce::String ExportConfiguration::getCommentSymbol() const noexcept
{
    return commentSymbol;
}

bool ExportConfiguration::isGenerateLabels() const noexcept
{
    return generateLabels;
}

juce::String ExportConfiguration::getGeneratedBaseLabel() const noexcept
{
    return generatedBaseLabel;
}

juce::String ExportConfiguration::getOrgMnemonic() const noexcept
{
    return orgMnemonic;
}


void ExportConfiguration::setDecimalPrefix(const juce::String& prefix) noexcept
{
    decimalPrefix = prefix;
}

void ExportConfiguration::setDecimalPostfix(const juce::String& postFix) noexcept
{
    decimalPostfix = postFix;
}

void ExportConfiguration::setHexadecimalPrefix(const juce::String& prefix) noexcept
{
    hexadecimalPrefix = prefix;
}

void ExportConfiguration::setHexadecimalPostfix(const juce::String& postFix) noexcept
{
    hexadecimalPostfix = postFix;
}

void ExportConfiguration::setEncode8BitNumberAsHex(bool encodeAsHex) noexcept
{
    encode8BitNumberAsHex = encodeAsHex;
}

void ExportConfiguration::setEncode16BitNumberAsHex(bool encodeAsHex) noexcept
{
    encode16BitNumberAsHex = encodeAsHex;
}

void ExportConfiguration::setGenerateLabels(bool generate) noexcept
{
    generateLabels = generate;
}

void ExportConfiguration::setGeneratedBaseLabel(const juce::String& baseLabel) noexcept
{
    generatedBaseLabel = baseLabel;
}

bool ExportConfiguration::isGenerateOrg() const noexcept
{
    return generateOrg;
}

void ExportConfiguration::setGenerateOrg(bool generate) noexcept
{
    generateOrg = generate;
}

void ExportConfiguration::setGenerateAddressesInComments(bool generateAddresses) noexcept
{
    generateAddressesInComments = generateAddresses;
}

bool ExportConfiguration::isUndocumentedOpcodesAsBytes() const noexcept
{
    return undocumentedOpcodesAsBytes;
}

void ExportConfiguration::setUndocumentedOpcodesAsBytes(bool asBytes) noexcept
{
    undocumentedOpcodesAsBytes = asBytes;
}

juce::String ExportConfiguration::getLabelPrefix() const noexcept
{
    return labelPrefix;
}

juce::String ExportConfiguration::getLabelPostfix() const noexcept
{
    return labelPostfix;
}

void ExportConfiguration::setLabelPrefix(const juce::String& prefix) noexcept
{
    labelPrefix = prefix;
}

void ExportConfiguration::setLabelPostfix(const juce::String& postfix) noexcept
{
    labelPostfix = postfix;
}

void ExportConfiguration::setDeclareByteMnemonic(const juce::String& mnemonic) noexcept
{
    declareByteMnemonic = mnemonic;
}

void ExportConfiguration::setDeclareWordMnemonic(const juce::String& mnemonic) noexcept
{
    declareWordMnemonic = mnemonic;
}

void ExportConfiguration::setOrgMnemonic(const juce::String& mnemonic) noexcept
{
    orgMnemonic = mnemonic;
}

void ExportConfiguration::setSdccRelativeRegisterSyntax(bool useSdccSyntax) noexcept
{
    sdccRelativeRegisterSyntax = useSdccSyntax;
}

bool ExportConfiguration::isSdccRelativeRegisterSyntaxUsed() const noexcept
{
    return sdccRelativeRegisterSyntax;
}

bool ExportConfiguration::isRstAsIndex() const noexcept
{
    return rstAsIndex;
}

void ExportConfiguration::setRstAsIndex(bool useRstAsIndex) noexcept
{
    rstAsIndex = useRstAsIndex;
}

juce::String ExportConfiguration::getImmediateDataDeclarationSymbol() const noexcept
{
    return immediateDataDeclarationSymbol;
}

void ExportConfiguration::setImmediateDataDeclarationSymbol(juce::String symbol) noexcept
{
    immediateDataDeclarationSymbol = std::move(symbol);
}

bool ExportConfiguration::isNoLabelBeforeSetInstruction() const noexcept
{
    return noLabelBeforeSetInstruction;
}

void ExportConfiguration::setNoLabelBeforeSetInstruction(bool newState) noexcept
{
    noLabelBeforeSetInstruction = newState;
}

juce::String ExportConfiguration::getExternalLabelPrefix() const noexcept
{
    return "_";        // For now, only SDCC uses this, it can be hardcoded.
}

juce::String ExportConfiguration::getExternalLabelPostfix() const noexcept
{
    return "::";        // For now, only SDCC uses this, it can be hardcoded.
}

bool ExportConfiguration::isGenerateExternalLabels() const noexcept
{
    return generateExternalLabels;
}

void ExportConfiguration::setGenerateExternalLabels(bool generate) noexcept
{
    generateExternalLabels = generate;
}

bool ExportConfiguration::isNoPostFixAfterLabelWithEqu() const noexcept
{
    return noPostFixAfterLabelWithEqu;
}

void ExportConfiguration::setNoPostFixAfterLabelWithEqu(bool newNoPostFixAfterLabelWithEqu) noexcept
{
    noPostFixAfterLabelWithEqu = newNoPostFixAfterLabelWithEqu;
}

}    // namespace disark
