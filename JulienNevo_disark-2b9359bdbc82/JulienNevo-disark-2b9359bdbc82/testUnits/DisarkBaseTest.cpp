#include "catch.hpp"

#include "../sources/base/ExportConfiguration.h"
#include "../sources/Disassembler.h"
#include "utils/MemoryBlockUtil.h"
#include "utils/BinaryParserTest.h"
#include "../sources/base/AreaGenerator.h"
#include "utils/DisassemblerTest.h"

namespace disark
{

// A wrapper around the "parse" call, as it is private. Declared as a friend class in Opcodes.cpp.
class DisarkBaseTest {
public:
    explicit DisarkBaseTest(Opcodes& pOpcodes) :
            opcodes(pOpcodes)
    {}

    std::vector<SourceItem> parse(const juce::String& pString, bool& pUndocumented) const {
        return opcodes.parse(pString, pUndocumented);
    }

    Opcodes& opcodes;
};




class LocalBytesProvider : public BinaryParser::BytesProvider
{
public:
    explicit LocalBytesProvider(std::vector<int> pBytes) :
            bytes(std::move(pBytes)),
            index(0)
    {
    }
    int fetchByte() override
    {
        // Returns bytes as much as possible.
        const auto result = hasNext() ? bytes.at(index) : -1;
        ++index;
        return result;
    }

    bool hasNext() override
    {
        return (index < bytes.size());
    }

    void reset() {
        index = 0;
    }

    std::vector<int> bytes;
    size_t index;
};







// =========================================================








TEST_CASE("Disark, opcodes_parse", "[Disark]")
{
    bool undocumented;
    ExportConfiguration exportConfiguration;
    Opcodes opcodes(exportConfiguration);
    DisarkBaseTest test(opcodes);
    REQUIRE(test.parse("nop", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeNop });
    REQUIRE(test.parse("ld a,n", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeLd, SourceItem::registerA, SourceItem::comma, SourceItem::value8Bits });
    REQUIRE(test.parse("ld hl,nn", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeLd, SourceItem::registerHL, SourceItem::comma, SourceItem::value16Bits });
    REQUIRE(test.parse("ex af,af'", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeEx, SourceItem::registerAF, SourceItem::comma, SourceItem::registerAFs });
    REQUIRE(test.parse("jr z,+e", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeJr, SourceItem::flagZ, SourceItem::comma, SourceItem::relativeJump8Bits });
    REQUIRE(test.parse("djnz +e", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeDjnz, SourceItem::relativeJump8Bits});
    REQUIRE(test.parse("LD (BC),A", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeLd, SourceItem::openParenthesis, SourceItem::registerBC, SourceItem::closeParenthesis,
                                                                                SourceItem::comma, SourceItem::registerA });
    REQUIRE(test.parse("im 0", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeIm, SourceItem::decorative0 });
    REQUIRE(test.parse("BIT 0,B", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeBit, SourceItem::decorative0, SourceItem::comma, SourceItem::registerB });
    REQUIRE(test.parse("rst 56", undocumented) == std::vector<SourceItem>{ SourceItem::opcodeRst, SourceItem::decorative56 });
}

TEST_CASE("Disark, ReadOpcode_Nop", "[Disark]")
{
    LocalBytesProvider bytesProvider({ 0x00 });

    ExportConfiguration exportConfiguration;
    BinaryParserTest tester(exportConfiguration, bytesProvider);

    auto opcodeAndResult = tester.readOpcode();

    REQUIRE(opcodeAndResult.second.isSuccess());
    auto opcode = opcodeAndResult.first;
    REQUIRE(opcode.getFirstByte() == 0x00);
    REQUIRE(opcode.getSecondByte() == -1);
    REQUIRE(opcode.getThirdByte() == -1);
}

TEST_CASE("Disark, ReadOpcode_TwoBytesOpcode", "[Disark]")
{
    LocalBytesProvider bytesProvider({ 0xdd, 0x09 });

    ExportConfiguration exportConfiguration;
    BinaryParserTest binaryParserTest(exportConfiguration, bytesProvider);
    auto opcodeAndResult = binaryParserTest.readOpcode();

    REQUIRE(opcodeAndResult.second.isSuccess());
    auto opcode = opcodeAndResult.first;
    REQUIRE(opcode.getFirstByte() == 0xdd);
    REQUIRE(opcode.getSecondByte() == 0x09);
    REQUIRE(opcode.getThirdByte() == -1);
}

TEST_CASE("Disark, ReadOpcode_ThreeBytesOpcode", "[Disark]")
{
    // Opcode, opcode, signed index, opcode.
    LocalBytesProvider bytesProvider({ 0xdd, 0xcb, 0x1, 0x0e });

    ExportConfiguration exportConfiguration;
    BinaryParserTest binaryParserTest(exportConfiguration, bytesProvider);
    auto opcodeAndResult = binaryParserTest.readOpcode();

    REQUIRE(opcodeAndResult.second.isSuccess());
    auto opcode = opcodeAndResult.first;
    REQUIRE(opcode.getFirstByte() == 0xdd);
    REQUIRE(opcode.getSecondByte() == 0xcb);
    REQUIRE(opcode.getThirdByte() == 0x0e);
    REQUIRE(opcode.isThreeBytesOpcode());
    REQUIRE(opcode.getSignedIndexForThreeBytesOpcode() == 0x1);
}

TEST_CASE("Disark, ReadOpcode_TwoBytesIllegal", "[Disark]")
{
    LocalBytesProvider bytesProvider({ 0xdd, 0x08 });

    ExportConfiguration exportConfiguration;
    BinaryParserTest binaryParserTest(exportConfiguration, bytesProvider);
    auto opcodeAndResult = binaryParserTest.readOpcode();

    REQUIRE(!opcodeAndResult.second.isSuccess());
    auto opcode = opcodeAndResult.first;
    REQUIRE(opcode.getFirstByte() == -1);
    REQUIRE(opcode.getSecondByte() == -1);
    REQUIRE(opcode.getThirdByte() == -1);
}


TEST_CASE("Disark, ReadOpcode_CantReadOneByte", "[Disark]")
{
    LocalBytesProvider bytesProvider({ -1 });

    ExportConfiguration exportConfiguration;
    BinaryParserTest binaryParserTest(exportConfiguration, bytesProvider);
    auto opcodeAndResult = binaryParserTest.readOpcode();

    REQUIRE(!opcodeAndResult.second.isSuccess());
    REQUIRE(opcodeAndResult.second.getReadBytesIfError().empty());
    auto opcode = opcodeAndResult.first;
    REQUIRE(opcode.getFirstByte() == -1);
    REQUIRE(opcode.getSecondByte() == -1);
    REQUIRE(opcode.getThirdByte() == -1);
}

TEST_CASE("Disark, ReadOpcode_CantReadTwoBytes", "[Disark]")
{
    LocalBytesProvider bytesProvider({ 0xdd, -1 });

    ExportConfiguration exportConfiguration;
    BinaryParserTest binaryParserTest(exportConfiguration, bytesProvider);
    auto opcodeAndResult = binaryParserTest.readOpcode();

    REQUIRE(!opcodeAndResult.second.isSuccess());
    REQUIRE(opcodeAndResult.second.getReadBytesIfError() == std::vector<int> { 0xdd });
    auto opcode = opcodeAndResult.first;
    REQUIRE(opcode.getFirstByte() == -1);
    REQUIRE(opcode.getSecondByte() == -1);
    REQUIRE(opcode.getThirdByte() == -1);
}

TEST_CASE("Disark, ReadOpcode_CantReadThreeBytes", "[Disark]")
{
    LocalBytesProvider bytesProvider({ 0xfd, 0xcb, -1 });

    ExportConfiguration exportConfiguration;
    BinaryParserTest binaryParserTest(exportConfiguration, bytesProvider);
    auto opcodeAndResult = binaryParserTest.readOpcode();

    REQUIRE(!opcodeAndResult.second.isSuccess());
    REQUIRE(opcodeAndResult.second.getReadBytesIfError() == std::vector<int> { 0xfd, 0xcb });
    auto opcode = opcodeAndResult.first;
    REQUIRE(opcode.getFirstByte() == -1);
    REQUIRE(opcode.getSecondByte() == -1);
    REQUIRE(opcode.getThirdByte() == -1);
}


// ====================================================================

TEST_CASE("Disark, Opcodes_OneByteOpcode", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Opcodes opcodes(exportConfiguration);

    {
        const Opcode* opcode = opcodes.search(0x00);
        REQUIRE(opcode != nullptr);
        REQUIRE(opcode->getFirstByte() == 0x00);
        REQUIRE(opcode->getSecondByte() == -1);
        REQUIRE(opcode->getThirdByte() == -1);
    }

    {
        const Opcode* opcode = opcodes.search(0x10);
        REQUIRE(opcode != nullptr);
        REQUIRE(opcode->getFirstByte() == 0x10);
        REQUIRE(opcode->getSecondByte() == -1);
        REQUIRE(opcode->getThirdByte() == -1);
    }
}

TEST_CASE("Disark, OneByteOpcode_MoreByteNeeded", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Opcodes opcodes(exportConfiguration);

    {
        const Opcode* opcode = opcodes.search(0xdd);
        REQUIRE(opcode == nullptr);
    }
    {
        const Opcode* opcode = opcodes.search(0xfd);
        REQUIRE(opcode == nullptr);
    }
}

TEST_CASE("Disark, Opcodes_TwoBytesOpcode", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Opcodes opcodes(exportConfiguration);

    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0x09, errorIllegalCombination);
        REQUIRE(opcode != nullptr);
        REQUIRE(!errorIllegalCombination);
        REQUIRE(opcode->getFirstByte() == 0xdd);
        REQUIRE(opcode->getSecondByte() == 0x09);
        REQUIRE(opcode->getThirdByte() == -1);
    }

    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0x26, errorIllegalCombination);
        REQUIRE(opcode != nullptr);
        REQUIRE(!errorIllegalCombination);
        REQUIRE(opcode->getFirstByte() == 0xdd);
        REQUIRE(opcode->getSecondByte() == 0x26);
        REQUIRE(opcode->getThirdByte() == -1);
    }
}

