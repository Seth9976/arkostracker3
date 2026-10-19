#include "../../../catch.hpp"

#include "../../../../source/business/serialization/song/ExpressionSerializer.h"
#include "../../../../source/utils/XmlHelper.h"
#include "../XmlTestHelper.h"

namespace arkostracker 
{

TEST_CASE("serialization, one expression without values", "[ExpressionSerializer]")
{
    // Given.
    std::vector<Expression> expressions;
    {
        const Expression expression(true, "First", false);
        expressions.push_back(expression);
    }

    // When.
    auto serializedXml = ExpressionSerializer::serialize(expressions);
    auto& rootElement = *serializedXml;

    // Then.
    // --------------------
    // The root.
    REQUIRE(rootElement.hasTagName(ExpressionSerializer::nodeExpressionsRoot));
    REQUIRE(rootElement.getNumChildElements() == 1);
    // The first expression.
    const auto* expressionElement = rootElement.getChildByName(ExpressionSerializer::nodeExpressionRoot);
    REQUIRE(expressionElement != nullptr);
    REQUIRE(expressionElement->getNumChildElements() == 7);
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeName, "First");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeIsArpeggio, "true");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeSpeed, "0");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeShift, "0");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeLoopStartIndex, "0");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeEndIndex, "0");
    const auto* valuesElement = expressionElement->getChildByName(ExpressionSerializer::nodeValues);
    REQUIRE(valuesElement->getNumChildElements() == 0);
}

TEST_CASE("serialization, one with one value", "[ExpressionSerializer]")
{
    // Given.
    std::vector<Expression> expressions;
    {
        Expression expression(false, "First", false);
        expression.addValue(56);
        expression.setName("First2");
        expression.setLoopStartAndEnd(0, 0);
        expression.setSpeed(12);

        expressions.push_back(expression);
    }

    // When.
    auto serializedXml = ExpressionSerializer::serialize(expressions);
    auto& rootElement = *serializedXml;

    // Then.
    // --------------------
    // The root.
    REQUIRE(rootElement.hasTagName(ExpressionSerializer::nodeExpressionsRoot));
    REQUIRE(rootElement.getNumChildElements() == 1);
    // The first expression.
    const auto* expressionElement = rootElement.getChildByName(ExpressionSerializer::nodeExpressionRoot);
    REQUIRE(expressionElement != nullptr);
    REQUIRE(expressionElement->getNumChildElements() == 7);
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeName, "First2");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeIsArpeggio, "false");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeSpeed, "12");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeShift, "0");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeLoopStartIndex, "0");
    XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeEndIndex, "0");
    const auto* valuesElement = expressionElement->getChildByName(ExpressionSerializer::nodeValues);
    REQUIRE(valuesElement->getNumChildElements() == 1);
    XmlTestHelper::checkXmlString(valuesElement, ExpressionSerializer::nodeValue, "56");
}

TEST_CASE("serialization, two", "[ExpressionSerializer]")
{
    // Given.
    std::vector<Expression> expressions;
    {
        Expression expression(true, "", false);
        expression.addValue(56);
        expression.addValue(12);
        expression.addValue(-15);
        expression.addValue(-30);
        expression.setLoopStartAndEnd(1, 3);
        expression.setSpeed(255);
        expression.setShift(12);

        expressions.push_back(expression);
    }
    {
        Expression expression(false, "Second", false);
        expression.addValue(-40);
        expression.addValue(40);
        expression.addValue(0);
        expression.addValue(1);
        expression.addValue(-1);
        expression.setLoopStartAndEnd(3, 4);
        expression.setSpeed(100);
        expression.setShift(255);

        expressions.push_back(expression);
    }

    // When.
    auto serializedXml = ExpressionSerializer::serialize(expressions);
    auto& rootElement = *serializedXml;

    // Then.
    // --------------------
    // The root.
    REQUIRE(rootElement.hasTagName(ExpressionSerializer::nodeExpressionsRoot));
    REQUIRE(rootElement.getNumChildElements() == 2);
    // Expression 0.
    {
        const auto* expressionElement = XmlTestHelper::getChildByIndex(rootElement, 0, ExpressionSerializer::nodeExpressionRoot);
        REQUIRE(expressionElement != nullptr);
        REQUIRE(expressionElement->getNumChildElements() == 7);
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeName, "");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeIsArpeggio, "true");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeSpeed, "255");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeShift, "12");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeLoopStartIndex, "1");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeEndIndex, "3");
        const auto* valuesElement = expressionElement->getChildByName(ExpressionSerializer::nodeValues);
        auto index = 0;
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "56");
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "12");
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "-15");
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "-30");
        REQUIRE(valuesElement->getNumChildElements() == index);
    }
    // Expression 1.
    {
        const auto* expressionElement = XmlTestHelper::getChildByIndex(rootElement, 1, ExpressionSerializer::nodeExpressionRoot);
        REQUIRE(expressionElement != nullptr);
        REQUIRE(expressionElement->getNumChildElements() == 7);
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeName, "Second");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeIsArpeggio, "false");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeSpeed, "100");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeShift, "255");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeLoopStartIndex, "3");
        XmlTestHelper::checkXmlString(expressionElement, ExpressionSerializer::nodeEndIndex, "4");
        const auto* valuesElement = expressionElement->getChildByName(ExpressionSerializer::nodeValues);
        auto index = 0;
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "-40");
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "40");
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "0");
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "1");
        XmlTestHelper::checkXmlString(valuesElement, index++, ExpressionSerializer::nodeValue, "-1");
        REQUIRE(valuesElement->getNumChildElements() == index);
    }
}


