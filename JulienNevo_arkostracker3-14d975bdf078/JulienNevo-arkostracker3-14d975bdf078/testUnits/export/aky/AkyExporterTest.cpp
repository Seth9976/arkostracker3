#include "../../catch.hpp"

#include <juce_core/juce_core.h>

#include <BinaryData.h>

#include "../../../source/export/aky/AkyExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../helper/RasmHelper.h"

namespace arkostracker 
{

/** Takes a music, exports it, compiles it, and compares it with the given source that is also compiled. */
static std::set<PlayerConfigurationFlag> testAkyMusic(const char* asmMusic, size_t asmMusicSize, const char* expectedSource, size_t expectedSourceSize)
{
    // Given.
    juce::MemoryInputStream inputStream(asmMusic, asmMusicSize, false);
    SongLoader loader;
    const auto result = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE((result != nullptr));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());

    const std::shared_ptr song = std::move(result->song);

    const auto subsongIds = { song->getFirstSubsongId() };
    constexpr auto address = 0x4000;
    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), subsongIds, "label_", address);
    AkyExporter akyExporter(song, exportConfiguration);

    // When.
    const auto&[success, generatedSourceMusicOutputStream] = akyExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((generatedSourceMusicOutputStream != nullptr));

    // Compiles with Rasm, compare with expected from AT2.
    auto generatedSourceMusicMemoryBlock = generatedSourceMusicOutputStream->getAggregatedData();
    // FOR TESTING.
    //FileUtil::saveMemoryBlockToFile("~/Downloads/genAky.asm", generatedSourceMusicMemoryBlock);

    const auto assembledMusic = RasmHelper::assembleSource(generatedSourceMusicMemoryBlock);
    REQUIRE((assembledMusic != nullptr));
    const auto assembledMusic2 = RasmHelper::assembleSource(generatedSourceMusicMemoryBlock);
    REQUIRE((assembledMusic2 != nullptr));

    juce::MemoryBlock expectedMusicMemoryBlock(expectedSource, expectedSourceSize);
    const auto assembledExpectedBinary = RasmHelper::assembleSource(expectedMusicMemoryBlock, address);
    REQUIRE((assembledExpectedBinary != nullptr));
    REQUIRE(MemoryBlockUtil::compare(*assembledMusic, *assembledExpectedBinary));

    // Checks the player configuration.
    return generatedSourceMusicOutputStream->getPlayerConfigurationRef().getFlags();
}

TEST_CASE("AkyExporter, simple music", "[AkyExporter]")
{
    const auto flags = testAkyMusic(BinaryData::At2Simple_xml, static_cast<size_t>(BinaryData::At2Simple_xmlSize),
                                    BinaryData::At2SimpleAky_asm, static_cast<size_t>(BinaryData::At2SimpleAky_asmSize));

    REQUIRE((flags.size() == 3U));
    REQUIRE((flags.find(PlayerConfigurationFlag::music) != flags.cend()));
    REQUIRE((flags.find(PlayerConfigurationFlag::noSoftNoHard) != flags.cend()));
    REQUIRE((flags.find(PlayerConfigurationFlag::softwareOnly) != flags.cend()));
}

TEST_CASE("AkyExporter, Glide Up", "[AkyExporter]")
{
    const auto flags = testAkyMusic(BinaryData::At2GlideUp_aks, static_cast<size_t>(BinaryData::At2GlideUp_aksSize),
                                    BinaryData::At2GlideUpAky_asm, static_cast<size_t>(BinaryData::At2GlideUpAky_asmSize));

    REQUIRE((flags == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::hardwareSounds,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::softwareAndHardware,
    }));
}

TEST_CASE("AkyExporter, Harmless Grenade", "[AkyExporter]")
{
    const auto flags = testAkyMusic(BinaryData::At2TarghanAHarmlessGrenade_aks, static_cast<size_t>(BinaryData::At2TarghanAHarmlessGrenade_aksSize),
                 BinaryData::HarmlessGrenade_asm, static_cast<size_t>(BinaryData::HarmlessGrenade_asmSize));

    REQUIRE((flags == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::hardwareSounds,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::noSoftNoHardNoise,
            PlayerConfigurationFlag::softwareOnly,
            PlayerConfigurationFlag::softwareOnlyNoise,
            PlayerConfigurationFlag::softwareAndHardware,
    }));
}

TEST_CASE("AkyExporter, Hocus Pocus shorter", "[AkyExporter]")
{
    // There was a bug in the Loop.
    const auto flags = testAkyMusic(BinaryData::At2HocusShorter_aks, static_cast<size_t>(BinaryData::At2HocusShorter_aksSize),
                                    BinaryData::HocusShorter_asm, static_cast<size_t>(BinaryData::HocusShorter_asmSize));

    REQUIRE((flags == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::retrig,
            PlayerConfigurationFlag::hardwareSounds,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::noSoftNoHardNoise,
            PlayerConfigurationFlag::softwareOnly,
            PlayerConfigurationFlag::softwareOnlyNoise,
            PlayerConfigurationFlag::hardwareOnly,
            PlayerConfigurationFlag::hardwareOnlyRetrig,
            PlayerConfigurationFlag::softwareAndHardware,
    }));
}

TEST_CASE("AkyExporter, SID CPC", "[AkyExporter]")
{
    testAkyMusic(BinaryData::At3SidExamplesCpc_xml, static_cast<size_t>(BinaryData::At3SidExamplesCpc_xmlSize),
                                    BinaryData::At3SidExamplesCpc_asm, static_cast<size_t>(BinaryData::At3SidExamplesCpc_asmSize));
}

// Test ignored because the AT2 behavior does not take the note limit in account, whereas AT3 does. So the test cannot work.
/*TEST_CASE("AkyExporter, Hocus Pocus hard high-pitch bug", "[AkyExporter]")
{
    testAkyMusic(BinaryData::At2HocusHardBug_aks, BinaryData::At2HocusHardBug_aksSize, BinaryData::AT2AkyHocusHardBug_bin, BinaryData::AT2AkyHocusHardBug_binSize);
}*/

// Test ignored because the AT2 behavior does not take the note limit in account, whereas AT3 does. So the test cannot work.
/*TEST_CASE("AkyExporter, Hocus Pocus", "[AkyExporter]")
{
    testAkyMusic(BinaryData::Targhan__Hocus_Pocus_aks, BinaryData::Targhan__Hocus_Pocus_aksSize, BinaryData::At2HocusPocusAky_bin, BinaryData::At2HocusPocusAky_binSize);
}*/


}   // namespace arkostracker

