#include "../../../../catch.hpp"

#include "../../../../../source/business/song/tool/optimizers/ExpressionOptimizer.h"

namespace arkostracker 
{

TEST_CASE("ExpressionOptimizer, simple, nothing optimized", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildArpeggio("exp", false);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(7);
    expression.addValue(9);
    expression.setLoopStartAndEnd(0, 3);
    expression.setSpeed(2);
    const auto originalExpression = expression;

    // When.
    ExpressionOptimizer optimizer(expression, false);
    optimizer.optimize();

    // Then. No change.
    REQUIRE((expression == originalExpression));
}

TEST_CASE("ExpressionOptimizer, could be optimized, but no because not flattened", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildArpeggio("exp", false);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(7);
    expression.addValue(7);
    expression.setLoopStartAndEnd(0, 5);
    expression.setSpeed(3);
    const auto originalExpression = expression;

    // When.
    ExpressionOptimizer optimizer(expression, false);
    optimizer.optimize();

    // Then. No change.
    REQUIRE((expression == originalExpression));
}

TEST_CASE("ExpressionOptimizer, not flattened so only last unused cells are removed", "[ExpressionOptimizer]")
{
    // Given.
    auto originalExpression = Expression::buildArpeggio("exp", false);
    originalExpression.addValue(0);
    originalExpression.addValue(0);
    originalExpression.addValue(3);
    originalExpression.addValue(3);
    originalExpression.addValue(7);
    originalExpression.addValue(7);
    originalExpression.addValue(0);
    originalExpression.addValue(1);
    originalExpression.addValue(2);
    originalExpression.addValue(3);
    originalExpression.setLoopStartAndEnd(0, 5);

    auto expectedExpression = Expression::buildArpeggio("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(3);
    expectedExpression.addValue(7);
    expectedExpression.addValue(7);
    expectedExpression.setLoopStartAndEnd(0, 5);

    // When.
    ExpressionOptimizer optimizer(originalExpression, false);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == originalExpression));
}

TEST_CASE("ExpressionOptimizer, flattened, remove duplicates", "[ExpressionOptimizer]")
{
    // Given.
    auto originalExpression = Expression::buildPitch("exp", false);
    originalExpression.addValue(0);
    originalExpression.addValue(0);
    originalExpression.addValue(0);
    originalExpression.addValue(3);
    originalExpression.addValue(3);
    originalExpression.addValue(3);
    originalExpression.addValue(7);
    originalExpression.addValue(7);
    originalExpression.addValue(7);
    originalExpression.setLoopStartAndEnd(0, 8);
    originalExpression.setSpeed(2);

    auto expectedExpression = Expression::buildPitch("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(7);
    expectedExpression.setLoopStartAndEnd(0, 2);
    expectedExpression.setSpeed(8);

    // When.
    ExpressionOptimizer optimizer(originalExpression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == originalExpression));
}

