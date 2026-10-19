#include "Disassembler.h"

#include "BinaryParser.h"
#include "base/AreaGenerator.h"
#include "base/ExportConfiguration.h"
#include "base/RegionDataHolder.h"
#include "base/WriterUtils.h"
#include "base/sourceItemVisitor/LabelGenerator.h"

namespace disark
{

Disassembler::Disassembler(const ExportConfiguration& pExportConfiguration) noexcept :
    exportConfiguration(pExportConfiguration),
    loadAddress(0),
    regions(),
    references(),
    pendingSymbols()
{
}

void Disassembler::setStartAddress(int address) noexcept
{
    loadAddress = address;
}

void Disassembler::addRegion(const Region& region) noexcept
{
    regions.addRegion(region);
}

void Disassembler::addSymbol(const Symbol& symbol) noexcept
{
    // Stores the reference for now.
    pendingSymbols.emplace_back(symbol);
}

void Disassembler::addSymbols(const std::vector<Symbol>& symbols) noexcept
{
    for (const auto& symbol : symbols) {
        addSymbol(symbol);
    }
}

std::vector<std::unique_ptr<RegionDataHolder>> Disassembler::disassembleRegions(juce::InputStream& inputStream) noexcept
{
    LocalBytesProvider bytesProvider(inputStream, *this);

    // Reads every Region (one iteration per Region). The iteration stops when a different Region is found.
    std::vector<std::unique_ptr<RegionDataHolder>> regionDataHolders;

    while (!inputStream.isExhausted()) {
        const auto currentAddress = calculateAddress(inputStream);
        BinaryParser binaryParser(exportConfiguration, bytesProvider);

        // What is the type of the forthcoming Region?
        auto regionType = regions.getRegionTypeSortIfNeeded(currentAddress);

        std::unique_ptr<RegionDataHolder> regionDataHolder;     // This will be filled.
        switch (regionType) {
            case RegionType::code: {
                // Parses the code and build Instructions.
                auto instructionsAndLeftOver = binaryParser.buildAllInstructions();

                // Stores this in a Holder.
                regionDataHolder = std::make_unique<CodeRegionDataHolder>(currentAddress, instructionsAndLeftOver, exportConfiguration.isUndocumentedOpcodesAsBytes());
            }
                break;
            case RegionType::byte: {
                // Parses the bytes.
                auto readBytes = binaryParser.buildByteRegion();

                // Stores this in a Holder.
                regionDataHolder = std::make_unique<ByteRegionDataHolder>(currentAddress, readBytes);
            }
                break;
            case RegionType::word: [[fallthrough]];
            case RegionType::pointers: {
                // Parses the bytes.
                auto readBytes = binaryParser.buildWordRegion();

                // Stores this in a Holder.
                regionDataHolder = std::make_unique<PointerRegionDataHolder>(currentAddress, readBytes,
                                                                             (regionType == RegionType::pointers)); // Pointers can infer refernces, but not words.
            }
                break;
            default:
                jassertfalse;           // Should never happen.
                break;
        }

        regionDataHolders.emplace_back(std::move(regionDataHolder));
    }

    return regionDataHolders;
}

int Disassembler::calculateAddress(juce::InputStream& inputStream) const noexcept
{
    const auto address = loadAddress + static_cast<int>(inputStream.getPosition());
    jassert(address < 65536);

    return address;
}


// LocalBytesProvider
// ============================================================

Disassembler::LocalBytesProvider::LocalBytesProvider(juce::InputStream& pInputStream, Disassembler& pParent) noexcept :
    regionType(RegionType::code),
    inputStream(pInputStream),
    parent(pParent)
{
}

int Disassembler::LocalBytesProvider::fetchByte()
{
    // No data? Then notifies the client.
    if (!hasNext()) {
        return -1;
    }

    return static_cast<unsigned char>(inputStream.readByte());
}

bool Disassembler::LocalBytesProvider::hasNext()
{
    // Obviously, if not more data, there is nothing next.
    if (inputStream.isExhausted()) {
        return false;
    }

    // There is data. However, we may have changed Region. If that's the case, we must stop.
    const auto address = parent.calculateAddress(inputStream);

    const auto newRegionType = parent.regions.getRegionTypeSortIfNeeded(address);
    if (regionType != newRegionType) {
        // The Region has changed. Stops the loading.
        regionType = newRegionType;
        return false;
    }

    return true;
}


// ============================================================

std::vector<juce::String> Disassembler::disassemble(juce::InputStream& inputStream, juce::OutputStream& outputStream) noexcept
{
    // Parses the labels from the symbols and generates Regions from them. Errors may happen.
    auto errorStrings = parsePendingSymbols();
    if (!errorStrings.empty()) {
        return errorStrings;            // Errors, stops here.
    }

    generateOrgIfNeeded(outputStream);

    // The generations consist of "visitors" which receives the instructions of the source.

    // The first visitor gathers the instruction addresses to generate labels.
    LabelGenerator labelGenerator(references, exportConfiguration);
    // This "temp" visitor encodes exactly like the real one, but we don't write anything. The point is to know all the references that were used,
    // which allows to delete the ones that are useless.
    FakeOutputStream fakeOutputStream;
    SourceItemEncoderAndGeneratedLabelCleaner tempSourceItemEncoder(references, fakeOutputStream, exportConfiguration);
    SourceItemEncoder sourceItemEncoder(references, outputStream, exportConfiguration);

    // Small optimization, only adds the label generator if the user wanted it.
    std::vector<SourceItemVisitor*> visitors;
    if (exportConfiguration.isGenerateLabels()) {
        visitors.push_back(&labelGenerator);
    }
    visitors.push_back(&tempSourceItemEncoder);
    visitors.push_back(&sourceItemEncoder);

    // Parses the bytes of all the Regions.
    auto regionDataHolders = disassembleRegions(inputStream);

    // Parses the full data for each visitor.
    for (auto* visitor : visitors) {
        for (const auto& regionDataHolder : regionDataHolders) {
            regionDataHolder->parseSourceItems(*visitor);
        }

        visitor->executeAfterVisit();
    }

    // No errors.
    return {};
}

void Disassembler::generateOrgIfNeeded(juce::OutputStream& outputStream) noexcept
{
    // Generates the ORG? The address may be 0, it is not a problem.
    if (!exportConfiguration.isGenerateOrg()) {
        return;
    }

    // Generates "org xxxx".
    const auto org = exportConfiguration.getTabulation() + exportConfiguration.getOrgMnemonic() + exportConfiguration.getMnemonicPostfix()
               + WriterUtils::getHexStringFromNumber(exportConfiguration, loadAddress);
    WriterUtils::writeString(outputStream, org);
}

std::vector<juce::String> Disassembler::parsePendingSymbols() noexcept
{
    AreaGenerator areaGenerator(regions, references);
    const auto& symbolsToKeepAndErrorStrings = areaGenerator.fillFromSymbols(pendingSymbols);

    // Any error? Then returns them.
    const auto& errorStrings = symbolsToKeepAndErrorStrings.second;
    if (!errorStrings.empty()) {
        return errorStrings;
    }

    // Stores all the Symbols that were returned: they are not markers and should be visible.
    for (const auto& symbol : symbolsToKeepAndErrorStrings.first) {
        references.storeSymbol(symbol);
    }

    // No errors.
    return {};
}

// SourceItemEncoderAndGeneratedLabelCleaner
// =========================================================

Disassembler::SourceItemEncoderAndGeneratedLabelCleaner::SourceItemEncoderAndGeneratedLabelCleaner(References& pReferences, juce::OutputStream& pOutputStream,
                                                                                                   const ExportConfiguration& pConfiguration) noexcept :
        SourceItemEncoder(pReferences, pOutputStream, pConfiguration)
{
}

void Disassembler::SourceItemEncoderAndGeneratedLabelCleaner::executeAfterVisit() const noexcept
{
    references.deleteUnusedReferences(true);
}


// FakeOutputStream
// =========================================================

void Disassembler::FakeOutputStream::flush()
{
}

bool Disassembler::FakeOutputStream::setPosition(juce::int64 /*newPosition*/)
{
    return true;
}

juce::int64 Disassembler::FakeOutputStream::getPosition()
{
    return 0;
}

bool Disassembler::FakeOutputStream::write(const void* /*dataToWrite*/, size_t /*numberOfBytes*/)
{
    return true;
}

}    // namespace disark
