#include "../catch.hpp"

#include "../helper/z80Emulator/Z80PlayerEmulator.h"

#include <BinaryData.h>

namespace arkostracker 
{

class Tester
{
public:
    /**
     * Tests the music with the Z80 player.
     * @param subsongIndexesToKeep the indexes of the Subsong to keep on the export. If empty, only the first one will be exported. Thus, the subsongIndexToPlay MUST be 0.
     * @param subsongIndexToPlay the Subsong indexes to play AFTER the Subsongs have been stripped.
     */
    static void testAkgMusic(const char* unzippedMusicData, const size_t unzippedMusicSize, const std::vector<int>& subsongIndexesToKeep = { }, const int subsongIndexToPlay = 0,
                      const std::map<TargetHardware, ExpectedStatistics>& targetToExpectedStatistics = { },
                      const int errorCountToleranceInVolume = 0, const int possibleAbsoluteDifferenceInVolume = 0,
                      const int possibleAbsoluteDifferenceInSoftwarePeriod = 0, const int possibleAbsoluteDifferenceInHardwarePeriod = 0,
                      const bool playTwice = true, const OptionalValue<TargetHardware> forcedTargetHardware = { })
    {
        Z80PlayerEmulator::testMusic(unzippedMusicData, unzippedMusicSize, subsongIndexToPlay, PlayerType::akg, targetToExpectedStatistics, subsongIndexesToKeep,
                                     errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                     possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod, 0,
                                     playTwice, forcedTargetHardware);
    }
};

// ============================================================

TEST_CASE("AkgZ80Player, empty song", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2Empty_aks, BinaryData::At2Empty_aksSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 50,

                                 3073, 1227,       // Player size, RAM, without/with player config.
                                 3324, 1285,       // Player size, ROM, without/with player config.

                                 1141, 856,        // Max nops, RAM, without/with player config.
                                 1319, 956         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkgZ80Player, Hocus Pocus shorter", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2HocusShorter_aks, BinaryData::At2HocusShorter_aksSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 1462,

                                 3073, 2522,       // Player size, RAM, without/with player config.
                                 3324, 2735,       // Player size, ROM, without/with player config.

                                 2180, 2084,       // Max nops, RAM, without/with player config.
                                 2427, 2309        // Max nops, ROM, without/with player config.
                         )
                         },
                 },
                 234, 1
    );
}

TEST_CASE("AkgZ80Player, Sarkboteur", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At3Sarkboteur_xml, BinaryData::At3Sarkboteur_xmlSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 2182,

                                 3073, 2508,               // Player size, RAM, without/with player config.
                                 3324, 2740,               // Player size, ROM, without/with player config.

                                 2232, 2164,               // Max nops, RAM, without/with player config.
                                 2489, 2408                // Max nops, ROM, without/with player config.
                         )
                         },
                 },
                 1129, 1
    );
}

TEST_CASE("AkgZ80Player, Simple soft sound channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SimpleSoftSoundChannel1_aks, BinaryData::At2SimpleSoftSoundChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, Simple soft sound channel 2", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SimpleSoftSoundChannel2_aks, BinaryData::At2SimpleSoftSoundChannel2_aksSize);
}

TEST_CASE("AkgZ80Player, Simple soft sound channel 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SimpleSoftSoundChannel3_aks, BinaryData::At2SimpleSoftSoundChannel3_aksSize);
}

TEST_CASE("AkgZ80Player, Speed", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2Speed_aks, BinaryData::At2Speed_aksSize);
}

TEST_CASE("AkgZ80Player, All Instrument Types, channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2AllInstrumentTypesChannel1_aks, BinaryData::At2AllInstrumentTypesChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, All Instrument Types, channel 2", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2AllInstrumentTypesChannel2_aks, BinaryData::At2AllInstrumentTypesChannel2_aksSize);
}

TEST_CASE("AkgZ80Player, All Instrument Types, channel 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2AllInstrumentTypesChannel3_aks, BinaryData::At2AllInstrumentTypesChannel3_aksSize);
}

TEST_CASE("AkgZ80Player, Glide up channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffect2Channel1_aks, BinaryData::At2GlideEffect2Channel1_aksSize);
}

TEST_CASE("AkgZ80Player, Glide up channel 2", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffect2Channel2_aks, BinaryData::At2GlideEffect2Channel2_aksSize);
}

TEST_CASE("AkgZ80Player, Glide up channel 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffect2Channel3_aks, BinaryData::At2GlideEffect2Channel3_aksSize);
}