TEST_CASE("Disark, Opcodes_TwoBytesOpcode_Illegal", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Opcodes opcodes(exportConfiguration);
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0x00, errorIllegalCombination);
        REQUIRE(opcode == nullptr);
        REQUIRE(errorIllegalCombination);
    }
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0xc6, errorIllegalCombination);
        REQUIRE(opcode == nullptr);
        REQUIRE(errorIllegalCombination);
    }
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0xff, errorIllegalCombination);
        REQUIRE(opcode == nullptr);
        REQUIRE(errorIllegalCombination);
    }
}

TEST_CASE("Disark, Opcodes_TwoBytesOpcode_MoreByteNeeded", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Opcodes opcodes(exportConfiguration);
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0xcb, errorIllegalCombination);
        REQUIRE(opcode == nullptr);
        REQUIRE(!errorIllegalCombination);
    }
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xfd, 0xcb, errorIllegalCombination);
        REQUIRE(opcode == nullptr);
        REQUIRE(!errorIllegalCombination);
    }
}

TEST_CASE("Disark, Opcodes_ThreeBytesOpcode_Match", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    Opcodes opcodes(exportConfiguration);
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0xcb, 0x06, errorIllegalCombination);
        REQUIRE(opcode != nullptr);
        REQUIRE(!errorIllegalCombination);
        REQUIRE(opcode->getFirstByte() == 0xdd);
        REQUIRE(opcode->getSecondByte() == 0xcb);
        REQUIRE(opcode->getThirdByte() == 0x06);
    }
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xdd, 0xcb, 0x0e, errorIllegalCombination);
        REQUIRE(opcode != nullptr);
        REQUIRE(!errorIllegalCombination);
        REQUIRE(opcode->getFirstByte() == 0xdd);
        REQUIRE(opcode->getSecondByte() == 0xcb);
        REQUIRE(opcode->getThirdByte() == 0x0e);
    }
    {
        bool errorIllegalCombination;
        const Opcode* opcode = opcodes.search(0xfd, 0xcb, 0x0e, errorIllegalCombination);
        REQUIRE(opcode != nullptr);
        REQUIRE(!errorIllegalCombination);
        REQUIRE(opcode->getFirstByte() == 0xfd);
        REQUIRE(opcode->getSecondByte() == 0xcb);
        REQUIRE(opcode->getThirdByte() == 0x0e);
    }
}

TEST_CASE("Disark, Opcode_determineSourceParameterType", "[Disark]")
{
    // No parameter.
    {
        Opcode opcode(0, { SourceItem::opcodeNop });
        REQUIRE(SourceParameterType::absent == opcode.getParameterType1());
        REQUIRE(SourceParameterType::absent == opcode.getParameterType2());
    }

    // All the following instructions are fake!!! It does not matter!
    // One parameter.
    {
        Opcode opcode(0, { SourceItem::opcodeLd, SourceItem::registerHL, SourceItem::comma, SourceItem::value16Bits });
        REQUIRE(SourceParameterType::number16bits == opcode.getParameterType1());
        REQUIRE(SourceParameterType::absent == opcode.getParameterType2());
    }
    {
        Opcode opcode(0x10, { SourceItem::opcodeLd, SourceItem::registerA, SourceItem::comma, SourceItem::value8Bits });
        REQUIRE(SourceParameterType::number8bits == opcode.getParameterType1());
        REQUIRE(SourceParameterType::absent == opcode.getParameterType2());
    }
    {
        Opcode opcode(0x20, { SourceItem::opcodeJr, SourceItem::relativeJump8Bits });
        REQUIRE(SourceParameterType::relativeJump8bits == opcode.getParameterType1());
        REQUIRE(SourceParameterType::absent == opcode.getParameterType2());
    }
    {
        Opcode opcode(0x30, { SourceItem::opcodeLd, SourceItem::registerIX, SourceItem::signedIndex8Bits });
        REQUIRE(SourceParameterType::signed8bitsIndex == opcode.getParameterType1());
        REQUIRE(SourceParameterType::absent == opcode.getParameterType2());
    }

    // Two parameters.
    {
        Opcode opcode(0x40, { SourceItem::opcodeLd, SourceItem::value16Bits, SourceItem::registerDE, SourceItem::signedIndex8Bits });
        REQUIRE(SourceParameterType::number16bits == opcode.getParameterType1());
        REQUIRE(SourceParameterType::signed8bitsIndex == opcode.getParameterType2());
    }
    {
        Opcode opcode(0x40, { SourceItem::opcodeEx, SourceItem::value8Bits, SourceItem::relativeJump8Bits });
        REQUIRE(SourceParameterType::number8bits == opcode.getParameterType1());
        REQUIRE(SourceParameterType::relativeJump8bits == opcode.getParameterType2());
    }
    {
        Opcode opcode(0x50, { SourceItem::opcodeEx, SourceItem::openParenthesis, SourceItem::signedIndex8Bits, SourceItem::closeParenthesis, SourceItem::value16Bits });
        REQUIRE(SourceParameterType::signed8bitsIndex == opcode.getParameterType1());
        REQUIRE(SourceParameterType::number16bits == opcode.getParameterType2());
    }
    {
        Opcode opcode(0xff, { SourceItem::opcodeDaa, SourceItem::value8Bits, SourceItem::value8Bits });
        REQUIRE(SourceParameterType::number8bits == opcode.getParameterType1());
        REQUIRE(SourceParameterType::number8bits == opcode.getParameterType2());
    }
}

