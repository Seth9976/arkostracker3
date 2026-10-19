#include "CheckHarmlessGrenade.h"

#include "../../../source/song/Song.h"
#include "../../catch.hpp"
#include "../../../source/song/instrument/psg/PsgPartConstants.h"

namespace arkostracker 
{

void CheckHarmlessGrenade::check(const Song& song)
{
    // Checks the Song.
    REQUIRE(song.getTitle() == "A Harmless Grenade");
    REQUIRE(song.getAuthor() == "Targhan");
    REQUIRE(song.getComposer() == "Targhan");
    REQUIRE(song.getComments() == "Some fun with Arkos Tracker 2!");
    REQUIRE(song.getSubsongCount() == 1);

    // Checks the Arpeggios.
    // ---------------------------------------------
    {
        const auto& handler = song.getConstExpressionHandler(true);
        REQUIRE(handler.getCount() == 3);
        {
            const auto expression = handler.getExpressionCopy(handler.find(0).getValue());
            REQUIRE(expression.getSpeed() == 0);
            REQUIRE(expression.getLength() == 1);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLoop() == Loop(0, 0, true));
            REQUIRE(expression.getValue(0) == 0);
        }
        {
            const auto expression = handler.getExpressionCopy(handler.find(1).getValue());
            REQUIRE(expression.getName() == "Arpic");
            REQUIRE(expression.getSpeed() == 0);
            REQUIRE(expression.getLength() == 5);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLoop() == Loop(0, 4, true));
            REQUIRE(expression.getValue(0) == 0);
            REQUIRE(expression.getValue(1) == 12);
            REQUIRE(expression.getValue(2) == 9);
            REQUIRE(expression.getValue(3) == -12);
            REQUIRE(expression.getValue(4) == (6 + 12));
        }
        {
            const auto expression = handler.getExpressionCopy(handler.find(2).getValue());
            REQUIRE(expression.getName() == "Strange");
            REQUIRE(expression.getSpeed() == 0);
            REQUIRE(expression.getLength() == 7);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLoop() == Loop(0, 6, true));
            REQUIRE(expression.getValue(0) == 0);
            REQUIRE(expression.getValue(1) == 6);
            REQUIRE(expression.getValue(2) == -3);
            REQUIRE(expression.getValue(3) == -12);
            REQUIRE(expression.getValue(4) == -6);
            REQUIRE(expression.getValue(5) == 0);
            REQUIRE(expression.getValue(6) == 12);
        }
    }

    // Checks the Pitches.
    // ---------------------------------------------
    {
        const auto& handler = song.getConstExpressionHandler(false);
        REQUIRE(handler.getCount() == 2);
        {
            auto expression = handler.getExpressionCopy(handler.find(0).getValue());
            REQUIRE(expression.getSpeed() == 0);
            REQUIRE(expression.getLength() == 1);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLoop() == Loop(0, 0, true));
            REQUIRE(expression.getValue(0) == 0);
        }
        {
            const auto expression = handler.getExpressionCopy(handler.find(1).getValue());
            REQUIRE(expression.getName() == "Strange vibrato");
            REQUIRE(expression.getSpeed() == 1);
            REQUIRE(expression.getLength() == 6);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLoop() == Loop(2, 5, true));
            REQUIRE(expression.getValue(0) == 0);
            REQUIRE(expression.getValue(1) == 0);
            REQUIRE(expression.getValue(2) == 0);
            REQUIRE(expression.getValue(3) == 1);
            REQUIRE(expression.getValue(4) == 4);
            REQUIRE(expression.getValue(5) == -2);
        }
    }

    // Checks the Instruments.
    // ---------------------------------------------
    REQUIRE(song.getInstrumentCount() == 20);
    // Instrument 0 (empty).
    song.performOnConstPsgInstrument(song.getInstrumentId(0).getValue(), [&](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(psgPart.getLength() == 1);
        REQUIRE(psgPart.getSpeed() == PsgPartConstants::slowestSpeed);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
        {
            const auto& cell = psgPart.getCellRefConst(0);
            REQUIRE(cell.isEmpty());
        }
    });
    // Instrument 1.
    song.performOnConstPsgInstrument(song.getInstrumentId(1).getValue(), [&](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "HardAttack");
        REQUIRE(psgPart.getLength() == 9);
        REQUIRE(psgPart.getSpeed() == 1);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 8, false));
        auto index = -1;
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softToHard);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 1);
            REQUIRE(cell.getRatio() == 5);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getHardwareEnvelope() == 8);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softToHard);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 1);
            REQUIRE(cell.getRatio() == 3);
            REQUIRE(cell.getHardwareEnvelope() == 8);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softToHard);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 1);
            REQUIRE(cell.getRatio() == 3);
            REQUIRE(cell.getHardwareEnvelope() == 8);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softToHard);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getRatio() == 5);
            REQUIRE(cell.getHardwareEnvelope() == 8);
            REQUIRE_FALSE(cell.isRetrig());
        }

        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 0xa);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 1);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 0xa);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 0xa);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 1);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 9);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 8);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE_FALSE(cell.isRetrig());
        }
    });
    // Instrument 2.
    song.performOnConstPsgInstrument(song.getInstrumentId(2).getValue(), [&](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(instrument.getName() == "BD");
        REQUIRE(psgPart.getLength() == 11);
        REQUIRE(psgPart.getSpeed() == 0);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 7, false));
        auto index = -1;
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 15);
            REQUIRE(cell.getNoise() == 2);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == 0);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 15);
            REQUIRE(cell.getNoise() == 1);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == -0x20);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 15);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == -0x30);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 15);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == -0x44);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 15);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == -0x74);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 15);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == -0xe4);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 14);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == -0xb4);
            REQUIRE_FALSE(cell.isRetrig());
        }
        {
            const auto& cell = psgPart.getCellRefConst(++index);
            REQUIRE(cell.getLink() == PsgInstrumentCellLink::softOnly);
            REQUIRE(cell.getVolume() == 13);
            REQUIRE(cell.getNoise() == 0);
            REQUIRE(cell.getPrimaryArpeggioNoteInOctave() == 0);
            REQUIRE(cell.getPrimaryArpeggioOctave() == 0);
            REQUIRE(cell.getPrimaryPitch() == -0x124);
            REQUIRE_FALSE(cell.isRetrig());
        }
    });
    // TODO Continues the test.

    song.performOnConstSubsong(song.getFirstSubsongId(), [&](const Subsong& subsong) {
        {
            REQUIRE(subsong.getPsgCount() == 1);
            const auto& psgs = subsong.getPsgRefs();
            const auto& psg = psgs.at(0);
            REQUIRE(psg.getType() == PsgType::ay);
            REQUIRE(psg.getPsgFrequency() == 1000000);
            REQUIRE(juce::exactlyEqual(psg.getReferenceFrequency(), 440.0F));
            REQUIRE(psg.getSamplePlayerFrequency() == 11025);
            REQUIRE(psg.getPsgMixingOutput() == PsgMixingOutput::ABC);

            const auto& position = subsong.getPosition(0);
            constexpr auto expectedPatternIndex = 0;
            REQUIRE(position.getHeight() == 32);
            REQUIRE(position.getPatternIndex() == expectedPatternIndex);
            REQUIRE(position.getTransposition(0) == 0);
            REQUIRE(position.getTransposition(1) == 0);
            REQUIRE(position.getTransposition(2) == 0);
            REQUIRE(position.getMarkerName() == Position::firstMarkerName);

            const auto& pattern = subsong.getPatternFromIndex(expectedPatternIndex);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 0);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 22);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 26);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
            REQUIRE(pattern.getArgbColor() == LookAndFeelConstants::defaultPatternColor);

            const auto& track = subsong.getTrackRefFromIndex(0);
            REQUIRE(track.getCell(0) == Cell(Note::buildNote(23), 1));
        }
    });

    // Checks the Linker.
    // ---------------------------------------------
    // TODO Tests.


    // Checks the Tracks.
    // ---------------------------------------------
    // TODO Tests.


    // Checks the Event Tracks.
    // ---------------------------------------------
    song.performOnConstSubsong(song.getFirstSubsongId(), [&](const Subsong& subsong) {
        {
            const auto& specialTrack = subsong.getSpecialTrackRefFromPosition(0, false);
            const auto cells = specialTrack.getNonEmptyItems();
            REQUIRE(cells.empty());
        }
    });
}


}   // namespace arkostracker

