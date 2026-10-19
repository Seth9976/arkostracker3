#include "XmlTestHelper.h"

namespace arkostracker 
{

void XmlTestHelper::checkXmlString(const juce::XmlElement* xmlElement, const juce::String& node, const juce::String& expected)
{
    const auto* nameElement = xmlElement->getChildByName(node);
    REQUIRE(nameElement->getNumChildElements() == 1);
    REQUIRE(nameElement->getAllSubText() == expected);
}

void XmlTestHelper::checkXmlInt(const juce::XmlElement* xmlElement, const juce::String& nodeName, int expected)
{
    const auto* nameElement = xmlElement->getChildByName(nodeName);
    REQUIRE(nameElement->getNumChildElements() == 1);
    REQUIRE(nameElement->getAllSubText().getIntValue() == expected);
}

void XmlTestHelper::checkXmlFloat(const juce::XmlElement* xmlElement, const juce::String& nodeName, float expected)
{
    const auto* nameElement = xmlElement->getChildByName(nodeName);
    REQUIRE(nameElement->getNumChildElements() == 1);
    REQUIRE(juce::exactlyEqual(nameElement->getAllSubText().getFloatValue(), expected));
}

void XmlTestHelper::checkXmlBool(const juce::XmlElement* xmlElement, const juce::String& nodeName, bool expected)
{
    const auto* nameElement = xmlElement->getChildByName(nodeName);
    REQUIRE(nameElement->getNumChildElements() == 1);

    const auto string = nameElement->getAllSubText();
    REQUIRE((expected ? (string == "true") : (string == "false")));
}

void XmlTestHelper::checkXmlString(const juce::XmlElement* xmlElement, int childIndex, const juce::String& expectedNodeName, const juce::String& expected)
{
    const auto* childElement = xmlElement->getChildElement(childIndex);
    REQUIRE(childElement != nullptr);

    REQUIRE(childElement->hasTagName(expectedNodeName));
    REQUIRE(childElement->getNumChildElements() == 1);
    REQUIRE(childElement->getAllSubText() == expected);
}

const juce::XmlElement* XmlTestHelper::getChildByIndex(const juce::XmlElement& xmlElement, int childIndex, const juce::String& expectedNodeName)
{
    const auto* childElement = xmlElement.getChildElement(childIndex);

    REQUIRE(childElement != nullptr);
    REQUIRE(childElement->hasTagName(expectedNodeName));

    return childElement;
}

void XmlTestHelper::checkNodeAbsent(const juce::XmlElement* xmlElement, const juce::String& nodeName)
{
    const auto* nameElement = xmlElement->getChildByName(nodeName);
    REQUIRE(nameElement == nullptr);
}


}   // namespace arkostracker

