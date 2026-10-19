#pragma once

#include <juce_core/juce_core.h>

/** Statistics for how large/fast are the Z80 players. Use 0 to skip a test. */
class ExpectedStatistics {
public:
    explicit ExpectedStatistics(
            bool pMustBeExact,
            size_t pMusicSize = 0,
            size_t pRamPlayerSizeWithoutPlayerConfig = 0,
            size_t pRamPlayerSizeWithPlayerConfig = 0,
            size_t pRomPlayerSizeWithoutPlayerConfig = 0,
            size_t pRomPlayerSizeWithPlayerConfig = 0,
            int pRamPlayerSpentNopsWithoutPlayerConfig = 0,
            int pRamPlayerSpentNopsWithPlayerConfig = 0,
            int pRomPlayerSpentNopsWithoutPlayerConfig = 0,
            int pRomPlayerSpentNopsWithPlayerConfig = 0
    ) :
            mustBeExact(pMustBeExact),
            musicSize(pMusicSize),
            ramPlayerSizeWithoutPlayerConfig(pRamPlayerSizeWithoutPlayerConfig),
            ramPlayerSizeWithPlayerConfig(pRamPlayerSizeWithPlayerConfig),
            romPlayerSizeWithoutPlayerConfig(pRomPlayerSizeWithoutPlayerConfig),
            romPlayerSizeWithPlayerConfig(pRomPlayerSizeWithPlayerConfig),
            ramPlayerSpentNopsWithoutPlayerConfig(pRamPlayerSpentNopsWithoutPlayerConfig),
            ramPlayerSpentNopsWithPlayerConfig(pRamPlayerSpentNopsWithPlayerConfig),
            romPlayerSpentNopsWithoutPlayerConfig(pRomPlayerSpentNopsWithoutPlayerConfig),
            romPlayerSpentNopsWithPlayerConfig(pRomPlayerSpentNopsWithPlayerConfig)
    {
    }

    const bool mustBeExact;
    const size_t musicSize;
    const size_t ramPlayerSizeWithoutPlayerConfig;
    const size_t ramPlayerSizeWithPlayerConfig;
    const size_t romPlayerSizeWithoutPlayerConfig;
    const size_t romPlayerSizeWithPlayerConfig;
    const int ramPlayerSpentNopsWithoutPlayerConfig;
    const int ramPlayerSpentNopsWithPlayerConfig;
    const int romPlayerSpentNopsWithoutPlayerConfig;
    const int romPlayerSpentNopsWithPlayerConfig;
};