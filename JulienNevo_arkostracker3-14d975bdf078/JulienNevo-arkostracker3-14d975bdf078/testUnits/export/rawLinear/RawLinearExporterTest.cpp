#include <juce_core/juce_core.h>

#include "../../../source/export/rawLinear/RawLinearExport.h"
#include "../../../source/song/Song.h"
#include "../../catch.hpp"
#include "../../helper/RasmHelper.h"
#include "../../helper/SongTestHelper.h"
#include "../../helper/TrackTestHelper.h"
#include "BinaryData.h"

namespace arkostracker
{

TEST_CASE("raw linear exporter, nominal with psg instruments", "[RawLinearExporter]")
{
    constexpr auto startAddress = 0x1000;
    auto songUniquePtr = Song::buildDefaultSong(false);
    auto song = std::shared_ptr(std::move(songUniquePtr));
    song->addInstrument(Instrument::buildEmptyPsgInstrument());
    song->addInstrument(Instrument::buildEmptyPsgInstrument());
    song->addInstrument(Instrument::buildEmptyPsgInstrument());
    const auto subsongId = song->getFirstSubsongId();

    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        subsong.setCell(0, 0, 0, Cell::build(6 * 12, 1));
        subsong.setCell(0, 1, 0, Cell::build(5 * 12, 1));

        subsong.setCell(0, 0, 1, Cell::build((6 * 12) + 1, 2));
        subsong.setCell(0, 3, 1, Cell::build((6 * 12) + 1, 40)); // Fake instrument.
        subsong.setCell(0, 4, 1, Cell({ }, { },
                                      CellEffects({
                                          { Effect::pitchUp, 0x123 },
                                      })));

        subsong.setCell(0, 13, 2, Cell::build((6 * 12) + 1, 3,
            CellEffects({
                { Effect::volume, 0x0f },
            })));
        subsong.setCell(0, 14, 2, Cell(Note::buildNote(99), 3));

        const auto position = subsong.getPosition(0).withHeight(16);
        subsong.setPosition(0, position);
    });

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
    SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::psgInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((result != nullptr));

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinearSimple_asm, BinaryData::ExportRawLinearSimple_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}

TEST_CASE("raw linear exporter, nominal with psg instruments, transposition", "[RawLinearExporter]")
{
    constexpr auto startAddress = 0x1000;
    auto songUniquePtr = Song::buildDefaultSong(false);
    auto song = std::shared_ptr(std::move(songUniquePtr));
    song->addInstrument(Instrument::buildEmptyPsgInstrument());
    song->addInstrument(Instrument::buildEmptyPsgInstrument());
    song->addInstrument(Instrument::buildEmptyPsgInstrument());
    const auto subsongId = song->getFirstSubsongId();

    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        subsong.setCell(0, 0, 0, Cell::build(6 * 12, 1));
        subsong.setCell(0, 1, 0, Cell::build(5 * 12, 1));

        subsong.setCell(0, 0, 1, Cell::build((6 * 12) + 1, 2));
        subsong.setCell(0, 3, 1, Cell::build((6 * 12) + 1, 40)); // Fake instrument.
        subsong.setCell(0, 4, 1, Cell({ }, { },
                                      CellEffects({
                                          { Effect::pitchUp, 0x123 },
                                      })));

        subsong.setCell(0, 13, 2, Cell::build((6 * 12) + 1, 3,
            CellEffects({
                { Effect::volume, 0x0f },
            })));
        subsong.setCell(0, 14, 2, Cell(Note::buildNote(99), 3));

        const auto position = subsong.getPosition(0).withHeight(16).withTranspositions(
            {
                { 0, 1 },
                { 1, 2 },
                { 2, -1 },
            });

        subsong.setPosition(0, position);
    });

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
    SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::psgInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((result != nullptr));

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinearSimpleWithTransposition_asm, BinaryData::ExportRawLinearSimpleWithTransposition_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}

