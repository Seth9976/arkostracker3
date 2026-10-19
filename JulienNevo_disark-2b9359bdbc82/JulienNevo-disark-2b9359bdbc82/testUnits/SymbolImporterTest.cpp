#include "catch.hpp"

#include "../sources/import/SymbolImporter.h"
#include "utils/MemoryBlockUtil.h"

#include <juce_core/juce_core.h>

namespace disark
{

static void checkLine(const juce::String& line, const juce::String& expectedLabel, int expectedAddress, int labelIndex, int addressIndex, bool expectError)
{
    std::vector<juce::String> strings;
    strings.emplace_back(line);

    auto memoryBlock = MemoryBlockUtil::fromStrings(strings);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    SymbolImporter symbolImporter(inputStream);
    auto labelsAndErrors = symbolImporter.import(labelIndex, addressIndex);

    auto labelsAndAddresses = labelsAndErrors.first;
    auto errorString = labelsAndErrors.second;
    if (expectError) {
        REQUIRE(errorString.isNotEmpty());
    } else {
        REQUIRE(errorString.isEmpty());
    }

    if (!expectError) {
        REQUIRE(labelsAndAddresses.size() == 1);
        REQUIRE(labelsAndAddresses.at(0).getLabel() == expectedLabel);
        REQUIRE(labelsAndAddresses.at(0).getAddress() == expectedAddress);
    }
}

static void expectError(const std::vector<juce::String>& strings)
{
    auto memoryBlock = MemoryBlockUtil::fromStrings(strings);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    SymbolImporter symbolImporter(inputStream);
    auto labelsAndErrors = symbolImporter.import();

    auto errorString = labelsAndErrors.second;
    REQUIRE(errorString.isNotEmpty());
}

TEST_CASE("SymbolImporter, simple", "[SymbolImporter]")
{
    std::vector<juce::String> strings;
    strings.emplace_back("LABEL1 #4000 B0");
    strings.emplace_back("LABEL2 &abcd B0");
    strings.emplace_back("LABEL3 0xAFDE B0");
    strings.emplace_back("");
    strings.emplace_back("LABEL4 0X0 B0");
    strings.emplace_back("LABEL5 0X12a B0");
    strings.emplace_back(".LABEL6 #13a B0");
    strings.emplace_back("LABEL7: #1 B0");
    strings.emplace_back(".LABEL8: #ffff B0");
    strings.emplace_back(".LABEL9 16384 B0 C0");
    strings.emplace_back("L10 0 B0 C0");
    strings.emplace_back("L11 65535 B0 C0");

    auto memoryBlock = MemoryBlockUtil::fromStrings(strings);
    juce::MemoryInputStream inputStream(memoryBlock, false);

    SymbolImporter symbolImporter(inputStream);
    auto labelsAndErrors = symbolImporter.import();

    auto labelsAndAddresses = labelsAndErrors.first;
    auto errorString = labelsAndErrors.second;
    REQUIRE(errorString.isEmpty());

    size_t index = 0;
    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL1");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0x4000);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL2");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0xabcd);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL3");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0xafde);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL4");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0x0);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL5");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0x12a);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL6");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0x13a);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL7");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0x1);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL8");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0xffff);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "LABEL9");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0x4000);

    REQUIRE(labelsAndAddresses.at(index).getLabel() == "L10");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0x0);
    REQUIRE(labelsAndAddresses.at(index).getLabel() == "L11");
    REQUIRE(labelsAndAddresses.at(index++).getAddress() == 0xffff);

    REQUIRE(labelsAndAddresses.size() == index);
}

TEST_CASE("SymbolImporter, errors", "[SymbolImporter]")
{
    // One word only.
    {
        std::vector<juce::String> strings;
        strings.emplace_back("LABEL1");
        expectError(strings);
    }

    // Unreadable address.
    {
        std::vector<juce::String> strings;
        strings.emplace_back("LABEL1 abc");
        expectError(strings);
    }
    {
        std::vector<juce::String> strings;
        strings.emplace_back("LABEL1 0x");
        expectError(strings);
    }
    {
        std::vector<juce::String> strings;
        strings.emplace_back("LABEL1 0xzzz");
        expectError(strings);
    }
}


TEST_CASE("SymbolImporter, position", "[SymbolImporter]")
{
    checkLine("LABEL5 #f", "LABEL5", 0xf, 0, 1, false);
    checkLine("bob LABEL1 #4000", "LABEL1", 0x4000, 1, 2, false);
    checkLine("bob bobette LABEL2 0x4000", "LABEL2", 0x4000, 2, 3, false);
    checkLine("bob bobette .LABEL3 micheline $abcd", "LABEL3", 0xabcd, 2, 4, false);
    checkLine("1234 LABEL4:", "LABEL4", 1234, 1, 0, false);
    checkLine("&4567 robert LABEL5", "LABEL5", 0x4567, 2, 0, false);
    checkLine("robert LABEL6 &45 yeah", "LABEL6", 0x45, 1, 2, false);
}

TEST_CASE("SymbolImporter, positionErrors", "[SymbolImporter]")
{
    checkLine("LABEL5 #f", "", 0, -1, 1, true);
    checkLine("LABEL5 #f", "", 0, -1, -1, true);
    checkLine("LABEL5 #f", "", 0, 1, -1, true);
    checkLine("LABEL5 #f", "", 0, 1, 2, true);
    checkLine("LABEL5 #f", "", 0, 2, 1, true);
}

}    // namespace disark
