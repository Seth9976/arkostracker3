#include <BinaryData.h>

#include "../../../catch.hpp"

#include "../../../../source/business/serialization/instrument/InstrumentDeserializerAt2.h"
#include "../../../../source/song/psg/PsgType.h"

namespace arkostracker
{

TEST_CASE("Instrument deserialization, JonDunnBass", "[InstrumentDeserializerAt2]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::AT2Bass_Jon_Dunn_xml, static_cast<size_t>(BinaryData::AT2Bass_Jon_Dunn_xmlSize), false);

    const auto string = inputStream.readEntireStreamAsString();
    juce::XmlDocument xmlDocument(string);
    const auto xmlElement = xmlDocument.getDocumentElement();
    REQUIRE((xmlElement != nullptr));

    // Deserializes the XML.
    const auto instrument = InstrumentDeserializerAt2::deserializeInstrument(*xmlElement);
    REQUIRE((instrument != nullptr));

    REQUIRE((instrument->getName() == "Bass Jon Dunn"));
    REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
    const auto& psgPart = instrument->getConstPsgPart();
    REQUIRE((psgPart.getSpeed() == 0));
    REQUIRE((psgPart.getLength() == 17));
    REQUIRE((psgPart.getMainLoop() == Loop(0, 16, false)));

    REQUIRE((psgPart.isInstrumentRetrig() == false));
    REQUIRE((psgPart.getCellRefConst(0) == PsgInstrumentCell::buildSoftwareCell(15, 1, 0,
        -1, 0, true, 0)));
    REQUIRE((psgPart.getCellRefConst(1) == PsgInstrumentCell::buildSoftwareCell(15, 0, 0,
        -1, 0, true, 0)));
    REQUIRE((psgPart.getCellRefConst(2) == PsgInstrumentCell::buildSoftwareCell(14, 0, 0,-1, 0, true, 0)));
    const auto baseCell = PsgInstrumentCell::buildSoftwareCell(14, 0, 0,0, 0, true, 0);
    REQUIRE((psgPart.getCellRefConst(3) == baseCell));
    REQUIRE((psgPart.getCellRefConst(4) == baseCell.withVolume(13)));
    REQUIRE((psgPart.getCellRefConst(5) == baseCell.withVolume(12)));
    REQUIRE((psgPart.getCellRefConst(6) == baseCell.withVolume(11)));
    REQUIRE((psgPart.getCellRefConst(7) == baseCell.withVolume(10)));
    REQUIRE((psgPart.getCellRefConst(8) == baseCell.withVolume(9)));
    REQUIRE((psgPart.getCellRefConst(9) == baseCell.withVolume(8)));
    REQUIRE((psgPart.getCellRefConst(10) == baseCell.withVolume(7)));
    REQUIRE((psgPart.getCellRefConst(11) == baseCell.withVolume(6)));
    REQUIRE((psgPart.getCellRefConst(12) == baseCell.withVolume(5)));
    REQUIRE((psgPart.getCellRefConst(13) == baseCell.withVolume(4)));
    REQUIRE((psgPart.getCellRefConst(14) == baseCell.withVolume(3)));
    REQUIRE((psgPart.getCellRefConst(15) == baseCell.withVolume(2)));
    REQUIRE((psgPart.getCellRefConst(16) == baseCell.withVolume(1)));
}

TEST_CASE("Instrument deserialization, laugh", "[InstrumentDeserializerAt2]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::AT2Fenyx_Kell_Laugh_xml, static_cast<size_t>(BinaryData::AT2Fenyx_Kell_Laugh_xmlSize), false);

    const auto string = inputStream.readEntireStreamAsString();
    juce::XmlDocument xmlDocument(string);
    const auto xmlElement = xmlDocument.getDocumentElement();
    REQUIRE((xmlElement != nullptr));

    // Deserializes the XML.
    const auto instrument = InstrumentDeserializerAt2::deserializeInstrument(*xmlElement);
    REQUIRE((instrument != nullptr));

    REQUIRE((instrument->getName() == "Fenyx Kell Laugh"));
    REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
    const auto& psgPart = instrument->getConstPsgPart();
    REQUIRE((psgPart.getSpeed() == 1));
    REQUIRE((psgPart.getLength() == 0x1b));
    REQUIRE((psgPart.getMainLoop() == Loop(0, 0x1a, false)));

    REQUIRE((psgPart.isInstrumentRetrig() == false));
    REQUIRE((psgPart.getCellRefConst(0).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(8, 0,
        0, 0, 0, true, 0))));
    REQUIRE((psgPart.getCellRefConst(1).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(9, 0,
        0, 0, 0x1a, true, 0))));
    REQUIRE((psgPart.getCellRefConst(2).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xb, 0,
        0, 0, 0x29, true, 0))));
    REQUIRE((psgPart.getCellRefConst(3).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0xc, 0,
        0, 0, 0x32, true, 0))));
    REQUIRE((psgPart.getCellRefConst(4).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x0, 0,
        0, 0, 0x0, true, 0))));

    REQUIRE((psgPart.getCellRefConst(0x1a).isMusicallyEqualTo(PsgInstrumentCell::buildSoftwareCell(0x7, 0,
        0, 0, -2, true, 0))));
}

