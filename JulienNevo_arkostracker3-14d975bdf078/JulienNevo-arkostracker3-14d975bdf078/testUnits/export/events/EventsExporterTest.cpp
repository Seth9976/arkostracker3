#include "../../catch.hpp"

#include "../../../source/export/events/EventsExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../helper/RasmHelper.h"
#include "BinaryData.h"

#include <juce_core/juce_core.h>

namespace arkostracker
{

class TestHelper
{
public:
    static void performTest(const char* inputSongData, size_t inputSongSize, const char* expectedSourceData, size_t expectedSourceDataSize,
        std::set<EventsExporter::Type> typesToExport = { EventsExporter::Type::events, EventsExporter::Type::samples })
    {
        // Given.
        juce::MemoryInputStream inputStream(inputSongData, inputSongSize, false);
        SongLoader loader;
        const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
        REQUIRE(loadResult != nullptr);
        REQUIRE(loadResult->errorReport != nullptr);
        REQUIRE(loadResult->errorReport->isOk());
        auto songUniquePtr = std::move(loadResult->song);
        auto song = std::shared_ptr(std::move(songUniquePtr));

        // When.
        const auto subsongId = song->getFirstSubsongId();
        // The SubsongId is only set here to prevent an assertion.
        const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), { subsongId }, "label_", 0x4000,
            SampleEncoderFlags(), false);
        EventsExporter exporter(song, typesToExport, exportConfiguration);
        const auto [success, result] = exporter.performTask();
        REQUIRE(success);
        REQUIRE(result != nullptr);

        // Then. Compares the assembled code.
        const auto songData = result->getSongData();
        const auto expectedSourceMemoryBlock = juce::MemoryBlock(expectedSourceData, expectedSourceDataSize);

        REQUIRE(RasmHelper::assembleAndCompareSources(songData, expectedSourceMemoryBlock));
    }
};

/** Tests the Events Exporter class. */

TEST_CASE("events exporter, sarkboteur", "[EventsExporter]")
{
    TestHelper::performTest(BinaryData::At3Sarkboteur_xml, BinaryData::At3Sarkboteur_xmlSize,
        BinaryData::eventsSarkboteur_asm, BinaryData::eventsSarkboteur_asmSize);
}

TEST_CASE("events exporter, sarkboteur, sample events only exported", "[EventsExporter]")
{
    TestHelper::performTest(BinaryData::At3Sarkboteur_xml, BinaryData::At3Sarkboteur_xmlSize,
        BinaryData::eventsSarkboteur_asm, BinaryData::eventsSarkboteur_asmSize,
        { EventsExporter::Type::samples});
}

TEST_CASE("events exporter, simple loop position 0", "[EventsExporter]")
{
    TestHelper::performTest(BinaryData::At2SimpleWithEvents_xml, BinaryData::At2SimpleWithEvents_xmlSize,
        BinaryData::eventsLoopPosition0_asm, BinaryData::eventsLoopPosition0_asmSize);
}

TEST_CASE("events exporter, simple loop position 1", "[EventsExporter]")
{
    TestHelper::performTest(BinaryData::At2SimpleWithEventsLoopPosition1_xml, BinaryData::At2SimpleWithEventsLoopPosition1_xmlSize,
        BinaryData::eventsLoopPosition1_asm, BinaryData::eventsLoopPosition1_asmSize);
}

TEST_CASE("events exporter, simple pattern, all events", "[EventsExporter]")
{
    TestHelper::performTest(BinaryData::At3EventTypes_xml, BinaryData::At3EventTypes_xmlSize,
        BinaryData::At3EventTypes_all_asm, BinaryData::At3EventTypes_all_asmSize);
}

TEST_CASE("events exporter, simple pattern, samples only", "[EventsExporter]")
{
    TestHelper::performTest(BinaryData::At3EventTypes_xml, BinaryData::At3EventTypes_xmlSize,
        BinaryData::At3EventTypes_sample_asm, BinaryData::At3EventTypes_sample_asmSize,
        { EventsExporter::Type::samples});
}

TEST_CASE("events exporter, simple pattern, events only", "[EventsExporter]")
{
    TestHelper::performTest(BinaryData::At3EventTypes_xml, BinaryData::At3EventTypes_xmlSize,
        BinaryData::At3EventTypes_event_asm, BinaryData::At3EventTypes_event_asmSize,
        { EventsExporter::Type::events});
}

}   // namespace arkostracker
