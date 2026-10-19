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
static void testAkyStabilizedMusic(const char* unzippedMusicData, size_t unzippedMusicSize, const std::vector<int>& subsongIndexesToKeep = { }, int subsongIndexToPlay = 0,
                  const std::map<TargetHardware, ExpectedStatistics>& targetToExpectedStatistics = { },
                  int errorCountToleranceInVolume = 0, int possibleAbsoluteDifferenceInVolume = 0,
                  int possibleAbsoluteDifferenceInSoftwarePeriod = 0, int possibleAbsoluteDifferenceInHardwarePeriod = 0,
                  int errorCountToleranceInHardwarePeriod = 0,
                  bool playTwice = true)
{
    Z80PlayerEmulator::testMusic(unzippedMusicData, unzippedMusicSize, subsongIndexToPlay, PlayerType::akyStabilized, targetToExpectedStatistics, subsongIndexesToKeep,
                                 errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                 possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod, errorCountToleranceInHardwarePeriod,
                                 playTwice);
}

/**
 * Before Hicks optimizations: 1187. How many cycles should take the player (not counting the call "hook" and the "jp" from the hook).
 * 1174 after Hicks optimizations.
 */
constexpr auto expectedNops = 1174;


// ============================================================

TEST_CASE("AkyStabilizedZ80Player, empty song", "[AkyStabilizedZ80Player] [Emulator]")
{
    testAkyStabilizedMusic(BinaryData::At2Empty_aks, BinaryData::At2Empty_aksSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 29,

                                 0, 0,0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyStabilizedZ80Player, carpet", "[AkyStabilizedZ80Player] [Emulator]")
{
    testAkyStabilizedMusic(BinaryData::Targhan__Midline_Process__Carpet_sks, BinaryData::Targhan__Midline_Process__Carpet_sksSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 0,

                                 0, 0, 0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyStabilizedZ80Player, all instrument types", "[AkyStabilizedZ80Player] [Emulator]")
{
    testAkyStabilizedMusic(BinaryData::At2AllInstrumentTypesChannel1_aks, BinaryData::At2AllInstrumentTypesChannel1_aksSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 0,

                                 0, 0, 0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyStabilizedZ80Player, hardware only with noise", "[AkyStabilizedZ80Player] [Emulator]")
{
    // Zik bug on NIS if noise and hardware only.
    testAkyStabilizedMusic(BinaryData::At3HardOnlyAndNoise_xml, BinaryData::At3HardOnlyAndNoise_xmlSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 0, 0, 0,0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyStabilizedZ80Player, hardware to software with noise", "[AkyStabilizedZ80Player] [Emulator]")
{
    testAkyStabilizedMusic(BinaryData::At3HardToSoftAndNoise_xml, BinaryData::At3HardToSoftAndNoise_xmlSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 0, 0, 0,0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyStabilizedZ80Player, software to hardware with noise", "[AkyStabilizedZ80Player] [Emulator]")
{
    testAkyStabilizedMusic(BinaryData::At3SoftToHardAndNoise_xml, BinaryData::At3SoftToHardAndNoise_xmlSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 0, 0, 0,0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );;
}

TEST_CASE("AkyStabilizedZ80Player, software and hardware with noise", "[AkyStabilizedZ80Player] [Emulator]")
{
    testAkyStabilizedMusic(BinaryData::At3SoftAndHardAndNoise_xml, BinaryData::At3SoftAndHardAndNoise_xmlSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 0, 0, 0,0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyStabilizedZ80Player, hard only with env 9", "[AkyStabilizedZ80Player] [Emulator]")
{
    // The odd bit was lost.
    testAkyStabilizedMusic(BinaryData::At3HardOnlyWithNoiseEnvelope9_xml, BinaryData::At3HardOnlyWithNoiseEnvelope9_xmlSize, { }, 0,
                 {
                         {
                                 TargetHardware::cpc, ExpectedStatistics(
                                 true,

                                 0, 0, 0,0, 0, // Don't care.

                                 expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                 expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                         )
                         },
                 }
    );
}

TEST_CASE("AkyStabilizedZ80Player, hard only with env F", "[AkyStabilizedZ80Player] [Emulator]")
{
    // The odd bit was lost.
        testAkyStabilizedMusic(BinaryData::At3HardOnlyWithNoiseEnvelopeF_xml, BinaryData::At3HardOnlyWithNoiseEnvelopeF_xmlSize, { }, 0,
                     {
                             {
                                     TargetHardware::cpc, ExpectedStatistics(
                                     true,

                                     0, 0, 0,0, 0, // Don't care.

                                     expectedNops, expectedNops,        // Max nops, RAM, without/with player config.
                                     expectedNops, expectedNops         // Max nops, ROM, without/with player config.
                             )
                             },
                     }
        );
}

}   // namespace arkostracker
