#pragma once

#include <vector>

#include <juce_core/juce_core.h>

namespace disark
{

class ExportConfiguration;
class Opcodes;

/** Class that fills the opcodes. Rather tedious... */
class OpcodesFiller
{
public:
    /**
     * Constructor.
     * @param exportConfiguration the configuration for the source export.
     * @param opcodes the Opcodes object to fill.
     */
    OpcodesFiller(const ExportConfiguration& exportConfiguration, Opcodes& opcodes);

    /**
     * Fills the opcodes inside the Opcodes object, which is a friend class.
     */
    void fillOpcodes() noexcept;

private:

    /**
     * Parses each expression and creates the related opcodes.
     * @param firstOpcode the first opcode byte, will be incremented each time.
     * @param expressions the expressions.
     */
    void parseExpressionsAndAddOpcodes(int firstOpcode, const std::vector<juce::String>& expressions) noexcept;

    /**
     * Parses each expression and creates the related opcodes.
     * @param firstOpcode the first opcode byte.
     * @param secondOpcode the second opcode byte, will be incremented each time.
     * @param expressions the expressions.
     */
    void parseExpressionsAndAddOpcodes(int firstOpcode, int secondOpcode, const std::vector<juce::String>& expressions) noexcept;

    /**
     * Parses each expression and creates the related opcodes.
     * @param firstOpcode the first opcode byte.
     * @param secondOpcode the second opcode byte.
     * @param thirdOpcode the third opcode byte, will be incremented each time.
     * @param expressions the expressions.
     */
    void parseExpressionsAndAddOpcodes(int firstOpcode, int secondOpcode, int thirdOpcode, const std::vector<juce::String>& expressions) noexcept;

    const ExportConfiguration& exportConfiguration;         // The configuration for the source export.
    Opcodes& opcodes;                                       // The Opcodes object to fill.
};

}    // namespace disark
