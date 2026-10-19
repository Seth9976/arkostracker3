#include "../../catch.hpp"

#include "../../../source/export/aky/process/RegisterBlock.h"
#include "../../../source/export/aky/process/RegisterBlockOptimizer.h"

namespace arkostracker 
{

TEST_CASE("AkyRegisterBlockOptimizer, determineSplit1", "[AkyRegisterBlockOptimizer]")
{
    // Decreasing sound with something else at the end.
    constexpr auto softwarePeriod = 100;
    const ChannelOutputRegisters channelRegisters1(ChannelOutputRegisters(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters2(ChannelOutputRegisters(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters3(ChannelOutputRegisters(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters4(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters5(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters6(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters7(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters8(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters9(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters10(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters11(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters12(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters13(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters14(ChannelOutputRegisters(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters15(ChannelOutputRegisters(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));

    RegisterBlock registerBlock;
    registerBlock.addChannelRegisters(channelRegisters1);
    registerBlock.addChannelRegisters(channelRegisters2);
    registerBlock.addChannelRegisters(channelRegisters3);
    registerBlock.addChannelRegisters(channelRegisters4);
    registerBlock.addChannelRegisters(channelRegisters5);
    registerBlock.addChannelRegisters(channelRegisters6);
    registerBlock.addChannelRegisters(channelRegisters7);
    registerBlock.addChannelRegisters(channelRegisters8);
    registerBlock.addChannelRegisters(channelRegisters9);
    registerBlock.addChannelRegisters(channelRegisters10);
    registerBlock.addChannelRegisters(channelRegisters11);
    registerBlock.addChannelRegisters(channelRegisters12);
    registerBlock.addChannelRegisters(channelRegisters13);
    registerBlock.addChannelRegisters(channelRegisters14);
    registerBlock.addChannelRegisters(channelRegisters15);

    auto result = RegisterBlockOptimizer::findAndSplitBlocksWithRepetitions(registerBlock);

    // Should be in two Blocks.
    REQUIRE(result.size() == 2U);
    RegisterBlock registerBlockResult1;
    registerBlockResult1.addChannelRegisters(channelRegisters1);
    registerBlockResult1.addChannelRegisters(channelRegisters2);
    registerBlockResult1.addChannelRegisters(channelRegisters3);
    registerBlockResult1.addChannelRegisters(channelRegisters4);
    registerBlockResult1.addChannelRegisters(channelRegisters5);
    registerBlockResult1.addChannelRegisters(channelRegisters6);
    registerBlockResult1.addChannelRegisters(channelRegisters7);
    registerBlockResult1.addChannelRegisters(channelRegisters8);
    registerBlockResult1.addChannelRegisters(channelRegisters9);
    registerBlockResult1.addChannelRegisters(channelRegisters10);
    registerBlockResult1.addChannelRegisters(channelRegisters11);
    registerBlockResult1.addChannelRegisters(channelRegisters12);
    registerBlockResult1.addChannelRegisters(channelRegisters13);

    RegisterBlock registerBlockResult2;
    registerBlockResult2.addChannelRegisters(channelRegisters14);
    registerBlockResult2.addChannelRegisters(channelRegisters15);

    REQUIRE(result.at(0U)->matches(registerBlockResult1));
    REQUIRE(result.at(1U)->matches(registerBlockResult2));
}

TEST_CASE("AkyRegisterBlockOptimizer, determine no split", "[AkyRegisterBlockOptimizer]")
{
    // Decreasing sound, that's all.
    constexpr auto softwarePeriod = 100;
    const ChannelOutputRegisters channelRegisters1(ChannelOutputRegisters(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters2(ChannelOutputRegisters(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters3(ChannelOutputRegisters(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters4(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters5(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters6(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters7(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters8(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters9(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters10(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters11(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters12(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters13(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));

    RegisterBlock registerBlock;
    registerBlock.addChannelRegisters(channelRegisters1);
    registerBlock.addChannelRegisters(channelRegisters2);
    registerBlock.addChannelRegisters(channelRegisters3);
    registerBlock.addChannelRegisters(channelRegisters4);
    registerBlock.addChannelRegisters(channelRegisters5);
    registerBlock.addChannelRegisters(channelRegisters6);
    registerBlock.addChannelRegisters(channelRegisters7);
    registerBlock.addChannelRegisters(channelRegisters8);
    registerBlock.addChannelRegisters(channelRegisters9);
    registerBlock.addChannelRegisters(channelRegisters10);
    registerBlock.addChannelRegisters(channelRegisters11);
    registerBlock.addChannelRegisters(channelRegisters12);
    registerBlock.addChannelRegisters(channelRegisters13);

    auto result = RegisterBlockOptimizer::findAndSplitBlocksWithRepetitions(registerBlock);

    // Should be in two Blocks.
    REQUIRE(result.size() == 1U);
    RegisterBlock registerBlockResult1;
    registerBlockResult1.addChannelRegisters(channelRegisters1);
    registerBlockResult1.addChannelRegisters(channelRegisters2);
    registerBlockResult1.addChannelRegisters(channelRegisters3);
    registerBlockResult1.addChannelRegisters(channelRegisters4);
    registerBlockResult1.addChannelRegisters(channelRegisters5);
    registerBlockResult1.addChannelRegisters(channelRegisters6);
    registerBlockResult1.addChannelRegisters(channelRegisters7);
    registerBlockResult1.addChannelRegisters(channelRegisters8);
    registerBlockResult1.addChannelRegisters(channelRegisters9);
    registerBlockResult1.addChannelRegisters(channelRegisters10);
    registerBlockResult1.addChannelRegisters(channelRegisters11);
    registerBlockResult1.addChannelRegisters(channelRegisters12);
    registerBlockResult1.addChannelRegisters(channelRegisters13);

    REQUIRE(result.at(0U)->matches(registerBlockResult1));
}

TEST_CASE("AkyRegisterBlockOptimizer, determineSplitThreeBlocks", "[AkyRegisterBlockOptimizer]")
{
    // Decreasing sound with something else at the end.
    constexpr auto softwarePeriod = 100;
    const ChannelOutputRegisters channelRegisters1(ChannelOutputRegisters(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters2(ChannelOutputRegisters(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters3(ChannelOutputRegisters(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters4(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters5(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters6(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters7(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters8(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters9(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters10(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters11(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters12(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters13(ChannelOutputRegisters(5, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters14(ChannelOutputRegisters(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters15(ChannelOutputRegisters(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters16(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters17(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters18(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters19(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters20(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters21(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters22(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters23(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters24(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters25(ChannelOutputRegisters(6, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters26(ChannelOutputRegisters(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));
    const ChannelOutputRegisters channelRegisters27(ChannelOutputRegisters(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect()));

    RegisterBlock registerBlock;
    registerBlock.addChannelRegisters(channelRegisters1);
    registerBlock.addChannelRegisters(channelRegisters2);
    registerBlock.addChannelRegisters(channelRegisters3);
    registerBlock.addChannelRegisters(channelRegisters4);
    registerBlock.addChannelRegisters(channelRegisters5);
    registerBlock.addChannelRegisters(channelRegisters6);
    registerBlock.addChannelRegisters(channelRegisters7);
    registerBlock.addChannelRegisters(channelRegisters8);
    registerBlock.addChannelRegisters(channelRegisters9);
    registerBlock.addChannelRegisters(channelRegisters10);
    registerBlock.addChannelRegisters(channelRegisters11);
    registerBlock.addChannelRegisters(channelRegisters12);
    registerBlock.addChannelRegisters(channelRegisters13);
    registerBlock.addChannelRegisters(channelRegisters14);
    registerBlock.addChannelRegisters(channelRegisters15);
    registerBlock.addChannelRegisters(channelRegisters16);
    registerBlock.addChannelRegisters(channelRegisters17);
    registerBlock.addChannelRegisters(channelRegisters18);
    registerBlock.addChannelRegisters(channelRegisters19);
    registerBlock.addChannelRegisters(channelRegisters20);
    registerBlock.addChannelRegisters(channelRegisters21);
    registerBlock.addChannelRegisters(channelRegisters22);
    registerBlock.addChannelRegisters(channelRegisters23);
    registerBlock.addChannelRegisters(channelRegisters24);
    registerBlock.addChannelRegisters(channelRegisters25);
    registerBlock.addChannelRegisters(channelRegisters26);
    registerBlock.addChannelRegisters(channelRegisters27);

    auto result = RegisterBlockOptimizer::findAndSplitBlocksWithRepetitions(registerBlock);

    // Should be in two Blocks.
    REQUIRE(result.size() == 3U);
    RegisterBlock registerBlockResult1;
    registerBlockResult1.addChannelRegisters(channelRegisters1);
    registerBlockResult1.addChannelRegisters(channelRegisters2);
    registerBlockResult1.addChannelRegisters(channelRegisters3);
    registerBlockResult1.addChannelRegisters(channelRegisters4);
    registerBlockResult1.addChannelRegisters(channelRegisters5);
    registerBlockResult1.addChannelRegisters(channelRegisters6);
    registerBlockResult1.addChannelRegisters(channelRegisters7);
    registerBlockResult1.addChannelRegisters(channelRegisters8);
    registerBlockResult1.addChannelRegisters(channelRegisters9);
    registerBlockResult1.addChannelRegisters(channelRegisters10);
    registerBlockResult1.addChannelRegisters(channelRegisters11);
    registerBlockResult1.addChannelRegisters(channelRegisters12);
    registerBlockResult1.addChannelRegisters(channelRegisters13);

    RegisterBlock registerBlockResult2;
    registerBlockResult2.addChannelRegisters(channelRegisters14);
    registerBlockResult2.addChannelRegisters(channelRegisters15);
    registerBlockResult2.addChannelRegisters(channelRegisters16);
    registerBlockResult2.addChannelRegisters(channelRegisters17);
    registerBlockResult2.addChannelRegisters(channelRegisters18);
    registerBlockResult2.addChannelRegisters(channelRegisters19);
    registerBlockResult2.addChannelRegisters(channelRegisters20);
    registerBlockResult2.addChannelRegisters(channelRegisters21);
    registerBlockResult2.addChannelRegisters(channelRegisters22);
    registerBlockResult2.addChannelRegisters(channelRegisters23);
    registerBlockResult2.addChannelRegisters(channelRegisters24);
    registerBlockResult2.addChannelRegisters(channelRegisters25);

    RegisterBlock registerBlockResult3;
    registerBlockResult3.addChannelRegisters(channelRegisters26);
    registerBlockResult3.addChannelRegisters(channelRegisters27);

    REQUIRE(result.at(0U)->matches(registerBlockResult1));
    REQUIRE(result.at(1U)->matches(registerBlockResult2));
    REQUIRE(result.at(2U)->matches(registerBlockResult3));
}

}   // namespace arkostracker
