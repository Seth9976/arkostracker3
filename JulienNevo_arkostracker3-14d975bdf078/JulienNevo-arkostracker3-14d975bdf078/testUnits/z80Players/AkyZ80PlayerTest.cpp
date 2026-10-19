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
    static void testAkyMusic(const char* unzippedMusicData, const size_t unzippedMusicSize, const std::vector<int>& subsongIndexesToKeep = { }, const int subsongIndexToPlay = 0,
                             const std::map<TargetHardware, ExpectedStatistics>& targetToExpectedStatistics = { },
                             const int errorCountToleranceInVolume = 0, const int possibleAbsoluteDifferenceInVolume = 0,
                             const int possibleAbsoluteDifferenceInSoftwarePeriod = 0, const int possibleAbsoluteDifferenceInHardwarePeriod = 0,
                             const int errorCountToleranceInHardwarePeriod = 0,
                             const bool playTwice = true,
                             const OptionalValue<TargetHardware> forcedTargetHardware = { }
    )
    {
        Z80PlayerEmulator::testMusic(unzippedMusicData, unzippedMusicSize, subsongIndexToPlay, PlayerType::aky, targetToExpectedStatistics, subsongIndexesToKeep,
                                     errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                     possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod, errorCountToleranceInHardwarePeriod,
                                     playTwice, forcedTargetHardware);
    }
};

// ============================================================

TEST_CASE("AkyZ80Player, empty song", "[AkyZ80Player] [Emulator]")
{
    Helper::testAkyMusic(BinaryData::At2Empty_aks, BinaryData::At2Empty_aksSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 29,

                                 952, 426,       // Player size, RAM, without/with player config.
                                 968, 442,       // Player size, ROM, without/with player config.

                                 581, 451,        // Max nops, RAM, without/with player config.
                                 601, 490         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyZ80Player, Simple soft sound channel 1", "[AkyZ80Player] [Emulator]")
{
    Helper::testAkyMusic(BinaryData::At2SimpleSoftSoundChannel1_aks, BinaryData::At2SimpleSoftSoundChannel1_aksSize);
}

TEST_CASE("AkyZ80Player, Molusk start", "[AkyZ80Player] [Emulator]")
{
    Helper::testAkyMusic(BinaryData::At2MoluskStart_aks, BinaryData::At2MoluskStart_aksSize);
}

TEST_CASE("AkyZ80Player, Molusk start, PCW", "[AkyZ80Player] [Emulator]")
{
    Helper::testAkyMusic(BinaryData::At2MoluskStart_aks, BinaryData::At2MoluskStart_aksSize, { }, 0, { },
        0, 0, 0, 0, 0, true,
        TargetHardware::pcw);
}

TEST_CASE("AkyZ80Player, Molusk", "[AkyZ80Player] [Emulator]")
{
    Helper::testAkyMusic(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize, { }, 0,
                 {
                         { TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 22693,

                                 952, 807,          // Player size, RAM, without/with player config.
                                 968, 823,          // Player size, ROM, without/with player config.

                                 771, 765,          // Max nops, RAM, without/with player config.
                                 814, 808           // Max nops, ROM, without/with player config.
                         )
                         },
                 }, 0, 0, 0, 0, 6, true);
}

TEST_CASE("AkyZ80Player, hardware only with noise", "[AkyZ80Player] [Emulator]")
{
    // Zik bug on NIS if noise and hardware only.
    Helper::testAkyMusic(BinaryData::At3HardOnlyAndNoise_xml, BinaryData::At3HardOnlyAndNoise_xmlSize);
}

TEST_CASE("AkyZ80Player, hardware to software with noise", "[AkyZ80Player] [Emulator]")
{
    // Also buggy...
    Helper::testAkyMusic(BinaryData::At3HardToSoftAndNoise_xml, BinaryData::At3HardToSoftAndNoise_xmlSize);
}

TEST_CASE("AkyZ80Player, software to hardware with noise", "[AkyZ80Player] [Emulator]")
{
    // Also buggy...
    Helper::testAkyMusic(BinaryData::At3SoftToHardAndNoise_xml, BinaryData::At3SoftToHardAndNoise_xmlSize);
}

TEST_CASE("AkyZ80Player, software and hardware with noise", "[AkyZ80Player] [Emulator]")
{
    // Also buggy...
    Helper::testAkyMusic(BinaryData::At3SoftAndHardAndNoise_xml, BinaryData::At3SoftAndHardAndNoise_xmlSize);
}

TEST_CASE("AkyZ80Player, hard only with env 9", "[AkyZ80Player] [Emulator]")
{
    // The odd bit was lost.
    Helper::testAkyMusic(BinaryData::At3HardOnlyWithNoiseEnvelope9_xml, BinaryData::At3HardOnlyWithNoiseEnvelope9_xmlSize);
}

TEST_CASE("AkyZ80Player, hard only with env F", "[AkyZ80Player] [Emulator]")
{
    // The odd bit was lost.
    Helper::testAkyMusic(BinaryData::At3HardOnlyWithNoiseEnvelopeF_xml, BinaryData::At3HardOnlyWithNoiseEnvelopeF_xmlSize);
}

}   // namespace arkostracker
