#pragma once

#include <juce_core/juce_core.h>

#include "../../source/disark/base/Symbol.h"
#include "../../source/utils/OptionalValue.h"
#include "z80Emulator/TargetHardware.h"

namespace arkostracker
{

class PlayerConfiguration;

/** Helper class to assemble InputStream and compare them. Handy to perform tests. */
class RasmHelper
{
public:
    /**
     * Assembles the given Z80 sources, and compares the result.
     * @param source1 the Z80 first source.
     * @param source2 the Z80 second source.
     * @param errorOffsets possible offsets where an difference is.
     * @param tolerance on those error offsets (only!), indicates the tolerance.
     * @return true if everything is fine.
     */
    static bool assembleAndCompareSources(const juce::MemoryBlock& source1, const juce::MemoryBlock& source2,
    	const std::unordered_set<int>& errorOffsets = { }, int tolerance = 0) noexcept;

    /**
     * Assembles the given MemoryBlock containing Z80 source and returns MemoryBlock containing the binary data.
     * @param source the Z80 source. It WILL be modified if the ORG address is added.
     * @param addedOrgAddress if present, an ORG mnemonic with the given address is encoded at the beginning of the source.
     * @param symbolsToFill the possible structure to fill, or nullptr if not interested.
     * @return the MemoryBlock of the Z80 binary, or nullptr if an error occurred (compilation error).
     */
    static std::unique_ptr<juce::MemoryBlock> assembleSource(juce::MemoryBlock& source, OptionalInt addedOrgAddress = OptionalInt(),
                                                      std::vector<Symbol>* symbolsToFill = nullptr) noexcept;

    /**
     * Assembles the given MemoryBlock containing Z80 source and returns MemoryBlock containing the binary data.
     * @param source the Z80 source.
     * @param symbolsToFill the possible structure to fill, or nullptr if not interested.
     * @return the MemoryBlock of the Z80 binary, or nullptr if an error occurred (compilation error).
     */
    static std::unique_ptr<juce::MemoryBlock> assembleSourceWithoutAddingOrg(const juce::MemoryBlock& source, std::vector<Symbol>* symbolsToFill = nullptr) noexcept;

    /**
     * Adds the Player Configuration at the beginning of the source.
     * @param source the MemoryBlock to add the data to.
     * @param playerConfiguration the player configuration to add.
     */
    static void addPlayerConfiguration(juce::MemoryBlock& source, const PlayerConfiguration& playerConfiguration) noexcept;

    /**
     * Adds a variable declaration to use the ROM play, at the beginning of the source, and the declaration of the ROM buffer.
     * @param source the source.
     * @param sourceTagPrefix the prefix of each source tag (PLY_AKG for example).
     * @param bufferAddress where the ROM buffer is.
     * @param addRomDeclaration if true, adds something, else do not do anything.
     */
    static void addRomPlayerDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, int bufferAddress = 0xf000, bool addRomDeclaration = true) noexcept;

    /**
     * Adds a hardware declaration, at the beginning of the source.
	 * @param source the source.
	 * @param sourceTagPrefix the prefix of each source tag (PLY_AKG for example).
     * @param targetHardware the hardware.
     */
    static void addHardwareDeclaration(juce::MemoryBlock& source, const juce::String& sourceTagPrefix, TargetHardware targetHardware) noexcept;

	/**
	 * Inserts the given MemoryBlock after the line where the Tag is, inside a source MemoryBlock.
	 * If not found, an assertion is raised.
	 */
	static void insertAfterTag(const juce::String& tag, juce::MemoryBlock& source, const juce::MemoryBlock& blockToInsert) noexcept;
};

}   // namespace arkostracker
