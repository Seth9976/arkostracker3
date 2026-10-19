#include "../../catch.hpp"

#include <BinaryData.h>
#include <juce_core/juce_core.h>

#include "../../../source/import/common/AmsdosHeaderUtil.h"

namespace arkostracker
{

TEST_CASE("AmsdosHeaderUtil, no header, soundtrakker", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::Targhan__Deep_Space_Resonance_128, BinaryData::Targhan__Deep_Space_Resonance_128Size);
    const auto newMemoryBlock = AmsdosHeaderUtil::removeHeaderIfNeeded(memoryBlock);

    REQUIRE(memoryBlock == newMemoryBlock);
}

TEST_CASE("AmsdosHeaderUtil, no header, Heppe", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::Kangaroo__Heppe2_128, BinaryData::Kangaroo__Heppe2_128Size);
    const auto hasHeader = AmsdosHeaderUtil::isHeaderPresent(memoryBlock);

    REQUIRE_FALSE(hasHeader);
}

TEST_CASE("AmsdosHeaderUtil, header, SKS song", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::TwistWithHeader_sks, BinaryData::TwistWithHeader_sksSize);
    const auto hasHeader = AmsdosHeaderUtil::isHeaderPresent(memoryBlock);

    REQUIRE(hasHeader);
}

TEST_CASE("AmsdosHeaderUtil, header, 128 song", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::ResonanceWithHeader_128, BinaryData::ResonanceWithHeader_128Size);
    const auto hasHeader = AmsdosHeaderUtil::isHeaderPresent(memoryBlock);

    REQUIRE(hasHeader);
}

TEST_CASE("AmsdosHeaderUtil, no header, starkos", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::Targhan__DemoIzArt__Twist_Part_sks, BinaryData::Targhan__DemoIzArt__Twist_Part_sksSize);
    const auto newMemoryBlock = AmsdosHeaderUtil::removeHeaderIfNeeded(memoryBlock);

    REQUIRE(memoryBlock == newMemoryBlock);
}

TEST_CASE("AmsdosHeaderUtil, header, soundtrakker", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::ResonanceWithHeader_128, BinaryData::ResonanceWithHeader_128Size);
    const auto newMemoryBlock = AmsdosHeaderUtil::removeHeaderIfNeeded(memoryBlock);
    REQUIRE(memoryBlock != newMemoryBlock);

    const auto memoryBlockWithoutHeader = juce::MemoryBlock(static_cast<const char*>(memoryBlock.getData()) + 128,memoryBlock.getSize() - 128);
    REQUIRE(newMemoryBlock == memoryBlockWithoutHeader);
}

TEST_CASE("AmsdosHeaderUtil, header, starkos", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::TwistWithHeader_sks, BinaryData::TwistWithHeader_sksSize);
    const auto newMemoryBlock = AmsdosHeaderUtil::removeHeaderIfNeeded(memoryBlock);
    REQUIRE(memoryBlock != newMemoryBlock);

    const auto memoryBlockWithoutHeader = juce::MemoryBlock(static_cast<const char*>(memoryBlock.getData()) + 128,memoryBlock.getSize() - 128);
    REQUIRE(newMemoryBlock == memoryBlockWithoutHeader);
}

TEST_CASE("AmsdosHeaderUtil, no header, abadia", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::ABADIA1_CHPZ80_Load500_BIN, BinaryData::ABADIA1_CHPZ80_Load500_BINSize);
    REQUIRE(!AmsdosHeaderUtil::isHeaderPresent(memoryBlock));
}

TEST_CASE("AmsdosHeaderUtil, header, abadia", "[AmsdosHeaderUtil]")
{
    const auto memoryBlock = juce::MemoryBlock(BinaryData::ABADIA1_CHPZ80_withHeader_BIN, BinaryData::ABADIA1_CHPZ80_withHeader_BINSize);
    REQUIRE(AmsdosHeaderUtil::isHeaderPresent(memoryBlock));
}

}   // namespace arkostracker
