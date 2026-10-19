#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/business/song/tool/builder/SongBuilder.h"
#include "../../../source/export/sfx/SfxExporter.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../helper/RasmHelper.h"

namespace arkostracker
{
class TestTool
{
public:
    static constexpr auto assemblingAddress = 0x4000;

    static void compare(const juce::MemoryBlock& generatedSource, const char* expectedMusicData, const int expectedMusicDataSize)
    {
        // Assembles the generated source.
        const auto generatedBinary = RasmHelper::assembleSourceWithoutAddingOrg(generatedSource);
        REQUIRE(generatedBinary != nullptr);

        // Assembles the expected result source.
        auto expectedSourceWithoutOrg = juce::MemoryBlock(expectedMusicData, static_cast<size_t>(expectedMusicDataSize));
        const auto expectedBinary = RasmHelper::assembleSource(expectedSourceWithoutOrg, assemblingAddress);
        REQUIRE(expectedBinary != nullptr);

        REQUIRE(MemoryBlockUtil::compare(*generatedBinary, *expectedBinary));
    }
};

TEST_CASE("SfxExporter, software only with loop", "[SfxExporter]")
{
    SongBuilder songBuilder;
    songBuilder.setSongMetaData("sfxSong", "Targhan", "Targhan", "Comments"); {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 0));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14, 0));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10, 0));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(7, 0));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(2, 0));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(1, 0));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(4, 12)); // Will be optimized.
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8, 16));
        psgPart.setMainLoop(Loop(3, 5, true));
        psgPart.setSpeed(1);

        auto instrument = Instrument::buildPsgInstrument("instr", psgPart);
        songBuilder.setInstrument(1, std::move(instrument));
    }
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg::buildForCpc());

    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(0);
    subsongBuilder.finishCurrentPosition();

    subsongBuilder.startNewTrack(0);
    subsongBuilder.startNewCell(10);
    subsongBuilder.setCurrentCellNote(4 * 12); // Places the instrument for the sfx to be exported.
    subsongBuilder.setCurrentCellInstrument(1);
    subsongBuilder.finishCurrentCell();
    subsongBuilder.finishCurrentTrack();

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.finishCurrentPattern();

    songBuilder.finishCurrentSubsong();

    auto [song, report] = songBuilder.buildSong();
    REQUIRE(report->isEmpty());

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { song->getFirstSubsongId() }, "sfx_", TestTool::assemblingAddress);

    SfxExporter sfxExporter(*song, exportConfiguration);
    auto [success, result] = sfxExporter.performTask();
    REQUIRE(success);
    REQUIRE(result != nullptr);
    REQUIRE(result->getSubsongData().empty());
    const auto generatedMusicMemoryBlock = result->getSongData();

    const auto& playerConfiguration = result->getPlayerConfigurationRef();
    const auto flags = playerConfiguration.getFlags();
    REQUIRE(flags == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::sfx,
            PlayerConfigurationFlag::sfxSoftOnly,
            PlayerConfigurationFlag::sfxLoopTo,
            });

    TestTool::compare(generatedMusicMemoryBlock, BinaryData::sfxSoftOnlyWithLoop_asm, BinaryData::sfxSoftOnlyWithLoop_asmSize);
}

