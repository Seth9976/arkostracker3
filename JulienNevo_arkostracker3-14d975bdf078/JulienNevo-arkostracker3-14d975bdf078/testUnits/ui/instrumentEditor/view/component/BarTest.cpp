#include "../../../../catch.hpp"

#include "../../../../../source/ui/editorWithBars/view/component/Bar.cpp"

namespace arkostracker 
{

TEST_CASE("calculateBarTopAndHeight, volume 15", "[Bar]")
{
    // This line produces an error which tells us the full name of `BarTest`
    // aggregate 'blah::Test<blah::BarTest> blah::t' has incomplete type and cannot be defined
    //Test<BarTest> t;

    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto value = 15;
    constexpr auto displayRatio = 10;           // 10 pixels per value.

    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    // Expects the full bar.
    REQUIRE(displayedValue.getTop() == 0);
    REQUIRE(displayedValue.getHeight() == 160);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}


TEST_CASE("calculateBarTopAndHeight, volume 14", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 14;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 10);
    REQUIRE(displayedValue.getHeight() == 150);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume 12", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 12;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 30);
    REQUIRE(displayedValue.getHeight() == 130);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume 1", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 1;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 140);
    REQUIRE(displayedValue.getHeight() == 20);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume 0", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 0;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 150);
    REQUIRE(displayedValue.getHeight() == 10);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume 15, signed", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = -15;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 15;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 0);
    REQUIRE(displayedValue.getHeight() == 160);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume 0, signed", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = -15;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 0;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 150);
    REQUIRE(displayedValue.getHeight() == 10);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume -1, signed", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = -15;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = -1;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 160);
    REQUIRE(displayedValue.getHeight() == 10);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume -2, signed", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = -15;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = -2;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 160);
    REQUIRE(displayedValue.getHeight() == 20);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume -15, signed", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = -15;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = -15;
    const BarData barData(false, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 160);
    REQUIRE(displayedValue.getHeight() == 150);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}


// ==================================================

TEST_CASE("calculateBarTopAndHeight, volume 15, shortBar", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 15;
    const BarData barData(true, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 0);
    REQUIRE(displayedValue.getHeight() == 10);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume 1, shortBar", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 1;
    const BarData barData(true, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 140);
    REQUIRE(displayedValue.getHeight() == 10);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

TEST_CASE("calculateBarTopAndHeight, volume 0, shortBar", "[Bar]")
{
    // Given.
    constexpr auto minimumValue = 0;
    constexpr auto maximumValue = 15;
    constexpr auto valueRange = maximumValue - minimumValue + 1;
    constexpr auto displayRatio = 10;           // 10 pixels per value.
    constexpr auto value = 0;
    const BarData barData(true, minimumValue, maximumValue, value,
                    LookAndFeelConstants::Colors::barPitchBackground, LookAndFeelConstants::Colors::barPitch,
                    false, false, false, false, false, false, false, false);

    Bar bar(0);
    bar.setDisplayedData(barData);
    bar.setSize(40, valueRange * displayRatio);

    // When.
    const auto displayedValue = bar.calculateBarTopAndHeight();

    // Then.
    REQUIRE(displayedValue.getTop() == 150);
    REQUIRE(displayedValue.getHeight() == 10);
    REQUIRE(!displayedValue.isOutOfVisibleMinMax());
}

// TODO Out of bounds.


}   // namespace arkostracker

