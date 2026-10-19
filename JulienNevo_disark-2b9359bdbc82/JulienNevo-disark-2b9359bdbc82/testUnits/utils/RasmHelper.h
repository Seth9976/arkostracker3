#pragma once

#include <memory>

#include <juce_core/juce_core.h>
#include "../../sources/base/Symbol.h"
#include "PlayerType.h"
#include "TargetHardware.h"

namespace disark
{

class RasmHelper
{
public:

    /**
     * Assembles the given MemoryBlock containing Z80 source and returns MemoryBlock containing the binary data.
     * @param source the Z80 source. It WILL be modified if the ORG address is added.
     * @param addedOrgAddress if >=0, an ORG mnemonic with the given address is encoded at the beginning of the source.
     * @param symbolsToFill the possible structure to fill, or nullptr if not interested.
     * @return the MemoryBlock of the Z80 binary, or nullptr if an error occurred (compilation error).
     */
    std::unique_ptr<juce::MemoryBlock> assembleSource(juce::MemoryBlock& source, int addedOrgAddress = -1, std::vector<Symbol>* symbolsToFill = nullptr) noexcept;

    /**
     * Assembles the given MemoryBlock containing Z80 source and returns MemoryBlock containing the binary data.
     * @param source the Z80 source. It WILL be modified if the ORG address is added.
     * @param symbolsToFill the possible structure to fill, or nullptr if not interested.
     * @return the MemoryBlock of the Z80 binary, or nullptr if an error occurred (compilation error).
     */
    std::unique_ptr<juce::MemoryBlock> assembleSourceWithoutAddingOrg(const juce::MemoryBlock& source, std::vector<Symbol>* symbolsToFill = nullptr) noexcept;

    /**
     * @return another MemoryBlock with the "include" commented. They can be either "include "" or "include"", not case sensitive.
     * @param source the source MemoryBlock.
     */
    juce::MemoryBlock commentIncludes(const juce::MemoryBlock& source) noexcept;

    /** Returns the prefix tag (PLY_AKG for example) according to the hardware. */
    juce::String getSourceTagPrefix(PlayerType playerType) noexcept;

    /**
	 * Adds a variable declaration to use the ROM play, at the beginning of the source, and the declaration of the ROM buffer.
	 * @param source the source.
	 * @param sourceTagPrefix the prefix of each source tag (PLY_AKG for example).
     * @param bufferAddress where the ROM buffer is.
     * @param addRomDeclaration if true, adds something, else do not do anything.
	 */
    void addRomPlayerDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, int bufferAddress = 0xf000, bool addRom = true) noexcept;

    /**
     * Adds a hardware declaration, at the beginning of the source.
	 * @param source the source.
	 * @param sourceTagPrefix the prefix of each source tag (PLY_AKG for example).
     * @param targetHardware the hardware.
     */
    void addHardwareDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, TargetHardware targetHardware) noexcept;

    /**
     * Adds a variable declaration at the beginning of the source (example: "<variable> = <value>").
     * @param source the MemoryBlock to add the data to.
     * @param variable the name of the variable.
     * @param value the value after the equal.
     */
    void addVariableDeclaration(juce::MemoryBlock& source, const juce::String& variable, const juce::String& value = "1") noexcept;

    /**
     * Inserts the given MemoryBlock after the line where the Tag is, inside a source MemoryBlock.
     * If not found, an assertion is raised.
     */
    void insertAfterTag(const juce::String& tag, juce::MemoryBlock& source, const juce::MemoryBlock& blockToInsert) noexcept;

};

}    // namespace disark
