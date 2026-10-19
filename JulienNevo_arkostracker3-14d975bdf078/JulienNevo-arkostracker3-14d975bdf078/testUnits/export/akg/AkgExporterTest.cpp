#include "../../catch.hpp"

#include <juce_core/juce_core.h>

#include <BinaryData.h>

#include "../../../source/export/akg/AkgExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../helper/RasmHelper.h"

namespace arkostracker 
{

// These tests are not thorough, it would be too complicated. However, the Z80 player test will do it right.

TEST_CASE("AkgSongExporter, simple", "[AkgSongExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At2Simple_xml, static_cast<size_t>(BinaryData::At2Simple_xmlSize), false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult != nullptr);
    REQUIRE(loadResult->errorReport != nullptr);
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    auto sourceConfiguration = SourceGeneratorConfiguration::buildZ80();
    const ExportConfiguration exportConfiguration(sourceConfiguration, { song->getFirstSubsongId() }, "label_", 0x4000);
    AkgExporter exporter(*song, exportConfiguration);
    auto exportResult = exporter.performTask();

    REQUIRE(exportResult.first);
    const auto& songExportResult = exportResult.second;
    REQUIRE(songExportResult != nullptr);
    REQUIRE(songExportResult->isOk());
    const auto subsongData = songExportResult->getSubsongData();
    REQUIRE(subsongData.size() == 1U);

    const auto generatedMusicMemoryBlock = songExportResult->getAggregatedData();

    // Then.
    // Assembled the generated source with the AT2 Expected export, and compares.
    const juce::MemoryBlock expected(BinaryData::AkgAt2Simple_asm, static_cast<size_t>(BinaryData::AkgAt2Simple_asmSize));
    const auto success = RasmHelper::assembleAndCompareSources(generatedMusicMemoryBlock, expected);
    REQUIRE(success);

    // Checks the PlayerConfiguration.
    const auto playerConfiguration = songExportResult->getPlayerConfigurationRef();

    // FOR TESTING.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/genAkg.asm", generatedMusicMemoryBlock);
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/genAkg_playerconfig.asm", PlayerConfigurationExporter::exportConfiguration(sourceConfiguration, playerConfiguration));

    REQUIRE(playerConfiguration.getFlags() == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::softwareOnly,
    });
}

TEST_CASE("AkgSongExporter, Sarkboteur", "[AkgSongExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At3Sarkboteur_xml, static_cast<size_t>(BinaryData::At3Sarkboteur_xmlSize), false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult != nullptr);
    REQUIRE(loadResult->errorReport != nullptr);
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    auto sourceConfiguration = SourceGeneratorConfiguration::buildZ80();
    const ExportConfiguration exportConfiguration(sourceConfiguration, { song->getFirstSubsongId() }, "label_", 0x4000, SampleEncoderFlags::buildNoExport());
    AkgExporter exporter(*song, exportConfiguration);
    auto exportResult = exporter.performTask();

    REQUIRE(exportResult.first);
    const auto& songExportResult = exportResult.second;
    REQUIRE(songExportResult != nullptr);
    REQUIRE(songExportResult->isOk());
    const auto subsongData = songExportResult->getSubsongData();
    REQUIRE(subsongData.size() == 1U);

    auto generatedMusicMemoryBlock = songExportResult->getAggregatedData();

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/genAkg.asm", generatedMusicMemoryBlock);

    // Then.
    // Makes sure the binary is at least smaller than the AT2 one.
    const auto assembledMusic = RasmHelper::assembleSource(generatedMusicMemoryBlock);
    REQUIRE(assembledMusic != nullptr);
    // Assembles the AT2 song.
    auto at2MusicMemoryBlock = juce::MemoryBlock(BinaryData::AkgAt2Sarkboteur_asm, static_cast<size_t>(BinaryData::AkgAt2Sarkboteur_asmSize));
    const auto at2AssembledMusic = RasmHelper::assembleSource(at2MusicMemoryBlock);
    REQUIRE(at2AssembledMusic != nullptr);

    REQUIRE(assembledMusic->getSize() <= at2AssembledMusic->getSize());
    REQUIRE(assembledMusic->getSize() == 2182U);

    // Checks the PlayerConfiguration.
    const auto playerConfiguration = songExportResult->getPlayerConfigurationRef();

    REQUIRE(playerConfiguration.getFlags() == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::softwareOnly,
            PlayerConfigurationFlag::instrumentLoopTo,
            PlayerConfigurationFlag::effects,
            PlayerConfigurationFlag::eventTracks,
            PlayerConfigurationFlag::transpositions,
            PlayerConfigurationFlag::hardwareSounds,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::softwareOnly,
            PlayerConfigurationFlag::softwareOnlyNoise,
            PlayerConfigurationFlag::softwareOnlySoftwareArpeggio,
            PlayerConfigurationFlag::softwareToHardware,
            PlayerConfigurationFlag::hardwareToSoftware,
            PlayerConfigurationFlag::hardwareToSoftwareSoftwarePitch,
            PlayerConfigurationFlag::effectSetVolume,
            PlayerConfigurationFlag::effectVolumeOut,
            PlayerConfigurationFlag::effectArpeggioTable,
            PlayerConfigurationFlag::effectPitchTable,
            PlayerConfigurationFlag::effectPitchDown,
            PlayerConfigurationFlag::effectReset,
    });
}

