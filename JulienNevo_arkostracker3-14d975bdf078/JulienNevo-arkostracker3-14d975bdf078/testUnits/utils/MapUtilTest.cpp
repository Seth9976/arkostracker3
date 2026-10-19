#include "../catch.hpp"

#include "../../source/utils/MapUtil.h"
#include "../../source/song/cells/Cell.h"

namespace arkostracker 
{

TEST_CASE("getMaximumKey, ordered", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 1, 5 },
            { 3, 5 },
            { 10, 5 },
    };

    REQUIRE(MapUtil::getMaximumKey(map) == 10);
}

TEST_CASE("getMaximumKey, empty", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int>();

    REQUIRE(MapUtil::getMaximumKey(map) == 0);
}

TEST_CASE("getMaximumKey, unordered", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 100, 5 },
            { 10, 5 },
            { 3, 5 },
    };

    REQUIRE(MapUtil::getMaximumKey(map) == 100);
}


// =========================================================

TEST_CASE("findNextHoleInKeys, right from start", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 1, 5 },
            { 2, 5 },
            { 3, 5 },
    };

    REQUIRE(MapUtil::findNextHoleInKeys(map, 0) == 0);
}

TEST_CASE("findNextHoleInKeys, second iteration", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 1, 5 },
            { 4, 5 },
            { 3, 5 },
    };

    REQUIRE(MapUtil::findNextHoleInKeys(map, 1) == 2);
}

TEST_CASE("findNextHoleInKeys, several iterations", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 0, 5 },
            { 1, 5 },
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
    };

    REQUIRE(MapUtil::findNextHoleInKeys(map, 0) == 6);
}


// =========================================================

TEST_CASE("areKeysContiguous, nominal", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 1, 5 },
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
    };

    REQUIRE(MapUtil::areKeysContiguous(map, 1).isAbsent());
}

TEST_CASE("areKeysContiguous, nominal from 0", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 0, 5 },
            { 1, 5 },
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
            { 6, 5 },
            { 7, 5 },
    };

    REQUIRE(MapUtil::areKeysContiguous(map, 0).isAbsent());
}

TEST_CASE("areKeysContiguous, hole right from start", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 1, 5 },
            { 2, 5 },
            { 3, 5 },
    };

    REQUIRE(MapUtil::areKeysContiguous(map, 0) == 0);
}

TEST_CASE("areKeysContiguous, hole after one iteration", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 1, 5 },
            { 3, 5 },
            { 4, 5 },
    };

    REQUIRE(MapUtil::areKeysContiguous(map, 1) == 2);
}

TEST_CASE("areKeysContiguous, hole from the start", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 1, 5 },
            { 2, 5 },
            { 3, 5 },
            { 5, 5 },
    };

    REQUIRE(MapUtil::areKeysContiguous(map, 4) == 4);
}

TEST_CASE("areKeysContiguous, starting with offset", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
            { 7, 5 },
            { 9, 5 },
            { 12, 5 },
            { 15, 5 },
    };

    REQUIRE(MapUtil::areKeysContiguous(map, 4) == 6);
}
TEST_CASE("areKeysContiguous, starting with end offset", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
            { 7, 5 },
            { 9, 5 },
            { 12, 5 },
            { 15, 5 },
    };

    REQUIRE(MapUtil::areKeysContiguous(map, 15).isAbsent());
}


// =========================================================

TEST_CASE("findHolesInKeys, no holes", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 0, 5 },
            { 1, 5 },
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
    };

    REQUIRE(MapUtil::findHolesInKeys(map, 0).empty());
}

TEST_CASE("findHolesInKeys, hole at first", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
    };

    REQUIRE(MapUtil::findHolesInKeys(map, 1) == std::set<int>{ 1 });
}

TEST_CASE("findHolesInKeys, multiple holes", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
            { 7, 5 },
            { 9, 5 },
            { 12, 5 },
    };

    REQUIRE(MapUtil::findHolesInKeys(map, 0) == std::set<int>{ 0, 1, 6, 8, 10, 11 });
}

TEST_CASE("findHolesInKeys, multiple holes, beginning skipped", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
            { 7, 5 },
            { 9, 5 },
            { 12, 5 },
            { 15, 5 },
    };

    REQUIRE(MapUtil::findHolesInKeys(map, 4) == std::set<int>{ 6, 8, 10, 11, 13, 14 });
}

TEST_CASE("findHolesInKeys, multiple holes, skipped till last", "[MapUtil]")
{
    // Given.
    const auto map = std::map<int, int> {
            { 2, 5 },
            { 3, 5 },
            { 4, 5 },
            { 5, 5 },
            { 7, 5 },
            { 9, 5 },
            { 12, 5 },
            { 15, 5 },
    };

    REQUIRE(MapUtil::findHolesInKeys(map, 15).empty());
}


