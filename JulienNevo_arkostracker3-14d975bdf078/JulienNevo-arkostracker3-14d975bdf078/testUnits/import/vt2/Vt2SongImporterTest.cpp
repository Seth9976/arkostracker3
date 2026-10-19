#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/import/vt2/Vt2SongImporter.h"
#include "../../../source/song/subsong/SubsongConstants.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("Vt2 import, wrong file", "[Vt2SongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::At2AllEffects_aks, BinaryData::At2AllEffects_aksSize, false);

    // Parses.
    Vt2SongImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "vt2"));
}

TEST_CASE("Vt2 import, format ok", "[Vt2SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::Simple_vt2, BinaryData::Simple_vt2Size, false);

    // Parses.
    Vt2SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "vt2"));
}

TEST_CASE("Vt2 import, simple music, parse ok", "[Vt2SongImporter]")
{
    juce::MemoryInputStream inputStream(BinaryData::Simple_vt2, BinaryData::Simple_vt2Size, false);

    // Parses.
    Vt2SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "vt2"));
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

TEST_CASE("Vt2 import, demosong, parse ok", "[Vt2SongImporter]")
{
    juce::MemoryInputStream inputStream(BinaryData::_2018_EA_demosong_vt2, BinaryData::_2018_EA_demosong_vt2Size, false);

    // Parses.
    Vt2SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "vt2"));
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

