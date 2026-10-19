#include "../catch.hpp"

#include "../../source/player/PsgRegisters.h"
#include "../../source/player/PsgRegistersConverter.h"
#include "../../source/utils/PsgValues.h"

namespace arkostracker 
{

TEST_CASE("encode as notes, no soft no hard", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        {
            // No sound.
            const PsgRegisters registers;

            registerList.push_back(registers);
        }
        {
            PsgRegisters registers;
            registers.setVolume(channelIndex, 1);
            registers.setNoise(1);
            registers.setMixerNoiseState(channelIndex, true);

            registerList.push_back(registers);
        }
        {
            PsgRegisters registers;
            registers.setVolume(channelIndex, 15);
            registers.setNoise(31);
            registers.setMixerNoiseState(channelIndex, true);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildNoSoftwareNoHardwareCell()));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(1, 1)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 31)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as notes, soft only", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        {
            // 0.
            PsgRegisters registers;
            registers.setSoftwarePeriod(channelIndex, 1804);        // 13th note.
            registers.setVolume(channelIndex, 10);
            registers.setMixerSoundState(channelIndex, true);

            registerList.push_back(registers);
        }
        {
            // 1: Another note: arpeggio will be used.
            PsgRegisters registers;
            registers.setSoftwarePeriod(channelIndex, 1703);        // 14th note.
            registers.setVolume(channelIndex, 15);
            registers.setMixerSoundState(channelIndex, true);

            registerList.push_back(registers);
        }
        {
            // 2: Another note: arpeggio will be used.
            PsgRegisters registers;
            registers.setSoftwarePeriod(channelIndex, 3608);        // 1st note.
            registers.setVolume(channelIndex, 1);
            registers.setMixerSoundState(channelIndex, true);
            registers.setNoise(18);
            registers.setMixerNoiseState(channelIndex, true);

            registerList.push_back(registers);
        }
        {
            // 3: Same note as the first, but with a positive pitch.
            PsgRegisters registers;
            registers.setSoftwarePeriod(channelIndex, 1804 + 1);        // 13th note + pitch.
            registers.setVolume(channelIndex, 2);
            registers.setMixerSoundState(channelIndex, true);
            registers.setNoise(31);
            registers.setMixerNoiseState(channelIndex, true);

            registerList.push_back(registers);
        }
        {
            // 4: Same note as the first, but with a negative pitch.
            PsgRegisters registers;
            registers.setSoftwarePeriod(channelIndex, 1911 -10);        // 12th note - pitch.
            registers.setVolume(channelIndex, 14);
            registers.setMixerSoundState(channelIndex, true);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(10)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 1)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(1, 18, 0, -1)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(2, 31, 0, 0, -1)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(14, 0, 11, -1, 10)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as notes, hard only", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        {
            // 0.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setHardwarePeriod(1804);        // 13th note.
            registers.setHardwareEnvelopeAndRetrig(8, false);

            registerList.push_back(registers);
        }
        {
            // 1. Higher note, noise.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setHardwarePeriod(1607);        // 15th note.
            registers.setMixerNoiseState(channelIndex, true);
            registers.setNoise(31);
            registers.setHardwareEnvelopeAndRetrig(10, false);

            registerList.push_back(registers);
        }
        {
            // 2. Lower note, noise, retrig.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setHardwarePeriod(1607);        // 15th note.
            registers.setMixerNoiseState(channelIndex, true);
            registers.setNoise(1);
            registers.setHardwareEnvelopeAndRetrig(12, true);

            registerList.push_back(registers);
        }
        {
            // 3. Lower note, positive shift, retrig.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setHardwarePeriod(2025 + 5);        // 11th note + shift.
            registers.setHardwareEnvelopeAndRetrig(12, true);

            registerList.push_back(registers);
        }
        {
            // 4. Lower note, negative shift, noise.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setHardwarePeriod(2025 - 10);        // 11th note + shift.
            registers.setHardwareEnvelopeAndRetrig(15, false);
            registers.setMixerNoiseState(channelIndex, true);
            registers.setNoise(17);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardOnly(0, 0, 0, 0, 8)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardOnly(31, 2, 0, 0, 10)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardOnly(1, 2, 0, 0, 12, true)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardOnly(0, 10, -1, -5, 12, true)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardOnly(17, 10, -1, 10, 15)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as notes, soft to hard", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        {
            // 0. Ratio = 4.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setMixerSoundState(channelIndex, true);
            registers.setSoftwarePeriod(channelIndex, 956);         // 24th note.
            registers.setHardwarePeriod(60);                               // 72nd note.
            registers.setHardwareEnvelopeAndRetrig(8, false);

            registerList.push_back(registers);
        }
        {
            // 1. Ratio = 4 + software shift.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setNoise(12);
            registers.setMixerNoiseState(channelIndex, true);
            registers.setMixerSoundState(channelIndex, true);
            registers.setSoftwarePeriod(channelIndex, 956 + 1);     // 24th note + shift.
            registers.setHardwarePeriod(60);                            // 72nd note, then shift has been lost in the division.
            registers.setHardwareEnvelopeAndRetrig(8, false);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(12, 0, 0, -1)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as notes, soft and hard, Ben Daglish", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        {
            // 0. Ratio = 4.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setMixerSoundState(channelIndex, true);
            registers.setSoftwarePeriod(channelIndex, 956);             // 24th note.
            registers.setHardwarePeriod(4);
            registers.setHardwareEnvelopeAndRetrig(10, false);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell(
                PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0,
                0, 0,
                4, 0, 0, 0, 10, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)
                ));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as notes, soft and hard", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        {
            // 0. Two different notes.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setMixerSoundState(channelIndex, true);
            registers.setSoftwarePeriod(channelIndex, 956);             // 24th note.
            registers.setHardwarePeriod(716);                           // 29th note.
            registers.setHardwareEnvelopeAndRetrig(15, false);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell(
                PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0,
                0, 0,
                0, 29 - 24, 0, 0, 15, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)
                ));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as notes, hard to soft", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        {
            // 0. Ratio = 4.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setMixerSoundState(channelIndex, true);
            registers.setHardwarePeriod(60);                        // 72nd note.
            registers.setSoftwarePeriod(channelIndex, 60 * 16);     // 960 instead of 956.
            registers.setHardwareEnvelopeAndRetrig(12, false);

            registerList.push_back(registers);
        }
        {
            // 0. Ratio = 4 + hardware shift.
            PsgRegisters registers;
            registers.setVolume(channelIndex, 16);
            registers.setMixerSoundState(channelIndex, true);
            registers.setHardwarePeriod(60 - 1);                        // 72nd note + shift.
            registers.setSoftwarePeriod(channelIndex, (60 - 1) * 16);
            registers.setHardwareEnvelopeAndRetrig(12, true);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardToSoft(0, 0, 0, 0, 4, 12)));
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardToSoft(0, 0, 0, 1, 4, 12, true)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

