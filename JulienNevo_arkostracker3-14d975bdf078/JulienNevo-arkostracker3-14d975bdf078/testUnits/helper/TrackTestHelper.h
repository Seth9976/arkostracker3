#pragma once

#include <map>

#include "../../source/song/CellLocationInPosition.h"
#include "../../source/song/cells/Cell.h"
#include "../../source/song/tracks/SpecialTrack.h"
#include "../../source/song/tracks/Track.h"

namespace arkostracker
{

class Song;

/** Helper for testing Tracks/SpecialTracks. */
class TrackTestHelper
{
public:
    static constexpr auto noteF2 = (2 * 12) + 5;

    static constexpr auto noteB2 = (3 * 12) - 1;
    static constexpr auto noteA2 = (3 * 12) - 3;
    static constexpr auto noteAs2 = (3 * 12) - 2;
    static constexpr auto noteD3 = (3 * 12) + 2;
    static constexpr auto noteDs3 = (3 * 12) + 3;
    static constexpr auto noteE3 = (3 * 12) + 4;
    static constexpr auto noteFs3 = (3 * 12) + 6;
    static constexpr auto noteA3 = (3 * 12) + 9;

    static constexpr auto noteG2 = (2 * 12) + 7;
    static constexpr auto noteGs2 = (2 * 12) + 8;

    static constexpr auto noteC3 = (3 * 12) + 0;
    static constexpr auto noteG3 = (3 * 12) + 7;
    static constexpr auto noteB3 = (4 * 12) - 1;

    static constexpr auto noteC4 = (4 * 12) + 0;
    static constexpr auto noteCs4 = (4 * 12) + 1;
    static constexpr auto noteD4 = (4 * 12) + 2;
    static constexpr auto noteDs4 = (4 * 12) + 3;
    static constexpr auto noteE4 = (4 * 12) + 4;
    static constexpr auto noteF4 = (4 * 12) + 5;
    static constexpr auto noteG4 = (4 * 12) + 7;
    static constexpr auto noteA4 = (4 * 12) + 9;

    static constexpr auto noteF5 = (5 * 12) + 5;

    static constexpr auto noteC5 = (5 * 12) + 0;
    static constexpr auto noteB5 = (6 * 12) - 1;
    static constexpr auto noteA5 = (6 * 12) - 3;
    static constexpr auto noteG5 = (5 * 12) + 7;

    static constexpr auto noteA6 = (7 * 12) - 3;
    static constexpr auto noteD6 = (6 * 12) + 2;
    static constexpr auto noteDs6 = (6 * 12) + 3;
    static constexpr auto noteE6 = (6 * 12) + 4;
    static constexpr auto noteF6 = (6 * 12) + 5;
    static constexpr auto noteFs6 = (6 * 12) + 6;

    /** Prevents instantiation. */
    TrackTestHelper() = delete;

    /**
     * @return true if a Special Track contains only the given values.
     * @param specialTrack the Track to check.
     * @param indexToValue the indexes where to find specific values.
     */
    static bool containsOnly(const SpecialTrack& specialTrack, const std::map<int, int>& indexToValue) noexcept;

    /**
     * @return true if a Track contains only the given values.
     * @param track the Track to check.
     * @param indexToCell the indexes where to find specific Cells.
     */
    static bool containsOnly(const Track& track, const std::map<int, Cell>& indexToCell) noexcept;

    /**
     * @return a Track, with one note at the first cell (a note and an instrument).
     * @param note the note (>=0).
     * @param instrument the instrument (>=0).
     */
    static Track buildTestTrack(int note, int instrument = 1) noexcept;

    /** @return an empty Track. */
    static Track buildEmptyTrack() noexcept;

    /**
     * @return a Track, based on the given map.
     * @param indexToCell a map linking an line index to a Cell.
     */
    static Track buildTrack(const std::unordered_map<int, Cell>& indexToCell) noexcept;

    /** @return an empty SpecialTrack. */
    static SpecialTrack buildEmptySpecialTrack() noexcept;

    /**
     * @return a SpecialTrack, based on the given map.
     * @param indexToCell a map linking an line index to a Cell.
     */
    static SpecialTrack buildSpecialTrack(const std::unordered_map<int, SpecialCell>& indexToCell) noexcept;

    /**
     * @return true if the given Track has a first note that matches the given one.
     * @param track the track.
     * @param expectedNote the expected note (>=0).
     */
    static bool checkTestTrack(const Track& track, int expectedNote) noexcept;

    /**
     * @return a Special Track, with one value at the first cell.
     * @param value the value (>0, as 0 means "nothing").
     */
    static SpecialTrack buildTestSpecialTrack(int value) noexcept;
    /**
     * @return true if the given SpecialTrack has a first value that matches the given one.
     * @param track the track.
     * @param expectedValue the expected value (>0).
     */
    static bool checkTestSpecialTrack(const SpecialTrack& track, int expectedValue) noexcept;

    /**
     * Sets a Cell into a Song.
     * @param song the Song.
     * @param location where to put the Cell.
     * @param cell the Cell.
     */
    static void setCell(Song& song, const CellLocationInPosition& location, const Cell& cell) noexcept;
};

}   // namespace arkostracker
