#include "Tool.h"

#include "Disassembler.h"
#include "base/ExportConfiguration.h"
#include "import/SymbolImporter.h"
#include "utils/commandLine/CommandLineArgumentDescriptor.h"
#include "utils/commandLine/CommandLineParser.h"
#include "utils/commandLine/Parameter.h"

namespace disark
{

int Tool::execute(int argc, char* argv[])      // NOLINT(*-avoid-c-arrays,clion-misra-cpp2008-3-1-3)
{
    // Creates the command line.
    juce::String description = "Z80 Disassembler. Disassembles any Z80 binary, reconstructs accurately the original code via its symbol table, including regions (code, byte, word, and pointer array).\n"
            "Usage: Disark <path to input binary file> <path to output z80 source file> "
            "[--sourceProfile <profile>] [--symbolFile <file with symbols>] [--labelPositionInSymbolFile <position>] [--addressPositionInSymbolFile <position>] "
            "[--loadAddress <address>] [--genOrg] [--genLabels] [--genLabelPrefix <prefix>] [--src8bitsValuesInHex] [--src16bitsValuesInHex]"
            "[--hexPrefix <prefix>] [--hexPostfix <postfix>] [--adrInComments] [--undocumentedOpcodesAsBytes]";

    std::vector<CommandLineArgumentDescriptor*> descriptors;

    // Declares all the command line parameters.
    auto descriptorParameterInput = CommandLineArgumentDescriptor::buildArgumentWithDirectValue(juce::translate("<path to input binary file>"),
                                                                                                juce::translate("Path and filename to the binary file to load."), true);
    descriptors.push_back(&descriptorParameterInput);
    auto descriptorParameterOutput = CommandLineArgumentDescriptor::buildArgumentWithDirectValue(juce::translate("<path to output z80 source file>"),
                                                                                                                          juce::translate("Path and filename to the z80 source to generate."), true);
    descriptors.push_back(&descriptorParameterOutput);

    auto optionSourceProfile = Option::buildLongOption("sourceProfile");
    Parameter parameterSourceProfile(ParameterType::string);
    auto descriptorSourceProfile = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("A source profile (can be overridden by the other options. Available: winape, maxam, pasmo, sdcc, vasm, orgams)."), optionSourceProfile, false, parameterSourceProfile);
    descriptors.push_back(&descriptorSourceProfile);

