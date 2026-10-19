#include "../catch.hpp"

#include "../helper/z80Emulator/Z80PlayerEmulator.h"

#include <BinaryData.h>

namespace arkostracker
{

/**
 * Tests the music with the Z80 player.
 * @param subsongIndexesToKeep the indexes of the Subsong to keep on the export. If empty, only the first one will be exported. Thus, the subsongIndexToPlay MUST be 0.
 * @param subsongIndexToPlay the Subsong indexes to play AFTER the Subsongs have been stripped.
 */
class Helper
{
public:
    static void testAkyMultiPsgMusic(const char* unzippedMusicData, const size_t unzippedMusicSize, const TargetHardware targetHardware,
                    const std::vector<int>& subsongIndexesToKeep = { }, const int subsongIndexToPlay = 0,
                    const std::map<TargetHardware, ExpectedStatistics>& targetToExpectedStatistics = { },
                    const int errorCountToleranceInVolume = 0, const int possibleAbsoluteDifferenceInVolume = 0,
                    const int possibleAbsoluteDifferenceInSoftwarePeriod = 0, const int possibleAbsoluteDifferenceInHardwarePeriod = 0,
                    const int errorCountToleranceInHardwarePeriod = 0,
                    const bool playTwice = false)       // False, because on some songs the sounds may continue on C++ but not Z80 in AKY.
    {
        Z80PlayerEmulator::testMusic(unzippedMusicData, unzippedMusicSize, subsongIndexToPlay, PlayerType::akyMultiPsg9Channels, targetToExpectedStatistics, subsongIndexesToKeep,
                                     errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                     possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod, errorCountToleranceInHardwarePeriod,
                                     playTwice, targetHardware);
    }
};
// ============================================================

TEST_CASE("AkyMultiPsgZ80Player, simple song 9 channels PlayCity", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1To9_xml, BinaryData::At2SimpleSoftSoundChannel1To9_xmlSize, TargetHardware::cpcPlayCity);
}

TEST_CASE("AkyMultiPsgZ80Player, simple song 9 channels SpecNext", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1To9_xml, BinaryData::At2SimpleSoftSoundChannel1To9_xmlSize, TargetHardware::spectrumNext);
}

TEST_CASE("AkyMultiPsgZ80Player, simple song 6 channels SpectrumTurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1To6_xml, BinaryData::At2SimpleSoftSoundChannel1To6_xmlSize, TargetHardware::spectrumTurboSound);
}

TEST_CASE("AkyMultiPsgZ80Player, simple song 6 channels PCW TurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1To6_xml, BinaryData::At2SimpleSoftSoundChannel1To6_xmlSize, TargetHardware::pcwTurboSound);
}

TEST_CASE("AkyMultiPsgZ80Player, simple song 6 channels MsxFgpa", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1To6_xml, BinaryData::At2SimpleSoftSoundChannel1To6_xmlSize, TargetHardware::msxFpgaPsg);
}

TEST_CASE("AkyMultiPsgZ80Player, simple song 6 channels MsxDarky", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1To6_xml, BinaryData::At2SimpleSoftSoundChannel1To6_xmlSize, TargetHardware::msxDarky);
}

TEST_CASE("AkyMultiPsgZ80Player, simple song 6 channels MsxFgpa, noise bug", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // Not related to the MSX or hardware, but bug when noise not present.
    Helper::testAkyMultiPsgMusic(BinaryData::At2AdeleSkyfall6ChannelsPattern0_xml, BinaryData::At2AdeleSkyfall6ChannelsPattern0_xmlSize, TargetHardware::msxFpgaPsg);
}