/** This was revealed by Zik. A high pitch from an original note provokes a wrong arp+pitch value. */
TEST_CASE("encode as notes, soft only, high pitch", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        std::vector<PsgRegisters> registerList;

        for (const auto period : { 0xef, 0xe7, 0xdf, 0xd7, 0xcf, 0xc7, 0xbf }){
            PsgRegisters registers;
            registers.setSoftwarePeriod(channelIndex, period);
            registers.setVolume(channelIndex, 15);
            registers.setMixerSoundState(channelIndex, true);

            registerList.push_back(registers);
        }

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, false);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 0, 0, 0)));        // 0xef = base note.
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 1, 0, -6)));       // 0xe1 + pitch.
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 1, 0, 2)));        // 0xe1 + pitch.
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 2, 0, -2)));       // 0xd5 + pitch.
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 2, 0, 6)));        // 0xd5 + pitch.
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 3, 0, 2)));        // 0xc9 + pitch.
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 0, 4, 0, -1)));       // 0xbe + pitch.
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

// =============================================================================

TEST_CASE("encode as forced periods, no soft no hard", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;
        registerList.emplace_back();

        // Converts.
        PsgRegistersConverter converter(1000000, 2000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildNoSoftwareNoHardwareCell()));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, no soft no hard with noise", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, false);
        registers.setMixerNoiseState(channelIndex, true);
        registers.setVolume(channelIndex, 15);
        registers.setNoise(31);
        registers.setSoftwarePeriod(channelIndex, 1000);        // Just for fun.

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(1000000, 2000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 31)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, soft only", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, true);
        registers.setVolume(channelIndex, 10);
        registers.setSoftwarePeriod(channelIndex, 100);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(1000000, 2000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(10, 0, 0, 0, 0, true, 200)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, soft only with noise", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, true);
        registers.setMixerNoiseState(channelIndex, true);
        registers.setVolume(channelIndex, 15);
        registers.setNoise(5);
        registers.setSoftwarePeriod(channelIndex, 1000);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(2000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 2, 0, 0, 0, true, 500)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, soft only with noise 2", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, true);
        registers.setMixerNoiseState(channelIndex, true);
        registers.setVolume(channelIndex, 15);
        registers.setNoise(5);
        registers.setSoftwarePeriod(channelIndex, 1000);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(15, 5, 0, 0, 0, true, 1000)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, hard only", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, false);
        registers.setVolume(channelIndex, 16);
        registers.setHardwarePeriod(500);
        registers.setHardwareEnvelopeAndRetrig(10, false);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(1000000, 2000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardOnly(0, 0, 0, 0, 10, false, 1000)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, hard only with noise", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, false);
        registers.setMixerNoiseState(channelIndex, true);
        registers.setVolume(channelIndex, 16);
        registers.setNoise(31);
        registers.setHardwarePeriod(500);
        registers.setHardwareEnvelopeAndRetrig(14, true);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(2000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell::buildHardOnly(15, 0, 0, 0, 14, true, 250)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, soft and hard", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, true);
        registers.setVolume(channelIndex, 16);
        registers.setSoftwarePeriod(channelIndex, 500);
        registers.setHardwarePeriod(500);
        registers.setHardwareEnvelopeAndRetrig(8, false);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(2000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell(
                PsgInstrumentCellLink::softAndHard, 0, 0, 250, 0, 0, 0, 0,
                250, 0, 0, 0, 8, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, soft and hard, with noise", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, true);
        registers.setVolume(channelIndex, 16);
        registers.setNoise(31);
        registers.setMixerNoiseState(channelIndex, true);
        registers.setSoftwarePeriod(channelIndex, 500);
        registers.setHardwarePeriod(500);
        registers.setHardwareEnvelopeAndRetrig(9, true);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(1000000, 2000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell(
                PsgInstrumentCellLink::softAndHard, 0, 31, 1000, 0, 0, 0, 0,
                1000, 0, 0, 0, 9, true,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}

TEST_CASE("encode as forced periods, soft and hard, with noise 2", "[PsgRegistersConverter]")
{
    for (auto channelIndex = 0; channelIndex < 3; ++channelIndex) {
        // No sound.
        std::vector<PsgRegisters> registerList;

        PsgRegisters registers;
        registers.setMixerSoundState(channelIndex, true);
        registers.setVolume(channelIndex, 16);
        registers.setNoise(15);
        registers.setMixerNoiseState(channelIndex, true);
        registers.setSoftwarePeriod(channelIndex, 500);
        registers.setHardwarePeriod(3000);
        registers.setHardwareEnvelopeAndRetrig(13, false);

        registerList.push_back(registers);

        // Converts.
        PsgRegistersConverter converter(1000000, 1000000, 440);
        auto cells = converter.encodeAsInstrumentCells(registerList, channelIndex, true);
        size_t index = 0;
        REQUIRE(cells.at(index++).isMusicallyEqualTo(PsgInstrumentCell(
                PsgInstrumentCellLink::softAndHard, 0, 15, 500, 0, 0, 0, 0,
                3000, 0, 0, 0, 13, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
        REQUIRE((cells.size() == index));
        REQUIRE((cells.size() == registerList.size()));
    }
}


// ===================================================================

TEST_CASE("convertPeriods, double frequency", "[PsgRegistersConverter]")
{
    // Given.
    for (auto channelIndex = 0; channelIndex < PsgValues::channelCountPerPsg; ++channelIndex) {
        PsgRegisters psgRegisters;
        psgRegisters.setMixerSoundState(channelIndex, true);
        psgRegisters.setVolume(channelIndex, 16);
        psgRegisters.setNoise(8);
        psgRegisters.setMixerNoiseState(channelIndex, true);
        psgRegisters.setSoftwarePeriod(channelIndex, 1000);
        psgRegisters.setHardwarePeriod(3000);
        psgRegisters.setHardwareEnvelopeAndRetrig(13, false);

        constexpr auto sourcePsgFrequencyHz = 2000000;
        constexpr auto targetPsgFrequencyHz = 1000000;

        const auto resultRegisters = PsgRegistersConverter::convertPeriods(psgRegisters, sourcePsgFrequencyHz, targetPsgFrequencyHz);

        PsgRegisters expectedPsgRegisters;
        expectedPsgRegisters.setMixerSoundState(channelIndex, true);
        expectedPsgRegisters.setVolume(channelIndex, 16);
        expectedPsgRegisters.setNoise(4);
        expectedPsgRegisters.setMixerNoiseState(channelIndex, true);
        expectedPsgRegisters.setSoftwarePeriod(channelIndex, 500);
        expectedPsgRegisters.setHardwarePeriod(1500);
        expectedPsgRegisters.setHardwareEnvelopeAndRetrig(13, false);

        REQUIRE((resultRegisters == expectedPsgRegisters));
    }
}

TEST_CASE("convertPeriods, divide by 2 frequency", "[PsgRegistersConverter]")
{
    // Given.
    for (auto channelIndex = 0; channelIndex < PsgValues::channelCountPerPsg; ++channelIndex) {
        PsgRegisters psgRegisters;
        psgRegisters.setMixerSoundState(channelIndex, false);
        psgRegisters.setVolume(channelIndex, 16);
        psgRegisters.setNoise(20);
        psgRegisters.setMixerNoiseState(channelIndex, false);
        psgRegisters.setSoftwarePeriod(channelIndex, 1000);
        psgRegisters.setHardwarePeriod(3000);
        psgRegisters.setHardwareEnvelopeAndRetrig(13, true);

        constexpr auto sourcePsgFrequencyHz = 1000000;
        constexpr auto targetPsgFrequencyHz = 2000000;

        const auto resultRegisters = PsgRegistersConverter::convertPeriods(psgRegisters, sourcePsgFrequencyHz, targetPsgFrequencyHz);

        PsgRegisters expectedPsgRegisters;
        expectedPsgRegisters.setMixerSoundState(channelIndex, false);
        expectedPsgRegisters.setVolume(channelIndex, 16);
        expectedPsgRegisters.setNoise(31);
        expectedPsgRegisters.setMixerNoiseState(channelIndex, false);
        expectedPsgRegisters.setSoftwarePeriod(channelIndex, 2000);
        expectedPsgRegisters.setHardwarePeriod(6000);
        expectedPsgRegisters.setHardwareEnvelopeAndRetrig(13, true);

        REQUIRE((resultRegisters == expectedPsgRegisters));
    }
}

TEST_CASE("convertPeriods, divide to minimum frequencies", "[PsgRegistersConverter]")
{
    // Given.
    for (auto channelIndex = 0; channelIndex < PsgValues::channelCountPerPsg; ++channelIndex) {
        PsgRegisters psgRegisters;
        psgRegisters.setMixerSoundState(channelIndex, true);
        psgRegisters.setVolume(channelIndex, 16);
        psgRegisters.setNoise(2);
        psgRegisters.setMixerNoiseState(channelIndex, true);
        psgRegisters.setSoftwarePeriod(channelIndex, 2);
        psgRegisters.setHardwarePeriod(2);
        psgRegisters.setHardwareEnvelopeAndRetrig(13, false);

        constexpr auto sourcePsgFrequencyHz = 4000000;
        constexpr auto targetPsgFrequencyHz = 1000000;

        const auto resultRegisters = PsgRegistersConverter::convertPeriods(psgRegisters, sourcePsgFrequencyHz, targetPsgFrequencyHz);

        PsgRegisters expectedPsgRegisters;
        expectedPsgRegisters.setMixerSoundState(channelIndex, true);
        expectedPsgRegisters.setVolume(channelIndex, 16);
        expectedPsgRegisters.setNoise(1);
        expectedPsgRegisters.setMixerNoiseState(channelIndex, true);
        expectedPsgRegisters.setSoftwarePeriod(channelIndex, 1);
        expectedPsgRegisters.setHardwarePeriod(1);
        expectedPsgRegisters.setHardwareEnvelopeAndRetrig(13, false);

        REQUIRE((resultRegisters == expectedPsgRegisters));
    }
}

TEST_CASE("convertPeriods, keep digidrums bits", "[PsgRegistersConverter]")
{
    // Given.
    for (auto channelIndex = 0; channelIndex < PsgValues::channelCountPerPsg; ++channelIndex) {
        PsgRegisters psgRegisters;
        psgRegisters.setMixerSoundState(channelIndex, true);
        psgRegisters.setVolume(channelIndex, 31);                                // 5 bits on volume, for the digidrum number.
        psgRegisters.setNoise(10 + 0b11100000);
        psgRegisters.setMixerNoiseState(channelIndex, true);
        psgRegisters.setValue(0 + (2 * channelIndex), 0x7c);            // Useless bits on software are kept.
        psgRegisters.setValue(1 + (2 * channelIndex), 1U | 0b11110000U);
        psgRegisters.setHardwarePeriod(0xffff);
        psgRegisters.setHardwareEnvelopeAndRetrig(13, false);

        constexpr auto sourcePsgFrequencyHz = 2000000;
        constexpr auto targetPsgFrequencyHz = 1000000;

        const auto resultRegisters = PsgRegistersConverter::convertPeriods(psgRegisters, sourcePsgFrequencyHz, targetPsgFrequencyHz);

        PsgRegisters expectedPsgRegisters;
        expectedPsgRegisters.setMixerSoundState(channelIndex, true);
        expectedPsgRegisters.setVolume(channelIndex, 31);
        expectedPsgRegisters.setNoise(5);
        expectedPsgRegisters.setMixerNoiseState(channelIndex, true);
        expectedPsgRegisters.setValue(0 + (2 * channelIndex), 0x3e + 128);
        expectedPsgRegisters.setValue(1 + (2 * channelIndex), 0U | 0b11110000U);
        expectedPsgRegisters.setHardwarePeriod(0x7fff);
        expectedPsgRegisters.setHardwareEnvelopeAndRetrig(13, false);

        REQUIRE((resultRegisters == expectedPsgRegisters));
    }
}

}   // namespace arkostracker
