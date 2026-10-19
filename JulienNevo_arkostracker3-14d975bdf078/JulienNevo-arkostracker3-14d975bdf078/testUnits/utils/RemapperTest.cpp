#include "../catch.hpp"

#include "../../source/song/Expression.h"
#include "../../source/utils/Remapper.h"

namespace arkostracker 
{

TEST_CASE("moveMap_NoChange", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForMove(8, { }, 5);

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 1));
    REQUIRE((map.find(2)->second == 2));
    REQUIRE((map.find(3)->second == 3));
    REQUIRE((map.find(4)->second == 4));
    REQUIRE((map.find(5)->second == 5));
    REQUIRE((map.find(6)->second == 6));
    REQUIRE((map.find(7)->second == 7));

    // Checks the vector.
    auto index = 0U;
    REQUIRE((*vector.at(index++) == 0));
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((*vector.at(index++) == 7));
    REQUIRE((vector.size() == index));

    // Undo.
    remapper->undoOnVector(vector);
    // Check.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("moveMap_MoveFirstToBeforeLast", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForMove(8, { 0 }, 7);
    // 0 A    B
    // 1 B    C
    // 2 C    D
    // 3 D    E
    // 4 E    F
    // 5 F    G
    // 6 G    A
    // 7 H    H

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 6));
    REQUIRE((map.find(1)->second == 0));
    REQUIRE((map.find(2)->second == 1));
    REQUIRE((map.find(3)->second == 2));
    REQUIRE((map.find(4)->second == 3));
    REQUIRE((map.find(5)->second == 4));
    REQUIRE((map.find(6)->second == 5));
    REQUIRE((map.find(7)->second == 7));

    // Checks the vector.
    auto index = 0U;
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((*vector.at(index++) == 0));
    REQUIRE((*vector.at(index++) == 7));
    REQUIRE((vector.size() == index));
}

TEST_CASE("moveMap_MoveFirstToEnd", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForMove(8, { 0 }, 8);
    // 0 A    B
    // 1 B    C
    // 2 C    D
    // 3 D    E
    // 4 E    F
    // 5 F    G
    // 6 G    H
    // 7 H    A

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 7));
    REQUIRE((map.find(1)->second == 0));
    REQUIRE((map.find(2)->second == 1));
    REQUIRE((map.find(3)->second == 2));
    REQUIRE((map.find(4)->second == 3));
    REQUIRE((map.find(5)->second == 4));
    REQUIRE((map.find(6)->second == 5));
    REQUIRE((map.find(7)->second == 6));
    // Checks the vector.
    size_t index = 0;
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((*vector.at(index++) == 7));
    REQUIRE((*vector.at(index++) == 0));
    REQUIRE((vector.size() == index));

    // Undo.
    remapper->undoOnVector(vector);
    // Check.
    index = 0;
    REQUIRE((*vector.at(index++) == 0));
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((*vector.at(index++) == 7));
    REQUIRE((vector.size() == index));
}

TEST_CASE("moveMap_ThreeMoves_InsertAfterTwo", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForMove(8, { 1, 3, 6 }, 5);
    // 0 A    A
    // 1 B    C
    // 2 C    E
    // 3 D    B   **
    // 4 E    D   **
    // 5 F    G   **
    // 6 G    F
    // 7 H    H

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 3));
    REQUIRE((map.find(2)->second == 1));
    REQUIRE((map.find(3)->second == 4));
    REQUIRE((map.find(4)->second == 2));
    REQUIRE((map.find(5)->second == 6));
    REQUIRE((map.find(6)->second == 5));
    REQUIRE((map.find(7)->second == 7));
    // Checks the vector.
    REQUIRE((vector.size() == 8));
    auto index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 4));

    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 6));

    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 7));

    // Undo.
    remapper->undoOnVector(vector);
    // Check.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("moveMap_MoveAllButOneAfterMiddle", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForMove(8, { 0, 1, 2, 4, 5, 6, 7 }, 4);
    // 0 A    D
    // 1 B    A
    // 2 C    B
    // 3 D    C    NOT MOVED. Insert all after "D".
    // 4 E    E
    // 5 F    F
    // 6 G    G
    // 7 H    H

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 1));
    REQUIRE((map.find(1)->second == 2));
    REQUIRE((map.find(2)->second == 3));
    REQUIRE((map.find(3)->second == 0));
    REQUIRE((map.find(4)->second == 4));
    REQUIRE((map.find(5)->second == 5));
    REQUIRE((map.find(6)->second == 6));
    REQUIRE((map.find(7)->second == 7));
    // Checks the vector.
    REQUIRE((vector.size() == 8));
    auto index = -1U;
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));

    // Undo.
    remapper->undoOnVector(vector);
    // Check.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}