    auto optionSymbolFile = Option::buildLongOption("symbolFile");
    Parameter parameterSymbolFile(ParameterType::string);
    auto descriptorSymbolFile = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("Path and filename to the symbol list (by default, the label must start, followed by an address (decimal or #/&/$/0x for hex). Other data is ignored. Region are determined from special labels (check the manual))."), optionSymbolFile, false, parameterSymbolFile);
    descriptors.push_back(&descriptorSymbolFile);

    auto optionLabelPositionInSymbolFile = Option::buildLongOption("labelPositionInSymbolFile");
    Parameter parameterLabelPositionInSymbolFile(ParameterType::integer);
    auto descriptorLabelPositionInSymbolFile = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("Position (>0) where the label is in each line of the symbol list. Default is 1."), optionLabelPositionInSymbolFile, false, parameterLabelPositionInSymbolFile);
    descriptors.push_back(&descriptorLabelPositionInSymbolFile);

    auto optionAddressPositionInSymbolFile = Option::buildLongOption("addressPositionInSymbolFile");
    Parameter parameterAddressPositionInSymbolFile(ParameterType::integer);
    auto descriptorAddressPositionInSymbolFile = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("Position (>0) where the address is in each line of the symbol list. Default is 2."), optionAddressPositionInSymbolFile, false, parameterAddressPositionInSymbolFile);
    descriptors.push_back(&descriptorAddressPositionInSymbolFile);

    auto optionLoadAddress = Option::buildLongOption("loadAddress");
    Parameter parameterLoadAddress(ParameterType::integer);
    auto descriptorLoadAddress = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("The address of where the original code was compiled. Greatly needed for accuracy! The address can be in hex (0x)."), optionLoadAddress, false, parameterLoadAddress);
    descriptors.push_back(&descriptorLoadAddress);

    auto optionGenOrg = Option::buildLongOption("genOrg");
    auto descriptorGenOrg = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("If present, an ORG mnemonic is generated. Use --loadAddress to indicate the value."), optionGenOrg, false);
    descriptors.push_back(&descriptorGenOrg);

    auto optionGenLabels = Option::buildLongOption("genLabels");
    auto descriptorGenLabels = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("If present, labels will be generated whenever needed. Allows relocation. Probably not needed if you import a symbol file (--symbolFile)."), optionGenLabels, false);
    descriptors.push_back(&descriptorGenLabels);

    auto optionGenLabelPrefix = Option::buildLongOption("genLabelPrefix");
    Parameter parameterGenLabelPrefix(ParameterType::string);
    auto descriptorGenLabelPrefix = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("Sets the prefix of generated labels. Default is 'lab'."), optionGenLabelPrefix, false, parameterGenLabelPrefix);
    descriptors.push_back(&descriptorGenLabelPrefix);

    auto optionValues8BitsInHex = Option::buildLongOption("src8bitsValuesInHex");
    auto descriptorValues8BitsInHex = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("If present, all 8 bits values will be written in hexadecimal."), optionValues8BitsInHex, false);
    descriptors.push_back(&descriptorValues8BitsInHex);

    auto optionValues16BitsInHex = Option::buildLongOption("src16bitsValuesInHex");
    auto descriptorValues16BitsInHex = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("If present, all 16 bits values will be written in hexadecimal."), optionValues16BitsInHex, false);
    descriptors.push_back(&descriptorValues16BitsInHex);

    auto optionHexPrefixSymbol = Option::buildLongOption("hexPrefix");
    Parameter parameterHexPrefixSymbol(ParameterType::string);
    auto descriptorHexPrefixSymbol = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("Sets the prefix symbol for hex numbers (# is default). You may use quotes, useful for empty strings."), optionHexPrefixSymbol, false, parameterHexPrefixSymbol);
    descriptors.push_back(&descriptorHexPrefixSymbol);

    auto optionHexPostfixSymbol = Option::buildLongOption("hexPostfix");
    Parameter parameterHexPostfixSymbol(ParameterType::string);
    auto descriptorHexPostfixSymbol = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("Sets the postfix symbol for hex numbers (default is empty)."), optionHexPostfixSymbol, false, parameterHexPostfixSymbol);
    descriptors.push_back(&descriptorHexPostfixSymbol);

    auto optionGenerateAddressesInComments = Option::buildLongOption("adrInComments");
    auto descriptorGenerateAddressesInComments = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("If present, the current address is generated in the comment of each line."), optionGenerateAddressesInComments, false);
    descriptors.push_back(&descriptorGenerateAddressesInComments);

    auto optionUndocumentedOpcodesToBytes = Option::buildLongOption("undocumentedOpcodesToBytes");
    auto descriptorUndocumentedOpcodesToBytes = CommandLineArgumentDescriptor::buildArgumentWithOption(juce::translate("Converts the undocumented opcodes to bytes, for more compatibility."), optionUndocumentedOpcodesToBytes, false);
    descriptors.push_back(&descriptorUndocumentedOpcodesToBytes);

    // Starts parsing.
    CommandLineParser parser(argc, argv, descriptors, description);
    if (!parser.parse()) {
        return -1;              // Stops if parsing failed.
    }
    // Gets the result of the command line. Their presence has already been checked.
    auto inputFileString = descriptorParameterInput.getDirectValue();
    auto outputFileString = descriptorParameterOutput.getDirectValue();
    auto inputSymbolFileString = descriptorSymbolFile.getDirectValue();
    auto symbolFileString = parameterSymbolFile.isPresent() ? parameterSymbolFile.getValueAsString() : juce::String();
    auto generateOrg = descriptorGenOrg.isPresent();
    auto generateLabels = descriptorGenLabels.isPresent();
    auto generatedLabelsPrefix = parameterGenLabelPrefix.getValueAsString();
    auto use8BitsValuesInHex = descriptorValues8BitsInHex.isPresent();
    auto use16BitsValuesInHex = descriptorValues16BitsInHex.isPresent();
    auto generateAddressInComment = descriptorGenerateAddressesInComments.isPresent();
    auto encodeAddress = (descriptorLoadAddress.isPresent() && parameterLoadAddress.isParameterAnInteger()) ? parameterLoadAddress.getValueAsInteger() : 0;
    auto positionLabelInSymbolFile = 1;
    if (parameterLabelPositionInSymbolFile.isPresent()) {
        positionLabelInSymbolFile = parameterLabelPositionInSymbolFile.getValueAsInteger();
        if ((positionLabelInSymbolFile <= 0) || !parameterLabelPositionInSymbolFile.isParameterAnInteger()) {
            std::cerr << juce::translate("The given label position must be >0.") << '\n';
            return -1;
        }
    }
    auto positionAddressInSymbolFile = 2;
    if (parameterAddressPositionInSymbolFile.isPresent()) {
        positionAddressInSymbolFile = parameterAddressPositionInSymbolFile.getValueAsInteger();
        if ((positionAddressInSymbolFile <= 0) || !parameterAddressPositionInSymbolFile.isParameterAnInteger()) {
            std::cerr << juce::translate("The given address position must be >0.") << '\n';
            return -1;
        }
    }
    // Tries to fill the Export Configuration via the possible source profile.
    ExportConfiguration exportConfiguration;
    auto success = manageSourceProfile(parameterSourceProfile, exportConfiguration);
    if (!success) {
        return -1;
    }

    // Creates the in/out streams.
    auto inputFile = juce::File::getCurrentWorkingDirectory().getChildFile(inputFileString);    // To return an absolute path, else JUCE assertion raises.
    if (!inputFile.existsAsFile()) {
        std::cerr << juce::translate("Unable to open the input file.") << '\n';
        return -1;
    }
    juce::FileInputStream inputStream(inputFile);

    auto outputFile = juce::File::getCurrentWorkingDirectory().getChildFile(outputFileString);    // To return an absolute path, else JUCE assertion raises.
    (void)outputFile.deleteFile();
    juce::FileOutputStream outputStream(outputFile);

    // Builds the export configuration.
    exportConfiguration.setGenerateOrg(generateOrg);
    exportConfiguration.setEncode8BitNumberAsHex(use8BitsValuesInHex);
    exportConfiguration.setEncode16BitNumberAsHex(use16BitsValuesInHex);
    exportConfiguration.setGenerateLabels(generateLabels);
    if (generatedLabelsPrefix.isNotEmpty()) {
        exportConfiguration.setGeneratedBaseLabel(generatedLabelsPrefix);
    }
    if (parameterHexPrefixSymbol.isPresent()) {
        exportConfiguration.setHexadecimalPrefix(parameterHexPrefixSymbol.getValueAsString());
    }
    if (parameterHexPostfixSymbol.isPresent()) {
        exportConfiguration.setHexadecimalPostfix(parameterHexPostfixSymbol.getValueAsString());
    }
    exportConfiguration.setGenerateAddressesInComments(generateAddressInComment);
    if (descriptorUndocumentedOpcodesToBytes.isPresent()) {
        exportConfiguration.setUndocumentedOpcodesAsBytes(true);
    }

    // Prepares the disassembling.
    Disassembler disassembler(exportConfiguration);
    disassembler.setStartAddress(encodeAddress);
    // Reads the possible symbol file.
    auto symbolInputFile = juce::File::getCurrentWorkingDirectory().getChildFile(symbolFileString);    // To return an absolute path, else JUCE assertion raises.
    if (symbolFileString.isNotEmpty()) {
        if (!symbolInputFile.existsAsFile()) {
            std::cerr << juce::translate("Unable to open the symbol file.") << '\n';
            return -1;
        }
        juce::FileInputStream symbolInputStream(symbolInputFile);

        // Parses the symbol file.
        SymbolImporter symbolImporter(symbolInputStream);
        auto labelsAndAddressesAndErrorString = symbolImporter.import(positionLabelInSymbolFile - 1, positionAddressInSymbolFile - 1); // Position converted to indexes.
        auto errorString = labelsAndAddressesAndErrorString.second;
        if (errorString.isNotEmpty()) {
            std::cerr << juce::translate("An error occurred while reading the symbol file:") << '\n' << errorString << '\n';
            return -1;
        }
        // Adds all the symbols into the disassembler.
        for (const auto& labelAndAddress : labelsAndAddressesAndErrorString.first) {
            disassembler.addSymbol({ labelAndAddress.getLabel(), labelAndAddress.getAddress(), false });
        }
    }

    // Disassembles!
    auto errorStrings = disassembler.disassemble(inputStream, outputStream);

    // Errors?
    success = errorStrings.empty();
    if (!success) {
        std::cerr << juce::translate("Error while disassembling:") << '\n';
        for (const auto& string : errorStrings) {
            std::cerr << string << '\n';
        }
    } else {
        std::cout << juce::translate("Source generated.") << '\n';
    }

    return success ? 0 : -1;
}

