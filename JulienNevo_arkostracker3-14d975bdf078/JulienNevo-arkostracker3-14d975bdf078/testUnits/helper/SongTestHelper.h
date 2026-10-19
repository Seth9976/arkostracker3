#pragma once

#include "../../source/song/Song.h"

namespace arkostracker
{

class SongTestHelper
{
public:
    /** Prevents instantiation. */
    SongTestHelper() = delete;

    static std::unique_ptr<Song> createSong() noexcept;
    /** Adds a Subsong to a Song, return a reference to it for testing. */
    static const Subsong& addSubsong(Song& song, int psgCount, int initialSpeed, int loopStartPosition, int endPosition, const std::vector<Position>& positions,
                         const std::vector<Pattern>& patterns, const std::vector<Track>& tracks,
                         const std::vector<SpecialTrack>& speedTracks, const std::vector<SpecialTrack>& eventTracks) noexcept;

    /** @return a Subsong from the given parameters. */
    static std::unique_ptr<Subsong> createSubsong(int psgCount, int initialSpeed, int loopStartPosition, int endPosition, const std::vector<Position>& positions,
                         const std::vector<Pattern>& patterns, const std::vector<Track>& tracks,
                         const std::vector<SpecialTrack>& speedTracks, const std::vector<SpecialTrack>& eventTracks) noexcept;

    /** This does NOT lock. */
    static bool areSongMusicallyEqual(const Song& firstSong, const Song& secondSong) noexcept;

    /**
     * Loads a possibly ZIPped Song.
     * @return nullptr if an error occurred.
     */
    static std::shared_ptr<Song> loadSong(const char* inputSongData, size_t inputSongSize) noexcept;
};

}   // namespace arkostracker
