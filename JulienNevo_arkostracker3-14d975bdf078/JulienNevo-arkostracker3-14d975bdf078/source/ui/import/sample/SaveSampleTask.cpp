#include "SaveSampleTask.h"

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_formats/juce_audio_formats.h>

#include <utility>

#include "../../../utils/FileUtil.h"

namespace arkostracker
{
SaveSampleTask::SaveSampleTask(SongController& pSongController, Id pInstrumentId, juce::String pFileToSave) noexcept :
        songController(pSongController),
        instrumentId(std::move(pInstrumentId)),
        fileToSave(std::move(pFileToSave))
{
}

std::pair<bool, std::unique_ptr<bool>> SaveSampleTask::performTask() noexcept
{
    // Retrieves the sample.
    const auto& song = songController.getSong();
    std::shared_ptr<Sample> sample;
    auto exportFrequencyHz = 0;
    song->performOnConstInstrument(instrumentId, [&] (const Instrument& instrument) {
        if (instrument.getType() == InstrumentType::sampleInstrument) {
            const auto& samplePart = instrument.getConstSamplePart();
            sample = samplePart.getSample();
            exportFrequencyHz = samplePart.getFrequencyHz();
        } else {
            jassertfalse;
        }
    });

    auto success = false;

    if ((sample != nullptr) && (exportFrequencyHz > 0)) {
        const auto fileName = FileUtil::getFileFromString(fileToSave);
        (void)fileName.deleteFile();

        auto outputStream = std::make_unique<juce::FileOutputStream>(fileToSave);
        // Gives the ownership to the AudioFormatWriter. Still need a local reference to it, as it will NOT be deleted in case of failure.
        auto* localOutputStream = outputStream.release();

        const auto originalSize = static_cast<unsigned int>(sample->getLength());
        const auto size = ((originalSize & 1U) != 0) ? originalSize - 1 : originalSize ;     // Incredibly enough, if size is odd, some WAV readers cannot read it.
        juce::AudioBuffer<float> sampleBuffer(1, static_cast<int>(size));

        // Converts unsigned char into float.
        for (auto index = 0; index < static_cast<int>(size); ++index) {
            const auto value = sample->operator[](index);
            const auto valueFloat = (static_cast<float>(value) - 128) / 128.0F;
            sampleBuffer.setSample(0, index, valueFloat);
        }

        constexpr auto channelCount = 1;
        constexpr auto bitsPerSample = 8;
        juce::WavAudioFormat wavAudioFormat;
        const std::unique_ptr<juce::AudioFormatWriter> audioFormatWriter(wavAudioFormat.createWriterFor(
            localOutputStream, exportFrequencyHz, channelCount, bitsPerSample, { }, 0));    // No optimization.

        // Stops if the Writer couldn't be created.
        if (audioFormatWriter == nullptr) {
            delete localOutputStream;       // The output stream is NOT deleted in case of failure (cf. createWriterFor documentation).
        } else {
            success = audioFormatWriter->writeFromAudioSampleBuffer(sampleBuffer, 0, sampleBuffer.getNumSamples());
        }
    }

    return { success, std::make_unique<bool>(success) };
}

}       // namespace arkostracker