// ==================================================

TEST_CASE("deleteMap_DeleteFirst", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 0 });
    // 0 A    Deleted
    // 1 B    0
    // 2 C    1
    // 3 D    2
    // 4 E    3
    // 5 F    4
    // 6 G    5
    // 7 H    6

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == OptionalInt()));
    REQUIRE((map.find(1)->second == 0));
    REQUIRE((map.find(2)->second == 1));
    REQUIRE((map.find(3)->second == 2));
    REQUIRE((map.find(4)->second == 3));
    REQUIRE((map.find(5)->second == 4));
    REQUIRE((map.find(6)->second == 5));
    REQUIRE((map.find(7)->second == 6));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((*vector.at(index++) == 7));
    REQUIRE((vector.size() == index));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    index = 0U;
    REQUIRE((*vector.at(index++) == 0));
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((*vector.at(index++) == 7));
    REQUIRE((vector.size() == index));
}

TEST_CASE("deleteMap_DeleteSecond", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 1 });
    // 0 A    0
    // 1 B    Deleted
    // 2 C    1
    // 3 D    2
    // 4 E    3
    // 5 F    4
    // 6 G    5
    // 7 H    6

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == OptionalInt()));
    REQUIRE((map.find(2)->second == 1));
    REQUIRE((map.find(3)->second == 2));
    REQUIRE((map.find(4)->second == 3));
    REQUIRE((map.find(5)->second == 4));
    REQUIRE((map.find(6)->second == 5));
    REQUIRE((map.find(7)->second == 6));
    // Checks the vector.
    REQUIRE((vector.size() == 7));
    auto index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("deleteMap_DeleteSecondAndThird", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 1, 2 });
    // 0 A    0
    // 1 B    Deleted
    // 2 C    Deleted
    // 3 D    1
    // 4 E    2
    // 5 F    3
    // 6 G    4
    // 7 H    5

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == OptionalInt()));
    REQUIRE((map.find(2)->second == OptionalInt()));
    REQUIRE((map.find(3)->second == 1));
    REQUIRE((map.find(4)->second == 2));
    REQUIRE((map.find(5)->second == 3));
    REQUIRE((map.find(6)->second == 4));
    REQUIRE((map.find(7)->second == 5));
    // Checks the vector.
    REQUIRE((vector.size() == 6));
    auto index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("deleteMap_DeleteLast", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 7 });
    // 0 A    0
    // 1 B    1
    // 2 C    2
    // 3 D    3
    // 4 E    4
    // 5 F    5
    // 6 G    6
    // 7 H    Deleted

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 1));
    REQUIRE((map.find(2)->second == 2));
    REQUIRE((map.find(3)->second == 3));
    REQUIRE((map.find(4)->second == 4));
    REQUIRE((map.find(5)->second == 5));
    REQUIRE((map.find(6)->second == 6));
    REQUIRE((map.find(7)->second == OptionalInt()));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((*vector.at(index++) == 0));
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((vector.size() == index));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("deleteMap_DeleteTwo", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 1, 4 });
    // 0 A    0
    // 1 B    Deleted
    // 2 C    1
    // 3 D    2
    // 4 E    Deleted
    // 5 F    3
    // 6 G    4
    // 7 H    5

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == OptionalInt()));
    REQUIRE((map.find(2)->second == 1));
    REQUIRE((map.find(3)->second == 2));
    REQUIRE((map.find(4)->second == OptionalInt()));
    REQUIRE((map.find(5)->second == 3));
    REQUIRE((map.find(6)->second == 4));
    REQUIRE((map.find(7)->second == 5));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((*vector.at(index++) == 0));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((*vector.at(index++) == 7));
    REQUIRE((vector.size() == index));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("deleteMap_DeleteFirstAndLast", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 0, 7 });
    // 0 A    Deleted
    // 1 B    0
    // 2 C    1
    // 3 D    2
    // 4 E    3
    // 5 F    4
    // 6 G    5
    // 7 H    Deleted

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == OptionalInt()));
    REQUIRE((map.find(1)->second == 0));
    REQUIRE((map.find(2)->second == 1));
    REQUIRE((map.find(3)->second == 2));
    REQUIRE((map.find(4)->second == 3));
    REQUIRE((map.find(5)->second == 4));
    REQUIRE((map.find(6)->second == 5));
    REQUIRE((map.find(7)->second == OptionalInt()));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((*vector.at(index++) == 1));
    REQUIRE((*vector.at(index++) == 2));
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((*vector.at(index++) == 4));
    REQUIRE((*vector.at(index++) == 5));
    REQUIRE((*vector.at(index++) == 6));
    REQUIRE((vector.size() == index));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("deleteMap_DeleteAll", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 0, 1, 2, 3, 4, 5, 6, 7 });
    // 0 A    Deleted
    // 1 B    Deleted
    // 2 C    Deleted
    // 3 D    Deleted
    // 4 E    Deleted
    // 5 F    Deleted
    // 6 G    Deleted
    // 7 H    Deleted

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));
    REQUIRE((map.find(0)->second == OptionalInt()));
    REQUIRE((map.find(1)->second == OptionalInt()));
    REQUIRE((map.find(2)->second == OptionalInt()));
    REQUIRE((map.find(3)->second == OptionalInt()));
    REQUIRE((map.find(4)->second == OptionalInt()));
    REQUIRE((map.find(5)->second == OptionalInt()));
    REQUIRE((map.find(6)->second == OptionalInt()));
    REQUIRE((map.find(7)->second == OptionalInt()));

    // Checks the vector.
    REQUIRE((vector.empty()));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    auto index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("deleteMap_DeleteAllButOne", "[Remapper]")
{
    // Given.
    auto remapper = Remapper<int>::buildForDelete(8, { 0, 1, 2, 4, 5, 6, 7 });
    // 0 A    Deleted
    // 1 B    Deleted
    // 2 C    Deleted
    // 3 D    0
    // 4 E    Deleted
    // 5 F    Deleted
    // 6 G    Deleted
    // 7 H    Deleted

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<int>> vector;
    vector.push_back(std::make_unique<int>(0));
    vector.push_back(std::make_unique<int>(1));
    vector.push_back(std::make_unique<int>(2));
    vector.push_back(std::make_unique<int>(3));
    vector.push_back(std::make_unique<int>(4));
    vector.push_back(std::make_unique<int>(5));
    vector.push_back(std::make_unique<int>(6));
    vector.push_back(std::make_unique<int>(7));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.find(0)->second == OptionalInt()));
    REQUIRE((map.find(1)->second == OptionalInt()));
    REQUIRE((map.find(2)->second == OptionalInt()));
    REQUIRE((map.find(3)->second == 0));
    REQUIRE((map.find(4)->second == OptionalInt()));
    REQUIRE((map.find(5)->second == OptionalInt()));
    REQUIRE((map.find(6)->second == OptionalInt()));
    REQUIRE((map.find(7)->second == OptionalInt()));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((*vector.at(index++) == 3));
    REQUIRE((vector.size() == index));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((*vector.at(++index) == 0));
    REQUIRE((*vector.at(++index) == 1));
    REQUIRE((*vector.at(++index) == 2));
    REQUIRE((*vector.at(++index) == 3));
    REQUIRE((*vector.at(++index) == 4));
    REQUIRE((*vector.at(++index) == 5));
    REQUIRE((*vector.at(++index) == 6));
    REQUIRE((*vector.at(++index) == 7));
}