TEST_CASE("Instrument deserialization, what is that", "[InstrumentDeserializerAt2]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::AT2What_Is_That_xml, static_cast<size_t>(BinaryData::AT2What_Is_That_xmlSize), false);

    const auto string = inputStream.readEntireStreamAsString();
    juce::XmlDocument xmlDocument(string);
    const auto xmlElement = xmlDocument.getDocumentElement();
    REQUIRE((xmlElement != nullptr));

    // Deserializes the XML.
    const auto instrument = InstrumentDeserializerAt2::deserializeInstrument(*xmlElement);
    REQUIRE((instrument != nullptr));

    REQUIRE((instrument->getName() == "What Is That"));
    REQUIRE((instrument->getType() == InstrumentType::psgInstrument));
    const auto& psgPart = instrument->getConstPsgPart();
    REQUIRE((psgPart.getSpeed() == 2));
    REQUIRE((psgPart.getLength() == 0x12));
    REQUIRE((psgPart.getMainLoop() == Loop(0, 0x11, true)));

    REQUIRE((psgPart.isInstrumentRetrig() == false));
    const auto baseCell = PsgInstrumentCell(
        PsgInstrumentCellLink::softAndHard, 15, 0, 0, 0, 0, 0, 4,
        1, 0, 5, 0, 0xa, false,
        PsgValues::defaultSidActivated, PsgValues::defaultSidBalancePercent, PsgValues::defaultSidLowShelfVolume, PsgValues::defaultSidRatio,
        PsgValues::defaultSidArpeggio, PsgValues::defaultSidPitch);
    REQUIRE((psgPart.getCellRefConst(0) == baseCell));
    REQUIRE((psgPart.getCellRefConst(1) == baseCell.withSecondaryPeriod(2)));
    REQUIRE((psgPart.getCellRefConst(2) == baseCell.withSecondaryPeriod(3)));
    REQUIRE((psgPart.getCellRefConst(3) == baseCell.withSecondaryPeriod(4)));
    REQUIRE((psgPart.getCellRefConst(4) == baseCell.withSecondaryPeriod(5)));
    REQUIRE((psgPart.getCellRefConst(5) == baseCell.withSecondaryPeriod(6)));
    REQUIRE((psgPart.getCellRefConst(6) == baseCell.withSecondaryPeriod(7)));
    REQUIRE((psgPart.getCellRefConst(7) == baseCell.withSecondaryPeriod(8)));
    REQUIRE((psgPart.getCellRefConst(8) == baseCell.withSecondaryPeriod(9)));
    REQUIRE((psgPart.getCellRefConst(9) == baseCell.withSecondaryPeriod(0xa)));
    REQUIRE((psgPart.getCellRefConst(0xa) == baseCell.withSecondaryPeriod(9)));
    REQUIRE((psgPart.getCellRefConst(0xb) == baseCell.withSecondaryPeriod(8)));
    REQUIRE((psgPart.getCellRefConst(0xc) == baseCell.withSecondaryPeriod(7)));
    REQUIRE((psgPart.getCellRefConst(0xd) == baseCell.withSecondaryPeriod(6)));
    REQUIRE((psgPart.getCellRefConst(0xe) == baseCell.withSecondaryPeriod(5)));
    REQUIRE((psgPart.getCellRefConst(0xf) == baseCell.withSecondaryPeriod(4)));
    REQUIRE((psgPart.getCellRefConst(0x10) == baseCell.withSecondaryPeriod(3)));
    REQUIRE((psgPart.getCellRefConst(0x11) == baseCell.withSecondaryPeriod(2)));
}

}   // namespace arkostracker
