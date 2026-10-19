#include "../catch.hpp"



#include "../../source/utils/NoteUtil.h"

namespace arkostracker 
{

TEST_CASE("getStringFromOctaveNote", "[NoteUtil]")
{
    REQUIRE(NoteUtil::getStringFromOctaveNote(0) == "C-");
    REQUIRE(NoteUtil::getStringFromOctaveNote(1) == "C#");
    REQUIRE(NoteUtil::getStringFromOctaveNote(2) == "D-");
    REQUIRE(NoteUtil::getStringFromOctaveNote(3) == "D#");
    REQUIRE(NoteUtil::getStringFromOctaveNote(4) == "E-");
    REQUIRE(NoteUtil::getStringFromOctaveNote(5) == "F-");
    REQUIRE(NoteUtil::getStringFromOctaveNote(6) == "F#");
    REQUIRE(NoteUtil::getStringFromOctaveNote(7) == "G-");
    REQUIRE(NoteUtil::getStringFromOctaveNote(8) == "G#");
    REQUIRE(NoteUtil::getStringFromOctaveNote(9) == "A-");
    REQUIRE(NoteUtil::getStringFromOctaveNote(10) == "A#");
    REQUIRE(NoteUtil::getStringFromOctaveNote(11) == "B-");

    REQUIRE(NoteUtil::getStringFromOctaveNote(12) == "C-");
    REQUIRE(NoteUtil::getStringFromOctaveNote(17) == "F-");

    REQUIRE(NoteUtil::getStringFromOctaveNote(24) == "C-");
}

TEST_CASE("getStringFromNote", "[NoteUtil]")
{
    REQUIRE(NoteUtil::getStringFromNote(0) == "C-0");
    REQUIRE(NoteUtil::getStringFromNote(1) == "C#0");
    REQUIRE(NoteUtil::getStringFromNote(2) == "D-0");
    REQUIRE(NoteUtil::getStringFromNote(3) == "D#0");
    REQUIRE(NoteUtil::getStringFromNote(4) == "E-0");
    REQUIRE(NoteUtil::getStringFromNote(5) == "F-0");
    REQUIRE(NoteUtil::getStringFromNote(6) == "F#0");
    REQUIRE(NoteUtil::getStringFromNote(7) == "G-0");
    REQUIRE(NoteUtil::getStringFromNote(8) == "G#0");
    REQUIRE(NoteUtil::getStringFromNote(9) == "A-0");
    REQUIRE(NoteUtil::getStringFromNote(10) == "A#0");
    REQUIRE(NoteUtil::getStringFromNote(11) == "B-0");

    REQUIRE(NoteUtil::getStringFromNote(12 * 1 + 0) == "C-1");
    REQUIRE(NoteUtil::getStringFromNote(12 * 1 + 7) == "G-1");
    REQUIRE(NoteUtil::getStringFromNote(12 * 1 + 11) == "B-1");

    REQUIRE(NoteUtil::getStringFromNote(12 * 7 + 1) == "C#7");
    REQUIRE(NoteUtil::getStringFromNote(12 * 7 + 7) == "G-7");
    REQUIRE(NoteUtil::getStringFromNote(12 * 7 + 11) == "B-7");
}

TEST_CASE("getStringFromNoteObject", "[NoteUtil]")
{
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(1)) == "C#0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(2)) == "D-0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(3)) == "D#0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(4)) == "E-0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(5)) == "F-0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(6)) == "F#0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(7)) == "G-0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(8)) == "G#0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(9)) == "A-0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(10)) == "A#0");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(11)) == "B-0");

    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(12 * 1 + 0)) == "C-1");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(12 * 1 + 7)) == "G-1");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(12 * 1 + 11)) == "B-1");

    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(12 * 7 + 1)) == "C#7");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(12 * 7 + 7)) == "G-7");
    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(12 * 7 + 11)) == "B-7");

    REQUIRE(NoteUtil::getStringFromNote(Note::buildNote(12 * 10 + 7)) == "G-A");
}

