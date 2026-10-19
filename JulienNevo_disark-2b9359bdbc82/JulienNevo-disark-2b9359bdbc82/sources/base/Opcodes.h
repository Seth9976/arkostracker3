#pragma once

#include <juce_core/juce_core.h>

#include <map>
#include <vector>

#include "Opcode.h"

namespace disark
{

class ExportConfiguration;

/**
 * Holds all the possible opcodes, as well as search method to find them.
 */
class Opcodes
{
public:
    friend class DisarkBaseTest;                // For test units.
    friend class OpcodesFiller;                 // Class that makes all the somewhat tedious job of filling the opcodes.

    /**
     * Constructor.
     * @param exportConfiguration the configuration for the source export.
     */
    explicit Opcodes(const ExportConfiguration& exportConfiguration) noexcept;

    /**
     * Searches for an opcode which is only composed of the given byte (regardless of the arguments after).
     * @param byte the first byte of the opcode.
     * @return the opcode, or nullptr if none matched.
     */
    const Opcode* search(int byte) const noexcept;

    /**
     * Searches for an opcode which is composed of two bytes (regardless of the arguments after).
     * @param firstByte the first byte of the opcode.
     * @param secondByte the second byte of the opcode.
     * @param errorIllegalCombination true if there is an error, and this error is an illegal combination.
     * @return the opcode, or nullptr if none matched. If errorIllegalCombination is false, it means another opcode is needed.
     */
    const Opcode* search(int firstByte, int secondByte, bool& errorIllegalCombination) const noexcept;

    /**
     * Searches for an opcode which is composed of three bytes (regardless of the arguments after).
     * @param firstByte the first byte of the opcode.
     * @param secondByte the second byte of the opcode.
     * @param thirdByte the second byte of the opcode.
     * @param errorIllegalCombination true if there is an error, and this error is an illegal combination.
     * @return the opcode, or nullptr if none matched. If errorIllegalCombination is false, it means another opcode is needed.
     */
    const Opcode* search(int firstByte, int secondByte, int thirdByte, bool& errorIllegalCombination) const noexcept;

    /** @return the opcodes that start with the given byte. */
    const std::vector<Opcode>& findOpcodesFromFirstByte(int firstByte) const noexcept;

private:
    /**
     * Stores an opcode.
     * @param opcode the opcode.
     */
    void addOpcode(const Opcode& opcode) noexcept;

    /**
     * Parses the expression and builds an opcode (of one byte only) from it. The parser is quite simple, so specific cases (IM 1, etc.) should not use it.
     * @param firstByte the first byte of the opcode.
     * @param expression the expression ("nop", "ld a,N", etc.). Starts with "*" for undocumented opcodes.
     */
    void parseAndAddOpcode(int firstByte, const juce::String& expression) noexcept;

    /**
     * Parses the expression and builds an opcode (of one byte only) from it. The parser is quite simple, so specific cases (IM 1, etc.) should not use it.
     * @param firstByte the first byte of the opcode.
     * @param secondByte the second byte of the opcode.
     * @param expression the expression ("nop", "ld a,N", etc.). Starts with "*" for undocumented opcodes.
     */
    void parseAndAddOpcode(int firstByte, int secondByte, const juce::String& expression) noexcept;
    /**
     * Parses the expression and builds an opcode (of one byte only) from it. The parser is quite simple, so specific cases (IM 1, etc.) should not use it.
     * @param firstByte the first byte of the opcode.
     * @param secondByte the second byte of the opcode.
     * @param thirdByte the second byte of the opcode.
     * @param expression the expression ("nop", "ld a,N", etc.). Starts with "*" for undocumented opcodes.
     */
    void parseAndAddOpcode(int firstByte, int secondByte, int thirdByte, const juce::String& expression) noexcept;

    /**
     * Parses the expression and returns the related Source Items. The parser is quite simple, so specific cases (IM 1, etc.) should not use it.
     * @param expression the expression ("nop", "ld a,N", etc.).
     * @param undocumented set to true if the opcode is officially undocumented.
     * @return the Source Items.
     */
    std::vector<SourceItem> parse(const juce::String& expression, bool& undocumented) const noexcept;

    /**
     * Parses the expression, from the given char index, looking for the next word. "(", ")", "," are separators, but returned as words.
     * @param expression the expression.
     * @param charIndex the char index from where to look. Spaces are skipped at this location. Updated after the word found.
     * @return the word, or empty if nothing could be found.
     */
    static juce::String readNextWord(const juce::String& expression, int& charIndex) noexcept;

    /**
     * Manages some boring special cases, especially for SDCC.
     * If "<opcode> <n/nn>" or ",n" or ",nn", then add an immediate symbol ("#") in between, but only for some specific opcodes (NOT for JP, CALL, etc.).
     * Example: "add a,4", "sub 45", "sbc a,55".
     * @param sourceItems the source items. May be modified.
     */
    static void manageImmediateDataDeclaration(std::vector<SourceItem>& sourceItems) noexcept;

    /**
     * SDCC does not like (IY +d) -> +d (IY).
     * Changes this if relevant for these Source Items.
     * @param sourceItems the source items. May be modified.
     */
    static void manageSdccRelativeRegister(std::vector<SourceItem>& sourceItems) noexcept;

    /**
     * SDCC does not like (IY +d) -> +d (IY). Finds the given sequence of SourceItems (either for IX or IY), and replaces with the other given sequence, if found.
     * Changes this if relevant for these Source Items.
     * @param sourceItems the source items. May be modified.
     * @param sequenceToFind the source items to find.
     * @param replacementSequence the source items to replace by.
     * @return true if found and replaced.
     */
    static bool findAndReplaceIfFoundRelativeRegister(std::vector<SourceItem>& sourceItems, const std::vector<SourceItem>& sequenceToFind,
        const std::vector<SourceItem>& replacementSequence) noexcept;

    const ExportConfiguration& exportConfiguration;                     // The configuration for the source export.
    std::map<int, std::vector<Opcode>> firstByteToOpcodes;              // Links the first byte to the possible opcodes that starts with.
};

}    // namespace disark