TEST_CASE("raw linear exporter, nominal with sample instruments", "[RawLinearExporter]")
{
    constexpr auto startAddress = 0x1000;
    auto songUniquePtr = Song::buildDefaultSong(false);
    auto song = std::shared_ptr(std::move(songUniquePtr));
    song->addInstrument(Instrument::buildSampleInstrument("i1", SamplePart()));
    song->addInstrument(Instrument::buildSampleInstrument("i2", SamplePart()));
    song->addInstrument(Instrument::buildSampleInstrument("i3", SamplePart()));
    const auto subsongId = song->getFirstSubsongId();

    // Same as above, but filtering only the samples.
    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        subsong.setCell(0, 0, 0, Cell::build(6 * 12, 1));
        subsong.setCell(0, 1, 0, Cell::build(5 * 12, 1));

        subsong.setCell(0, 0, 1, Cell::build((6 * 12) + 1, 2));
        subsong.setCell(0, 3, 1, Cell::build((6 * 12) + 1, 40)); // Fake instrument.
        subsong.setCell(0, 4, 1, Cell({ }, { },
                                      CellEffects({
                                          { Effect::pitchUp, 0x123 },
                                      })));

        subsong.setCell(0, 13, 2, Cell::build((6 * 12) + 1, 3,
            CellEffects({
                { Effect::volume, 0x0f },
            })));
        subsong.setCell(0, 14, 2, Cell(Note::buildNote(99), 3));

        const auto position = subsong.getPosition(0).withHeight(16);
        subsong.setPosition(0, position);
    });

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
    SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::sampleInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((result != nullptr));

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinearSimple_asm, BinaryData::ExportRawLinearSimple_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}

// Legato not supported... TO IMPROVE: ACTUALLY it could be now!
/*
TEST_CASE("raw linear exporter, samples and legato", "[RawLinearExporter]")
{
    constexpr auto startAddress = 0x1000;
    auto songUniquePtr = Song::buildDefaultSong(false);
    auto song = std::shared_ptr(std::move(songUniquePtr));
    song->addInstrument(Instrument::buildSampleInstrument("i1", SamplePart()));
    song->addInstrument(Instrument::buildSampleInstrument("i2", SamplePart()));
    song->addInstrument(Instrument::buildSampleInstrument("i3", SamplePart()));
    const auto subsongId = song->getFirstSubsongId();

    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        subsong.setCell(0, 0, 0, Cell::build(30, 1));
        subsong.setCell(0, 1, 0, Cell(Note::buildNote(31), { }));

        const auto position = subsong.getPosition(0).withHeight(16);
        subsong.setPosition(0, position);
    });

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
    SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::sampleInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE(result != nullptr);

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinearSimple_asm, BinaryData::ExportRawLinearSimple_asmSize);

    // Useful for testing.
    FileUtil::saveMemoryBlockToFile("~/Documents/dev/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}*/

TEST_CASE("raw linear exporter, both types but only sample is wanted", "[RawLinearExporter]")
{
    constexpr auto startAddress = 0x1000;
    auto songUniquePtr = Song::buildDefaultSong(false);
    auto song = std::shared_ptr(std::move(songUniquePtr));
    song->addInstrument(Instrument::buildSampleInstrument("i1", SamplePart()));      // 1, sample.
    song->addInstrument(Instrument::buildEmptyPsgInstrument());      // 2, PSG, stop.
    song->addInstrument(Instrument::buildEmptyPsgInstrument());      // 3, PSG, stop.
    const auto subsongId = song->getFirstSubsongId();

    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        subsong.setCell(0, 0, 0, Cell::build(50, 1));
        subsong.setCell(0, 1, 0, Cell::build(5 * 12, 2));       // Stops sample.
        subsong.setCell(0, 2, 0, Cell::build(5 * 12, 2));       // Ignored.

        subsong.setCell(0, 0, 1, Cell::build((6 * 12) + 1, 2));   // PSG instrument, so force RST.
        subsong.setCell(0, 4, 1, Cell({ }, { },             // Ignored.
                                      CellEffects({
                                          { Effect::pitchUp, 0x123 },
                                      })));

        subsong.setCell(0, 13, 2, Cell::build((6 * 12) + 1, 3,    // PSG instrument, so force RST.
            CellEffects({
                { Effect::volume, 0x0f },
            })));
        subsong.setCell(0, 14, 2, Cell(Note::buildNote(99), 2));    // Ignored.

        const auto position = subsong.getPosition(0).withHeight(16);
        subsong.setPosition(0, position);
    });

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
    SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::sampleInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((result != nullptr));

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinearSample_asm, BinaryData::ExportRawLinearSample_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}

