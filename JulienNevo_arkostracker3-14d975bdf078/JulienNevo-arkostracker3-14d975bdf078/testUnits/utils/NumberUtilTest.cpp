#include "../catch.hpp"

#include "../../source/utils/NumberUtil.h"

namespace arkostracker 
{

TEST_CASE("toHexDigit, positive", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexDigit(0) == "0");
    REQUIRE(NumberUtil::toHexDigit(1) == "1");
    REQUIRE(NumberUtil::toHexDigit(9) == "9");
    REQUIRE(NumberUtil::toHexDigit(0xa) == "A");
    REQUIRE(NumberUtil::toHexDigit(0xf) == "F");

    REQUIRE(NumberUtil::toHexDigit(0x10) == "0");
    REQUIRE(NumberUtil::toHexDigit(0x1c) == "C");
    REQUIRE(NumberUtil::toHexDigit(0x1f) == "F");
    REQUIRE(NumberUtil::toHexDigit(0xa3) == "3");
    REQUIRE(NumberUtil::toHexDigit(0x1234) == "4");
    REQUIRE(NumberUtil::toHexDigit(0xfffe) == "E");
}

TEST_CASE("toHexDigit, negative", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexDigit(-1) == "1");
    REQUIRE(NumberUtil::toHexDigit(-4) == "4");
    REQUIRE(NumberUtil::toHexDigit(-9) == "9");
    REQUIRE(NumberUtil::toHexDigit(-0xa) == "A");
    REQUIRE(NumberUtil::toHexDigit(-0xf) == "F");

    REQUIRE(NumberUtil::toHexDigit(-0x10) == "0");
    REQUIRE(NumberUtil::toHexDigit(-0x1c) == "C");
    REQUIRE(NumberUtil::toHexDigit(-0x1f) == "F");
    REQUIRE(NumberUtil::toHexDigit(-0xa3) == "3");
    REQUIRE(NumberUtil::toHexDigit(-0x1234) == "4");
    REQUIRE(NumberUtil::toHexDigit(-0xffffe) == "E");
}


// =====================================================

TEST_CASE("toHexByte, positive", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexByte(0) == "00");
    REQUIRE(NumberUtil::toHexByte(1) == "01");
    REQUIRE(NumberUtil::toHexByte(9) == "09");
    REQUIRE(NumberUtil::toHexByte(0xa) == "0A");
    REQUIRE(NumberUtil::toHexByte(0xf) == "0F");

    REQUIRE(NumberUtil::toHexByte(0x10) == "10");
    REQUIRE(NumberUtil::toHexByte(0x1c) == "1C");
    REQUIRE(NumberUtil::toHexByte(0x1f) == "1F");
    REQUIRE(NumberUtil::toHexByte(0x4d) == "4D");
    REQUIRE(NumberUtil::toHexByte(0xa3) == "A3");
    REQUIRE(NumberUtil::toHexByte(0xcb) == "CB");
    REQUIRE(NumberUtil::toHexByte(0x1234) == "34");
    REQUIRE(NumberUtil::toHexByte(0xfffe) == "FE");
}

TEST_CASE("toHexByte, negative", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexByte(-1) == "01");
    REQUIRE(NumberUtil::toHexByte(-9) == "09");
    REQUIRE(NumberUtil::toHexByte(-0xa) == "0A");
    REQUIRE(NumberUtil::toHexByte(-0xf) == "0F");

    REQUIRE(NumberUtil::toHexByte(-0x10) == "10");
    REQUIRE(NumberUtil::toHexByte(-0x1c) == "1C");
    REQUIRE(NumberUtil::toHexByte(-0x1f) == "1F");
    REQUIRE(NumberUtil::toHexByte(-0x4d) == "4D");
    REQUIRE(NumberUtil::toHexByte(-0xa3) == "A3");
    REQUIRE(NumberUtil::toHexByte(-0xcb) == "CB");
    REQUIRE(NumberUtil::toHexByte(-0x1234) == "34");
    REQUIRE(NumberUtil::toHexByte(-0xfffe) == "FE");
}


// =====================================================

