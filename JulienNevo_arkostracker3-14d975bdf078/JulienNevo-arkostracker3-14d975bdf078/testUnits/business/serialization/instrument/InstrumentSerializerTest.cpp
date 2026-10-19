#include "../../../catch.hpp"

#include "../../../../source/business/serialization/instrument//InstrumentNodes.h"
#include "../../../../source/business/serialization/instrument//InstrumentSerializer.h"
#include "../../../../source/song/instrument/psg/PsgPartConstants.h"
#include "../../../../source/utils/MemoryBlockUtil.h"
#include "../../../../source/utils/XmlHelper.h"
#include "../XmlTestHelper.h"

namespace arkostracker 
{

class Check
{
public:
    static void checkInstrumentCell(const juce::XmlElement* node, const int volume, const int noise,
                             const int primaryPeriod, const int primaryArpeggioNoteInOctave, const int primaryArpeggioOctave, const int primaryPitch,
                             const PsgInstrumentCellLink link, const int ratio, const int hardwareEnvelope,
                             const int secondaryPeriod, const int secondaryArpeggioNoteInOctave, const int secondaryArpeggioOctave, const int secondaryPitch,
                             const bool isRetrig)
    {
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeVolume, volume);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeNoise, noise);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodePrimaryPeriod, primaryPeriod);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodePrimaryArpeggioNoteInOctave, primaryArpeggioNoteInOctave);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodePrimaryArpeggioOctave, primaryArpeggioOctave);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodePrimaryPitch, primaryPitch);
        XmlTestHelper::checkXmlString(node, InstrumentNodes::nodeLink, PsgInstrumentCellLinkHelper::toString(link));
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeRatio, ratio);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeHardwareEnvelope, hardwareEnvelope);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeSecondaryPeriod, secondaryPeriod);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeSecondaryArpeggioNoteInOctave, secondaryArpeggioNoteInOctave);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeSecondaryArpeggioOctave, secondaryArpeggioOctave);
        XmlTestHelper::checkXmlInt(node, InstrumentNodes::nodeSecondaryPitch, secondaryPitch);
        XmlTestHelper::checkXmlBool(node, InstrumentNodes::nodeIsRetrig, isRetrig);
    }
};

TEST_CASE("Instrument serialization, empty PSG instrument", "[InstrumentSerializer]")
{
    // Given.
    auto instrument = Instrument::buildEmptyPsgInstrument();

    // When.
    const auto instrumentNode = InstrumentSerializer::serialize(*instrument);

    // Then.
    REQUIRE((instrumentNode != nullptr));
    // The instrument root.
    REQUIRE(instrumentNode->hasTagName(InstrumentNodes::nodeInstrumentRoot));
    REQUIRE((instrumentNode->getNumChildElements() == 10));
    XmlTestHelper::checkXmlString(instrumentNode.get(), InstrumentNodes::nodeName, "Empty");
    XmlTestHelper::checkXmlString(instrumentNode.get(), InstrumentNodes::nodeType, "psg");
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeColorArgb, static_cast<int>(Instrument::defaultColor));
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeSpeed, PsgPartConstants::slowestSpeed);
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeLoopStartIndex, 0);
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeEndIndex, 0);
    XmlTestHelper::checkXmlBool(instrumentNode.get(), InstrumentNodes::nodeIsLooping, true);
    XmlTestHelper::checkXmlBool(instrumentNode.get(), InstrumentNodes::nodeIsRetrig, false);
    XmlTestHelper::checkNodeAbsent(instrumentNode.get(), InstrumentNodes::nodeAutoSpread);
    XmlTestHelper::checkXmlBool(instrumentNode.get(), InstrumentNodes::nodeSfxIsExported, true);

    // Cells.
    const auto cellsNodes = XmlHelper::getChildrenList(instrumentNode.get(), InstrumentNodes::nodeCells);
    REQUIRE((cellsNodes.size() == 1U));
    const auto* cellsNode = cellsNodes.at(0U);
    REQUIRE((cellsNode->getNumChildElements() == 1));

    const auto* cellNode = cellsNode->getChildByName(InstrumentNodes::nodeCell);
    REQUIRE((cellNode->getNumChildElements() == 14));
    Check::checkInstrumentCell(cellNode, 0, 0, 0, 0, 0, 0,
                        PsgInstrumentCellLink::noSoftNoHard, 4, 8,
                        0, 0, 0, 0, false);
}

// TODO more PSG instruments.

