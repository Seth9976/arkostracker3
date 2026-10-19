#include "Z80PlayerEmulator.h"

#include <algorithm>

#include "../../../source/business/song/tool/frameCounter/FrameCounter.h"
#include "../../../source/export/akg/AkgExporter.h"
#include "../../../source/export/akm/AkmExporter.h"
#include "../../../source/export/aky/AkyExporter.h"
#include "../../../source/import/loader/SongLoader.h"
#include "../../../source/utils/MemoryBlockUtil.h"
#include "../../../source/utils/RasmUtil.h"
#include "../../catch.hpp"
#include "../RasmHelper.h"
#include "BinaryData.h"
#include "Z80Emulator.h"

namespace arkostracker 
{

void Z80PlayerEmulator::testMusic(const char* unzippedMusicData, size_t unzippedMusicSize, int subsongIndexToPlay, PlayerType playerType,
                                  const std::map<TargetHardware, ExpectedStatistics>& targetToExpectedStatistics,
                                  const std::vector<int>& subsongIndexesToKeepOriginal,
                                  int errorCountToleranceInVolume, int possibleAbsoluteDifferenceInVolume,
                                  int possibleAbsoluteDifferenceInSoftwarePeriod,
                                  int possibleAbsoluteDifferenceInHardwarePeriod, int errorCountToleranceInHardwarePeriod,
                                  bool playTwice, OptionalValue<TargetHardware> forcedTargetHardware)
{
    if (subsongIndexesToKeepOriginal.empty()) {
        jassert(subsongIndexToPlay == 0);           // Else, we're going to play something that doesn't exist anymore!
    }

    const auto subsongIndexesToKeep = subsongIndexesToKeepOriginal.empty() ? std::vector { 0 } : subsongIndexesToKeepOriginal;

    DBG("");
    DBG("");
    DBG("New music");
    DBG("*********");

    // Uses the forced hardware if present, else the hardware from the player type.
    const auto targetHardwares = forcedTargetHardware.isPresent() ? std::vector { forcedTargetHardware.getValue() } : TargetHardwareHelper::getNormal(playerType);
    for (const auto targetHardware : targetHardwares) {
    //for (const auto targetHardware : { TargetHardware::cpc }) {     // TEST

        // Tests the RAM/ROM players.
        for (const auto useRomPlayer: { false, true }) {
        //for (const auto useRomPlayer: { false }) {     // TEST
            DBG("Target hardware = " + TargetHardwareHelper::getDisplayableName(targetHardware) + ". ROM? " + (useRomPlayer ? "Yes" : "No"));
            const auto returnStatisticsWithoutPlayerConfiguration = testMusic(unzippedMusicData, unzippedMusicSize, subsongIndexesToKeep, subsongIndexToPlay,
                                                                              targetHardware, playerType, false, useRomPlayer,
                                                                              errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                                                              possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod,
                                                                              errorCountToleranceInHardwarePeriod, playTwice);
            const auto returnStatisticsWithPlayerConfiguration = testMusic(unzippedMusicData, unzippedMusicSize, subsongIndexesToKeep, subsongIndexToPlay,
                                                                           targetHardware, playerType, true, useRomPlayer,
                                                                           errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                                                           possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod,
                                                                           errorCountToleranceInHardwarePeriod, playTwice);

            // NOTE: the timings are defined from the real player, WITH the hook, WITHOUT counting the CALL calling the player. It includes the final RET to return to the caller.

            const auto maxPlayerSize = returnStatisticsWithoutPlayerConfiguration.playerSize;
            const auto minPlayerSize = returnStatisticsWithPlayerConfiguration.playerSize;
            const auto sizeDiff = static_cast<int>(maxPlayerSize) - static_cast<int>(minPlayerSize);
            DBG("Player size without/with Statistics: " + juce::String(maxPlayerSize) + " / " + juce::String(minPlayerSize) + ". Diff = " + juce::String(sizeDiff));

            const auto maxSpentNops = returnStatisticsWithoutPlayerConfiguration.spentNops;
            const auto minSpentNops = returnStatisticsWithPlayerConfiguration.spentNops;
            const auto spentNopsDiff = static_cast<int>(maxSpentNops) - static_cast<int>(minSpentNops);
            DBG("Spent NOPS without/with Statistics: " + juce::String(maxSpentNops) + " / " + juce::String(minSpentNops) + ". Diff = " + juce::String(spentNopsDiff));
            REQUIRE((sizeDiff >= 0));
            REQUIRE((spentNopsDiff >= 0));

            const auto musicSize1 = returnStatisticsWithPlayerConfiguration.musicSize;
            const auto musicSize2 = returnStatisticsWithoutPlayerConfiguration.musicSize;
            REQUIRE((musicSize1 == musicSize2));
            DBG("Music size: " + juce::String(musicSize1));
            DBG("-------");

            // Matching the given expected stats?
            if (auto it = targetToExpectedStatistics.find(targetHardware); it != targetToExpectedStatistics.cend()) {
                const auto& expectedStats = it->second;

                if (expectedStats.musicSize != 0) {
                    if (expectedStats.mustBeExact) {
                        REQUIRE((musicSize1 == expectedStats.musicSize));
                    } else {
                        REQUIRE((musicSize1 <= expectedStats.musicSize));
                    }
                }

                if (useRomPlayer) {
                    if (expectedStats.mustBeExact) {
                        if (expectedStats.romPlayerSizeWithoutPlayerConfig != 0) {
                            REQUIRE((maxPlayerSize == expectedStats.romPlayerSizeWithoutPlayerConfig));
                        }
                        if (expectedStats.romPlayerSizeWithPlayerConfig != 0) {
                            REQUIRE((minPlayerSize == expectedStats.romPlayerSizeWithPlayerConfig));
                        }
                        if (expectedStats.romPlayerSpentNopsWithoutPlayerConfig != 0) {
                            REQUIRE((maxSpentNops == expectedStats.romPlayerSpentNopsWithoutPlayerConfig));
                        }
                        if (expectedStats.romPlayerSpentNopsWithPlayerConfig != 0) {
                            REQUIRE((minSpentNops == expectedStats.romPlayerSpentNopsWithPlayerConfig));
                        }
                    } else {
                        if (expectedStats.romPlayerSizeWithoutPlayerConfig != 0) {
                            REQUIRE((maxPlayerSize <= expectedStats.romPlayerSizeWithoutPlayerConfig));
                        }
                        if (expectedStats.romPlayerSizeWithPlayerConfig != 0) {
                            REQUIRE((minPlayerSize <= expectedStats.romPlayerSizeWithPlayerConfig));
                        }
                        if (expectedStats.romPlayerSpentNopsWithoutPlayerConfig != 0) {
                            REQUIRE((maxSpentNops <= expectedStats.romPlayerSpentNopsWithoutPlayerConfig));
                        }
                        if (expectedStats.romPlayerSpentNopsWithPlayerConfig != 0) {
                            REQUIRE((minSpentNops <= expectedStats.romPlayerSpentNopsWithPlayerConfig));
                        }
                    }
                } else {
                    if (expectedStats.mustBeExact) {
                        if (expectedStats.ramPlayerSizeWithoutPlayerConfig != 0) {
                            REQUIRE((maxPlayerSize == expectedStats.ramPlayerSizeWithoutPlayerConfig));
                        }
                        if (expectedStats.ramPlayerSizeWithPlayerConfig != 0) {
                            REQUIRE((minPlayerSize == expectedStats.ramPlayerSizeWithPlayerConfig));
                        }
                        if (expectedStats.ramPlayerSpentNopsWithoutPlayerConfig != 0) {
                            REQUIRE((maxSpentNops == expectedStats.ramPlayerSpentNopsWithoutPlayerConfig));
                        }
                        if (expectedStats.ramPlayerSpentNopsWithPlayerConfig != 0) {
                            REQUIRE((minSpentNops == expectedStats.ramPlayerSpentNopsWithPlayerConfig));
                        }
                    } else {
                        if (expectedStats.ramPlayerSizeWithoutPlayerConfig != 0) {
                            REQUIRE((maxPlayerSize <= expectedStats.ramPlayerSizeWithoutPlayerConfig));
                        }
                        if (expectedStats.ramPlayerSizeWithPlayerConfig != 0) {
                            REQUIRE((minPlayerSize <= expectedStats.ramPlayerSizeWithPlayerConfig));
                        }
                        if (expectedStats.ramPlayerSpentNopsWithoutPlayerConfig != 0) {
                            REQUIRE((maxSpentNops <= expectedStats.ramPlayerSpentNopsWithoutPlayerConfig));
                        }
                        if (expectedStats.ramPlayerSpentNopsWithPlayerConfig != 0) {
                            REQUIRE((minSpentNops <= expectedStats.ramPlayerSpentNopsWithPlayerConfig));
                        }
                    }
                }
            }
        }
    }
}

Z80PlayerEmulator::ReturnStatistics Z80PlayerEmulator::testMusic(const char* musicData, size_t musicSize,
                                                                 const std::vector<int>& subsongIndexesToKeep, int subsongIndexToPlay,
                                                                 TargetHardware targetHardware, PlayerType playerType,
                                                                 bool usePlayerConfiguration, bool romPlayer,
                                                                 int errorCountToleranceInVolume, int possibleAbsoluteDifferenceInVolume,
                                                                 int possibleAbsoluteDifferenceInSoftwarePeriod,
                                                                 int possibleAbsoluteDifferenceInHardwarePeriod, int errorCountToleranceInHardwarePeriod,
                                                                 bool playTwice)
{
    // Loads the music for the C++ player.
    juce::MemoryInputStream inputStream(musicData, musicSize, false);
    SongLoader loader;
    const auto loadResult = loader.loadSong(inputStream, "aks", false, nullptr);
    REQUIRE(loadResult->errorReport->isOk());

    auto originalSong = std::move(loadResult->song);
    const std::shared_ptr song = std::move(originalSong);

    // Forces the PSG frequency of the Song.
    Z80Emulator::setPsgFrequencyToSong(*song, targetHardware);

    // Exports the music into a Z80 source.
    // Converts the Subsong indexes to IDs.
    std::vector<Id> subsongIdsToKeep;
    for (const auto subsongIndex : subsongIndexesToKeep) {
        const auto subsongId = song->getSubsongId(subsongIndex);
        REQUIRE(subsongId.isPresent());
        subsongIdsToKeep.push_back(subsongId.getValueRef());
    }

    const auto musicExportResult = getMusicSource(song, playerType, subsongIdsToKeep);
    REQUIRE((musicExportResult != nullptr));      // Error on export.

    const auto musicSource = musicExportResult->getAggregatedData();
    const auto& playerConfiguration = musicExportResult->getPlayerConfigurationRef();
    // Useful for testing.
    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/cpc/tests/genMusic.asm", musicSource);        // Do not commit!

    // Assembles the music. The ORG has been added by the exporter.
    const auto assembledMusic = RasmHelper::assembleSourceWithoutAddingOrg(musicSource);
    REQUIRE((assembledMusic != nullptr));         // Unable to assemble the exported Z80 music code.
    const auto assembledMusicSize = assembledMusic->getSize();

    // Assembles the player.
    const auto assembledPlayer = assemblePlayer(playerType, targetHardware, romPlayer, usePlayerConfiguration ? &playerConfiguration : nullptr);
    REQUIRE((assembledPlayer != nullptr));        // Unable to assemble the exported Z80 music code.
    const auto playerSize = assembledPlayer->getSize();

    // Assembles the launchers.
    const auto assembledInitLauncher = assembleInitLauncher(subsongIndexToPlay);
    const auto assembledPlayLauncher = assemblePlayLauncher();
    REQUIRE((assembledInitLauncher != nullptr));  // Unable to assemble the Z80 player init launcher.
    REQUIRE((assembledPlayLauncher != nullptr));  // Unable to assemble the Z80 player call launcher.

    // Adds all this to the Z80 memory.
    Z80Emulator z80Emulator(targetHardware);
    z80Emulator.injectData(*assembledInitLauncher, launcherInitAddress);
    z80Emulator.injectData(*assembledPlayLauncher, launcherPlayAddress);
    z80Emulator.injectData(*assembledPlayer, playerAddress);
    z80Emulator.injectData(*assembledMusic, musicAddress);

    // Calls the init.
    auto spentNops = z80Emulator.runTillRst38(launcherInitAddress);
    if ((spentNops < 20) || (spentNops > 3000)) {                           // Not accurate.
        FAIL();
    }

    // Prepares the C++ player.
    const auto subsongId = subsongIdsToKeep.at(static_cast<size_t>(subsongIndexToPlay));
    // Counts how many iterations are in the Song.
    FrameCounter::count(*song, subsongId);
    const auto[counter, upTo, loopCounter] = FrameCounter::count(*song, subsongId);
    REQUIRE((loopCounter <= counter));
    const auto iterationCount = counter + (playTwice ? (counter - loopCounter) : 0);      // Plays the song twice?

    const auto startLocation = Location(subsongId, 0);
    const auto[loopStartLocation, pastEndLocation] = song->getLoopStartAndPastEndPositions(subsongId);

    SongPlayer songPlayer(song);
    songPlayer.play(startLocation, loopStartLocation, pastEndLocation, true, true);
    const auto psgCount = song->getPsgCount(subsongId);
    auto errorCountInVolume = 0;
    auto errorCountInNoise = 0;
    auto errorCountInHardwarePeriod = 0;
    auto latestHardwareEnvelope = 16;    // Sentinel value for "unknown yet".
    auto frameCounter = 0;
    auto maxSpentNops = 0;

    // Plays each frame of the Song (twice, see the iterationCount calculation).
    for (auto iteration = 0 ; iteration < iterationCount; ++iteration) {
        // Calls the C++ player. All the PSGs must be read.
        std::vector<PsgRegisters> psgsRegisters;
        psgsRegisters.reserve(static_cast<size_t>(psgCount));

        // Stores all the PSGs from the C++ player.
        for (auto psgIndex = 0; psgIndex < psgCount; ++psgIndex) {
            auto [psgRegistersPtr, _]  = songPlayer.getNextRegisters(psgIndex);
            psgsRegisters.push_back(*psgRegistersPtr);

            // Marks the R13 as 255 to allow easy testing of the Retrig, along with the C++ player. This value will be overwritten by the Z80 player IF the
            // envelope changes, thus making the comparison with the C++ player easy.
            z80Emulator.markHardwareEnvelopeRegisterAsNonRetrig(psgIndex);
        }

        // Calls the Z80 player.
        spentNops = z80Emulator.runTillRst38(launcherPlayAddress);
        spentNops -= 5 + 3 + 4;     // Removes the Call to player, JP to the Play hook, and the RST#38 to return.
        maxSpentNops = std::max(spentNops, maxSpentNops);

        // Compares the Z80 result with the C++ registers.
        for (auto psgIndex = 0; psgIndex < psgCount; ++psgIndex) {
            const auto& psgRegisters = psgsRegisters.at(static_cast<size_t>(psgIndex));

            auto tempLatestHardwareEnvelope = latestHardwareEnvelope;        // Stores a temp value to allow the re-match.
            auto match = z80Emulator.comparePsgFrame(psgIndex, psgRegisters, latestHardwareEnvelope,
                                                     errorCountInVolume, errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                                     errorCountInNoise, 0, possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod,
                                                     errorCountToleranceInHardwarePeriod, errorCountInHardwarePeriod);
            if (!match) {               // Useful for testing.
                jassertfalse;           // Watch out for the TargetHardware, RAM/ROM player and playerconfiguration.
                match = z80Emulator.comparePsgFrame(psgIndex, psgRegisters, tempLatestHardwareEnvelope,
                                                    errorCountInVolume, errorCountToleranceInVolume, possibleAbsoluteDifferenceInVolume,
                                                    errorCountInNoise, 0, possibleAbsoluteDifferenceInSoftwarePeriod, possibleAbsoluteDifferenceInHardwarePeriod,
                                                    errorCountToleranceInHardwarePeriod, errorCountInHardwarePeriod);
            }
            REQUIRE(match);
        }

        ++frameCounter;
    }

    REQUIRE((frameCounter > 20));        // Just a small check to avoid an empty song.

    return { playerSize, maxSpentNops, assembledMusicSize };
}

std::unique_ptr<SongExportResult> Z80PlayerEmulator::getMusicSource(const std::shared_ptr<Song>& song, PlayerType playerType, const std::vector<Id>& subsongIds)
{
    const ExportConfiguration exportConfiguration(SourceGeneratorConfiguration::buildZ80(), subsongIds, "Label_",
                                            musicAddress, SampleEncoderFlags::buildNoExport(), false);

    std::pair<bool, std::unique_ptr<SongExportResult>> result;

    switch (playerType) {
        case PlayerType::aky: [[fallthrough]];
        case PlayerType::akyStabilized: [[fallthrough]];
        case PlayerType::akyMultiPsg9Channels:
        {
            AkyExporter exporter(song, exportConfiguration);
            result = exporter.performTask();
            break;
        }
        case PlayerType::akg:
        {
            AkgExporter exporter(*song, exportConfiguration);
            result = exporter.performTask();
            break;
        }
        case PlayerType::akm:
        {
            AkmExporter exporter(*song, exportConfiguration);
            result = exporter.performTask();
            break;
        }
        default:
            jassertfalse;
            break;
    }

    if (result.first) {
        return std::move(result.second);
    }

    return nullptr;     // Error on export.
}

std::unique_ptr<juce::MemoryBlock> Z80PlayerEmulator::assemblePlayer(const PlayerType playerType, const TargetHardware targetHardware,
                                                                     const bool romPlayer, const PlayerConfiguration* playerConfiguration)
{
    const char* playerData;         // NOLINT(*-init-variables)
    size_t playerSize;              // NOLINT(*-init-variables)
    juce::String sourceTagPrefix;

    switch (playerType) {
        case PlayerType::aky:
            playerData = BinaryData::PlayerAky_asm;
            playerSize = BinaryData::PlayerAky_asmSize;
            sourceTagPrefix = "PLY_AKY";
            break;
        case PlayerType::akyStabilized:
            playerData = BinaryData::PlayerAkyStabilized_CPC_asm;
            playerSize = BinaryData::PlayerAkyStabilized_CPC_asmSize;
            sourceTagPrefix = "PLY_AKYst";
            break;
        case PlayerType::akyMultiPsg9Channels:
            playerData = BinaryData::PlayerAkyMultiPsg_asm;
            playerSize = BinaryData::PlayerAkyMultiPsg_asmSize;
            sourceTagPrefix = "PLY_AKY";
            break;
        case PlayerType::akg:
            playerData = BinaryData::PlayerAkg_asm;
            playerSize = BinaryData::PlayerAkg_asmSize;
            sourceTagPrefix = "PLY_AKG";
            break;
        case PlayerType::akm:
            playerData = BinaryData::PlayerAkm_asm;
            playerSize = BinaryData::PlayerAkm_asmSize;
            sourceTagPrefix = "PLY_AKM";
            break;
        default:
            jassertfalse;       // Unhandled player?
            return nullptr;
    }

    const juce::MemoryBlock originalPlayerSourceMemoryBlock(playerData, playerSize);

    // Assembles the player, at the right ORG and with the player configuration, if given.
    auto playerSourceMemoryBlock = RasmUtil::commentIncludes(originalPlayerSourceMemoryBlock);    // Else, won't compile.

    if (playerConfiguration != nullptr) {
        RasmHelper::addPlayerConfiguration(playerSourceMemoryBlock, *playerConfiguration);
    }

    // Declares the hardware to use.
    RasmHelper::addHardwareDeclaration(playerSourceMemoryBlock, sourceTagPrefix, targetHardware);

    // Rom player?
    RasmHelper::addRomPlayerDeclaration(playerSourceMemoryBlock, sourceTagPrefix, romBufferAddress, romPlayer);

    //FileUtil::saveMemoryBlockToFile("~/Documents/dev/cpc/tests/genPlayer.asm", playerSourceMemoryBlock);        // Do not commit!

    return RasmHelper::assembleSource(playerSourceMemoryBlock, playerAddress);
}

std::unique_ptr<juce::MemoryBlock> Z80PlayerEmulator::assembleInitLauncher(const int subsongIndex)
{
    std::vector<juce::String> strings;
    strings.emplace_back("    org " + juce::String(launcherInitAddress));
    strings.emplace_back("    ld hl," + juce::String(musicAddress));

    strings.emplace_back("    ld a," + juce::String(subsongIndex));                     // Subsong index. it may not be useful to some players.
    strings.emplace_back("    call " + juce::String(playerAddress + 0));                // Call player init (player +0).

    strings.emplace_back("    rst #38");            // Triggers the end of the execution.

    const auto sourceMemoryBlock = MemoryBlockUtil::fromStrings(strings);

    // Assembles it.
    return RasmHelper::assembleSourceWithoutAddingOrg(sourceMemoryBlock);
}

std::unique_ptr<juce::MemoryBlock> Z80PlayerEmulator::assemblePlayLauncher()
{
    std::vector<juce::String> strings;
    strings.emplace_back("    org " + juce::String(launcherPlayAddress));
    strings.emplace_back("    call " + juce::String(playerAddress + 3));    // Jumps on the hook.
    strings.emplace_back("    rst #38");            // Triggers the end of the execution.
    const auto sourceMemoryBlock = MemoryBlockUtil::fromStrings(strings);

    // Assembles it.
    return RasmHelper::assembleSourceWithoutAddingOrg(sourceMemoryBlock);
}

}   // namespace arkostracker