// =======================================================================================

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 1, CPC, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1_aks, BinaryData::At2SimpleSoftSoundChannel1_aksSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 1, SPECTRUM, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1_aks, BinaryData::At2SimpleSoftSoundChannel1_aksSize, TargetHardware::spectrum);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 1, MSX, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel1_aks, BinaryData::At2SimpleSoftSoundChannel1_aksSize, TargetHardware::msx);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 3, CPC, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel3_aks, BinaryData::At2SimpleSoftSoundChannel3_aksSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 3, SPECTRUM, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel3_aks, BinaryData::At2SimpleSoftSoundChannel3_aksSize, TargetHardware::spectrum);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 3, PCW, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel3_aks, BinaryData::At2SimpleSoftSoundChannel3_aksSize, TargetHardware::pcw);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 3, MSX, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftSoundChannel3_aks, BinaryData::At2SimpleSoftSoundChannel3_aksSize, TargetHardware::msx);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 1 to 3, CPC, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2Simple2_xml, BinaryData::At2Simple2_xmlSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 1 to 3, MSX, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2Simple2_xml, BinaryData::At2Simple2_xmlSize, TargetHardware::msx);
}

TEST_CASE("AkyMultiPsgZ80Player, Simple soft sound channel 1 to 3, SPECTRUM, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2Simple2_xml, BinaryData::At2Simple2_xmlSize, TargetHardware::spectrum);
}

TEST_CASE("AkyMultiPsgZ80Player, hard only and noise, 1 psg", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // Zik bug on NIS if noise and hardware only.
    Helper::testAkyMultiPsgMusic(BinaryData::At3HardOnlyAndNoise_xml, BinaryData::At3HardOnlyAndNoise_xmlSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, hard only and noise, 1 psg, spectrum", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // Zik bug on NIS if noise and hardware only.
    Helper::testAkyMultiPsgMusic(BinaryData::At3HardOnlyAndNoise_xml, BinaryData::At3HardOnlyAndNoise_xmlSize, TargetHardware::spectrum);
}

TEST_CASE("AkyMultiPsgZ80Player, hard only and noise, 1 psg, msx", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // Zik bug on NIS if noise and hardware only.
    Helper::testAkyMultiPsgMusic(BinaryData::At3HardOnlyAndNoise_xml, BinaryData::At3HardOnlyAndNoise_xmlSize, TargetHardware::msx);
}

TEST_CASE("AkyMultiPsgZ80Player, hardware to software with noise", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // Also buggy...
    Helper::testAkyMultiPsgMusic(BinaryData::At3HardToSoftAndNoise_xml, BinaryData::At3HardToSoftAndNoise_xmlSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, software to hardware with noise", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // Also buggy...
    Helper::testAkyMultiPsgMusic(BinaryData::At3SoftToHardAndNoise_xml, BinaryData::At3SoftToHardAndNoise_xmlSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, software and hardware with noise", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // Also buggy...
    Helper::testAkyMultiPsgMusic(BinaryData::At3SoftAndHardAndNoise_xml, BinaryData::At3SoftAndHardAndNoise_xmlSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, hard only with env 9", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // The odd bit was lost.
    Helper::testAkyMultiPsgMusic(BinaryData::At3HardOnlyWithNoiseEnvelope9_xml, BinaryData::At3HardOnlyWithNoiseEnvelope9_xmlSize, TargetHardware::cpc);
}

TEST_CASE("AkyMultiPsgZ80Player, hard only with env F", "[AkyMultiPsgZ80Player] [Emulator]")
{
    // The odd bit was lost.
    Helper::testAkyMultiPsgMusic(BinaryData::At3HardOnlyWithNoiseEnvelopeF_xml, BinaryData::At3HardOnlyWithNoiseEnvelopeF_xmlSize, TargetHardware::cpc);
}


// =======================================================================================

TEST_CASE("AkyMultiPsgZ80Player, simple and noise song 9 channels PlayCity", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftAndNoiseSoundChannel1To9_xml, BinaryData::At2SimpleSoftAndNoiseSoundChannel1To9_xmlSize, TargetHardware::cpcPlayCity);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and noise song 9 channels SpecNext", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftAndNoiseSoundChannel1To9_xml, BinaryData::At2SimpleSoftAndNoiseSoundChannel1To9_xmlSize, TargetHardware::spectrumNext);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and noise song 6 channels Spectrum TurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xml, BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xmlSize, TargetHardware::spectrumTurboSound);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and noise song 6 channels Msx FPGA", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xml, BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xmlSize, TargetHardware::msxFpgaPsg);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and noise song 6 channels Msx Darty", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xml, BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xmlSize, TargetHardware::msxDarky);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and noise song 6 channels PCW TurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xml, BinaryData::At2SimpleSoftAndNoiseSoundChannel1To6_xmlSize, TargetHardware::pcwTurboSound);
}


// =======================================================================================

TEST_CASE("AkyMultiPsgZ80Player, simple and hard song 9 channels PlayCity", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SoftAndHardOnlyChannel1To9_xml, BinaryData::At2SoftAndHardOnlyChannel1To9_xmlSize, TargetHardware::cpcPlayCity);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and hard song 9 channels SpecNext", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SoftAndHardOnlyChannel1To9_xml, BinaryData::At2SoftAndHardOnlyChannel1To9_xmlSize, TargetHardware::spectrumNext);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and hard song 6 channels Spectrum TurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SoftAndHardOnlyChannel1To6_xml, BinaryData::At2SoftAndHardOnlyChannel1To6_xmlSize, TargetHardware::spectrumTurboSound);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and hard song 6 channels Msx FPGA", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SoftAndHardOnlyChannel1To6_xml, BinaryData::At2SoftAndHardOnlyChannel1To6_xmlSize, TargetHardware::msxFpgaPsg);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and hard song 6 channels Msx Darty", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SoftAndHardOnlyChannel1To6_xml, BinaryData::At2SoftAndHardOnlyChannel1To6_xmlSize, TargetHardware::msxDarky);
}

