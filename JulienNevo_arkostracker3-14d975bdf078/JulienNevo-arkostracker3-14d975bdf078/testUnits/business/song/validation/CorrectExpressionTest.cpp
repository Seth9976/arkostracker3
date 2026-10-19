#include "../../../catch.hpp"

#include "../../../../source/business/song/validation/CorrectExpression.h"
#include "../../../../source/song/Expression.h"

namespace arkostracker 
{

TEST_CASE("correct arp empty", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "First", false);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "First");
    REQUIRE(expression.getSpeed() == 0);
    REQUIRE(expression.getLoopStart() == 0);
    REQUIRE(expression.getEnd() == 0);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp nominalOneValue", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "First", true);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "First");
    REQUIRE(expression.getSpeed() == 0);
    REQUIRE(expression.getLoopStart() == 0);
    REQUIRE(expression.getEnd() == 0);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp nominalSeveralValues", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "MyArp", false);
    expression.addValue(4);
    expression.addValue(-4);
    expression.addValue(0);
    expression.addValue(0x77);
    expression.addValue(-0x77);
    expression.addValue(0x43);
    expression.addValue(-0x76);
    expression.setSpeed(5);
    expression.setLoopStartAndEnd(2, 6);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyArp");
    REQUIRE(expression.getSpeed() == 5);
    REQUIRE(expression.getLoopStart() == 2);
    REQUIRE(expression.getEnd() == 6);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 4);
    REQUIRE(expression.getValue(index++) == -4);
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x77);
    REQUIRE(expression.getValue(index++) == -0x77);
    REQUIRE(expression.getValue(index++) == 0x43);
    REQUIRE(expression.getValue(index++) == -0x76);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp wrongValues", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "MyArp", false);
    expression.addValue(0);
    expression.addValue(0x80);
    expression.addValue(-0x80);
    expression.addValue(0x7f);
    expression.addValue(-0x7f);
    expression.addValue(0x78);
    expression.addValue(-0x78);
    expression.setSpeed(3);
    expression.setLoopStartAndEnd(1, 1);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyArp");
    REQUIRE(expression.getSpeed() == 3);
    REQUIRE(expression.getLoopStart() == 1);
    REQUIRE(expression.getEnd() == 1);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x77);
    REQUIRE(expression.getValue(index++) == -0x77);
    REQUIRE(expression.getValue(index++) == 0x77);
    REQUIRE(expression.getValue(index++) == -0x77);
    REQUIRE(expression.getValue(index++) == 0x77);
    REQUIRE(expression.getValue(index++) == -0x77);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp speedTooHigh", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "MyArp", false);
    expression.addValue(4);
    expression.addValue(-4);
    expression.addValue(0);
    expression.addValue(0x7f);
    expression.addValue(-0x7f);
    expression.addValue(0x43);
    expression.addValue(-0x76);
    expression.setSpeed(256);
    expression.setLoopStartAndEnd(2, 6);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyArp");
    REQUIRE(expression.getSpeed() == 255);
    REQUIRE(expression.getLoopStart() == 2);
    REQUIRE(expression.getEnd() == 6);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 4);
    REQUIRE(expression.getValue(index++) == -4);
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x77);
    REQUIRE(expression.getValue(index++) == -0x77);
    REQUIRE(expression.getValue(index++) == 0x43);
    REQUIRE(expression.getValue(index++) == -0x76);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp speedTooLow", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "MyArp", false);
    expression.addValue(4);
    expression.addValue(-4);
    expression.addValue(0);
    expression.addValue(0x76);
    expression.addValue(-0x76);
    expression.addValue(0x43);
    expression.addValue(-0x76);
    expression.setSpeed(-1);
    expression.setLoopStartAndEnd(2, 6);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyArp");
    REQUIRE(expression.getSpeed() == 0);
    REQUIRE(expression.getLoopStart() == 2);
    REQUIRE(expression.getEnd() == 6);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 4);
    REQUIRE(expression.getValue(index++) == -4);
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x76);
    REQUIRE(expression.getValue(index++) == -0x76);
    REQUIRE(expression.getValue(index++) == 0x43);
    REQUIRE(expression.getValue(index++) == -0x76);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp startAfterEnd", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "MyArp", false);
    expression.addValue(4);
    expression.addValue(-4);
    expression.addValue(0);
    expression.addValue(0x77);
    expression.addValue(-0x77);
    expression.addValue(0x43);
    expression.addValue(-0x76);
    expression.setSpeed(10);
    expression.setLoopStartAndEnd(5, 4);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyArp");
    REQUIRE(expression.getSpeed() == 10);
    REQUIRE(expression.getLoopStart() == 0);
    REQUIRE(expression.getEnd() == 4);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 4);
    REQUIRE(expression.getValue(index++) == -4);
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x77);
    REQUIRE(expression.getValue(index++) == -0x77);
    REQUIRE(expression.getValue(index++) == 0x43);
    REQUIRE(expression.getValue(index++) == -0x76);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp endAfterLength", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "MyArp", false);
    expression.addValue(4);
    expression.addValue(-4);
    expression.addValue(0);
    expression.addValue(0x70);
    expression.addValue(-0x70);
    expression.addValue(0x43);
    expression.addValue(-0x76);
    expression.setSpeed(10);
    expression.setLoopStartAndEnd(1, 40);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyArp");
    REQUIRE(expression.getSpeed() == 10);
    REQUIRE(expression.getLoopStart() == 1);
    REQUIRE(expression.getEnd() == 6);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 4);
    REQUIRE(expression.getValue(index++) == -4);
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x70);
    REQUIRE(expression.getValue(index++) == -0x70);
    REQUIRE(expression.getValue(index++) == 0x43);
    REQUIRE(expression.getValue(index++) == -0x76);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct arp startAndEndAfterLength", "[CorrectExpression]")
{
    // Given.
    Expression expression(true, "MyArp", false);
    expression.addValue(4);
    expression.addValue(-4);
    expression.addValue(0);
    expression.addValue(0x74);
    expression.addValue(-0x73);
    expression.addValue(0x43);
    expression.addValue(-0x76);
    expression.setSpeed(10);
    expression.setLoopStartAndEnd(41, 43);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyArp");
    REQUIRE(expression.getSpeed() == 10);
    REQUIRE(expression.getLoopStart() == 0);
    REQUIRE(expression.getEnd() == 6);
    REQUIRE(expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 4);
    REQUIRE(expression.getValue(index++) == -4);
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x74);
    REQUIRE(expression.getValue(index++) == -0x73);
    REQUIRE(expression.getValue(index++) == 0x43);
    REQUIRE(expression.getValue(index++) == -0x76);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct pitch nominalSeveralValues", "[CorrectExpression]")
{
    // Given.
    Expression expression(false, "MyPitch", false);
    expression.addValue(0);
    expression.addValue(0x1);
    expression.addValue(-0x1);
    expression.addValue(0x80);
    expression.addValue(-0x80);
    expression.addValue(0x7f);
    expression.addValue(-0x7f);
    expression.addValue(0xfff);
    expression.addValue(-0xfff);
    expression.setSpeed(30);
    expression.setLoopStartAndEnd(4, 4);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyPitch");
    REQUIRE(expression.getSpeed() == 30);
    REQUIRE(expression.getLoopStart() == 4);
    REQUIRE(expression.getEnd() == 4);
    REQUIRE(!expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x1);
    REQUIRE(expression.getValue(index++) == -0x1);
    REQUIRE(expression.getValue(index++) == 0x80);
    REQUIRE(expression.getValue(index++) == -0x80);
    REQUIRE(expression.getValue(index++) == 0x7f);
    REQUIRE(expression.getValue(index++) == -0x7f);
    REQUIRE(expression.getValue(index++) == 0xfff);
    REQUIRE(expression.getValue(index++) == -0xfff);
    REQUIRE(expression.getLength() == index);
}