TEST_CASE("Disark, opcode_getOpcodeBytes", "[Disark]")
{
    // These instructions are all fake, it does not matter!
    {
        Opcode opcode(0, { SourceItem::opcodeEx });
        REQUIRE(opcode.getOpcodeBytes() == std::vector<int>{ 0 });
    }
    {
        Opcode opcode(0x50, { SourceItem::opcodeEx });
        REQUIRE(opcode.getOpcodeBytes() == std::vector<int>{ 0x50 });
    }
    {
        Opcode opcode(0x50, 0xdd, { SourceItem::opcodeEx, SourceItem::value8Bits });
        REQUIRE(opcode.getOpcodeBytes() == std::vector<int>{ 0x50, 0xdd });
    }
    {
        Opcode opcode(0x50, 0xdd, 0xff, { SourceItem::opcodeLdir });
        opcode.setSignedIndexForThreeBytesOpcode(5);
        REQUIRE(opcode.getOpcodeBytes() == std::vector<int>{ 0x50, 0xdd, 5, 0xff });
    }
}

TEST_CASE("Disark, binaryParser_readBytesFromParameterType", "[Disark]")
{
    LocalBytesProvider bytesProvider({ 0x12, 0x34 });

    ExportConfiguration exportConfiguration;
    BinaryParserTest disassembler(exportConfiguration, bytesProvider);
    bool success;

    {
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::number16bits, success);
        REQUIRE(success);
        REQUIRE(readBytes == std::vector<int>{0x12, 0x34});
    }
    {
        bytesProvider.reset();
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::signed8bitsIndex, success);
        REQUIRE(success);
        REQUIRE(readBytes == std::vector<int>{ 0x12 });
    }
    {
        bytesProvider.reset();
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::relativeJump8bits, success);
        REQUIRE(success);
        REQUIRE(readBytes == std::vector<int>{ 0x12 });
    }
    {
        bytesProvider.reset();
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::number8bits, success);
        REQUIRE(success);
        REQUIRE(readBytes == std::vector<int>{ 0x12 });
    }
    {
        bytesProvider.reset();
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::absent, success);
        REQUIRE(success);
        REQUIRE(readBytes.empty());
    }
}

TEST_CASE("Disark, binaryParser_readBytesFromParameterType_NotEnoughData_16bits", "[Disark]")
{
    {
        LocalBytesProvider bytesProvider({0x12});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);
        bool success;

        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::number16bits, success);
        REQUIRE(!success);
        REQUIRE(readBytes == std::vector<int>{0x12});
    }

    {
        LocalBytesProvider bytesProvider({});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);
        bool success;

        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::number16bits, success);
        REQUIRE(!success);
        REQUIRE(readBytes.empty());
    }
}


TEST_CASE("Disark, binaryParser_readBytesFromParameterType_NotEnoughData_8bits", "[Disark]")
{
    LocalBytesProvider bytesProvider({});
    ExportConfiguration exportConfiguration;
    BinaryParserTest disassembler(exportConfiguration, bytesProvider);
    bool success;

    {
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::number8bits, success);
        REQUIRE(!success);
        REQUIRE(readBytes.empty());
    }
    {
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::relativeJump8bits, success);
        REQUIRE(!success);
        REQUIRE(readBytes.empty());
    }
    {
        auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::signed8bitsIndex, success);
        REQUIRE(!success);
        REQUIRE(readBytes.empty());
    }
}

TEST_CASE("Disark, binaryParser_readBytesFromParameterType_EnoughDataForAbsent", "[Disark]")
{
    LocalBytesProvider bytesProvider({});
    ExportConfiguration exportConfiguration;
    BinaryParserTest disassembler(exportConfiguration, bytesProvider);
    bool success;

    auto readBytes = disassembler.readBytesFromParameterType(SourceParameterType::absent, success);
    REQUIRE(success);
    REQUIRE(readBytes.empty());
}

TEST_CASE("Disark, binaryParser_buildParameter", "[Disark]")
{
    REQUIRE(BinaryParserTest::buildParameter({}) == -1);

    REQUIRE(BinaryParserTest::buildParameter({0}) == 0);
    REQUIRE(BinaryParserTest::buildParameter({128}) == 128);
    REQUIRE(BinaryParserTest::buildParameter({255}) == 255);

    REQUIRE(BinaryParserTest::buildParameter({0x00, 0x00}) == 0x0);
    REQUIRE(BinaryParserTest::buildParameter({0x12, 0x56}) == 0x5612);
    REQUIRE(BinaryParserTest::buildParameter({0xff, 0x00}) == 0xff);
    REQUIRE(BinaryParserTest::buildParameter({0xff, 0xff}) == 0xffff);
}

TEST_CASE("Disark, binaryParser_readInstruction", "[Disark]")
{
    {
        LocalBytesProvider bytesProvider({0x12, 0x34});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);

        Opcode opcode(0x00, { SourceItem::opcodeLd, SourceItem::registerHL, SourceItem::value16Bits });        // ld hl,N
        auto instructionAndResult = disassembler.readInstruction(opcode);

        REQUIRE(instructionAndResult.second.isSuccess());
        REQUIRE(instructionAndResult.first != nullptr);
        auto instruction = std::move(instructionAndResult.first);
        REQUIRE(instruction->getParameter1() == 0x3412);
        REQUIRE(instruction->getParameter2() == -1);
    }

    {
        LocalBytesProvider bytesProvider({0x12, 0x34, 0x55, 0x77, 0xff});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);

        Opcode opcode(0x00, { SourceItem::opcodeLd, SourceItem::openParenthesis,
                              SourceItem::value16Bits, SourceItem::closeParenthesis,
                              SourceItem::comma, SourceItem::value16Bits });        // "ld (%N),%N"  I can invent instructions if I want!
        auto instructionAndResult = disassembler.readInstruction(opcode);

        REQUIRE(instructionAndResult.second.isSuccess());
        REQUIRE(instructionAndResult.first != nullptr);
        auto instruction = std::move(instructionAndResult.first);
        REQUIRE(instruction->getParameter1() == 0x3412);
        REQUIRE(instruction->getParameter2() == 0x7755);
    }

    {
        LocalBytesProvider bytesProvider({0x88, 0x34, 0x55, 0x77, 0xff});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);

        Opcode opcode(0x00, { SourceItem::opcodeLd, SourceItem::registerA, SourceItem::value8Bits });        // ld a,%n
        auto instructionAndResult = disassembler.readInstruction(opcode);

        REQUIRE(instructionAndResult.second.isSuccess());
        REQUIRE(instructionAndResult.first != nullptr);
        auto instruction = std::move(instructionAndResult.first);
        REQUIRE(instruction->getParameter1() == 0x88);
        REQUIRE(instruction->getParameter2() == -1);
    }

    {
        LocalBytesProvider bytesProvider({0x88, 0x44});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);

        Opcode opcode(0x00, { SourceItem::opcodeLd, SourceItem::registerA, SourceItem::signedIndex8Bits, SourceItem::value8Bits });        // "ld a %d %n". I can invent instructions if I want!
        auto instructionAndResult = disassembler.readInstruction(opcode);

        REQUIRE(instructionAndResult.second.isSuccess());
        REQUIRE(instructionAndResult.first != nullptr);
        auto instruction = std::move(instructionAndResult.first);
        REQUIRE(instruction->getParameter1() == 0x88);
        REQUIRE(instruction->getParameter2() == 0x44);
    }

    {
        LocalBytesProvider bytesProvider({0xdc, 0x49, 0x12});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);

        Opcode opcode(0x00, { SourceItem::opcodeLd, SourceItem::signedIndex8Bits, SourceItem::value16Bits });        // "ld a %d". I can invent instructions if I want!
        auto instructionAndResult = disassembler.readInstruction(opcode);

        REQUIRE(instructionAndResult.second.isSuccess());
        REQUIRE(instructionAndResult.first != nullptr);
        auto instruction = std::move(instructionAndResult.first);
        REQUIRE(instruction->getParameter1() == 0xdc);
        REQUIRE(instruction->getParameter2() == 0x1249);
    }
}

