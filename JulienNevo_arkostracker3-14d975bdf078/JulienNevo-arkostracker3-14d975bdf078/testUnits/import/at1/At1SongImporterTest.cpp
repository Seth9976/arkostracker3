#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/song/subsong/SubsongConstants.h"
#include "../../../source/import/at1/At1SongImporter.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker 
{

TEST_CASE("AT1 Import, wrong file", "[At1SongImporter]")
{
    // Loads a wrong song.
    juce::MemoryInputStream inputStream(BinaryData::At2AllEffects_aks, BinaryData::At2AllEffects_aksSize, false);

    // Parses.
    const At1SongImporter importer;
    REQUIRE_FALSE(importer.doesFormatMatch(inputStream, "aks"));
}

TEST_CASE("AT1 Import, format ok, new", "[At1SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At1SongDemo_xml, BinaryData::At1SongDemo_xmlSize, false);

    // Parses.
    const At1SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
}

TEST_CASE("AT1 Import, format ok, old", "[At1SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At1SongTJOutro_xml, BinaryData::At1SongTJOutro_xmlSize, false);

    // Parses.
    const At1SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
}

TEST_CASE("AT1 Import, test music", "[At1SongImporter]")
{
    // Loads a song.
    juce::MemoryInputStream inputStream(BinaryData::At1SongDemo_xml, BinaryData::At1SongDemo_xmlSize, false);

    // Parses.
    At1SongImporter importer;
    REQUIRE(importer.doesFormatMatch(inputStream, "aks"));
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
    REQUIRE(song->getTitle() == "Demo");
    REQUIRE(song->getSubsongCount() == 1);
    const auto subsongId = song->getFirstSubsongId();
    REQUIRE(song->getAuthor() == "Targhan");
    REQUIRE(song->getComposer() == "Targhan");
    REQUIRE(song->getComments() == "Some fun with Arkos Tracker");
    const auto subsongMetadata = song->getSubsongMetadata(subsongId);
    const auto psgCount = song->getPsgCount(subsongId);
    REQUIRE(subsongMetadata.getDigiChannel() == 1);
    REQUIRE(juce::exactlyEqual(subsongMetadata.getReplayFrequencyHz(), 50.0F));
    REQUIRE(subsongMetadata.getInitialSpeed() == 6);
    REQUIRE(subsongMetadata.getName() == SubsongConstants::defaultFirstSubsongName);
    REQUIRE(psgCount == 1);
    REQUIRE(subsongMetadata.getHighlightSpacing() == 8);
    REQUIRE(subsongMetadata.getSecondaryHighlight() == 4);
    REQUIRE(subsongMetadata.getLoopStartPosition() == 0);
    REQUIRE(subsongMetadata.getEndPosition() == 0x12);
    song->performOnConstSubsong(subsongId, [&](const Subsong& subsong) {
        const auto psgs = subsong.getPsgs();
        REQUIRE(psgs.size() == 1U);
        REQUIRE(psgs.at(0U) == Psg(PsgType::ay, 1000000,
            440.0F, 8000, PsgMixingOutput::ABC));

        // Checks the patterns.
        {
            auto positionIndex = 0;
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 1);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 2);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 3);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 4);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 5);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 6);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 7);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 7);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 8);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 9);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xa);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xb);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xc);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xc);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xd);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xe);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xe);
            REQUIRE(subsong.getPosition(positionIndex++).getPatternIndex() == 0xe);
            REQUIRE(subsong.getLength() == positionIndex);

            REQUIRE(subsong.getPatterns().size() == 15U);
            REQUIRE(subsong.getTrackCount() == 15 * 3);

            positionIndex = 0;
            REQUIRE(subsong.getPosition(positionIndex).getHeight() == 0x18);
            REQUIRE(subsong.getPosition(positionIndex++).getMarkerName() == Position::firstMarkerName);

            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x18);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x40);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x10);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x10);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x40);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex++).getHeight() == 0x20);
            REQUIRE(subsong.getPosition(positionIndex).getHeight() == 0x20);
        }

        // Checks the Tracks.
        {
            // Position 0, channel 0.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(0);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 0, Cell::build(TrackTestHelper::noteC4, 1, CellEffects({{ Effect::volume, 0xf }})) },     // NOLINT(clion-misra-cpp2008-5-2-4)
                    { 3, Cell::build(TrackTestHelper::noteC4, 1) },
                    { 6, Cell::build(TrackTestHelper::noteC4, 1) },
                    { 9, Cell::build(TrackTestHelper::noteC4, 1) },
                    { 0xc, Cell::build(TrackTestHelper::noteC4, 1) },
                    { 0xf, Cell::build(TrackTestHelper::noteC4, 1) },
                    { 0x12, Cell::build(TrackTestHelper::noteC4, 1) },
                    { 0x15, Cell::build(TrackTestHelper::noteC4, 1) },
            });
            REQUIRE(success);
        }
        {
            // Position 0, channel 1.
            const auto patternIndex = subsong.getPosition(0).getPatternIndex();
            const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(1);
            const auto& track = subsong.getTrackRefFromIndex(trackIndex);
            const auto success = TrackTestHelper::containsOnly(track, {
                    { 1, Cell::build(TrackTestHelper::noteD4, 1, CellEffects({{ Effect::volume, 0xf }})) },     // NOLINT(clion-misra-cpp2008-5-2-4)
                    { 4, Cell::build(TrackTestHelper::noteD4, 1) },
                    { 7, Cell::build(TrackTestHelper::noteDs4, 1) },
                    { 0xa, Cell::build(TrackTestHelper::noteDs4, 1) },
                    { 0xd, Cell::build(TrackTestHelper::noteE4, 1) },
                    { 0x10, Cell::build(TrackTestHelper::noteE4, 1) },
                    { 0x13, Cell::build(TrackTestHelper::noteF4, 1) },
                    { 0x16, Cell::build(TrackTestHelper::noteF4, 1) },
            });
            REQUIRE(success);
        }
        {
            // Position 12, channel 0-1-2.
            const auto patternIndex = subsong.getPosition(0x12).getPatternIndex();
            for (auto channelIndex = 0; channelIndex <= 2; ++channelIndex) {
                const auto trackIndex = subsong.getPatternFromIndex(patternIndex).getCurrentTrackIndex(channelIndex);
                const auto& track = subsong.getTrackRefFromIndex(trackIndex);
                const auto success = TrackTestHelper::containsOnly(track, {
                        { 0,    Cell::build(TrackTestHelper::noteC5, 9, CellEffects({{ Effect::volume, 0xf }})) },     // NOLINT(clion-misra-cpp2008-5-2-4)
                        { 2,    Cell::build(TrackTestHelper::noteC5, 9) },
                        { 3,    Cell::build(TrackTestHelper::noteC5, 9) },
                        { 5,    Cell::build(TrackTestHelper::noteC5, 9) },
                        { 7,    Cell::build(TrackTestHelper::noteC5, 9) },
                        { 8,    Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0xa,  Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0xc,  Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0xe,  Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x10, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x12, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x13, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x15, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x17, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x18, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x1a, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x1c, Cell::build(TrackTestHelper::noteC5, 9) },
                        { 0x1e, Cell::build(TrackTestHelper::noteC5, 9) },
                });
                REQUIRE(success);
            }
        }

        // Event tracks. All empty.
        for (auto positionIndex = 0; positionIndex < 0x12; ++positionIndex) {
            const auto& eventTrack = subsong.getSpecialTrackRefFromPosition(positionIndex, false);
            REQUIRE(eventTrack.isEmpty());
        }

        // Speed tracks.
        {
            // Position 0, speed track.
            const auto& speedTrack = subsong.getSpecialTrackRefFromPosition(0, true);
            const auto success = TrackTestHelper::containsOnly(speedTrack, {
                    { 0, 0x10 },
            });
            REQUIRE(success);
        }
        {
            // Position 1, speed track.
            const auto& speedTrack = subsong.getSpecialTrackRefFromPosition(1, true);
            const auto success = TrackTestHelper::containsOnly(speedTrack, {
                    { 0, 0xf },
                    { 5, 0xe },
                    { 9, 0xd },
                    { 0xb, 0xc },
                    { 0xe, 0xb },
                    { 0x10, 0xa },
                    { 0x13, 0x9 },
            });
            REQUIRE(success);
        }
        {
            // Position 2, speed track.
            const auto& speedTrack = subsong.getSpecialTrackRefFromPosition(2, true);
            const auto success = TrackTestHelper::containsOnly(speedTrack, {
                    { 0, 0x6 },
                    { 2, 0xff },
                    { 4, 0x6 },
            });
            REQUIRE(success);
        }
        // Speed tracks.
        for (auto positionIndex : { 3, 4, 5, 6, 7, 8, 9, 0xc, 0xd, 0xe, 0xf, 0x10, 0x11, 0x12 }) {
            const auto& speedTrack = subsong.getSpecialTrackRefFromPosition(positionIndex, true);
            const auto success = TrackTestHelper::containsOnly(speedTrack, {
                    { 0, 0x6 },
            });
            REQUIRE(success);
        }
        for (auto positionIndex : { 0xa, 0xb }) {
            const auto& speedTrack = subsong.getSpecialTrackRefFromPosition(positionIndex, true);
            const auto success = TrackTestHelper::containsOnly(speedTrack, {
                    { 0, 0x18 },
            });
            REQUIRE(success);
        }
    });

    // Checks the Instruments.
    song->performOnConstInstruments([&](const std::vector<std::unique_ptr<Instrument>>& instruments) {
        REQUIRE(instruments.size() == 0x12U);
        {
            const auto& instrument = instruments.at(1U);
            REQUIRE(instrument->getName() == "Normal");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 3);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0xe, false));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xe)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xa)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x9)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x8)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x7)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x6)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x5)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x4)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x1)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(2U);
            REQUIRE(instrument->getName() == "Big Arpeg");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 1);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0x11, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 2, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 2, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 4, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 4, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 7, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 7, 1)));

            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 2)));

            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 7, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 7, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 4, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 4, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 2, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 2, 1)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xf, 0, 0, 1)));

            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(4U);
            REQUIRE(instrument->getName() == "Big Arpeg Hard");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 1);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0xf, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 1, 0, 2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 2, 0, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 2, 1, 0, 2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 4, 0, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 4, 1, 0, 2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 7, 0, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 7, 1, 0, 2)));

            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 1, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 2, 0, 2)));

            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 7, 0, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 7, 1, 0, 2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 4, 0, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 4, 1, 0, 2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 2, 0, 0, 3)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 2, 1, 0, 2)));

            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(5U);
            REQUIRE(instrument->getName() == "BassHardTrig");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 7);
            REQUIRE(psgPart.getMainLoop() == Loop(1, 0x2, false));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0, 5)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xa)));

            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(6U);
            REQUIRE(instrument->getName() == "BassHardTrig2");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 2);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 1, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 1, 0, 2)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xd)));

            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(7U);
            REQUIRE(instrument->getName() == "HardMinor");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 1);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 2, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0, 3, 0xe)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 3, 0, 0, 3, 0xe)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 7, 0, 0, 3, 0xe)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(0xaU);
            REQUIRE(instrument->getName() == "Bass Hard R0");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0, 0)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(0xbU);
            REQUIRE(instrument->getName() == "Double Sound");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell(PsgInstrumentCellLink::softAndHard,
              0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 8, false,
              PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
              PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(0xeU);
            REQUIRE(instrument->getName() == "Hard Soft");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft,
                0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
                PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(0xfU);
            REQUIRE(instrument->getName() == "Hard Soft Waaaaw");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell(PsgInstrumentCellLink::hardToSoft,
                0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 1, 0xa, false,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
                PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(0x10U);
            REQUIRE(instrument->getName() == "Hard CoolBass");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 1);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 1, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0)));
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0, 4, 0xa)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
        {
            const auto& instrument = instruments.at(0x11U);
            REQUIRE(instrument->getName() == "Hard No Sound");
            REQUIRE(instrument->getType() == InstrumentType::psgInstrument);
            const auto& psgPart = instrument->getPsgPart();
            REQUIRE_FALSE(psgPart.isInstrumentRetrig());
            REQUIRE(psgPart.getSpeed() == 0);
            REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
            auto cellIndex = 0;
            REQUIRE(psgPart.getCellRefConst(cellIndex++).isMusicallyEqualTo(PsgInstrumentCell(PsgInstrumentCellLink::hardOnly,
                  0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0xe, false,
                  PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
                  PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
            REQUIRE(psgPart.getLength() == cellIndex);
        }
    });
}

}   // namespace arkostracker
