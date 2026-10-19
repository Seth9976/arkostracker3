#include "../catch.hpp"



#include "../../source/utils/StreamUtil.h"
#include "../../source/utils/MemoryBlockUtil.h"

namespace arkostracker 
{

/** Tests the StreamUtil class. */

TEST_CASE("extractString, nominal", "[StreamUtil]")
{
    // Given.
    auto memoryBlock = MemoryBlockUtil::fromString("Hello Johnny");
    juce::MemoryInputStream inputStream(memoryBlock, true);

    // When.
    bool success;
    auto result = StreamUtil::extractString(inputStream, 10, success);

    // Then.
    REQUIRE(success);
    REQUIRE(result == "Hello John");
}

TEST_CASE("extractString, exact size", "[StreamUtil]")
{
    // Given.
    auto memoryBlock = MemoryBlockUtil::fromString("abcdefg");
    juce::MemoryInputStream inputStream(memoryBlock, true);

    // When.
    bool success;
    auto result = StreamUtil::extractString(inputStream, 7, success);

    // Then.
    REQUIRE(success);
    REQUIRE(result == "abcdefg");
}

TEST_CASE("extractString, not enough room", "[StreamUtil]")
{
    // Given.
    auto memoryBlock = MemoryBlockUtil::fromString("abcdefg");
    juce::MemoryInputStream inputStream(memoryBlock, true);

    // When.
    bool success;
    auto result = StreamUtil::extractString(inputStream, 8, success);

    // Then.
    REQUIRE_FALSE(success);
    REQUIRE(result.isEmpty());
}

}   // namespace arkostracker

