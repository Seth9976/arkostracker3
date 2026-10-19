#include "BinaryData.h"
#include "../../catch.hpp"

#include "../../../source/business/instrument/GenericInstrumentGenerator.h"
#include "../../../source/business/instrument/SampleLoader.h"
#include "../../../source/export/instrumentAsWav/InstrumentAsWavExporter.h"
#include "../../controllers/SongControllerForTest.h"

namespace arkostracker
{

static void perform(const std::shared_ptr<Song>& song, const Id& instrumentId, const int minimumSizeToCheck, const int maximumSizeToCheck,
    const int firstNote, const int lastNote,
    const float replayFrequencyHz, const int minimumDurationMs, const OptionalInt maximumSize)
{
    const auto outputFolder = juce::File::getSpecialLocation(juce::File::tempDirectory);
    //const auto outputFolder = juce::File("~/Documents/dev/cpc/tests");

    const auto psg = Psg::buildForCpc();
    const auto generatedFileCount = lastNote - firstNote + 1;
    InstrumentAsWavExporter exporter(song, instrumentId, outputFolder, "Instr", firstNote, lastNote,
        psg, replayFrequencyHz, SidPlayerCapability::buildForCpc(), minimumDurationMs, maximumSize);

    const auto [success, outputFiles] = exporter.performTask();
    REQUIRE(success);
    REQUIRE((outputFiles != nullptr));
    REQUIRE((outputFiles->size() == static_cast<size_t>(generatedFileCount)));

    if (outputFiles != nullptr) {
        for (const auto& outputFile : *outputFiles) {
            REQUIRE((outputFile.getSize() >= minimumSizeToCheck));
            REQUIRE((outputFile.getSize() <= maximumSizeToCheck));
            (void)outputFile.deleteFile();
        }
    }
}

TEST_CASE("InstrumentAsWavExporter, simple PSG sound", "[InstrumentAsWavExporter]")
{
    auto uniqueSong = Song::buildDefaultSong(false);
    const auto song = std::shared_ptr(std::move(uniqueSong));

    auto instr1 = GenericInstrumentGenerator::generateInstrumentForDecreasingVolume("i1");
    const auto instrumentId = instr1->getId();
    song->addInstrument(std::move(instr1));

    constexpr auto firstNote = (4 * 12) + 10;
    constexpr auto lastNote = firstNote + 10;

    constexpr auto minimumSizeToCheck = 12 * 1024;
    constexpr auto maximumSizeToCheck = 13 * 1024;

    perform(song, instrumentId, minimumSizeToCheck, maximumSizeToCheck, firstNote, lastNote, PsgFrequency::defaultReplayFrequencyHz, 0, { });
}

TEST_CASE("InstrumentAsWavExporter, PSG sound, hard with minimum duration", "[InstrumentAsWavExporter]")
{
    auto uniqueSong = Song::buildDefaultSong(false);
    const auto song = std::shared_ptr(std::move(uniqueSong));

    auto instr1 = GenericInstrumentGenerator::generateInstrumentForHardBass1();
    const auto instrumentId = instr1->getId();
    song->addInstrument(std::move(instr1));

    constexpr auto firstNote = 4 * 12;
    constexpr auto lastNote = firstNote;

    constexpr auto minimumDurationMs = 5000;
    constexpr auto minimumSizeToCheck = 214 * 1024;
    constexpr auto maximumSizeToCheck = 215 * 1024;

    perform(song, instrumentId, minimumSizeToCheck, maximumSizeToCheck, firstNote, lastNote, PsgFrequency::defaultReplayFrequencyHz, minimumDurationMs, { });
}

TEST_CASE("InstrumentAsWavExporter, sample", "[InstrumentAsWavExporter]")
{
    auto uniqueSong = Song::buildDefaultSong(false);
    const auto song = std::shared_ptr(std::move(uniqueSong));

    // Loads a WAV file.
    const auto sampleWav = juce::MemoryBlock(BinaryData::Analogstring_wav, BinaryData::Analogstring_wavSize);
    auto sampleInputStream = std::make_unique<juce::MemoryInputStream>(sampleWav, false);

    juce::AudioFormatManager audioFormatManager;
    audioFormatManager.registerBasicFormats();
    const std::unique_ptr<juce::AudioFormatReader> reader(audioFormatManager.createReaderFor(std::move(sampleInputStream)));

    const auto result = SampleLoader::read(*reader, "");
    REQUIRE((result != nullptr));
    const auto sampleMemoryBlock = result->getData();

    const auto sample = std::make_shared<Sample>(*sampleMemoryBlock);
    const auto samplePart = SamplePart(sample, Loop(0, static_cast<int>(sampleMemoryBlock->getSize())), 1.0F,
        8363);

    auto instr1 = Instrument::buildSampleInstrument("i1", samplePart);
    const auto instrumentId = instr1->getId();
    song->addInstrument(std::move(instr1));

    constexpr auto firstNote = 6 * 12;
    constexpr auto lastNote = firstNote + 5;
    constexpr auto minimumSizeToCheck = 6 * 1024;
    constexpr auto maximumSizeToCheck = 9 * 1024;

    perform(song, instrumentId, minimumSizeToCheck, maximumSizeToCheck, firstNote, lastNote, PsgFrequency::defaultReplayFrequencyHz, { }, { });
}

TEST_CASE("InstrumentAsWavExporter, sample with limitation", "[InstrumentAsWavExporter]")
{
    auto uniqueSong = Song::buildDefaultSong(false);
    const auto song = std::shared_ptr(std::move(uniqueSong));

    // Loads a WAV file.
    const auto sampleWav = juce::MemoryBlock(BinaryData::Analogstring_wav, BinaryData::Analogstring_wavSize);
    auto sampleInputStream = std::make_unique<juce::MemoryInputStream>(sampleWav, false);

    juce::AudioFormatManager audioFormatManager;
    audioFormatManager.registerBasicFormats();
    const std::unique_ptr<juce::AudioFormatReader> reader(audioFormatManager.createReaderFor(std::move(sampleInputStream)));

    const auto result = SampleLoader::read(*reader, "");
    REQUIRE((result != nullptr));
    const auto sampleMemoryBlock = result->getData();

    const auto sample = std::make_shared<Sample>(*sampleMemoryBlock);
    const auto samplePart = SamplePart(sample, Loop(0, static_cast<int>(sampleMemoryBlock->getSize())), 1.0F,
        8363);

    auto instr1 = Instrument::buildSampleInstrument("i1", samplePart);
    const auto instrumentId = instr1->getId();
    song->addInstrument(std::move(instr1));

    constexpr auto firstNote = 0;
    constexpr auto lastNote = firstNote;
    constexpr auto minimumSizeToCheck = 65640;
    constexpr auto maximumSizeToCheck = minimumSizeToCheck;
    constexpr auto maximumSize = 1024 * 64;

    perform(song, instrumentId, minimumSizeToCheck, maximumSizeToCheck, firstNote, lastNote, PsgFrequency::defaultReplayFrequencyHz, { }, maximumSize);
}

}   // namespace arkostracker
