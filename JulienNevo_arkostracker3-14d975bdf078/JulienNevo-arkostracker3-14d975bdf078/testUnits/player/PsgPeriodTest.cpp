#include "../catch.hpp"

#include "../../source/player/PsgPeriod.h"
#include "../../source/song/psg/PsgFrequency.h"

namespace arkostracker 
{

TEST_CASE("PsgPeriod, cpc", "[PsgPeriod]")
{
    const auto psgFrequency = PsgFrequency::psgFrequencyCPC;
    const auto refFrequency = PsgFrequency::defaultReferenceFrequencyHz;

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 0) == 3822));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 1) == 3608));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 2) == 3405));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 3) == 3214));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 11) == 2025));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (1 * 12) + 0) == 1911));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (1 * 12) + 8) == 1204));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (4 * 12) + 0) == 239));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (4 * 12) + 11) == 127));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (7 * 12) + 0) == 30));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (7 * 12) + 11) == 16));
}

TEST_CASE("PsgPeriod, cpc, other ref frequency", "[PsgPeriod]")
{
    const auto psgFrequency = PsgFrequency::psgFrequencyCPC;
    constexpr auto refFrequency = 234;

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 0) == 7187));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 11) == 3807));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (1 * 12) + 0) == 3594));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (4 * 12) + 0) == 449));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (7 * 12) + 0) == 56));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (7 * 12) + 11) == 30));
}

TEST_CASE("PsgPeriod, msx", "[PsgPeriod]")
{
    const auto psgFrequency = PsgFrequency::psgFrequencyMsxAndSvi;
    const auto refFrequency = PsgFrequency::defaultReferenceFrequencyHz;

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (0 * 12) + 0) == 6841));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (3 * 12) + 5) == 641));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (4 * 12) + 0) == 428));

    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (7 * 12) + 0) == 53));
    REQUIRE((PsgPeriod::getPeriod(psgFrequency, refFrequency, (7 * 12) + 11) == 28));
}


// ======================================================================

TEST_CASE("frequencyToPeriod, cpc", "[PsgPeriod]")
{
    const auto psgFrequency = PsgFrequency::psgFrequencyCPC;

    REQUIRE((static_cast<int>(PsgPeriod::getFrequency(psgFrequency, 142)) == 440));
}


}   // namespace arkostracker