TEST_CASE("AkgZ80Player, Glide up all channels", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffect2ChannelAll_aks, BinaryData::At2GlideEffect2ChannelAll_aksSize);
}

TEST_CASE("AkgZ80Player, Glide up, hard sound", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideUp_aks, BinaryData::At2GlideUp_aksSize);
}

TEST_CASE("AkgZ80Player, Glide down, hard sound", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideDown_aks, BinaryData::At2GlideDown_aksSize,
                 { }, 0, { }, 0, 0,
                 0, 0, false);
}
TEST_CASE("AkgZ80Player, Glide down, hard sound, play twice", "[AkgZ80Player] [Emulator]")
{
    // When looping, the decimal part is kept on the new note, so a rounding is performed, tolerated here.
    Tester::testAkgMusic(BinaryData::At2GlideDown_aks, BinaryData::At2GlideDown_aksSize,
                 { }, 0, { },
                 0, 0, 1, 1);
}

TEST_CASE("AkgZ80Player, Glide up and down short", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideUpAndDownShort_aks, BinaryData::At2GlideUpAndDownShort_aksSize);
}

TEST_CASE("AkgZ80Player, Glide up and down", "[AkgZ80Player] [Emulator]")
{
    // TO IMPROVE, possibly... If playing twice, some tolerance must be increased on Spectrum. Who cares...
    Tester::testAkgMusic(BinaryData::At2GlideUpAndDown_aks, BinaryData::At2GlideUpAndDown_aksSize, { }, 0, { }, 0, 0, 0, 0, false);
}

TEST_CASE("AkgZ80Player, Glide channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffectChannel1_aks, BinaryData::At2GlideEffectChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, Glide channel all", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffectChannelAll_aks, BinaryData::At2GlideEffectChannelAll_aksSize);
}

TEST_CASE("AkgZ80Player, Glide all channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffect2Channel1_aks, BinaryData::At2GlideEffect2Channel1_aksSize);
}

TEST_CASE("AkgZ80Player, Glide all channel 2", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffect2Channel2_aks, BinaryData::At2GlideEffect2Channel2_aksSize);
}

TEST_CASE("AkgZ80Player, Glide all channel 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2GlideEffect2Channel3_aks, BinaryData::At2GlideEffect2Channel3_aksSize);
}

TEST_CASE("AkgZ80Player, Volume Effects Full Volume Channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2VolumeEffectsFullVolumeChannel1_aks, BinaryData::At2VolumeEffectsFullVolumeChannel1_aksSize,
        { }, 0, {},
        256, 1);
}

TEST_CASE("AkgZ80Player, Volume Effects channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2VolumeEffectsChannel1_aks, BinaryData::At2VolumeEffectsChannel1_aksSize,
        { }, 0, {},
        80, 1);
}

TEST_CASE("AkgZ80Player, Arpeggio effect accumulated channel 1 to 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2ArpeggioEffectCummulatedChannel1To3_aks, BinaryData::At2ArpeggioEffectCummulatedChannel1To3_aksSize);
}

TEST_CASE("AkgZ80Player, Inline Arpeggios and Speed Channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2InlineArpeggiosAndSpeedChannel1_aks, BinaryData::At2InlineArpeggiosAndSpeedChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, Inline Arpeggios and Speed Channel 2", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2InlineArpeggiosAndSpeedChannel2_aks, BinaryData::At2InlineArpeggiosAndSpeedChannel2_aksSize);
}

TEST_CASE("AkgZ80Player, Inline Arpeggios and Speed Channel 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2InlineArpeggiosAndSpeedChannel3_aks, BinaryData::At2InlineArpeggiosAndSpeedChannel3_aksSize);
}

TEST_CASE("AkgZ80Player, Pitch Table Effects Channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2PitchTableEffectsChannel1_aks, BinaryData::At2PitchTableEffectsChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, Legato channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2LegatoChannel1_aks, BinaryData::At2LegatoChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, all effects, channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2AllEffectsChannel1_aks, BinaryData::At2AllEffectsChannel1_aksSize,
                 { }, 0, { },
                 120, 1);
}

TEST_CASE("AkgZ80Player, all effects, channel 2", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2AllEffectsChannel2_aks, BinaryData::At2AllEffectsChannel2_aksSize,
                 { }, 0, { },
                 120, 1);
}