TEST_CASE("AkgSongExporter, Carpet", "[AkgSongExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__Midline_Process__Carpet_sks, static_cast<size_t>(BinaryData::Targhan__Midline_Process__Carpet_sksSize), false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult != nullptr);
    REQUIRE(loadResult->errorReport != nullptr);
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    auto sourceConfiguration = SourceGeneratorConfiguration::buildZ80();
    const ExportConfiguration exportConfiguration(sourceConfiguration, { song->getFirstSubsongId() }, "Untitled_", 0x4000, SampleEncoderFlags::buildNoExport());
    AkgExporter exporter(*song, exportConfiguration);
    auto exportResult = exporter.performTask();

    REQUIRE(exportResult.first);
    const auto& songExportResult = exportResult.second;
    REQUIRE(songExportResult != nullptr);
    REQUIRE(songExportResult->isOk());
    const auto subsongData = songExportResult->getSubsongData();
    REQUIRE(subsongData.size() == 1U);

    auto generatedMusicMemoryBlock = songExportResult->getAggregatedData();

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/At3Carpet.asm", generatedMusicMemoryBlock);

    // Then.
    const auto assembledMusic = RasmHelper::assembleSource(generatedMusicMemoryBlock);
    REQUIRE(assembledMusic != nullptr);
    REQUIRE(assembledMusic->getSize() == 7543U);     // 7565 In AT2. Didn't quite search where the gain is done... Complicated.

    // Checks the PlayerConfiguration.
    const auto playerConfiguration = songExportResult->getPlayerConfigurationRef();

    REQUIRE(playerConfiguration.getFlags() == std::set<PlayerConfigurationFlag> {
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
            PlayerConfigurationFlag::hardwareToSoftware,
            PlayerConfigurationFlag::hardwareToSoftwareHardwareArpeggio,
            PlayerConfigurationFlag::hardwareToSoftwareSoftwarePitch,
            PlayerConfigurationFlag::effectSetVolume,
            PlayerConfigurationFlag::effectPitchUp,
            PlayerConfigurationFlag::effectPitchDown,
    });
}

TEST_CASE("AkgSongExporter, Molusk", "[AkgSongExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__Midline_Process__Molusk_sks, static_cast<size_t>(BinaryData::Targhan__Midline_Process__Molusk_sksSize), false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult != nullptr);
    REQUIRE(loadResult->errorReport != nullptr);
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    auto sourceConfiguration = SourceGeneratorConfiguration::buildZ80();
    const ExportConfiguration exportConfiguration(sourceConfiguration, { song->getFirstSubsongId() }, "Untitled_", 0x4000, SampleEncoderFlags::buildNoExport());
    AkgExporter exporter(*song, exportConfiguration);
    auto exportResult = exporter.performTask();

    REQUIRE(exportResult.first);
    const auto& songExportResult = exportResult.second;
    REQUIRE(songExportResult != nullptr);
    REQUIRE(songExportResult->isOk());
    const auto subsongData = songExportResult->getSubsongData();
    REQUIRE(subsongData.size() == 1U);

    auto generatedMusicMemoryBlock = songExportResult->getAggregatedData();

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/At3Molusk.asm", generatedMusicMemoryBlock);

    // Then.
    const auto assembledMusic = RasmHelper::assembleSource(generatedMusicMemoryBlock);
    REQUIRE(assembledMusic != nullptr);
    REQUIRE(assembledMusic->getSize() == 7882U);     // AT2 import = 7849, but because of wrongly imported pitch (see position 0x15).

    // Checks the PlayerConfiguration.
    const auto playerConfiguration = songExportResult->getPlayerConfigurationRef();

    REQUIRE(playerConfiguration.getFlags() == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::instrumentLoopTo,
            PlayerConfigurationFlag::effects,
            PlayerConfigurationFlag::hardwareSounds,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::noSoftNoHardNoise,
            PlayerConfigurationFlag::softwareOnly,
            PlayerConfigurationFlag::softwareOnlyNoise,
            PlayerConfigurationFlag::softwareOnlySoftwareArpeggio,
            PlayerConfigurationFlag::softwareOnlySoftwarePitch,
            PlayerConfigurationFlag::softwareToHardware,
            PlayerConfigurationFlag::softwareToHardwareSoftwareArpeggio,
            PlayerConfigurationFlag::softwareToHardwareSoftwarePitch,
            PlayerConfigurationFlag::effectSetVolume,
            PlayerConfigurationFlag::effectPitchUp,
            PlayerConfigurationFlag::effectPitchDown,
    });
}