TEST_CASE("Disark, binaryParser_readInstruction_NotEnoughBytes", "[Disark]")
{
    {
        LocalBytesProvider bytesProvider({0x12});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);

        Opcode opcode(0x12, { SourceItem::opcodeLd, SourceItem::registerHL, SourceItem::value16Bits });        // ld hl,N
        auto instructionAndResult = disassembler.readInstruction(opcode);

        REQUIRE(!instructionAndResult.second.isSuccess());
        REQUIRE(instructionAndResult.first == nullptr);
        REQUIRE(instructionAndResult.second.getReadBytesIfError() == std::vector<int>{0x12});
    }

    {
        LocalBytesProvider bytesProvider({0x12, 0x34, 0xff});
        ExportConfiguration exportConfiguration;
        BinaryParserTest disassembler(exportConfiguration, bytesProvider);

        Opcode opcode(0x12, { SourceItem::opcodeLd, SourceItem::registerHL, SourceItem::value16Bits, SourceItem::value16Bits });        // ld hl N N. I can invent instructions if I want!
        auto instructionAndResult = disassembler.readInstruction(opcode);

        REQUIRE(!instructionAndResult.second.isSuccess());
        REQUIRE(instructionAndResult.first == nullptr);
        REQUIRE(instructionAndResult.second.getReadBytesIfError() == std::vector<int>{0x12, 0x34, 0xff});
    }
}

TEST_CASE("Disark, binaryParser_buildAllInstructions", "[Disark]")
{
    // One instruction.
    {
        LocalBytesProvider bytesProvider({0x01, 0x12, 0x34});       // ld bc,xxxx
        ExportConfiguration exportConfiguration;
        BinaryParser disassembler(exportConfiguration, bytesProvider);

        auto instructionsAndLeftOverBytes = disassembler.buildAllInstructions();
        const auto& instructions = instructionsAndLeftOverBytes.first;
        const auto& leftOverBytes = instructionsAndLeftOverBytes.second;
        REQUIRE(instructions.size() == 1);
        REQUIRE(leftOverBytes.empty());

        Instruction instruction = instructions.at(0);
        REQUIRE(instruction.getParameter1() == 0x3412);
        REQUIRE(instruction.getParameter2() == -1);
        REQUIRE(instruction.getOpcode().getParameterType1() == SourceParameterType::number16bits);
        REQUIRE(instruction.getOpcode().getParameterType2() == SourceParameterType::absent);
        REQUIRE(instruction.getOpcode().getFirstByte() == 0x01);
        REQUIRE(instruction.getOpcode().getSecondByte() == -1);
        REQUIRE(instruction.getOpcode().getThirdByte() == -1);
    }

    // Three instructions.
    {
        LocalBytesProvider bytesProvider({
                                                 0xdd, 0x21, 0x44, 0xff,                    // ld ix,%N
                                                 0x03,                                      // inc bc
                                                 0x0e, 0x55                                 // ld c,%n
                                         });
        ExportConfiguration exportConfiguration;
        BinaryParser disassembler(exportConfiguration, bytesProvider);

        auto instructionsAndLeftOverBytes = disassembler.buildAllInstructions();
        const auto& instructions = instructionsAndLeftOverBytes.first;
        const auto& leftOverBytes = instructionsAndLeftOverBytes.second;
        REQUIRE(instructions.size() == 3);
        REQUIRE(leftOverBytes.empty());

        {
            Instruction instruction = instructions.at(0);
            REQUIRE(instruction.getParameter1() == 0xff44);
            REQUIRE(instruction.getParameter2() == -1);
            REQUIRE(instruction.getOpcode().getParameterType1() == SourceParameterType::number16bits);
            REQUIRE(instruction.getOpcode().getParameterType2() == SourceParameterType::absent);
            REQUIRE(instruction.getOpcode().getFirstByte() == 0xdd);
            REQUIRE(instruction.getOpcode().getSecondByte() == 0x21);
            REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        }
        {
            Instruction instruction = instructions.at(1);
            REQUIRE(instruction.getParameter1() == -1);
            REQUIRE(instruction.getParameter2() == -1);
            REQUIRE(instruction.getOpcode().getParameterType1() == SourceParameterType::absent);
            REQUIRE(instruction.getOpcode().getParameterType2() == SourceParameterType::absent);
            REQUIRE(instruction.getOpcode().getFirstByte() == 0x03);
            REQUIRE(instruction.getOpcode().getSecondByte() == -1);
            REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        }
        {
            Instruction instruction = instructions.at(2);
            REQUIRE(instruction.getParameter1() == 0x55);
            REQUIRE(instruction.getParameter2() == -1);
            REQUIRE(instruction.getOpcode().getParameterType1() == SourceParameterType::number8bits);
            REQUIRE(instruction.getOpcode().getParameterType2() == SourceParameterType::absent);
            REQUIRE(instruction.getOpcode().getFirstByte() == 0x0e);
            REQUIRE(instruction.getOpcode().getSecondByte() == -1);
            REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        }
    }
}

TEST_CASE("Disark, binaryParser_buildAllInstructions, incomplete", "[Disark]")
{
    // One instruction, parameter incomplete.
    {
        LocalBytesProvider bytesProvider({0xdd, 0x22, 0xff});       // ld (%N),ix, one byte missing.
        ExportConfiguration exportConfiguration;
        BinaryParser disassembler(exportConfiguration, bytesProvider);

        auto instructionsAndLeftOverBytes = disassembler.buildAllInstructions();
        const auto& instructions = instructionsAndLeftOverBytes.first;
        const auto& leftOverBytes = instructionsAndLeftOverBytes.second;
        REQUIRE(instructions.empty());
        REQUIRE(leftOverBytes == std::vector<int>{ 0xdd, 0x22, 0xff });
    }

    // One instruction, opcode incomplete.
    {
        LocalBytesProvider bytesProvider({ 0xdd });                 // Only prefix.
        ExportConfiguration exportConfiguration;
        BinaryParser disassembler(exportConfiguration, bytesProvider);

        auto instructionsAndLeftOverBytes = disassembler.buildAllInstructions();
        const auto& instructions = instructionsAndLeftOverBytes.first;
        const auto& leftOverBytes = instructionsAndLeftOverBytes.second;
        REQUIRE(instructions.empty());
        REQUIRE(leftOverBytes == std::vector<int>{ 0xdd });
    }

    // Two instructions, 8-bit parameter incomplete.
    {
        LocalBytesProvider bytesProvider({
                                                 0x10, 0x50,             // djnz %r
                                                 0x0e,                   // ld c,%n, parameter missing.
                                         });

        ExportConfiguration exportConfiguration;
        BinaryParser disassembler(exportConfiguration, bytesProvider);

        auto instructionsAndLeftOverBytes = disassembler.buildAllInstructions();
        const auto& instructions = instructionsAndLeftOverBytes.first;
        const auto& leftOverBytes = instructionsAndLeftOverBytes.second;
        REQUIRE(instructions.size() == 1);       // Only one is encoded.
        REQUIRE(leftOverBytes == std::vector<int>{ 0x0e });

        {
            Instruction instruction = instructions.at(0);
            REQUIRE(instruction.getParameter1() == 0x50);
            REQUIRE(instruction.getParameter2() == -1);
            REQUIRE(instruction.getOpcode().getParameterType1() == SourceParameterType::relativeJump8bits);
            REQUIRE(instruction.getOpcode().getParameterType2() == SourceParameterType::absent);
            REQUIRE(instruction.getOpcode().getFirstByte() == 0x10);
            REQUIRE(instruction.getOpcode().getSecondByte() == -1);
            REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        }
    }

    // Two instructions, second parameter incomplete.
    {
        LocalBytesProvider bytesProvider({
                                                 0x10, 0x50,                         // djnz %r
                                                 0xdd, 0x36, 0xaa                    // ld (ix%d),%n, second parameter missing.
                                         });

        ExportConfiguration exportConfiguration;
        BinaryParser disassembler(exportConfiguration, bytesProvider);

        auto instructionsAndLeftOverBytes = disassembler.buildAllInstructions();
        const auto& instructions = instructionsAndLeftOverBytes.first;
        const auto& leftOverBytes = instructionsAndLeftOverBytes.second;
        REQUIRE(instructions.size() == 1);       // Only one is encoded.
        REQUIRE(leftOverBytes == std::vector<int>{ 0xdd, 0x36, 0xaa });

        {
            Instruction instruction = instructions.at(0);
            REQUIRE(instruction.getParameter1() == 0x50);
            REQUIRE(instruction.getParameter2() == -1);
            REQUIRE(instruction.getOpcode().getParameterType1() == SourceParameterType::relativeJump8bits);
            REQUIRE(instruction.getOpcode().getParameterType2() == SourceParameterType::absent);
            REQUIRE(instruction.getOpcode().getFirstByte() == 0x10);
            REQUIRE(instruction.getOpcode().getSecondByte() == -1);
            REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        }

    }
}