TEST_CASE("Soft only with all combination", "[SfxExporter]")
{
    SongBuilder songBuilder;
    songBuilder.setSongMetaData("sfxSong", "Targhan", "Targhan", "Comments"); {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 1));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 0, 2));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14, 1, 3));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(13, 31, 0, 0, 50));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12, 31, 11, -1, -50));
        psgPart.setMainLoop(Loop(0, 4, false));
        psgPart.setSpeed(0);

        psgPart.setSoundEffectExported(true);

        auto instrument = Instrument::buildPsgInstrument("instr", psgPart);
        songBuilder.setInstrument(1, std::move(instrument));
    }
    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg::buildForCpc());

    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(0);
    subsongBuilder.finishCurrentPosition();

    subsongBuilder.startNewTrack(0);
    subsongBuilder.startNewCell(10);
    subsongBuilder.setCurrentCellNote(4 * 12 + 1); // Places the instrument for the sfx to be exported.
    subsongBuilder.setCurrentCellInstrument(1);
    subsongBuilder.finishCurrentCell();
    subsongBuilder.finishCurrentTrack();

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.finishCurrentPattern();

    songBuilder.finishCurrentSubsong();

    auto [song, report] = songBuilder.buildSong();
    REQUIRE(report->isEmpty());

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { song->getFirstSubsongId() }, "sfx_", TestTool::assemblingAddress);

    SfxExporter sfxExporter(*song, exportConfiguration);
    auto [success, result] = sfxExporter.performTask();
    REQUIRE(success);
    REQUIRE(result != nullptr);
    REQUIRE(result->getSubsongData().empty());
    const auto generatedMusicMemoryBlock = result->getSongData();

    const auto& playerConfiguration = result->getPlayerConfigurationRef();
    const auto flags = playerConfiguration.getFlags();
    REQUIRE(flags == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::sfx,
            PlayerConfigurationFlag::sfxSoftOnly,
            PlayerConfigurationFlag::sfxSoftOnlyNoise,
            });

    TestTool::compare(generatedMusicMemoryBlock, BinaryData::sfxSoftAll_asm, BinaryData::sfxSoftAll_asmSize);
}

TEST_CASE("Full", "[SfxExporter]")
{
    SongBuilder songBuilder;
    songBuilder.setSongMetaData("sfxSong", "Targhan", "Targhan", "Comments");

    auto instrumentIndex = 0; // Increased before use.
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(7));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(2));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(1));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10, 1)); // Optimized.
        psgPart.setMainLoop(Loop(3, 5, true));
        psgPart.setSpeed(1);

        auto instrument = Instrument::buildPsgInstrument("soft only", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 1));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 0, 2));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14, 1, 3));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(13, 31, 0, 0, 50));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12, 31, 11, -1, -50));
        psgPart.setMainLoop(Loop(0, 4));

        auto instrument = Instrument::buildPsgInstrument("soft only with all combination", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(0, 0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 1));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 31));
        psgPart.setMainLoop(Loop(0, 3));

        auto instrument = Instrument::buildPsgInstrument("no soft no hard", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftToHard());
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 5, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 50, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 1, 0, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 1, 50, 4, 0, 0, 0, 0, 12, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(0, 3));

        auto instrument = Instrument::buildPsgInstrument("Soft to hard", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(0, 0, 0, 0, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(31, 0, 0, 0, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(31, 3, 0, 0, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(0, 3, 0, -50, 8, true, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(31, 0, 0, -50, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(1, 0, 0, -50, 8, false, 1000));
        psgPart.setMainLoop(Loop(0, 5));

        auto instrument = Instrument::buildPsgInstrument("Hard only", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0, 50, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 31, 1000, 0, 0, 3, 4, 0, 0, 0, 0, 10, false,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch
            )); // Soft period overflow.
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 7, 0, 0, 4, 0, 0, 0, 0, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 7, 0, -80, 2, 0, 0, 0, 0, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 7, 0, -80, 3, 0, 0, 0, 40, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(4, 5));

        auto instrument = Instrument::buildPsgInstrument("Hard to soft", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 1, 0, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 1, 1000, 0, 0, 0, 0, 1000, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 1, 0, 5, 0, 0, 0, 0, 0, 1, 0, 15, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 1, 0, 5, 0, -50, 0, 0, 0, 1, 50, 15, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(0, 5));

        auto instrument = Instrument::buildPsgInstrument("Soft and hard", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    }

    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg::buildForCpc());

    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(0);
    subsongBuilder.finishCurrentPosition();

    // Places the instrument for the sfx to be exported.
    subsongBuilder.setCellOnTrack(0, 10, Cell::build(4 * 12, 1));
    subsongBuilder.setCellOnTrack(0, 14, Cell::build(4 * 12, 2));
    subsongBuilder.setCellOnTrack(0, 18, Cell::build(4 * 12, 3));
    subsongBuilder.setCellOnTrack(0, 12, Cell::build(4 * 12, 4));
    subsongBuilder.setCellOnTrack(0, 4, Cell::build(4 * 12, 5));
    subsongBuilder.setCellOnTrack(0, 20, Cell::build(4 * 12, 6));
    subsongBuilder.setCellOnTrack(0, 24, Cell::build(4 * 12, 7));
    subsongBuilder.setCellOnTrack(0, 40, Cell::build(4 * 12, 20)); // As a test.

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.finishCurrentPattern();

    songBuilder.finishCurrentSubsong();

    auto [song, report] = songBuilder.buildSong();
    REQUIRE(report->isEmpty());

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { song->getFirstSubsongId() }, "sfx_", TestTool::assemblingAddress);

    SfxExporter sfxExporter(*song, exportConfiguration);
    auto [success, result] = sfxExporter.performTask();
    REQUIRE(success);
    REQUIRE(result != nullptr);
    REQUIRE(result->getSubsongData().empty());
    const auto generatedMusicMemoryBlock = result->getSongData();

    const auto& playerConfiguration = result->getPlayerConfigurationRef();
    const auto flags = playerConfiguration.getFlags();
    REQUIRE(flags == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::sfx,
            PlayerConfigurationFlag::retrig,
            PlayerConfigurationFlag::sfxLoopTo,
            PlayerConfigurationFlag::sfxNoSoftNoHard,
            PlayerConfigurationFlag::sfxNoSoftNoHardNoise,
            PlayerConfigurationFlag::sfxSoftOnly,
            PlayerConfigurationFlag::sfxSoftOnlyNoise,
            PlayerConfigurationFlag::sfxHardOnly,
            PlayerConfigurationFlag::sfxHardOnlyRetrig,
            PlayerConfigurationFlag::sfxHardOnlyNoise,
            PlayerConfigurationFlag::sfxSoftAndHard,
            PlayerConfigurationFlag::sfxSoftAndHardRetrig,
            PlayerConfigurationFlag::sfxSoftAndHardNoise,
            });

    TestTool::compare(generatedMusicMemoryBlock, BinaryData::sfxFull_asm, BinaryData::sfxFull_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/output.asm", generatedMusicMemoryBlock);
}

