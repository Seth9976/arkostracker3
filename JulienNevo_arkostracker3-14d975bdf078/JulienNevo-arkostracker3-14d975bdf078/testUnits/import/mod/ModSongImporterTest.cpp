#include "../../catch.hpp"

#include <juce_core/juce_core.h>

#include "../../../source/song/subsong/SubsongConstants.h"
#include "../../../source/import/mod/ModSongImporter.h"
#include "../../helper/TrackTestHelper.h"
#include "BinaryData.h"

namespace arkostracker 
{

TEST_CASE("MOD import, wrong file", "[ModSongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::At2AllEffects_aks, BinaryData::At2AllEffects_aksSize, false);

    // Parses.
    const ModSongImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "aaa"));
}

TEST_CASE("MOD import, format ok, thanks to extension", "[ModSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::BLUESHAD_MOD, BinaryData::BLUESHAD_MODSize, false);

    // Parses.
    const ModSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mod"));
}

TEST_CASE("MOD import, format ok, thanks to MK in header", "[ModSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::EAGLES_MOD, BinaryData::EAGLES_MODSize, false);

    // Parses.
    const ModSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "XYZ"));
}

TEST_CASE("MOD import, format ok, thanks to MK in header, mod declared", "[ModSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::ENDTHEME_MOD, BinaryData::ENDTHEME_MODSize, false);

    // Parses.
    const ModSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mod"));
}

TEST_CASE("MOD import, format ok, thanks to MK in header, endtheme", "[ModSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::ENDTHEME_MOD, BinaryData::ENDTHEME_MODSize, false);

    // Parses.
    const ModSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "MOD"));
}

TEST_CASE("MOD import, Endtheme music", "[ModSongImporter]")
{
    juce::MemoryInputStream inputStream(BinaryData::ENDTHEME_MOD, BinaryData::ENDTHEME_MODSize, false);

    // Parses.
    ModSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mod"));
    inputStream.setPosition(0);

    ModConfiguration modConfiguration(false,
                                      { },
                                      { 0, 1, 2 } );
    ImportConfiguration importConfiguration(&modConfiguration);
    auto result = importer.loadSong(inputStream, importConfiguration);

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);
}

TEST_CASE("MOD import, Castle Master music, 2 PSGs", "[ModSongImporter]")
{
    juce::MemoryInputStream inputStream(BinaryData::Castle_Master_mod, BinaryData::Castle_Master_modSize, false);

    // Parses.
    ModSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mod"));
    inputStream.setPosition(0);

    ModConfiguration modConfiguration(false,
                                      { },
                                      { 0, 1, 2, 3 } );
    ImportConfiguration importConfiguration(&modConfiguration);
    auto result = importer.loadSong(inputStream, importConfiguration);

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "castle master");
    REQUIRE(song->getSubsongCount() == 1);
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted by Arkos Tracker 3");
    const auto subsongMetadata = song->getSubsongMetadata(subsongId);
    const auto psgCount = song->getPsgCount(subsongId);
    REQUIRE(subsongMetadata.getDigiChannel() == 1);
    REQUIRE(juce::exactlyEqual(subsongMetadata.getReplayFrequencyHz(), 50.0F));
    REQUIRE(subsongMetadata.getInitialSpeed() == 6);
    REQUIRE(subsongMetadata.getName() == SubsongConstants::defaultFirstSubsongName);
    REQUIRE(psgCount == 2);
    REQUIRE(subsongMetadata.getHighlightSpacing() == 4);
    REQUIRE(subsongMetadata.getSecondaryHighlight() == 4);
    REQUIRE(subsongMetadata.getLoopStartPosition() == 0);
    REQUIRE(subsongMetadata.getEndPosition() == 51);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        const auto psgs = subsong.getPsgs();
        REQUIRE(psgs.size() == 2);
        REQUIRE(psgs.at(0) == Psg(PsgType::ay, PsgFrequency::psgFrequencyCPC, 440.0F, PsgFrequency::defaultModSamplePlayerFrequencyHz, PsgMixingOutput::ABC));
        REQUIRE(psgs.at(1) == Psg(PsgType::ay, PsgFrequency::psgFrequencyCPC, 440.0F, PsgFrequency::defaultModSamplePlayerFrequencyHz, PsgMixingOutput::ABC));

        // Checks the Patterns.
        constexpr auto expectedPatternCount = 39;
        REQUIRE(subsong.getPatternCount() == expectedPatternCount);
        for (auto patternIndex = 0; patternIndex < expectedPatternCount; ++patternIndex) {
            const auto& pattern = subsong.getPatternFromIndex(patternIndex);
            REQUIRE(pattern.getChannelCount() == 6);
            REQUIRE(pattern.getCurrentTrackIndex(0) == patternIndex * 6 + 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == patternIndex * 6 + 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == patternIndex * 6 + 2);
            REQUIRE(pattern.getCurrentTrackIndex(3) == patternIndex * 6 + 3);
            REQUIRE(pattern.getCurrentTrackIndex(4) == patternIndex * 6 + 4);
            REQUIRE(pattern.getCurrentTrackIndex(5) == patternIndex * 6 + 5);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == patternIndex);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == patternIndex);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(3).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(4).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(5).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Positions.
        REQUIRE(subsong.getLoopStartPosition() == 0);
        REQUIRE(subsong.getEndPosition() == 51);
        REQUIRE(subsong.getLength() == 52);
        {
            auto positionIndex = 0;
            for (auto patternIndex : { 4, 0, 1, 2, 3, 3, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 12, 13, 14, 15,
                                       13, 13, 16, 17, 18, 19, 15, 14, 13, 21, 22, 23, 24, 14, 13, 25, 26, 27, 28, 29, 29,
                                       30, 31, 32, 31, 32, 33, 34, 35, 36, 37, 38 }) {
                const auto& position = subsong.getPosition(positionIndex);
                REQUIRE(position.getPatternIndex() == patternIndex);
                auto height = (positionIndex < 0x26 ? 0x40 : 0x30);
                if (positionIndex == 0x29) {
                    height = 0x18;
                } else if (positionIndex == 0x33) {
                    height = 48;
                }
                REQUIRE(position.getHeight() == height);
                REQUIRE(position.getTransposition(0) == 0);
                REQUIRE(position.getTransposition(1) == 0);
                REQUIRE(position.getTransposition(2) == 0);
                REQUIRE(position.getTransposition(3) == 0);
                REQUIRE(position.getTransposition(4) == 0);
                REQUIRE(position.getTransposition(5) == 0);
                REQUIRE(position.getMarkerName() == ((positionIndex == 0) ? Position::firstMarkerName : ""));
                ++positionIndex;
            }
        }
    });

    // Checks the Instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE(instruments.size() == 32);
    });
}

