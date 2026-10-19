#include "RasmHelper.h"

#include "../thirdParty/rasm/rasm.h"

namespace disark
{

std::unique_ptr<juce::MemoryBlock> RasmHelper::assembleSource(juce::MemoryBlock& source, int addedOrgAddress, std::vector<Symbol>* symbolsToFill) noexcept
{
    // Adds an "ORG" mnemonic, if needed.
    if (addedOrgAddress >= 0) {
        auto org = " org " + juce::String(addedOrgAddress) + "\r\n";
        source.insert(org.toRawUTF8(), static_cast<size_t>(org.length()), 0);
    }

    return assembleSourceWithoutAddingOrg(source, symbolsToFill);
}

std::unique_ptr<juce::MemoryBlock> RasmHelper::assembleSourceWithoutAddingOrg(const juce::MemoryBlock& source, std::vector<Symbol>* symbolsToFill) noexcept
{
    auto getLabelInfo = (symbolsToFill != nullptr);
    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;
    s_rasm_info* labelInfoPt = nullptr;

    size_t lengthIn = source.getSize();
    const char* dataIn = source.begin();

    int lengthOut = 0;
    int result;
    if (getLabelInfo) {
        result = RasmAssembleInfo(dataIn, (int)lengthIn, &dataOutPt, &lengthOut, &labelInfoPt);
    } else {
        result = RasmAssemble(dataIn, (int)lengthIn, &dataOutPt, &lengthOut);
    }

    std::unique_ptr<juce::MemoryBlock> outputMemoryBlock = nullptr;
    // Error?
    if (result == 0) {
        // Makes a copy of the data into a MemoryBlock.
        outputMemoryBlock = std::make_unique<juce::MemoryBlock>(dataOutPt, lengthOut);

        // Copies all the labels.
        if (labelInfoPt != nullptr) {
            for (int i = 0, symbolCount = labelInfoPt->nbsymbol; i < symbolCount; ++i) {
                const auto& labelData = labelInfoPt->symbol[i];
                auto label = labelData.name;
                auto address = labelData.v;

                jassert(symbolsToFill != nullptr);
                if (symbolsToFill != nullptr) {
                    symbolsToFill->emplace_back(label, address);
                }
            }
        }
    }
    // Cleans the memory.
    free(dataOutPt);
    if (getLabelInfo) {
        RasmFreeInfoStruct(labelInfoPt);
    }

    return outputMemoryBlock;
}

juce::MemoryBlock RasmHelper::commentIncludes(const juce::MemoryBlock& source) noexcept
{
    juce::MemoryInputStream playerSourceInputStream(source, false);

    // Reads all the lines, as long as we can.
    juce::MemoryOutputStream playerSourceOutputStreamWithoutInclude;
    while (!playerSourceInputStream.isExhausted()) {
        juce::String line = playerSourceInputStream.readNextLine();       // This excludes the end of lines, we have to add them below.
        if (line.containsIgnoreCase("include \"") || line.containsIgnoreCase("include\"")) {
            line = ";" + line;
        }
        playerSourceOutputStreamWithoutInclude << line << "\r\n";
    }

    return playerSourceOutputStreamWithoutInclude.getMemoryBlock();
}

juce::String RasmHelper::getSourceTagPrefix(PlayerType playerType) noexcept
{
    switch (playerType) {
        case PlayerType::Akg: return "PLY_AKG";
        case PlayerType::Aky: return "PLY_AKY";
        case PlayerType::AkyMultiplePsgs: return "PLY_AKY";
        case PlayerType::Lightweight:
        case PlayerType::LightweightSharpMz700:
            return "PLY_LW";
        case PlayerType::Akm: return "PLY_AKM";
        case PlayerType::StandAloneSoundEffects: return "PLY_SE";
        default:
            jassertfalse;
            return "";
    }
}

void RasmHelper::addRomPlayerDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, int bufferAddress, bool addRom) noexcept
{
    if (!addRom) {
        return;
    }
    addVariableDeclaration(source, sourceTagPrefix + "_ROM", "1");
    addVariableDeclaration(source, sourceTagPrefix + "_ROM_Buffer", juce::String(bufferAddress));
}

void RasmHelper::addHardwareDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, TargetHardware targetHardware) noexcept
{
    juce::String hardwareString;
    switch (targetHardware) {
        case TargetHardware::cpc:
            hardwareString = "CPC";
            break;
        case TargetHardware::msx:
            hardwareString = "MSX";
            break;
        case TargetHardware::pentagon:
            hardwareString = "PENTAGON";
            break;
        case TargetHardware::spectrum:
            hardwareString = "SPECTRUM";
            break;
        case TargetHardware::sharpMz:
            hardwareString = "SHARPMZ";
            break;

        case TargetHardware::cpcPlayCity:
            hardwareString = "PLAYCITY";
            break;
        case TargetHardware::spectrumTurboSound:
            hardwareString = "TURBOSOUND";
            break;
        case TargetHardware::spectrumNext:
            hardwareString = "SPECNEXT";
            break;
        case TargetHardware::msxFpgaPsg:
            hardwareString = "FPGAPSG";
            break;
        case TargetHardware::msxDarky:
            hardwareString = "DARKY";
            break;

        case TargetHardware::none:
        default:
            // Abnormal, unknown hardware.
            jassertfalse;
    }
    addVariableDeclaration(source, sourceTagPrefix + "_HARDWARE_" + hardwareString, "1");
}

void RasmHelper::addVariableDeclaration(juce::MemoryBlock& source, const juce::String& variable, const juce::String& value) noexcept
{
    juce::String lineToInsert = "    " + variable + " = " + value + "\r\n";
    source.insert(lineToInsert.toRawUTF8(), (size_t)lineToInsert.length(), 0);
}

void RasmHelper::insertAfterTag(const juce::String& tag, juce::MemoryBlock& source, const juce::MemoryBlock& blockToInsert) noexcept
{
    juce::MemoryInputStream sourceInputStream(source, false);

    // Finds the tag.
    bool found = false;
    while (!found && !sourceInputStream.isExhausted()) {
        const auto line = sourceInputStream.readNextLine();
        if (line.contains(tag)) {
            found = true;

            // Inserts the block.
            auto position = sourceInputStream.getPosition();
            source.insert(blockToInsert.getData(), blockToInsert.getSize(), (size_t)position);
        }
    }

    // We must have found the Tag to insert the code!
    jassert(found);
}

}    // namespace disark
