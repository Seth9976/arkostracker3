#include "../../catch.hpp"

#include "../../../source/business/instrument/SampleLoader.h"
#include "../../../source/export/wav/SongWavExporter.h"
#include "../../../source/import/loader/SongLoader.h"

#include <juce_core/juce_core.h>

#include <BinaryData.h>

namespace arkostracker
{

TEST_CASE("WavExporter, check volume with 200hz 6 channels song", "[WavExporter]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::At3_200Hz6ChannelsSquare_xml, BinaryData::At3_200Hz6ChannelsSquare_xmlSize, false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE((loadResult != nullptr));
    REQUIRE((loadResult->errorReport != nullptr));
    REQUIRE((loadResult->errorReport->isOk()));
    const std::shared_ptr song = std::move(loadResult->song);

    const auto subsongId = song->getFirstSubsongId();

    OutputMix const outputMix(100, 100, 100, 100, false, 100);

    const auto outputFile = juce::File::createTempFile("wav");

    // When.
    SongWavExporter exporter(song, subsongId, 44100.0, 1, outputMix, outputFile, false);

    // Then.
    const auto [success, snd] = exporter.performTask();
    REQUIRE(success);

    const auto result = SampleLoader::readFile(outputFile);
    (void)outputFile.deleteFile();

    REQUIRE((result->getOutcome() == SampleLoader::Outcome::success));

    const auto& data = result->getData();
    const auto dataSize = data->getSize();
    REQUIRE((dataSize == 63488));

    // Makes sure there are no "holes", since the sound is full on all channels. Holes ("stuttering") were happening when the PSG had not queues.
    for (size_t i = 0; i < dataSize; ++i) {
        const auto value = data->operator[](i);
        REQUIRE((value != 0));
    }
}

}   // namespace arkostracker
