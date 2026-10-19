#include "../../catch.hpp"

#include "BinaryData.h"

#include <juce_core/juce_core.h>

#include "../../../source/export/midi/MidiExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../../source/utils/ZipHelper.h"
#include "../../controllers/SongControllerForTest.h"

namespace arkostracker
{

class TestHelper
{
public:
    static void performTest(const char* inputSongData, size_t inputSongSize, const char* expectedSourceData, size_t expectedSourceDataSize,
        const MidiExporter::ExportData& exportData)
    {
        // Given.
        juce::MemoryInputStream zippedInputStream(inputSongData, inputSongSize, false);
        const auto inputStream = ZipHelper::unzip(zippedInputStream);

        SongLoader loader;
        const auto loadResult = loader.loadSong(*inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto songUniquePtr = std::move(loadResult->song);
        auto song = std::shared_ptr(std::move(songUniquePtr));

        // When.
        const auto subsongId = song->getFirstSubsongId();

        SongControllerForTest songController(song);
        MidiExporter exporter(songController, subsongId, exportData);
        const auto [success, result] = exporter.performTask();
        REQUIRE(success);
        REQUIRE(result != nullptr);

        //FileUtil::saveMemoryBlockToFile("~/Documents/dev/cpc/tests/test.mid", *result);

        juce::MemoryBlock expectedMemoryBlock(expectedSourceData, expectedSourceDataSize);
        REQUIRE(MemoryBlockUtil::compare(*result, expectedMemoryBlock));
    }
};

TEST_CASE("midi exporter, several channels, tempo", "[MidiExporter]")
{
    const MidiExporter::ExportData exportData(
        {
            { 1, MidiExporter::InstrumentWithMidiData(0, { }) },
        },
        10, true);
    TestHelper::performTest(BinaryData::At3MidiTest_aks, BinaryData::At3MidiTest_aksSize,
        BinaryData::ExpectedMidiSeveralChannelsTempo_mid, BinaryData::ExpectedMidiSeveralChannelsTempo_midSize, exportData);
}

TEST_CASE("midi exporter, simple", "[MidiExporter]")
{
    const MidiExporter::ExportData exportData(
        {
            { 1, MidiExporter::InstrumentWithMidiData(0, { }) },
        },
        10, true);
    TestHelper::performTest(BinaryData::At3MidiSimple_aks, BinaryData::At3MidiSimple_aksSize,
        BinaryData::ExpectedMidiSimple_mid, BinaryData::ExpectedMidiSimple_midSize, exportData);
}

TEST_CASE("midi exporter, simple2", "[MidiExporter]")
{
    const MidiExporter::ExportData exportData(
        {
            { 1, MidiExporter::InstrumentWithMidiData(0, { }) },
        },
        10, true);
    TestHelper::performTest(BinaryData::At3MidiSimple2_aks, BinaryData::At3MidiSimple2_aksSize,
        BinaryData::ExpectedMidiSimple2_mid, BinaryData::ExpectedMidiSimple2_midSize, exportData);
}

TEST_CASE("midi exporter, crime parking", "[MidiExporter]")
{
    const MidiExporter::ExportData exportData(
        {
            { 1, MidiExporter::InstrumentWithMidiData(0, { }) },
            { 6, MidiExporter::InstrumentWithMidiData(1, { }) },
        },
        10, true);
    TestHelper::performTest(BinaryData::At3CrimeParkingIntro_aks, BinaryData::At3CrimeParkingIntro_aksSize,
        BinaryData::ExpectedMidiCrimeParkingIntro_mid, BinaryData::ExpectedMidiCrimeParkingIntro_midSize, exportData);
}

TEST_CASE("midi exporter, crime parking, more tracks", "[MidiExporter]")
{
    const MidiExporter::ExportData exportData(
        {
            { 1, MidiExporter::InstrumentWithMidiData(0, { }) },
            { 2, MidiExporter::InstrumentWithMidiData(0, 35) },
            { 3, MidiExporter::InstrumentWithMidiData(0, 38) },
            { 4, MidiExporter::InstrumentWithMidiData(3, { }) },
            { 5, MidiExporter::InstrumentWithMidiData(4, { }) },
            { 6, MidiExporter::InstrumentWithMidiData(5, { }) },
            { 7, MidiExporter::InstrumentWithMidiData(6, { }) },
            { 8, MidiExporter::InstrumentWithMidiData(7, { }) },
            { 9, MidiExporter::InstrumentWithMidiData(8, { }) },
            { 0xa, MidiExporter::InstrumentWithMidiData(9, { }) },
            { 0xb, MidiExporter::InstrumentWithMidiData(10, { }) },
            { 0xc, MidiExporter::InstrumentWithMidiData(11, { }) },
            { 0xd, MidiExporter::InstrumentWithMidiData(12, { }) },
            { 0xe, MidiExporter::InstrumentWithMidiData(13, { }) },
            { 0xf, MidiExporter::InstrumentWithMidiData(14, { }) },
        },
        10, true);
    TestHelper::performTest(BinaryData::At3CrimeParkingIntro_aks, BinaryData::At3CrimeParkingIntro_aksSize,
        BinaryData::ExpectedMidiCrimeParkingIntroMoreTracks_mid, BinaryData::ExpectedMidiCrimeParkingIntroMoreTracks_midSize, exportData);
}

TEST_CASE("midi exporter, 2 psgs", "[MidiExporter]")
{
    const MidiExporter::ExportData exportData(
        {
            { 1, MidiExporter::InstrumentWithMidiData(1, { }) },
        },
        10, false);
    TestHelper::performTest(BinaryData::At3Midi2Psgs_aks, BinaryData::At3Midi2Psgs_aksSize,
        BinaryData::ExpectedMidi2Psgs_mid, BinaryData::ExpectedMidi2Psgs_midSize, exportData);
}

}   // namespace arkostracker
