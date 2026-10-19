#include "../../../catch.hpp"

#include "../../../../source/business/song/validation/CheckTrackHeight.h"

namespace arkostracker 
{

TEST_CASE("correctHeight, nominal", "[CheckTrackHeight]")
{
    REQUIRE(CheckTrackHeight::correctHeight(1) == 1);
    REQUIRE(CheckTrackHeight::correctHeight(2) == 2);
    REQUIRE(CheckTrackHeight::correctHeight(10) == 10);
    REQUIRE(CheckTrackHeight::correctHeight(50) == 50);
    REQUIRE(CheckTrackHeight::correctHeight(100) == 100);
    REQUIRE(CheckTrackHeight::correctHeight(120) == 120);
    REQUIRE(CheckTrackHeight::correctHeight(127) == 127);
    REQUIRE(CheckTrackHeight::correctHeight(128) == 128);
}

TEST_CASE("correctHeight, too low", "[CheckTrackHeight]")
{
    REQUIRE(CheckTrackHeight::correctHeight(0) == 1);
    REQUIRE(CheckTrackHeight::correctHeight(-1) == 1);
    REQUIRE(CheckTrackHeight::correctHeight(-20) == 1);
}

TEST_CASE("correctHeight, too high", "[CheckTrackHeight]")
{
    REQUIRE(CheckTrackHeight::correctHeight(129) == 128);
    REQUIRE(CheckTrackHeight::correctHeight(150) == 128);
    REQUIRE(CheckTrackHeight::correctHeight(250) == 128);
}

}   // namespace arkostracker
