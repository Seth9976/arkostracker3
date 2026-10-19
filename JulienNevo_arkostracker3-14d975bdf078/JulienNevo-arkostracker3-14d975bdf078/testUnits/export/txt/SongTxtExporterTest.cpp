#include "../../catch.hpp"

#include <juce_core/juce_core.h>

#include "../../../source/export/txt/SongTxtExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "BinaryData.h"

namespace arkostracker
{

TEST_CASE("export Sarkboteur", "[SongTxtExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At3Sarkboteur_xml, BinaryData::At3Sarkboteur_xmlSize, false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE((loadResult != nullptr));
    REQUIRE((loadResult->errorReport != nullptr));
    REQUIRE(loadResult->errorReport->isOk());
    const auto song = std::move(loadResult->song);

    auto outputStream = std::make_unique<juce::MemoryOutputStream>();
    auto& outputStreamRef = *outputStream;
    auto exporter = SongTxtExporter(*song, std::move(outputStream));

    // When.
    const auto& [success1, success2] = exporter.performTask();
    REQUIRE(success1);
    REQUIRE(*success2);

    // Then.
    const juce::MemoryBlock expectedMemoryBlock(BinaryData::SarkboteurTxtExport_txt, BinaryData::SarkboteurTxtExport_txtSize);
    REQUIRE(MemoryBlockUtil::compare(expectedMemoryBlock, outputStreamRef.getMemoryBlock()));
}

}   // namespace arkostracker
