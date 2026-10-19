#pragma once

#include <utility>
#include "../../sources/base/Opcode.h"
#include "../../sources/BinaryParser.h"

namespace disark
{

/** A "wrapper" to a call to disassemble of the Binary Parser, which is private. This class is a friend class. */
class BinaryParserTest
{
public:
    BinaryParserTest(ExportConfiguration& exportConfiguration, BinaryParser::BytesProvider& bytesProvider) :
            disassembler(exportConfiguration, bytesProvider)
    {
    }

    std::pair<Opcode, BinaryParser::ReadResult> readOpcode() noexcept
    {
        return disassembler.readOpcode();
    }

    std::vector<int> readBytesFromParameterType(SourceParameterType type, bool& success) noexcept
    {
        return disassembler.readBytesFromParameterType(type, success);
    }

    std::pair<std::unique_ptr<Instruction>, BinaryParser::ReadResult> readInstruction(const Opcode& opcode) noexcept
    {
        return disassembler.readInstruction(opcode);
    }

    static int buildParameter(std::vector<int> bytes) noexcept
    {
        return BinaryParser::buildParameter(bytes);
    }

private:
    BinaryParser disassembler;
};

}    // namespace disark
