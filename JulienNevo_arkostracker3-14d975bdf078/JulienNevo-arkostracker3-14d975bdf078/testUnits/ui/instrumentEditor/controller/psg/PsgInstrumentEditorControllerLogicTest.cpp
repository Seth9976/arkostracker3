#include "../../../../catch.hpp"

#include <memory>

#include "../../../../../source/ui/instrumentEditor/controller/psg/PsgInstrumentEditorControllerLogic.h"
#include "../../../../../source/utils/MainControllerNoOp.h"
#include "../../../../../source/controllers/SongControllerImpl.h"

namespace arkostracker 
{

TEST_CASE("checkValueAndChangeInstrumentCell, soft, no change", "[PsgInstrumentEditorControllerLogic]")
{
    // Given.
    // Simple instrument.
    PsgPart psgPart;
    {
        PsgInstrumentCell cell(PsgInstrumentCellLink::softOnly, 13, 12, 0x123, 1, -1, -4,
                               3, 0x8000, 3, 2, 15, 0x8, true,
                               PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                               PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        psgPart.addCell(cell);
    }
    auto instrument = Instrument::buildPsgInstrument("i1", psgPart);

    auto song = std::make_shared<Song>("song", "me", "me", juce::String(), true);
    song->addInstrument(std::move(instrument));

    MainControllerNoOp mainController;
    SongControllerImpl songController(mainController, song);

    // When/then.
    constexpr auto barIndex = 0;
    const auto instrumentId = song->getLastInstrumentId();

    // All the values are the same, so no change.
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::envelope, barIndex, 13, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::noise, barIndex, 12, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPeriod, barIndex, 0x123, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioNoteInOctave, barIndex, 1, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioOctave, barIndex, -1, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPitch, barIndex, -4, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPeriod, barIndex, 0x8000, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioNoteInOctave, barIndex, 3, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioOctave, barIndex, 2, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPitch, barIndex, 15, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
}

TEST_CASE("checkValueAndChangeInstrumentCell, hard, no change", "[PsgInstrumentEditorControllerLogic]")
{
    // Given.
    // Simple instrument.
    PsgPart psgPart;
    {
        PsgInstrumentCell cell(PsgInstrumentCellLink::softToHard, 13, 12, 0x123, 1, -1, -4,
                               3, 0x8000, 3, 2, 15, 0xa, true,
                               PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                               PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        psgPart.addCell(cell);
    }
    auto instrument = Instrument::buildPsgInstrument("i1", psgPart);

    auto song = std::make_shared<Song>("song", "me", "me", juce::String(), true);
    song->addInstrument(std::move(instrument));

    MainControllerNoOp mainController;
    SongControllerImpl songController(mainController, song);

    // When/then.
    constexpr auto barIndex = 0;
    const auto instrumentId = song->getLastInstrumentId();

    // All the values are the same, so no change.
    {
        // Envelope (starting at 8,a,c,e) * 8 + ratio.
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::envelope, barIndex, 1 * 8 + 3, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::noise, barIndex, 12, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPeriod, barIndex, 0x123, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioNoteInOctave, barIndex, 1, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioOctave, barIndex, -1, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPitch, barIndex, -4, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPeriod, barIndex, 0x8000, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioNoteInOctave, barIndex, 3, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioOctave, barIndex, 2, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPitch, barIndex, 15, songController, instrumentId);
        REQUIRE(newCell == nullptr);
    }
}

TEST_CASE("checkValueAndChangeInstrumentCell, simple, soft", "[PsgInstrumentEditorControllerLogic]")
{
    // Given.
    // Simple instrument.
    PsgPart psgPart;
    {
        PsgInstrumentCell cell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 2, 1, 0x40,
                               4, 0x4000, 1, -2, -50, 0x8, true,
                               PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                               PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        psgPart.addCell(cell);
    }
    auto instrument = Instrument::buildPsgInstrument("i1", psgPart);

    auto song = std::make_shared<Song>("song", "me", "me", juce::String(), true);
    song->addInstrument(std::move(instrument));

    MainControllerNoOp mainController;
    SongControllerImpl songController(mainController, song);

    // When/then.
    constexpr auto barIndex = 0;
    const auto instrumentId = song->getLastInstrumentId();


    // Changes one value.
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::envelope, barIndex, 10, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 10, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::noise, barIndex, 30, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 30, 0x123, 2, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPeriod, barIndex, 0x100, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x100, 2, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioNoteInOctave, barIndex, 0, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 0, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioOctave, barIndex, 2, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 2, 2, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
                PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
                PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPitch, barIndex, -12, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 2, 1, -12, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPeriod, barIndex, 0x1400, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 2, 1, 0x40, 4, 0x1400, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioNoteInOctave, barIndex, 11, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 11, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioOctave, barIndex, 0, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 1, 0, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPitch, barIndex, 148, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 13, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 1, -2, 148, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
}

TEST_CASE("checkValueAndChangeInstrumentCell, simple, hard", "[PsgInstrumentEditorControllerLogic]")
{
    // Given.
    // Simple instrument.
    PsgPart psgPart;
    {
        PsgInstrumentCell cell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 1, 0x40,
        4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        psgPart.addCell(cell);
    }
    auto instrument = Instrument::buildPsgInstrument("i1", psgPart);

    auto song = std::make_shared<Song>("song", "me", "me", juce::String(), true);
    song->addInstrument(std::move(instrument));

    MainControllerNoOp mainController;
    SongControllerImpl songController(mainController, song);

    // When/then.
    constexpr auto barIndex = 0;
    const auto instrumentId = song->getLastInstrumentId();

    // Changes one value.
    {
        // 0xC env (third wave) + ratio 5.
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::envelope, barIndex, 2 * 8 + 5, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 1, 0x40, 5, 0x4000, 1, -2, -50, 0xc, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::noise, barIndex, 30, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 30, 0x123, 2, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPeriod, barIndex, 0x100, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x100, 2, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioNoteInOctave, barIndex, 0, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 0, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryArpeggioOctave, barIndex, 2, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 2, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::primaryPitch, barIndex, -12, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 1, -12, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPeriod, barIndex, 0x1400, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 1, 0x40, 4, 0x1400, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioNoteInOctave, barIndex, 11, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 11, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryArpeggioOctave, barIndex, 0, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 1, 0, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
    {
        auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::secondaryPitch, barIndex, 148, songController, instrumentId);
        REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softAndHard, 13, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 1, -2, 148, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    }
}

TEST_CASE("checkValueAndChangeInstrumentCell, auto-spread", "[PsgInstrumentEditorControllerLogic]")
{
    // Given.
    // A bug was present:
    // Env is   15,1,1,1 with autospread 0->0 to on.
    // Noise is  0,0,0,0.
    // Changing the index 2 of noise to 31 to example, would ALSO make env at the index 2 env be equal to auto-spread value (15 as auto-spread is on).

    // Simple instrument.
    PsgPart psgPart;
    {
        PsgInstrumentCell cell0(PsgInstrumentCellLink::softOnly, 15, 0, 0x123, 2, 1, 0x40,
                               4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        PsgInstrumentCell cellOthers(PsgInstrumentCellLink::softOnly, 1, 0, 0x123, 2, 1, 0x40,
        4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
        psgPart.addCell(cell0);
        psgPart.addCell(cellOthers);
        psgPart.addCell(cellOthers);
        psgPart.addCell(cellOthers);

        psgPart.setAutoSpreadLoop(PsgSection::envelope, Loop(0, 0, true));
    }
    auto instrument = Instrument::buildPsgInstrument("i1", psgPart);

    auto song = std::make_shared<Song>("song", "me", "me", juce::String(), true);
    song->addInstrument(std::move(instrument));

    MainControllerNoOp mainController;
    SongControllerImpl songController(mainController, song);

    // When/then.
    const auto instrumentId = song->getLastInstrumentId();

    // Modifies the noise at index 2. The volume shouldn't change!!
    auto newCell = PsgInstrumentEditorControllerLogic::checkValueAndChangeInstrumentCell(AreaType::noise, 2, 31, songController, instrumentId);
    REQUIRE(*newCell == PsgInstrumentCell(PsgInstrumentCellLink::softOnly, 1, 31, 0x123, 2, 1, 0x40, 4, 0x4000, 1, -2, -50, 0x8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
            PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
}

}   // namespace arkostracker
