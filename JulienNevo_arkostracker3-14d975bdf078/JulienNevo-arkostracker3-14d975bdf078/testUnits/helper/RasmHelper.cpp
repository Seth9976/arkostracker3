#include "RasmHelper.h"

#include "../../source/export/playerConfiguration/PlayerConfigurationExporter.h"
#include "../../source/export/sourceGenerator/SourceGeneratorConfiguration.h"
#include "../../source/utils/MemoryBlockUtil.h"
#include "../../source/utils/RasmUtil.h"
#include "../../thirdParty/rasm/rasm.h"

namespace arkostracker 
{

bool RasmHelper::assembleAndCompareSources(const juce::MemoryBlock& source1, const juce::MemoryBlock& source2,
    const std::unordered_set<int>& errorOffsets, const int tolerance) noexcept
{
    // Assembles the two codes.
    const auto assembleResult1 = assembleSourceWithoutAddingOrg(source1);
    if (assembleResult1 == nullptr) {
        return false;
    }
    const auto assembleResult2 = assembleSourceWithoutAddingOrg(source2);
    if (assembleResult2 == nullptr) {
        return false;
    }

    return MemoryBlockUtil::compare(*assembleResult1, *assembleResult2, errorOffsets, tolerance);
}

std::unique_ptr<juce::MemoryBlock> RasmHelper::assembleSource(juce::MemoryBlock& source, const OptionalInt addedOrgAddress, std::vector<Symbol>* symbolsToFill) noexcept
{
    // Adds an "ORG" mnemonic, if needed.
    if (addedOrgAddress.isPresent()) {
        const auto org = " org " + juce::String(addedOrgAddress.getValue()) + "\r\n";
        source.insert(org.toRawUTF8(), static_cast<size_t>(org.length()), 0);
    }

    return assembleSourceWithoutAddingOrg(source, symbolsToFill);
}

std::unique_ptr<juce::MemoryBlock> RasmHelper::assembleSourceWithoutAddingOrg(const juce::MemoryBlock& source, std::vector<Symbol>* symbolsToFill) noexcept
{
    const auto getLabelInfo = (symbolsToFill != nullptr);
    // Creates a pointer of pointer. Rasm will make it point to a new buffer.
    unsigned char* dataOutPt = nullptr;
    s_rasm_info* labelInfoPt = nullptr;

    const auto lengthIn = source.getSize();
    const auto* dataIn = source.begin();

    auto lengthOut = 0;
    int result;     // NOLINT(*-init-variables)
    if (getLabelInfo) {
        result = RasmAssembleInfo(dataIn, static_cast<int>(lengthIn), &dataOutPt, &lengthOut, &labelInfoPt);
    } else {
        result = RasmAssemble(dataIn, static_cast<int>(lengthIn), &dataOutPt, &lengthOut);
    }

    std::unique_ptr<juce::MemoryBlock> outputMemoryBlock = nullptr;
    // Error?
    if (result == 0) {
        // Makes a copy of the data into a MemoryBlock.
        outputMemoryBlock = std::make_unique<juce::MemoryBlock>(dataOutPt, lengthOut);

        // Copies all the labels.
        if (labelInfoPt != nullptr) {
            for (auto i = 0, symbolCount = labelInfoPt->nbsymbol; i < symbolCount; ++i) {
                const auto& labelData = labelInfoPt->symbol[i];
                const auto* label = labelData.name;
                const auto address = labelData.v;

                jassert(symbolsToFill != nullptr);
                symbolsToFill->emplace_back(label, address);
            }
        }
    }
    // Cleans the memory.
    free(dataOutPt);    // NOLINT(*-no-malloc)
    if (getLabelInfo) {
        RasmFreeInfoStruct(labelInfoPt);
    }

    return outputMemoryBlock;
}

void RasmHelper::addPlayerConfiguration(juce::MemoryBlock& source, const PlayerConfiguration& playerConfiguration) noexcept
{
    const auto sourceGeneratorConfiguration = SourceGeneratorConfiguration::buildZ80(true);

    const auto playerConfigurationSource = PlayerConfigurationExporter::exportConfiguration(sourceGeneratorConfiguration, playerConfiguration);
    source.insert(playerConfigurationSource.getData(), playerConfigurationSource.getSize(), 0);
}

void RasmHelper::addRomPlayerDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, const int bufferAddress, const bool addRom) noexcept
{
    if (!addRom) {
        return;
    }
    RasmUtil::addVariableDeclaration(source, sourceTagPrefix + "_ROM", "1");
    RasmUtil::addVariableDeclaration(source, sourceTagPrefix + "_ROM_Buffer", juce::String(bufferAddress));
}

void RasmHelper::addHardwareDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, const TargetHardware targetHardware) noexcept
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
        case TargetHardware::pcw:
            hardwareString = "PCW";
            break;
        case TargetHardware::pcwTurboSound:
            hardwareString = "PCW_TURBOSOUND";
            break;
        case TargetHardware::svi:
            hardwareString = "SVI";
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

        default:
            jassertfalse;   // Abnormal, unknown hardware.
            break;
    }
    RasmUtil::addVariableDeclaration(source, sourceTagPrefix + "_HARDWARE_" + hardwareString, "1");
}

void RasmHelper::insertAfterTag(const juce::String& tag, juce::MemoryBlock& source, const juce::MemoryBlock& blockToInsert) noexcept
{
    juce::MemoryInputStream sourceInputStream(source, false);

    // Finds the tag.
    auto found = false;
    while (!found && !sourceInputStream.isExhausted()) {
        const auto line = sourceInputStream.readNextLine();
        if (line.contains(tag)) {
            found = true;

            // Inserts the block.
            const auto position = sourceInputStream.getPosition();
            source.insert(blockToInsert.getData(), blockToInsert.getSize(), static_cast<size_t>(position));
        }
    }

    // We must have found the Tag to insert the code!
    jassert(found);
}

}   // namespace arkostracker
