#include "../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../source/reader/vgm/VgmReader.h"
#include "../../source/song/psg/PsgFrequency.h"

namespace arkostracker 
{

TEST_CASE("Import A Harmless Grenade", "[VgmReader]")
{
    // Given.
    juce::MemoryInputStream inputStream(BinaryData::HarmlessLoopAt4_vgm, BinaryData::HarmlessLoopAt4_vgmSize, false);

    // When.
    VgmReader vgmReader(inputStream);

    auto success = vgmReader.checkFormat();
    REQUIRE(success);

    success = vgmReader.prepare();
    REQUIRE(success);

    // Then.
    REQUIRE(vgmReader.getPsgCount() == 1);
    REQUIRE(vgmReader.getPsgType(0) == PsgType::ay);
    REQUIRE(vgmReader.getPsgFrequencyHz(0) == PsgFrequency::psgFrequencyCPC);
    REQUIRE(juce::exactlyEqual(vgmReader.getPlayerReplayHz(), PsgFrequency::defaultReplayFrequencyHz));
    REQUIRE(vgmReader.getIterationCount() == 3072);
    REQUIRE(vgmReader.getLoopIndex() == 768);
    REQUIRE(vgmReader.getTitle() == "A Harmless Grenade - Main");
    REQUIRE(vgmReader.getAuthor() == "Targhan");
    // TODO

    constexpr auto psgIndex = 0;
    auto iterationIndex = 0;
    {
        const auto regs = vgmReader.getRegisters(psgIndex, iterationIndex++);
        REQUIRE(regs.second);
        const auto envAndRetrig = regs.first.getHardwareEnvelopeAndRetrig();
        REQUIRE(envAndRetrig.getEnvelope() == 0x8);
        REQUIRE(envAndRetrig.isRetrig());       // FIXME Not sure about this.
    }
    {
        const auto regs = vgmReader.getRegisters(psgIndex, iterationIndex++);
        REQUIRE(regs.second);
        const auto envAndRetrig = regs.first.getHardwareEnvelopeAndRetrig();
        REQUIRE(envAndRetrig.getEnvelope() == 0x8);
        REQUIRE_FALSE(envAndRetrig.isRetrig());
    }
    {
        const auto regs = vgmReader.getRegisters(psgIndex, iterationIndex++);
        REQUIRE(regs.second);
        const auto envAndRetrig = regs.first.getHardwareEnvelopeAndRetrig();
        REQUIRE(envAndRetrig.getEnvelope() == 0x8);
        REQUIRE_FALSE(envAndRetrig.isRetrig());
    }
    {
        const auto regs = vgmReader.getRegisters(psgIndex, iterationIndex++);
        REQUIRE(regs.second);
        const auto envAndRetrig = regs.first.getHardwareEnvelopeAndRetrig();
        REQUIRE(envAndRetrig.getEnvelope() == 0x8);
        REQUIRE_FALSE(envAndRetrig.isRetrig());
    }
}


}   // namespace arkostracker