TEST_CASE("toHexThreeDigits, positive", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexThreeDigits(0) == "000");
    REQUIRE(NumberUtil::toHexThreeDigits(1) == "001");
    REQUIRE(NumberUtil::toHexThreeDigits(3) == "003");
    REQUIRE(NumberUtil::toHexThreeDigits(9) == "009");
    REQUIRE(NumberUtil::toHexThreeDigits(0xa) == "00A");
    REQUIRE(NumberUtil::toHexThreeDigits(0xb) == "00B");
    REQUIRE(NumberUtil::toHexThreeDigits(0xf) == "00F");

    REQUIRE(NumberUtil::toHexThreeDigits(0x10) == "010");
    REQUIRE(NumberUtil::toHexThreeDigits(0x1c) == "01C");
    REQUIRE(NumberUtil::toHexThreeDigits(0x1f) == "01F");
    REQUIRE(NumberUtil::toHexThreeDigits(0x4d) == "04D");
    REQUIRE(NumberUtil::toHexThreeDigits(0xa3) == "0A3");
    REQUIRE(NumberUtil::toHexThreeDigits(0xcb) == "0CB");
    REQUIRE(NumberUtil::toHexThreeDigits(0x123) == "123");
    REQUIRE(NumberUtil::toHexThreeDigits(0x8a1) == "8A1");
    REQUIRE(NumberUtil::toHexThreeDigits(0xfdc) == "FDC");
    REQUIRE(NumberUtil::toHexThreeDigits(0x1234) == "234");
    REQUIRE(NumberUtil::toHexThreeDigits(0xfffe) == "FFE");
}

TEST_CASE("toHexThreeDigits, negative", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexThreeDigits(-1) == "001");
    REQUIRE(NumberUtil::toHexThreeDigits(-3) == "003");
    REQUIRE(NumberUtil::toHexThreeDigits(-9) == "009");
    REQUIRE(NumberUtil::toHexThreeDigits(-0xa) == "00A");
    REQUIRE(NumberUtil::toHexThreeDigits(-0xb) == "00B");
    REQUIRE(NumberUtil::toHexThreeDigits(-0xf) == "00F");

    REQUIRE(NumberUtil::toHexThreeDigits(-0x10) == "010");
    REQUIRE(NumberUtil::toHexThreeDigits(-0x1c) == "01C");
    REQUIRE(NumberUtil::toHexThreeDigits(-0x1f) == "01F");
    REQUIRE(NumberUtil::toHexThreeDigits(-0x4d) == "04D");
    REQUIRE(NumberUtil::toHexThreeDigits(-0xa3) == "0A3");
    REQUIRE(NumberUtil::toHexThreeDigits(-0xcb) == "0CB");
    REQUIRE(NumberUtil::toHexThreeDigits(-0x123) == "123");
    REQUIRE(NumberUtil::toHexThreeDigits(-0x8a1) == "8A1");
    REQUIRE(NumberUtil::toHexThreeDigits(-0xfdc) == "FDC");
    REQUIRE(NumberUtil::toHexThreeDigits(-0x1234) == "234");
    REQUIRE(NumberUtil::toHexThreeDigits(-0xfffe) == "FFE");
}

// =====================================================

TEST_CASE("toHexFourDigits, positive", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexFourDigits(0) == "0000");
    REQUIRE(NumberUtil::toHexFourDigits(1) == "0001");
    REQUIRE(NumberUtil::toHexFourDigits(3) == "0003");
    REQUIRE(NumberUtil::toHexFourDigits(9) == "0009");
    REQUIRE(NumberUtil::toHexFourDigits(0xa) == "000A");
    REQUIRE(NumberUtil::toHexFourDigits(0xb) == "000B");
    REQUIRE(NumberUtil::toHexFourDigits(0xf) == "000F");

    REQUIRE(NumberUtil::toHexFourDigits(0x10) == "0010");
    REQUIRE(NumberUtil::toHexFourDigits(0x1c) == "001C");
    REQUIRE(NumberUtil::toHexFourDigits(0x1f) == "001F");
    REQUIRE(NumberUtil::toHexFourDigits(0x4d) == "004D");
    REQUIRE(NumberUtil::toHexFourDigits(0xa3) == "00A3");
    REQUIRE(NumberUtil::toHexFourDigits(0xcb) == "00CB");
    REQUIRE(NumberUtil::toHexFourDigits(0x123) == "0123");
    REQUIRE(NumberUtil::toHexFourDigits(0x8a1) == "08A1");
    REQUIRE(NumberUtil::toHexFourDigits(0xfdc) == "0FDC");
    REQUIRE(NumberUtil::toHexFourDigits(0x1234) == "1234");
    REQUIRE(NumberUtil::toHexFourDigits(0x943A) == "943A");
    REQUIRE(NumberUtil::toHexFourDigits(0xC2FA) == "C2FA");
    REQUIRE(NumberUtil::toHexFourDigits(0xfffe) == "FFFE");

    REQUIRE(NumberUtil::toHexFourDigits(0xfffe, true) == "fffe");
}

