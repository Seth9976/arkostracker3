#include <juce_core/juce_core.h>

#include "../../../source/export/raw/RawExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../catch.hpp"
#include "../../helper/RasmHelper.h"
#include "BinaryData.h"

namespace arkostracker
{

/** Tests the RawExporter class. */

class TestHelper
{
public:
    static void performTest(const EncodedDataFlag& encodedDataFlag, const char* inputSongData, size_t inputSongSize,
        const char* expectedSourceData, size_t expectedSourceDataSize, const juce::String& commentHack = juce::String(),
        const std::unordered_set<int>& errorAddresses = { }, int tolerance = 0)
    {
        // Given.
        juce::MemoryInputStream inputStream(inputSongData, inputSongSize, false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE((loadResult != nullptr));
        REQUIRE((loadResult->errorReport != nullptr));
        REQUIRE(loadResult->errorReport->isOk());
        auto songUniquePtr = std::move(loadResult->song);
        auto song = std::shared_ptr(std::move(songUniquePtr));

        // When.
        // A hack to force the comment.
        if (commentHack.isNotEmpty()) {
            song->setComments(commentHack);
        }
        const auto subsongId = song->getFirstSubsongId();
        const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", 0x100,
            SampleEncoderFlags(), false);
        RawExporter exporter(*song, encodedDataFlag, exportConfiguration);
        const auto [success, result] = exporter.performTask();
        REQUIRE(success);
        REQUIRE((result != nullptr));

        // Then. Compares the assembled code.
        const auto songData = result->getSongData();
        const auto expectedSourceMemoryBlock = juce::MemoryBlock(expectedSourceData, expectedSourceDataSize);

        // Useful for testing.
        //FileUtil::saveMemoryBlockToFile("~/Documents/dev/cpc/tests/genRaw.asm", songData);

        REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock, errorAddresses, tolerance));
    }
};

TEST_CASE("raw exporter, minimalist using MOD parameters", "[RawExporter]")
{
    const EncodedDataFlag encodedDataFlag;

    TestHelper::performTest(encodedDataFlag, BinaryData::At2ExportRawInput_xml, BinaryData::At2ExportRawInput_xmlSize,
        BinaryData::ExportRawOutputMod_asm, BinaryData::ExportRawOutputMod_asmSize);
}

TEST_CASE("raw exporter, export full", "[RawExporter]")
{
    const EncodedDataFlag encodedDataFlag(true);

    TestHelper::performTest(encodedDataFlag, BinaryData::At2ExportRawInput_xml, BinaryData::At2ExportRawInput_xmlSize,
        BinaryData::ExportRawOutput_asm, BinaryData::ExportRawOutput_asmSize);
}

TEST_CASE("raw exporter, export PSG and SPL", "[RawExporter]")
{
    const EncodedDataFlag encodedDataFlag(true);

    // A 'comment' hack is used, because the original Song has illegal chars in the comment... Nothing done about it for now.
    TestHelper::performTest(encodedDataFlag, BinaryData::At3Sarkboteur_xml, BinaryData::At3Sarkboteur_xmlSize,
        BinaryData::ExportSarkboteur_asm, BinaryData::ExportSarkboteur_asmSize, "The comment",
#ifdef JUCE_MAC
        // F*ing hell, a small approx is possible on Mac (CI only!!).
        { 5302, 5364 }, 1
#else
        { }, 0
#endif
    );
}

}   // namespace arkostracker
