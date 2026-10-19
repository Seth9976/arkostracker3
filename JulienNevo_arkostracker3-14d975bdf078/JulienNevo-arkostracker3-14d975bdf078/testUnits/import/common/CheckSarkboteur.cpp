#include "CheckSarkboteur.h"

#include "../../../source/song/Song.h"
#include "../../catch.hpp"

namespace arkostracker 
{

void CheckSarkboteur::check(const Song& song, bool /*isNative*/)
{
    // Checks the Song.
    REQUIRE(song.getTitle() == "Sarkboteur");
    REQUIRE(song.getAuthor() == "Targhan");
    REQUIRE(song.getComposer() == "Rob Hubbard");
    REQUIRE(song.getComments() == "\"Vanity are the best!\". I had to say that to be allowed by Hicks to use this song in the Arkos Tracker 2 package :).");
    REQUIRE(song.getSubsongCount() == 1);

    // Checks the Arpeggios.
    // ---------------------------------------------
    {
        //const auto& handler = song.getConstExpressionHandler(true);
        //REQUIRE(handler.getCount() == 3);
        // TODO
        /*{
            const auto expression = handler.getExpressionCopy(handler.find(0).getValue());
            REQUIRE(expression.getSpeed() == 0);
            REQUIRE(expression.getLength() == 1);
            REQUIRE(expression.getShift() == 0);
            REQUIRE(expression.getLoop() == Loop(0, 0, true));
            REQUIRE(expression.getValue(0) == 0);
        }*/
    }

    // Checks the Pitches.
    // ---------------------------------------------
    {
        //const auto& handler = song.getConstExpressionHandler(false);
        // TODO
        //REQUIRE(handler.getCount() == 2);
        /*{
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
        }*/
    }

    // Checks the Instruments.
    // ---------------------------------------------
    REQUIRE(song.getInstrumentCount() == 18);
    // Instrument 0 (empty).
    /*song.performOnConstPsgInstrument(song.getInstrumentId(0).getValue(), [&](const Instrument& instrument, const PsgPart& psgPart) {
        REQUIRE(instrument.getType() == InstrumentType::psgInstrument);
        REQUIRE(psgPart.getLength() == 1);
        REQUIRE(psgPart.getSpeed() == 0);
        REQUIRE(psgPart.getMainLoop() == Loop(0, 0, true));
        {
            const auto& cell = psgPart.getCellRefConst(0);
            REQUIRE(cell.isEmpty());
        }
    });*/

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

            const auto& pattern = subsong.getPatternFromIndex(expectedPatternIndex);
            REQUIRE(pattern.getChannelCount() == 3);
            REQUIRE(pattern.getCurrentTrackIndex(0) == 1);
            REQUIRE(pattern.getCurrentTrackIndex(1) == 4);
            REQUIRE(pattern.getCurrentTrackIndex(2) == 47);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(true) == 0);
            REQUIRE(pattern.getCurrentSpecialTrackIndex(false) == 0);
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(0).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(1).isLinked());
            REQUIRE_FALSE(pattern.getTrackIndexAndLinkedTrackIndex(2).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(true).isLinked());
            REQUIRE_FALSE(pattern.getSpecialTrackIndexAndLinkedTrackIndex(false).isLinked());
            REQUIRE(pattern.getArgbColor() == LookAndFeelConstants::defaultPatternColor);

            //const auto& track = subsong.getTrackRefFromIndex(0);
            //REQUIRE(track.getCell(0) == Cell(Note::buildNote(23), 1));
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
            const auto expected = std::vector<std::pair<int, SpecialCell>> {
                    { 0, SpecialCell::buildSpecialCell(4) },
                    { 2, SpecialCell::buildSpecialCell(6) },
                    { 4, SpecialCell::buildSpecialCell(5) },
                    { 7, SpecialCell::buildSpecialCell(4) },
                    { 0xa, SpecialCell::buildSpecialCell(4) },
                    { 0xc, SpecialCell::buildSpecialCell(5) },
                    { 0xe, SpecialCell::buildSpecialCell(7) },
                    { 0x10, SpecialCell::buildSpecialCell(4) },
                    { 0x12, SpecialCell::buildSpecialCell(7) },
                    { 0x14, SpecialCell::buildSpecialCell(5) },
                    { 0x17, SpecialCell::buildSpecialCell(4) },
                    { 0x1a, SpecialCell::buildSpecialCell(6) },
                    { 0x1c, SpecialCell::buildSpecialCell(5) },
                    { 0x1e, SpecialCell::buildSpecialCell(5) },
                    { 0x1f, SpecialCell::buildSpecialCell(5) },
            };
            REQUIRE(cells == expected);
        }
    });
}


}   // namespace arkostracker