// ==============================================================

TEST_CASE("Disark, regions", "[Disark]")
{
    {
        Regions regs;
        REQUIRE(regs.getRegionTypeSortIfNeeded(0) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x1000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xf000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xffff) == RegionType::code);
    }

    {
        Regions regs;
        Region region1(0x500, 0x1000, RegionType::byte);
        regs.addRegion(region1);

        REQUIRE(regs.getRegionTypeSortIfNeeded(0) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x4ff) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x500) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xe00) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xfff) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x1000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x4000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xf000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xffff) == RegionType::code);
    }

    {
        Regions regs;
        Region region1(0x500, 0x1000, RegionType::byte);
        regs.addRegion(region1);
        Region region2(0x600, 0x700, RegionType::code);
        regs.addRegion(region2);
        Region region3(0x800, 0x900, RegionType::pointers);
        regs.addRegion(region3);
        Region region4(0x820, 0x850, RegionType::word);
        regs.addRegion(region4);

        REQUIRE(regs.getRegionTypeSortIfNeeded(0) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x4ff) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x500) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x5ff) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x600) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x6a0) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x6ff) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x700) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x800) == RegionType::pointers);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x81f) == RegionType::pointers);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x820) == RegionType::word);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x830) == RegionType::word);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x84f) == RegionType::word);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x850) == RegionType::pointers);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x8a0) == RegionType::pointers);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x8ff) == RegionType::pointers);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x900) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xe00) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xfff) == RegionType::byte);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x1000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0x4000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xf000) == RegionType::code);
        REQUIRE(regs.getRegionTypeSortIfNeeded(0xffff) == RegionType::code);
    }
}

TEST_CASE("Disark, regions_fromLabels", "[Disark]")
{
    {
        References references;
        Regions regions;
        AreaGenerator areaGenerator(regions, references);
        std::vector<Symbol> symbols;
        symbols.emplace_back("aa_DisarkCodeRegionStart_1", 0x100);
        symbols.emplace_back("aa_DisarkCodeRegionEnd_1", 0xfff);
        auto symbolsToKeepAndErrors = areaGenerator.fillFromSymbols(symbols);

        REQUIRE(symbolsToKeepAndErrors.first.empty());
        REQUIRE(symbolsToKeepAndErrors.second.empty());
        REQUIRE(regions.getRegionTypeSortIfNeeded(0) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0xff) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x100) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x500) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0xfff) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x1000) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x5000) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0xffff) == RegionType::code);
    }

    {
        References references;
        Regions regions;
        AreaGenerator areaGenerator(regions, references);

        std::vector<Symbol> symbols;
        symbols.emplace_back("aa_DisarkCodeRegionStart_1", 0x100);
        symbols.emplace_back("aa_DisarkCodeRegionEnd_1", 0x1000);

        symbols.emplace_back("aa_DisarkByteRegionStart_2", 0x110);
        symbols.emplace_back("bob", 0x200);
        symbols.emplace_back("aa_DisarkByteRegionEnd_2", 0x120);

        symbols.emplace_back("aa_DisarkByteRegionStart_3", 0x130);
        symbols.emplace_back("DisarkByteRegionzzStart_3", 0x145);
        symbols.emplace_back("aa_DisarkByteRegionEnd_3", 0x150);

        symbols.emplace_back("aa_DisarkPointerRegionStart_4", 0x150);
        symbols.emplace_back("DisarkByteRegionzzStart_4", 0x155);
        symbols.emplace_back("aa_DisarkPointerRegionEnd_4", 0x170);

        symbols.emplace_back("aa_DisarkPointerRegionEnd_5", 0x1a0);      // End can be declared before the start.
        symbols.emplace_back("DisarkByteRegionzzStart_5", 0x155);
        symbols.emplace_back("aa_DisarkPointerRegionStart_5", 0x180);

        symbols.emplace_back("aa_DisarkWordRegionStart_6", 0x300);
        symbols.emplace_back("DisarkWordRegionzzStart_6", 0x310);
        symbols.emplace_back("aa_DisarkWordRegionEnd_6", 0x320);

        auto symbolsToKeepAndErrors = areaGenerator.fillFromSymbols(symbols);

        REQUIRE(symbolsToKeepAndErrors.second.empty());
        REQUIRE(symbolsToKeepAndErrors.first.size() == 5);
        REQUIRE(symbolsToKeepAndErrors.first.at(0).getLabel() == "bob");
        REQUIRE(symbolsToKeepAndErrors.first.at(1).getLabel() == "DisarkByteRegionzzStart_3");
        REQUIRE(symbolsToKeepAndErrors.first.at(2).getLabel() == "DisarkByteRegionzzStart_4");
        REQUIRE(symbolsToKeepAndErrors.first.at(3).getLabel() == "DisarkByteRegionzzStart_5");
        REQUIRE(symbolsToKeepAndErrors.first.at(4).getLabel() == "DisarkWordRegionzzStart_6");

        REQUIRE(regions.getRegionTypeSortIfNeeded(0) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0xff) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x100) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x10f) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x110) == RegionType::byte);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x115) == RegionType::byte);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x11f) == RegionType::byte);

        REQUIRE(regions.getRegionTypeSortIfNeeded(0x120) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x128) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x12f) == RegionType::code);

        REQUIRE(regions.getRegionTypeSortIfNeeded(0x130) == RegionType::byte);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x140) == RegionType::byte);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x14f) == RegionType::byte);

        REQUIRE(regions.getRegionTypeSortIfNeeded(0x150) == RegionType::pointers);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x160) == RegionType::pointers);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x16f) == RegionType::pointers);

        REQUIRE(regions.getRegionTypeSortIfNeeded(0x170) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x178) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x17f) == RegionType::code);

        REQUIRE(regions.getRegionTypeSortIfNeeded(0x180) == RegionType::pointers);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x190) == RegionType::pointers);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x19f) == RegionType::pointers);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x200) == RegionType::code);

        REQUIRE(regions.getRegionTypeSortIfNeeded(0x2ff) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x300) == RegionType::word);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x310) == RegionType::word);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x31f) == RegionType::word);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x320) == RegionType::code);

        REQUIRE(regions.getRegionTypeSortIfNeeded(0xfff) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x1000) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0x5000) == RegionType::code);
        REQUIRE(regions.getRegionTypeSortIfNeeded(0xffff) == RegionType::code);
    }

    // End declared before start: no a problem.
    {
        References references;
        Regions regions;
        AreaGenerator areaGenerator(regions, references);

        std::vector<Symbol> symbols;
        symbols.emplace_back("aa_DisarkCodeRegionEnd_1", 0xfff);
        symbols.emplace_back("aa_DisarkCodeRegionStart_1", 0x100);

        auto symbolsToKeepAndErrors = areaGenerator.fillFromSymbols(symbols);

        REQUIRE(symbolsToKeepAndErrors.first.empty());
        REQUIRE(symbolsToKeepAndErrors.second.empty());
    }

    // Error. Two codes regions started.
    {
        References references;
        Regions regions;
        AreaGenerator areaGenerator(regions, references);

        std::vector<Symbol> symbols;
        symbols.emplace_back("aa_DisarkCodeRegionStart_1", 0x100);
        symbols.emplace_back("aa_DisarkCodeRegionStart_2", 0xfff);

        auto symbolsToKeepAndErrors = areaGenerator.fillFromSymbols(symbols);

        REQUIRE(symbolsToKeepAndErrors.first.empty());
        REQUIRE(symbolsToKeepAndErrors.second.size() == (2 * 3));
    }

    // Error. Two Ends, no starts.
    {
        References references;
        Regions regions;
        AreaGenerator areaGenerator(regions, references);

        std::vector<Symbol> symbols;
        symbols.emplace_back("aa_DisarkCodeRegionEnd_1", 0x100);
        symbols.emplace_back("aa_DisarkCodeRegionEnd_2", 0xfff);

        auto symbolsToKeepAndErrors = areaGenerator.fillFromSymbols(symbols);

        REQUIRE(symbolsToKeepAndErrors.first.empty());
        REQUIRE(symbolsToKeepAndErrors.second.size() == (2 * 3));
    }

    // Error. End inferior to start.
    {
        References references;
        Regions regions;
        AreaGenerator areaGenerator(regions, references);

        std::vector<Symbol> symbols;
        symbols.emplace_back("aa_DisarkByteRegionStart_1", 0xfff);
        symbols.emplace_back("aa_DisarkByteRegionEnd_1", 0x100);

        auto symbolsToKeepAndErrors = areaGenerator.fillFromSymbols(symbols);

        REQUIRE(symbolsToKeepAndErrors.first.empty());
        REQUIRE(symbolsToKeepAndErrors.second.size() == (1 * 3));
    }

    // Error. Two ends.
    {
        References references;
        Regions regions;
        AreaGenerator areaGenerator(regions, references);

        std::vector<Symbol> symbols;
        symbols.emplace_back("aa_DisarkByteRegionEnd_1", 0x0ff);
        symbols.emplace_back("aa_DisarkByteRegionEnd_1", 0x100);

        auto symbolsToKeepAndErrors = areaGenerator.fillFromSymbols(symbols);

        REQUIRE(symbolsToKeepAndErrors.first.empty());
        REQUIRE(symbolsToKeepAndErrors.second.size() == 1);
    }
}

