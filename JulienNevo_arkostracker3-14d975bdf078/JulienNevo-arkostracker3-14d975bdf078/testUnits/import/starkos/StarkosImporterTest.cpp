#include "../../catch.hpp"

#include <BinaryData.h>

#include "../../../source/import/starkos/StarkosImporter.h"
#include "../../../source/song/instrument/psg/PsgPartConstants.h"
#include "../../../source/song/subsong/SubsongConstants.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker
{

TEST_CASE("Starkos import, wrong file", "[StarkosImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::Kangaroo__Alienall_128, BinaryData::Kangaroo__Alienall_128Size, false);

    // Parses.
    const StarkosImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "sks"));
}

TEST_CASE("Starkos import, right file, DIA end part", "[StarkosImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__DemoIzArt__End_Part_sks, BinaryData::Targhan__DemoIzArt__End_Part_sksSize, false);

    // Parses.
    StarkosImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "sks"));

    auto result = importer.loadSong(inputStream, ImportConfiguration());
    const auto& song = result->song;
    REQUIRE(song != nullptr);
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());
    REQUIRE(result->errorReport->getWarningCount() == 0);

    // Checks the first instrument, hard to soft.
    song->performOnConstPsgInstrument(song->getInstrumentId(1).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(psgPart.getLength() == 25);
        REQUIRE(psgPart.getSpeed() == 2);
        REQUIRE(psgPart.getMainLoop() == Loop(0x17, 0x18, true));
        // Cell 0. Hard to soft.
        {
            const auto& cell = psgPart.getCellRefConst(0);
            REQUIRE(cell.getPrimaryPeriod() == 0);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::hardToSoft);
            REQUIRE(cell.getRatio() == 5);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getHardwareEnvelope() == 0xc);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 5);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == 0);
            REQUIRE(cell.getSecondaryArpeggioOctave() == 0);
            REQUIRE(cell.getSecondaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getSecondaryPitch() == 0);
            REQUIRE_FALSE(cell.isRetrig());
        }
        // Cell 1. Soft.
        {
            const auto& cell = psgPart.getCellRefConst(1);
            REQUIRE(cell.getPrimaryPeriod() == 0);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 15);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == 0);
            REQUIRE(cell.getSecondaryArpeggioOctave() == 0);
            REQUIRE(cell.getSecondaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getSecondaryPitch() == 0);
            REQUIRE_FALSE(cell.isRetrig());
        }
    });
}

