#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/import/furnace/FurnaceImporter.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker
{

TEST_CASE("Furnace import, aeration version 181", "[FurnaceImporter]")
{
    juce::MemoryInputStream compressedInputStream(BinaryData::aeration_fur, BinaryData::aeration_furSize, false);
    juce::BufferedInputStream bufferedCompressedInputStream(compressedInputStream, 16384);

    juce::GZIPDecompressorInputStream dis(&bufferedCompressedInputStream, false);

    juce::MemoryBlock memoryBlock;
    dis.readIntoMemoryBlock(memoryBlock);

    juce::MemoryInputStream mis(memoryBlock, false);

    //FileUtil::saveMemoryBlockToFile("~/Downloads/aerationDecomp.bin", memoryBlock);

    REQUIRE((memoryBlock.getSize() > 0));

    // Parses.
    FurnaceImporter importer;
    REQUIRE(importer.doesFormatMatch(mis, "fur"));

    mis.setPosition(0);
    auto result = importer.loadSong(mis, ImportConfiguration());
    REQUIRE((result != nullptr));
    REQUIRE((result->song != nullptr));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());
}

TEST_CASE("Furnace import, simple", "[FurnaceImporter]")
{
    juce::MemoryInputStream compressedInputStream(BinaryData::FurnaceSimple_fur, BinaryData::FurnaceSimple_furSize, false);
    juce::BufferedInputStream bufferedCompressedInputStream(compressedInputStream, 16384);

    juce::GZIPDecompressorInputStream dis(&bufferedCompressedInputStream, false);

    juce::MemoryBlock memoryBlock;
    dis.readIntoMemoryBlock(memoryBlock);

    juce::MemoryInputStream mis(memoryBlock, false);

    //FileUtil::saveMemoryBlockToFile("~/Downloads/FurnaceSimpleDecomp.bin", memoryBlock);

    REQUIRE((memoryBlock.getSize() > 0));

    // Parses.
    FurnaceImporter importer;
    REQUIRE(importer.doesFormatMatch(mis, "fur"));

    mis.setPosition(0);
    auto result = importer.loadSong(mis, ImportConfiguration());
    REQUIRE((result != nullptr));
    REQUIRE((result->song != nullptr));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());
    const auto& song = result->song;

    REQUIRE((song->getSubsongCount() == 1));
    const auto subsong1Id = song->getSubsongId(0).getValue();

    // Checks the PSGs.
    const auto psgs = song->getSubsongPsgs(subsong1Id);
    REQUIRE((psgs.size() == 1));
    REQUIRE((psgs.at(0) == Psg::buildForCpc()));

    // Checks the instrument.
    REQUIRE((song->getInstrumentCount() == 5));

    // Instr 2: simple decay
    song->performOnConstPsgInstrumentFromIndex(2, [&] (const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE((instrument.getName() == "Simple decay"));
        REQUIRE((psgPart.getLength() == 16));
        REQUIRE((psgPart.getSpeed() == 0));
        REQUIRE((psgPart.getMainLoopRef() == Loop(15, 15, true)));

        REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15)));
        REQUIRE((psgPart.getCellRefConst(1) == PsgInstrumentCell::buildSoftwareCell(14)));
        REQUIRE((psgPart.getCellRefConst(2) == PsgInstrumentCell::buildSoftwareCell(13)));
        REQUIRE((psgPart.getCellRefConst(3) == PsgInstrumentCell::buildSoftwareCell(12)));
        REQUIRE((psgPart.getCellRefConst(4) == PsgInstrumentCell::buildSoftwareCell(11)));
        REQUIRE((psgPart.getCellRefConst(5) == PsgInstrumentCell::buildSoftwareCell(10)));
        REQUIRE((psgPart.getCellRefConst(6) == PsgInstrumentCell::buildSoftwareCell(9)));
        REQUIRE((psgPart.getCellRefConst(7) == PsgInstrumentCell::buildSoftwareCell(8)));
        REQUIRE((psgPart.getCellRefConst(8) == PsgInstrumentCell::buildSoftwareCell(7)));
        REQUIRE((psgPart.getCellRefConst(9) == PsgInstrumentCell::buildSoftwareCell(6)));
        REQUIRE((psgPart.getCellRefConst(10) == PsgInstrumentCell::buildSoftwareCell(5)));
        REQUIRE((psgPart.getCellRefConst(11) == PsgInstrumentCell::buildSoftwareCell(4)));
        REQUIRE((psgPart.getCellRefConst(12) == PsgInstrumentCell::buildSoftwareCell(3)));
        REQUIRE((psgPart.getCellRefConst(13) == PsgInstrumentCell::buildSoftwareCell(2)));
        REQUIRE((psgPart.getCellRefConst(14) == PsgInstrumentCell::buildSoftwareCell(1)));
        REQUIRE((psgPart.getCellRefConst(15) == PsgInstrumentCell::buildSoftwareCell(0)));
    });

    // Instr 1: My Instr0
    song->performOnConstPsgInstrumentFromIndex(1, [&] (const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE((instrument.getName() == "My Instr0"));
        REQUIRE((psgPart.getLength() == 15));
        REQUIRE((psgPart.getSpeed() == 0));
        REQUIRE((psgPart.getMainLoopRef() == Loop(3, 14, true)));

        REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15, 0, 0, 0, 64)));
        REQUIRE((psgPart.getCellRefConst(1) == PsgInstrumentCell::buildSoftwareCell(14, 0, 0, 0, 54)));
        REQUIRE((psgPart.getCellRefConst(2) == PsgInstrumentCell::buildSoftwareCell(13, 0, 0, 0, 50)));
        REQUIRE((psgPart.getCellRefConst(3) == PsgInstrumentCell::buildSoftwareCell(12, 0, 0, 1, 39)));
        REQUIRE((psgPart.getCellRefConst(4) == PsgInstrumentCell::buildSoftwareCell(11, 0, 0, 0, 19)));
        REQUIRE((psgPart.getCellRefConst(5) == PsgInstrumentCell::buildSoftwareCell(10, 0, 0, 0, -50)));
        REQUIRE((psgPart.getCellRefConst(6) == PsgInstrumentCell::buildSoftwareCell(9, 1, 0, 0, -34)));
        REQUIRE((psgPart.getCellRefConst(7) == PsgInstrumentCell::buildSoftwareCell(8, 2, 0, 0, -20)));
        REQUIRE((psgPart.getCellRefConst(8) == PsgInstrumentCell::buildSoftwareCell(7, 2)));
        REQUIRE((psgPart.getCellRefConst(9) == PsgInstrumentCell::buildSoftwareCell(6, 3)));
        REQUIRE((psgPart.getCellRefConst(10) == PsgInstrumentCell::buildSoftwareCell(5, 4)));
        REQUIRE((psgPart.getCellRefConst(11) == PsgInstrumentCell::buildSoftwareCell(4, 4)));
        REQUIRE((psgPart.getCellRefConst(12) == PsgInstrumentCell::buildSoftwareCell(3, 4)));
        REQUIRE((psgPart.getCellRefConst(13) == PsgInstrumentCell::buildSoftwareCell(2, 4)));
        REQUIRE((psgPart.getCellRefConst(14) == PsgInstrumentCell::buildSoftwareCell(1, 4)));
    });

    // Instr 3: Simple hardware
    song->performOnConstPsgInstrumentFromIndex(3, [&] (const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE((instrument.getName() == "Simple hardware"));
        REQUIRE((psgPart.getLength() == 1));
        REQUIRE((psgPart.getSpeed() == 0));
        REQUIRE((psgPart.getMainLoopRef() == Loop(0, 0, true)));

        REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftToHard(0, 0, 0, 0, 4, 10)));
    });

    // Instr 4: Forced stuff
    song->performOnConstPsgInstrumentFromIndex(4, [&] (const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE((instrument.getName() == "Forced stuff"));
        REQUIRE((psgPart.getLength() == 2));
        REQUIRE((psgPart.getSpeed() == 12));
        REQUIRE((psgPart.getMainLoopRef() == Loop(0, 1, true)));

        REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15, 0, 0, 0, 0, true, 307)));
        REQUIRE((psgPart.getCellRefConst(1) == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 0, 0, 102, 0, 0, 0, 4,
            1638, 0, 0, 0, 8, true, PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
            PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch)));
    });

    // Subsong 1.
    song->performOnConstSubsong(subsong1Id, [&] (const Subsong& subsong) {
        REQUIRE((subsong.getLength() == 2));
        REQUIRE((subsong.getPatternCount() == 2));
        REQUIRE((subsong.getTrackCount() == 6));
        REQUIRE((subsong.getName() == "Subsong 1"));
        REQUIRE((subsong.getMetadata().getHighlightSpacing() == 4));
        REQUIRE((subsong.getMetadata().getSecondaryHighlight() == 4));
        REQUIRE((subsong.getMetadata().getInitialSpeed() == 9));
        REQUIRE((subsong.getMetadata().getDigiChannel() == 1));
        REQUIRE(juce::exactlyEqual(subsong.getReplayFrequencyHz(), 60.0F));
        REQUIRE((subsong.getLoop() == Loop(0, 1, true)));

        // Position 0.
        {
            const auto& pattern = subsong.getPatternRef(0);

            const auto& track0 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(0));
            const auto& track1 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(1));
            const auto& track2 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(2));

            REQUIRE(TrackTestHelper::containsOnly(track0, {
                { 0, Cell::build((4 * 12) + 0, 1) },
                { 4, Cell::build((4 * 12) + 2, 1) },
                { 8, Cell::build((4 * 12) + 4, 1) },
                { 12, Cell::build((4 * 12) + 5, 1) },
                { 16, Cell::build((4 * 12) + 7, 1) },

                { 22, Cell::build((3 * 12) + 0, 3) },
                { 25, Cell::build((3 * 12) + 2, 3) },
                { 28, Cell::build((3 * 12) + 4, 3) },
            }));
            REQUIRE((track1.isEmpty()));
            REQUIRE(TrackTestHelper::containsOnly(track2, {
                { 1, Cell::build((5 * 12) + 0, 2) },
                { 5, Cell::build((5 * 12) + 2, 2) },
                { 9, Cell::build((5 * 12) + 4, 2) },
                { 13, Cell::build((5 * 12) + 5, 2) },
                { 17, Cell::build((5 * 12) + 7, 2) },
            }));
        }

        // Position 1.
        {
            const auto& pattern = subsong.getPatternRef(1);

            const auto& track0 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(0));
            const auto& track1 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(1));
            const auto& track2 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(2));

            REQUIRE(TrackTestHelper::containsOnly(track0, {
                { 0, Cell::build((3 * 12) + 0, 1, CellEffects({ { Effect::volume, 0xf } }))},
                { 2, Cell::build((4 * 12) + 0, 1, CellEffects({ { Effect::volume, 0xa } }))},
                { 4, Cell::build((4 * 12) + 0, 1, CellEffects({ { Effect::volume, 0x5 } }))},
            }));
            REQUIRE((track1.isEmpty()));
            REQUIRE(TrackTestHelper::containsOnly(track2, {
                { 8, Cell::build((4 * 12) + 4, 2, CellEffects({ { Effect::volume, 0xe } }))},
                { 16, Cell::build((4 * 12) + 7, 2, CellEffects({ { Effect::volume, 0x1 } }))},
            }));
        }
    });
}