TEST_CASE("Disark, disassemble_disassembleRegions_NoRegion", "[Disark]")
{
    // No region.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0x40U, 0x50U,           // ld bc,%N
            0x04U,                       // inc b
            0xddU, 0x09U                  // add ix,bc
    };
    memoryBlock.insert(dataIn, 6, 0);
    juce::MemoryInputStream memoryInputStream(memoryBlock, false);

    ExportConfiguration exportConfiguration;
    DisassemblerTest disassembler(exportConfiguration);
    auto holders = disassembler.disassembleRegions(memoryInputStream);
    REQUIRE(holders.size() == 1);

    auto holder = std::move(holders.at(0));         // Dirtily retrieves the data.
    auto& codeRegionDataHolder = dynamic_cast<CodeRegionDataHolder&>(*holder);
    REQUIRE(codeRegionDataHolder.getStartAddress() == 0);
    REQUIRE(codeRegionDataHolder.getLeftOverBytes().empty());

    const auto& instructions = codeRegionDataHolder.getInstructions();
    REQUIRE(instructions.size() == 3);
    {
        const Instruction& instruction = instructions.at(0);
        REQUIRE(instruction.getOpcode().getFirstByte() == 0x01);
        REQUIRE(instruction.getOpcode().getSecondByte() == -1);
        REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        REQUIRE(instruction.getParameter1() == 0x5040);
        REQUIRE(instruction.getParameter2() == -1);
    }
    {
        const Instruction& instruction = instructions.at(1);
        REQUIRE(instruction.getOpcode().getFirstByte() == 0x04);
        REQUIRE(instruction.getOpcode().getSecondByte() == -1);
        REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        REQUIRE(instruction.getParameter1() == -1);
        REQUIRE(instruction.getParameter2() == -1);
    }
    {
        const Instruction& instruction = instructions.at(2);
        REQUIRE(instruction.getOpcode().getFirstByte() == 0xdd);
        REQUIRE(instruction.getOpcode().getSecondByte() == 0x09);
        REQUIRE(instruction.getOpcode().getThirdByte() == -1);
        REQUIRE(instruction.getParameter1() == -1);
        REQUIRE(instruction.getParameter2() == -1);
    }

}

TEST_CASE("Disark, disassemble_disassembleRegions_CodeAndByteRegions", "[Disark]")
{
    // A code region, and a byte region.
    juce::MemoryBlock memoryBlock;
    const unsigned char dataIn[] = {
            0x01U, 0x40U, 0x50U,                               // ld bc,%N
            0x20U, 0x60U, 0xffU,                               // Random bytes for the Byte region.
    };
    memoryBlock.insert(dataIn, 6, 0);
    juce::MemoryInputStream memoryInputStream(memoryBlock, false);

    ExportConfiguration exportConfiguration;
    DisassemblerTest disassembler(exportConfiguration);
    // Only declares the Byte Region, the Code Region is implicit.
    disassembler.addRegion({ 3, 6, RegionType::byte });

    auto holders = disassembler.disassembleRegions(memoryInputStream);
    REQUIRE(holders.size() == 2);

    // Checks the Code Region.
    {
        auto holder = std::move(holders.at(0));         // Dirtily retrieves the data.
        auto& codeRegionDataHolder = dynamic_cast<CodeRegionDataHolder&>(*holder);
        REQUIRE(codeRegionDataHolder.getStartAddress() == 0);
        REQUIRE(codeRegionDataHolder.getLeftOverBytes().empty());

        const auto& instructions = codeRegionDataHolder.getInstructions();
        REQUIRE(instructions.size() == 1);
        {
            const Instruction& instruction = instructions.at(0);
            REQUIRE(instruction.getOpcode().getFirstByte() == 0x01);
            REQUIRE(instruction.getOpcode().getSecondByte() == -1);
            REQUIRE(instruction.getOpcode().getThirdByte() == -1);
            REQUIRE(instruction.getParameter1() == 0x5040);
            REQUIRE(instruction.getParameter2() == -1);
        }
    }

    // Checks the Byte Region.
    {
        auto holder = std::move(holders.at(1));         // Dirtily retrieves the data.
        auto& codeRegionDataHolder = dynamic_cast<ByteRegionDataHolder&>(*holder);
        REQUIRE(codeRegionDataHolder.getStartAddress() == 3);
        REQUIRE(codeRegionDataHolder.getBytes() == std::vector<int>{ 0x20, 0x60, 0xff });
    }
}

