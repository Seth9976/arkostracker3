#pragma once

#include <vector>

#include <juce_core/juce_core.h>

#include "SourceItemVisitor.h"
#include "../ReferencingType.h"

namespace disark
{

class ExportConfiguration;
class References;

/**
 * Visitor that encodes to source the given Source Items. It can be parameterized to display instructions in any way.
 */
class SourceItemEncoder : public SourceItemVisitor
{
public:
    /**
     * Constructor.
     * @param references holds the references to labels.
     * @param outputStream where to write the generated source.
     * @param configuration the source configuration to use.
     */
    SourceItemEncoder(References& references, juce::OutputStream& outputStream, const ExportConfiguration& configuration) noexcept;

    void visitInstruction(int address, int instructionSize, const std::vector<SourceItem>& sourceItems, int parameter1Value, int parameter2Value) const noexcept override;
    void executeAfterVisit() const noexcept override;

private:
    /**
     * Encodes an 8-bit unsigned value. May be decimal or hexadecimal.
     * @param value the value, positive.
     * @return the String.
     */
    juce::String encode8BitsNumber(int value) const noexcept;
    /**
     * Encodes an 8-bit unsigned value as a signed value, always as a decimal.
     * @param value the value, positive.
     * @return the String, may be negative. Even if positive, always has a sign.
     */
    juce::String encodeUnsigned8BitsToSignedNumber(int value) const noexcept;

    /**
     * Encodes an 8-bit signed value, always as a decimal.
     * @param value the value, positive.
     * @return the String, may be negative. Even if positive, always has a sign.
     */
    juce::String encodeSigned8BitsToNumber(int value) const noexcept;

    /**
     * Encodes an 8-bit unsigned value. May be decimal or hexadecimal, or can be transformed into a reference, with an index or not (e.g. "Label + 1").
     * @param address the address.
     * @param value the value, positive.
     * @return the String.
     */
    juce::String encode8BitRelativeJump(int address, int value) const noexcept;

    /**
     * Encodes a 16-bit unsigned value. May be decimal or hexadecimal, or can be transformed into a reference, with an index or not (e.g. "Label + 1").
     * @param value the value, positive.
     * @param referencingType indicates if references can be inferred, must be, or never.
     * @return the String.
     */
    juce::String encode16BitsNumber(int value, ReferencingType referencingType) const noexcept;

    /**
     * Checks whether one or more labels must be written, and do so if needed.
     * @param startAddress the address of the instruction.
     * @param instructionSize the size of the instruction (parameter included), in bytes.
     * @param forceReturnCarriageAfterLabel true to add a Return carriage after the last label is added. Also adds a tabulation to allow an instruction afterward.
     * @return the last sentence started, so that the instruction can be written after. May be empty.
     */
    juce::String manageLabels(int startAddress, int instructionSize, bool forceReturnCarriageAfterLabel) const noexcept;

    /**
     * Manages the possible comment, if wanted (shows the address).
     * @param address the address of the instruction.
     * @param result the currently build String.
     */
    void manageComments(int address, juce::String& result) const noexcept;

    /**
     * Checks whether the given address can be linked with a reference. If yes, a String with a possible offset is returned, so be added as-is in the source.
     * If a reference is found, it is noted as "referred to".
     * @param address the address.
     * @param forceReferencing true to force a reference. The closest label will be chosen, even if far away.
     * @return the String, or empty if no label could be found.
     */
    juce::String tryToGetReferenceAndIncreaseReferenceCounter(int address, bool forceReferencing = false) const noexcept;

    const ExportConfiguration& configuration;                               // The source configuration to use.
    juce::OutputStream& outputStream;                                       // Where to write the generated source.
};

}    // namespace disark