TEST_CASE("Instrument serialization, Sample instrument", "[InstrumentSerializer]")
{
    // Given.
    const juce::String originalFilename = "myDrum.wav";

    // Creates a dummy sample.
    const auto sampleData = MemoryBlockUtil::fromVector({ 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U });
    const auto sample = std::make_shared<Sample>(sampleData);
    const SamplePart samplePart(sample, Loop(5, 7, true), 1.5F, 22050, 42, originalFilename);
    const auto instrument = Instrument::buildSampleInstrument("kick", samplePart, 0xff112233);

    // When.
    const auto instrumentNode = InstrumentSerializer::serialize(*instrument);

    // Then.
    REQUIRE((instrumentNode != nullptr));
    // The instrument root.
    REQUIRE(instrumentNode->hasTagName(InstrumentNodes::nodeInstrumentRoot));
    REQUIRE((instrumentNode->getNumChildElements() == 11));
    XmlTestHelper::checkXmlString(instrumentNode.get(), InstrumentNodes::nodeName, "kick");
    XmlTestHelper::checkXmlString(instrumentNode.get(), InstrumentNodes::nodeType, "sample");
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeColorArgb, static_cast<int>(0xff112233));
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeLoopStartIndex, 5);
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeEndIndex, 7);
    XmlTestHelper::checkXmlBool(instrumentNode.get(), InstrumentNodes::nodeIsLooping, true);
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeFrequencyHz, 22050);
    XmlTestHelper::checkXmlFloat(instrumentNode.get(), InstrumentNodes::nodeAmplificationRatio, 1.5F);
    XmlTestHelper::checkXmlString(instrumentNode.get(), InstrumentNodes::nodeOriginalFilename, originalFilename);
    XmlTestHelper::checkXmlString(instrumentNode.get(), InstrumentNodes::nodeSampleUnsigned8BitsBase64, "AAECAwQFBgcICQ==");
    XmlTestHelper::checkXmlInt(instrumentNode.get(), InstrumentNodes::nodeDigiNote, 42);
}

TEST_CASE("Instrument deserialization, Sample instrument", "[InstrumentSerializer]")
{
    // Given.
    const juce::String originalFilename = "myDrum.wav";
    juce::XmlElement rootNode(InstrumentNodes::nodeInstrumentsRoot);

    // Creates Instrument Sample 0.
    {
        auto& expressionNode = XmlHelper::addNode(rootNode, InstrumentNodes::nodeInstrumentRoot);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeName, "First");
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeType, "sample");
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeColorArgb, 0xffeeddaa);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeLoopStartIndex, 2);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeEndIndex, 4);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeIsLooping, true);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeFrequencyHz, 12345);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeAmplificationRatio, 0.3F);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeOriginalFilename, originalFilename);
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeSampleUnsigned8BitsBase64, "AAECAwQFBgcICQ==");
        XmlHelper::addValueNode(expressionNode, InstrumentNodes::nodeDigiNote, 31);
    }

    // When.
    const auto instruments = InstrumentSerializer::deserializeInstruments(rootNode);

    // Then.
    REQUIRE((instruments.size() == 1U));
    const auto& instrument = instruments.at(0U);
    REQUIRE((instrument->getName() == "First"));
    REQUIRE((instrument->getType() == InstrumentType::sampleInstrument));
    REQUIRE((instrument->getArgbColor() == 0xffeeddaa));
    const auto& samplePart = instrument->getConstSamplePart();
    REQUIRE((samplePart.getLoop() == Loop(2, 4, true)));
    REQUIRE(juce::exactlyEqual(samplePart.getAmplificationRatio(), 0.3F));
    REQUIRE((samplePart.getFrequencyHz() == 12345));
    REQUIRE((samplePart.getDigidrumNote() == 31));
    REQUIRE((samplePart.getOriginalFileName() == originalFilename));
    const auto sample = samplePart.getSample();
    REQUIRE((sample->getLength() == 10));
    const auto sampleData = sample->getData();
    REQUIRE((sampleData[0] == 0));
    REQUIRE((sampleData[1] == 1));
    REQUIRE((sampleData[2] == 2));
    REQUIRE((sampleData[3] == 3));
    REQUIRE((sampleData[4] == 4));
    REQUIRE((sampleData[5] == 5));
    REQUIRE((sampleData[6] == 6));
    REQUIRE((sampleData[7] == 7));
    REQUIRE((sampleData[8] == 8));
    REQUIRE((sampleData[9] == 9));
    REQUIRE((sampleData.getSize() == 10U));
}

}   // namespace arkostracker