// ----------------------------------------------------

TEST_CASE("deserialization, empty", "[ExpressionSerializer]")
{
    // Given.
    const juce::XmlElement rootNode(ExpressionSerializer::nodeExpressionsRoot);

    // When.
    const auto deserializedExpressions = ExpressionSerializer::deserializeExpressions(rootNode);

    // Then.
    REQUIRE(deserializedExpressions.empty());
}

TEST_CASE("deserialization, one", "[ExpressionSerializer]")
{
    // Given.
    juce::XmlElement rootNode(ExpressionSerializer::nodeExpressionsRoot);
    // Creates Expression 0.
    {
        auto& expressionNode = XmlHelper::addNode(rootNode, ExpressionSerializer::nodeExpressionRoot);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeName, "First");
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeIsArpeggio, true);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeSpeed, 5);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeLoopStartIndex, 1);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeEndIndex, 2);
        auto& valuesNode = XmlHelper::addNode(expressionNode, ExpressionSerializer::nodeValues);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 1);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, -1);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 0);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 50);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, -49);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 72);
    }

    // When.
    auto deserializedExpressions = ExpressionSerializer::deserializeExpressions(rootNode);

    // Then.
    // Expression 0.
    REQUIRE(deserializedExpressions.size() == 1U);
    {
        auto& expression = *deserializedExpressions.at(0U);
        REQUIRE(expression.getName() == "First");
        REQUIRE(expression.isArpeggio());
        REQUIRE(expression.getSpeed() == 5);
        REQUIRE(expression.getLoopStart() == 1);
        REQUIRE(expression.getEnd() == 2);
        auto index = 0;
        REQUIRE(expression.getValue(index++) == 1);
        REQUIRE(expression.getValue(index++) == -1);
        REQUIRE(expression.getValue(index++) == 0);
        REQUIRE(expression.getValue(index++) == 50);
        REQUIRE(expression.getValue(index++) == -49);
        REQUIRE(expression.getValue(index++) == 72);
        REQUIRE(index == 6);
    }
}

TEST_CASE("deserialization, two", "[ExpressionSerializer]")
{
    // Given.
    juce::XmlElement rootNode(ExpressionSerializer::nodeExpressionsRoot);
    // Creates Expression 0.
    {
        auto& expressionNode = XmlHelper::addNode(rootNode, ExpressionSerializer::nodeExpressionRoot);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeName, "Yeah");
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeIsArpeggio, false);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeSpeed, 0);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeLoopStartIndex, 3);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeEndIndex, 3);
        auto& valuesNode = XmlHelper::addNode(expressionNode, ExpressionSerializer::nodeValues);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, -50);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 0);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 50);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 30);
    }
    // Creates Expression 1.
    {
        auto& expressionNode = XmlHelper::addNode(rootNode, ExpressionSerializer::nodeExpressionRoot);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeName, "Yeah2");
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeIsArpeggio, true);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeSpeed, 1);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeLoopStartIndex, 1);
        XmlHelper::addValueNode(expressionNode, ExpressionSerializer::nodeEndIndex, 1);
        auto& valuesNode = XmlHelper::addNode(expressionNode, ExpressionSerializer::nodeValues);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, 1);
        XmlHelper::addValueNode(valuesNode, ExpressionSerializer::nodeValue, -1);
    }

    // When.
    auto deserializedExpressions = ExpressionSerializer::deserializeExpressions(rootNode);

    // Then.
    // Expression 0.
    REQUIRE(deserializedExpressions.size() == 2U);
    {
        auto& expression = *deserializedExpressions.at(0U);
        REQUIRE(expression.getName() == "Yeah");
        REQUIRE(!expression.isArpeggio());
        REQUIRE(expression.getSpeed() == 0);
        REQUIRE(expression.getLoopStart() == 3);
        REQUIRE(expression.getEnd() == 3);
        auto index = 0;
        REQUIRE(expression.getValue(index++) == -50);
        REQUIRE(expression.getValue(index++) == 0);
        REQUIRE(expression.getValue(index++) == 50);
        REQUIRE(expression.getValue(index++) == 30);
        REQUIRE(index == 4);
    }
    {
        auto& expression = *deserializedExpressions.at(1U);
        REQUIRE(expression.getName() == "Yeah2");
        REQUIRE(expression.isArpeggio());
        REQUIRE(expression.getSpeed() == 1);
        REQUIRE(expression.getLoopStart() == 1);
        REQUIRE(expression.getEnd() == 1);
        auto index = 0;
        REQUIRE(expression.getValue(index++) == 1);
        REQUIRE(expression.getValue(index++) == -1);
        REQUIRE(index == 2);
    }
}

}   // namespace arkostracker
