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
static void testAkmMusic(const char* unzippedMusicData, size_t unzippedMusicSize, const std::vector<int>& subsongIndexesToKeep = { }, int subsongIndexToPlay = 0,
                  const std::map<TargetHardware, ExpectedStatistics>& targetToExpectedStatistics = { },
                  int errorCountToleranceInVolume = 0, int possibleAbsoluteDifferenceInVolume = 0,
                  int possibleAbsoluteDifferenceInSoftwarePeriod = 0, int possibleAbsoluteDifferenceInHardwarePeriod = 0,
                  bool playTwice = true)
{
    Z80PlayerEmulator::testMusic(unzippedMusicData, unzippedMusicSize, subsongIndexToPlay, PlayerType::akm, targetToExpectedStatistics, subsongIndexesToKeep,
                                 errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                 possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod, 0,
                                 playTwice);
}


// ============================================================

TEST_CASE("AkmZ80Player, empty song", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::At2Empty_aks, static_cast<size_t>(BinaryData::At2Empty_aksSize), { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 41U,

                                 1617U, 842U,       // Player size, RAM, without/with player config.
                                 1564U, 846U,       // Player size, ROM, without/with player config.

                                 1637, 1327,       // Max nops, RAM, without/with player config.
                                 1695, 1373         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkmZ80Player, simple soft sound channel 1", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::At2SimpleSoftSoundChannel1_aks, static_cast<size_t>(BinaryData::At2SimpleSoftSoundChannel1_aksSize),
                 { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 99U,

                                 1617U, 842U,       // Player size, RAM, without/with player config.
                                 1564U, 846U,       // Player size, ROM, without/with player config.

                                 1863, 1473,       // Max nops, RAM, without/with player config.
                                 1923, 1521         // Max nops, ROM, without/with player config.
                         )
                         },
                 }, 0, 0, 1
    );
}

TEST_CASE("AkmZ80Player, simple soft sound channel 2", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::At2SimpleSoftSoundChannel2_aks, static_cast<size_t>(BinaryData::At2SimpleSoftSoundChannel2_aksSize),
                 { }, 0, { },
                 0, 0, 1);
}

TEST_CASE("AkmZ80Player, simple soft sound channel 3", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::At2SimpleSoftSoundChannel3_aks, static_cast<size_t>(BinaryData::At2SimpleSoftSoundChannel3_aksSize),
                 { }, 0, { },
                 0, 0, 1);
}

TEST_CASE("AkmZ80Player, many arpeggios", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::AkmManyArpeggios_aks, static_cast<size_t>(BinaryData::AkmManyArpeggios_aksSize),
                 { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,
                                 337U
                         )
                         }
                 }, 0, 0, 1
    );
}

TEST_CASE("AkmZ80Player, many pitches", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::AkmManyPitches_aks, static_cast<size_t>(BinaryData::AkmManyPitches_aksSize),
                 { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,
                                 223U
                         )
                         }
                 }
    );
}

TEST_CASE("AkmZ80Player, bug unknown effect", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::AkmBugUnknownEffect_aks, static_cast<size_t>(BinaryData::AkmBugUnknownEffect_aksSize),
                 { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,
                                 51U
                         )
                         }
                 }
    );
}

TEST_CASE("AkmZ80Player, harmless grenade, bug pitch", "[AkmZ80Player] [Emulator]")
{
    // Using Pitch table could damage the sound on the next channel(s).
    testAkmMusic(BinaryData::AkmBugHarmlessPitchTableEffect_aks, static_cast<size_t>(BinaryData::AkmBugHarmlessPitchTableEffect_aksSize));
}

TEST_CASE("AkmZ80Player, harmless grenade, bug arpeggio", "[AkmZ80Player] [Emulator]")
{
    // Using Arpeggio table could damage the sound on the next channel(s).
    testAkmMusic(BinaryData::AkmBugHarmlessArpTableEffect_aks, static_cast<size_t>(BinaryData::AkmBugHarmlessArpTableEffect_aksSize));
}

TEST_CASE("AkmZ80Player, molusk drum pattern", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::At2DrumPatternMoluskChannel1_aks, static_cast<size_t>(BinaryData::At2DrumPatternMoluskChannel1_aksSize),
                 { }, 0, { },
                 0, 0, 1);      // On Spectrum...
}

TEST_CASE("AkmZ80Player, Speed", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::At2SpeedAtBeginning_xml, BinaryData::At2SpeedAtBeginning_xmlSize);
}

TEST_CASE("AkmZ80Player, all sounds", "[AkmZ80Player] [Emulator]")
{
    // AKM can have a more approximate software period.
    testAkmMusic(BinaryData::At2AllSoundsLwAkm_aks, static_cast<size_t>(BinaryData::At2AllSoundsLwAkm_aksSize),
                 { }, 0, {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true, 184U
                         )
                         }
                 }, 0,
                 0, 1);
}

/*
TEST_CASE("AkmZ80Player, harmless grenade", "[AkmZ80Player] [Emulator]")
{
    testAkmMusic(BinaryData::AT3HarmlessGrenade_xml, BinaryData::AT3HarmlessGrenade_xmlSize, { },
                 0, {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 1043,      // FIXME AT2 1043, AT3 1046!

                                 // FIXME Wrong number
                                 1617, 842,       // Player size, RAM, without/with player config.
                                 1564, 846,       // Player size, ROM, without/with player config.

                                 1866, 1476,       // Max nops, RAM, without/with player config.
                                 1926, 1524         // Max nops, ROM, without/with player config.
                         )
                         },
                 }, 0, 0,
                 1, 0);
}*/


}   // namespace arkostracker

