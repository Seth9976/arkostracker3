#include "../../catch.hpp"

#include <juce_core/juce_core.h>

#include <BinaryData.h>

#include "../../../source/export/akm/AkmExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../helper/RasmHelper.h"

namespace arkostracker 
{

// These tests are not thorough, it would be too complicated. However, the Z80 player test will do it right.

TEST_CASE("AkmSongExporter, Carpet", "[AkmSongExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__Midline_Process__Carpet_sks, static_cast<size_t>(BinaryData::Targhan__Midline_Process__Carpet_sksSize), false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE((loadResult != nullptr));
    REQUIRE((loadResult->errorReport != nullptr));
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    auto sourceConfiguration = SourceGeneratorConfiguration::buildZ80();
    const ExportConfiguration exportConfiguration(sourceConfiguration, { song->getFirstSubsongId() }, "Untitled_", 0x4000,
                                            SampleEncoderFlags::buildNoExport());
    AkmExporter exporter(*song, exportConfiguration);
    auto exportResult = exporter.performTask();

    REQUIRE(exportResult.first);
    const auto& songExportResult = exportResult.second;
    REQUIRE((songExportResult != nullptr));
    REQUIRE(songExportResult->isOk());

    auto generatedMusicMemoryBlock = songExportResult->getAggregatedData();

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/output.asm", generatedMusicMemoryBlock);

    const auto subsongData = songExportResult->getSubsongData();
    REQUIRE((subsongData.size() == 1U));

    // Then.
    const auto assembledMusic = RasmHelper::assembleSource(generatedMusicMemoryBlock);
    REQUIRE((assembledMusic != nullptr));
    REQUIRE((assembledMusic->getSize() == 6986U));     // 6999 In AT2, woohoo!

    // Checks the PlayerConfiguration.
    const auto& playerConfiguration = songExportResult->getPlayerConfigurationRef();

    REQUIRE((playerConfiguration.getFlags() == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::instrumentLoopTo,
            PlayerConfigurationFlag::effects,
            PlayerConfigurationFlag::speedTracks,
            PlayerConfigurationFlag::hardwareSounds,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::noSoftNoHardNoise,
            PlayerConfigurationFlag::softwareOnly,
            PlayerConfigurationFlag::softwareOnlyNoise,
            PlayerConfigurationFlag::softwareOnlySoftwarePitch,
            PlayerConfigurationFlag::softwareOnlySoftwareArpeggio,
            PlayerConfigurationFlag::softwareToHardware,
            PlayerConfigurationFlag::softwareToHardwareSoftwareArpeggio,
            PlayerConfigurationFlag::softwareToHardwareSoftwarePitch,
            PlayerConfigurationFlag::effectSetVolume,
            PlayerConfigurationFlag::effectPitchUp,
            PlayerConfigurationFlag::effectPitchDown,
    }));
}

}   // namespace arkostracker
