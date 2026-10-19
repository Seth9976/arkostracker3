#include "../catch.hpp"

#include "../../source/utils/FpFloat.h"

namespace arkostracker
{

TEST_CASE("get parts", "[FpFloat]")
{
    const FpFloat f(1, 45);

    REQUIRE((f.getIntegerPart() == 1));
    REQUIRE((f.getDecimalPart() == 45));
}

TEST_CASE("set values", "[FpFloat]")
{
    FpFloat f(1, 45);
    f.setValues(10, 255);

    REQUIRE((f.getIntegerPart() == 10));
    REQUIRE((f.getDecimalPart() == 255));
}

TEST_CASE("set values, out of bounds", "[FpFloat]")
{
    FpFloat f(1, 45);
    f.setValues(0x1234, 0x45ab);

    REQUIRE((f.getIntegerPart() == 0x1234));
    REQUIRE((f.getDecimalPart() == 0xab));
}

TEST_CASE("set from digits", "[FpFloat]")
{
    FpFloat f(1, 45);
    f.setFromDigits(0xabcf);

    REQUIRE((f.getIntegerPart() == 0xab));
    REQUIRE((f.getDecimalPart() == 0xcf));
}

TEST_CASE("negates", "[FpFloat]")
{
    FpFloat f(1, 2);
    f.negate();

    REQUIRE((f.getIntegerPart() == 0xfffe));
    REQUIRE((f.getDecimalPart() == 254));
}

TEST_CASE("reset", "[FpFloat]")
{
    FpFloat f(1, 2);
    f.reset();

    REQUIRE((f.getIntegerPart() == 0));
    REQUIRE((f.getDecimalPart() == 0));
}

TEST_CASE("isNegative", "[FpFloat]")
{
    REQUIRE_FALSE((FpFloat(1, 2).isNegative()));
    REQUIRE_FALSE((FpFloat(0x7fff, 255).isNegative()));
    REQUIRE((FpFloat(0x8000, 2).isNegative()));
    REQUIRE((FpFloat(0x8001, 2).isNegative()));
    REQUIRE((FpFloat(0xffff, 255).isNegative()));
}

TEST_CASE("correctFrom0To, no correction", "[FpFloat]")
{
    FpFloat f(91, 255);
    f.correctFrom0To(91);

    REQUIRE((f.getIntegerPart() == 91));
    REQUIRE((f.getDecimalPart() == 255));
}

TEST_CASE("correctFrom0To, correction", "[FpFloat]")
{
    FpFloat f(91, 255);
    f.correctFrom0To(90);

    REQUIRE((f.getIntegerPart() == 90));
    REQUIRE((f.getDecimalPart() == 0));
}

TEST_CASE("correctFrom0To, correction because negative", "[FpFloat]")
{
    FpFloat f(91, 255);
    f.negate();
    f.correctFrom0To(10);

    REQUIRE((f.getIntegerPart() == 0));
    REQUIRE((f.getDecimalPart() == 0));
}

TEST_CASE("addition", "[FpFloat]")
{
    FpFloat f(1, 10);
    f += FpFloat(10, 20);

    REQUIRE((f.getIntegerPart() == 11));
    REQUIRE((f.getDecimalPart() == 30));
}

TEST_CASE("addition, overflow in decimal", "[FpFloat]")
{
    FpFloat f(1, 100);
    f += FpFloat(10, 157);

    REQUIRE((f.getIntegerPart() == 12));
    REQUIRE((f.getDecimalPart() == 1));
}

TEST_CASE("subtraction", "[FpFloat]")
{
    FpFloat f(50, 10);
    f -= FpFloat(10, 3);

    REQUIRE((f.getIntegerPart() == 40));
    REQUIRE((f.getDecimalPart() == 7));
}

TEST_CASE("subtraction, overflow in decimal", "[FpFloat]")
{
    FpFloat f(50, 10);
    f -= FpFloat(10, 11);

    REQUIRE((f.getIntegerPart() == 39));
    REQUIRE((f.getDecimalPart() == 255));
}

TEST_CASE("multiplication", "[FpFloat]")
{
    const FpFloat f(5, 0x10);
    const auto f2 = f * 2;

    REQUIRE((f2.getIntegerPart() == 10));
    REQUIRE((f2.getDecimalPart() == 0x20));
}

TEST_CASE("multiplication, decimal overflow", "[FpFloat]")
{
    const FpFloat f(5, 200);
    const auto f2 = f * 2;

    REQUIRE((f2.getIntegerPart() == 11));
    REQUIRE((f2.getDecimalPart() == (400 - 256)));
}

TEST_CASE("multiplication, decimal large overflow", "[FpFloat]")
{
    const FpFloat f(5, 0x80);
    const auto f2 = f * 0xa;

    REQUIRE((f2.getIntegerPart() == 0x32 + 5)); // 5 * a + 5 (carry).
    REQUIRE((f2.getDecimalPart() == 0));
}

TEST_CASE("multiplication with negative number, no decimal overflow", "[FpFloat]")
{
    const FpFloat f(0xffff, 0xe0);
    const auto f2 = f * 2;

    REQUIRE((f2.getIntegerPart() == 0xffff));
    REQUIRE((f2.getDecimalPart() == 0xc0));
}

TEST_CASE("multiplication with negative number, no decimal overflow 2", "[FpFloat]")
{
    const FpFloat f(0xffff, 0xc0);
    const auto f2 = f * 2;

    REQUIRE((f2.getIntegerPart() == 0xffff));
    REQUIRE((f2.getDecimalPart() == 0x80));
}

TEST_CASE("multiplication with negative number, decimal overflow", "[FpFloat]")
{
    const FpFloat f(0xffff, 0x80);
    const auto f2 = f * 2;

    REQUIRE((f2.getIntegerPart() == 0xffff));
    REQUIRE((f2.getDecimalPart() == 0x00));
}

TEST_CASE("multiplication with bigger negative number, no decimal overflow", "[FpFloat]")
{
    const FpFloat f(0xfffe, 0xff);
    const auto f2 = f * 2;

    REQUIRE((f2.getIntegerPart() == 0xfffd));
    REQUIRE((f2.getDecimalPart() == 0xfe));
}

TEST_CASE("multiplication with bigger negative number, decimal overflow", "[FpFloat]")
{
    const FpFloat f(0xfffe, 0x80);
    const auto f2 = f * 4;

    REQUIRE((f2.getIntegerPart() == 0xfffa));
    REQUIRE((f2.getDecimalPart() == 0x00));
}

TEST_CASE("multiplication, positive, mult by 1", "[FpFloat]")
{
    const FpFloat f(0x50, 0x60);
    const auto f2 = f * 1;

    REQUIRE((f2.getIntegerPart() == 0x50));
    REQUIRE((f2.getDecimalPart() == 0x60));
}

TEST_CASE("multiplication, negative, mult by 1, decimal", "[FpFloat]")
{
    const FpFloat f(0xfffe, 0x40);
    const auto f2 = f * 1;

    REQUIRE((f2.getIntegerPart() == 0xfffe));
    REQUIRE((f2.getDecimalPart() == 0x40));
}

TEST_CASE("multiplication, negative, mult by 1, 0 decimal", "[FpFloat]")
{
    const FpFloat f(0xfffe, 0x00);
    const auto f2 = f * 1;

    REQUIRE((f2.getIntegerPart() == 0xfffe));
    REQUIRE((f2.getDecimalPart() == 0x00));
}

TEST_CASE("multiplication, negative, mult by 2, 0 decimal", "[FpFloat]")
{
    const FpFloat f(0xff00, 0x00);
    const auto f2 = f * 2;

    REQUIRE((f2.getIntegerPart() == 0xfe00));
    REQUIRE((f2.getDecimalPart() == 0x00));
}

}   // namespace arkostracker