TEST_CASE("AkgSongExporter, Software and hardware", "[AkgSongExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At2SoftAndHard_aks, static_cast<size_t>(BinaryData::At2SoftAndHard_aksSize), false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult != nullptr);
    REQUIRE(loadResult->errorReport != nullptr);
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    auto sourceConfiguration = SourceGeneratorConfiguration::buildZ80();
    const ExportConfiguration exportConfiguration(sourceConfiguration, { song->getFirstSubsongId() }, "Untitled_", 0x4000, SampleEncoderFlags::buildNoExport());
    AkgExporter exporter(*song, exportConfiguration);
    auto exportResult = exporter.performTask();

    REQUIRE(exportResult.first);
    const auto& songExportResult = exportResult.second;
    REQUIRE(songExportResult != nullptr);
    REQUIRE(songExportResult->isOk());
    const auto subsongData = songExportResult->getSubsongData();
    REQUIRE(subsongData.size() == 1U);

    auto generatedMusicMemoryBlock = songExportResult->getAggregatedData();

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/At3SoftAndHard.asm", generatedMusicMemoryBlock);

    // Then.
    const auto assembledMusic = RasmHelper::assembleSource(generatedMusicMemoryBlock);
    REQUIRE(assembledMusic != nullptr);
    REQUIRE(assembledMusic->getSize() == 95U);

    // Checks the PlayerConfiguration.
    const auto playerConfiguration = songExportResult->getPlayerConfigurationRef();

    REQUIRE(playerConfiguration.getFlags() == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::music,
            PlayerConfigurationFlag::instrumentLoopTo,
            PlayerConfigurationFlag::hardwareSounds,
            PlayerConfigurationFlag::noSoftNoHard,
            PlayerConfigurationFlag::softwareAndHardware,
            PlayerConfigurationFlag::softwareAndHardwareSoftwareArpeggio,
            PlayerConfigurationFlag::softwareAndHardwareSoftwarePitch,
            PlayerConfigurationFlag::softwareAndHardwareForcedHardwarePeriod,
    });
}

// Not a real test. Only to export a song to check its generated content.
TEST_CASE("AkgSongExporter, export to file", "[AkgSongExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At2SoftAndHard_aks, static_cast<size_t>(BinaryData::At2SoftAndHard_aksSize), false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult != nullptr);
    REQUIRE(loadResult->errorReport != nullptr);
    REQUIRE(loadResult->errorReport->isOk());
    auto song = std::move(loadResult->song);

    // When.
    auto sourceConfiguration = SourceGeneratorConfiguration::buildZ80();
    const ExportConfiguration exportConfiguration(sourceConfiguration, { song->getFirstSubsongId() }, "label_", 0x4000, SampleEncoderFlags::buildNoExport());
    AkgExporter exporter(*song, exportConfiguration);
    auto exportResult = exporter.performTask();

    REQUIRE(exportResult.first);
    const auto& songExportResult = exportResult.second;
    REQUIRE(songExportResult != nullptr);
    REQUIRE(songExportResult->isOk());
    const auto subsongData = songExportResult->getSubsongData();
    REQUIRE(subsongData.size() == 1U);

    auto generatedMusicMemoryBlock = songExportResult->getAggregatedData();

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/genAkg.asm", generatedMusicMemoryBlock);
    //const auto playerConfigurationMemoryBlock = PlayerConfigurationExporter::exportConfiguration(sourceConfiguration, songExportResult->getPlayerConfigurationRef(), false);
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/genAkg_playerconfig.asm", playerConfigurationMemoryBlock);

    // Then.
    const auto assembledMusic = RasmHelper::assembleSource(generatedMusicMemoryBlock);
    REQUIRE(assembledMusic != nullptr);
}

}   // namespace arkostracker