TEST_CASE("MOD import, Transformer music", "[ModSongImporter]")
{
    juce::MemoryInputStream inputStream(BinaryData::transformer_mod, BinaryData::transformer_modSize, false);

    // Parses.
    ModSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "mod"));
    inputStream.setPosition(0);

    ModConfiguration modConfiguration(false,
                                      { },
                                      { 0, 1, 2 } );
    ImportConfiguration importConfiguration(&modConfiguration);
    auto result = importer.loadSong(inputStream, importConfiguration);

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "transformer");
    REQUIRE(song->getSubsongCount() == 1);
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted by Arkos Tracker 3");
    const auto subsongMetadata = song->getSubsongMetadata(subsongId);
    const auto psgCount = song->getPsgCount(subsongId);
    REQUIRE(subsongMetadata.getDigiChannel() == 1);
    REQUIRE(juce::exactlyEqual(subsongMetadata.getReplayFrequencyHz(), 50.0F));
    REQUIRE(subsongMetadata.getInitialSpeed() == 6);
    REQUIRE(subsongMetadata.getName() == SubsongConstants::defaultFirstSubsongName);
    REQUIRE(psgCount == 1);
    REQUIRE(subsongMetadata.getHighlightSpacing() == 4);
    REQUIRE(subsongMetadata.getSecondaryHighlight() == 4);
    REQUIRE(subsongMetadata.getLoopStartPosition() == 0);
    REQUIRE(subsongMetadata.getEndPosition() == 19);

    // Checks the Subsong.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        const auto psgs = subsong.getPsgs();
        REQUIRE(psgs.size() == 1);
        REQUIRE(psgs.at(0) == Psg(PsgType::ay, PsgFrequency::psgFrequencyCPC, 440.0F,
            PsgFrequency::defaultModSamplePlayerFrequencyHz, PsgMixingOutput::ABC));

        // Checks the Patterns.
        REQUIRE(subsong.getPatternCount() == 9);
        for (auto patternIndex = 0; patternIndex < 9; ++patternIndex) {
            const auto& pattern = subsong.getPatternFromIndex(patternIndex);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == patternIndex * 3 + 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == patternIndex * 3 + 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == patternIndex * 3 + 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == patternIndex);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == patternIndex);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Positions.
        REQUIRE(subsong.getLoopStartPosition() == 0);
        REQUIRE(subsong.getEndPosition() == 0x13);
        REQUIRE(subsong.getLength() == 0x14);
        {
            auto positionIndex = 0;
            for (auto patternIndex : { 3, 2, 4, 1, 1, 5, 5, 0, 0, 1, 1, 2, 5, 5, 7, 6, 1, 1, 0, 8 }) {
                const auto& position = subsong.getPosition(positionIndex);
                REQUIRE(position.getPatternIndex() == patternIndex);
                REQUIRE(position.getHeight() == 0x40);
                REQUIRE(position.getTransposition(0) == 0);
                REQUIRE(position.getTransposition(1) == 0);
                REQUIRE(position.getTransposition(2) == 0);
                ++positionIndex;
            }
        }

        // Checks some Tracks.
        {
            // Position 0, channel 0.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(0);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell::build(TrackTestHelper::noteC5, 7, CellEffects({{ Effect::volume, 0x3 }})) },
                    { 0x1, Cell(CellEffects({{ Effect::volume, 0x5 }})) },
                    { 0x2, Cell(CellEffects({{ Effect::volume, 0x6 }})) },
                    { 0x3, Cell(CellEffects({{ Effect::volume, 0x8 }})) },
                    { 0x4, Cell(CellEffects({{ Effect::volume, 0xa }})) },
                    { 0x6, Cell(CellEffects({{ Effect::volume, 0xb }})) },
                    { 0x8, Cell(CellEffects({{ Effect::volume, 0xc }})) },
                    { 0x9, Cell(CellEffects({{ Effect::volume, 0xd }})) },
                    { 0xe, Cell(CellEffects({{ Effect::volume, 0xe }})) },
                    { 0x12, Cell(CellEffects({{ Effect::volume, 0xf }})) },

                    { 0x30, Cell(CellEffects({{ Effect::fastPitchUp, 0xe }})) },
                    { 0x31, Cell(CellEffects({{ Effect::fastPitchUp, 0x1c }})) },
                    { 0x32, Cell(CellEffects({{ Effect::fastPitchUp, 0x2a }})) },
                    { 0x33, Cell(CellEffects({{ Effect::fastPitchUp, 0x38 }})) },
                    { 0x34, Cell(CellEffects({{ Effect::fastPitchUp, 0x46 }})) },
                    { 0x35, Cell(CellEffects({{ Effect::fastPitchUp, 0x54 }})) },
                    { 0x36, Cell(CellEffects({{ Effect::fastPitchUp, 0x62 }})) },
                    { 0x37, Cell(CellEffects({{ Effect::fastPitchUp, 0x70 }})) },
                    { 0x38, Cell(CellEffects({{ Effect::fastPitchUp, 0x7e }})) },
                    { 0x39, Cell(CellEffects({{ Effect::fastPitchUp, 0x8c }})) },
                    { 0x3a, Cell(CellEffects({{ Effect::fastPitchUp, 0x9a }})) },
                    { 0x3b, Cell(CellEffects({{ Effect::fastPitchUp, 0xa8 }})) },
                    { 0x3c, Cell(CellEffects({{ Effect::fastPitchUp, 0xb6 }})) },
                    { 0x3d, Cell(CellEffects({{ Effect::fastPitchUp, 0xc4 }})) },
                    { 0x3e, Cell(CellEffects({{ Effect::fastPitchUp, 0xd2 }})) },
            });
            REQUIRE(success);
        }
        {
            // Position 0, channel 1.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(1);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            REQUIRE(track.isEmpty());
        }
        {
            // Position 0, channel 2.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(2);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            REQUIRE(track.isEmpty());
        }
    });

    // Checks the Instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE(instruments.size() == 16);

        {
            // Instrument 1.
            const auto& instrument = instruments.at(1);
            REQUIRE(instrument->getName() == "st-78:trans-major");
            REQUIRE(instrument->getType() == InstrumentType::sampleInstrument);
            const auto& samplePart = instrument->getSamplePart();
            const auto loop = samplePart.getLoop();
            REQUIRE_FALSE(loop.isLooping());
            REQUIRE(loop.getStartIndex() == 0);
            REQUIRE(loop.getEndIndex() == 15053);
            REQUIRE(loop.getLength() == 15054);
        }
        {
            // Instrument 7.
            const auto& instrument = instruments.at(7);
            REQUIRE(instrument->getName() == "st-78:trans-machine");
            REQUIRE(instrument->getType() == InstrumentType::sampleInstrument);
            const auto& samplePart = instrument->getSamplePart();
            const auto loop = samplePart.getLoop();
            REQUIRE(loop.isLooping());
            REQUIRE(loop.getStartIndex() == 174);       // Strange, not the same values as ModPlug...
            REQUIRE(loop.getEndIndex() == 12009);
            REQUIRE(samplePart.getSample()->getLength() == 12064);
        }
    });
}

}   // namespace arkostracker

