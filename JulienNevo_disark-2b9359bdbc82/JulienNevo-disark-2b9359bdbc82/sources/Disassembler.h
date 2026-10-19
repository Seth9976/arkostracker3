#pragma once

#include <juce_core/juce_core.h>

#include "base/Regions.h"
#include "BinaryParser.h"
#include "base/References.h"
#include "base/RegionDataHolder.h"
#include "base/Symbol.h"
#include "base/sourceItemVisitor/SourceItemEncoder.h"

namespace disark
{

class ExportConfiguration;

/**
 * This class disassembles the input stream into source.
 */
class Disassembler
{
public:
    friend class DisassemblerTest;                    // For test units.

    /**
     * Constructor.
     * @param exportConfiguration the source configuration to use.
     */
    explicit Disassembler(const ExportConfiguration& exportConfiguration) noexcept;

    /**
     * Sets the start address of the source.
     * @param address the address.
     */
    void setStartAddress(int address) noexcept;

    /**
     * Adds a Region.
     * @param region the Region.
     */
    void addRegion(const Region& region) noexcept;

    /**
     * Adds a symbol (from a symbol file, for example).
     * @param symbol the symbol.
     */
    void addSymbol(const Symbol& symbol) noexcept;

    /**
     * Adds symbols (from a symbol file, for example).
     * @param symbols the symbols.
     */
    void addSymbols(const std::vector<Symbol>& symbols) noexcept;

    /**
     * Disassembles. Parses all the Regions (which must have been set before (via the addRegion method)), and generates the source.
     * @param inputStream the stream to read.
     * @param outputStream the stream where to write the generated source.
     * @return the possible error strings. Empty if no error.
     */
    std::vector<juce::String> disassemble(juce::InputStream& inputStream, juce::OutputStream& outputStream) noexcept;

private:

    /**
     * Adds an ORG directive, if the start address has been set.
     * @param outputStream where to generate the ORG.
     */
    void generateOrgIfNeeded(juce::OutputStream& outputStream) noexcept;

    /** @return the current address, from the pointer in the InputStream and the input address given by the user. */
    int calculateAddress(juce::InputStream& inputStream) const noexcept;

    /**
     * Disassembles all the Regions. They must have been set before (via the addRegion method), else everything is considered as code (which may be what is wanted).
     * @param inputStream the input data.
     * @return the data for each Region, in the order of memory.
     */
    std::vector<std::unique_ptr<RegionDataHolder>> disassembleRegions(juce::InputStream& inputStream) noexcept;

    /**
     * Parses the Symbols previously added. May builds Regions from all the Symbols (they may contain tags such as "DisarkCodeRegionStart", etc.).
     * Obviously, they must have been added first.
     * @return the possible error strings. Empty if no error.
     */
    std::vector<juce::String> parsePendingSymbols() noexcept;

    /**
     * Provides the bytes from the input file.
     */
    class LocalBytesProvider final : public BinaryParser::BytesProvider
    {
    public:
        /** Constructor. */
        explicit LocalBytesProvider(juce::InputStream& inputStream, Disassembler& parent) noexcept;
        int fetchByte() override;
        bool hasNext() override;

    private:
        RegionType regionType;                          // The current Region type.
        juce::InputStream& inputStream;                 // The input file.
        Disassembler& parent;                           // The parent class.
    };

    /** A no-op OutputStream. */
    class FakeOutputStream final : public juce::OutputStream
    {
    public:
        void flush() override;
        bool setPosition(juce::int64 newPosition) override;
        juce::int64 getPosition() override;
        bool write(const void* dataToWrite, size_t numberOfBytes) override;
    };

    /** A SourceItemEncoder, which cleans the generated labels at the end. */
    class SourceItemEncoderAndGeneratedLabelCleaner final : public SourceItemEncoder
    {
    public:
        /**
         * Constructor.
         * @param references holds the references to labels.
         * @param outputStream where to write the generated source.
         * @param configuration the source configuration to use.
         */
        SourceItemEncoderAndGeneratedLabelCleaner(References& references, juce::OutputStream& outputStream, const ExportConfiguration& configuration) noexcept;
        void executeAfterVisit() const noexcept override;
    };

    const ExportConfiguration& exportConfiguration;     // The source configuration to use.
    int loadAddress;                                    // Where the file is loaded. 0 by default.
    Regions regions;                                    // All the Regions.
    References references;                              // All the references (from a reference file for example).

    std::vector<Symbol> pendingSymbols;                 // Accumulated Symbols, ultimately used when the disassembling begins.
};

}    // namespace disark
