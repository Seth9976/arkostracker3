#pragma once

#include <juce_core/juce_core.h>

#include "../../../thirdParty/z80emulatorLibz80/mmu.h"
#include "../../../thirdParty/z80emulatorLibz80/z80.hpp"
#include "TargetHardware.h"

namespace arkostracker
{

class PsgRegisters;
class Song;

/** Wrapper around the low-level Z80 emulator. */
class Z80Emulator
{
public:
    /**
     * Constructor. Initializes a Z80, and an empty MMU.
     * @param targetHardware useful to know how to handle the PSG ports.
     */
    explicit Z80Emulator(TargetHardware targetHardware) noexcept;

    /**
     * Injects the given MemoryBlock into the CPC memory.
     * @param memoryBlock the block to load.
     * @param address where to load the block. Must be < 0xffff.
     */
    void injectData(const juce::MemoryBlock& memoryBlock, unsigned int address) noexcept;

    /**
     * Runs the Z80 emulator till a RST#38 is found.
     * The stack pointer is reset to an initial value.
     * @param pc the Program Counter to start with.
     * @param maximumNops how many nops before giving up.
     * @return how many cycles have been spent, or -1 if an error occurred.
     */
    int runTillRst38(int pc, int maximumNops = 999999) noexcept;

    /**
     * Runs the Z80 emulator till the end address is reached.
     * The stack pointer is reset to an initial value.
     * @param pc the Program Counter to start with.
     * @param endAddress the end address.
     * @param sp the stack pointer.
     * @param maximumNops how many nops before giving up.
     * @return how many cycles have been spent, or -1 if an error occurred.
     */
    int runTill(unsigned short pc, unsigned short endAddress, unsigned short sp, int maximumNops = 999999) noexcept;

    /**
     * Reads a PSG data. The data comes from an internal array, which must have been filled by
     * the MMU upon writing on the right IO depending on the hardware (#F4/#F6 on CPC).
     * @param address the address.
     * @param psgIndex the psg index (>=0).
     * @return the data.
     */
    unsigned int readPsgData(int address, int psgIndex) noexcept;

	/** Sets to the hardware envelope register to 255. Useful for testing. */
    void markHardwareEnvelopeRegisterAsNonRetrig(int psgIndex) noexcept;

    /**
     * Compares one PSG register with the current *static* data from the CPC IO Memory.
     * False is returned if it doesn't match, unless an error count is tolerated.
     * If the error count has reached the maximum number, false is returned.
     * IMPORTANT: To test easily the R13 retrig or not, we suppose the R13 has been filled with either 255 (no retrig) or the hard value. The
     * R13 (in the Z80 IO memory) should be filled with 255 BEFORE playing the frame (via the markHardwareEnvelopeRegisterAsNonRetrig method for example).
     * @param psgIndex the index of the PSG, to read on the hardware.
     * @param psgRegisters the PSG registers.
     * @param previousHardwareEnvelope the previous Hardware envelope (0-15, or 16 if unknown at first). Will be reset by this method.
     * @param errorCountInVolume the current error count for the volume.
     * @param toleratedErrorsInVolume may be >0 because the player may not compute the volume slide exactly the same way, but this may not be noticeable.
     * @param possibleAbsoluteDifferenceInVolume if the previous flag is >0, how many difference is tolerated (>=0).
     * @param errorCountInNoise the current error count for the noise.
     * @param toleratedErrorsInNoise in the "accurate" mode, this must be 0. However, in the not accurate, some mistakes can be tolerated, for the noise.
     * @param possibleAbsoluteDifferenceInSoftwarePeriod difference tolerated in software period (>=0). The AKM player can be more approximative.
     * @param possibleAbsoluteDifferenceInHardwarePeriod difference tolerated in hardware period (>=0). The AKM player can be more approximative.
     * @param errorCountToleranceInHardwarePeriod tolerance in the hardware period.
     * @param errorCountInHardwarePeriod the current error count for the hardware period.
     * @return true if everything went fine.
     */
    bool comparePsgFrame(int psgIndex, const PsgRegisters& psgRegisters, int& previousHardwareEnvelope,
                         int& errorCountInVolume, int toleratedErrorsInVolume, int possibleAbsoluteDifferenceInVolume,
                         int& errorCountInNoise, int toleratedErrorsInNoise, int possibleAbsoluteDifferenceInSoftwarePeriod,
                         int possibleAbsoluteDifferenceInHardwarePeriod, int errorCountToleranceInHardwarePeriod, int& errorCountInHardwarePeriod) noexcept;

    /**
     * Sets the PSG frequency to ALL the PSG of all the Subsongs of the given Song.
     * @param song the Song.
     * @param targetHardware the target hardware.
     */
    static void setPsgFrequencyToSong(Song& song, TargetHardware targetHardware) noexcept;

    /** @return the log of each instruction. Call setMustLogInstruction first! */
    std::vector<z80emulator::Z80::InstructionLog> getInstructionLog() const noexcept;

    /** If true, the instructions will be logged. */
    void setMustLogInstruction(bool mustLog) noexcept;

private:
    static constexpr auto stackPointer = 0x40;

    static constexpr auto registersPerPsg = 16;

    /**
     * Returns the psg frequency, in Hz, from the given target hardware.
     * @param targetHardware the hardware.
     * @return the frequency.
     */
    static int getPsgFrequency(TargetHardware targetHardware) noexcept;

    /**
     * Stores the register to use for a specific PSG.
     * @param psgIndex the PSG index (>=0).
     * @param psgRegister the register (0-15).
     */
    void selectRegister(int psgIndex, int psgRegister) noexcept;

    /** Sets a data to the given PSG. The selected register has been previously set for this PSG, use it directly The data is stored in an internal array. */
    void setPsgData(int psgIndex, unsigned int data) noexcept;

    /** Sets a data to the given PSG. */
    void setPsgData(int psgIndex, int registerIndex, unsigned int data) noexcept;

    /**
     * Called by the emulator whenever a OUT is performed.
     * @param port the port.
     * @param value the value.
     */
    void onOutPort(unsigned short port, unsigned char value) noexcept;

    const TargetHardware targetHardware;
    z80emulator::MMU mmu;
    z80emulator::Z80 z80;

    /** Holds the PSG data for many PSGs. */
    std::array<unsigned int, static_cast<size_t>(registersPerPsg) * 50U> psgData;
    /** Which register is selected on any PSG. */
    std::array<int, 50U> selectedRegisterOnPsg;

    bool nextCallIsRegister;
    bool nextCallIsValue;
    int spectrumIndexPsgSelected;               // The index of the PSG being selected. Only useful for Spectrum TurboSound or SpecNext.
    int pcwTurboSoundIndexPsgSelected;          // The index of the PSG being selected, for PCW TurboSound.
};

}   // namespace arkostracker
