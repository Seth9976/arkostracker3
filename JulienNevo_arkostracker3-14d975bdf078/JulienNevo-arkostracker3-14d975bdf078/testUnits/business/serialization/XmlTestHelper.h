#pragma once

#include <juce_core/juce_core.h>

#include "../../catch.hpp"

namespace arkostracker
{

/** Contains some methods to help test XML. */
class XmlTestHelper
{
public:
    static void checkXmlString(const juce::XmlElement* xmlElement, const juce::String& node, const juce::String& expected);
    static void checkXmlString(const juce::XmlElement* xmlElement, int childIndex, const juce::String& expectedNodeName, const juce::String& expected);

    static void checkXmlInt(const juce::XmlElement* xmlElement, const juce::String& nodeName, int expected);
    static void checkXmlFloat(const juce::XmlElement* xmlElement, const juce::String& nodeName, float expected);
    static void checkXmlBool(const juce::XmlElement* xmlElement, const juce::String& nodeName, bool expected);

    static void checkNodeAbsent(const juce::XmlElement* xmlElement, const juce::String& nodeName);

    static const juce::XmlElement* getChildByIndex(const juce::XmlElement& xmlElement, int childIndex, const juce::String& expectedNodeName);
};

}   // namespace arkostracker
