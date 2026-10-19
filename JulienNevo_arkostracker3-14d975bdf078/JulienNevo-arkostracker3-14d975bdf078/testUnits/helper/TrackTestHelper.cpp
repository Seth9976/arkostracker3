#include "TrackTestHelper.h"

#include "../../source/song/Song.h"

namespace arkostracker 
{

bool TrackTestHelper::containsOnly(const SpecialTrack& specialTrack, const std::map<int, int>& indexToValue) noexcept
{
    const auto size = specialTrack.getSize();
    for (auto cellIndex = 0; cellIndex < size; ++cellIndex) {
        const auto& cell = specialTrack.getCellRefConst(cellIndex);

        // Any expected value?
        auto iterator = indexToValue.find(cellIndex);
        if (iterator ==  indexToValue.cend()) {
            // The cell should be empty.
            if (!cell.isEmpty()) {
                return false;
            }
        } else {
            if (cell.getValue() != iterator->second) {
                return false;
            }
        }
    }

    return true;
}

bool TrackTestHelper::containsOnly(const Track& track, const std::map<int, Cell>& indexToCell) noexcept
{
    const auto size = track.getSize();
    for (auto cellIndex = 0; cellIndex < size; ++cellIndex) {
        const auto& cell = track.getCellRefConst(cellIndex);

        // Any expected value?
        auto iterator = indexToCell.find(cellIndex);
        if (iterator == indexToCell.cend()) {
            // The cell should be empty.
            if (!cell.isEmpty()) {
                DBG("CellIndex " + juce::String(cellIndex) + " should be empty!");
                jassertfalse;
                return false;
            }
        } else {
            if (cell != iterator->second) {
                DBG("CellIndex " + juce::String(cellIndex) + " is not the same!");
                jassertfalse;
                return false;
            }
        }
    }

    return true;
}

Track TrackTestHelper::buildTestTrack(const int note, const int instrument) noexcept
{
    Track track;
    track.setCell(0, Cell(Note::buildNote(note), instrument));

    return track;
}

bool TrackTestHelper::checkTestTrack(const Track& track, const int expectedNote) noexcept
{
    const auto note = track.getCell(0).getNote();
    if (note.isAbsent() || (note.getValue().getNote() != expectedNote)) {
        return false;
    }

    // Makes sure the other cells are empty.
    for (auto cellIndex = 1; cellIndex < track.getSize(); ++cellIndex) {
        if (!track.isCellEmpty(cellIndex)) {
            return false;
        }
    }

    return true;
}

SpecialTrack TrackTestHelper::buildTestSpecialTrack(const int value) noexcept
{
    jassert(value > 0);         // Are you sure you want no value??

    SpecialTrack specialTrack;
    specialTrack.setCell(0, SpecialCell::buildSpecialCell(value));

    return specialTrack;
}

bool TrackTestHelper::checkTestSpecialTrack(const SpecialTrack& track, const int expectedValue) noexcept
{
    const auto value = track.getCell(0).getValue();
    if (value != expectedValue) {
        return false;
    }

    // Makes sure the other cells are empty.
    for (auto cellIndex = 1; cellIndex < track.getSize(); ++cellIndex) {
        if (!track.isCellEmpty(cellIndex)) {
            return false;
        }
    }

    return true;
}

Track TrackTestHelper::buildEmptyTrack() noexcept
{
    return { };
}

Track TrackTestHelper::buildTrack(const std::unordered_map<int, Cell>& indexToCell) noexcept
{
    Track track;

    for (const auto& [index, cell] : indexToCell) {
        track.setCell(index, cell);
    }

    return track;
}

SpecialTrack TrackTestHelper::buildEmptySpecialTrack() noexcept
{
    return { };
}

SpecialTrack TrackTestHelper::buildSpecialTrack(const std::unordered_map<int, SpecialCell>& indexToCell) noexcept
{
    SpecialTrack track;

    for (const auto& [index, cell] : indexToCell) {
        track.setCell(index, cell);
    }

    return track;
}

void TrackTestHelper::setCell(Song& song, const CellLocationInPosition& location, const Cell& cell) noexcept
{
    song.performOnSubsong(location.getSubsongId(),[&] (Subsong& subsong) {
        subsong.setCell(location.getPositionIndex(), location.getLineIndex(), location.getChannelIndex(), cell);
    });
}

}   // namespace arkostracker
