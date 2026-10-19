#include "../../../catch.hpp"

#include "../../../../source/business/serialization/patternViewer/EffectToCharSerializer.h"
#include "../XmlTestHelper.h"
#include "../../../../source/utils/XmlHelper.h"

namespace arkostracker 
{

TEST_CASE("Serialization of effectToChar", "[EffectToCharSerializer]")
{
    // Given.
    const std::unordered_map<Effect, juce::juce_wchar> originalEffectToChar = {
            { Effect::arpeggioTable, 'a' },
            { Effect::arpeggio3Notes, 'b' },
            { Effect::reset, 'r' },
    };

    // When.
    auto serializedXml = EffectToCharSerializer::serialize(originalEffectToChar);
    auto& rootElement = *serializedXml;

    // Then.
    // --------------------
    // The root.
    REQUIRE(rootElement.hasTagName(EffectToCharSerializer::nodeRoot));
    REQUIRE(rootElement.getNumChildElements() == 3);
    auto foundArpeggioTable = false;
    auto foundArpeggio3Notes = false;
    auto foundReset = false;

    // It is unordered, so don't expect on... an order. This makes the code clumsier.
    for (auto index = 0; index < 3; ++index) {
        const auto& xmlEntry = rootElement.getChildElement(index);
        REQUIRE(xmlEntry->hasTagName(EffectToCharSerializer::nodeEntry));
        REQUIRE(xmlEntry->getNumChildElements() == 2);

        const auto& nodeEffect = xmlEntry->getChildByName(EffectToCharSerializer::nodeEffect);
        if (nodeEffect->getAllSubText() == "arpeggioTable") {
            REQUIRE_FALSE(foundArpeggioTable);
            XmlTestHelper::checkXmlString(xmlEntry, EffectToCharSerializer::nodeChar, "a");
            foundArpeggioTable = true;
        } else if (nodeEffect->getAllSubText() == "reset") {
            REQUIRE_FALSE(foundReset);
            XmlTestHelper::checkXmlString(xmlEntry, EffectToCharSerializer::nodeChar, "r");
            foundReset = true;
        } else if (nodeEffect->getAllSubText() == "arpeggio3Notes") {
            REQUIRE_FALSE(foundArpeggio3Notes);
            XmlTestHelper::checkXmlString(xmlEntry, EffectToCharSerializer::nodeChar, "b");
            foundArpeggio3Notes = true;
        } else {
            REQUIRE(false);
        }
    }

    REQUIRE(foundArpeggioTable);
    REQUIRE(foundArpeggio3Notes);
    REQUIRE(foundReset);
}

TEST_CASE("Deserialization of effectToChar", "[EffectToCharSerializer]")
{
    // Given.
    juce::XmlElement rootNode(EffectToCharSerializer::nodeRoot);
    {
        auto& entryNode = XmlHelper::addNode(rootNode, EffectToCharSerializer::nodeEntry);
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeEffect, "reset");
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeChar, "8");
    }
    {
        auto& entryNode = XmlHelper::addNode(rootNode, EffectToCharSerializer::nodeEntry);
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeEffect, "volumeIn");
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeChar, "k");
    }
    {
        auto& entryNode = XmlHelper::addNode(rootNode, EffectToCharSerializer::nodeEntry);
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeEffect, "fastPitchUp");
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeChar, "4");
    }
    {
        auto& entryNode = XmlHelper::addNode(rootNode, EffectToCharSerializer::nodeEntry);
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeEffect, "unknown");         // An unknown effect. Must be skipped.
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeChar, "a");
    }
    {
        auto& entryNode = XmlHelper::addNode(rootNode, EffectToCharSerializer::nodeEntry);
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeEffect, "reset");
        XmlHelper::addValueNode(entryNode, EffectToCharSerializer::nodeChar, "abc");               // Overwrites with an invalid char. Must be skipped.
    }

    // When.
    const auto effectToChar = EffectToCharSerializer::deserialize(rootNode);

    // Then.
    REQUIRE(effectToChar.size() == 16);
    REQUIRE(effectToChar.at(Effect::arpeggioTable) == 'a');
    REQUIRE(effectToChar.at(Effect::arpeggio3Notes) == 'b');
    REQUIRE(effectToChar.at(Effect::arpeggio4Notes) == 'c');
    REQUIRE(effectToChar.at(Effect::pitchUp) == 'u');
    REQUIRE(effectToChar.at(Effect::pitchDown) == 'd');
    REQUIRE(effectToChar.at(Effect::pitchGlide) == 'g');
    REQUIRE(effectToChar.at(Effect::pitchTable) == 'p');
    REQUIRE(effectToChar.at(Effect::volume) == 'v');
    REQUIRE(effectToChar.at(Effect::volumeIn) == 'k');
    REQUIRE(effectToChar.at(Effect::volumeOut) == 'o');
    REQUIRE(effectToChar.at(Effect::reset) == '8');
    REQUIRE(effectToChar.at(Effect::forceInstrumentSpeed) == 's');
    REQUIRE(effectToChar.at(Effect::forceArpeggioSpeed) == 'w');
    REQUIRE(effectToChar.at(Effect::forcePitchTableSpeed) == 'x');
    REQUIRE(effectToChar.at(Effect::fastPitchUp) == '4');
    REQUIRE(effectToChar.at(Effect::fastPitchDown) == 'f');
}

}   // namespace arkostracker