TEST_CASE("Starkos import, Carpet", "[StarkosImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__Midline_Process__Carpet_sks, BinaryData::Targhan__Midline_Process__Carpet_sksSize, false);

    // Parses.
    StarkosImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "sks"));

    auto result = importer.loadSong(inputStream, ImportConfiguration());
    const auto& song = result->song;
    REQUIRE(song != nullptr);
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());
    REQUIRE(result->errorReport->getWarningCount() == 0);

    // Checks the Hard To Soft with soft pitch.
    song->performOnConstInstrumentFromIndex(0x2f, [&](const Instrument& instrument) {
        const auto& psgPart = instrument.getConstPsgPart();
        REQUIRE(psgPart.getLength() == 1);
        REQUIRE(psgPart.getMainLoopRef() == Loop(0, 0, true));
        const auto& cell = psgPart.getCellRefConst(0);
        REQUIRE(cell.getLink() == PsgInstrumentCellLink::hardToSoft);
        REQUIRE(cell.getHardwareEnvelope() == 0xa);
        REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
        REQUIRE(cell.getPrimaryArpeggioOctave() == 5);
        REQUIRE(cell.getSecondaryArpeggioNoteInOctave() == 0);
        REQUIRE(cell.getSecondaryArpeggioOctave() == 0);
        REQUIRE(cell.getNoise() == 0);
        REQUIRE(cell.getPrimaryPeriod() == 0);
        REQUIRE(cell.getPrimaryPitch() == 0);
        REQUIRE(cell.getSecondaryPeriod() == 0);
        REQUIRE(cell.getSecondaryPitch() == 1);
    });

    // Checks some tracks.
    // Checks the Track 1, volume shouldn't be encoded every time.
    song->performOnConstSubsong(song->getFirstSubsongId(), [&](const Subsong& subsong) {
        const auto patternIndex = subsong.getPosition(1).getPatternIndex();
        const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(0);
        const auto& track = subsong.getTrackRefFromIndex(trackIndex);
        const auto success = TrackTestHelper::containsOnly(track, {
                { 0xa, Cell::build(12 * 4 + 4, 3, CellEffects({{ Effect::volume, 0x9 }})) },
                { 0xe, Cell::build(12 * 4 + 4, 2) },
                { 0x14, Cell::build(12 * 4 + 4, 3, CellEffects({{ Effect::volume, 0xa }})) },
                { 0x18, Cell::build(12 * 4 + 4, 2) },
                { 0x1e, Cell::build(12 * 4 + 4, 3) },
                { 0x22, Cell::build(12 * 4 + 4, 2) },
                { 0x2a, Cell::build(12 * 4 + 4, 4) },
                { 0x2e, Cell::build(12 * 4 + 4, 5, CellEffects({{ Effect::volume, 0xb }})) },
                { 0x34, Cell::build(12 * 4 + 4, 4) },
                { 0x38, Cell::build(12 * 4 + 4, 5) },
                { 0x3e, Cell::build(12 * 4 + 4, 4, CellEffects({{ Effect::volume, 0xc }})) },
                // Out of bounds.
                { 0x42, Cell::build(12 * 4 + 4, 5, CellEffects({{ Effect::volume, 0xb }})) },
                { 0x44, Cell::build(12 * 4 + 4, 1, CellEffects({{ Effect::volume, 0xc }})) },
        });
        REQUIRE(success);
    });

    // Tests the track with pitches up/down.
    // Checks the Track 0x52, pitch shouldn't be encoded every time.
    song->performOnConstSubsong(song->getFirstSubsongId(), [&](const Subsong& subsong) {
        const auto patternIndex = subsong.getPosition(5).getPatternIndex();
        const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(0);
        const auto& track = subsong.getTrackRefFromIndex(trackIndex);
        const auto success = TrackTestHelper::containsOnly(track, {
                { 0x0, Cell::build(12 * 1 + 4, 7) },
                { 0x18, Cell::build(12 * 1 + 11, 7) },
                { 0x1d, Cell(CellEffects({{ Effect::fastPitchUp, 0xb0 }} )) },
                { 0x20, Cell::build(12 * 2 + 4, 7) },
                { 0x3d, Cell(CellEffects({{ Effect::fastPitchDown, 0x280 }} )) },
        });
        REQUIRE(success);
    });

}

static void checkTrack1(const Track& track)
{
    REQUIRE(TrackTestHelper::containsOnly(track, {
            { 0x10, Cell(Note::buildNote(12 * 4 + 4), 2) },
            { 0x20, Cell(Note::buildRst(), 0) },
    }));
}

TEST_CASE("Starkos import, right file, Molusk", "[StarkosImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::Targhan__Midline_Process__Molusk_sks, BinaryData::Targhan__Midline_Process__Molusk_sksSize, false);

    // Parses.
    StarkosImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "sks"));

    auto result = importer.loadSong(inputStream, ImportConfiguration());
    REQUIRE(result->song != nullptr);
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());
    REQUIRE(result->errorReport->getWarningCount() == 0);
}