TEST_CASE("Disark, disassemble_disassembleRegions_CodeAndWordRegions", "[Disark]")
{
    // A code region, and a byte region.
    juce::MemoryBlock memoryBlock;
    const char dataIn[] = {
            0x01, 0x40, 0x50,                               // ld bc,%N
            0x20, 0x60, 0x79U, 0x45, 0x01,             // Words, and a left over.
    };
    memoryBlock.insert(dataIn, 8, 0);
    juce::MemoryInputStream memoryInputStream(memoryBlock, false);

    ExportConfiguration exportConfiguration;
    DisassemblerTest disassembler(exportConfiguration);
    // Only declares the Byte Region, the Code Region is implicit.
    disassembler.addRegion({ 3, 8, RegionType::pointers});

    auto holders = disassembler.disassembleRegions(memoryInputStream);
    REQUIRE(holders.size() == 2);

    // Checks the Code Region.
    {
        auto holder = std::move(holders.at(0));         // Dirtily retrieves the data.
        auto& codeRegionDataHolder = dynamic_cast<CodeRegionDataHolder&>(*holder);
        REQUIRE(codeRegionDataHolder.getStartAddress() == 0);
        REQUIRE(codeRegionDataHolder.getLeftOverBytes().empty());

        const auto& instructions = codeRegionDataHolder.getInstructions();
        REQUIRE(instructions.size() == 1);
        {
            const Instruction& instruction = instructions.at(0);
            REQUIRE(instruction.getOpcode().getFirstByte() == 0x01);
            REQUIRE(instruction.getOpcode().getSecondByte() == -1);
            REQUIRE(instruction.getOpcode().getThirdByte() == -1);
            REQUIRE(instruction.getParameter1() == 0x5040);
            REQUIRE(instruction.getParameter2() == -1);
        }
    }

    // Checks the Word Region.
    {
        auto holder = std::move(holders.at(1));         // Dirtily retrieves the data.
        auto& codeRegionDataHolder = dynamic_cast<PointerRegionDataHolder&>(*holder);
        REQUIRE(codeRegionDataHolder.getStartAddress() == 3);
        REQUIRE(codeRegionDataHolder.getWords() == std::vector<int>{ 0x6020, 0x4579 });
        REQUIRE(codeRegionDataHolder.getLeftOver() == 1);
    }
}

TEST_CASE("Disark, sourceItemEncoder_encodeInstructionToString", "[Disark]")
{
    ExportConfiguration exportConfiguration;
    {
        juce::MemoryOutputStream outputStream;
        References references;
        SourceItemEncoder sourceItemEncoder(references, outputStream, exportConfiguration);

        std::vector<SourceItem> sourceItems{SourceItem::declareByte, SourceItem::value8Bits};
        sourceItemEncoder.visitInstruction(0x1000, 2, sourceItems, 0x5a, -1);

        auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
        REQUIRE(strings.size() == 1);
        REQUIRE(strings.at(0) == "    db #5a");
    }

    {
        juce::MemoryOutputStream outputStream;
        References references;
        SourceItemEncoder sourceItemEncoder(references, outputStream, exportConfiguration);

        std::vector<SourceItem> sourceItems{SourceItem::declareWord, SourceItem::value16Bits};
        sourceItemEncoder.visitInstruction(0x1000, 2, sourceItems, 0x1234, -1);

        auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
        REQUIRE(strings.size() == 1);
        REQUIRE(strings.at(0) == "    dw #1234");
    }

    // One label here.
    {
        juce::MemoryOutputStream outputStream;
        References references;
        references.storeSymbol({ "mylabel", 0x1000, false });
        SourceItemEncoder sourceItemEncoder(references, outputStream, exportConfiguration);

        std::vector<SourceItem> sourceItems{SourceItem::declareWord, SourceItem::value16Bits};
        sourceItemEncoder.visitInstruction(0x1000, 2, sourceItems, 0xff, -1);

        auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
        REQUIRE(strings.size() == 1);
        REQUIRE(strings.at(0) == "mylabel dw #ff");
    }

    // Nop.
    {
        juce::MemoryOutputStream outputStream;
        References references;
        SourceItemEncoder sourceItemEncoder(references, outputStream, exportConfiguration);

        std::vector<SourceItem> sourceItems{ SourceItem::opcodeNop };
        sourceItemEncoder.visitInstruction(0x1000, 1, sourceItems, -1, -1);

        auto strings = MemoryBlockUtil::extractStrings(outputStream.getMemoryBlock());
        REQUIRE(strings.size() == 1);
        REQUIRE(strings.at(0) == "    nop");
    }
}

TEST_CASE("Disark, empty", "[Disark]")
{
    References references;
    REQUIRE(references.getReference(0x0).label.isEmpty());
    REQUIRE(references.getReference(0x10).label.isEmpty());
    REQUIRE(references.getReference(0x100).label.isEmpty());
    REQUIRE(references.getReference(0x4000).label.isEmpty());
    REQUIRE(references.getReference(0xffff).label.isEmpty());
}

TEST_CASE("Disark, getReference", "[Disark]")
{
    References references;
    references.storeSymbol({ "label1", 0x4000, false });
    references.storeSymbol({ "label2", 0x3123, false });
    references.storeSymbol({ "label3", 0xffff, true });
    references.storeSymbol({ "label4", 0x0, true });

    references.storeSymbol({ "label1b", 0x4000, false });
    references.storeSymbol({ "label1c", 0x4000, false });
    references.storeSymbol({ "label4b", 0x0, false });
    references.storeSymbol({ "label4c", 0x0, false });

    REQUIRE(references.getReference(0x100).label.isEmpty());

    // Same reference even when "walking away".
    {
        auto reference = references.getReference(0x4000);
        REQUIRE(reference.label == "label1");
        REQUIRE(reference.offset == 0x0);
    }
    {
        auto reference = references.getReference(0x3fff);
        REQUIRE(reference.label == "label1");
        REQUIRE(reference.offset == 0x1);
    }
    {
        auto reference = references.getReference(0x3ffd);
        REQUIRE(reference.label == "label1");
        REQUIRE(reference.offset == 3);
    }
    {
        auto reference = references.getReference(0x4004);
        REQUIRE(reference.label == "label1");
        REQUIRE(reference.offset == -4);
    }
    // Too far away.
    REQUIRE(references.getReference(0x4010).label.isEmpty());

    {
        auto reference = references.getReference(0x0);
        REQUIRE(reference.label == "label4");
        REQUIRE(reference.offset == 0);
    }
    {
        auto reference = references.getReference(0x1);
        REQUIRE(reference.label == "label4");
        REQUIRE(reference.offset == -1);
    }
    {
        auto reference = references.getReference(0x2);
        REQUIRE(reference.label == "label4");
        REQUIRE(reference.offset == -2);
    }
    {
        auto reference = references.getReference(0x7);
        REQUIRE(reference.label == "label4");
        REQUIRE(reference.offset == -0x7);
    }
    REQUIRE(references.getReference(0x10).label.isEmpty());
}

