#pragma once

#include "../SongImporter.h"
#include "../../business/song/tool/builder/SongBuilder.h"

namespace arkostracker
{

/** Importer of a Furnace song. */
class FurnaceImporter : public SongImporter
{
public:
    /** Constructor. */
    FurnaceImporter();

    // SongImporter method implementations.
    // =======================================
    bool doesFormatMatch(juce::InputStream& inputStream, const juce::String& extension) const noexcept override;
    std::unique_ptr<Result> loadSong(juce::InputStream& inputStream, const ImportConfiguration& configuration) noexcept override;
    ImportedFormat getFormat() noexcept override;

private:
    static const juce::String headerTag;                            // Tag to identify the song format.
    static const int minimumFormatNumber;
    static const int maximumFormatNumber;

    static const std::unordered_map<unsigned char, int> chipIdToChannelCount;

    /** Reads the old "INFO" block, and returns true if success. */
    bool readOldInfoBlock(juce::InputStream& inputStream, int blockSize);

    /** Reads a track, stores it in case they are not stored by subsongs. */
    bool readTrack(juce::InputStream& inputStream);

    /** Reads the chip flags. */
    bool readFlagBlock(juce::InputStream& inputStream);

    /** Builds all the subsongs, from the already known patterns. */
    bool buildSubsongsAndPatterns();

    /** Reads the Subsong block and stores its data for later. */
    bool readSubsongBlock(juce::InputStream& inputStream, int blockSize);

    /** Reads the order, storing the patterns and positions into the internal maps for the given Subsong index. */
    void readAndStoreOrder(int subsongIndex, juce::InputStream& inputStream, int orderLength);

    /** @return the AT3 highlights from the ones read in the original format. */
    static std::pair<int, int> calculateHighlights(int readHighlight1, int readHighlight2) noexcept;

    std::unique_ptr<SongBuilder> songBuilder;

    juce::int16 formatNumber;
    int currentInstrumentIndex;
    int originalSongChannelCount;
    std::vector<Psg> psgs;                              // Common to all subsongs.

    int flagChunkCount;
    std::map<int, int> subsongIndexToOrderLength;        // Necessary because tracks indexes are "by channels".
    std::vector<std::tuple<int, int, int, Track>> subsongIndexAndChannelIndexAndTrackIndexAndTrack;
    std::map<int, std::vector<Pattern>> subsongIndexToPatterns;
    std::map<int, std::vector<Position>> subsongIndexToPositions;

    std::map<int, Subsong::Metadata> subsongIndexToMetadata;

    int subsongCountFromBlocks;                         // Increases as INFO/SONG are discovered.
};

}   // namespace arkostracker
