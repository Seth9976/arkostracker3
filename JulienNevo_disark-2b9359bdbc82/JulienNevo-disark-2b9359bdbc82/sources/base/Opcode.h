#pragma once

#include <juce_core/juce_core.h>

#include "SourceParameterType.h"
#include "SourceItem.h"

namespace disark
{

/**
 * An opcode. They normally do NOT hold the parameters (+5, #4000, etc.) see Instructions for that.
 * HOWEVER, since 3-bytes opcodes have a signed index in the 3 bytes (opcode-opcode-signed index-opcode),
 * it was much simpler to store this, exceptionally, and only for this case.
 */
class Opcode
{
public:
    friend class TestDisarkBase;                      // For test units.
    friend class TestDisark;                          // For test units.

    /**
     * Constructor for opcodes with one byte.
     * @param singleOpcode the opcode.
     * @param sourceItems the source items this opcode is composed of.
     * @param undocumented true if the opcode is undocumented (officially).
     */
    Opcode(int singleOpcode, std::vector<SourceItem> sourceItems, bool undocumented = false) noexcept;

    /**
     * Constructor for opcodes with one prefix.
     * @param firstByte the first byte (a prefix, #dd for example).
     * @param secondByte the second byte (#09 for ADD IX,BC).
     * @param sourceItems the source items this opcode is composed of.
     * @param undocumented true if the opcode is undocumented (officially).
     */
    Opcode(int firstByte, int secondByte, std::vector<SourceItem> sourceItems, bool undocumented = false) noexcept;

    /**
     * Constructor for three bytes opcodes. The signed index they all possess must be set via a setter.
     * @param firstByte the first byte (#dd for example).
     * @param secondByte the second byte (#cb for example).
     * @param thirdByte the third byte (#06 for RLC (ix+d) for example).
     * @param sourceItems the source items this opcode is composed of.
     * @param undocumented true if the opcode is undocumented (officially).
     */
    Opcode(int firstByte, int secondByte, int thirdByte, std::vector<SourceItem> sourceItems, bool undocumented = false) noexcept;

    /** @return an Opcode for errors. */
    static Opcode buildError() noexcept;

    /**
     * Indicates whether the opcode matches the first and second bytes, without checking the third.
     * @param firstByte the first byte.
     * @param secondByte the second byte.
     * @return true if the opcode matches.
     */
    bool match(int firstByte, int secondByte) const noexcept;

    /**
     * Indicates whether the opcode matches the first, second and third bytes.
     * @param firstByte the first byte.
     * @param secondByte the second byte.
     * @param thirdByte the third byte.
     * @return true if the opcode matches.
     */
    bool match(int firstByte, int secondByte, int thirdByte) const noexcept;

    /** @return the first byte (0 for nop, 0xc3 for JP, #ed for out (c),0. */
    int getFirstByte() const noexcept;
    /** @return the second byte, or -1 if there is none (#71 for out (c),0 for example). */
    int getSecondByte() const noexcept;
    /** @return the third byte, or -1 if there is none (#06 for RLC (ix+d) for example). */
    int getThirdByte() const noexcept;

    /** @return the type of the first parameter. If not known yet, it is determined. */
    SourceParameterType getParameterType1() const noexcept;
    /** @return the type of the second parameter. If not known yet, it is determined. */
    SourceParameterType getParameterType2() const noexcept;

    /**
     * @return the bytes that this opcode consists of (only the opcode of course, nothing about the parameters, EXCEPT for the three-byte opcode,
     * which also contains the signed index in the third position). */
    std::vector<int> getOpcodeBytes() const noexcept;

    /** @return the SourceItems that compose this opcode. */
    const std::vector<SourceItem>& getSourceItems() const noexcept;

    /** @return how many bytes are required to encode this opcode, with the parameters. */
    int getEncodedSizeWithParameter() const noexcept;

    /** @return true if this is a three-bytes opcodes. This means a signed-index is ALWAYS encoded in the 3 position, before the third byte. Yeeeah. */
    bool isThreeBytesOpcode() const noexcept;

    /** @return the signed index, in the code this is a three-byte opcode. And only in this case! */
    int getSignedIndexForThreeBytesOpcode() const noexcept;

    /**
     * Sets the signed index the 3-byte opcode always have.
     * @param signedIndex the index (0-255).
     */
    void setSignedIndexForThreeBytesOpcode(int signedIndex) noexcept;

    /** @return true if the opcode is undocumented (officially). */
    bool isUndocumented() const noexcept;

private:
    /** Determines the inner type of parameter this opcode may hold. */
    void determineParameterTypes() noexcept;

    /**
     * Sets the Parameter Type of a parameter from its index.
     * @param parameterIndex must be 0 or 1.
     * @param parameterType the type of the parameter.
     */
    void setParameterType(int parameterIndex, SourceParameterType parameterType) noexcept;

    /**
     * Returns how many bytes are needed to encode the parameter which type is given.
     * @param parameterType the parameter type.
     * @return the byte count.
     */
    static int getParameterEncodingSize(SourceParameterType parameterType) noexcept;

    /** @return how many bytes are composing the opcode (NOT the parameters!). */
    int getOpcodeSize() const noexcept;

    int firstByte;                              // The first byte (0 for nop, 0xc3 for JP, #ed for out (c),0.
    int secondByte;                             // The second byte, or -1 if there is none (#71 for out (c),0 for example).
    int thirdByte;                              // The third byte, or -1 if there is none (#06 for RLC (ix+d) for example).

    int signedIndexForThreeBytesOpcodes;        // Only if this is a 3-byte opcode, the signed index is stored here. Else, -1.

    std::vector<SourceItem> sourceItems;        // Each component of the opcode (ld, (, de, ), etc.).

    SourceParameterType parameterType1;         // The type of the possible first parameter. May be not present.
    SourceParameterType parameterType2;         // The type of the possible first parameter. May be not present.

    bool undocumented;                          // True if the opcode is undocumented (officially).
};

}    // namespace disark
