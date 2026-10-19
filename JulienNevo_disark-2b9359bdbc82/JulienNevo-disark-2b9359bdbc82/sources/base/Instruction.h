#pragma once

#include "Opcode.h"

namespace disark
{

/**
 * An instruction, which consists of an opcode and zero, one or two parameters (16 bits number, 8 bits number, etc.).
 */
class Instruction
{
public:
    /**
     * Constructor.
     * @param opcode the underlying opcode.
     * @param parameter1 the parameter, always positive, or -1 if not present.
     * @param parameter2 the parameter, always positive, or -1 if not present.
     */
    explicit Instruction(Opcode opcode, int parameter1 = -1, int parameter2 = -1) noexcept;

    /** @return the opcode. */
    const Opcode& getOpcode() const noexcept;
    /** @return the first parameter, always positive, or -1 if not present. */
    int getParameter1() const noexcept;
    /** @return the second parameter, always positive, or -1 if not present. */
    int getParameter2() const noexcept;

    /** @return true if the opcode is undocumented (officially). */
    bool isUndocumented() const noexcept;

private:
    const Opcode opcode;                        // The inner opcode.
    int parameter1;                             // The first parameter, always positive, or -1 if not present.
    int parameter2;                             // The second parameter, always positive, or -1 if not present.
};

}    // namespace disark
