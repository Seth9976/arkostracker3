#include "Z80Emulator.h"

#include "../../../source/player/PsgRegisters.h"
#include "../../../source/song/Song.h"
#include "../../../source/utils/PsgValues.h"
#include "../../../thirdParty/z80emulatorLibz80/z80.hpp"

namespace arkostracker 
{

// Raw class, so many warnings are silenced.

// memory read request per 1 byte from CPU
unsigned char readByte(void* arg, const uint16_t addr)
{
    // NOTE: implement switching procedure here if your MMU has bank switch feature
    return ((z80emulator::MMU*)arg)->RAM[addr];         // NOLINT(*)
}

// memory write request per 1 byte from CPU
void writeByte(void* arg, const uint16_t addr, const unsigned char value)
{
    // NOTE: implement switching procedure here if your MMU has bank switch feature
    ((z80emulator::MMU*)arg)->RAM[addr] = value;         // NOLINT(*)
}

// IN operand request from CPU
unsigned char inPort(void* arg, const unsigned char port)
{
    return ((z80emulator::MMU*)arg)->IO[port];         // NOLINT(*)
}

// OUT operand request from CPU
/*
void outPort(void* arg, unsigned char port, unsigned char value)
{
    ((MMU*)arg)->IO[port] = value;
}
*/

// ==============================================================================


Z80Emulator::Z80Emulator(const TargetHardware pTargetHardware) noexcept :
        targetHardware(pTargetHardware),
        mmu(),
        z80(readByte, writeByte, inPort,         // NOLINT(*)
            [&](const unsigned short port, const unsigned char value) { onOutPort(port, value); },
            &mmu),
        psgData(),
        selectedRegisterOnPsg(),
        nextCallIsRegister(false),
        nextCallIsValue(false),
        spectrumIndexPsgSelected(-1),
        pcwTurboSoundIndexPsgSelected(-1)
{
    psgData.fill(0U);
    selectedRegisterOnPsg.fill(0);
}

void Z80Emulator::injectData(const juce::MemoryBlock& memoryBlock, const unsigned int address) noexcept
{
    const auto size = memoryBlock.getSize();
    jassert((address + size) < sizeof(mmu.RAM));

    for (size_t i = 0U; i < size; ++i) {
        auto c = static_cast<unsigned char>(memoryBlock[i]);
        z80.writeByte(address + i, c);         // NOLINT(*)
    }
}

int Z80Emulator::runTillRst38(const int pc, const int maximumNops) noexcept
{
    z80.reg.PC = pc;                    // NOLINT(*)
    z80.reg.SP = stackPointer;          // NOLINT(*)

    z80.removeAllBreakOperands();

    z80.addBreakOperand(0xffU, [&] {
        z80.requestBreak();
    });

    z80.instructionLog.clear();

    return z80.execute(maximumNops);        // Runs for a long time, the break above should be encountered way before that.
}

int Z80Emulator::runTill(const unsigned short pc, const unsigned short endAddress, const unsigned short sp, const int maximumNops) noexcept
{
    z80.reg.PC = pc;
    z80.reg.SP = sp;
    z80.reg.IFF = 0;        // DI.

    z80.removeAllBreakPoints();

    z80.addBreakPoint(endAddress, [&] {
        z80.requestBreak();
    });

    z80.instructionLog.clear();

    return z80.execute(maximumNops);        // Runs for a long time, the break above should be encountered way before that.
}

std::vector<z80emulator::Z80::InstructionLog> Z80Emulator::getInstructionLog() const noexcept
{
    return z80.instructionLog;
}

void Z80Emulator::setMustLogInstruction(const bool mustLog) noexcept
{
    z80.mustLogInstructions = mustLog;
}

unsigned int Z80Emulator::readPsgData(const int psgRegister, const int psgIndex) noexcept
{
    return psgData[static_cast<size_t>(psgIndex) * registersPerPsg + static_cast<size_t>(psgRegister)];         // NOLINT(*)
}

void Z80Emulator::setPsgData(const int psgIndex, const unsigned int data) noexcept
{
    const auto selectedRegister = selectedRegisterOnPsg[static_cast<size_t>(psgIndex)];         // NOLINT(*)
    setPsgData(psgIndex, selectedRegister, data);
}

void Z80Emulator::setPsgData(const int psgIndex, const int registerIndex, const unsigned int data) noexcept
{
    psgData[static_cast<size_t>(psgIndex) * registersPerPsg + static_cast<size_t>(registerIndex)] = data;         // NOLINT(*)
}

void Z80Emulator::selectRegister(const int psgIndex, const int psgRegister) noexcept
{
    selectedRegisterOnPsg[static_cast<size_t>(psgIndex)] = psgRegister;         // NOLINT(*)
}

void Z80Emulator::markHardwareEnvelopeRegisterAsNonRetrig(const int psgIndex) noexcept
{
    setPsgData(psgIndex, PsgValues::registerHardwareEnvelope, 0xffU);
}

bool Z80Emulator::comparePsgFrame(const int psgIndex, const PsgRegisters& psgRegisters, int& previousHardwareEnvelope,
                                  int& errorCountInVolume, const int toleratedErrorsInVolume, const int possibleAbsoluteDifferenceInVolume,
                                  int& errorCountInNoise, const int toleratedErrorsInNoise,
                                  const int possibleAbsoluteDifferenceInSoftwarePeriod, const int possibleAbsoluteDifferenceInHardwarePeriod,
                                  const int errorCountToleranceInHardwarePeriod, int& errorCountInHardwarePeriod) noexcept
{
    // The mixer, but checked after.
    const auto originalZ80Mixer = readPsgData(PsgValues::registerMixer, psgIndex);
    // Makes sure bits 7 and 6 are compliant to the platform.
    switch (targetHardware) {
        case TargetHardware::cpc:
            [[fallthrough]];
        case TargetHardware::pcw:
            [[fallthrough]];
        case TargetHardware::pcwTurboSound:
            [[fallthrough]];
        case TargetHardware::cpcPlayCity:
            if ((originalZ80Mixer & 0b01000000U) != 0U) {
                jassertfalse;           // b6 MUST be 0 on CPC, else no more keyboard!
                return false;
            }
            break;
        case TargetHardware::msx:
            [[fallthrough]];
        case TargetHardware::svi:
            [[fallthrough]];
        case TargetHardware::msxDarky:
            [[fallthrough]];
        case TargetHardware::msxFpgaPsg:
            if ((originalZ80Mixer & 0b11000000U) != 0b10000000U) {
                jassertfalse;           // b7 MUST be 1, and b6 MUST be 0 on MSX (joystick problem, or can damage hardware)!
                return false;
            }
            break;
        case TargetHardware::spectrum:
            [[fallthrough]];
        case TargetHardware::pentagon:
            [[fallthrough]];
        case TargetHardware::sharpMz:
            [[fallthrough]];
        case TargetHardware::spectrumTurboSound:
            [[fallthrough]];
        case TargetHardware::spectrumNext:
            [[fallthrough]];
        default:
            // Other platforms don't care.
            break;
    }

    const auto z80Mixer = originalZ80Mixer & 0b00111111U;
    const auto cppYmMixer = static_cast<unsigned int>(psgRegisters.getMixer());

    // Volumes.
    const auto cppVolumeChannel1 = static_cast<unsigned int>(psgRegisters.getVolume(0));
    const auto cppVolumeChannel2 = static_cast<unsigned int>(psgRegisters.getVolume(1));
    const auto cppVolumeChannel3 = static_cast<unsigned int>(psgRegisters.getVolume(2));

    const auto z80VolumeChannel1 = readPsgData(PsgValues::registerVolumeChannel1, psgIndex) & PsgValues::maskVolume;
    const auto z80VolumeChannel2 = readPsgData(PsgValues::registerVolumeChannel2, psgIndex) & PsgValues::maskVolume;
    const auto z80VolumeChannel3 = readPsgData(PsgValues::registerVolumeChannel3, psgIndex) & PsgValues::maskVolume;

    if (z80VolumeChannel1 != cppVolumeChannel1) {
        // An optimization can be that volume on Z80 is not set if the mixer is off (and the volume is not 0x10, no hardware envelope).
        // However, the noise mixer must also be to off, else the volume is important!
        if (((cppVolumeChannel1 < 0x10U) && (z80VolumeChannel1 < 0x10U) && ((z80Mixer & 0b00000001U) != 0U)
            && ((z80Mixer & 0b00001000U) != 0U) && ((cppYmMixer & 0b00001000U) != 0U))
            ||
            (((cppVolumeChannel1 & 0b10000U) > 0U) && ((z80VolumeChannel1 & 0b10000U) > 0U))      // Both hardware.
            ) {
            // Optimization. No error.
        } else {
            // Error. If within tolerance, ok. The error count must also stay within range.
            if ((++errorCountInVolume > toleratedErrorsInVolume) || (std::abs(static_cast<int>(cppVolumeChannel1 - z80VolumeChannel1)) > possibleAbsoluteDifferenceInVolume)) {
                return false;
            }
        }
    }
    if (z80VolumeChannel2 != cppVolumeChannel2) {
        // An optimization can be that volume on Z80 is not set if the mixer is off (and the volume is not 0x10, no hardware envelope).
        // However, the noise mixer must also be to off, else the volume is important!
        if (((cppVolumeChannel2 < 0x10U) && (z80VolumeChannel2 < 0x10U) && ((z80Mixer & 0b00000010U) != 0U)
            && ((z80Mixer & 0b00010000U) != 0U) && ((cppYmMixer & 0b00010000U) != 0U))
            ||
            (((cppVolumeChannel2 & 0b10000U) > 0U) && ((z80VolumeChannel2 & 0b10000U) > 0U))      // Both hardware.
            ) {
            // Optimization. No error.
        } else {
            // Error. If within tolerance, ok. The error count must also stay within range.
            if ((++errorCountInVolume > toleratedErrorsInVolume) || (std::abs(static_cast<int>(cppVolumeChannel2 - z80VolumeChannel2)) > possibleAbsoluteDifferenceInVolume)) {
                return false;
            }
        }
    }
    if (z80VolumeChannel3 != cppVolumeChannel3) {
        // An optimization can be that volume on Z80 is not set if the mixer is off (and the volume is not 0x10, no hardware envelope).
        // However, the noise mixer must also be to off, else the volume is important!
        if (((cppVolumeChannel3 < 0x10U) && (z80VolumeChannel3 < 0x10U) && ((z80Mixer & 0b00000100U) != 0U) && ((z80Mixer & 0b00100000U) != 0U)
            && ((cppYmMixer & 0b00100000U) != 0U))
            ||
            (((cppVolumeChannel3 & 0b10000U) > 0U) && ((z80VolumeChannel3 & 0b10000U) > 0U))      // Both hardware.
            ) {
            // Optimization. No error.
        } else {
            // Error. If within tolerance, ok. The error count must also stay within range.
            if ((++errorCountInVolume > toleratedErrorsInVolume) || (std::abs(static_cast<int>(cppVolumeChannel3 - z80VolumeChannel3)) > possibleAbsoluteDifferenceInVolume)) {
                return false;
            }
        }
    }

    // Hardware envelope? Only if necessary.
    const auto isHardwareEnvelope = (((cppVolumeChannel1 & PsgValues::maskVolumeHardwareVolumeFlag) != 0U)
        || ((cppVolumeChannel2 & PsgValues::maskVolumeHardwareVolumeFlag) != 0U)
        || ((cppVolumeChannel3 & PsgValues::maskVolumeHardwareVolumeFlag) != 0U));
    if (isHardwareEnvelope) {
		// The CPC Memory is supposed to manage R13 and 255. The native players don't handle that, so the client must put it by itself BEFORE playing the CPC frame
		// for example via the markHardwareEnvelopeRegisterAsNonRetrig method of the Z80EmulatorHelper.
		const auto dataFromMemory = static_cast<int>(readPsgData(PsgValues::registerHardwareEnvelope, psgIndex));         // Can be 0-15 or 255.
        const auto cppYmHardwareEnvelope = psgRegisters.getHardwareEnvelopeAndRetrig().getEnvelope();

        // If the latest hardware envelope is unknown (16), sets it from the CPP YM hardware envelope value.
        if (previousHardwareEnvelope == 16) {
            previousHardwareEnvelope = cppYmHardwareEnvelope;
        }

        if (dataFromMemory != cppYmHardwareEnvelope) {
            // If 0-15 and yet different, abnormal.
            if ((dataFromMemory >= 0) && (dataFromMemory <= 15)) {
                return false;
            }
            // Should be 255.
            if (dataFromMemory != 255) {
                // A value that is not 0-15 or 255?? Abnormal.
                jassertfalse;
                return false;
            }
            // 255. OK if not retrig (from CPP), and the previous hardware envelope is the same, which means there is no retrig on Z80.
            if ((psgRegisters.getHardwareEnvelopeAndRetrig().isRetrig()) || (previousHardwareEnvelope != cppYmHardwareEnvelope)) {
			    return false;
            }
		}
        // Stores the previous hardware envelope, (never 255).
        jassert((cppYmHardwareEnvelope >= 0) && (cppYmHardwareEnvelope <= 15));
        previousHardwareEnvelope = cppYmHardwareEnvelope;
        
           
        // Compares the hardware period (LSB, then MSB).
        const auto cppHardwarePeriod = static_cast<unsigned int>(psgRegisters.getHardwarePeriod());
        const auto dataFromMemoryLsb = readPsgData(PsgValues::registerHardwareFrequencyLSB, psgIndex) & PsgValues::maskHardwarePeriodLSB;
        const auto dataFromMemoryMsb = readPsgData(PsgValues::registerHardwareFrequencyMSB, psgIndex) & PsgValues::maskHardwarePeriodMSB;
        const auto z80HardwarePeriod = dataFromMemoryLsb + dataFromMemoryMsb * 256U;
        // Error. If within tolerance, ok. The error count must also stay within range.
        if ((cppHardwarePeriod != z80HardwarePeriod)
            && (std::abs(static_cast<int>(cppHardwarePeriod) - static_cast<int>(z80HardwarePeriod)) > possibleAbsoluteDifferenceInHardwarePeriod)) {
            if (++errorCountInHardwarePeriod > errorCountToleranceInHardwarePeriod) {
                return false;
            }
        }
    }

    // Software period. Which channels are open?
    const auto isSoftwarePeriodChannel1 = (((z80Mixer & 0b001U) == 0U) && (cppVolumeChannel1 > 0U));
    const auto isSoftwarePeriodChannel2 = (((z80Mixer & 0b010U) == 0U) && (cppVolumeChannel2 > 0U));
    const auto isSoftwarePeriodChannel3 = (((z80Mixer & 0b100U) == 0U) && (cppVolumeChannel3 > 0U));
    // Software period, channel 1? Only if necessary.
    if (isSoftwarePeriodChannel1) {
        const auto cppSoftwarePeriod = static_cast<unsigned int>(psgRegisters.getSoftwarePeriod(0));
        const auto dataFromMemoryLsb = readPsgData(PsgValues::registerSoftwareFrequencyChannel1LSB, psgIndex) & PsgValues::maskSoftwarePeriodLSB;
        const auto dataFromMemoryMsb = readPsgData(PsgValues::registerSoftwareFrequencyChannel1MSB, psgIndex) & PsgValues::maskSoftwarePeriodMSB;
        const auto z80SoftwarePeriod = dataFromMemoryLsb + dataFromMemoryMsb * 256U;
        // Tolerance?
        if ((cppSoftwarePeriod != z80SoftwarePeriod)
            && (std::abs(static_cast<int>(cppSoftwarePeriod) - static_cast<int>(z80SoftwarePeriod)) > possibleAbsoluteDifferenceInSoftwarePeriod)) {
            return false;
        }
    }

    // Allow me a bit of duplication...
    // Software period, channel 2? Only if necessary.
    if (isSoftwarePeriodChannel2) {
        const auto cppSoftwarePeriod = static_cast<unsigned int>(psgRegisters.getSoftwarePeriod(1));
        const auto dataFromMemoryLsb = readPsgData(PsgValues::registerSoftwareFrequencyChannel2LSB, psgIndex) & PsgValues::maskSoftwarePeriodLSB;
        const auto dataFromMemoryMsb = readPsgData(PsgValues::registerSoftwareFrequencyChannel2MSB, psgIndex) & PsgValues::maskSoftwarePeriodMSB;
        const auto z80SoftwarePeriod = dataFromMemoryLsb + dataFromMemoryMsb * 256U;
        // Tolerance?
        if ((cppSoftwarePeriod != z80SoftwarePeriod)
            && (std::abs(static_cast<int>(cppSoftwarePeriod) - static_cast<int>(z80SoftwarePeriod)) > possibleAbsoluteDifferenceInSoftwarePeriod)) {
            return false;
        }
    }

    // Software period, channel 3? Only if necessary.
    if (isSoftwarePeriodChannel3) {
        const auto cppSoftwarePeriod = static_cast<unsigned int>(psgRegisters.getSoftwarePeriod(2));
        const auto dataFromMemoryLsb = readPsgData(PsgValues::registerSoftwareFrequencyChannel3LSB, psgIndex) & PsgValues::maskSoftwarePeriodLSB;
        const auto dataFromMemoryMsb = readPsgData(PsgValues::registerSoftwareFrequencyChannel3MSB, psgIndex) & PsgValues::maskSoftwarePeriodMSB;
        const auto z80SoftwarePeriod = dataFromMemoryLsb + dataFromMemoryMsb * 256U;
        // Tolerance?
        if ((cppSoftwarePeriod != z80SoftwarePeriod)
            && (std::abs(static_cast<int>(cppSoftwarePeriod) - static_cast<int>(z80SoftwarePeriod)) > possibleAbsoluteDifferenceInSoftwarePeriod)) {
            return false;
        }
    }

    // Mixer.
    if (cppYmMixer != z80Mixer) {
        // The mixer can be different because some optimizations can be performed.
        // If the volume of a channel is 0, the mixer may be optimized to off, no need to encode the volume.
        if ((cppVolumeChannel1 > 0U) && ((cppYmMixer & 0b00000001U) != (z80Mixer & 0b00000001U))) {
            return false;
        }
        if ((cppVolumeChannel2 > 0U) && ((cppYmMixer & 0b00000010U) != (z80Mixer & 0b00000010U))) {
            return false;
        }
        if ((cppVolumeChannel3 > 0U) && ((cppYmMixer & 0b00000100U) != (z80Mixer & 0b00000100U))) {
            return false;
        }
        // The same for the noise. If the volume is 0, the mixer may be optimized, no need to encode the noise.
        if ((cppVolumeChannel1 > 0U) && ((cppYmMixer & 0b00001000U) != (z80Mixer & 0b00001000U))) {
            return false;
        }
        if ((cppVolumeChannel2 > 0U) && ((cppYmMixer & 0b00010000U) != (z80Mixer & 0b00010000U))) {
            return false;
        }
        if ((cppVolumeChannel3 > 0U) && ((cppYmMixer & 0b00100000U) != (z80Mixer & 0b00100000U))) {
            return false;
        }
    }

    const auto isNoise = ((z80Mixer & 0b00111000U) != 0b00111000U);                                             // Noise? Only if necessary.
    if (isNoise) {
        const auto z80Noise = readPsgData(PsgValues::registerNoise, psgIndex) & PsgValues::maskNoise;
        const auto cppNoise = static_cast<unsigned int>(psgRegisters.getNoise());
        if (cppNoise != z80Noise) {
            // The tolerance error must stay within limits.
            if (++errorCountInNoise > toleratedErrorsInNoise) {
                return false;
            }
        }
    }

    return true;
}
/*
bool Z80EmulatorHelper::compareSharpMZ700PSGFrame(const PsgRegisters& psgRegisters) noexcept
{
    // Same mixer? Only the channel 1 is useful on the SharpMZ700.
    // 0 = open channel. 1 = closed channel (no sound).
    const auto z80Mixer = (z80Memory[static_cast<size_t>(addressSharpMz700MixerState)] & 0b1U);
    const auto cppYmMixer = (static_cast<unsigned int>(psgRegisters.getMixer()) & 0b1U);
    if (z80Mixer != cppYmMixer) {
        return false;
    }

    // If no mix, no need to check the period.
    if (z80Mixer != 0) {
        return true;
    }

    // Checks the software period.
    int cppValR0 = psgRegisters.getValueFromRegister(0);
    int z80ValR0 = z80Memory[addressSharpMz700SoftwarePeriodLSB];

    int cppValR1 = psgRegisters.getValueFromRegister(1);
    int z80ValR1 = z80Memory[addressSharpMz700SoftwarePeriodMSB];

    return (cppValR0 == z80ValR0) && (cppValR1 == z80ValR1);
}*/

void Z80Emulator::setPsgFrequencyToSong(Song& song, const TargetHardware pTargetHardware) noexcept
{
    const auto psgFrequency = getPsgFrequency(pTargetHardware);

    // Forces the PSG frequency of the Song.
    for (const auto& subsongId : song.getSubsongIds()) {
        song.performOnSubsong(subsongId, [&](Subsong& subsong) {
            auto psgs = subsong.getPsgs();
            std::vector<Psg> newPsgs;
            newPsgs.reserve(psgs.size());

            for (const auto& psg : psgs) {
                newPsgs.push_back(psg.withPsgFrequency(psgFrequency));
            }

            subsong.setPsgs(newPsgs);
        });
    }
}

int Z80Emulator::getPsgFrequency(const TargetHardware targetHardware) noexcept
{
    switch (targetHardware) {
        case TargetHardware::cpc: [[fallthrough]];
        case TargetHardware::pcw: [[fallthrough]];
        case TargetHardware::pcwTurboSound: [[fallthrough]];
        case TargetHardware::cpcPlayCity:
            return PsgFrequency::psgFrequencyCPC;

        case TargetHardware::spectrum: [[fallthrough]];
        case TargetHardware::spectrumNext: [[fallthrough]];
        case TargetHardware::spectrumTurboSound:
            return PsgFrequency::psgFrequencySpectrum;

        case TargetHardware::pentagon:
            return PsgFrequency::psgFrequencyPentagon128K;

        case TargetHardware::msx: [[fallthrough]];
        case TargetHardware::msxFpgaPsg: [[fallthrough]];
        case TargetHardware::svi: [[fallthrough]];
        case TargetHardware::msxDarky:
            return PsgFrequency::psgFrequencyMsxAndSvi;

        case TargetHardware::sharpMz:
            return PsgFrequency::psgFrequencySharpMz700;

        default:
            jassertfalse;       // Unknown hardware!
            return 0;
    }
}

void Z80Emulator::onOutPort(const unsigned short port, const unsigned char value) noexcept
{
    if ((targetHardware == TargetHardware::cpc) || (targetHardware == TargetHardware::cpcPlayCity)) {
        auto foundSpecificPsg = false;
        if (targetHardware == TargetHardware::cpcPlayCity) {
            foundSpecificPsg = true;
            if (port == 0xf988U) {                // PSG 1 register.
                selectRegister(0, static_cast<int>(value));
            } else if (port == 0xf888U) {         // PSG 1 value.
                setPsgData(0, value);
            } else if (port == 0xf984U) {         // PSG 3 register.
                selectRegister(2, static_cast<int>(value));
            } else if (port == 0xf884U) {         // PSG 3 value.
                setPsgData(2, value);

            } else if (
                // Don't do anything: initializing the PlayCity.
                (port == 0xf880U) ||
                // Don't do anything: Setting the clock generator/frequency index.
                ((port == 0xf8ffU) && (value == 0xffU))) {
            } else {
                // PlayCity, but not any of the "special PSG" port. So it must be the middle "normal" PSG in the middle.
                foundSpecificPsg = false;
            }
        }

        if (!foundSpecificPsg) {
            // On a real CPC, uses the normal CPC (0), else use the middle one (1), for PlayCity.
            const auto psgIndexToUse = (targetHardware == TargetHardware::cpc) ? 0 : 1;
            const auto portMsb = port / 256;
            // CPC or PlayCity middle PSG.

            // Sequence is:
            // port  / value

            // #f6xx / #c0
            // #f4xx / port
            // #f6xx / #0
            // #f4xx / value
            // #f6xx / #80

            if ((portMsb == 0xf6) && (value == 0xc0)) {
                nextCallIsRegister = true;
                nextCallIsValue = false;
            } else if ((portMsb == 0xf6) && (value == 0U)) {
                nextCallIsRegister = false;
                nextCallIsValue = true;
            } else if (nextCallIsRegister) {
                nextCallIsRegister = false;
                jassert(value < 16U);
                selectRegister(psgIndexToUse, static_cast<int>(value));
            } else if (nextCallIsValue) {
                nextCallIsValue = false;
                setPsgData(psgIndexToUse, value);
            }
        }
    } else if ((targetHardware == TargetHardware::msx) || (targetHardware == TargetHardware::msxFpgaPsg) || (targetHardware == TargetHardware::msxDarky)
        || (targetHardware == TargetHardware::pcw) || (targetHardware == TargetHardware::svi)
    ) {
        // MSX:
        // 0xa0 / port
        // 0xa1 / value
        // MSX FPGA:
        // 0x10 / port      -> PSG 2, PSG1 being the same as MSX.
        // 0x11 / value
        // MSX Darky:
        // 0x44 / port      -> PSG 1.
        // 0x45 / value
        // 0x4c / port      -> PSG 2.
        // 0x4d / value
        // PCW:
        // 0xaa / port
        // 0xab / value
        // SVI:
        // 0x88 / port
        // 0x8c / value
        auto registerAddressPsg1 = 0xa0U;
        auto valueAddressPsg1 = 0xa1U;
        auto registerAddressPsg2 = 0U;      // Sentinel value.
        auto valueAddressPsg2 = 0U;         // Sentinel value.
        if (targetHardware == TargetHardware::msxFpgaPsg) {
            registerAddressPsg2 = 0x10U;
            valueAddressPsg2 = 0x11U;
        } else if (targetHardware == TargetHardware::msxDarky) {
            registerAddressPsg1 = 0x44U;
            valueAddressPsg1 = 0x45U;
            registerAddressPsg2 = 0x4cU;
            valueAddressPsg2 = 0x4dU;
        } else if (targetHardware == TargetHardware::pcw) {
            registerAddressPsg1 = 0xaaU;
            valueAddressPsg1 = 0xabU;
        } else if (targetHardware == TargetHardware::svi) {
            registerAddressPsg1 = 0x88U;
            valueAddressPsg1 = 0x8cU;
        }

        if (port == registerAddressPsg1) {             // New register selected, for PSG 1.
            selectRegister(0, value);
        } else if (port == valueAddressPsg1) {
            setPsgData(0, value);
        } else if (port == registerAddressPsg2) {      // New register selected, for PSG 2.
            selectRegister(1, value);
        } else if (port == valueAddressPsg2) {
            setPsgData(1, value);
        } else if ((port == 0x40U) && (value == 0xaaU) && (targetHardware == TargetHardware::msxDarky)) {
            // Nothing to do, only init Darky.
        } else {
            jassertfalse;            // Wrong port addressed.
        }
    } else if (targetHardware == TargetHardware::pcwTurboSound) {
        // PCW TurboSound:
        // Select a PSG: 0xaa / #ff (psg 1) or #fe (psg 2).
        // 0xaa / port
        // 0xab / value
        constexpr auto registerAddressPsg = 0xaaU;
        constexpr auto valueAddressPsg1 = 0xabU;
        if (port == registerAddressPsg) {
            if (value == 0xff) {
                pcwTurboSoundIndexPsgSelected = 0;
            } else  if (value == 0xfe) {
                pcwTurboSoundIndexPsgSelected = 1;
            } else {
                // Not a PSG selection, but a change of register.
                selectRegister(pcwTurboSoundIndexPsgSelected, value);
            }
        } else if (port == valueAddressPsg1) {
            setPsgData(pcwTurboSoundIndexPsgSelected, value);
        } else {
            jassertfalse;            // Wrong port addressed.
        }
    } else if ((targetHardware == TargetHardware::spectrum) || (targetHardware == TargetHardware::pentagon)
            || (targetHardware == TargetHardware::spectrumNext) || (targetHardware == TargetHardware::spectrumTurboSound)) {
        // Spectrum/pentagon or Spectrum Turbosound/SpecNext.
        const auto turboSoundOrSpecNext = ((targetHardware == TargetHardware::spectrumNext) || (targetHardware == TargetHardware::spectrumTurboSound));
        const auto specNext = (targetHardware == TargetHardware::spectrumNext);
        const auto psgIndexToUse = turboSoundOrSpecNext ? spectrumIndexPsgSelected : 0;
        if (port == 0xfffdU) {    // New register selected, or PSG selection for TurboSound.
            if (turboSoundOrSpecNext && (value == 0xffU)) {
                // Turbosound or SpecNext: select PSG 1.
                spectrumIndexPsgSelected = 0;
            } else if (turboSoundOrSpecNext && (value == 0xfeU)) {
                // Turbosound or SpecNext: select PSG 2.
                spectrumIndexPsgSelected = 1;
            } else if (specNext && (value == 0xfdU)) {
                // SpecNext (only): select PSG 3.
                spectrumIndexPsgSelected = 2;
            } else {
                selectRegister(psgIndexToUse, static_cast<int>(value));
            }
        } else if (port == 0xbffdU) {
            setPsgData(psgIndexToUse, value);
        } else {
            abort();            // Wrong port addressed.    // NOLINT(clion-misra-cpp2008-18-0-3)
        }
    } else {
        // Unhandled hardware.
        abort();   // NOLINT(clion-misra-cpp2008-18-0-3)
    }
}

}   // namespace arkostracker