TEST_CASE("insert_First", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 0, std::move(itemsToInsert));
    // 0 A    1
    // 1 B    2
    // 2 C    3
    // 3 D    4
    // 4 E    5
    // 5 F    6
    // 6 G    7
    // 7 H    8

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entry does not appear in the mapping (where would it be?).
    REQUIRE((map.find(0)->second == 1));
    REQUIRE((map.find(1)->second == 2));
    REQUIRE((map.find(2)->second == 3));
    REQUIRE((map.find(3)->second == 4));
    REQUIRE((map.find(4)->second == 5));
    REQUIRE((map.find(5)->second == 6));
    REQUIRE((map.find(6)->second == 7));
    REQUIRE((map.find(7)->second == 8));
    // Checks the vector.
    REQUIRE((vector.size() == 9));             // But the new entry is here.
    auto index = -1U;
    REQUIRE((vector.at(++index)->getName() == "New"));
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}

TEST_CASE("insert_First_Several", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New1", true));
    itemsToInsert.push_back(std::make_unique<Expression>(false, "New2", true));
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New3", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 0, std::move(itemsToInsert));
    // 0 A    3
    // 1 B    4
    // 2 C    5
    // 3 D    6
    // 4 E    7
    // 5 F    8
    // 6 G    9
    // 7 H    10

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entry does not appear in the mapping (where would it be?).
    REQUIRE((map.find(0)->second == 3));
    REQUIRE((map.find(1)->second == 4));
    REQUIRE((map.find(2)->second == 5));
    REQUIRE((map.find(3)->second == 6));
    REQUIRE((map.find(4)->second == 7));
    REQUIRE((map.find(5)->second == 8));
    REQUIRE((map.find(6)->second == 9));
    REQUIRE((map.find(7)->second == 10));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((vector.at(index++)->getName() == "New1"));
    REQUIRE((vector.at(index++)->getName() == "New2"));
    REQUIRE((vector.at(index++)->getName() == "New3"));
    REQUIRE((vector.at(index++)->getName() == "0"));
    REQUIRE((vector.at(index++)->getName() == "1"));
    REQUIRE((vector.at(index++)->getName() == "2"));
    REQUIRE((vector.at(index++)->getName() == "3"));
    REQUIRE((vector.at(index++)->getName() == "4"));
    REQUIRE((vector.at(index++)->getName() == "5"));
    REQUIRE((vector.at(index++)->getName() == "6"));
    REQUIRE((vector.at(index++)->getName() == "7"));
    REQUIRE((vector.size() == index));


    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}

