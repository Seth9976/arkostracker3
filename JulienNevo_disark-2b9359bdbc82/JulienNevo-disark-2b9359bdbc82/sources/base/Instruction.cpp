#include "Instruction.h"

namespace disark
{

Instruction::Instruction(Opcode pOpcode, const int pParameter1, const int pParameter2) noexcept :
    opcode(std::move(pOpcode)),
    parameter1(pParameter1),
    parameter2(pParameter2)
{
}

const Opcode& Instruction::getOpcode() const noexcept
{
    return opcode;
}

int Instruction::getParameter1() const noexcept
{
    return parameter1;
}

int Instruction::getParameter2() const noexcept
{
    return parameter2;
}

bool Instruction::isUndocumented() const noexcept
{
    return opcode.isUndocumented();
}

}    // namespace disark
