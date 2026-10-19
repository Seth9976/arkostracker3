#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/song/subsong/SubsongConstants.h"
#include "../../../source/import/wyz/WyzSongImporter.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("Wyz import, wrong file", "[WyzSongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::At2AllEffects_aks, BinaryData::At2AllEffects_aksSize, false);

    // Parses.
    const WyzSongImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "wyz"));
}

TEST_CASE("Wyz import, format ok", "[WyzSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::maryjane2_xml, BinaryData::maryjane2_xmlSize, false);

    // Parses.
    const WyzSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "wyz"));
}

static void readAndParseSong(const void* musicData, size_t musicSize)
{
    // Loads a song.
    juce::MemoryInputStream inputStream(musicData, musicSize, false);

    // Parses.
    WyzSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "wyz"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);
}

TEST_CASE("Wyz Import, parse songs ok", "[WyzSongImporter]")
{
    readAndParseSong(BinaryData::jinj_med_xml, BinaryData::jinj_med_xmlSize);
    readAndParseSong(BinaryData::pt10_xml, BinaryData::pt10_xmlSize);
    readAndParseSong(BinaryData::pt10NtscZx_xml, BinaryData::pt10NtscZx_xmlSize);
    readAndParseSong(BinaryData::shampooCpc_xml, BinaryData::shampooCpc_xmlSize);
    readAndParseSong(BinaryData::gothic_xml, BinaryData::gothic_xmlSize);
    readAndParseSong(BinaryData::gothicModified_xml, BinaryData::gothicModified_xmlSize);
    readAndParseSong(BinaryData::knightmare_start_xml, BinaryData::knightmare_start_xmlSize);
    readAndParseSong(BinaryData::midnight_xprss_xml, BinaryData::midnight_xprss_xmlSize);
    readAndParseSong(BinaryData::quezesto_xml, BinaryData::quezesto_xmlSize);
    readAndParseSong(BinaryData::RA_PSG_xml, BinaryData::RA_PSG_xmlSize);
}

