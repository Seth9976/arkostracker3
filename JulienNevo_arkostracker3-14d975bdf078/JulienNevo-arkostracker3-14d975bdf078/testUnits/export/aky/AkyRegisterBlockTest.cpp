#include "../../catch.hpp"

#include "../../../source/export/aky/process/RegisterBlock.h"

namespace arkostracker 
{

TEST_CASE("AkyRegisterBlock, determineLoop1", "[AkyRegisterBlock]")
{
    RegisterBlock registerBlock;
    constexpr auto softwarePeriod = 100;

    // Simple decreasing sound with a sustain at the end.
    const ChannelOutputRegisters channelRegisters1(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters2(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters3(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters4(12, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters5(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters6(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters7(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters8(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters9(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters10(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters11(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());

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

    registerBlock.determineLoop();

    REQUIRE(registerBlock.isLooping());
    REQUIRE(registerBlock.getLoopStartIndex() == 4);
    REQUIRE(registerBlock.getLoopSize() == 1);
}

TEST_CASE("AkyRegisterBlock, determineLoop2", "[AkyRegisterBlock]")
{
    RegisterBlock registerBlock;
    const auto softwarePeriod = 100;

    // Loop of a decreasing sound, with a different first iteration. The last iteration is not complete.
    // First loop, different.
    const ChannelOutputRegisters channelRegisters1(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters2(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters3(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters4(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    // Second loop, the same as the next ones.
    const ChannelOutputRegisters channelRegisters5(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters6(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters7(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters8(12, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters9(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    // Third loop, same as the second.
    const ChannelOutputRegisters channelRegisters10(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters11(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters12(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());

    const ChannelOutputRegisters channelRegisters13(12, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters14(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    // Fourth loop, same as the second and third, but incomplete.
    const ChannelOutputRegisters channelRegisters15(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters16(14, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters17(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());

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

    registerBlock.determineLoop();

    REQUIRE(registerBlock.isLooping());
    REQUIRE(registerBlock.getLoopStartIndex() == 7);
    REQUIRE(registerBlock.getLoopSize() == 5);
}

TEST_CASE("AkyRegisterBlock, determineLoop3", "[AkyRegisterBlock]")
{
    RegisterBlock registerBlock;
    const auto softwarePeriod = 100;

    // Loop of a decreasing sound, done three times. But the first index is not included because it is the initial state.
    const ChannelOutputRegisters channelRegisters1(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters2(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters3(12, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters4(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters5(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());

    const ChannelOutputRegisters channelRegisters6(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters7(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters8(12, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters9(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters10(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());

    const ChannelOutputRegisters channelRegisters11(15, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters12(13, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters13(12, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters14(11, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters15(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());

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

    registerBlock.determineLoop();

    REQUIRE(registerBlock.isLooping());
    REQUIRE(registerBlock.getLoopStartIndex() == 5);
    REQUIRE(registerBlock.getLoopSize() == 5);
}

TEST_CASE("AkyRegisterBlock, determineLoop4", "[AkyRegisterBlock]")
{
    RegisterBlock registerBlock;
    const int softwarePeriod = 119;

    // Decreasing sound with an arp of the first four notes.
    const ChannelOutputRegisters channelRegisters1(15, 0x19, true, softwarePeriod,  0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters2(15, 0x14, true, 100,             0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters3(15, 0xc, true, 60,               0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters4(13, 9, true, softwarePeriod,     0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters5(12, 8, true, softwarePeriod,     0, 0, false, SpecialEffect());

    const ChannelOutputRegisters channelRegisters6(11, 6, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters7(10, 6, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters8(9, 6, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters9(8, 6, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters10(7, 6, true, softwarePeriod, 0, 0, false, SpecialEffect());

    const ChannelOutputRegisters channelRegisters11(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters12(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters13(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters14(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters15(10, 0, true, 113, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters16(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters17(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters18(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());
    const ChannelOutputRegisters channelRegisters19(10, 0, true, softwarePeriod, 0, 0, false, SpecialEffect());

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

    registerBlock.determineLoop();

    REQUIRE(registerBlock.isLooping());
    REQUIRE(registerBlock.getLoopStartIndex() == 15);
    REQUIRE(registerBlock.getLoopSize() == 1);
}

TEST_CASE("AkyRegisterBlock, determineLoop5", "[AkyRegisterBlock]")
{
    RegisterBlock registerBlock;

    // Simple decreasing sound with a sustain at the end.
    auto noise = 0;
    for (auto i = 0; i < 128; ++i) {
        const auto subIndex = i % 6;
        if (subIndex == 0) {
            ++noise;
        }
        const ChannelOutputRegisters channelRegisters(subIndex < 3 ? 11 : 5, noise, false, 0, 0, 0, false, SpecialEffect());
        registerBlock.addChannelRegisters(channelRegisters);
    }

    registerBlock.determineLoop();

    REQUIRE(!registerBlock.isLooping());
}

TEST_CASE("AkyRegisterBlock, determineLoop6", "[AkyRegisterBlock]")
{
    RegisterBlock registerBlock;

    const ChannelOutputRegisters channelRegisters(15, 0, true, 120, 0, 0, false, SpecialEffect());

    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);

    registerBlock.determineLoop();

    REQUIRE(registerBlock.isLooping());
    REQUIRE(registerBlock.getLoopStartIndex() == 1);
    REQUIRE(registerBlock.getLoopSize() == 1);
}

TEST_CASE("AkyRegisterBlock, determineLoop7", "[AkyRegisterBlock]")
{
    RegisterBlock registerBlock;

    const ChannelOutputRegisters channelRegisters(15, 0, true, 120, 0, 0, false, SpecialEffect());

    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);
    registerBlock.addChannelRegisters(channelRegisters);

    registerBlock.determineLoop();

    REQUIRE(!registerBlock.isLooping());
}

}   // namespace arkostracker