TEST_CASE("AkyMultiPsgZ80Player, simple and hard song 6 channels PCW TurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2SoftAndHardOnlyChannel1To6_xml, BinaryData::At2SoftAndHardOnlyChannel1To6_xmlSize, TargetHardware::pcwTurboSound);
}


// =======================================================================================

TEST_CASE("AkyMultiPsgZ80Player, hard to soft Bug 9 channels SpecNext", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2Bug9ChannelsHardToSoft_xml, BinaryData::At2Bug9ChannelsHardToSoft_xmlSize, TargetHardware::spectrumNext);
}


// =======================================================================================

TEST_CASE("AkyMultiPsgZ80Player, all instrument types 9 channels PlayCity", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2AllInstrumentTypesChannel1To9_xml, BinaryData::At2AllInstrumentTypesChannel1To9_xmlSize, TargetHardware::cpcPlayCity);
}

TEST_CASE("AkyMultiPsgZ80Player, all instrument types 9 channels SpecNext", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2AllInstrumentTypesChannel1To9_xml, BinaryData::At2AllInstrumentTypesChannel1To9_xmlSize, TargetHardware::spectrumNext);
}

TEST_CASE("AkyMultiPsgZ80Player, all instrument types 6 channels Spectrum TurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2AllInstrumentTypesChannel1To6_xml, BinaryData::At2AllInstrumentTypesChannel1To6_xmlSize, TargetHardware::spectrumTurboSound);
}

TEST_CASE("AkyMultiPsgZ80Player, all instrument types 6 channels Msx FPGA", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2AllInstrumentTypesChannel1To6_xml, BinaryData::At2AllInstrumentTypesChannel1To6_xmlSize, TargetHardware::msxFpgaPsg);
}

TEST_CASE("AkyMultiPsgZ80Player, all instrument types 6 channels Msx Darty", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2AllInstrumentTypesChannel1To6_xml, BinaryData::At2AllInstrumentTypesChannel1To6_xmlSize, TargetHardware::msxDarky);
}

TEST_CASE("AkyMultiPsgZ80Player, all instrument types 6 channels PCW TurboSound", "[AkyMultiPsgZ80Player] [Emulator]")
{
    Helper::testAkyMultiPsgMusic(BinaryData::At2AllInstrumentTypesChannel1To6_xml, BinaryData::At2AllInstrumentTypesChannel1To6_xmlSize, TargetHardware::pcwTurboSound);
}

}   // namespace arkostracker
