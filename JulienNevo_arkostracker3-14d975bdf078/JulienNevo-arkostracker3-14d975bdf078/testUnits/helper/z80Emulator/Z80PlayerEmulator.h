#pragma once

#include <juce_core/juce_core.h>

#include "PlayerType.h"
#include "../../../source/export/SongExportResult.h"
#include "TargetHardware.h"
#include "ExpectedStatistics.h"

namespace arkostracker
{

class Song;

/** Class to play a Song on an emulated Z80 and makes sure it "sounds" the same as the C++ player. */
class Z80PlayerEmulator
{
public:
    class ReturnStatistics
    {
    public:
        ReturnStatistics(size_t pPlayerSize, int pSpentNops, size_t pMusicSize) :
                playerSize(pPlayerSize),
                spentNops(pSpentNops),
                musicSize(pMusicSize)
        {
        }
        const size_t playerSize;
        const int spentNops;
        const size_t musicSize;
    };

    static void testMusic(const char* unzippedMusicData, size_t unzippedMusicSize, int subsongIndexToPlay, PlayerType playerType,
                          const std::map<TargetHardware, ExpectedStatistics>& targetToExpectedStatistics,
                          const std::vector<int>& subsongIndexesToKeep = { },     // If empty, keeps only the one to play.
                          int errorCountToleranceInVolume = 0, int possibleAbsoluteDifferenceInVolume = 0,
                          int possibleAbsoluteDifferenceInSoftwarePeriod = 0,
                          int possibleAbsoluteDifferenceInHardwarePeriod = 0, int errorCountToleranceInHardwarePeriod = 0,
                          bool playTwice = true, OptionalValue<TargetHardware> forcedTargetHardware = { });

private:
    static const unsigned int launcherInitAddress = 0x100;                      // Where a small code is stored to init the player.
    static const unsigned int launcherPlayAddress = 0x200;                      // Where a small code is stored to "play" the player.
    static const unsigned int playerAddress = 0x1000;                           // Where the player is stored in the CPC memory.
    static const unsigned int musicAddress = 0x4000;                            // Where the music is stored in the CPC memory.
    static const unsigned int romBufferAddress = 0xf000;                        // Where the ROM buffer is stored in the CPC memory.

    static ReturnStatistics testMusic(const char* unzippedMusicData, size_t unzippedMusicSize,
                                      const std::vector<int>& subsongIndexesToKeep, int subsongIndex,
                                      TargetHardware targetHardware, PlayerType playerType,
                                      bool usePlayerConfiguration, bool romPlayer,
                                      int errorCountToleranceInVolume, int possibleAbsoluteDifferenceInVolume,
                                      int possibleAbsoluteDifferenceInSoftwarePeriod,
                                      int possibleAbsoluteDifferenceInHardwarePeriod, int errorCountToleranceInHardwarePeriod,
                                      bool playTwice);

    /** Asks for the source of the music, all in one stream. */
    static std::unique_ptr<SongExportResult> getMusicSource(const std::shared_ptr<Song>& song, PlayerType playerType, const std::vector<Id>& subsongIds);

    /** Assembles a player, according to the given PlayerConfiguration, if given. */
    static std::unique_ptr<juce::MemoryBlock> assemblePlayer(PlayerType playerType, TargetHardware targetHardware, bool romPlayer, const PlayerConfiguration* playerConfiguration);

    /** Assembles a launcher that will init the player, with a subsong index. Use 0 if you don't care (like for AKY). */
    static std::unique_ptr<juce::MemoryBlock> assembleInitLauncher(int subsongIndex);

    /** Assembles a launcher that will call the player. */
    static std::unique_ptr<juce::MemoryBlock> assemblePlayLauncher();
};

}   // namespace arkostracker
