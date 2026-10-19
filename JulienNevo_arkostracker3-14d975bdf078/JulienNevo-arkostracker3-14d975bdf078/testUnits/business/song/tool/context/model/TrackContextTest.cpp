#include "../../../../../catch.hpp"

#include "../../../../../../source/business/song/tool/context/EffectContextImpl.h"
#include "../../../../../../source/song/CellLocationInPosition.h"

namespace arkostracker
{

TEST_CASE("TrackContext, empty track", "[TrackContext]")
{
    // Given.
    const TrackContext trackContext;
    const auto defaultLineContext = LineContext();

    // When/Then.
    REQUIRE((trackContext.getContext(0) == defaultLineContext));
    REQUIRE((trackContext.getContext(1) == defaultLineContext));
    REQUIRE((trackContext.getContext(30) == defaultLineContext));
    REQUIRE((trackContext.getContext(127) == defaultLineContext));
}

TEST_CASE("TrackContext, two cells", "[TrackContext]")
{
    // Given.
    const auto id1 = Id();
    const auto id2 = Id();
    const LineContext defaultLineContext;
    const LineContext lineContext1(id1, { }, 15);
    const LineContext lineContext2(id2, { }, 10);

    TrackContext trackContext;
    trackContext.setContext(5, lineContext1);
    trackContext.setContext(10, lineContext2);

    // When.
    const auto contextLine0 = trackContext.getContext(0);
    const auto contextLine4 = trackContext.getContext(4);
    const auto contextLine5 = trackContext.getContext(5);
    const auto contextLine6 = trackContext.getContext(6);
    const auto contextLine9 = trackContext.getContext(9);
    const auto contextLine10 = trackContext.getContext(10);
    const auto contextLine11 = trackContext.getContext(11);
    const auto contextLine50 = trackContext.getContext(50);

    // Then.
    REQUIRE((contextLine0 == defaultLineContext));
    REQUIRE((contextLine4 == defaultLineContext));
    REQUIRE((contextLine5 == lineContext1));
    REQUIRE((contextLine6 == lineContext1));
    REQUIRE((contextLine9 == lineContext1));
    REQUIRE((contextLine10 == lineContext2));
    REQUIRE((contextLine11 == lineContext2));
    REQUIRE((contextLine50 == lineContext2));
}

}   // namespace arkostracker