TEST_CASE("raw linear exporter, sample with speed 1", "[RawLinearExporter]")
{
    constexpr auto startAddress = 0x1000;
    auto songUniquePtr = Song::buildDefaultSong(false);
    auto song = std::shared_ptr(std::move(songUniquePtr));
    song->addInstrument(Instrument::buildSampleInstrument("i1", SamplePart()));
    const auto subsongId = song->getFirstSubsongId();

    // Same as above, but filtering only the samples.
    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        subsong.setInitialSpeed(1);

        subsong.setCell(0, 0, 0, Cell::build(10, 1));
        subsong.setCell(0, 1, 0, Cell::build(11, 1));
        subsong.setCell(0, 2, 0, Cell::build(12, 1));

        subsong.setCell(0, 3, 1, Cell::build(20, 1));
        subsong.setCell(0, 4, 1, Cell::build(21, 1));
        subsong.setCell(0, 5, 1, Cell::build(22, 1));

        // One empty line!
        subsong.setCell(0, 7, 2, Cell::build(30, 1));

        const auto position = subsong.getPosition(0).withHeight(10);
        subsong.setPosition(0, position);
    });

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
    SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::sampleInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((result != nullptr));

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinearSampleSpeed1_asm, BinaryData::ExportRawLinearSampleSpeed1_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}

TEST_CASE("raw linear exporter, nominal with sample instruments and loop between space", "[RawLinearExporter]")
{
    constexpr auto startAddress = 0x1000;
    auto songUniquePtr = Song::buildDefaultSong(false);
    auto song = std::shared_ptr(std::move(songUniquePtr));
    const auto subsongId = song->getFirstSubsongId();

    song->addInstrument(Instrument::buildSampleInstrument("i1", SamplePart()));

    song->performOnSubsong(subsongId, [&](Subsong& subsong) {
        const auto position0 = subsong.getPosition(0).withHeight(10);
        subsong.setPosition(0, position0);

        const auto position1 = Position(1, 10);
        subsong.addPosition(position1);

        const auto pattern1 = Pattern({ 3, 4, 5}, 0, 0);
        subsong.addPattern(pattern1);

        subsong.addTrack(Track());
        subsong.addTrack(Track());
        subsong.addTrack(Track());

        subsong.setCell(0, 1, 0, Cell::build(5 * 12, 1));
        subsong.setCell(1, 1, 2, Cell::build((5 * 12) + 1, 1));

        subsong.setLoop(Loop(1, 1, true));
    });

    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
    SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::sampleInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((result != nullptr));

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinearWithLoop_asm, BinaryData::ExportRawLinearWithLoop_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}

TEST_CASE("raw linear exporter, 2 psgs", "[RawLinearExporter]")
{
    // Given.
    const auto song = SongTestHelper::loadSong(BinaryData::At3Midi2Psgs_aks, BinaryData::At3Midi2Psgs_aksSize);
    REQUIRE((song != nullptr));
    const auto subsongId = song->getFirstSubsongId();

    constexpr auto startAddress = 0x4000;
    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", startAddress,
        SampleEncoderFlags(), false);

    RawLinearExporter rawLinearExporter(song, exportConfiguration, { InstrumentType::psgInstrument });

    const auto [success, result] = rawLinearExporter.performTask();

    // Then.
    REQUIRE(success);
    REQUIRE((result != nullptr));

    // Then. Compares the assembled code.
    const auto songData = result->getSongData();
    const auto expectedSourceMemoryBlock = juce::MemoryBlock(BinaryData::ExportRawLinear2Psgs_asm, BinaryData::ExportRawLinear2Psgs_asmSize);

    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/cpc/tests/genRawLinear.asm", songData);

    REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
}

}   // namespace arkostracker
