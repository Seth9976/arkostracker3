#include "../../catch.hpp"

#include "BinaryData.h"

#include <juce_core/juce_core.h>

#include "../../../source/export/mod/ModExporter.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../helper/SongTestHelper.h"

namespace arkostracker
{

class TestHelper
{
public:
    static void performTest(const char* inputSongData, size_t inputSongSize, const char* expectedSourceData, size_t expectedSourceDataSize,
        int minimumDurationMs = 0)
    {
        const auto song = SongTestHelper::loadSong(inputSongData, inputSongSize);
        REQUIRE((song != nullptr));

        const auto subsongId = song->getFirstSubsongId();
        juce::MemoryOutputStream outputStream;
        // For testing.
        //const juce::File outputFile("~/Documents/dev/cpc/tests/test.mod");
        //REQUIRE(outputFile.deleteFile());
        //juce::FileOutputStream outputStream(outputFile);

        ModExporter exporter(song, subsongId, minimumDurationMs, outputStream);
        const auto [success, result] = exporter.performTask();
        REQUIRE(success);
        REQUIRE((result != nullptr));

        const juce::MemoryBlock expectedMemoryBlock(expectedSourceData, expectedSourceDataSize);
        REQUIRE(MemoryBlockUtil::compare(outputStream.getMemoryBlock(), expectedMemoryBlock));
    }
};

TEST_CASE("mod exporter, simple", "[ModExporter]")
{
    TestHelper::performTest(BinaryData::At3SimpleWithVolume_aks, BinaryData::At3SimpleWithVolume_aksSize,
        BinaryData::ExportSimple_mod, BinaryData::ExportSimple_modSize);
}

TEST_CASE("mod exporter, sample", "[ModExporter]")
{
    TestHelper::performTest(BinaryData::At3SimpleWav_aks, BinaryData::At3SimpleWav_aksSize,
        BinaryData::ExportSample_mod, BinaryData::ExportSample_modSize);
}

TEST_CASE("mod exporter, 9 channels, PSG", "[ModExporter]")
{
    TestHelper::performTest(BinaryData::At2TheLastV8_aks, BinaryData::At2TheLastV8_aksSize,
        BinaryData::ExportLastV8_mod, BinaryData::ExportLastV8_modSize,
        3000);
}

TEST_CASE("mod exporter, tempo change", "[ModExporter]")
{
    TestHelper::performTest(BinaryData::At3TempoChange_aks, BinaryData::At3TempoChange_aksSize,
        BinaryData::ExportTempoChange_mod, BinaryData::ExportTempoChange_modSize,
        1000);
}

TEST_CASE("mod exporter, molusk", "[ModExporter]")
{
    TestHelper::performTest(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize,
        BinaryData::ExportMolusk_mod, BinaryData::ExportMolusk_modSize,
        1000);
}

}   // namespace arkostracker