TEST_CASE("getOctaveFromNote", "[NoteUtil]")
{
    REQUIRE(NoteUtil::getOctaveFromNote(0) == 0);
    REQUIRE(NoteUtil::getOctaveFromNote(1) == 0);
    REQUIRE(NoteUtil::getOctaveFromNote(5) == 0);
    REQUIRE(NoteUtil::getOctaveFromNote(11) == 0);

    REQUIRE(NoteUtil::getOctaveFromNote(12 * 1 + 0) == 1);
    REQUIRE(NoteUtil::getOctaveFromNote(12 * 1 + 6) == 1);
    REQUIRE(NoteUtil::getOctaveFromNote(12 * 1 + 11) == 1);

    REQUIRE(NoteUtil::getOctaveFromNote(12 * 5 + 0) == 5);
    REQUIRE(NoteUtil::getOctaveFromNote(12 * 5 + 3) == 5);
    REQUIRE(NoteUtil::getOctaveFromNote(12 * 5 + 11) == 5);

    REQUIRE(NoteUtil::getOctaveFromNote(12 * 10 + 0) == 10);
    REQUIRE(NoteUtil::getOctaveFromNote(12 * 10 + 7) == 10);
    REQUIRE(NoteUtil::getOctaveFromNote(12 * 10 + 11) == 10);

    // Negative.
    REQUIRE(NoteUtil::getOctaveFromNote(0) == 0);
    REQUIRE(NoteUtil::getOctaveFromNote(-1) == -1);
    REQUIRE(NoteUtil::getOctaveFromNote(-11) == -1);

    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 1 - 0) == -1);
    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 1 - 1) == -2);
    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 1 - 11) == -2);

    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 2 - 0) == -2);
    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 2 - 1) == -3);
    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 2 - 11) == -3);

    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 7 - 0) == -7);
    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 7 - 1) == -8);
    REQUIRE(NoteUtil::getOctaveFromNote(-12 * 7 - 11) == -8);
}

TEST_CASE("getNoteInOctave", "[NoteUtil]")
{
    REQUIRE(NoteUtil::getNoteInOctave(0) == 0);
    REQUIRE(NoteUtil::getNoteInOctave(1) == 1);
    REQUIRE(NoteUtil::getNoteInOctave(11) == 11);

    REQUIRE(NoteUtil::getNoteInOctave(12 * 1 + 0) == 0);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 1 + 1) == 1);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 1 + 2) == 2);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 1 + 11) == 11);

    REQUIRE(NoteUtil::getNoteInOctave(12 * 2 + 0) == 0);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 2 + 1) == 1);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 2 + 9) == 9);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 2 + 11) == 11);

    REQUIRE(NoteUtil::getNoteInOctave(12 * 10 + 0) == 0);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 10 + 1) == 1);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 10 + 2) == 2);
    REQUIRE(NoteUtil::getNoteInOctave(12 * 10 + 11) == 11);

    // Negative.
    REQUIRE(NoteUtil::getNoteInOctave(-1) == 11);
    REQUIRE(NoteUtil::getNoteInOctave(-4) == 8);
    REQUIRE(NoteUtil::getNoteInOctave(-11) == 1);

    REQUIRE(NoteUtil::getNoteInOctave(-12 * 1 - 0) == 0);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 1 - 1) == 11);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 1 - 4) == 8);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 1 - 11) == 1);

    REQUIRE(NoteUtil::getNoteInOctave(-12 * 7 - 0) == 0);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 7 - 1) == 11);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 7 - 4) == 8);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 7 - 11) == 1);

    REQUIRE(NoteUtil::getNoteInOctave(-12 * 10 - 0) == 0);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 10 - 1) == 11);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 10 - 4) == 8);
    REQUIRE(NoteUtil::getNoteInOctave(-12 * 10 - 11) == 1);
}

TEST_CASE("getNote", "[NoteUtil]")
{
    REQUIRE(NoteUtil::getNote(0, 0) == 0);
    REQUIRE(NoteUtil::getNote(7, 0) == 7);
    REQUIRE(NoteUtil::getNote(11, 0) == 11);
    REQUIRE(NoteUtil::getNote(12, 0) == 12);
    REQUIRE(NoteUtil::getNote(15, 0) == 15);
    REQUIRE(NoteUtil::getNote(0, 1) == 12);
    REQUIRE(NoteUtil::getNote(11, 1) == 23);
    REQUIRE(NoteUtil::getNote(20, 1) == 32);
    REQUIRE(NoteUtil::getNote(0, 2) == 24);
    REQUIRE(NoteUtil::getNote(1, 4) == 49);
    REQUIRE(NoteUtil::getNote(30, 4) == 78);
    REQUIRE(NoteUtil::getNote(0, 10) == 120);

    REQUIRE(NoteUtil::getNote(0, -1) == -12);
    REQUIRE(NoteUtil::getNote(1, -1) == -11);
    REQUIRE(NoteUtil::getNote(11, -1) == -1);
    REQUIRE(NoteUtil::getNote(12, -1) == 0);

    REQUIRE(NoteUtil::getNote(0, -2) == -24);
    REQUIRE(NoteUtil::getNote(2, -2) == -22);

    REQUIRE(NoteUtil::getNote(0, -5) == -60);
}

}   // namespace arkostracker