TEST_CASE("toHexFourDigits, negative", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toHexFourDigits(-1) == "0001");
    REQUIRE(NumberUtil::toHexFourDigits(-3) == "0003");
    REQUIRE(NumberUtil::toHexFourDigits(-9) == "0009");
    REQUIRE(NumberUtil::toHexFourDigits(-0xa) == "000A");
    REQUIRE(NumberUtil::toHexFourDigits(-0xb) == "000B");
    REQUIRE(NumberUtil::toHexFourDigits(-0xf) == "000F");

    REQUIRE(NumberUtil::toHexFourDigits(-0x10) == "0010");
    REQUIRE(NumberUtil::toHexFourDigits(-0x1c) == "001C");
    REQUIRE(NumberUtil::toHexFourDigits(-0x1f) == "001F");
    REQUIRE(NumberUtil::toHexFourDigits(-0x4d) == "004D");
    REQUIRE(NumberUtil::toHexFourDigits(-0xa3) == "00A3");
    REQUIRE(NumberUtil::toHexFourDigits(-0xcb) == "00CB");
    REQUIRE(NumberUtil::toHexFourDigits(-0x123) == "0123");
    REQUIRE(NumberUtil::toHexFourDigits(-0x8a1) == "08A1");
    REQUIRE(NumberUtil::toHexFourDigits(-0xfdc) == "0FDC");
    REQUIRE(NumberUtil::toHexFourDigits(-0x1234) == "1234");
    REQUIRE(NumberUtil::toHexFourDigits(-0x943A) == "943A");
    REQUIRE(NumberUtil::toHexFourDigits(-0xC2FA) == "C2FA");
    REQUIRE(NumberUtil::toHexFourDigits(-0xfffe) == "FFFE");
}


// =====================================================

TEST_CASE("toUnsignedHex", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toUnsignedHex(0) == "0");
    REQUIRE(NumberUtil::toUnsignedHex(1) == "1");
    REQUIRE(NumberUtil::toUnsignedHex(7) == "7");
    REQUIRE(NumberUtil::toUnsignedHex(0xa) == "A");
    REQUIRE(NumberUtil::toUnsignedHex(0xF) == "F");

    REQUIRE(NumberUtil::toUnsignedHex(0x10) == "10");
    REQUIRE(NumberUtil::toUnsignedHex(0x1e) == "1E");
    REQUIRE(NumberUtil::toUnsignedHex(0xab) == "AB");
    REQUIRE(NumberUtil::toUnsignedHex(0xff) == "FF");

    REQUIRE(NumberUtil::toUnsignedHex(0x147) == "147");
    REQUIRE(NumberUtil::toUnsignedHex(0xaaa) == "AAA");
    REQUIRE(NumberUtil::toUnsignedHex(0x1fac) == "1FAC");
    REQUIRE(NumberUtil::toUnsignedHex(0xabcd) == "ABCD");
    REQUIRE(NumberUtil::toUnsignedHex(0xffff) == "FFFF");
}


// =====================================================

TEST_CASE("signedHexToStringWithPrefix, prefix, no plus sign", "[NumberUtil]")
{
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0) == "&0");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(1) == "&1");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xa, "X") == "XA");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xfa) == "&FA");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0x678, "BOB") == "BOB678");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xadf) == "&ADF");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xf120, "#") == "#F120");

    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-1) == "-&1");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0xa) == "-&A");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0xfa, "x") == "-xFA");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0x678) == "-&678");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0xadf, "X") == "-XADF");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0xf120, "PPP") == "-PPPF120");
}