TEST_CASE("AkgZ80Player, all effects, channel 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2AllEffectsChannel3_aks, BinaryData::At2AllEffectsChannel3_aksSize,
                 { }, 0, { },
                 120, 1);
}

TEST_CASE("AkgZ80Player, all effects", "[AkgZ80Player] [Emulator]")
{
    // Due to the volume management that is different on Z80, some frames don't have the same volume at the same time.
    Tester::testAkgMusic(BinaryData::At2AllEffects_aks, BinaryData::At2AllEffects_aksSize,
        { }, 0, {},
        360, 1);
}

TEST_CASE("AkgZ80Player, Transpositions Volume Only", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2TranspositionsVolumeOnly_aks, BinaryData::At2TranspositionsVolumeOnly_aksSize);
}

TEST_CASE("AkgZ80Player, transpositions shorter", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2TranspositionsShorter_aks, BinaryData::At2TranspositionsShorter_aksSize);
}

TEST_CASE("AkgZ80Player, transpositions", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2Transpositions_aks, BinaryData::At2Transpositions_aksSize);
}

TEST_CASE("AkgZ80Player, Molusk start", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2MoluskStart_aks, BinaryData::At2MoluskStart_aksSize);
}

TEST_CASE("AkgZ80Player, Drum Pattern Molusk Channel1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2DrumPatternMoluskChannel1_aks, BinaryData::At2DrumPatternMoluskChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, Molusk", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize, { }, 0,
                 {
                         { TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 7882,             // More than AT2, because the latter imported the song with errors (fewer data, but wrong pitch. See Position 0x15).

                                 3073, 1821,       // Player size, RAM, without/with player config.
                                 3324, 2017,       // Player size, ROM, without/with player config.

                                 2071, 1693,        // Max nops, RAM, without/with player config.
                                 2340, 1889         // Max nops, ROM, without/with player config.
                         )
                         },
                 });
}

TEST_CASE("AkgZ80Player, Molusk for PCW", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize, { }, 0,
                 {}, 0, 0, 0, 0, true,
                 TargetHardware::pcw);
}

TEST_CASE("AkgZ80Player, Molusk for SVI", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize, { }, 0,
                 {}, 0, 0, 0, 0, true,
                 TargetHardware::svi);
}

TEST_CASE("AkgZ80Player, Carpet", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::Targhan__Midline_Process__Carpet_sks, BinaryData::Targhan__Midline_Process__Carpet_sksSize, { }, 0,
                 {
                         { TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 7543,

                                 3073, 1918,       // Player size, RAM, without/with player config.
                                 3324, 2128,       // Player size, ROM, without/with player config.

                                 1990, 1664,        // Max nops, RAM, without/with player config.
                                 2227, 1834         // Max nops, ROM, without/with player config.
                         )
                         },
                 });
}

TEST_CASE("AkgZ80Player, retrig", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2RetrigChannel1_aks, BinaryData::At2RetrigChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, A Harmless Grenade", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2TarghanAHarmlessGrenade_aks, BinaryData::At2TarghanAHarmlessGrenade_aksSize);
}

TEST_CASE("AkgZ80Player, A Harmless Grenade, loop 4", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2TarghanAHarmlessGrenade_LoopAt4_aks, BinaryData::At2TarghanAHarmlessGrenade_LoopAt4_aksSize);
}

TEST_CASE("AkgZ80Player, multiple subsongs, play 0, keep only one", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SeveralSubsongs_aks, BinaryData::At2SeveralSubsongs_aksSize, { 0 }, 0);
}

TEST_CASE("AkgZ80Player, multiple subsongs, play 1, keep only one", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SeveralSubsongs_aks, BinaryData::At2SeveralSubsongs_aksSize, { 1 }, 0);
}

TEST_CASE("AkgZ80Player, multiple subsongs, play 2, keep only one", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SeveralSubsongs_aks, BinaryData::At2SeveralSubsongs_aksSize, { 2 }, 0);
}

TEST_CASE("AkgZ80Player, multiple subsongs, play 0, keep all", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SeveralSubsongs_aks, BinaryData::At2SeveralSubsongs_aksSize, { 0, 1, 2 }, 0);
}

TEST_CASE("AkgZ80Player, multiple subsongs, play 1, keep all", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SeveralSubsongs_aks, BinaryData::At2SeveralSubsongs_aksSize, { 0, 1, 2 }, 1);
}

TEST_CASE("AkgZ80Player, multiple subsongs, play 2, keep all", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SeveralSubsongs_aks, BinaryData::At2SeveralSubsongs_aksSize, { 0, 1, 2 }, 2);
}