TEST_CASE("Vt2 import, skrju music", "[Vt2SongImporter]")
{
    juce::MemoryInputStream inputStream(BinaryData::_2018_nq_skrju_demosong_vt2, BinaryData::_2018_nq_skrju_demosong_vt2Size, false);

    // Parses.
    Vt2SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "vt2"));
    inputStream.setPosition(0);
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 2);
    REQUIRE(song != nullptr);

    // Checks the Song.
    REQUIRE(song->getTitle() == "Testicool chiptune for VT2.5");
    REQUIRE(song->getSubsongCount() == 1);
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE(song->getAuthor() == "n1k-o 11.02.2018");
    REQUIRE(song->getComposer() == "n1k-o 11.02.2018");
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
    REQUIRE(subsongMetadata.getLoopStartPosition() == 2);
    REQUIRE(subsongMetadata.getEndPosition() == 5);

    // Checks the Song.
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        const auto psgs = subsong.getPsgs();
        REQUIRE(psgs.size() == 1);
        REQUIRE(psgs.at(0) == Psg(PsgType::ay, 1750000, 440.0F, 8000, PsgMixingOutput::ABC));

        // Checks the Patterns.
        REQUIRE(subsong.getPatternCount() == 5);
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
        {
            const auto& pattern = subsong.getPatternFromIndex(2);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 6);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 7);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 8);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 2);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 2);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternFromIndex(3);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 9);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 10);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 11);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 3);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 3);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternFromIndex(4);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 12);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 13);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 14);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 4);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 4);
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
            REQUIRE(position.getHeight() == 0x80);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName() == Position::firstMarkerName);
        }
        {
            const auto& position = subsong.getPosition(1);
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 0x80);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(2);
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getHeight() == 0x80);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(3);
            REQUIRE(position.getPatternIndex() == 2);
            REQUIRE(position.getHeight() == 0x80);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(4);
            REQUIRE(position.getPatternIndex() == 3);
            REQUIRE(position.getHeight() == 0x80);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPosition(5);
            REQUIRE(position.getPatternIndex() == 4);
            REQUIRE(position.getHeight() == 0x80);
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
                    { 0x0, Cell::build(TrackTestHelper::noteB3, 4, CellEffects({{ Effect::volume, 0xf }})) },
                    { 0x2, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x4, Cell::buildRst() },
                    { 0x6, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x8, Cell::build(TrackTestHelper::noteCs4, 7) },
                    { 0xa, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0xc, Cell::build(TrackTestHelper::noteD3, 1) },
                    { 0xe, Cell::build(TrackTestHelper::noteB3, 4) },

                    { 0x10, Cell::build(TrackTestHelper::noteG5, 9, CellEffects({{ Effect::arpeggioTable, 0x3 }})) },
                    { 0x12, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x14, Cell::build(TrackTestHelper::noteA3, 1) },
                    { 0x16, Cell::buildRst() },
                    { 0x18, Cell::build(TrackTestHelper::noteCs4, 7, CellEffects({{ Effect::arpeggioTable, 0x0 }})) },
                    { 0x1a, Cell::build(TrackTestHelper::noteA3, 8) },
                    { 0x1c, Cell::build(TrackTestHelper::noteG5, 9, CellEffects({{ Effect::arpeggioTable, 0x3 }})) },
                    { 0x1e, Cell::build(TrackTestHelper::noteB3, 4) },

                    { 0x20, Cell::build(TrackTestHelper::noteF2, 8) },
                    { 0x22, Cell::build(TrackTestHelper::noteB3, 4) },
                    { 0x24, Cell::buildRst() },
                    { 0x26, Cell::build(TrackTestHelper::noteF2, 8) },
                    { 0x28, Cell::build(TrackTestHelper::noteCs4, 7) },
                    { 0x2a, Cell::build(TrackTestHelper::noteB3, 4) },
                    { 0x2c, Cell::build(TrackTestHelper::noteC3, 1) },
                    { 0x2e, Cell::build(TrackTestHelper::noteB3, 4) },

                    { 0x30, Cell::build(TrackTestHelper::noteF5, 9, CellEffects({{ Effect::arpeggioTable, 0x8 }})) },
                    { 0x32, Cell::build(TrackTestHelper::noteB3, 4) },
                    { 0x34, Cell::build(TrackTestHelper::noteG3, 1) },
                    { 0x36, Cell::buildRst() },
                    { 0x38, Cell::build(TrackTestHelper::noteCs4, 7, CellEffects({{ Effect::arpeggioTable, 0x0 }})) },
                    { 0x3a, Cell::build(TrackTestHelper::noteG3, 8) },
                    { 0x3c, Cell::build(TrackTestHelper::noteF5, 9, CellEffects({{ Effect::arpeggioTable, 0x8 }})) },
                    { 0x3e, Cell::build(TrackTestHelper::noteB3, 4) },

                    { 0x40, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x42, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x44, Cell::buildRst() },
                    { 0x46, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x48, Cell::build(TrackTestHelper::noteCs4, 7) },
                    { 0x4a, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x4c, Cell::build(TrackTestHelper::noteD3, 1) },
                    { 0x4e, Cell::build(TrackTestHelper::noteB3, 4) },

                    { 0x50, Cell::build(TrackTestHelper::noteG5, 9, CellEffects({{ Effect::arpeggioTable, 0x3 }})) },
                    { 0x52, Cell::build(TrackTestHelper::noteG2, 8) },
                    { 0x54, Cell::build(TrackTestHelper::noteA3, 1) },
                    { 0x56, Cell::buildRst() },
                    { 0x58, Cell::build(TrackTestHelper::noteCs4, 7, CellEffects({{ Effect::arpeggioTable, 0x0 }})) },
                    { 0x5a, Cell::build(TrackTestHelper::noteA3, 8) },
                    { 0x5c, Cell::build(TrackTestHelper::noteG5, 9, CellEffects({{ Effect::arpeggioTable, 0x3 }})) },
                    { 0x5e, Cell::build(TrackTestHelper::noteB3, 4) },

                    { 0x60, Cell::build(TrackTestHelper::noteF2, 8) },
                    { 0x62, Cell::build(TrackTestHelper::noteB3, 4) },
                    { 0x64, Cell::buildRst() },
                    { 0x66, Cell::build(TrackTestHelper::noteF2, 8) },
                    { 0x68, Cell::build(TrackTestHelper::noteCs4, 7) },
                    { 0x6a, Cell::build(TrackTestHelper::noteB3, 4) },
                    { 0x6c, Cell::build(TrackTestHelper::noteC3, 1) },
                    { 0x6e, Cell::build(TrackTestHelper::noteB3, 4) },
                    { 0x70, Cell::build(TrackTestHelper::noteF5, 9, CellEffects({{ Effect::arpeggioTable, 0x8 }})) },
                    { 0x72, Cell::build(TrackTestHelper::noteB3, 4) },
                    { 0x74, Cell::build(TrackTestHelper::noteG3, 1) },
                    { 0x76, Cell::buildRst() },
                    { 0x78, Cell::build(TrackTestHelper::noteCs4, 7, CellEffects({{ Effect::arpeggioTable, 0x0 }})) },
            });
            REQUIRE(success);
        }
    });

    // Checks the Instruments.
    song->performOnInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE(instruments.size() == 10);

        {
            // Instrument 2.
            const auto& instrument = instruments.at(2);
            REQUIRE(instrument->getName() == "Sample 2");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0,
                                                                                                                 0, 0, -1)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }

        {
            // Instrument 4.
            const auto& instrument = instruments.at(4);
            REQUIRE(instrument->getName() == "Sample 4");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 3, false));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 7)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 0, -0x100)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 0, -0x200)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc, 0, 0, 0, -0x300)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }

        {
            // Instrument 9.
            const auto& instrument = instruments.at(9);
            REQUIRE(instrument->getName() == "Sample 9");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0x1e, false));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xe, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x9, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x9, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x7, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x7, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x7, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x6, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x6, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x6, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x5, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x5, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x5, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x4, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x4, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x4, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x3, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x3, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x3, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x2, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x2, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x2, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x1, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x1, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x1, 0)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
    });
}


}   // namespace arkostracker