TEST_CASE("signedHexToStringWithPrefix, prefix, plus sign", "[NumberUtil]")
{
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0, "&", true) == "+&0");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(1, "x", true) == "+x1");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xa, "&", true) == "+&A");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xfa, "R", true) == "+RFA");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0x678, "&", true) == "+&678");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xdef, "#", true) == "+#DEF");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0x10456, "&", true) == "+&10456");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(0xfac, "&", true, false)
        == "+&fac");

    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-1, "&", true) == "-&1");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0x2f, "&", true) == "-&2F");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0xdaf, "x", true) == "-xDAF");
    REQUIRE(NumberUtil::signedHexToStringWithPrefix(-0xdaf, "x", true, false) == "-xdaf");
}


// =====================================================

TEST_CASE("toDecimalString", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toDecimalString(0, 1) == "0");
    REQUIRE(NumberUtil::toDecimalString(1, 1) == "1");
    REQUIRE(NumberUtil::toDecimalString(9, 1) == "9");
    REQUIRE(NumberUtil::toDecimalString(15, 1) == "15");
    REQUIRE(NumberUtil::toDecimalString(954, 1) == "954");

    REQUIRE(NumberUtil::toDecimalString(0, 2) == "00");
    REQUIRE(NumberUtil::toDecimalString(0, 3) == "000");
    REQUIRE(NumberUtil::toDecimalString(1, 3) == "001");
    REQUIRE(NumberUtil::toDecimalString(10, 3) == "010");
    REQUIRE(NumberUtil::toDecimalString(456, 6) == "000456");
    REQUIRE(NumberUtil::toDecimalString(123456, 9) == "000123456");
    REQUIRE(NumberUtil::toDecimalString(123456, 6) == "123456");
    REQUIRE(NumberUtil::toDecimalString(123456, 0) == "123456");
}


// =====================================================

TEST_CASE("correctNumber, no correction", "[NumberUtil]")
{
    REQUIRE(NumberUtil::correctNumber(0, 0, 0) == 0);
    REQUIRE(NumberUtil::correctNumber(0, -1, 1) == 0);

    REQUIRE(NumberUtil::correctNumber(1, 0, 2) == 1);
    REQUIRE(NumberUtil::correctNumber(10, 0, 10) == 10);
    REQUIRE(NumberUtil::correctNumber(10, 0, 20) == 10);

}

TEST_CASE("correctNumber, too low", "[NumberUtil]")
{
    REQUIRE(NumberUtil::correctNumber(-1, 0, 3) == 0);
    REQUIRE(NumberUtil::correctNumber(-10, 3, 3) == 3);
    REQUIRE(NumberUtil::correctNumber(-500, -100, 3) == -100);
}

TEST_CASE("correctNumber, too high", "[NumberUtil]")
{
    REQUIRE(NumberUtil::correctNumber(-1, -3, 0) == -1);
    REQUIRE(NumberUtil::correctNumber(4, 0, 1) == 1);
    REQUIRE(NumberUtil::correctNumber(1000, -2100, 500) == 500);
}


// =====================================================

TEST_CASE("isBitPresent", "[NumberUtil]")
{
    REQUIRE(NumberUtil::isBitPresent(0b111, 0b001));
    REQUIRE(NumberUtil::isBitPresent(0b111, 0b111));
    REQUIRE(NumberUtil::isBitPresent(0b111, 0b110));
    REQUIRE(NumberUtil::isBitPresent(0b101, 0b100));
    REQUIRE(NumberUtil::isBitPresent(0b0010100, 0b0000100));
    REQUIRE(NumberUtil::isBitPresent(0b0010100, 0b0010000));

    REQUIRE_FALSE(NumberUtil::isBitPresent(0b0000000, 0b0010000));
    REQUIRE_FALSE(NumberUtil::isBitPresent(0b0001000, 0b0010000));
    REQUIRE_FALSE(NumberUtil::isBitPresent(0b01111, 0b10000));
}


// =====================================================

