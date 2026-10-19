#include "../../catch.hpp"

#include <unordered_set>

#include "../../../source/business/instrument/GenerateInstrument.h"
#include "../../../source/business/instrument/GenericInstrumentGenerator.h"
#include "../../../source/utils/NoteUtil.h"
#include "../../controllers/SongControllerForTest.h"
#include "../../helper/SongTestHelper.h"
#include "../../helper/TrackTestHelper.h"

namespace arkostracker
{

class TestHelper
{

public:
    static std::unique_ptr<Song> buildSong(const int firstNoteLine, const Cell& firstCell)
    {
        auto song = SongTestHelper::createSong();
        song->addInstrument(Instrument::buildEmptyPsgInstrument());
        song->addInstrument(GenericInstrumentGenerator::generateInstrumentForDecreasingVolume()); // 1.

        {
            auto& arpeggioHandler = song->getExpressionHandler(true);
            arpeggioHandler.addExpression(Expression(true));
            auto& pitchHandler = song->getExpressionHandler(false);
            pitchHandler.addExpression(Expression(false));
        }

        SongTestHelper::addSubsong(*song, 1, 5, 0, 1,
                                   {
                                       Position(0, 64),
                                   },
                                   {
                                       Pattern({ 0, 1, 2 }, 0, 0),
                                   },
                                   {
                                       // Track 0.
                                       TrackTestHelper::buildTrack({ }),
                                       // Track 1.
                                       TrackTestHelper::buildTrack({
                                           {
                                               firstNoteLine, firstCell
                                           },
                                           {
                                               firstNoteLine + 1, Cell::build(5 * 12, 1)
                                           },
                                       }),
                                       // Track 2.
                                       TrackTestHelper::buildTrack({ }),
                                   },
                                   {
                                       // Speed Track 0.
                                       TrackTestHelper::buildSpecialTrack({ }),
                                   },
                                   {
                                       // Event Track 0.
                                       TrackTestHelper::buildSpecialTrack({ }),
                                   }
        );
        REQUIRE((song != nullptr));

        return song;
    }
};

TEST_CASE("GenerateInstrument, using periods", "[GenerateInstrument]")
{
    // Given.
    constexpr auto firstLine = 3;
    constexpr auto lastLine = 5;
    constexpr auto channelIndex = 1;
    const auto instrumentName = juce::String("Instr");
    constexpr auto encodeWithPeriods = true;
    constexpr auto positionIndex = 0;

    const auto firstCell = Cell::build(4 * 12, 1, CellEffects({
        { Effect::pitchUp, 0x80 }
    }));

    auto originalSong = TestHelper::buildSong(firstLine, firstCell);
    const auto subsongId = originalSong->getFirstSubsongId();
    const std::shared_ptr song = std::move(originalSong);

    const SongControllerForTest songController(song);

    // When.
    const auto result = GenerateInstrument::generateInstrument(songController, subsongId, positionIndex,
                                                               firstLine, lastLine, channelIndex, instrumentName, encodeWithPeriods);

    // Then.
    REQUIRE((result != nullptr));
    const auto& instrument = *result;
    REQUIRE((instrument.getName() == instrumentName));
    REQUIRE((instrument.getType() == InstrumentType::psgInstrument));
    const auto& psgPart = instrument.getConstPsgPart();
    constexpr auto length = 15;
    REQUIRE((psgPart.getMainLoop() == Loop(0, length - 1, false)));
    REQUIRE((psgPart.getLength() == length));

    const std::vector<std::pair<int, int>> volumeAndPeriod = {
        { 15, 238 },
        { 14, 238 },
        { 13, 237 },
        { 12, 237 },
        { 11, 236 },

        { 15, 119 },
        { 14, 119 },
        { 13, 119 },
        { 12, 119 },
        { 11, 119 },

        { 10, 119 },
        { 9, 119 },
        { 8, 119 },
        { 7, 119 },
        { 6, 119 },
    };

    auto cellIndex = 0;
    for (const auto& [volume, period] : volumeAndPeriod) {
        const auto& cell = psgPart.getCellRefConst(cellIndex);
        REQUIRE((cell.getLink() == PsgInstrumentCellLink::softOnly));
        REQUIRE((cell.getPrimaryPeriod() == period));
        REQUIRE((cell.getVolume() == volume));

        ++cellIndex;
    }
}

TEST_CASE("GenerateInstrument, using notes and shifts", "[GenerateInstrument]")
{
    // Given.
    constexpr auto firstLine = 3;
    constexpr auto lastLine = 5;
    constexpr auto channelIndex = 1;
    const auto instrumentName = juce::String("Instr");
    constexpr auto encodeWithPeriods = false;
    constexpr auto positionIndex = 0;

    const auto firstCell = Cell::build(4 * 12, 1, CellEffects({
        { Effect::arpeggio4Notes, 0x37c }
    }));
    auto originalSong = TestHelper::buildSong(firstLine, firstCell);
    const auto subsongId = originalSong->getFirstSubsongId();
    const std::shared_ptr song = std::move(originalSong);

    const SongControllerForTest songController(song);

    // When.
    const auto result = GenerateInstrument::generateInstrument(songController, subsongId, positionIndex,
                                                               firstLine, lastLine, channelIndex, instrumentName, encodeWithPeriods);

    // Then.
    REQUIRE((result != nullptr));
    const auto& instrument = *result;
    REQUIRE((instrument.getName() == instrumentName));
    REQUIRE((instrument.getType() == InstrumentType::psgInstrument));
    const auto& psgPart = instrument.getConstPsgPart();
    constexpr auto length = 15;
    REQUIRE((psgPart.getMainLoop() == Loop(0, length - 1, false)));
    REQUIRE((psgPart.getLength() == length));

    const std::vector<std::pair<int, int>> volumeAndArpeggioNote = {
        { 15, 0 },
        { 14, 3 },
        { 13, 7 },
        { 12, 12 },
        { 11, 0 },

        { 15, 0 + 12 },
        { 14, 3 + 12 },
        { 13, 7 + 12 },
        { 12, 12 + 12 },
        { 11, 0 + 12 },

        { 10, 3 + 12 },
        { 9, 7 + 12 },
        { 8, 12 + 12 },
        { 7, 0 + 12 },
        { 6, 3 + 12 },
    };

    auto cellIndex = 0;
    for (const auto& [volume, arpeggioNote] : volumeAndArpeggioNote) {
        const auto& cell = psgPart.getCellRefConst(cellIndex);
        REQUIRE((cell.getLink() == PsgInstrumentCellLink::softOnly));
        const auto [noteInOctave, octave] = NoteUtil::getNoteInOctaveAndOctave(arpeggioNote);
        REQUIRE((cell.getPrimaryArpeggioNoteInOctave() == noteInOctave));
        REQUIRE((cell.getPrimaryArpeggioOctave() == octave));
        REQUIRE((cell.getVolume() == volume));

        ++cellIndex;
    }
}

} // namespace arkostracker
