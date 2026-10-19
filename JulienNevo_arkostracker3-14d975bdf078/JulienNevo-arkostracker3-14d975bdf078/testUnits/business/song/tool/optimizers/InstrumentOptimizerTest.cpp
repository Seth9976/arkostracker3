#include "../../../../catch.hpp"

#include "../../../../../source/song/instrument/Instrument.h"
#include "../../../../../source/business/song/tool/optimizers/InstrumentOptimizer.h"

namespace arkostracker 
{

TEST_CASE("InstrumentOptimizer, simple, nothing optimized", "[InstrumentOptimizer]")
{
    // Given.
    PsgPart psgPart;
    psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
    psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
    psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(5));
    psgPart.setMainLoop(Loop(0, 2));
    const auto instrument = Instrument::buildPsgInstrument("instr", psgPart);
    const auto originalInstrument = std::make_unique<Instrument>(*instrument);

    // When.
    InstrumentOptimizer optimizer(*instrument, true, true);
    optimizer.optimize();

    // Then. No change.
    REQUIRE(*instrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, unused cells at the end removed", "[InstrumentOptimizer]")
{
    // Given.
    PsgPart originalPsgPart;
    originalPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
    originalPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
    originalPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
    originalPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(5));
    originalPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(2));
    originalPsgPart.setMainLoop(Loop(0, 2));
    const auto originalInstrument = Instrument::buildPsgInstrument("instr", originalPsgPart);

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    PsgPart expectedPsgPart;
    expectedPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
    expectedPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
    expectedPsgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
    expectedPsgPart.setMainLoop(Loop(0, 2));
    const auto expectedInstrument = Instrument::buildPsgInstrument("instr", expectedPsgPart);
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, mute empty software cells", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0, 15, 2, 3, -5, true));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0, 1, 0, 0, 0, true));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(1));
        psgPart.setMainLoop(Loop(0, 4));
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(1));
        psgPart.setMainLoop(Loop(0, 4));
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, last mute cells not removed because looping", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0, 1, 0, 0, 0, true));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(13));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0, 1, 0, 0, 0, true));
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.setMainLoop(Loop(0, 6, true));
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14));
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(13));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.setMainLoop(Loop(0, 6, true));
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, remove last mute cells", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0, 1, 0, 0, 0, true));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(13));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0, 1, 0, 0, 0, true));
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.setMainLoop(Loop(0, 6));
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(14));
        psgPart.addCell(PsgInstrumentCell::getEmptyPsgInstrumentCell());
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(13));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(0, 4));
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, one series.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.setMainLoop(Loop(0, 3));
        psgPart.setSpeed(0);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.setMainLoop(Loop(0, 0));
        psgPart.setSpeed(3);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, one series, with loop.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.setMainLoop(Loop(0, 3, true));
        psgPart.setSpeed(0);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.setMainLoop(Loop(0, 0, true));
        psgPart.setSpeed(3);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, two series.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(0, 3));
        psgPart.setSpeed(3);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(0, 1));
        psgPart.setSpeed(7);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, two series, with loop the second.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(2, 3, true));
        psgPart.setSpeed(3);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(1, 1, true));
        psgPart.setSpeed(7);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, two series, with loop the second, bis.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(4, 7, true));
        psgPart.setSpeed(3);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(1, 1, true));
        psgPart.setSpeed(15);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, three series with the two last equals.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(0, 5));
        psgPart.setSpeed(1);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(8));
        psgPart.setMainLoop(Loop(0, 2));
        psgPart.setSpeed(3);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, three series.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(0, 8));
        psgPart.setSpeed(10);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(0, 2));
        psgPart.setSpeed(32);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, three series, loop on second till the end.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(3, 8, true));
        psgPart.setSpeed(10);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(1, 2, true));
        psgPart.setSpeed(32);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, three series but the last is too small.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(0, 7));
        psgPart.setSpeed(10);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    const auto expectedInstrument = std::make_unique<Instrument>(*originalInstrument);

    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, three series but the last is too large.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(0, 9));
        psgPart.setSpeed(10);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    const auto expectedInstrument = std::make_unique<Instrument>(*originalInstrument);

    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, duplicate with same cell duplicated, three series, but loop in the middle of the second, abort.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(11));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(12));
        psgPart.setMainLoop(Loop(4, 8, true));
        psgPart.setSpeed(10);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    const auto expectedInstrument = std::make_unique<Instrument>(*originalInstrument);

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, preloop duplication.", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(5));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(5));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(5));
        psgPart.setMainLoop(Loop(6, 8, true));
        psgPart.setSpeed(3);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(5));
        psgPart.setMainLoop(Loop(0, 2, true));
        psgPart.setSpeed(3);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, retrig, cannot be optimized", "[InstrumentOptimizer]")
{
    // Given.
    PsgPart psgPart;
    psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0xf, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8, true, PsgValues::defaultSidActivated,
        PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0xf, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated,
        PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0xf, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 8, false, PsgValues::defaultSidActivated,
        PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
    psgPart.setMainLoop(Loop(1, 2));
    const auto instrument = Instrument::buildPsgInstrument("instr", psgPart);
    const auto originalInstrument = std::make_unique<Instrument>(*instrument);

    // When.
    InstrumentOptimizer optimizer(*instrument, true, true);
    optimizer.optimize();

    // Then. No change.
    REQUIRE(*instrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, header retrig, one line, no loop", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.setInstrumentRetrig(true);
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0xf, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 8, false,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
            PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(0, 0, false));
        psgPart.setSpeed(4);
        const auto instrument = Instrument::buildPsgInstrument("instr", psgPart);
        originalInstrument = std::make_unique<Instrument>(*instrument);
    }


    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.setInstrumentRetrig(false);
        psgPart.addCell(PsgInstrumentCell(PsgInstrumentCellLink::softToHard, 0xf, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 8, true,
            PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume,
            PsgValues::defaultSidRatio, PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch));
        psgPart.setMainLoop(Loop(0, 0, false));
        psgPart.setSpeed(4);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);

}

