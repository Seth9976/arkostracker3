#pragma once

#include <vector>

#include "Instruction.h"
#include "ExportConfiguration.h"

namespace disark
{

class SourceItemVisitor;

/**
 * Abstract class representing the data (instructions, left over bytes) for each Region.
 */
class RegionDataHolder
{
public:
    explicit RegionDataHolder(int startAddress);

    /** Destructor. */
    virtual ~RegionDataHolder() = default;

    /** @return where the region starts. */
    int getStartAddress() const;

    /**
     * Parses source items, and given them to the visitor, which might generating a source, or find labels, etc..
     * @param sourceItemVisitor the SourceItemVisitor to use.
     */
    virtual void parseSourceItems(SourceItemVisitor& sourceItemVisitor) const noexcept = 0;

private:
    int startAddress;                               // Where the region starts.
};




/** Holds the data (instructions, etc.) that belong to a Code Region. */
class CodeRegionDataHolder final : public RegionDataHolder
{
public:
    /**
     * Constructor.
     * @param startAddress the start address for this region.
     * @param instructionAndLeftOverBytes the Instructions, and the bytes we couldn't encode as instructions.
     * @param undocumentedOpcodesAsBytes true if undocumented opcodes must be encoded as "db".
     */
    CodeRegionDataHolder(int startAddress, std::pair<std::vector<Instruction>, std::vector<int>> instructionAndLeftOverBytes, bool undocumentedOpcodesAsBytes) noexcept;

    /** @return the instructions. */
    const std::vector<Instruction>& getInstructions() const;
    /** @return the bytes we couldn't encode as instructions. */
    const std::vector<int>& getLeftOverBytes() const;

    void parseSourceItems(SourceItemVisitor& sourceItemVisitor) const noexcept override;

private:
    std::vector<Instruction> instructions;          // The instructions.
    std::vector<int> leftOverBytes;                 // The bytes we couldn't encode as instructions.
    bool undocumentedOpcodesAsBytes;                // True if undocumented opcodes must be encoded as "db".
};




/** Holds the bytes that belong to a Byte Region. */
class ByteRegionDataHolder final : public RegionDataHolder
{
public:
    /**
     * Constructor.
     * @param startAddress the start address for this region.
     * @param bytes the bytes.
     */
    ByteRegionDataHolder(int startAddress, std::vector<int> bytes) noexcept;

    /** @return the bytes. */
    const std::vector<int>& getBytes() const noexcept;

    void parseSourceItems(SourceItemVisitor& sourceItemVisitor) const noexcept override;

private:
    std::vector<int> bytes;                             // The found bytes.
};


/** Holds the pointers (16 bits) that belong to a Pointer Region, and a possible left-over. */
class PointerRegionDataHolder final : public RegionDataHolder
{
public:
    /**
     * Constructor.
     * @param startAddress the start address for this region.
     * @param wordsAndLeftOver the words, and a possible leftOver (-1 if not present).
     * @param referenceCanBeInferred true if it is possible to infer references from the words. False to produce only DW <value> for example.
     */
    PointerRegionDataHolder(int startAddress, const std::pair<std::vector<int>, int>& wordsAndLeftOver, bool referenceCanBeInferred) noexcept;

    /** @return the words. */
    const std::vector<int>& getWords() const noexcept;
    /** @return the left-over, or -1 if not present. */
    int getLeftOver() const;

    void parseSourceItems(SourceItemVisitor& sourceItemVisitor) const noexcept override;

private:
    std::vector<int> words;                             // The found pointers/words.
    int leftOver;                                       // The possible left over, or -1 if not present.
    bool referenceCanBeInferred;                        // True if it is possible to infer references from the words.
};

}    // namespace disark