TEST_CASE("Disark, exactReference", "[Disark]")
{
    References references;
    references.storeSymbol({ "label1", 0x4000, false });
    references.storeSymbol({ "label2", 0x3123, false });
    references.storeSymbol({ "label3", 0xffff, true });
    references.storeSymbol({ "label4", 0x0, true });

    references.storeSymbol({ "label1b", 0x4000, true });
    references.storeSymbol({ "label1c", 0x4000, false });
    references.storeSymbol({ "label4b", 0x0, false });
    references.storeSymbol({ "label4c", 0x0, false });

    REQUIRE(references.getReference(0x100).label.isEmpty());

    {
        auto referenceList = references.getExactReferences(0x4000);
        REQUIRE(referenceList.size() == 3);

        REQUIRE(referenceList.at(0).getName() == "label1");
        REQUIRE(!referenceList.at(0).isGenerated());

        REQUIRE(referenceList.at(1).getName() == "label1b");
        REQUIRE(referenceList.at(1).isGenerated());

        REQUIRE(referenceList.at(2).getName() == "label1c");
        REQUIRE(!referenceList.at(2).isGenerated());
    }

    {
        auto referenceList = references.getExactReferences(0x0);
        REQUIRE(referenceList.size() == 3);

        REQUIRE(referenceList.at(0).getName() == "label4");
        REQUIRE(referenceList.at(0).isGenerated());

        REQUIRE(referenceList.at(1).getName() == "label4b");
        REQUIRE(!referenceList.at(1).isGenerated());

        REQUIRE(referenceList.at(2).getName() == "label4c");
        REQUIRE(!referenceList.at(2).isGenerated());
    }

    {
        auto referenceList = references.getExactReferences(0xffff);
        REQUIRE(referenceList.size() == 1);

        REQUIRE(referenceList.at(0).getName() == "label3");
        REQUIRE(referenceList.at(0).isGenerated());
    }

    {
        auto referenceList = references.getExactReferences(0x3123);
        REQUIRE(referenceList.size() == 1);

        REQUIRE(referenceList.at(0).getName() == "label2");
        REQUIRE(!referenceList.at(0).isGenerated());
    }

    REQUIRE(references.getExactReferences(0x1).empty());
    REQUIRE(references.getExactReferences(0x4001).empty());
    REQUIRE(references.getExactReferences(0x3fff).empty());
    REQUIRE(references.getExactReferences(0xfffe).empty());
}

TEST_CASE("Disark, references_clearAllUnusedReferences", "[Disark]")
{
    // None is referred to.
    {
        References references;
        references.storeSymbol({ "label1", 0x4000, false });
        references.storeSymbol({ "label2", 0x3123, false });
        references.storeSymbol({ "label3", 0xffff, true });
        references.storeSymbol({ "label4", 0x0, true });

        references.storeSymbol({ "label1b", 0x4000, true });
        references.storeSymbol({ "label1c", 0x4000, false });
        references.storeSymbol({ "label4b", 0x0, false });
        references.storeSymbol({ "label4c", 0x0, false });

        references.deleteUnusedReferences(false);

        REQUIRE(references.getExactReferences(0x4000).empty());
        REQUIRE(references.getExactReferences(0x3123).empty());
        REQUIRE(references.getExactReferences(0xffff).empty());
        REQUIRE(references.getExactReferences(0x0).empty());
    }

    // A few are referred to.
    {
        References references;
        references.storeSymbol({ "label1", 0x4000, false });
        references.storeSymbol({ "label2", 0x3123, false });
        references.storeSymbol({ "label3", 0xffff, true });
        references.storeSymbol({ "label4", 0x0, true });

        references.storeSymbol({ "label1b", 0x4000, true });
        references.storeSymbol({ "label1c", 0x4000, true });
        references.storeSymbol({ "label4b", 0x0, false });
        references.storeSymbol({ "label4c", 0x0, false });

        references.markLabelAsReferredTo("label1");
        references.markLabelAsReferredTo("label1");         // A second time, as a test, as it will surely happen many time.
        references.markLabelAsReferredTo("label4b");
        references.markLabelAsReferredTo("label4");

        references.deleteUnusedReferences(false);

        {
            auto referenceList = references.getExactReferences(0x4000);
            REQUIRE(referenceList.size() == 1);

            REQUIRE(referenceList.at(0).getName() == "label1");
            REQUIRE(!referenceList.at(0).isGenerated());
        }
        REQUIRE(references.getExactReferences(0x3123).empty());
        REQUIRE(references.getExactReferences(0xffff).empty());

        {
            auto referenceList = references.getExactReferences(0x0);
            REQUIRE(referenceList.size() == 2);

            REQUIRE(referenceList.at(0).getName() == "label4");
            REQUIRE(referenceList.at(0).isGenerated());

            REQUIRE(referenceList.at(1).getName() == "label4b");
            REQUIRE(!referenceList.at(1).isGenerated());
        }
    }

    // Deletes only generated labels.
    {
        References references;
        references.storeSymbol({ "label1", 0x4000, false });
        references.storeSymbol({ "label2", 0x3123, false });
        references.storeSymbol({ "label3", 0xffff, true });
        references.storeSymbol({ "label4", 0x0, true });

        references.storeSymbol({ "label1b", 0x4000, true });
        references.storeSymbol({ "label1c", 0x4000, true });
        references.storeSymbol({ "label4b", 0x0, false });
        references.storeSymbol({ "label4c", 0x0, true });

        references.markLabelAsReferredTo("label1");
        references.markLabelAsReferredTo("label1");         // A second time, as a test, as it will surely happen many time.
        references.markLabelAsReferredTo("label4b");
        references.markLabelAsReferredTo("label4");

        references.deleteUnusedReferences(true);

        {
            auto referenceList = references.getExactReferences(0x4000);
            REQUIRE(referenceList.size() == 1);

            REQUIRE(referenceList.at(0).getName() == "label1");
            REQUIRE(!referenceList.at(0).isGenerated());
        }
        {
            auto referenceList = references.getExactReferences(0x3123);
            REQUIRE(referenceList.size() == 1);

            REQUIRE(referenceList.at(0).getName() == "label2");
            REQUIRE(!referenceList.at(0).isGenerated());
        }

        REQUIRE(references.getExactReferences(0xffff).empty());

        {
            auto referenceList = references.getExactReferences(0x0);
            REQUIRE(referenceList.size() == 2);

            REQUIRE(referenceList.at(0).getName() == "label4");
            REQUIRE(referenceList.at(0).isGenerated());

            REQUIRE(referenceList.at(1).getName() == "label4b");
            REQUIRE(!referenceList.at(1).isGenerated());
        }
    }
}

TEST_CASE("Disark, references_getSortedLabelsAndAddresses", "[Disark]")
{
    References references;
    references.storeSymbol({ "label1", 0x4000, false });
    references.storeSymbol({ "label2", 0x3123, false });
    references.storeSymbol({ "label3", 0xffff, true });
    references.storeSymbol({ "label4", 0x0, true });

    references.storeSymbol({ "label1b", 0x4000, true });
    references.storeSymbol({ "label1c", 0x4000, true });
    references.storeSymbol({ "label4b", 0x0, false });
    references.storeSymbol({ "label4c", 0x0, true });

    auto labelsAndAddresses = references.getSortedLabelsAndAddresses();

    REQUIRE(labelsAndAddresses.size() == 8);
    REQUIRE(labelsAndAddresses.at(0).getAddress() == 0);
    REQUIRE(labelsAndAddresses.at(0).getLabel() == "label4");
    REQUIRE(labelsAndAddresses.at(1).getAddress() == 0);
    REQUIRE(labelsAndAddresses.at(1).getLabel() == "label4b");
    REQUIRE(labelsAndAddresses.at(2).getAddress() == 0);
    REQUIRE(labelsAndAddresses.at(2).getLabel() == "label4c");

    REQUIRE(labelsAndAddresses.at(3).getAddress() == 0x3123);
    REQUIRE(labelsAndAddresses.at(3).getLabel() == "label2");

    REQUIRE(labelsAndAddresses.at(4).getAddress() == 0x4000);
    REQUIRE(labelsAndAddresses.at(4).getLabel() == "label1");
    REQUIRE(labelsAndAddresses.at(5).getAddress() == 0x4000);
    REQUIRE(labelsAndAddresses.at(5).getLabel() == "label1b");
    REQUIRE(labelsAndAddresses.at(6).getAddress() == 0x4000);
    REQUIRE(labelsAndAddresses.at(6).getLabel() == "label1c");

    REQUIRE(labelsAndAddresses.at(7).getAddress() == 0xffff);
    REQUIRE(labelsAndAddresses.at(7).getLabel() == "label3");
}

}    // namespace disark