TEST_CASE("Wyz Import, maryjane2 music", "[WyzSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::maryjane2_xml, BinaryData::maryjane2_xmlSize, false);

    // Parses.
    WyzSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "wyz"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "maryjane");
    REQUIRE(song->getSubsongCount() == 1);
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted by Arkos Tracker 3");
    const auto subsongMetadata = song->getSubsongMetadata(subsongId);
    const auto psgCount = song->getPsgCount(subsongId);
    REQUIRE(subsongMetadata.getDigiChannel() == 1);
    REQUIRE(juce::exactlyEqual(subsongMetadata.getReplayFrequencyHz(), 50.0F));
    REQUIRE(subsongMetadata.getInitialSpeed() == 4);
    REQUIRE(subsongMetadata.getName() == SubsongConstants::defaultFirstSubsongName);
    REQUIRE(psgCount == 1);
    REQUIRE(subsongMetadata.getHighlightSpacing() == 4);
    REQUIRE(subsongMetadata.getSecondaryHighlight() == 4);
    REQUIRE(subsongMetadata.getLoopStartPosition() == 0);
    REQUIRE(subsongMetadata.getEndPosition() == 0x10);

    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        const auto psgs = subsong.getPsgs();
        REQUIRE(psgs.size() == 1);
        REQUIRE(psgs.at(0) == Psg(PsgType::ay, PsgFrequency::psgFrequencySpectrum, 440.0F, 8000, PsgMixingOutput::ABC));

        // Checks some Patterns.
        REQUIRE(subsong.getPatternCount() == 22);
        {
            const auto& pattern = subsong.getPatternFromIndex(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternFromIndex(1);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 3);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 5);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 1);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 1);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Positions.
        {
            const auto& position = subsong.getPosition(0);
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName() == Position::firstMarkerName);
        }
        {
            const auto& position = subsong.getPosition(1);
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(2);
            REQUIRE(position.getPatternIndex() == 2);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(3);
            REQUIRE(position.getPatternIndex() == 3);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(6);
            REQUIRE(position.getPatternIndex() == 6);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(7);
            REQUIRE(position.getPatternIndex() == 8);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(0xd);
            REQUIRE(position.getPatternIndex() == 0x10);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(0xe);
            REQUIRE(position.getPatternIndex() == 0x11);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(0xf);
            REQUIRE(position.getPatternIndex() == 0x10);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(0x10);
            REQUIRE(position.getPatternIndex() == 0x14);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }

        // Checks some Tracks.
        {
            // Position 0, channel 0.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(0);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell::build(TrackTestHelper::noteC4, 8) },
                    { 0x2, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x4, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0x6, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x8, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0xa, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0xc, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0xe, Cell::build(TrackTestHelper::noteC4, 0x8) },

                    { 0x10, Cell::build(TrackTestHelper::noteD6, 0x2) },
                    { 0x12, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x14, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0x16, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x17, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x18, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x1a, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x1c, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0x1e, Cell::build(TrackTestHelper::noteC4, 0xa) },

                    { 0x20, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x22, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x24, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0x26, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x28, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x2a, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x2c, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0x2e, Cell::build(TrackTestHelper::noteC4, 0x8) },

                    { 0x30, Cell::build(TrackTestHelper::noteF6, 0x2) },
                    { 0x32, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x34, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0x36, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x37, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x38, Cell::build(TrackTestHelper::noteC4, 0x8) },
                    { 0x3a, Cell::build(TrackTestHelper::noteC4, 0xa) },
                    { 0x3c, Cell::build(TrackTestHelper::noteC4, 0x9) },
                    { 0x3e, Cell::build(TrackTestHelper::noteC4, 0xa) },
            });
            REQUIRE(success);
        }
        {
            // Position 0, channel 1.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(1);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell::build(TrackTestHelper::noteC3, 1) },
                    { 0x10, Cell::build(TrackTestHelper::noteAs2, 1) },
                    { 0x20, Cell::build(TrackTestHelper::noteA2, 1) },
                    { 0x30, Cell::build(TrackTestHelper::noteGs2, 1) },
                    { 0x38, Cell::build(TrackTestHelper::noteDs3, 1) },
            });
            REQUIRE(success);
        }
    });

    // Checks the Instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE(instruments.size() == 0xc);

        {
            // Instrument 1.
            const auto& instrument = instruments.at(1);
            REQUIRE(instrument->getName() == "Bajo");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(3, 3, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xe, 0, 0, -1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd, 0, 0, -1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc, 0, 0, -1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, -1)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            // Instrument 2.
            const auto& instrument = instruments.at(2);
            REQUIRE(instrument->getName() == "triririn");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(5, 8, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xa, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xa, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0, 0, 0)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            // Instrument 8.
            const auto& instrument = instruments.at(8);
            REQUIRE(instrument->getName() == "Fx: bass drum");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 1, false));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 0, 0, true, 0x3d1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd, 0, 0, 0, 0, true, 0xa45)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            // Instrument 9.
            const auto& instrument = instruments.at(9);
            REQUIRE(instrument->getName() == "Fx: drum");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 2, false));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd, 0, 0, 0, 0, true, 0x25d)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc, 2, 0, 0, 0, true, 0x2a2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x7, 1)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
    });
}

TEST_CASE("Wyz Import, maryjane2 modified for hard FXs", "[WyzSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::maryjane2Modified_xml, BinaryData::maryjane2Modified_xmlSize, false);

    // Parses.
    WyzSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "wyz"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "maryjane");
    REQUIRE(song->getSubsongCount() == 1);
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted by Arkos Tracker 3");
    const auto subsongMetadata = song->getSubsongMetadata(subsongId);
    const auto psgCount = song->getPsgCount(subsongId);
    REQUIRE(subsongMetadata.getDigiChannel() == 1);
    REQUIRE(juce::exactlyEqual(subsongMetadata.getReplayFrequencyHz(), 50.0F));
    REQUIRE(subsongMetadata.getInitialSpeed() == 4);
    REQUIRE(subsongMetadata.getName() == SubsongConstants::defaultFirstSubsongName);
    REQUIRE(psgCount == 1);
    REQUIRE(subsongMetadata.getHighlightSpacing() == 4);
    REQUIRE(subsongMetadata.getSecondaryHighlight() == 4);
    REQUIRE(subsongMetadata.getLoopStartPosition() == 0);
    REQUIRE(subsongMetadata.getEndPosition() == 0x10);

    // Checks the Instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE(instruments.size() == 0xc);

        {
            // Instrument 8.
            const auto& instrument = instruments.at(8);
            REQUIRE(instrument->getName() == "Fx: bass drum");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 1, false));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0x13d, 0, 0, 0, 0, 0x9, 0, 0, 0, 8, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0x108, 0, 0, 0, 0, 0x10, 0, 0, 0, 8, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
    });
}