TEST_CASE("insert_Second", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 1, std::move(itemsToInsert));
    // 0 A    0
    // 1 B    2
    // 2 C    3
    // 3 D    4
    // 4 E    5
    // 5 F    6
    // 6 G    7
    // 7 H    8

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entry does not appear in the mapping (where would it be?).
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 2));
    REQUIRE((map.find(2)->second == 3));
    REQUIRE((map.find(3)->second == 4));
    REQUIRE((map.find(4)->second == 5));
    REQUIRE((map.find(5)->second == 6));
    REQUIRE((map.find(6)->second == 7));
    REQUIRE((map.find(7)->second == 8));
    // Checks the vector.
    REQUIRE((vector.size() == 9));             // But the new entry is here.
    auto index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "New"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}

TEST_CASE("insert_Last", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 8, std::move(itemsToInsert));
    // 0 A    0
    // 1 B    1
    // 2 C    2
    // 3 D    3
    // 4 E    4
    // 5 F    5
    // 6 G    6
    // 7 H    7

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entry does not appear in the mapping (where would it be?).
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 1));
    REQUIRE((map.find(2)->second == 2));
    REQUIRE((map.find(3)->second == 3));
    REQUIRE((map.find(4)->second == 4));
    REQUIRE((map.find(5)->second == 5));
    REQUIRE((map.find(6)->second == 6));
    REQUIRE((map.find(7)->second == 7));
    // Checks the vector.
    REQUIRE((vector.size() == 9));             // But the new entry is here.
    auto index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
    REQUIRE((vector.at(++index)->getName() == "New"));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}

TEST_CASE("insert_Last_Several", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(false, "New1", true));
    itemsToInsert.push_back(std::make_unique<Expression>(false, "New2", true));
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New3", true));
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New4", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 8, std::move(itemsToInsert));
    // 0 A    0
    // 1 B    1
    // 2 C    2
    // 3 D    3
    // 4 E    4
    // 5 F    5
    // 6 G    6
    // 7 H    7

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entries do not appear in the mapping (where would they be?).
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 1));
    REQUIRE((map.find(2)->second == 2));
    REQUIRE((map.find(3)->second == 3));
    REQUIRE((map.find(4)->second == 4));
    REQUIRE((map.find(5)->second == 5));
    REQUIRE((map.find(6)->second == 6));
    REQUIRE((map.find(7)->second == 7));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((vector.at(index++)->getName() == "0"));
    REQUIRE((vector.at(index++)->getName() == "1"));
    REQUIRE((vector.at(index++)->getName() == "2"));
    REQUIRE((vector.at(index++)->getName() == "3"));
    REQUIRE((vector.at(index++)->getName() == "4"));
    REQUIRE((vector.at(index++)->getName() == "5"));
    REQUIRE((vector.at(index++)->getName() == "6"));
    REQUIRE((vector.at(index++)->getName() == "7"));
    REQUIRE((vector.at(index++)->getName() == "New1"));
    REQUIRE((vector.at(index++)->getName() == "New2"));
    REQUIRE((vector.at(index++)->getName() == "New3"));
    REQUIRE((vector.at(index++)->getName() == "New4"));
    REQUIRE((vector.size() == index));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}

