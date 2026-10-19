#include "../catch.hpp"

#include "../../source/utils/BitNumber.h"

namespace arkostracker 
{

TEST_CASE("BitNumber, empty", "[BitNumber]")
{
    const BitNumber bitNumber;
    const auto number = bitNumber.get();
    REQUIRE(number == 0);
}

TEST_CASE("BitNumber, 1011", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBits("1011");
    const auto number = bitNumber.get();
    REQUIRE(number == 0b1011);
}

TEST_CASE("BitNumber, 0", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBits("0");
    const auto number = bitNumber.get();
    REQUIRE(number == 0);
}

TEST_CASE("BitNumber, 1", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBits("1");
    const auto number = bitNumber.get();
    REQUIRE(number == 1);
}

TEST_CASE("BitNumber, 000000000001001", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBits("000000000001001");
    const auto number = bitNumber.get();
    REQUIRE(number == 0b1001);
}

TEST_CASE("BitNumber, 8 bits limit", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBits("110011011");
    const auto number = bitNumber.get();
    REQUIRE(number == 0b10011011);       // The number is truncated to 8 bits.
}

TEST_CASE("BitNumber, 16 bits limit", "[BitNumber]")
{
    BitNumber bitNumber(0xffffU);
    bitNumber.injectBits("101110011011");
    const auto number = bitNumber.get();
    REQUIRE(number == 0b101110011011);
}

TEST_CASE("BitNumber, boolean true", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBool(true);
    const auto number = bitNumber.get();
    REQUIRE(number == 1);
}

TEST_CASE("BitNumber, boolean false", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBool(false);
    const auto number = bitNumber.get();
    REQUIRE(number == 0);
}

TEST_CASE("BitNumber, booleans test 1", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBool(true);
    bitNumber.injectBool(true);
    bitNumber.injectBool(false);
    bitNumber.injectBool(true);
    bitNumber.injectBool(true);
    bitNumber.injectBool(false);
    const auto number = bitNumber.get();
    REQUIRE(number == 0b11011);
}

TEST_CASE("BitNumber, booleans test 2", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBool(false);
    bitNumber.injectBool(false);
    bitNumber.injectBool(true);
    bitNumber.injectBool(true);
    bitNumber.injectBool(false);
    bitNumber.injectBool(true);
    const auto number = bitNumber.get();
    REQUIRE(number == 0b101100);
}

TEST_CASE("BitNumber, numbers test 1", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectNumber(15, 4U);
    const auto number = bitNumber.get();
    REQUIRE(number == 0b1111);
}

TEST_CASE("BitNumber, numbers test 2", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectNumber(255, 2U);
    const auto number = bitNumber.get();
    REQUIRE(number == 0b11);
}

TEST_CASE("BitNumber, combination 1", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectNumber(0b1100, 4U);
    bitNumber.injectBool(true);
    bitNumber.injectBool(false);
    bitNumber.injectBits("10");
    const auto number = bitNumber.get();
    REQUIRE(number == 0b10011100);
}

TEST_CASE("BitNumber, combination 2", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBits("000");
    bitNumber.injectNumber(0b11, 4U);
    bitNumber.injectBool(true);
    const auto number = bitNumber.get();
    REQUIRE(number == 0b10011000);
}

TEST_CASE("BitNumber, combination 3", "[BitNumber]")
{
    BitNumber bitNumber;
    bitNumber.injectBool(true);
    bitNumber.injectBool(false);
    bitNumber.injectBool(false);
    bitNumber.injectBits("1010");
    bitNumber.injectNumber(1, 1U);
    const auto number = bitNumber.get();
    REQUIRE(number == 0b11010001);
}

}   // namespace arkostracker