TEST_CASE("ExpressionOptimizer, shift without flattening, nothing optimized", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildArpeggio("exp", false);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(7);
    expression.addValue(9);
    expression.setLoopStartAndEnd(0, 3);
    expression.setSpeed(1);
    expression.setShift(5);

    auto expectedExpression = Expression::buildArpeggio("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(7);
    expectedExpression.addValue(9);
    expectedExpression.setLoopStartAndEnd(0, 3);
    expectedExpression.setSpeed(1);
    expectedExpression.setShift(5);

    // When.
    ExpressionOptimizer optimizer(expression, false);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, shift with flattening, nothing optimized", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildPitch("exp", false);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(7);
    expression.addValue(9);
    expression.setLoopStartAndEnd(0, 3);
    expression.setSpeed(1);
    expression.setShift(5);

    auto expectedExpression = Expression::buildPitch("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(7);
    expectedExpression.addValue(9);
    expectedExpression.setLoopStartAndEnd(5, 8);
    expectedExpression.setSpeed(1);
    expectedExpression.setShift(0);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, shift with flattening, unused cells optimized", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildArpeggio("exp", false);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(7);
    expression.addValue(9);
    expression.addValue(4);
    expression.addValue(9);
    expression.setLoopStartAndEnd(0, 3);
    expression.setSpeed(1);
    expression.setShift(5);

    auto expectedExpression = Expression::buildArpeggio("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(7);
    expectedExpression.addValue(9);
    expectedExpression.setLoopStartAndEnd(5, 8);
    expectedExpression.setSpeed(1);
    expectedExpression.setShift(0);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, optimized loop", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildArpeggio("exp", false);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.setLoopStartAndEnd(0, 11);
    expression.setSpeed(1);
    expression.setShift(0);

    auto expectedExpression = Expression::buildArpeggio("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(9);
    expectedExpression.addValue(12);
    expectedExpression.setLoopStartAndEnd(0, 3);
    expectedExpression.setSpeed(5);
    expectedExpression.setShift(0);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, optimized loop, unused cells removed", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildPitch("exp", false);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.setLoopStartAndEnd(0, 15);
    expression.setSpeed(2);
    expression.setShift(0);

    auto expectedExpression = Expression::buildPitch("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(9);
    expectedExpression.addValue(12);
    expectedExpression.setLoopStartAndEnd(0, 3);
    expectedExpression.setSpeed(11);
    expectedExpression.setShift(0);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, unable to optimized loop because one item wrong", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildPitch("exp", false);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.setLoopStartAndEnd(0, 16);
    expression.setSpeed(2);
    expression.setShift(0);

    const auto expectedExpression = expression;

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, unable to optimized loop because one item wrong, but useless cells removed.", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::buildPitch("exp", false);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(0);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(3);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(9);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(12);
    expression.addValue(14);
    expression.addValue(14);
    expression.setLoopStartAndEnd(0, 16);
    expression.setSpeed(2);
    expression.setShift(0);

    auto expectedExpression = Expression::buildPitch("exp", false);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(0);
    expectedExpression.addValue(3);
    expectedExpression.addValue(3);
    expectedExpression.addValue(3);
    expectedExpression.addValue(3);
    expectedExpression.addValue(9);
    expectedExpression.addValue(9);
    expectedExpression.addValue(9);
    expectedExpression.addValue(9);
    expectedExpression.addValue(12);
    expectedExpression.addValue(12);
    expectedExpression.addValue(12);
    expectedExpression.addValue(12);
    expectedExpression.addValue(12);
    expectedExpression.setLoopStartAndEnd(0, 16);
    expectedExpression.setSpeed(2);
    expectedExpression.setShift(0);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, remove cycle of 1", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", false, { 1, 1, 1, 1 });
    const auto expectedExpression = Expression::build("exp", false, { 1 });

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, remove cycle of 3", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 3, 7, 0, 3, 7 });
    const auto expectedExpression = Expression::build("exp", true, { 0, 3, 7 });

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, remove cycle of 3, loop at 2", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 1, 0, 3, 7, 0, 3, 7 });
    expression.setLoopStartAndEnd(2, 7);
    auto expectedExpression = Expression::build("exp", true, { 0, 1, 0, 3, 7 });
    expectedExpression.setLoopStartAndEnd(2, 4);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, remove cycle of 3, loop at 1", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 1, 2, 3, 0, 1, 2, 3, 0 });
    expression.setLoopStartAndEnd(1, 8);
    auto expectedExpression = Expression::build("exp", true, { 0, 1, 2, 3 });
    expectedExpression.setLoopStartAndEnd(0, 3);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, integrate loop if cycle", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", false, { 0, 3, 0, 3 });
    expression.setLoopStartAndEnd(2, 3);
    auto expectedExpression = Expression::build("exp", false, { 0, 3 });
    expectedExpression.setLoopStartAndEnd(0, 1);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, integrate loop if cycle, two cycles", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 3, 0, 3, 0, 3 });
    expression.setLoopStartAndEnd(4, 5);
    auto expectedExpression = Expression::build("exp", true, { 0, 3 });
    expectedExpression.setLoopStartAndEnd(0, 1);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, integrate loop if cycle, one cycle", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 0, 0, 0 });
    expression.setLoopStartAndEnd(2, 3);
    auto expectedExpression = Expression::build("exp", true, { 0 });
    expectedExpression.setLoopStartAndEnd(0, 0);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, remove 1-sized loop with the same multiple value before", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", false, { 0, 0, 0, 0, 0, 0 });
    expression.setLoopStartAndEnd(5, 5);
    auto expectedExpression = Expression::build("exp", false, { 0 });
    expectedExpression.setLoopStartAndEnd(0, 0);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expectedExpression == expression));
}

TEST_CASE("ExpressionOptimizer, cannot be optimized because no real cycle", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 0, 0, 0, -5, -5, -5, -7, -7, -7, -0xb, -0xb, -0xb, -0xb, -7, -7, -7, -5, -5, -5});
    expression.setLoopStartAndEnd(0, 19);
    const auto originalExpression = expression;

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then. No change.
    REQUIRE((expression == originalExpression));
}

TEST_CASE("ExpressionOptimizer, can be optimized because real cycle, plus preloop optimization", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 0, 0, -5, -5, -5, -7, -7, -7, -0xb, -0xb, -0xb, -7, -7, -7, -5, -5, -5});
    expression.setLoopStartAndEnd(6, 17);
    auto expectedExpression = Expression::build("exp", true, { 0, -5, -7, -0xb, -7 });
    expectedExpression.setLoopStartAndEnd(1, 4);
    expectedExpression.setSpeed(2);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expression == expectedExpression));
}

TEST_CASE("ExpressionOptimizer, preloop optimization", "[ExpressionOptimizer]")
{
    // Given.
    auto expression = Expression::build("exp", true, { 0, 1, 2, 3, 4, 5, 0, 1, 2 });
    expression.setLoopStartAndEnd(3, 8);
    auto expectedExpression = Expression::build("exp", true, { 0, 1, 2, 3, 4, 5 });
    expectedExpression.setLoopStartAndEnd(0, 5);

    // When.
    ExpressionOptimizer optimizer(expression, true);
    optimizer.optimize();

    // Then.
    REQUIRE((expression == expectedExpression));
}

}   // namespace arkostracker