TEST_CASE("Furnace import, two subsongs", "[FurnaceImporter]")
{
    juce::MemoryInputStream compressedInputStream(BinaryData::TwoSubsongs_fur, BinaryData::TwoSubsongs_furSize, false);
    juce::BufferedInputStream bufferedCompressedInputStream(compressedInputStream, 16384);

    juce::GZIPDecompressorInputStream dis(&bufferedCompressedInputStream, false);

    juce::MemoryBlock memoryBlock;
    dis.readIntoMemoryBlock(memoryBlock);

    juce::MemoryInputStream mis(memoryBlock, false);

    //FileUtil::saveMemoryBlockToFile("~/Downloads/TwoSubsongsDecomp.bin", memoryBlock);

    REQUIRE((memoryBlock.getSize() > 0));

    // Parses.
    FurnaceImporter importer;
    REQUIRE(importer.doesFormatMatch(mis, "fur"));

    mis.setPosition(0);
    auto result = importer.loadSong(mis, ImportConfiguration());
    REQUIRE((result != nullptr));
    REQUIRE((result->song != nullptr));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());
    const auto& song = result->song;

    REQUIRE((song->getSubsongCount() == 2));
    REQUIRE((song->getInstrumentCount() == 2));
    REQUIRE((song->getTitle() == "MySuperSong"));
    REQUIRE((song->getAuthor() == "Targhan"));
    REQUIRE((song->getComposer() == ""));
    REQUIRE((song->getComments() == "This is the song comment. Yay!\nConverted by Arkos Tracker 3."));

    const auto subsong1Id = song->getSubsongId(0).getValue();
    const auto subsong2Id = song->getSubsongId(1).getValue();

    const auto expectedPsg = std::vector { Psg::buildForCpc() };

    // Subsong 1.
    song->performOnConstSubsong(subsong1Id, [&] (const Subsong& subsong) {
        REQUIRE((subsong.getPsgCount() == 1));

        REQUIRE((subsong.getPsgRefs() == expectedPsg));
        REQUIRE((subsong.getLength() == 1));
        REQUIRE((subsong.getPatternCount() == 1));
        REQUIRE((subsong.getTrackCount() == 3));
        REQUIRE((subsong.getName() == "MySubsong1"));
        REQUIRE((subsong.getMetadata().getHighlightSpacing() == 4));
        REQUIRE((subsong.getMetadata().getSecondaryHighlight() == 4));
        REQUIRE((subsong.getMetadata().getInitialSpeed() == 6));
        REQUIRE((subsong.getMetadata().getDigiChannel() == 1));
        REQUIRE(juce::exactlyEqual(subsong.getReplayFrequencyHz(), 60.0F));
        REQUIRE((subsong.getLoop() == Loop(0, 0, true)));

        const auto& pattern0 = subsong.getPatternRef(0);

        const auto& track0 = subsong.getTrackRefFromIndex(pattern0.getCurrentTrackIndex(0));
        const auto& track1 = subsong.getTrackRefFromIndex(pattern0.getCurrentTrackIndex(1));
        const auto& track2 = subsong.getTrackRefFromIndex(pattern0.getCurrentTrackIndex(2));
        REQUIRE((track0.getName() == "Youpi"));
        REQUIRE((track1.getName() == "Youpa"));
        REQUIRE((track2.getName() == "Youpo"));

        REQUIRE((track1.isEmpty()));
        REQUIRE((track2.isEmpty()));
        const auto valid = TrackTestHelper::containsOnly(track0, {
            { 0, Cell::build((4 * 12) + 0, 1)},
            { 2, Cell::build((4 * 12) + 2, 1)},
            { 4, Cell::build((4 * 12) + 4, 1)},
            { 6, Cell::build((4 * 12) + 5, 1)},
            { 8, Cell::build((4 * 12) + 7, 1)},
        });
        REQUIRE(valid);
    });

    // Subsong 2.
    song->performOnConstSubsong(subsong2Id, [&] (const Subsong& subsong) {
        REQUIRE((subsong.getPsgCount() == 1));

        REQUIRE((subsong.getPsgRefs() == expectedPsg));
        REQUIRE((subsong.getLength() == 1));
        REQUIRE((subsong.getPatternCount() == 1));
        REQUIRE((subsong.getTrackCount() == 3));
        REQUIRE((subsong.getName() == "The second Subsong"));
        REQUIRE((subsong.getMetadata().getHighlightSpacing() == 4));
        REQUIRE((subsong.getMetadata().getSecondaryHighlight() == 4));
        REQUIRE((subsong.getMetadata().getInitialSpeed() == 6));
        REQUIRE((subsong.getMetadata().getDigiChannel() == 1));
        REQUIRE(juce::exactlyEqual(subsong.getReplayFrequencyHz(), 60.0F));
        REQUIRE((subsong.getLoop() == Loop(0, 0, true)));

        const auto& pattern0 = subsong.getPatternRef(0);

        const auto& track0 = subsong.getTrackRefFromIndex(pattern0.getCurrentTrackIndex(0));
        const auto& track1 = subsong.getTrackRefFromIndex(pattern0.getCurrentTrackIndex(1));
        const auto& track2 = subsong.getTrackRefFromIndex(pattern0.getCurrentTrackIndex(2));
        REQUIRE((track0.getName() == "Robert1"));
        REQUIRE((track1.getName() == "Robert2"));
        REQUIRE((track2.getName() == "Robert3"));

        REQUIRE((track0.isEmpty()));
        REQUIRE((track1.isEmpty()));
        const auto valid = TrackTestHelper::containsOnly(track2, {
            { 0, Cell::build((4 * 12) + 5, 1)},     // F-4
            { 1, Cell::build((4 * 12) + 4, 1)},     // E-4
            { 2, Cell::build((4 * 12) + 5, 1)},     // F-4
            { 3, Cell::build((4 * 12) + 4, 1)},     // E-4
            { 4, Cell::build((4 * 12) + 5, 1)},     // F-4
            { 5, Cell::build((4 * 12) + 4, 1)},     // E-4
            { 6, Cell::build((4 * 12) + 5, 1)},     // F-4
            { 7, Cell::build((4 * 12) + 4, 1)},     // E-4
            { 8, Cell::build((4 * 12) + 5, 1)},     // F-4
            { 9, Cell::build((4 * 12) + 4, 1)},     // E-4
            { 10, Cell::build((4 * 12) + 5, 1)},     // F-4
        });
        REQUIRE(valid);
    });

    // Instr 1.
    song->performOnConstPsgInstrumentFromIndex(1, [&] (const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE((instrument.getName() == "Beep"));
        REQUIRE((psgPart.getLength() == 1));
        REQUIRE((psgPart.getSpeed() == 0));
        REQUIRE((psgPart.getMainLoopRef() == Loop(0, 0, true)));

        REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15)));
    });
}

