#include "../../../catch.hpp"

#include "../../../../source/business/serialization/sourceProfile/SourceProfileSerializer.h"
#include "../../../../source/business/serialization/sourceProfile/SourceProfileXmlNodes.h"
#include "../../../../source/business/sourceProfile/SourceProfile.h"
#include "../../../../source/utils/XmlHelper.h"
#include "../XmlTestHelper.h"

namespace arkostracker 
{

TEST_CASE("SourceProfileSerializer, serialization", "[SourceProfileSerializer]")
{
    // Given.
    std::vector<SourceProfile> sourceProfiles;
    {
        const SourceGeneratorConfiguration configuration("adr {x}", "comm {x}", true,
                                                   "db {x}", "dw {x}", "da {x}", "ds  {x}",
                                                   "equ {x}", ".{x}:",
                                                   true, "asm", "bin", 6);
        sourceProfiles.emplace_back(configuration, "first", false);
    }
    {
        const SourceGeneratorConfiguration configuration("org {x}", ";{x}", false,
                                                   "db {x}", "dw {x}", "da {x}", "ds {x}",
                                                   "= {x}",
                                                   "{x}", false, "a", "b", 3);
        sourceProfiles.emplace_back(configuration, "second", true);
    }

    // When.
    const auto xmlElement = SourceProfileSerializer::serialize(sourceProfiles);

    // Then.
    REQUIRE((xmlElement != nullptr));
    REQUIRE((xmlElement->getNumChildElements() == 2));
    {
        const auto* sourceProfileNode = xmlElement->getChildElement(0);
        REQUIRE((sourceProfileNode->getNumChildElements() == 15));
        REQUIRE((sourceProfileNode->getTagName() == SourceProfileXmlNodes::sourceProfileRoot));
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::name, "first");
        XmlTestHelper::checkXmlBool(sourceProfileNode, SourceProfileXmlNodes::readOnly, false);
        XmlTestHelper::checkXmlBool(sourceProfileNode, SourceProfileXmlNodes::littleEndian, true);
        XmlTestHelper::checkXmlBool(sourceProfileNode, SourceProfileXmlNodes::generateComments, true);
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::commentDeclaration, "comm {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::addressChangeDeclaration, "adr {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::addressDeclaration, "da {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::byteDeclaration, "db {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::wordDeclaration, "dw {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::labelDeclaration, ".{x}:");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::stringDeclaration, "ds  {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::constantDeclaration, "equ {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::binaryFileExtension, "bin");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::sourceFileExtension, "asm");
        XmlTestHelper::checkXmlInt(sourceProfileNode, SourceProfileXmlNodes::tabulationLength, 6);
    }
    {
        const auto* sourceProfileNode = xmlElement->getChildElement(1);
        REQUIRE((sourceProfileNode->getNumChildElements() == 15));
        REQUIRE((sourceProfileNode->getTagName() == SourceProfileXmlNodes::sourceProfileRoot));
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::name, "second");
        XmlTestHelper::checkXmlBool(sourceProfileNode, SourceProfileXmlNodes::readOnly, true);
        XmlTestHelper::checkXmlBool(sourceProfileNode, SourceProfileXmlNodes::littleEndian, false);
        XmlTestHelper::checkXmlBool(sourceProfileNode, SourceProfileXmlNodes::generateComments, false);
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::commentDeclaration, ";{x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::addressChangeDeclaration, "org {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::addressDeclaration, "da {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::byteDeclaration, "db {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::wordDeclaration, "dw {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::labelDeclaration, "{x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::stringDeclaration, "ds {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::constantDeclaration, "= {x}");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::binaryFileExtension, "b");
        XmlTestHelper::checkXmlString(sourceProfileNode, SourceProfileXmlNodes::sourceFileExtension, "a");
        XmlTestHelper::checkXmlInt(sourceProfileNode, SourceProfileXmlNodes::tabulationLength, 3);
    }
}

TEST_CASE("SourceProfileSerializer, deserialization", "[SourceProfileSerializer]")
{
    // Given.
    juce::XmlElement rootNode(SourceProfileXmlNodes::sourceProfilesRoot);
    // Creates SourceProfile 0.
    {
        auto& sourceProfileNode = XmlHelper::addNode(rootNode, SourceProfileXmlNodes::sourceProfileRoot);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::name, "First");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::readOnly, true);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::littleEndian, false);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::generateComments, true);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::commentDeclaration, "com{x}");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::addressChangeDeclaration, "org {x}");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::addressDeclaration, "dw {x}");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::byteDeclaration, "db {x}");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::wordDeclaration, "db {x}\r\naaa");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::labelDeclaration, "--{x}--");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::stringDeclaration, "{x} str");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::binaryFileExtension, "bin");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::sourceFileExtension, "asm");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::tabulationLength, 16);
    }
    // Creates SourceProfile 1.
    {
        auto& sourceProfileNode = XmlHelper::addNode(rootNode, SourceProfileXmlNodes::sourceProfileRoot);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::name, "Second");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::readOnly, false);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::littleEndian, true);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::generateComments, false);
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::commentDeclaration, "com{x}com");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::addressChangeDeclaration, "{x}");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::addressDeclaration, "dw {x}\r\n aaa\r\nbbb");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::byteDeclaration, "db {x}");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::wordDeclaration, "db {x}\r\naaa");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::labelDeclaration, "--{x}--");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::stringDeclaration, "{x} str");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::binaryFileExtension, "b");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::sourceFileExtension, "a");
        XmlHelper::addValueNode(sourceProfileNode, SourceProfileXmlNodes::tabulationLength, 1);
    }

    // When.
    const auto sourceProfiles = SourceProfileSerializer::deserialize(rootNode);

    // Then.
    REQUIRE((sourceProfiles.size() == 2U));
    {
        // SourceProfile 0.
        const auto& sourceProfile = sourceProfiles.at(0U);
        REQUIRE((sourceProfile.getName() == "First"));
        REQUIRE(sourceProfile.isReadOnly());
        const auto& configuration = sourceProfile.getSourceGeneratorConfiguration();
        REQUIRE_FALSE(configuration.isLittleEndian());
        REQUIRE(configuration.doesGenerateComments());
        REQUIRE((configuration.getCommentDeclaration() == "com{x}"));
        REQUIRE((configuration.getAddressChangeDeclaration() == "org {x}"));
        REQUIRE((configuration.getAddressDeclaration() == "dw {x}"));
        REQUIRE((configuration.getByteDeclaration() == "db {x}"));
        REQUIRE((configuration.getWordDeclaration() == "db {x}\r\naaa"));
        REQUIRE((configuration.getLabelDeclaration() == "--{x}--"));
        REQUIRE((configuration.getStringDeclaration() == "{x} str"));
        REQUIRE((configuration.getBinaryFileExtension() == "bin"));
        REQUIRE((configuration.getSourceFileExtension() == "asm"));
        REQUIRE((configuration.getTabulationLength() == 16));
    }
    {
        // SourceProfile 1.
        const auto& sourceProfile = sourceProfiles.at(1U);
        REQUIRE((sourceProfile.getName() == "Second"));
        REQUIRE_FALSE(sourceProfile.isReadOnly());
        const auto& configuration = sourceProfile.getSourceGeneratorConfiguration();
        REQUIRE(configuration.isLittleEndian());
        REQUIRE_FALSE(configuration.doesGenerateComments());
        REQUIRE((configuration.getCommentDeclaration() == "com{x}com"));
        REQUIRE((configuration.getAddressChangeDeclaration() == "{x}"));
        REQUIRE((configuration.getAddressDeclaration() == "dw {x}\r\n aaa\r\nbbb"));
        REQUIRE((configuration.getByteDeclaration() == "db {x}"));
        REQUIRE((configuration.getWordDeclaration() == "db {x}\r\naaa"));
        REQUIRE((configuration.getLabelDeclaration() == "--{x}--"));
        REQUIRE((configuration.getStringDeclaration() == "{x} str"));
        REQUIRE((configuration.getBinaryFileExtension() == "b"));
        REQUIRE((configuration.getSourceFileExtension() == "a"));
        REQUIRE((configuration.getTabulationLength() == 1));
    }
}

}   // namespace arkostracker
