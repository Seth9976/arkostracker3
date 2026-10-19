#include "FurnaceImporter.h"

#include <cstddef>

#include "../../song/cells/CellConstants.h"
#include "../../utils/NumberUtil.h"
#include "../../utils/StreamUtil.h"
#include "../../utils/StringUtil.h"
#include "FurnaceInstrumentReader.h"

namespace arkostracker
{

const juce::String FurnaceImporter::headerTag = "-Furnace module-";          // NOLINT(cert-err58-cpp, *-statically-constructed-objects)
const int FurnaceImporter::minimumFormatNumber = 181;
const int FurnaceImporter::maximumFormatNumber = 239;

const std::unordered_map<unsigned char, int> FurnaceImporter::chipIdToChannelCount = {  // NOLINT(cert-err58-cpp, *-statically-constructed-objects)
    { 0x01, 17 },
    { 0x03, 4 },
    { 0x04, 4 },
    { 0x05, 6 },
    { 0x06, 5 },
    { 0x07, 3 },
    { 0x47, 3 },
    { 0x80, 3 },
    { 0x81, 4 },
    { 0x82, 8 },
    { 0x83, 6 },
    { 0x84, 2 },
    { 0x85, 4 },
    { 0x86, 1 },
    { 0x87, 8 },
    { 0x88, 3 },
    { 0x89, 9 },
    { 0x8a, 1 },
    { 0x8b, 3 },
    { 0x8c, 8 },
    { 0x8d, 6 },
    { 0x8e, 16 },
    { 0x8f, 9 },
    { 0x90, 9 },
    { 0x91, 18 },
    { 0x92, 28 },
    { 0x93, 1 },
    { 0x94, 4 },
    { 0x95, 8 },
    { 0x96, 4 },
    { 0x97, 6 },
    { 0x98, 8 },
    { 0x99, 1 },
    { 0x9a, 3 },
    { 0x9b, 16 },
    { 0x9c, 6 },
    { 0x9d, 6 },
    { 0x9e, 16 },
    { 0x9f, 6 },
    { 0xa0, 9 },
    { 0xa1, 5 },
    { 0xa2, 11 },
    { 0xa3, 11 },
    { 0xa4, 20 },
    { 0xa5, 14 },
    { 0xa6, 17 },
    { 0xa7, 11 },
    { 0xa8, 4 },
    { 0xaa, 4 },
    { 0xab, 1 },
    { 0xac, 17 },
    { 0xad, 2 },
    { 0xae, 42 },
    { 0xaf, 44 },
    { 0xb0, 16 },
    { 0xb1, 32 },
    { 0xb2, 10 },
    { 0xb3, 12 },
    { 0xb4, 5 },
    { 0xb5, 8 },
    { 0xb6, 9 },
    { 0xb7, 19 },
    { 0xb8, 8 },
    { 0xb9, 3 },
    { 0xba, 8 },
    { 0xbb, 8 },
    { 0xbc, 8 },
    { 0xbd, 11 },
    { 0xbe, 7 },
    { 0xbf, 4 },
    { 0xc0, 1 },
    { 0xc1, 10 },
    { 0xc2, 18 },
    { 0xc3, 10 },
    { 0xc4, 20 },
    { 0xc5, 20 },
    { 0xc6, 2 },
    { 0xc7, 4 },
    { 0xc8, 3 },
    { 0xc9, 16 },
    { 0xca, 5 },
    { 0xcb, 3 },
    { 0xcc, 4 },
    { 0xcd, 2 },
    { 0xce, 24 },
    { 0xcf, 16 },
    { 0xd0, 32 },
    { 0xd1, 18 },
    { 0xd2, 32 },
    { 0xd4, 4 },
    { 0xd5, 6 },
    { 0xd6, 16 },
    { 0xd7, 2 },
    { 0xd8, 16 },
    { 0xd9, 4 },
    { 0xda, 32 },
    { 0xdb, 48 },
    { 0xdc, 32 },
    { 0xdd, 9 },
    { 0xde, 19 },
    { 0xdf, 13 },
    { 0xe0, 19 },
    { 0xe1, 24 },
    { 0xe2, 4 },
    { 0xe3, 4 },
    { 0xe4, 8 },
    { 0xe5, 4 },
    { 0xf0, 3 },
    { 0xf1, 5 },
    { 0xf5, 7 },
    { 0xfc, 1 },
    { 0xfd, 8 },
};

FurnaceImporter::FurnaceImporter() :
    songBuilder(),
    formatNumber(),
    currentInstrumentIndex(1),
    originalSongChannelCount(),
    psgs(),
    flagChunkCount(),
    subsongIndexToOrderLength(),
    subsongIndexAndChannelIndexAndTrackIndexAndTrack(),
    subsongIndexToPatterns(),
    subsongIndexToPositions(),
    subsongCountFromBlocks(1)
{
}

bool FurnaceImporter::doesFormatMatch(juce::InputStream& inputStream, const juce::String& /*extension*/) const noexcept
{
    // Checks the header.
    const auto headerTagSize = headerTag.length();
    if (inputStream.getTotalLength() < headerTagSize) {
        return false;
    }

    juce::MemoryBlock memoryBlock(static_cast<size_t>(headerTagSize));
    inputStream.read(memoryBlock.getData(), headerTagSize);

    return (memoryBlock.toString() == headerTag);
}

ImportedFormat FurnaceImporter::getFormat() noexcept
{
    return ImportedFormat::furnace;
}

std::unique_ptr<SongImporter::Result> FurnaceImporter::loadSong(juce::InputStream& inputStream, const ImportConfiguration& /*configuration*/) noexcept
{
    inputStream.skipNextBytes(headerTag.length());

    songBuilder = std::make_unique<SongBuilder>();

    // Checks the format version.
    formatNumber = inputStream.readShort();
    if (formatNumber < minimumFormatNumber) {
        songBuilder->addError("Format version is too low. Minimum is " + juce::String(minimumFormatNumber) + " (save it again with a newest Furnace version to correct this).");
        return std::make_unique<Result>(nullptr, songBuilder->getErrorReport());
    }
    if (formatNumber > maximumFormatNumber) {
        songBuilder->addError("Format version is too high. Maximum is " + juce::String(maximumFormatNumber) + " (send me the song!).");
        return std::make_unique<Result>(nullptr, songBuilder->getErrorReport());
    }

    inputStream.skipNextBytes(14);  // Skips reserved and song info pointer.

    auto success = true;
    const auto fileSize = inputStream.getTotalLength();

    while (!inputStream.isExhausted() && success) {
        const auto blockId = StreamUtil::extractString(inputStream, 4, success);
        const auto blockSize = inputStream.readInt();

        if (inputStream.getPosition() + blockSize > fileSize) {
            songBuilder->addError("Malformed block: size is too large compared to the file size.");
            return std::make_unique<Result>(nullptr, songBuilder->getErrorReport());
        }

        if (!success) {
            songBuilder->addError("Unable to read the next block id.");
            return std::make_unique<Result>(nullptr, songBuilder->getErrorReport());
        }

        DBG("Found block: " + blockId);

        if (blockId == "INFO") {
            success = readOldInfoBlock(inputStream, blockSize);
        //} else if (blockId == "INF2") {     // >= 240.
        //    success = readInfoBlock(inputStream);
        } else if (blockId == "SONG") {     // Present for each *subsequent* subsongs.
            success = readSubsongBlock(inputStream, blockSize);
        } else if (blockId == "FLAG") {     // As many as there are PSGs.
            success = readFlagBlock(inputStream);
        } else if (blockId == "INS2") {
            success = FurnaceInstrumentReader::readInstrument(*songBuilder, inputStream, blockSize, currentInstrumentIndex);
            ++currentInstrumentIndex;
        } else if (blockId == "PATN") {
            success = readTrack(inputStream);
        } else {
            inputStream.skipNextBytes(blockSize);
        }
    }

    success = success && buildSubsongsAndPatterns();

    if (!success) {
        return std::make_unique<Result>(nullptr, songBuilder->getErrorReport());
    }

    auto [song, errorReport] = songBuilder->buildSong();

    return std::make_unique<Result>(std::move(song), std::move(errorReport));
}

bool FurnaceImporter::readOldInfoBlock(juce::InputStream& inputStream, const int blockSize)
{
    const auto currentPositionInStream = inputStream.getPosition();

    inputStream.skipNextBytes(1);   // Time base.
    const auto speed = inputStream.readByte();
    inputStream.skipNextBytes(2);   // Speed 2, initial arpeggio time.
    const auto playerFrequencyHz = inputStream.readFloat();
    inputStream.skipNextBytes(2);   // Length.
    const auto orderLength = inputStream.readShort();
    const auto readHighlight1 = inputStream.readByte();
    const auto readHighlight2 = inputStream.readByte();
    const auto instrumentCount = inputStream.readShort();
    const auto waveTableCount = inputStream.readShort();
    const auto sampleCount = inputStream.readShort();
    const auto patternCount = inputStream.readInt();

    juce::MemoryBlock soundChipIds;
    inputStream.readIntoMemoryBlock(soundChipIds, 32);

    inputStream.skipNextBytes(32);   // Sound chip volumes.
    inputStream.skipNextBytes(32);   // Sound chip panning.
    inputStream.skipNextBytes(128);  // Sound chip flag pointers.

    const auto songName = inputStream.readString();
    const auto author = inputStream.readString();

    const auto referenceHz = inputStream.readFloat();

    inputStream.skipNextBytes(20);                      // Skips junk bytes.

    inputStream.skipNextBytes(static_cast<unsigned int>(instrumentCount * 4));     // Skips pointers to instruments.
    inputStream.skipNextBytes(static_cast<unsigned int>(waveTableCount * 4));      // Skips pointers to wave tables.
    inputStream.skipNextBytes(static_cast<unsigned int>(sampleCount * 4));         // Skips pointers to sample tables.
    inputStream.skipNextBytes(static_cast<unsigned int>(patternCount * 4));

    // How many *channels*? Depends on the chip(s).
    auto channelCount = 0;
    for (size_t i = 0U, size = soundChipIds.getSize(); i < size; ++i) {
        const auto chipId = static_cast<unsigned char>(soundChipIds[i]);
        if (chipId == 0) {      // End of list?
            break;
        }

        if (auto it = chipIdToChannelCount.find(chipId); it != chipIdToChannelCount.cend()) {
            channelCount += it->second;
        }  else {
            songBuilder->addError("Chip ID " + NumberUtil::toHexByte(chipId) + " is unknown.");
            return false;
        }
    }
    originalSongChannelCount = channelCount;

    // There may be more PSG in the output song that in the input!
    // So there can be discrepancy if 3/4/3 PSGs for example, since the output will have 3/3/3/3.
    // No need to manage this, really...
    const auto psgCount = PsgValues::getPsgCount(channelCount);

    for (auto psgIndex = 0; psgIndex < psgCount; ++psgIndex) {
        // For now, adds the PSG even though the "FLAG" chunk isn't here yet. We will modify the PSGs later.
        psgs.emplace_back(PsgType::ay, PsgFrequency::psgFrequencyCPC, referenceHz);
    }

    // Reads the patterns/positions.
    constexpr auto subsongIndex = 0;
    readAndStoreOrder(subsongIndex, inputStream, orderLength);

    inputStream.skipNextBytes(channelCount);    // Effect columns.
    inputStream.skipNextBytes(channelCount);    // Channel hide columns.
    inputStream.skipNextBytes(channelCount);    // Channel collapse columns.
    for (auto i = 0; i < channelCount * 2; ++i) {
        inputStream.readString();               // Channel names and short names.
    }
    const auto songComment = inputStream.readString().trim();
    inputStream.skipNextBytes(36);              // Master volume + compatibility flags + virtual tempo data.

    const auto subsongName = inputStream.readString();

    // Finally, we have the basic song/subsong metadata.
    const auto finalSongComment = (songComment.isEmpty() ? juce::String() : (songComment + "\n")) + "Converted by Arkos Tracker 3.";
    songBuilder->setSongMetaData(songName, author, juce::String(), finalSongComment);

    const auto [highlight1, highlight2] = calculateHighlights(readHighlight1, readHighlight2);
    const Subsong::Metadata metadata(subsongName, speed, playerFrequencyHz, 1, highlight1, highlight2,
        0, 0, SidPlayerCapability::buildForCpc());
    subsongIndexToMetadata.insert(std::make_pair(subsongIndex, metadata));

    // Skips the remaining data.
    inputStream.skipNextBytes(blockSize - (inputStream.getPosition() - currentPositionInStream));

    return true;
}

bool FurnaceImporter::readTrack(juce::InputStream& inputStream)
{
    const auto subsongIndex = static_cast<int>(static_cast<unsigned char>(inputStream.readByte()));
    const auto channelIndex = formatNumber < 240 ? static_cast<unsigned char>(inputStream.readByte()) : static_cast<juce::uint16>(inputStream.readShort());
    const auto trackIndex = static_cast<int>(inputStream.readShort());
    const auto trackName = inputStream.readString();

    Track track(trackName);
    auto cellIndex = 0;
    auto mustContinue = true;

    while (mustContinue) {
        auto byte = static_cast<unsigned char>(inputStream.readByte());
        if (byte == 0xff) {
            mustContinue = false;
            break;
        }
        // Lines to skip?
        if ((byte & 0x80U) != 0) {
            const auto lineCountToSkip = (byte & 0x7fU) + 2;
            cellIndex += static_cast<int>(lineCountToSkip);
            continue;
        }
        if (byte == 0) {
            ++cellIndex;
            continue;
        }

        Cell cell;

        const auto isNotePresent = (byte & 0b1U) != 0;
        const auto isInstrumentPresent = (byte & 0b10U) != 0;
        const auto isVolumePresent = (byte & 0b100U) != 0;
        auto isEffect0Present = (byte & 0b1000U) != 0;
        auto isEffect1Present = false;
        auto isEffect2Present = false;
        auto isEffect3Present = false;
        auto isEffect4Present = false;
        auto isEffect5Present = false;
        auto isEffect6Present = false;
        auto isEffect7Present = false;
        auto isEffect0ValuePresent = (byte & 0b10000U) != 0;
        auto isEffect1ValuePresent = false;
        auto isEffect2ValuePresent = false;
        auto isEffect3ValuePresent = false;
        auto isEffect4ValuePresent = false;
        auto isEffect5ValuePresent = false;
        auto isEffect6ValuePresent = false;
        auto isEffect7ValuePresent = false;
        const auto areEffects0To3Present = (byte & 0b100000U) != 0;
        const auto areEffects4To7Present = (byte & 0b1000000U) != 0;

        if (areEffects0To3Present) {
            byte = static_cast<unsigned char>(inputStream.readByte());
            isEffect0Present = (byte & 0b1U) != 0;
            isEffect0ValuePresent = (byte & 0b10U) != 0;
            isEffect1Present = (byte & 0b100U) != 0;
            isEffect1ValuePresent = (byte & 0b1000U) != 0;
            isEffect2Present = (byte & 0b10000U) != 0;
            isEffect2ValuePresent = (byte & 0b100000U) != 0;
            isEffect3Present = (byte & 0b1000000U) != 0;
            isEffect3ValuePresent = (byte & 0b10000000U) != 0;
        }

        if (areEffects4To7Present) {
            byte = static_cast<unsigned char>(inputStream.readByte());
            isEffect4Present = (byte & 0b1U) != 0;
            isEffect4ValuePresent = (byte & 0b10U) != 0;
            isEffect5Present = (byte & 0b100U) != 0;
            isEffect5ValuePresent = (byte & 0b1000U) != 0;
            isEffect6Present = (byte & 0b10000U) != 0;
            isEffect6ValuePresent = (byte & 0b100000U) != 0;
            isEffect7Present = (byte & 0b1000000U) != 0;
            isEffect7ValuePresent = (byte & 0b10000000U) != 0;
        }

        auto isRst = false;
        if (isNotePresent) {
            auto writeNote = true;

            auto noteIndex = static_cast<unsigned char>(inputStream.readByte());
            switch (noteIndex) {
                case 179:       // B-9. Don't know what to do with that.
                case 180:       // Note off.
                    noteIndex = CellConstants::rstNote;
                    isRst = true;
                    break;
                case 183:       // Raw frequency.
                    inputStream.skipNextBytes(4);       // Reads the 4 next bytes, but we don't use them.
                    [[fallthrough]];
                case 181:       // Note release.
                case 182:       // Macro release.
                    writeNote = false;
                    break;
                default:
                    break;
            }

            if (writeNote) {
                const auto signedNoteIndex = static_cast<int>(noteIndex);
                const auto correctedNoteIndex = NumberUtil::correctNumber(signedNoteIndex - (5 * CellConstants::noteCountInOctave),
                    CellConstants::minimumNote, CellConstants::maximumNote);
                cell.setNote(Note::buildNote(correctedNoteIndex));
            }
        }
        if (isInstrumentPresent) {
            const auto instrumentIndex = static_cast<unsigned char>(inputStream.readByte()) + 1;    // To skip the Empty instrument.
            cell.setInstrument(instrumentIndex);
        }
        // Overrides all is RST.
        if (isRst) {
            cell.setNote(Note::buildRst());
            cell.setInstrument(CellConstants::rstInstrument);
        }

        if (isVolumePresent) {
            const auto volume = static_cast<unsigned char>(inputStream.readByte());
            cell.addEffect(Effect::volume, volume);
        }

        // ** For now, effects are skipped! **

        constexpr auto effectSize = 1;
        constexpr auto effectValueSize = 1;
        if (isEffect0Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect0ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        if (isEffect1Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect1ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        if (isEffect2Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect2ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        if (isEffect3Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect3ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        if (isEffect4Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect4ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        if (isEffect5Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect5ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        if (isEffect6Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect6ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        if (isEffect7Present) {
            inputStream.skipNextBytes(effectSize);
        }
        if (isEffect7ValuePresent) {
            inputStream.skipNextBytes(effectValueSize);
        }

        track.setCell(cellIndex, cell);

        ++cellIndex;
    }

    // Stores the Track.
    const std::tuple data = { subsongIndex, channelIndex, trackIndex, track};
    subsongIndexAndChannelIndexAndTrackIndexAndTrack.push_back(data);

    return true;
}

bool FurnaceImporter::buildSubsongsAndPatterns()
{
    std::set<int> subsongIndexes;       // Ordered.
    for (const auto& entry: subsongIndexAndChannelIndexAndTrackIndexAndTrack) {
        const auto subsongIndex = std::get<0>(entry);
        subsongIndexes.emplace(subsongIndex);
    }

    // Browses each Subsong, and grabs the patterns to build it.
    for (const auto subsongIndex : subsongIndexes) {
        auto& subsongBuilder = songBuilder->startNewSubsong(subsongIndex);

        // Adds the PSGs. They must be known by now.
        jassert(!psgs.empty());
        for (const auto& psg : psgs) {
            subsongBuilder.addPsg(psg);
        }

        // Adds the metadata.
        if (auto it = subsongIndexToMetadata.find(subsongIndex); it != subsongIndexToMetadata.cend()) {
            const auto& subsongMetadata = it->second;
            // Corrects the name, if empty.
            auto subsongName = subsongMetadata.getName();
            if (subsongName.trim().isEmpty()) {
                subsongName = "Subsong " + juce::String(subsongIndex + 1);
            }
            subsongBuilder.setMetadata(subsongName, subsongMetadata.getInitialSpeed(), subsongMetadata.getReplayFrequencyHz(),
                subsongMetadata.getDigiChannel(), subsongMetadata.getHighlightSpacing(), subsongMetadata.getSecondaryHighlight());
        } else {
            songBuilder->addError("Subsong " + juce::String(subsongIndex) + " has no metadata!");
            return false;
        }

        // Adds the patterns.
        if (auto it = subsongIndexToPatterns.find(subsongIndex); it != subsongIndexToPatterns.cend()) {
            subsongBuilder.addPatterns(it->second);
        } else {
            songBuilder->addError("Subsong " + juce::String(subsongIndex) + " has no patterns! Abnormal!");
            return false;
        }

        // Adds the positions.
        auto subsongLength = 0;
        if (auto it = subsongIndexToPositions.find(subsongIndex); it != subsongIndexToPositions.cend()) {
            const auto& positions = it->second;
            subsongBuilder.addPositions(positions);
            subsongLength = static_cast<int>(positions.size());
        } else {
            songBuilder->addError("Subsong " + juce::String(subsongIndex) + " has no positions! Abnormal!");
            return false;
        }

        // Adds the tracks.
        for (const auto& entry: subsongIndexAndChannelIndexAndTrackIndexAndTrack) {
            if (subsongIndex != std::get<0>(entry)) {   // Only the current Subsong interests us!
                continue;
            }

            const auto channelIndex = std::get<1>(entry);
            const auto baseTrackIndex = std::get<2>(entry);
            const auto& track = std::get<3>(entry);

            // Adds the Tracks.
            // The track index must be "transposed" to each channel!
            if (subsongIndexToOrderLength.find(subsongIndex) == subsongIndexToOrderLength.cend()) {     // Sanity check.
                songBuilder->addError("Subsong " + juce::String(subsongIndex) + " was not set the order length!");
                return false;
            }
            const auto orderLength = subsongIndexToOrderLength.at(subsongIndex);
            const auto trackIndex = baseTrackIndex + (channelIndex * orderLength);

            subsongBuilder.setTrack(trackIndex, track);
        }

        subsongBuilder.setLoop(0, subsongLength - 1);

        songBuilder->finishCurrentSubsong();
    }

    return true;
}

bool FurnaceImporter::readFlagBlock(juce::InputStream& inputStream)
{
    // Some default values.
    auto chipType = 0;      // 0 = AY.
    constexpr auto cpcSelector = 5;
    auto clockSelector = cpcSelector;
    auto customFrequencyHz = 0;       // 0 means unused.

    const auto rawString = inputStream.readString();
    //DBG("FLAGS = " + rawString);

    // Separated by "0xa".
    // chipType=0           0=AY, 1=YM, may be others.
    // clockSel=0           2=1.75mHz 3=2mHz 4=1.5 mHz, 5=1mHz, 6=0.89mHz, 8=0.83mHz 9=1.10 13=1.25 14=1.536s
    // customClock=0
    const auto strings = StringUtil::split(rawString, "\n");
    for (const auto& string : strings) {
        const auto tagAndValue = StringUtil::split(string, "=");
        if (tagAndValue.size() == 2) {
            const auto& tag = tagAndValue[0];
            const auto& value = tagAndValue[1];
            if (tag == "chipType") {
                chipType = value.getIntValue();
            } else if (tag == "clockSel") {
                clockSelector = value.getIntValue();
            } else if (tag == "customClock") {          // Present even a clockSel is present.
                customFrequencyHz = value.getIntValue();
            }
        } else {
            jassertfalse;       // Wrong format?
        }
    }

    // Determines the chip frequency from stupidly encoded values.
    auto chipFrequencyHz = PsgFrequency::psgFrequencyCPC;
    switch (clockSelector) {
        case 0:
            chipFrequencyHz = PsgFrequency::psgFrequencyMsxAndSvi;
            break;
        case 1:
            chipFrequencyHz = PsgFrequency::psgFrequencySpectrum;
            break;
        case 2:
            chipFrequencyHz = PsgFrequency::psgFrequencyPentagon128K;
            break;
        case 3:
            chipFrequencyHz = PsgFrequency::psgFrequencyAtariST;
            break;
        case 4:
            chipFrequencyHz = PsgFrequency::psgFrequencyVectrex;
            break;
        case cpcSelector:
            chipFrequencyHz = PsgFrequency::psgFrequencyCPC;
            break;
        case 6:
            chipFrequencyHz = 890000;
            break;
        case 8:
            chipFrequencyHz = 830000;
            break;
        case 9:
            chipFrequencyHz = 1100000;
            break;
        case 13:
            chipFrequencyHz = 1250000;
            break;
        case 14:
            chipFrequencyHz = 1536000;
            break;
        default:
            jassertfalse;       // Not managed?
            break;
    }
    // Overrides if custom frequency present.
    if (customFrequencyHz > 0) {
        chipFrequencyHz = customFrequencyHz;
    }

    // PsgType?
    const auto psgType = (chipType == 1) ? PsgType::ym : PsgType::ay;

    // Replaces the already existing PSG (only the reference freq was correctly set).
    const auto psgIndex = static_cast<size_t>(flagChunkCount);
    if (psgIndex < psgs.size()) {
        const auto& oldPsg = psgs.at(psgIndex);
        psgs[psgIndex] = Psg(psgType, chipFrequencyHz, oldPsg.getReferenceFrequency());
    } else {
        songBuilder->addWarning("PSG " + juce::String(psgIndex) + " was not found!");
        jassertfalse;
    }

    ++flagChunkCount;           // All subsongs have the same PSG count.

    return true;
}

bool FurnaceImporter::readSubsongBlock(juce::InputStream& inputStream, const int blockSize)
{
    ++subsongCountFromBlocks;

    const auto subsongIndex = subsongCountFromBlocks - 1;
    const auto currentPositionInStream = inputStream.getPosition();

    inputStream.skipNextBytes(1);       // Time base.
    const auto speed1 = static_cast<int>(static_cast<unsigned char>(inputStream.readByte()));
    inputStream.skipNextBytes(2);       // Speed 2, initial arpeggio time.
    const auto playerFrequencyHz = inputStream.readFloat();
    inputStream.skipNextBytes(2);       // Pattern length.
    const auto orderLength = inputStream.readShort();
    const auto readHighlight1 = inputStream.readByte();
    const auto readHighlight2 = inputStream.readByte();
    inputStream.skipNextBytes(4);       // Tempo num/den.

    const auto subsongName = inputStream.readString();
    inputStream.readString();           // Subsong comment.

    // Stores the data for later!
    const auto [highlight1, highlight2] = calculateHighlights(readHighlight1, readHighlight2);
    const Subsong::Metadata metadata(subsongName, speed1, playerFrequencyHz, 1, highlight1, highlight2,
        0, 0, SidPlayerCapability::buildForCpc());
    subsongIndexToMetadata.insert(std::make_pair(subsongIndex, metadata));

    // Reads the patterns/positions.
    readAndStoreOrder(subsongIndex, inputStream, orderLength);

    // Skips the remaining data.
    inputStream.skipNextBytes(blockSize - (inputStream.getPosition() - currentPositionInStream));

    return true;
}

void FurnaceImporter::readAndStoreOrder(const int subsongIndex, juce::InputStream& inputStream, const int orderLength)
{
    subsongIndexToOrderLength.insert({ subsongIndex, orderLength });    // Needed later.

    const auto channelCount = originalSongChannelCount;
    // We may need more channels!
    const auto psgCount = PsgValues::getPsgCount(channelCount);
    const auto finalChannelCount = PsgValues::getChannelCount(psgCount);

    // Reads the order, PER channel.
    const auto orderDataLength = channelCount * orderLength;
    juce::MemoryBlock orderData;
    inputStream.readIntoMemoryBlock(orderData, orderDataLength);

    std::vector<Pattern> patterns;
    auto lastTrackIndex = 0;
    for (auto patternIndex = 0; patternIndex < orderLength; ++patternIndex) {
        Pattern pattern;
        for (auto channelIndex = 0; channelIndex < channelCount; ++channelIndex) {
            // This is the track index for *this* channel. The other channels cannot access it!
            // So in AT, other channels' tracks must be mapped after.
            const auto channelTrackIndex = static_cast<unsigned char>(orderData[(channelIndex * orderLength) + patternIndex]);
            const auto trackIndex = channelTrackIndex + (channelIndex * orderLength);
            pattern.addTrackIndex(trackIndex, { });

            lastTrackIndex = std::max(lastTrackIndex, trackIndex);
        }
        // Fills for more channels if needed, with a last track.
        // No need to create it, it seems.
        const auto emptyTrackIndex = lastTrackIndex + 1;
        for (auto channelIndex = channelCount; channelIndex < finalChannelCount; ++channelIndex) {
            pattern.addTrackIndex(emptyTrackIndex, { });
        }

        patterns.emplace_back(pattern);
    }

    // Creates the positions. One per pattern!
    std::vector<Position> positions;
    positions.reserve(static_cast<size_t>(orderLength));
    for (auto patternIndex = 0; patternIndex < orderLength; ++patternIndex) {
        positions.emplace_back(patternIndex);
    }

    // Stores them for later.
    subsongIndexToPatterns.insert(std::make_pair(subsongIndex, patterns));
    subsongIndexToPositions.insert(std::make_pair(subsongIndex, positions));
}

std::pair<int, int> FurnaceImporter::calculateHighlights(int readHighlight1, int readHighlight2) noexcept
{
    // Sanity check.
    readHighlight1 = std::max(1, readHighlight1);
    readHighlight2 = std::max(1, readHighlight2);

    const auto highlight2 = readHighlight2 / readHighlight1;
    return { readHighlight1, highlight2 };
}

}   // namespace arkostracker
