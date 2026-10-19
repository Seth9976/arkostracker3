#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/builder/SongBuilder.h"
#include "../../../../../source/business/song/tool/sfx/FirstNotePerInstrumentFinder.h"

namespace arkostracker
{

TEST_CASE("FirstNotePerInstrumentFinder, harmless grenade", "[FirstNotePerInstrumentFinder]")
{
    // Given.
    SongBuilder songBuilder;

    songBuilder.startNewPsgInstrument(1);
    songBuilder.startNewPsgInstrumentCell();
    songBuilder.finishCurrentPsgInstrumentCell();
    songBuilder.finishCurrentInstrument();

    songBuilder.startNewSampleInstrument(2);
    songBuilder.setCurrentSampleInstrumentSample("aGVsbG8=");       // Hello
    songBuilder.finishCurrentInstrument();

    songBuilder.startNewPsgInstrument(3);       // Not exported.
    songBuilder.setCurrentPsgInstrumentSoundEffectExported(false);
    songBuilder.startNewPsgInstrumentCell();
    songBuilder.finishCurrentPsgInstrumentCell();
    songBuilder.finishCurrentInstrument();

    songBuilder.startNewPsgInstrument(4);       // Not found.
    songBuilder.startNewPsgInstrumentCell();
    songBuilder.finishCurrentPsgInstrumentCell();
    songBuilder.finishCurrentInstrument();

    songBuilder.startNewPsgInstrument(5);
    songBuilder.startNewPsgInstrumentCell();
    songBuilder.finishCurrentPsgInstrumentCell();
    songBuilder.finishCurrentInstrument();

    auto& subsongBuilder = songBuilder.startNewSubsong(0);
    subsongBuilder.addPsg(Psg::buildForCpc());

    // Positions.
    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(1);
    subsongBuilder.finishCurrentPosition();

    subsongBuilder.startNewPosition();
    subsongBuilder.setCurrentPositionPatternIndex(0);
    subsongBuilder.finishCurrentPosition();

    // Patterns. The most relevant info are here.
    subsongBuilder.startNewPattern(1);
    subsongBuilder.setCurrentPatternTrackIndex(0, 3);
    subsongBuilder.setCurrentPatternTrackIndex(1, 4);
    subsongBuilder.setCurrentPatternTrackIndex(2, 5);
    subsongBuilder.finishCurrentPattern();

    subsongBuilder.startNewPattern(0);
    subsongBuilder.setCurrentPatternTrackIndex(0, 0);
    subsongBuilder.setCurrentPatternTrackIndex(1, 1);
    subsongBuilder.setCurrentPatternTrackIndex(2, 2);
    subsongBuilder.finishCurrentPattern();

    // Instrument 1 is declared several times, but the first seen value matters.
    subsongBuilder.setCellOnTrack(3, 20, Cell::build(5 * 12, 1));
    subsongBuilder.setCellOnTrack(4, 20, Cell::build(5 * 12 + 5, 1));
    subsongBuilder.setCellOnTrack(5, 21, Cell::build(5 * 12 + 6, 1));
    subsongBuilder.setCellOnTrack(0, 10, Cell::build(6 * 12, 1));

    // Instrument 2 is a sample.
    subsongBuilder.setCellOnTrack(1, 50, Cell::build(6 * 12, 2));

    // Instrument 3 is a present but not exported.
    subsongBuilder.setCellOnTrack(2, 8, Cell::build(20, 3));

    // Instrument 4 is not found.

    // Instrument 5 is declared twice, but the first seen value matters.
    subsongBuilder.setCellOnTrack(1, 30, Cell::build(77, 5));
    subsongBuilder.setCellOnTrack(2, 31, Cell::build(79, 5));

    subsongBuilder.addPositions( {
        Position(1),
        Position(0),
    });
    subsongBuilder.setLoop(0, 1);

    songBuilder.finishCurrentSubsong();

    auto buildResult = songBuilder.buildSong();
    REQUIRE(buildResult.second->isOk());

    auto& song = buildResult.first;
    REQUIRE(song != nullptr);

    // When.
    const auto findResult = FirstNotePerInstrumentFinder::find(*song);
    REQUIRE(findResult.size() == 4U);
    {
        // Instrument 1 is found and exported.
        const auto& findItem = findResult.at(1);
        REQUIRE(findItem.canUseUsed());
        REQUIRE(findItem.isExported());
        REQUIRE(findItem.getFoundNote().isPresent());
        REQUIRE(findItem.getFoundNote().getValue() == (5 * 12));
    }
    {
        // Instrument 2 is a sample.
        REQUIRE(findResult.find(2) == findResult.cend());
    }
    {
        // Instrument 3 is found but not exported.
        const auto& findItem = findResult.at(3);
        REQUIRE_FALSE(findItem.canUseUsed());
        REQUIRE_FALSE(findItem.isExported());
        REQUIRE(findItem.getFoundNote().isPresent());
        REQUIRE(findItem.getFoundNote().getValue() == 20);
    }
    {
        // Instrument 4 is not found.
        const auto& findItem = findResult.at(4);
        REQUIRE_FALSE(findItem.canUseUsed());
        REQUIRE(findItem.isExported());
        REQUIRE(findItem.getFoundNote().isAbsent());
    }
    {
        // Instrument 5 is found and exported.
        const auto& findItem = findResult.at(5);
        REQUIRE(findItem.canUseUsed());
        REQUIRE(findItem.isExported());
        REQUIRE(findItem.getFoundNote().isPresent());
        REQUIRE(findItem.getFoundNote().getValue() == 77);
    }
}

}   // namespace arkostracker
