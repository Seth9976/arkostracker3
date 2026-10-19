#include "../../catch.hpp"

#include "../../../source/business/sid/StSidPeriodCalculator.h"

namespace arkostracker
{

TEST_CASE("calculate, 0x123", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0x123);

    // Then.
    REQUIRE((timerControl == 3));
    REQUIRE((timerData == 0xb3));
}

TEST_CASE("calculate, 0x1de", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0x1de);

    // Then.
    REQUIRE((timerControl == 4));
    REQUIRE((timerData == 0x5e));
}

TEST_CASE("calculate, 0x1aa", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0x1aa);

    // Then.
    REQUIRE((timerControl == 4));
    REQUIRE((timerData == 0x54));
}

TEST_CASE("calculate, 0x17b", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0x17b);

    // Then.
    REQUIRE((timerControl == 3));
    REQUIRE((timerData == 0xe9));
}

TEST_CASE("calculate, 0x166", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0x166);

    // Then.
    REQUIRE((timerControl == 3));
    REQUIRE((timerData == 0xdc));
}

TEST_CASE("calculate, 0x13f", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0x13f);

    // Then.
    REQUIRE((timerControl == 3));
    REQUIRE((timerData == 0xc4));
}

TEST_CASE("calculate, 0x11c", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0x11c);

    // Then.
    REQUIRE((timerControl == 3));
    REQUIRE((timerData == 0xae));
}

TEST_CASE("calculate, 0xfd", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0xfd);

    // Then.
    REQUIRE((timerControl == 2));
    REQUIRE((timerData == 0xf8));
}

TEST_CASE("calculate, 0xef", "[StSidPeriodCalculator]")
{
    // Given.
    const auto [timerControl, timerData] = StSidPeriodCalculator::calculate(0xef);

    // Then.
    REQUIRE((timerControl == 2));
    REQUIRE((timerData == 0xeb));
}

}   // namespace arkostracker
