#pragma once

#include <utility>
#include "../../sources/base/Opcode.h"
#include "../../sources/BinaryParser.h"
#include "../../sources/Disassembler.h"

namespace disark
{

/** A "wrapper" to a call to disassemble of the Binary Parser, which is private. This class is a friend class. */
class DisassemblerTest
{
public:
    explicit DisassemblerTest(ExportConfiguration& exportConfiguration) :
            disassembler(exportConfiguration)
    {
    }

    std::vector<std::unique_ptr<RegionDataHolder>> disassembleRegions(juce::InputStream& inputStream) noexcept
    {
        return disassembler.disassembleRegions(inputStream);
    }

    void addRegion(const Region& region) noexcept
    {
        disassembler.addRegion(region);
    }

    void setStartAddress(int address) noexcept
    {
        disassembler.setStartAddress(address);
    }

    /**
     * Adds a symbol (from a symbol file, for example).
     * @param symbol the symbol.
     */
    void addSymbol(const Symbol& symbol) noexcept
    {
        disassembler.addSymbol(symbol);
    }

    References& references() noexcept
    {
        return disassembler.references;
    }

    std::vector<juce::String> disassemble(juce::InputStream& inputStream, juce::OutputStream& outputStream) noexcept
    {
        return disassembler.disassemble(inputStream, outputStream);
    }

private:
    Disassembler disassembler;
};

}    // namespace disark
