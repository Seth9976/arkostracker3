#include "../../catch.hpp"

#include <unordered_set>

#include "../../../source/business/channels/ChannelsMute.h"

namespace arkostracker 
{

TEST_CASE("solo on 0, all unmuted, 3 Channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ }, 0, 3);

    // Then.
    REQUIRE((result == std::unordered_set<int>{ 1, 2 }));
}

TEST_CASE("solo On 2, all unmuted, 3 channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ }, 2, 3);

    // Then.
    REQUIRE((result == std::unordered_set<int>{ 0, 1 }));
}

TEST_CASE("select 0, solo because 0 is muted, 3 channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ 0, 1 }, 0, 3);

    // Then.
    REQUIRE((result == std::unordered_set<int>{ 1, 2 }));
}

TEST_CASE("select 1, Solo because1 is muted, 9 channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ 1, 4, 5, 6, 7, 8 }, 1, 9);

    // Then.
    REQUIRE((result == std::unordered_set<int>{ 0, 2, 3, 4, 5, 6, 7, 8 }));
}

TEST_CASE("select2, 013 muted, all muted, 4 channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ 0, 1, 3 }, 2, 4);

    // Then.
    REQUIRE(result.empty());
}

TEST_CASE("select2, all muted except 2, all muted, 4 channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ 0, 1, 3 }, 2, 4);

    // Then.
    REQUIRE(result.empty());
}

TEST_CASE("select 1, 02 muted, mustSolo1, 4 channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ 0, 2 }, 1, 4);

    // Then.
    REQUIRE((result == std::unordered_set<int>{ 0, 2, 3 }));
}

TEST_CASE("select 2, 0 muted, must solo 2, 3 channels", "[ChannelsMute]")
{
    // Given/when.
    const auto result = ChannelsMute().toggleSoloOrUnmuteAll({ 0 }, 2, 3);

    // Then.
    REQUIRE((result == std::unordered_set<int>{ 0, 1 }));
}

}   // namespace arkostracker