TEST_CASE("Furnace import, one channel speaker", "[FurnaceImporter]")
{
    juce::MemoryInputStream compressedInputStream(BinaryData::OneChannelSpeaker_fur, BinaryData::OneChannelSpeaker_furSize, false);
    juce::BufferedInputStream bufferedCompressedInputStream(compressedInputStream, 16384);

    juce::GZIPDecompressorInputStream dis(&bufferedCompressedInputStream, false);

    juce::MemoryBlock memoryBlock;
    dis.readIntoMemoryBlock(memoryBlock);

    juce::MemoryInputStream mis(memoryBlock, false);

    //FileUtil::saveMemoryBlockToFile("~/Downloads/OneChannelSpeaker.bin", memoryBlock);

    REQUIRE((memoryBlock.getSize() > 0));

    // Parses.
    FurnaceImporter importer;
    REQUIRE(importer.doesFormatMatch(mis, "fur"));

    mis.setPosition(0);
    auto result = importer.loadSong(mis, ImportConfiguration());
    REQUIRE((result != nullptr));
    REQUIRE((result->song != nullptr));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());
    const auto& song = result->song;

    REQUIRE((song->getSubsongCount() == 1));
    const auto subsong1Id = song->getSubsongId(0).getValue();

    // Checks the PSGs.
    const auto psgs = song->getSubsongPsgs(subsong1Id);
    REQUIRE((psgs.size() == 1));
    REQUIRE((psgs.at(0) == Psg::buildForCpc()));

    // Checks the instrument.
    REQUIRE((song->getInstrumentCount() == 2));

    // Instr 1: Speaker
    song->performOnConstPsgInstrumentFromIndex(1, [&] (const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE((instrument.getName() == "Instrument 0"));
        REQUIRE((psgPart.getLength() == 1));
        REQUIRE((psgPart.getSpeed() == 0));
        REQUIRE((psgPart.getMainLoopRef() == Loop(0, 0, false)));

        REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15)));
    });

    // Subsong 1.
    song->performOnConstSubsong(subsong1Id, [&] (const Subsong& subsong) {
        REQUIRE((subsong.getLength() == 1));
        REQUIRE((subsong.getPatternCount() == 1));
        REQUIRE((subsong.getTrackCount() == 3));
        REQUIRE((subsong.getName() == "Subsong 1"));
        REQUIRE((subsong.getMetadata().getHighlightSpacing() == 4));
        REQUIRE((subsong.getMetadata().getSecondaryHighlight() == 4));
        REQUIRE((subsong.getMetadata().getInitialSpeed() == 6));
        REQUIRE((subsong.getMetadata().getDigiChannel() == 1));
        REQUIRE(juce::exactlyEqual(subsong.getReplayFrequencyHz(), 60.0F));
        REQUIRE((subsong.getLoop() == Loop(0, 0, true)));

        // Position 0.
        {
            const auto& pattern = subsong.getPatternRef(0);

            const auto& track0 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(0));
            const auto& track1 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(1));
            const auto& track2 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(2));

            REQUIRE(TrackTestHelper::containsOnly(track0, {
                { 0, Cell::build((4 * 12) + 0, 1) },
                { 4, Cell::build((4 * 12) + 2, 1) },
                { 8, Cell::build((4 * 12) + 4, 1) },
            }));
            REQUIRE((track1.isEmpty()));
            REQUIRE((track2.isEmpty()));
        }
    });
}

