#include <juce_core/juce_core.h>

#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/speed/BpmCalculator.h"

namespace arkostracker
{

TEST_CASE("BpmCalculator, speed 6", "[BpmCalculator]")
{
    // Given/when.
    const auto result = BpmCalculator::calculateBpm(4, 6, 50.0F);

    // Then.
    REQUIRE((result == 125));
}

TEST_CASE("BpmCalculator, speed 6, 60hz", "[BpmCalculator]")
{
    // Given/when.
    const auto result = BpmCalculator::calculateBpm(4, 6, 60.0F);

    // Then.
    REQUIRE((result == 150));
}

TEST_CASE("BpmCalculator, speed 3, rows 2", "[BpmCalculator]")
{
    // Given/when.
    const auto result = BpmCalculator::calculateBpm(2, 6, 50.0F);

    // Then.
    REQUIRE((result == 250));
}

TEST_CASE("BpmCalculator, speed 3", "[BpmCalculator]")
{
    // Given/when.
    const auto result = BpmCalculator::calculateBpm(4, 3, 50.0F);

    // Then.
    REQUIRE((result == 250));
}

TEST_CASE("BpmCalculator, speed 5", "[BpmCalculator]")
{
    // Given/when.
    const auto result = BpmCalculator::calculateBpm(4, 5, 50.0F);

    // Then.
    REQUIRE((result == 150));
}

}   // namespace arkostracker
