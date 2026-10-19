#include "../../catch.hpp"

#include "../../../source/export/ym/YmExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../../source/utils/MemoryBlockUtil.h"

#include <juce_core/juce_core.h>

#include <BinaryData.h>

#include "../../../source/reader/ym/YmReader.h"

namespace arkostracker 
{

class Tool
{
public:
    static juce::MemoryBlock exportToYm(const char* songBinary, int songSize, bool interleaved, bool isYm3)
    {
        // Given.
        juce::MemoryInputStream inputStream(songBinary, static_cast<size_t>(songSize), false);
        SongLoader loader;
        const auto result = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE((result != nullptr));
        REQUIRE((result->errorReport != nullptr));
        REQUIRE(result->errorReport->isOk());
        const std::shared_ptr song = std::move(result->song);

        // When.
        YmExporter ymExporter(song, song->getFirstSubsongId(), 0, interleaved, isYm3);
        const auto&[success, outputStream] = ymExporter.performTask();

        // Then.
        REQUIRE(success);
        REQUIRE((outputStream != nullptr));

        return outputStream->getMemoryBlock();
    }
};

TEST_CASE("YmExporter, harmless grenade, non-interleaved", "[YmExporter]")
{
    const auto generatedYm = Tool::exportToYm(BinaryData::At2TarghanAHarmlessGrenade_aks, BinaryData::At2TarghanAHarmlessGrenade_aksSize, false, false);
    const juce::MemoryBlock expectedMusicMemoryBlock(BinaryData::HarmlessNonInterleaved_ym, BinaryData::HarmlessNonInterleaved_ymSize);

    REQUIRE(MemoryBlockUtil::compare(generatedYm, expectedMusicMemoryBlock));
}

TEST_CASE("YmExporter, harmless grenade, interleaved", "[YmExporter]")
{
    const auto generatedYm = Tool::exportToYm(BinaryData::At2TarghanAHarmlessGrenade_aks, BinaryData::At2TarghanAHarmlessGrenade_aksSize, true, false);
    const juce::MemoryBlock expectedMusicMemoryBlock(BinaryData::HarmlessInterleaved_ym, BinaryData::HarmlessInterleaved_ymSize);

    REQUIRE(MemoryBlockUtil::compare(generatedYm, expectedMusicMemoryBlock));
}

TEST_CASE("YmExporter, simple with bass hard", "[YmExporter]")
{
    const auto generatedYm = Tool::exportToYm(BinaryData::At3SimpleForYmExport_xml, BinaryData::At3SimpleForYmExport_xmlSize, true, false);
    const juce::MemoryBlock expectedMusicMemoryBlock(BinaryData::At3SimpleForYmExport_ym, BinaryData::At3SimpleForYmExport_ymSize);

    REQUIRE(MemoryBlockUtil::compare(generatedYm, expectedMusicMemoryBlock));
}

TEST_CASE("YmExporter, edredon song didn't work", "[YmExporter]")
{
    // An event was programmed but no linked sample.
    const auto generatedYm = Tool::exportToYm(BinaryData::At2EdredonAlcaloids_xml, BinaryData::At2EdredonAlcaloids_xmlSize, true, false);
    juce::MemoryInputStream mis(generatedYm, false);

    YmReader ymReader(mis);
    REQUIRE(ymReader.checkFormat());
    REQUIRE(ymReader.prepare());
}

TEST_CASE("YmExporter, molusk, ym3", "[YmExporter]")
{
    const auto generatedYm = Tool::exportToYm(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize, true, true);
    const juce::MemoryBlock expectedMusicMemoryBlock(BinaryData::moluskYm3Interleaved_ym, BinaryData::moluskYm3Interleaved_ymSize);

    REQUIRE(MemoryBlockUtil::compare(generatedYm, expectedMusicMemoryBlock));
}

}   // namespace arkostracker