TEST_CASE("toLog", "[NumberUtil]")
{
    REQUIRE(juce::exactlyEqual(NumberUtil::toLog(0.0, 9990.0, 99915.0), 0.0));
    REQUIRE(juce::exactlyEqual(NumberUtil::toLog(1.0, 9990.0, 99915.0), 0.0));
    REQUIRE(juce::exactlyEqual(NumberUtil::toLog(10.0, 9990.0, 99915.0), 24981.0));
    REQUIRE(juce::exactlyEqual(NumberUtil::toLog(100.0, 9990.0, 99915.0), 49963.0));
    //REQUIRE(NumberUtil::toLog(100.0, 9990.0, 3000.0) == 3000.0);          // FIXME Is it normal?? Result is 1500!!!???
}


// =====================================================

TEST_CASE("restrictWithLoop", "[NumberUtil]")
{
    REQUIRE(NumberUtil::restrictWithLoop(10, 30) == 10);
    REQUIRE(NumberUtil::restrictWithLoop(0, 30) == 0);

    REQUIRE(NumberUtil::restrictWithLoop(30, 30) == 30);
    REQUIRE(NumberUtil::restrictWithLoop(31, 30) == 0);
    REQUIRE(NumberUtil::restrictWithLoop(32, 30) == 1);
    REQUIRE(NumberUtil::restrictWithLoop(33, 30) == 2);
    REQUIRE(NumberUtil::restrictWithLoop(60, 30) == 29);
    REQUIRE(NumberUtil::restrictWithLoop(61, 30) == 30);
    REQUIRE(NumberUtil::restrictWithLoop(62, 30) == 0);

    REQUIRE(NumberUtil::restrictWithLoop(-1, 30) == 30);
    REQUIRE(NumberUtil::restrictWithLoop(-2, 30) == 29);
    REQUIRE(NumberUtil::restrictWithLoop(-12, 30) == 19);
    REQUIRE(NumberUtil::restrictWithLoop(-22, 30) == 9);
    REQUIRE(NumberUtil::restrictWithLoop(-29, 30) == 2);
    REQUIRE(NumberUtil::restrictWithLoop(-30, 30) == 1);
    REQUIRE(NumberUtil::restrictWithLoop(-31, 30) == 0);
    REQUIRE(NumberUtil::restrictWithLoop(-32, 30) == 30);
    REQUIRE(NumberUtil::restrictWithLoop(-33, 30) == 29);
    REQUIRE(NumberUtil::restrictWithLoop(-53, 30) == 9);
    REQUIRE(NumberUtil::restrictWithLoop(-60, 30) == 2);
    REQUIRE(NumberUtil::restrictWithLoop(-61, 30) == 1);
    REQUIRE(NumberUtil::restrictWithLoop(-62, 30) == 0);
    REQUIRE(NumberUtil::restrictWithLoop(-63, 30) == 30);
    REQUIRE(NumberUtil::restrictWithLoop(-64, 30) == 29);
    REQUIRE(NumberUtil::restrictWithLoop(-65, 30) == 28);
}



// =====================================================

TEST_CASE("correctWithLimitedLoop", "[NumberUtil]")
{
    REQUIRE(NumberUtil::correctWithLimitedLoop(5, 1, 10) == 5);
    REQUIRE(NumberUtil::correctWithLimitedLoop(1, 1, 10) == 1);
    REQUIRE(NumberUtil::correctWithLimitedLoop(2, 1, 10) == 2);
    REQUIRE(NumberUtil::correctWithLimitedLoop(9, 1, 10) == 9);
    REQUIRE(NumberUtil::correctWithLimitedLoop(10, 1, 10) == 10);

    REQUIRE(NumberUtil::correctWithLimitedLoop(11, 1, 10) == 1);
    REQUIRE(NumberUtil::correctWithLimitedLoop(18, 1, 10) == 1);
    REQUIRE(NumberUtil::correctWithLimitedLoop(0, 1, 10) == 10);
    REQUIRE(NumberUtil::correctWithLimitedLoop(-2, 1, 10) == 10);

    REQUIRE(NumberUtil::correctWithLimitedLoop(0, -8, -4) == -8);
    REQUIRE(NumberUtil::correctWithLimitedLoop(-4, -8, -4) == -4);
    REQUIRE(NumberUtil::correctWithLimitedLoop(-3, -8, -4) == -8);
    REQUIRE(NumberUtil::correctWithLimitedLoop(-9, -8, -4) == -4);
}