TEST_CASE("correct pitch wrongValues", "[CorrectExpression]")
{
    // Given.
    Expression expression(false, "MyPitch", false);
    expression.addValue(0);
    expression.addValue(0x80);
    expression.addValue(-0x80);
    expression.addValue(0x7f);
    expression.addValue(-0x7f);
    expression.addValue(0xfff);
    expression.addValue(-0xfff);
    expression.addValue(0x1000);
    expression.addValue(-0x1000);
    expression.addValue(0xffff);
    expression.addValue(-0xffff);
    expression.setSpeed(3);
    expression.setLoopStartAndEnd(1, 1);

    // When.
    CorrectExpression().correctExpression(expression);

    // Then.
    REQUIRE(expression.getName() == "MyPitch");
    REQUIRE(expression.getSpeed() == 3);
    REQUIRE(expression.getLoopStart() == 1);
    REQUIRE(expression.getEnd() == 1);
    REQUIRE(!expression.isArpeggio());
    auto index = 0;
    REQUIRE(expression.getValue(index++) == 0);
    REQUIRE(expression.getValue(index++) == 0x80);
    REQUIRE(expression.getValue(index++) == -0x80);
    REQUIRE(expression.getValue(index++) == 0x7f);
    REQUIRE(expression.getValue(index++) == -0x7f);
    REQUIRE(expression.getValue(index++) == 0xfff);
    REQUIRE(expression.getValue(index++) == -0xfff);
    REQUIRE(expression.getValue(index++) == 0xfff);
    REQUIRE(expression.getValue(index++) == -0xfff);
    REQUIRE(expression.getValue(index++) == 0xfff);
    REQUIRE(expression.getValue(index++) == -0xfff);
    REQUIRE(expression.getLength() == index);
}

}   // namespace arkostracker