TEST_CASE("AkgZ80Player, pitch effect, channel 1", "[AkgZ80Player] [Emulator]")
{
    // Players can have a more approximate software period.
    Tester::testAkgMusic(BinaryData::At2PitchEffectChannel1_aks, BinaryData::At2PitchEffectChannel1_aksSize, { }, 0, { }, 0, 0, 1);
}

TEST_CASE("AkgZ80Player, pitch table effect, force pitch speed, pitch and reset, channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2PitchTableEffectAndForcePitchSpeedAndPitchAndResetChannel1_aks, BinaryData::At2PitchTableEffectAndForcePitchSpeedAndPitchAndResetChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, pitch table effect, force pitch speed, channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2PitchTableEffectAndForcePitchSpeedChannel1_aks, BinaryData::At2PitchTableEffectAndForcePitchSpeedChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, pitch table effects, channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2PitchTableEffectsChannel1_aks, BinaryData::At2PitchTableEffectsChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, software only", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SoftwareOnly, BinaryData::At2SoftwareOnlySize);
}

TEST_CASE("AkgZ80Player, soft and hard", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2SoftAndHard_aks, BinaryData::At2SoftAndHard_aksSize);
}

TEST_CASE("AkgZ80Player, All sounds LW AKM", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2AllSoundsLwAkm_aks, BinaryData::At2AllSoundsLwAkm_aksSize);
}

TEST_CASE("AkgZ80Player, volume effects set only, channel 1 to 3", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2VolumeEffectsSetOnlyChannel1To3_aks, BinaryData::At2VolumeEffectsSetOnlyChannel1To3_aksSize);
}

TEST_CASE("AkgZ80Player, force arpeggio speed, channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2ForceArpeggioSpeedChannel1_aks, BinaryData::At2ForceArpeggioSpeedChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, force instrument speed, channel 1", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2ForceInstrumentSpeedChannel1_aks, BinaryData::At2ForceInstrumentSpeedChannel1_aksSize);
}

TEST_CASE("AkgZ80Player, force inline arpeggios, all channels", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2InlineArpeggiosChannelAll_aks, BinaryData::At2InlineArpeggiosChannelAll_aksSize);
}

TEST_CASE("AkgZ80Player, events no retrig", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At2EventsNoRetrig_aks, BinaryData::At2EventsNoRetrig_aksSize);
}

TEST_CASE("AkgZ80Player, hardware only with noise", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At3HardOnlyAndNoise_xml, BinaryData::At3HardOnlyAndNoise_xmlSize);
}

TEST_CASE("AkgZ80Player, hardware to software with noise", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At3HardToSoftAndNoise_xml, BinaryData::At3HardToSoftAndNoise_xmlSize);
}

TEST_CASE("AkgZ80Player, software to hardware with noise", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At3SoftToHardAndNoise_xml, BinaryData::At3SoftToHardAndNoise_xmlSize);
}

TEST_CASE("AkgZ80Player, software and hardware with noise", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At3SoftAndHardAndNoise_xml, BinaryData::At3SoftAndHardAndNoise_xmlSize);
}

TEST_CASE("AkgZ80Player, hard only with env 9", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At3HardOnlyWithNoiseEnvelope9_xml, BinaryData::At3HardOnlyWithNoiseEnvelope9_xmlSize);
}

TEST_CASE("AkgZ80Player, the rivals", "[AkgZ80Player] [Emulator]")
{
    Tester::testAkgMusic(BinaryData::At3TheRivals1Mhz_xml, BinaryData::At3TheRivals1Mhz_xmlSize);
}

TEST_CASE("AkgZ80Player, small room", "[AkgZ80Player] [Emulator]")
{
    // JRM used glide without pitch, the player configuration didn't work well.
    Tester::testAkgMusic(BinaryData::At3SecretRoomShort_xml, BinaryData::At3SecretRoomShort_xmlSize);
}

TEST_CASE("AkgZ80Player, Volume out and legato", "[AkgZ80Player] [Emulator]")
{
    // The channel player was stopping the volume in/out during a legato. Not logical.
    // Many wrong occurrences, as the volume fade-out is long...
    Tester::testAkgMusic(BinaryData::At3VolumeOutAndLegato_xml, BinaryData::At3VolumeOutAndLegato_xmlSize, { }, 0, { }, 110, 1);
}

}   // namespace arkostracker