TEST_CASE("insert_BeforeLast", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 7, std::move(itemsToInsert));
    // 0 A    0
    // 1 B    1
    // 2 C    2
    // 3 D    3
    // 4 E    4
    // 5 F    5
    // 6 G    6
    // 7 H    8

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entry does not appear in the mapping (where would it be?).
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 1));
    REQUIRE((map.find(2)->second == 2));
    REQUIRE((map.find(3)->second == 3));
    REQUIRE((map.find(4)->second == 4));
    REQUIRE((map.find(5)->second == 5));
    REQUIRE((map.find(6)->second == 6));
    REQUIRE((map.find(7)->second == 8));
    // Checks the vector.
    REQUIRE((vector.size() == 9));             // But the new entry is here.
    auto index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "New"));
    REQUIRE((vector.at(++index)->getName() == "7"));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}

TEST_CASE("insert_Middle", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 4, std::move(itemsToInsert));
    // 0 A    0
    // 1 B    1
    // 2 C    2
    // 3 D    3
    // 4 E    5
    // 5 F    6
    // 6 G    7
    // 7 H    8

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entry does not appear in the mapping (where would it be?).
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 1));
    REQUIRE((map.find(2)->second == 2));
    REQUIRE((map.find(3)->second == 3));
    REQUIRE((map.find(4)->second == 5));
    REQUIRE((map.find(5)->second == 6));
    REQUIRE((map.find(6)->second == 7));
    REQUIRE((map.find(7)->second == 8));
    // Checks the vector.
    REQUIRE((vector.size() == 9));             // But the new entry is here.
    auto index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "New"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}

TEST_CASE("insert_Middle_Several", "[Remapper]")
{
    // Given.
    auto itemsToInsert = std::vector<std::unique_ptr<Expression>>();
    itemsToInsert.push_back(std::make_unique<Expression>(true, "New1", true));
    itemsToInsert.push_back(std::make_unique<Expression>(false, "New2", true));

    auto remapper = Remapper<Expression>::buildForInsert(8, 4, std::move(itemsToInsert));
    // 0 A    0
    // 1 B    1
    // 2 C    2
    // 3 D    3
    // 4 E    6
    // 5 F    7
    // 6 G    8
    // 7 H    9

    // When.
    const auto& map = remapper->getMapping();
    std::vector<std::unique_ptr<Expression>> vector;
    vector.push_back(std::make_unique<Expression>(true, "0", true));
    vector.push_back(std::make_unique<Expression>(true, "1", true));
    vector.push_back(std::make_unique<Expression>(true, "2", true));
    vector.push_back(std::make_unique<Expression>(true, "3", true));
    vector.push_back(std::make_unique<Expression>(true, "4", true));
    vector.push_back(std::make_unique<Expression>(true, "5", true));
    vector.push_back(std::make_unique<Expression>(true, "6", true));
    vector.push_back(std::make_unique<Expression>(true, "7", true));
    remapper->applyOnVector(vector);

    // Then.
    REQUIRE((map.size() == 8));                // The new entries does not appear in the mapping (where would they be?).
    REQUIRE((map.find(0)->second == 0));
    REQUIRE((map.find(1)->second == 1));
    REQUIRE((map.find(2)->second == 2));
    REQUIRE((map.find(3)->second == 3));
    REQUIRE((map.find(4)->second == 6));
    REQUIRE((map.find(5)->second == 7));
    REQUIRE((map.find(6)->second == 8));
    REQUIRE((map.find(7)->second == 9));
    // Checks the vector.
    auto index = 0U;
    REQUIRE((vector.at(index++)->getName() == "0"));
    REQUIRE((vector.at(index++)->getName() == "1"));
    REQUIRE((vector.at(index++)->getName() == "2"));
    REQUIRE((vector.at(index++)->getName() == "3"));
    REQUIRE((vector.at(index++)->getName() == "New1"));
    REQUIRE((vector.at(index++)->getName() == "New2"));
    REQUIRE((vector.at(index++)->getName() == "4"));
    REQUIRE((vector.at(index++)->getName() == "5"));
    REQUIRE((vector.at(index++)->getName() == "6"));
    REQUIRE((vector.at(index++)->getName() == "7"));
    REQUIRE((vector.size() == index));

    // Undo.
    // ------------
    remapper->undoOnVector(vector);

    // Checks.
    REQUIRE((vector.size() == 8));
    index = -1U;
    REQUIRE((vector.at(++index)->getName() == "0"));
    REQUIRE((vector.at(++index)->getName() == "1"));
    REQUIRE((vector.at(++index)->getName() == "2"));
    REQUIRE((vector.at(++index)->getName() == "3"));
    REQUIRE((vector.at(++index)->getName() == "4"));
    REQUIRE((vector.at(++index)->getName() == "5"));
    REQUIRE((vector.at(++index)->getName() == "6"));
    REQUIRE((vector.at(++index)->getName() == "7"));
}


}   // namespace arkostracker