// =====================================================

TEST_CASE("getFirstNibble", "[NumberUtil]")
{
    REQUIRE(NumberUtil::getFirstNibble(0xabc) == 0xc);
    REQUIRE(NumberUtil::getFirstNibble(0xabcd0a) == 0xa);
    REQUIRE(NumberUtil::getFirstNibble(0xabcd0) == 0x0);
    REQUIRE(NumberUtil::getFirstNibble(0x0) == 0x0);
}

TEST_CASE("getSecondNibble", "[NumberUtil]")
{
    REQUIRE(NumberUtil::getSecondNibble(0x0) == 0x0);
    REQUIRE(NumberUtil::getSecondNibble(0xabc) == 0xb);
    REQUIRE(NumberUtil::getSecondNibble(0xabcd0a) == 0x0);
    REQUIRE(NumberUtil::getSecondNibble(0xabcd0) == 0xd);
    REQUIRE(NumberUtil::getSecondNibble(0x987) == 0x8);
}

TEST_CASE("getThirdNibble", "[NumberUtil]")
{
    REQUIRE(NumberUtil::getThirdNibble(0x0) == 0x0);
    REQUIRE(NumberUtil::getThirdNibble(0xf) == 0x0);
    REQUIRE(NumberUtil::getThirdNibble(0x1f) == 0x0);
    REQUIRE(NumberUtil::getThirdNibble(0xe1f) == 0xe);
    REQUIRE(NumberUtil::getThirdNibble(0x1234) == 0x2);
}

TEST_CASE("getByte", "[NumberUtil]")
{
    REQUIRE((NumberUtil::getByte(0x1234, 0) == 0x34));
    REQUIRE((NumberUtil::getByte(0x1234, 1) == 0x12));
    REQUIRE((NumberUtil::getByte(0x1234, 2) == 0x0));
}


// =====================================================

TEST_CASE("toMinutesAndSeconds", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toMinutesAndSeconds(0) == std::pair<int, int>(0, 0));
    REQUIRE(NumberUtil::toMinutesAndSeconds(1) == std::pair<int, int>(0, 1));
    REQUIRE(NumberUtil::toMinutesAndSeconds(59) == std::pair<int, int>(0, 59));
    REQUIRE(NumberUtil::toMinutesAndSeconds(60) == std::pair<int, int>(1, 0));
    REQUIRE(NumberUtil::toMinutesAndSeconds(60 * 2) == std::pair<int, int>(2, 0));
    REQUIRE(NumberUtil::toMinutesAndSeconds(60 * 5 + 10) == std::pair<int, int>(5, 10));
    REQUIRE(NumberUtil::toMinutesAndSeconds(60 * 50 + 54) == std::pair<int, int>(50, 54));
    REQUIRE(NumberUtil::toMinutesAndSeconds(60 * 51 + 59) == std::pair<int, int>(51, 59));
}