bool Tool::manageSourceProfile(const Parameter& sourceProfileParameter, ExportConfiguration& exportConfiguration)
{
    // Not present? Then exits.
    if (!sourceProfileParameter.isPresent()) {
        return true;
    }

    auto profile = sourceProfileParameter.getValueAsString();
    if (profile == "winape") {
        exportConfiguration.setUndocumentedOpcodesAsBytes(true);
        exportConfiguration.setRstAsIndex(true);
    } else if (profile == "orgams") {
        exportConfiguration.setDeclareByteMnemonic("BYTE");
        exportConfiguration.setDeclareWordMnemonic("WORD");
    } else if (profile == "vasm") {
        exportConfiguration.setNoLabelBeforeSetInstruction(true);
    } else if ((profile == "maxam") || (profile == "pasmo")) {
        exportConfiguration.setUndocumentedOpcodesAsBytes(true);
    } else if (profile == "sdcc") {
        exportConfiguration.setDeclareByteMnemonic(".db");
        exportConfiguration.setDeclareWordMnemonic(".dw");
        exportConfiguration.setOrgMnemonic(".org");
        exportConfiguration.setEquMnemonic("=");
        exportConfiguration.setImmediateDataDeclarationSymbol("#");
        exportConfiguration.setCurrentAddressSymbol(".");
        exportConfiguration.setHexadecimalPrefix("0x");
        exportConfiguration.setLabelPostfix(":");
        exportConfiguration.setUndocumentedOpcodesAsBytes(true);
        exportConfiguration.setSdccRelativeRegisterSyntax(true);
        exportConfiguration.setGenerateExternalLabels(true);
        exportConfiguration.setNoPostFixAfterLabelWithEqu(true);
    } else {
        // Unknown profile.
        std::cerr << "The profile " + profile + " is unknown." << '\n';
        return false;
    }

    return true;
}

}    // namespace disark