// =========================================================

TEST_CASE("fillHolesInMap, hole in the middle", "[MapUtil]")
{
    // Given.
    auto map = std::map<int, int> {
            { 0, 5 },
            { 1, 6 },
            { 3, 7 },
            { 4, 8 },
    };

    // When.
    MapUtil::fillHolesInMap<int>(0, map, []() noexcept { return 12; });

    // Then.
    const auto expectedMap = std::map<int, int> {
            { 0, 5 },
            { 1, 6 },
            { 2, 12 },
            { 3, 7 },
            { 4, 8 },
    };
    REQUIRE(map == expectedMap);
}

TEST_CASE("fillHolesInMap, hole in the middle, with skipped values", "[MapUtil]")
{
    // Given.
    auto map = std::map<int, int> {
            { 0, 5 },
            { 1, 6 },
            { 2, 70 },
            { 5, 8 },
    };

    // When.
    MapUtil::fillHolesInMap<int>(2, map, []() noexcept { return 12; });

    // Then.
    const auto expectedMap = std::map<int, int> {
            { 0, 5 },
            { 1, 6 },
            { 2, 70 },
            { 3, 12 },
            { 4, 12 },
            { 5, 8 },
    };
    REQUIRE(map == expectedMap);
}

TEST_CASE("fillHolesInMap, no holes", "[MapUtil]")
{
    // Given.
    auto map = std::map<int, int> {
            { 0, 5 },
            { 1, 6 },
            { 2, 70 },
            { 3, 70 },
            { 4, 70 },
            { 5, 8 },
    };

    // When.
    MapUtil::fillHolesInMap<int>(0, map, []() noexcept { return 12; });

    // Then.
    const auto expectedMap = std::map<int, int> {
            { 0, 5 },
            { 1, 6 },
            { 2, 70 },
            { 3, 70 },
            { 4, 70 },
            { 5, 8 },
    };
    REQUIRE(map == expectedMap);
}

TEST_CASE("fillHolesInMap, hole from the start", "[MapUtil]")
{
    // Given.
    auto map = std::map<int, int> {
            { 2, 5 },
            { 3, 7 },
            { 4, 8 },
    };

    // When.
    MapUtil::fillHolesInMap<int>(0, map, []() noexcept { return 12; });

    // Then.
    const auto expectedMap = std::map<int, int> {
            { 0, 12 },
            { 1, 12 },
            { 2, 5 },
            { 3, 7 },
            { 4, 8 },
    };
    REQUIRE(map == expectedMap);
}


// =========================================================

TEST_CASE("fillHolesInMapUniquePtr, hole in the middle", "[MapUtil]")
{
    // Given.

    std::map<int, std::unique_ptr<int>> map;
    map.insert(std::make_pair(0, std::make_unique<int>(5)));
    map.insert(std::make_pair(1, std::make_unique<int>(6)));
    map.insert(std::make_pair(2, std::make_unique<int>(7)));
    map.insert(std::make_pair(4, std::make_unique<int>(8)));
    map.insert(std::make_pair(5, std::make_unique<int>(9)));


    // When.
    MapUtil::fillHolesInMapUniquePtr<int>(0, map, []() noexcept { return std::make_unique<int>(1000); });

    // Then.
    REQUIRE(map.size() == 6);
    REQUIRE(*map.at(0) == 5);
    REQUIRE(*map.at(1) == 6);
    REQUIRE(*map.at(2) == 7);
    REQUIRE(*map.at(3) == 1000);
    REQUIRE(*map.at(4) == 8);
    REQUIRE(*map.at(5) == 9);
}

TEST_CASE("fillHolesInMapUniquePtr, holes", "[MapUtil]")
{
    // Given.

    std::map<int, std::unique_ptr<int>> map;

    map.insert(std::make_pair(1, std::make_unique<int>(6)));
    map.insert(std::make_pair(2, std::make_unique<int>(7)));
    map.insert(std::make_pair(4, std::make_unique<int>(8)));
    map.insert(std::make_pair(5, std::make_unique<int>(9)));
    map.insert(std::make_pair(9, std::make_unique<int>(10)));

    // When.
    MapUtil::fillHolesInMapUniquePtr<int>(0, map, []() noexcept { return std::make_unique<int>(1000); });

    // Then.
    REQUIRE(map.size() == 10);
    REQUIRE(*map.at(0) == 1000);
    REQUIRE(*map.at(1) == 6);
    REQUIRE(*map.at(2) == 7);
    REQUIRE(*map.at(3) == 1000);
    REQUIRE(*map.at(4) == 8);
    REQUIRE(*map.at(5) == 9);
    REQUIRE(*map.at(6) == 1000);
    REQUIRE(*map.at(7) == 1000);
    REQUIRE(*map.at(8) == 1000);
    REQUIRE(*map.at(9) == 10);
}