TEST_CASE("getDisplayMinutesAndSeconds", "[NumberUtil]")
{
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(0, 0) == juce::String("0:00"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(0, 1) == juce::String("0:01"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(0, 9) == juce::String("0:09"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(0, 10) == juce::String("0:10"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(0, 59) == juce::String("0:59"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(1, 0) == juce::String("1:00"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(1, 59) == juce::String("1:59"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(9, 59) == juce::String("9:59"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(10, 00) == juce::String("10:00"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(10, 45) == juce::String("10:45"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(99, 59) == juce::String("99:59"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(100, 32) == juce::String("100:32"));

    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(0, 59, true) == juce::String("-0:59"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(1, 10, true) == juce::String("-1:10"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(15, 47, true) == juce::String("-15:47"));
    REQUIRE(NumberUtil::getDisplayMinutesAndSeconds(195, 5, true) == juce::String("-195:05"));
}


// =====================================================

TEST_CASE("replaceDigit", "[NumberUtil]")
{
    REQUIRE(NumberUtil::replaceDigit(0, 0, 0xf) == 0xf);
    REQUIRE(NumberUtil::replaceDigit(0xfff, 0, 0xf) == 0xfff);
    REQUIRE(NumberUtil::replaceDigit(0xfff, 0, 0x0) == 0xff0);
    REQUIRE(NumberUtil::replaceDigit(0xff0, 0, 0xa) == 0xffa);

    REQUIRE(NumberUtil::replaceDigit(0x123, 1, 0x0) == 0x103);
    REQUIRE(NumberUtil::replaceDigit(0x123, 1, 0xf) == 0x1f3);
    REQUIRE(NumberUtil::replaceDigit(0x123, 1, 0x7) == 0x173);
    REQUIRE(NumberUtil::replaceDigit(0x123, 1, 0x8) == 0x183);

    REQUIRE(NumberUtil::replaceDigit(0xabc, 2, 0x0) == 0x0bc);
    REQUIRE(NumberUtil::replaceDigit(0xabc, 2, 0x1) == 0x1bc);
    REQUIRE(NumberUtil::replaceDigit(0xabc, 2, 0xe) == 0xebc);

    REQUIRE(NumberUtil::replaceDigit(0xabc, 3, 0xf) == 0xfabc);
    REQUIRE(NumberUtil::replaceDigit(0xdabc, 3, 0) == 0xabc);

    // Negative.
    REQUIRE(NumberUtil::replaceDigit(-0xfff, 0, 0xf) == -0xfff);
    REQUIRE(NumberUtil::replaceDigit(-0xfff, 0, 0x0) == -0xff0);
    REQUIRE(NumberUtil::replaceDigit(-0xff0, 0, 0xa) == -0xffa);

    REQUIRE(NumberUtil::replaceDigit(-0x123, 1, 0xc) == -0x1c3);

    REQUIRE(NumberUtil::replaceDigit(-0xabc, 2, 0x0) == -0x0bc);
    REQUIRE(NumberUtil::replaceDigit(-0xabc, 2, 0xd) == -0xdbc);

    REQUIRE(NumberUtil::replaceDigit(-0xabc, 3, 0xf) == -0xfabc);
    REQUIRE(NumberUtil::replaceDigit(-0xaabc, 3, 0x0) == -0xabc);
}

TEST_CASE("boolToInt", "[NumberUtil]")
{
    REQUIRE(NumberUtil::boolToInt(false) == 0);
    REQUIRE(NumberUtil::boolToInt(true) == 1);
}


// =====================================================

TEST_CASE("generateIdFromArray", "[NumberUtil]")
{
    REQUIRE(NumberUtil::generateIdFromArray(std::vector<int>{ }) == "");
    REQUIRE(NumberUtil::generateIdFromArray(std::vector<int>{ 41 }) == "P41");
    REQUIRE(NumberUtil::generateIdFromArray(std::vector<int>{ 1, 2, 3 }) == "P1P2P3");
    REQUIRE(NumberUtil::generateIdFromArray(std::vector<int>{ 1, -2, -303, 0 }) == "P1M2M303P0");
}


// =====================================================

TEST_CASE("toBinaryString", "[NumberUtil]")
{
    REQUIRE(NumberUtil::toBinaryString(0b11100010, 0) == "");
    REQUIRE(NumberUtil::toBinaryString(0b11100010, 1) == "0");
    REQUIRE(NumberUtil::toBinaryString(0b11100010, 2) == "10");
    REQUIRE(NumberUtil::toBinaryString(0b11100010, 8) == "11100010");
    REQUIRE(NumberUtil::toBinaryString(0b100010110, 16) == "0000000100010110");
}


// =====================================================

TEST_CASE("signedHexStringToInt, no check", "[NumberUtil]")
{
    REQUIRE(NumberUtil::signedHexStringToInt("0") == 0);
    REQUIRE(NumberUtil::signedHexStringToInt("-1") == -1);
    REQUIRE(NumberUtil::signedHexStringToInt("-1f") == -0x1f);
    REQUIRE(NumberUtil::signedHexStringToInt("-abcf") == -0xabcf);
    REQUIRE(NumberUtil::signedHexStringToInt("abcf") == 0xabcf);
    REQUIRE(NumberUtil::signedHexStringToInt("Ab") == 0xab);
    REQUIRE(NumberUtil::signedHexStringToInt(" Ab ") == 0xab);
    REQUIRE(NumberUtil::signedHexStringToInt(" -Ab ") == -0xab);
    REQUIRE(NumberUtil::signedHexStringToInt("--5") == -5);
    // Borderline cases.
    REQUIRE(NumberUtil::signedHexStringToInt("5-6") == 0x56);
    REQUIRE(NumberUtil::signedHexStringToInt("bob") == 0xbb);
}

TEST_CASE("signedHexStringToInt, check", "[NumberUtil]")
{
    auto error = false;
    REQUIRE(NumberUtil::signedHexStringToInt("0", error) == 0);
    REQUIRE_FALSE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("-1", error) == -1);
    REQUIRE_FALSE(error);
    REQUIRE(NumberUtil::signedHexStringToInt(" -1f", error) == -0x1f);
    REQUIRE_FALSE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("  -abcf  ", error) == -0xabcf);
    REQUIRE_FALSE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("abcf", error) == 0xabcf);
    REQUIRE_FALSE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("Ab", error) == 0xab);
    REQUIRE_FALSE(error);
    REQUIRE(NumberUtil::signedHexStringToInt(" Af0 ", error) == 0xaf0);
    REQUIRE_FALSE(error);

    REQUIRE(NumberUtil::signedHexStringToInt("-", error) == 0);
    REQUIRE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("", error) == 0);
    REQUIRE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("--5", error) == 0);
    REQUIRE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("5-6", error) == 0);
    REQUIRE(error);
    REQUIRE(NumberUtil::signedHexStringToInt("bob", error) == 0);
    REQUIRE(error);
}


// =====================================================

TEST_CASE("isInteger", "[NumberUtil]")
{
    REQUIRE(NumberUtil::isInteger(0.0));
    REQUIRE(NumberUtil::isInteger(-0.0));
    REQUIRE(NumberUtil::isInteger(1.0));
    REQUIRE(NumberUtil::isInteger(-1.0));
    REQUIRE(NumberUtil::isInteger(123.0));
    REQUIRE(NumberUtil::isInteger(-123.0));
    REQUIRE(NumberUtil::isInteger(981.0));
    REQUIRE(NumberUtil::isInteger(-981.0));
    REQUIRE(NumberUtil::isInteger(9797866.0));
    REQUIRE(NumberUtil::isInteger(-9797866.0));

    REQUIRE_FALSE(NumberUtil::isInteger(0.1));
    REQUIRE_FALSE(NumberUtil::isInteger(-0.1));
    REQUIRE_FALSE(NumberUtil::isInteger(0.000001));
    REQUIRE_FALSE(NumberUtil::isInteger(-0.000001));
    REQUIRE_FALSE(NumberUtil::isInteger(1.197));
    REQUIRE_FALSE(NumberUtil::isInteger(-1.197));
    REQUIRE_FALSE(NumberUtil::isInteger(2.999999));
    REQUIRE_FALSE(NumberUtil::isInteger(-2.999999));
    REQUIRE_FALSE(NumberUtil::isInteger(79486915.5));
    REQUIRE_FALSE(NumberUtil::isInteger(-79486915.5));
}


// =====================================================

TEST_CASE("calculateBalance", "[NumberUtil]")
{
    constexpr auto max = 255;
    REQUIRE((NumberUtil::calculateBalance(30, 30, 50, 1, max) == std::make_pair(30, 30)));

    REQUIRE((NumberUtil::calculateBalance(30, 30, 0, 0, max) == std::make_pair(60, 0)));
    REQUIRE((NumberUtil::calculateBalance(30, 30, 100, 0, max) == std::make_pair(0, 60)));

    REQUIRE((NumberUtil::calculateBalance(30, 30, 0, 1, max) == std::make_pair(59, 1)));
    REQUIRE((NumberUtil::calculateBalance(30, 30, 100, 1, max) == std::make_pair(1, 59)));

    REQUIRE((NumberUtil::calculateBalance(100, 100, 25, 1, max) == std::make_pair(150, 50)));
    REQUIRE((NumberUtil::calculateBalance(100, 100, 75, 1, max) == std::make_pair(50, 150)));

    REQUIRE((NumberUtil::calculateBalance(100, 100, 75, 1, 100) == std::make_pair(50, 100)));
}

}   // namespace arkostracker