/** Instrument 2 is not exported, and 5 is not used, a sample is added. */
TEST_CASE("Full, minus", "[SfxExporter]")
{
    SongBuilder songBuilder;
    songBuilder.setSongMetaData("sfxSong", "Targhan", "Targhan", "Comments");

    auto instrumentIndex = 0; // Increased before use.
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(7));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(2));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(1));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10, 1)); // Optimized.
        psgPart.setMainLoop(Loop(3, 5, true));
        psgPart.setSpeed(1);

        auto instrument = Instrument::buildPsgInstrument("soft only", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 1));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15, 0, 2));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14, 1, 3));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(13, 31, 0, 0, 50));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12, 31, 11, -1, -50));
        psgPart.setMainLoop(Loop(0, 4));

        psgPart.setSoundEffectExported(false); // Not exported.

        auto instrument = Instrument::buildPsgInstrument("soft only with all combination", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(0, 0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 1));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell(15, 31));
        psgPart.setMainLoop(Loop(0, 3));

        auto instrument = Instrument::buildPsgInstrument("no soft no hard", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftToHard());
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 5, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 50, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 1, 0, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 1, 50, 4, 0, 0, 0, 0, 12, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(0, 3));

        auto instrument = Instrument::buildPsgInstrument("Soft to hard", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(0, 0, 0, 0, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(31, 0, 0, 0, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(31, 3, 0, 0, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(0, 3, 0, -50, 8, true, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(31, 0, 0, -50, 8, false, 0));
        psgPart.addCell(PsgInstrumentCell::buildHardOnly(1, 0, 0, -50, 8, false, 1000));
        psgPart.setMainLoop(Loop(0, 5));

        auto instrument = Instrument::buildPsgInstrument("Hard only", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0, 50, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 31, 1000, 0, 0, 3, 4, 0, 0, 0, 0, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)); // Soft period overflow.
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 7, 0, 0, 4, 0, 0, 0, 0, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 7, 0, -80, 2, 0, 0, 0, 0, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 7, 0, -80, 3, 0, 0, 0, 40, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(4, 5));

        auto instrument = Instrument::buildPsgInstrument("Hard to soft", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 1, 0, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 1, 1000, 0, 0, 0, 0, 1000, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 1, 0, 5, 0, 0, 0, 0, 0, 1, 0, 15, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 1, 0, 5, 0, -50, 0, 0, 0, 1, 50, 15, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(0, 5));

        auto instrument = Instrument::buildPsgInstrument("Soft and hard", psgPart);
        songBuilder.setInstrument(++instrumentIndex, std::move(instrument));
    } {
        SamplePart samplePart;
        auto instrument = Instrument::buildSampleInstrument("Sample", samplePart);
    }

    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg::buildForCpc());

    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(0);
    subsongBuilder.finishCurrentPosition();

    // Places the instrument for the sfx to be exported.
    // 5 is not used
    subsongBuilder.setCellOnTrack(0, 10, Cell::build(4 * 12, 1));
    subsongBuilder.setCellOnTrack(0, 14, Cell::build(4 * 12, 2));
    subsongBuilder.setCellOnTrack(0, 18, Cell::build(4 * 12, 3));
    subsongBuilder.setCellOnTrack(0, 12, Cell::build(4 * 12, 4));
    //subsongBuilder.setCellOnTrack(0, 4, Cell::build(4*12, 5));
    subsongBuilder.setCellOnTrack(0, 20, Cell::build(4 * 12, 6));
    subsongBuilder.setCellOnTrack(0, 24, Cell::build(4 * 12, 7));
    subsongBuilder.setCellOnTrack(0, 40, Cell::build(4 * 12, 8)); // Sample.

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 0);
    subsongBuilder.setCurrentPatternTrackIndex(2, 0);
    subsongBuilder.finishCurrentPattern();

    songBuilder.finishCurrentSubsong();

    auto [song, report] = songBuilder.buildSong();
    REQUIRE(report->isEmpty());

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { song->getFirstSubsongId() }, "sfx_", TestTool::assemblingAddress);

    SfxExporter sfxExporter(*song, exportConfiguration);
    auto [success, result] = sfxExporter.performTask();
    REQUIRE(success);
    REQUIRE(result != nullptr);
    REQUIRE(result->getSubsongData().empty());
    const auto generatedMusicMemoryBlock = result->getSongData();

    const auto& playerConfiguration = result->getPlayerConfigurationRef();
    const auto flags = playerConfiguration.getFlags();
    REQUIRE(flags == std::set<PlayerConfigurationFlag> {
            PlayerConfigurationFlag::sfx,
            PlayerConfigurationFlag::retrig,
            PlayerConfigurationFlag::sfxLoopTo,
            PlayerConfigurationFlag::sfxNoSoftNoHard,
            PlayerConfigurationFlag::sfxNoSoftNoHardNoise,
            PlayerConfigurationFlag::sfxSoftOnly,
            PlayerConfigurationFlag::sfxSoftAndHard,
            PlayerConfigurationFlag::sfxSoftAndHardRetrig,
            PlayerConfigurationFlag::sfxSoftAndHardNoise,
            });

    TestTool::compare(generatedMusicMemoryBlock, BinaryData::sfxFullMinus_asm, BinaryData::sfxFullMinus_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/test/output.asm", generatedMusicMemoryBlock);
}

} // namespace arkostracker
