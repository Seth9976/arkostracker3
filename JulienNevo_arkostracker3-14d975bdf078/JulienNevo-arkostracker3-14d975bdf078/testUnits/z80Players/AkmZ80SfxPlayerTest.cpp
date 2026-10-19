#include "../catch.hpp"

#include <BinaryData.h>

#include "../../source/export/playerConfiguration/PlayerConfigurationExporter.h"
#include "../../source/export/sfx/SfxExporter.h"
#include "../../source/utils/RasmUtil.h"
#include "../helper/RasmHelper.h"
#include "../helper/SongTestHelper.h"

namespace arkostracker
{

class Helper
{
public:
    static void test()
    {
        test(true, false);
        test(true, true);
        test(false, false);
        test(false, true);
    }

private:
    static void test(const bool usePlayerConfigurationForMusic, const bool usePlayerConfigurationForSfx)
    {
        constexpr auto playerAddress = 0x4000;
        const auto sourceGeneratorConfiguration = SourceGeneratorConfiguration::buildZ80();

        // Builds the SFX Song from the SFX song with hardware sounds.
        const auto sfxSong = SongTestHelper::loadSong(BinaryData::sfxWithHardware_xml, BinaryData::sfxWithHardware_xmlSize);
        REQUIRE((sfxSong != nullptr));
        SfxExporter sfxExporter(*sfxSong, ExportConfiguration(
            sourceGeneratorConfiguration,
            sfxSong->getSubsongIds(), "BASE_"));
        const auto& [success, sfxSongExportResult] = sfxExporter.performTask();
        REQUIRE(success);
        const auto& sfxPlayerConfiguration = sfxSongExportResult->getPlayerConfigurationRef();
        const auto sfxPlayerConfigurationMemoryBlock = PlayerConfigurationExporter::exportConfiguration(sourceGeneratorConfiguration, sfxPlayerConfiguration);

        // The music player configuration has nothing in it.
        const auto musicPlayerConfiguration = PlayerConfiguration(true);
        const auto musicPlayerConfigurationMemoryBlock = PlayerConfigurationExporter::exportConfiguration(sourceGeneratorConfiguration, musicPlayerConfiguration);

        // Compiles the Z80 player with SFX, with player configuration.
        auto playerNoSfx = juce::MemoryBlock(BinaryData::PlayerAkm_asm, BinaryData::PlayerAkm_asmSize);
        auto playerSfx = juce::MemoryBlock(BinaryData::PlayerAkm_SoundEffects_asm, BinaryData::PlayerAkm_SoundEffects_asmSize);

        // Appends the player configurations and the player source (without SFX).
        auto originalSources = juce::MemoryBlock();
        if (usePlayerConfigurationForMusic) {
            originalSources.append(musicPlayerConfigurationMemoryBlock.getData(), musicPlayerConfigurationMemoryBlock.getSize());
        }
        if (usePlayerConfigurationForSfx) {
            originalSources.append(sfxPlayerConfigurationMemoryBlock.getData(), sfxPlayerConfigurationMemoryBlock.getSize());
        }
        originalSources.append(playerNoSfx.getData(), playerNoSfx.getSize());

        // The SFX player is added after the include.
        auto wholeSources = RasmUtil::commentIncludes(originalSources);    // Else, won't compile.
        RasmHelper::insertAfterTag("[[INSERT_SOUND_EFFECT_SOURCE]]", wholeSources, juce::MemoryBlock(playerSfx.getData(), playerSfx.getSize()));

        //FileUtil::saveMemoryBlockToFile("~/Documents/dev/cpc/tests/test.asm", wholeSources);        // Do not commit!

        const auto finalBinary = RasmHelper::assembleSource(wholeSources, playerAddress);
        REQUIRE((finalBinary != nullptr));
        REQUIRE((finalBinary->getSize() > 1000));       // Arbitrary.
    }
};

// ============================================================

TEST_CASE("AkmZ80SfxPlayer, compilation test, sfx has hardware, song does not", "[AkmZ80SfxPlayer] [Emulator]")
{
    Helper::test();
}

}   // namespace arkostracker