TEST_CASE("InstrumentOptimizer, looping on one mute cell at the end, optimize", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0));
        psgPart.setMainLoop(Loop(3, 3, true));
        psgPart.setSpeed(3);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(10));
        psgPart.setMainLoop(Loop(0, 2, false));
        psgPart.setSpeed(3);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, looping on several mute cells at the end, optimize", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell());
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell());
        psgPart.setMainLoop(Loop(1, 4, true));
        psgPart.setSpeed(3);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(15));
        psgPart.setMainLoop(Loop(0, 0, false));
        psgPart.setSpeed(3);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, looping on one mute cell at the end, but only one cell, don't optimize but simplify", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0));
        psgPart.setMainLoop(Loop(0, 0, true));
        psgPart.setSpeed(0);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell());        // Still simplified.
        psgPart.setMainLoop(Loop(0, 0, true));
        psgPart.setSpeed(0);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

TEST_CASE("InstrumentOptimizer, looping on fully mute cells, optimize", "[InstrumentOptimizer]")
{
    // Given.
    std::unique_ptr<Instrument> originalInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell());
        psgPart.addCell(PsgInstrumentCell::buildSoftwareCell(0));
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell());
        psgPart.setMainLoop(Loop(0, 3, true));
        psgPart.setSpeed(2);
        originalInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }

    // When.
    InstrumentOptimizer optimizer(*originalInstrument, true, true);
    optimizer.optimize();

    // Then.
    std::unique_ptr<Instrument> expectedInstrument;
    {
        PsgPart psgPart;
        psgPart.addCell(PsgInstrumentCell::buildNoSoftwareNoHardwareCell());
        psgPart.setMainLoop(Loop(0, 0, false));
        psgPart.setSpeed(2);
        expectedInstrument = Instrument::buildPsgInstrument("instr", psgPart);
    }
    REQUIRE(*expectedInstrument == *originalInstrument);
}

}   // namespace arkostracker