TEST_CASE("fillHolesInMapUniquePtr, holes, with skip", "[MapUtil]")
{
    // Given.
    std::map<int, std::unique_ptr<int>> map;

    map.insert(std::make_pair(1, std::make_unique<int>(6)));
    map.insert(std::make_pair(2, std::make_unique<int>(7)));
    map.insert(std::make_pair(4, std::make_unique<int>(8)));
    map.insert(std::make_pair(7, std::make_unique<int>(9)));
    map.insert(std::make_pair(9, std::make_unique<int>(10)));

    // When.
    MapUtil::fillHolesInMapUniquePtr<int>(4, map, []() noexcept { return std::make_unique<int>(1000); });

    // Then.
    REQUIRE(map.size() == 8);
    REQUIRE(*map.at(1) == 6);
    REQUIRE(*map.at(2) == 7);
    REQUIRE(*map.at(4) == 8);
    REQUIRE(*map.at(5) == 1000);
    REQUIRE(*map.at(6) == 1000);
    REQUIRE(*map.at(7) == 9);
    REQUIRE(*map.at(8) == 1000);
    REQUIRE(*map.at(9) == 10);
}


// =========================================================

TEST_CASE("createVectorFromMap, empty input map", "[MapUtil]")
{
    // Given.
    std::map<int, int> map;

    // When.
    const auto result = MapUtil::createVectorFromMap<int, std::map<int, int>>(0, 5, map);

    // Then.
    size_t index = 0;
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.size() == index);
}

TEST_CASE("createVectorFromMap, input map with holes", "[MapUtil]")
{
    // Given.
    std::map<int, int> map = {
            { 2, 5 },
            { 4, 10 },
    };

    // When.
    const auto result = MapUtil::createVectorFromMap<int, std::map<int, int>>(0, 5, map);

    // Then.
    size_t index = 0;
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 5);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 10);
    REQUIRE(result.size() == index);
}

TEST_CASE("createVectorFromMap, input map with holes, using Cell", "[MapUtil]")
{
    // Given.
    std::map<int, Cell> map = {
            { 2, Cell(Note::buildNote(10), 5) },
            { 4, Cell(Note::buildNote(11), 6) },
            };

    // When.
    const auto result = MapUtil::createVectorFromMap<Cell, std::map<int, Cell>>(0, 5, map);

    // Then.
    size_t index = 0;
    REQUIRE(result.at(index++) == Cell());
    REQUIRE(result.at(index++) == Cell());
    REQUIRE(result.at(index++) == Cell(Note::buildNote(10), 5));
    REQUIRE(result.at(index++) == Cell());
    REQUIRE(result.at(index++) == Cell(Note::buildNote(11), 6));
    REQUIRE(result.size() == index);
}

TEST_CASE("createVectorFromMap, input map with no holes, start with offset", "[MapUtil]")
{
    // Given.
    std::map<int, int> map = {
            { 2, 5 },
            { 3, 1 },
            { 4, 10 },
            { 5, 20 },
            { 6, 40 },
            { 7, 80 },
    };

    // When.
    const auto result = MapUtil::createVectorFromMap<int, std::map<int, int>>(2, 6, map);

    // Then.
    size_t index = 0;
    REQUIRE(result.at(index++) == 5);
    REQUIRE(result.at(index++) == 1);
    REQUIRE(result.at(index++) == 10);
    REQUIRE(result.at(index++) == 20);
    REQUIRE(result.at(index++) == 40);
    REQUIRE(result.at(index++) == 80);
    REQUIRE(result.size() == index);
}

TEST_CASE("createVectorFromMap, input map with holes, start with offset, skip latest entries", "[MapUtil]")
{
    // Given.
    std::unordered_map<int, int> map = {
            { 2, 5 },
            { 3, 1 },
            { 6, 40 },
            { 7, 80 },
            { 10, 100 },
    };

    // When.
    const auto result = MapUtil::createVectorFromMap<int, std::unordered_map<int, int>>(3, 6, map);

    // Then.
    size_t index = 0;
    REQUIRE(result.at(index++) == 1);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.at(index++) == 40);
    REQUIRE(result.at(index++) == 80);
    REQUIRE(result.at(index++) == 0);
    REQUIRE(result.size() == index);
}

}   // namespace arkostracker