TEST_CASE("Furnace import, 6 channels, strange instrument", "[FurnaceImporter]")
{
    juce::MemoryInputStream compressedInputStream(BinaryData::_6ChannelsStrangeInstruments_fur, BinaryData::_6ChannelsStrangeInstruments_furSize, false);
    juce::BufferedInputStream bufferedCompressedInputStream(compressedInputStream, 16384);

    juce::GZIPDecompressorInputStream dis(&bufferedCompressedInputStream, false);

    juce::MemoryBlock memoryBlock;
    dis.readIntoMemoryBlock(memoryBlock);

    juce::MemoryInputStream mis(memoryBlock, false);

    //FileUtil::saveMemoryBlockToFile("~/Downloads/OneChannelSpeaker.bin", memoryBlock);

    REQUIRE((memoryBlock.getSize() > 0));

    // Parses.
    FurnaceImporter importer;
    REQUIRE(importer.doesFormatMatch(mis, "fur"));

    mis.setPosition(0);
    auto result = importer.loadSong(mis, ImportConfiguration());
    REQUIRE((result != nullptr));
    REQUIRE((result->song != nullptr));
    REQUIRE((result->errorReport != nullptr));
    REQUIRE(result->errorReport->isOk());
    const auto& song = result->song;

    REQUIRE((song->getSubsongCount() == 1));
    const auto subsong1Id = song->getSubsongId(0).getValue();

    // Checks the PSGs.
    const auto psgs = song->getSubsongPsgs(subsong1Id);
    REQUIRE((psgs.size() == 2));
    REQUIRE((psgs.at(0) == Psg::buildForCpc()));
    REQUIRE((psgs.at(1) == Psg::buildForCpc()));

    // Checks the instrument.
    REQUIRE((song->getInstrumentCount() == 2));

    // Instr 1: Adsr, LFO.
    song->performOnConstPsgInstrumentFromIndex(1, [&] (const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE((instrument.getName() == "SimpleDecay"));
        REQUIRE((psgPart.getLength() == 3));
        REQUIRE((psgPart.getSpeed() == 0));
        REQUIRE((psgPart.getMainLoopRef() == Loop(2, 2, true)));

        REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(13)));
        REQUIRE((psgPart.getCellRefConst(1) == PsgInstrumentCell::buildSoftwareCell(11)));
        REQUIRE((psgPart.getCellRefConst(2) == PsgInstrumentCell::buildSoftwareCell(8)));
    });

    // Subsong 1.
    song->performOnConstSubsong(subsong1Id, [&] (const Subsong& subsong) {
        REQUIRE((subsong.getLength() == 1));
        REQUIRE((subsong.getPatternCount() == 1));
        REQUIRE((subsong.getTrackCount() == 6));
        REQUIRE((subsong.getName() == "Subsong 1"));
        REQUIRE((subsong.getMetadata().getHighlightSpacing() == 4));
        REQUIRE((subsong.getMetadata().getSecondaryHighlight() == 4));
        REQUIRE((subsong.getMetadata().getInitialSpeed() == 6));
        REQUIRE((subsong.getMetadata().getDigiChannel() == 1));
        REQUIRE(juce::exactlyEqual(subsong.getReplayFrequencyHz(), 60.0F));
        REQUIRE((subsong.getLoop() == Loop(0, 0, true)));

        // Position 0.
        {
            const auto& pattern = subsong.getPatternRef(0);

            const auto& track0 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(0));
            const auto& track1 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(1));
            const auto& track2 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(2));
            const auto& track3 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(3));
            const auto& track4 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(4));
            const auto& track5 = subsong.getTrackRefFromIndex(pattern.getCurrentTrackIndex(5));

            REQUIRE(TrackTestHelper::containsOnly(track0, {{ 0, Cell::build((4 * 12) + 0, 1) } }));
            REQUIRE(TrackTestHelper::containsOnly(track1, {{ 1, Cell::build((4 * 12) + 2, 1) } }));
            REQUIRE(TrackTestHelper::containsOnly(track2, {{ 2, Cell::build((4 * 12) + 4, 1) } }));
            REQUIRE(TrackTestHelper::containsOnly(track3, {{ 3, Cell::build((4 * 12) + 5, 1) } }));
            REQUIRE(TrackTestHelper::containsOnly(track4, {{ 4, Cell::build((4 * 12) + 7, 1) } }));
            REQUIRE(TrackTestHelper::containsOnly(track5, {{ 5, Cell::build((4 * 12) + 9, 1) } }));
        }
    });
}

}   // namespace arkostracker