TEST_CASE("Starkos import, full song", "[StarkosImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::StarkosAll_sks, BinaryData::StarkosAll_sksSize, false);

    // Parses.
    StarkosImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "sks"));

    auto result = importer.loadSong(inputStream, ImportConfiguration());
    const auto& song = result->song;
    const auto subsongId = song->getFirstSubsongId();

    REQUIRE(song != nullptr);
    REQUIRE(result->errorReport != nullptr);
    REQUIRE(result->errorReport->isOk());
    REQUIRE(result->errorReport->getWarningCount() == 0);
    REQUIRE(song->getSubsongCount() == 1);
    REQUIRE(song->getChannelCount(subsongId) == 3);
    REQUIRE(song->getInstrumentCount() == 7);

    // Checks the instruments
    // ---------------------------------------------
    // Instrument 0 (empty).
    song->performOnConstPsgInstrument(song->getInstrumentId(0).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "Empty");
        REQUIRE(psgPart.getLength() == 1);
        REQUIRE_FALSE(psgPart.isInstrumentRetrig());
        REQUIRE(psgPart.getSpeed() == PsgPartConstants::slowestSpeed);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
        // Cell 0.
        {
            const auto& cell = psgPart.getCellRefConst(0);
            REQUIRE(cell.getPrimaryPeriod() == 0);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::noSoftNoHard);
            REQUIRE(cell.getVolume() == 0);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == 0);
            REQUIRE(cell.getSecondaryArpeggioOctave() == 0);
            REQUIRE(cell.getSecondaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getSecondaryPitch() == 0);
            REQUIRE_FALSE(cell.isRetrig());
        }
    });
    song->performOnConstPsgInstrument(song->getInstrumentId(1).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "FIRST");
        REQUIRE(psgPart.getSpeed() == 0);
        REQUIRE(psgPart.getMainLoop() == Loop(0x0, 0xe, false));
        REQUIRE_FALSE(psgPart.isInstrumentRetrig());
        auto index = 0;
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(14, 1));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(13, 0xe));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(12, 0x1f));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(11));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(10));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(9));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(8));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(7));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(6));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(5));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(4));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(3));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(2));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(1));
        REQUIRE(psgPart.getLength() == index);
    });
    song->performOnConstPsgInstrument(song->getInstrumentId(2).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "SOFT");
        REQUIRE(psgPart.getSpeed() == 6);
        REQUIRE(psgPart.getMainLoop() == Loop(0x4, 0x6, true));
        REQUIRE_FALSE(psgPart.isInstrumentRetrig());
        auto index = 0;
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 0, 0, 0, -7));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 15, 0, 0x123, 0, 0, 0, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent,
            PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 0, 3));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 0, 7));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 0, 0, -1));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 0, 0, 0, 3));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 0, 0, 0, -3));
        REQUIRE(psgPart.getLength() == index);
    });
    song->performOnConstPsgInstrument(song->getInstrumentId(3).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "HARD");
        REQUIRE(psgPart.getSpeed() == 0x10);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 0xe, true));
        REQUIRE_FALSE(psgPart.isInstrumentRetrig());
        auto index = 0;
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0x1f, 0, 0, 1, 0, 4, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0x1f, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0x1f, 0, 0, 0, 0x16, 4, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0x35, 4, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0xc, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0xc, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0xc, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0xc, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0xe, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getLength() == index);
    });
    song->performOnConstPsgInstrument(song->getInstrumentId(4).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "SNA");
        REQUIRE(psgPart.getSpeed() == 0);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 0x4, false));
        REQUIRE_FALSE(psgPart.isInstrumentRetrig());
        auto index = 0;
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 1, 0, 0, 0, false));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(15, 2, 0, 0, 0, false));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(14, 4, 0, 0, 0, false));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(13, 7, 0, 0, 0, false));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(12, 0x1f, 0, 0, 0, false));
        REQUIRE(psgPart.getLength() == index);
    });
    song->performOnConstPsgInstrument(song->getInstrumentId(5).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "HARDER");
        REQUIRE(psgPart.getSpeed() == 0x21);
        REQUIRE(psgPart.getMainLoop() == Loop(2, 5, true));
        REQUIRE_FALSE(psgPart.isInstrumentRetrig());
        auto index = 0;
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::hardOnly, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0x200, 0, 0, 0, 4, 0x400, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 0, 0, 0, 0, 4, 0x3, 0, 0, 0, 0xa, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::hardOnly, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x18, 8, false, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        REQUIRE(psgPart.getLength() == index);
    });
    song->performOnConstPsgInstrument(song->getInstrumentId(6).getValue(), [](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "");
        REQUIRE(psgPart.getSpeed() == 0);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 1, true));
        REQUIRE_FALSE(psgPart.isInstrumentRetrig());
        auto index = 0;
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(13, 0));
        REQUIRE(psgPart.getCellRefConst(index++) == PsgInstrumentCell::buildSoftwareCell(13, 0, 11, -1));
        REQUIRE(psgPart.getLength() == index);
    });

    // Checks the Expressions. There are only the empty ones.
    // ---------------------------------------------
    {
        const auto& handler = song->getConstExpressionHandler(true);
        REQUIRE(handler.getCount() == 1);
        auto expression = handler.getExpressionCopy(handler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getValue(0) == 0);
    }
    {
        const auto& handler = song->getConstExpressionHandler(false);
        REQUIRE(handler.getCount() == 1);
        auto expression = handler.getExpressionCopy(handler.find(0).getValue());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getLength() == 1);
        REQUIRE(expression.getShift() == 0);
        REQUIRE(expression.getLoop() == Loop(0, 0, true));
        REQUIRE(expression.getValue(0) == 0);
    }

    // Checks the Subsong.
    // ---------------------------------------------
    song->performOnConstSubsong(subsongId, [](const Subsong& subsong) {
        REQUIRE(subsong.getChannelCount() == 3);
        REQUIRE(subsong.getName() == SubsongConstants::defaultFirstSubsongName);
        REQUIRE(subsong.getLength() == 3);
        REQUIRE(subsong.getLoopStartPosition() == 0);
        REQUIRE(subsong.getEndPosition() == 2);
        REQUIRE(juce::exactlyEqual(subsong.getReplayFrequencyHz(), PsgFrequency::defaultReplayFrequencyHz));
        const auto& psgs = subsong.getPsgRefs();
        REQUIRE(psgs.size() == 1);
        REQUIRE(psgs.at(0).getType() == PsgType::ay);
        REQUIRE(psgs.at(0).getPsgFrequency() == PsgFrequency::psgFrequencyCPC);
        REQUIRE(psgs.at(0).getPsgMixingOutput() == PsgMixingOutput::ABC);
        REQUIRE(juce::exactlyEqual(psgs.at(0).getReferenceFrequency(), PsgFrequency::defaultReferenceFrequencyHz));
        REQUIRE(psgs.at(0).getSamplePlayerFrequency() == PsgFrequency::defaultSamplePlayerFrequencyHz);

        // Checks the Linker.
        // ---------------------------------------------
        {
            const auto& position = subsong.getPositionRef(0);
            REQUIRE(position.getHeight() == 0x23);
            REQUIRE(position.getPatternIndex() == 0);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName() == Position::firstMarkerName);

        }
        {
            const auto& position = subsong.getPositionRef(1);
            REQUIRE(position.getHeight() == 0x40);
            REQUIRE(position.getPatternIndex() == 1);
            REQUIRE(position.getTransposition(0) == 1);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName().isEmpty());
        }
        {
            const auto& position = subsong.getPositionRef(2);
            REQUIRE(position.getHeight() == 0x21);
            REQUIRE(position.getPatternIndex() == 2);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 2);
            REQUIRE(position.getTransposition(2) == 1);
            REQUIRE(position.getMarkerName().isEmpty());
        }

        // Checks the Patterns.
        // ---------------------------------------------
        REQUIRE(subsong.getPatternCount() == 3);
        {
            const auto& pattern = subsong.getPatternRef(0);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 2);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(1);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 1);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 7);     // New duplication after all the Tracks.
            REQUIRE(pattern.getCurrentTrackIndex(1) == 8);     // Same one, duplicated.
            REQUIRE(pattern.getCurrentTrackIndex(2) == 3);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }
        {
            const auto& pattern = subsong.getPatternRef(2);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 2);       // Duplication of 0.
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 2);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 5);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 6);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
        }

        // Checks the Event Tracks.
        // ---------------------------------------------
        REQUIRE(subsong.getSpecialTrackCount(false) == 3);
        REQUIRE(subsong.getSpecialTrackRefFromIndex(0, false).isEmpty());
        REQUIRE(subsong.getSpecialTrackRefFromIndex(1, false).isEmpty());
        REQUIRE(subsong.getSpecialTrackRefFromIndex(2, false).isEmpty());

        // Checks the Speed Tracks.
        // ---------------------------------------------
        REQUIRE(subsong.getSpecialTrackCount(true) == 3);
        REQUIRE(subsong.getSpecialTrackRefFromIndex(0, true).isEmpty());
        {
            const auto& speedTrack = subsong.getSpecialTrackRefFromIndex(1, true);
            REQUIRE(TrackTestHelper::containsOnly(speedTrack, { { 0, 9 }, }));
        }
        REQUIRE(subsong.getSpecialTrackRefFromIndex(2, true).isEmpty());

        // Checks the Tracks.
        // ---------------------------------------------
        {
            const auto& track = subsong.getTrackRefFromIndex(0);
            REQUIRE(TrackTestHelper::containsOnly(track, {
                { 0, Cell(Note::buildNote(12 * 3 + 0), 1, CellEffects({{ Effect::volume, 15 }})) },
                { 2, Cell(Note::buildNote(12 * 3 + 2), 1, CellEffects({{ Effect::volume, 14 }})) },
                { 4, Cell(Note::buildNote(12 * 3 + 4), 1, CellEffects({{ Effect::volume, 13 }})) },
                { 6, Cell(Note::buildNote(12 * 3 + 5), 1, CellEffects({{ Effect::volume, 1 }})) },
                { 8, Cell(Note::buildNote(12 * 3 + 7), 1, CellEffects({{ Effect::volume, 0 }})) },
                { 10, Cell(Note::buildNote(12 * 3 + 9), 1, CellEffects({{ Effect::volume, 15 }})) },
                { 12, Cell(Note::buildNote(12 * 3 + 11), 1) },
                { 14, Cell(Note::buildNote(12 * 4 + 0), 1) },
                { 15, Cell(Note::buildNote(12 * 4 + 0), 1) },
            }));
        }
        {
            const auto& track = subsong.getTrackRefFromIndex(1);
            checkTrack1(track);
        }
        {
            const auto& track = subsong.getTrackRefFromIndex(2);
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0x6, Cell(Note::buildNote(12 * 5 + 7), 6, CellEffects({{ Effect::volume, 0xc }})) },
                    { 0x7, Cell(CellEffects({{ Effect::fastPitchUp, 0x8 }})) },
                    { 0x8, Cell(CellEffects({{ Effect::fastPitchUp, 0x10 }})) },
                    { 0xb, Cell(CellEffects({{ Effect::fastPitchDown, 0x10 }})) },
                    { 0xe, Cell(CellEffects({{ Effect::fastPitchDown, 0x0 }})) },     // Pitch stop generated.
                    { 0x11, Cell(Note::buildRst(), 0) },
            }));
        }

        {
            const auto& track = subsong.getTrackRefFromIndex(3);
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell(Note::buildNote(12 * 2), 3) },
            }));
        }

        {
            const auto& track = subsong.getTrackRefFromIndex(4);
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell(Note::buildNote(12 * 5), 4) },
                    { 0x4, Cell(Note::buildNote(12 * 5), 4) },
                    { 0x8, Cell(Note::buildNote(12 * 5), 4) },
                    { 0xb, Cell(Note::buildNote(12 * 5), 4) },
                    { 0x15, Cell(Note::buildNote(12 * 5), 4) },
            }));
        }

        {
            const auto& track = subsong.getTrackRefFromIndex(5);
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0x2, Cell(Note::buildNote(12 * 5 + 7), 1) },
                    { 0x6, Cell(Note::buildNote(12 * 5 + 7), 1) },
                    { 0x7, Cell(Note::buildNote(12 * 5 + 9), 1) },
                    { 0xd, Cell(Note::buildNote(12 * 5 + 11), 1) },
                    { 0x10, Cell(Note::buildNote(12 * 6 + 0), 1) },
            }));
        }

        {
            const auto& track = subsong.getTrackRefFromIndex(6);
            REQUIRE(TrackTestHelper::containsOnly(track, {
                    { 0x0, Cell(Note::buildNote(12 * 5 + 9), 5) },
            }));
        }

        {
            const auto& track = subsong.getTrackRefFromIndex(7);                // Duplicate from 1.
            checkTrack1(track);
        }
        {
            const auto& track = subsong.getTrackRefFromIndex(8);                // Duplicate from 1.
            checkTrack1(track);
        }
    });
}

TEST_CASE("Song import, twist, with amsdos header", "[StarkosImporter]")
{
    // Loads the song.
    juce::MemoryInputStream inputStream(BinaryData::TwistWithHeader_sks, BinaryData::TwistWithHeader_sksSize, false);

    // Parses.
    StarkosImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "sks"));
    auto result = importer.loadSong(inputStream, ImportConfiguration());

    REQUIRE(result != nullptr);
    auto& song = result->song;
    auto& report = result->errorReport;
    REQUIRE(report != nullptr);
    REQUIRE(report->isOk());
    REQUIRE(report->getWarningCount() == 0);
    REQUIRE(song != nullptr);

    REQUIRE(song->getTitle() == "Untitled");
}

}   // namespace arkostracker
