#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../../source/utils/NumberUtil.h"
#include "../../helper/RasmHelper.h"
#include "../../helper/z80Emulator/Z80Emulator.h"

namespace arkostracker
{

TEST_CASE("Z80Emulator, small timings, no logs", "[Z80Emulator]")
{
    constexpr auto startAddress = 0x4000;

    Z80Emulator emulator(TargetHardware::cpc);

    const juce::String source = R"(
        org #4000

        ld hl,#1234
        add hl,de

        jp #ffff
)";
    const auto sourceMemoryBlock = MemoryBlockUtil::fromString(source);
    const auto data = RasmHelper::assembleSourceWithoutAddingOrg(sourceMemoryBlock);
    REQUIRE((data != nullptr));

    emulator.injectData(*data, startAddress);

    // Launch emulator.
    const auto nopCount = emulator.runTill(startAddress, 0xffff, 0xffff);
    REQUIRE((nopCount == (9 + 1)));     // + 1 because of the instruction (nop) in FFFF.

    REQUIRE(emulator.getInstructionLog().empty());      // Because not asked by default.
}

TEST_CASE("Z80Emulator, small timings, with logs", "[Z80Emulator]")
{
    constexpr auto startAddress = 0x4000;

    Z80Emulator emulator(TargetHardware::cpc);

    const juce::String source = R"(
        org #4000

        ld hl,#1234
        add hl,de

        jp #ffff
)";
    const auto sourceMemoryBlock = MemoryBlockUtil::fromString(source);
    const auto data = RasmHelper::assembleSourceWithoutAddingOrg(sourceMemoryBlock);
    REQUIRE((data != nullptr));

    emulator.injectData(*data, startAddress);

    // Launch emulator.
    emulator.setMustLogInstruction(true);
    const auto nopCount = emulator.runTill(startAddress, 0xffff, 0xffff);
    REQUIRE((nopCount == (9 + 1)));     // + 1 because of the instruction (nop) in FFFF.

    REQUIRE(emulator.getInstructionLog() == std::vector<z80emulator::Z80::InstructionLog> {
        z80emulator::Z80::InstructionLog(0x4000, 0x21, 0),
        z80emulator::Z80::InstructionLog(0x4003, 0x19, 3),
        z80emulator::Z80::InstructionLog(0x4004, 0xc3, 6),
        z80emulator::Z80::InstructionLog(0xffff, 0x0, 9),
    });
}

TEST_CASE("Z80Emulator, unknown instruction", "[Z80Emulator]")
{
    constexpr auto startAddress = 0x4000;

    Z80Emulator emulator(TargetHardware::cpc);

    const juce::String source = R"(
        org #4000

        defb #ed, #81
)";
    const auto sourceMemoryBlock = MemoryBlockUtil::fromString(source);
    const auto data = RasmHelper::assembleSourceWithoutAddingOrg(sourceMemoryBlock);
    REQUIRE((data != nullptr));

    emulator.injectData(*data, startAddress);

    // Launch emulator.
    const auto nopCount = emulator.runTill(startAddress, 0xffff, 0xffff);
    REQUIRE((nopCount == -1));
}

TEST_CASE("Z80Emulator, all timings", "[Z80Emulator]")
{
    constexpr auto loadAddress = 0x0;
    constexpr auto execAddress = 0x40;
    constexpr auto endAddress = 0xd64;       // A nop after the last ei.

    Z80Emulator emulator(TargetHardware::cpc);

    const auto sourceMemoryBlock = juce::MemoryBlock(BinaryData::allInstructionSet_asm, BinaryData::allInstructionSet_asmSize);
    const auto data = RasmHelper::assembleSourceWithoutAddingOrg(sourceMemoryBlock);
    REQUIRE((data != nullptr));

    emulator.injectData(*data, loadAddress);
    emulator.setMustLogInstruction(true);

    // Reads the reference log.
    std::vector<z80emulator::Z80::InstructionLog> referenceLogs;
    const auto referenceLogMemoryBlock = juce::MemoryBlock(BinaryData::allInstructionSet_log, BinaryData::allInstructionSet_logSize);
    juce::MemoryInputStream referenceLogInputStream(referenceLogMemoryBlock, false);
    auto previousLogPc = -1;
    while (!referenceLogInputStream.isExhausted()) {
        const auto readReferenceString = referenceLogInputStream.readNextLine();
        auto logPc = -1;
        auto logNopCount = -1;
        // Last line is special.
        if (readReferenceString.startsWith("executed in ")) {
            logPc = previousLogPc + 1;      // The last instruction is a EI.
            logNopCount = readReferenceString.substring(12, readReferenceString.indexOf(" nop(s)")).getIntValue();
        } else {
            if (readReferenceString.startsWith("PC: ")) {
                logPc = readReferenceString.substring(4, 8).getHexValue32();
            }
            const auto nopTag = juce::String("nop: ");
            const auto nopTagIndex = readReferenceString.indexOf(nopTag);
            const auto nopTagSize = nopTag.length();
            const auto lastInstructionNop = readReferenceString.indexOf("last instruction nop");
            if ((nopTagIndex >= 0) && (lastInstructionNop > nopTagIndex)) {
                logNopCount = readReferenceString.substring(nopTagIndex + nopTagSize, lastInstructionNop).trim().getIntValue();
            }
        }

        if ((logPc >= 0) && (logNopCount >= 0)) {
            //DBG("Reference log: " + readReferenceString);
            referenceLogs.emplace_back(logPc, -1, logNopCount);

            previousLogPc = logPc;
        }
    }

    // Launch emulator.
    const auto nopCount = emulator.runTill(execAddress, endAddress, 0xffff);
    DBG("NOPS " + juce::String(nopCount));
    REQUIRE((nopCount == 5320 + 1));        // Because of the NOP at the end.
    const auto emulatorLogs = emulator.getInstructionLog();

    REQUIRE((emulatorLogs.size() == referenceLogs.size()));

    size_t logIndex = 0;
    for (const auto& emulatorLog : emulatorLogs) {
        const auto& referenceLog = referenceLogs.at(logIndex);
        const auto logPc = referenceLog.pc;
        const auto logNopCount = referenceLog.previouslyCumulatedCpcNops;

        /*DBG("Emulator log:  PC: " + NumberUtil::toHexFourDigits(emulatorLog.pc) + ", operand #" + juce::String::toHexString(emulatorLog.operand)
            + ", nops = " + juce::String(emulatorLog.cpcNops));
        DBG("");*/
        REQUIRE((logPc == emulatorLog.pc));
        if (logNopCount != emulatorLog.previouslyCumulatedCpcNops) {
            FAIL("Nop count failure: Expected: " + juce::String(logNopCount) + " vs emulator: " + juce::String(emulatorLog.previouslyCumulatedCpcNops));
        }

        ++logIndex;
    }
}

}   // namespace arkostracker