/** Checks that the "no instrument" is well managed (= use previous instrument). */
TEST_CASE("Wyz Import, shampoo", "[WyzSongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::shampooCpc_xml, BinaryData::shampooCpc_xmlSize, false);

    // Parses.
    WyzSongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "wyz"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Canción Nueva");
    REQUIRE(song->getSubsongCount() == 1);
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE(song->getAuthor() == "");
    REQUIRE(song->getComposer() == "");
    REQUIRE(song->getComments() == "Converted by Arkos Tracker 3");
    const auto subsongMetadata = song->getSubsongMetadata(subsongId);
    const auto psgCount = song->getPsgCount(subsongId);
    REQUIRE(subsongMetadata.getDigiChannel() == 1);
    REQUIRE(juce::exactlyEqual(subsongMetadata.getReplayFrequencyHz(), 50.0F));
    REQUIRE(subsongMetadata.getInitialSpeed() == 3);
    REQUIRE(subsongMetadata.getName() == SubsongConstants::defaultFirstSubsongName);
    REQUIRE(psgCount == 1);
    REQUIRE(subsongMetadata.getHighlightSpacing() == 4);
    REQUIRE(subsongMetadata.getSecondaryHighlight() == 4);
    REQUIRE(subsongMetadata.getLoopStartPosition() == 3);
    REQUIRE(subsongMetadata.getEndPosition() == 0x13);

    // Checks the Instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE(instruments.size() == 0xc);
    });

    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        const auto psgs = subsong.getPsgs();
        REQUIRE(psgs.size() == 1);
        REQUIRE(psgs.at(0) == Psg(PsgType::ay, PsgFrequency::psgFrequencyCPC, 440.0F, 8000, PsgMixingOutput::ABC));

        // Checks some Tracks.
        {
            // Position 0, channel 2.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(2);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell::build(TrackTestHelper::noteD4, 2) },
                    { 0x1, Cell::build(TrackTestHelper::noteG4, 2) },
                    { 0x2, Cell::build(TrackTestHelper::noteA4, 2) },
                    { 0x3, Cell::build(TrackTestHelper::noteD4, 2) },
                    { 0x4, Cell::build(TrackTestHelper::noteG4, 2) },
                    { 0x5, Cell::build(TrackTestHelper::noteA4, 2) },

                    { 0x6, Cell::build(TrackTestHelper::noteD4, 3) },
                    { 0x7, Cell::build(TrackTestHelper::noteG4, 3) },
                    { 0x8, Cell::build(TrackTestHelper::noteA4, 3) },
                    { 0x9, Cell::build(TrackTestHelper::noteD4, 3) },
                    { 0xa, Cell::build(TrackTestHelper::noteG4, 3) },
                    { 0xb, Cell::build(TrackTestHelper::noteA4, 3) },

                    { 0xc, Cell::build(TrackTestHelper::noteD4, 6) },
                    { 0xd, Cell::build(TrackTestHelper::noteG4, 6) },
                    { 0xe, Cell::build(TrackTestHelper::noteA4, 6) },
                    { 0xf, Cell::build(TrackTestHelper::noteD4, 6) },
                    { 0x10, Cell::build(TrackTestHelper::noteG4, 6) },
                    { 0x11, Cell::build(TrackTestHelper::noteA4, 6) },
                    { 0x12, Cell::build(TrackTestHelper::noteD4, 6) },
                    { 0x13, Cell::build(TrackTestHelper::noteG4, 6) },
                    { 0x14, Cell::build(TrackTestHelper::noteA4, 6) },
            });
            REQUIRE(success);
        }
    });
}

}   // namespace arkostracker

