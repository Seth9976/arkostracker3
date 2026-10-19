# Packaging of the files themselves.
set(PLAYERS_FOLDER ${DESTINATION_FOLDER}/players)

# Files at the root.
install(FILES
        ${CPACK_RESOURCE_FILE_LICENSE}
        ${CMAKE_SOURCE_DIR}/ChangeLog.md
        DESTINATION ${DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)

if (UNIX)
    install(FILES
            ${CMAKE_SOURCE_DIR}/cpack/ArkosTracker3.png           # Icon for Linux desktop, referred to in arkostracker3.desktop.
            DESTINATION ${DESTINATION_FOLDER}
            COMPONENT ${OUTPUT_COMPONENT}
    )
endif ()

# Copy of raw folders.
install(DIRECTORY
        ${CMAKE_SOURCE_DIR}/packageFiles/instruments
        ${CMAKE_SOURCE_DIR}/packageFiles/manual
        ${CMAKE_SOURCE_DIR}/packageFiles/songs
        DESTINATION ${DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
        #FILES_MATCHING     As an example!!!
        #PATTERN "*.aks"
        #PATTERN "*.aki"
)

# Tips.
install(DIRECTORY
        ${CMAKE_SOURCE_DIR}/tips
        DESTINATION ${DESTINATION_FOLDER}/private
        COMPONENT ${OUTPUT_COMPONENT}
        FILES_MATCHING
        PATTERN "*.png"
        PATTERN "*.jpg"
        PATTERN "*.zip"
)

# AKG player.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/PlayerAkg.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/PlayerAkg_SoundEffects.asm
        DESTINATION ${PLAYERS_FOLDER}/playerAkg/sources/z80
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/Basic_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/InterruptionsBasicCpc/BasicInterruptions_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/InterruptionsBasicCpc/BasicInterruptions_CPC.dsk
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgTester_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgTester_PCW.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgTester_PENTAGON.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgTester_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgTester_SVI.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgWithSoundEffectTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/tester/PlayerAkgWithSoundEffectTester_SPECTRUM.asm
        DESTINATION ${PLAYERS_FOLDER}/playerAkg/sources/z80/tester
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/resources/Music_AHarmlessGrenade.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/resources/Music_AHarmlessGrenade_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/resources/Music_Empty.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/resources/Music_Empty_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkg/sources/resources/SoundEffects.asm
        DESTINATION ${PLAYERS_FOLDER}/playerAkg/sources/z80/resources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/doc/export/AKG.md
        DESTINATION ${PLAYERS_FOLDER}/playerAkg/doc
        COMPONENT ${OUTPUT_COMPONENT}
)

# AKM player.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/PlayerAkm.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/PlayerAkm_SoundEffects.asm
        DESTINATION ${PLAYERS_FOLDER}/playerAkm/sources/z80
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/tester/PlayerAkmTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/tester/PlayerAkmTester_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/tester/PlayerAkmTester_SPECTRUM_PENTAGON.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/tester/PlayerAkmWithSoundEffectsTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/tester/PlayerAkmWithSoundEffectsTester_SPECTRUM_PENTAGON.asm
        DESTINATION ${PLAYERS_FOLDER}/playerAkm/sources/z80/tester
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/resources/Dead On Time - Main Menu.asm"
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/resources/Dead On Time - Main Menu_playerconfig.asm"
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/resources/Dead On Time - Main Menu_playerconfig.asm"
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/resources/SoundEffects.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/resources/SoundEffectsDeadOnTime.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/resources/SoundEffectsDeadOnTime_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAkm/sources/resources/SoundEffects_playerconfig.asm
        DESTINATION ${PLAYERS_FOLDER}/playerAkm/sources/z80/resources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/doc/export/AKM.md
        DESTINATION ${PLAYERS_FOLDER}/playerAkm/doc
        COMPONENT ${OUTPUT_COMPONENT}
)

# AKY player - Z80.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAky.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAkyMultiPsg.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAkyMultiPsg_SoundEffects.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAkyMultiPsg_Digidrums.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAkyMultiPsg_Sample.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAkyStabilized_CPC.asm

        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAkySid_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/PlayerAkySidMacros_CPC.asm

        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/z80
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester6Channels_Darky_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester6Channels_FPGAPSG_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester6Channels_TurboSound_PCW.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester6Channels_TurboSound_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester9Channels_PlayCity_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester9Channels_SPECNEXT.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester_PCW.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester_PENTAGON.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyTester_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyWithSoundEffectTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyWithSoundEffectTester_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyWithSoundEffectTester_PCW.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyWithSoundEffectTester_SPECTRUM_PENTAGON.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyWithSoundEffectTester_TurboSound_PCW.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyDigidrumsTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyDigidrumsTester_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkyDigidrumsTester_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkySampleTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkySampleTester_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkySampleTester_SPECTRUM.asm

        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/tester/PlayerAkySidTester_CPC.asm

        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/z80/tester
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicAHarmlessGrenade_MSX_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicAHarmlessGrenade_MSX_SPECTRUM_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicBoulesEtBits.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicBoulesEtBits_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicCarpet.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicCarpet_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicTheLastV8_6Channels.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicTheLastV8_6Channels_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicTheLastV8_9Channels.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicTheLastV8_9Channels_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/SoundEffectsDeadOnTime.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/SoundEffectsDeadOnTime_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigitestEvents.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigitestMusic_CPC_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigitestMusic_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigitestMusic_MSX_SPECTRUM_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigitestMusic_MSX_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigitestSamples.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicSarkboteur_CPC_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicSarkboteur_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicSarkboteur_MSX_SPECTRUM_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/MusicSarkboteur_MSX_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigidrumSarkboteurEvents.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/DigidrumSarkboteurSamples.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/LoPanAttackAky_MSX_SPECTRUM_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/LoPanAttackAky_MSX_SPECTRUM.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/LoPanAttackAky_playerconfig.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/LoPanAttackAky.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/LoPanAttackRawLinear.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/LoPanAttackSamples.asm

        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/SidExamples.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerAky/sources/resources/SignalInDisarray.asm

        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/z80/resources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/doc/export/AKY.md
        DESTINATION ${PLAYERS_FOLDER}/playerAky/doc
        COMPONENT ${OUTPUT_COMPONENT}
)

# AKY player - 68000.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/atariSt/playerAky/readme.txt
        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/68000
        COMPONENT ${OUTPUT_COMPONENT}
)

# AKY player - 6502 - Apple2 & Oric.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/PlayerAKY_6502.a
        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/6502/apple2_oric
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicAHarmlessGrenade_APPLE2_ORIC.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicAHarmlessGrenade_APPLE2_ORIC_playerconfig.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicBoulesEtBits_APPLE2_ORIC.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicBoulesEtBits_APPLE2_ORIC_playerconfig.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicHocusPocus_APPLE2_ORIC.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicHocusPocus_APPLE2_ORIC_playerconfig.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicSarkboteur_APPLE2_ORIC.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicSarkboteur_APPLE2_ORIC_playerconfig.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicYMType_APPLE2_ORIC.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/resources/MusicYMType_APPLE2_ORIC_playerconfig.a
        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/6502/apple2_oric/resources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/tester/PlayerAKYTester_APPLE2.a
        ${CMAKE_SOURCE_DIR}/hardware/apple2_oric/playerAky/sources/tester/PlayerAKYTester_ORIC.a
        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/6502/apple2_oric/tester
        COMPONENT ${OUTPUT_COMPONENT}
)

# AKY player - 6502 - Atari 8 bits.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/PlayerAky.asm
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/psgSettings.png
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/readme.txt
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/setupSourceProfile.png
        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/6502/atari8bits
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/resources/KellyOn.ASM
        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/6502/atari8bits/resources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/tester/AtariAkyTest.asm
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/tester/compile.bat
        ${CMAKE_SOURCE_DIR}/hardware/atari8bits/playerAky/sources/tester/mads.exe
        DESTINATION ${PLAYERS_FOLDER}/playerAky/sources/6502/atari8bits/tester
        COMPONENT ${OUTPUT_COMPONENT}
)

# FAP player.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/License.TXT
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/FapInit.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/FapMacro.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/FapPlay.asm
        DESTINATION ${PLAYERS_FOLDER}/playerFap/sources/z80
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/tester/PlayerFapTester_CPC.asm
        DESTINATION ${PLAYERS_FOLDER}/playerFap/sources/z80/tester
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/resources/FenyxKell - Bobline.fap"
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/resources/Targhan - A Harmless Grenade.fap"
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/resources/Targhan - Hocus Pocus.fap"
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/resources/Tom&Jerry - Boules Et Bits (Extended).fap"
        "${CMAKE_SOURCE_DIR}/hardware/cpc/playerFap/sources/resources/UltraSyd - Fractal.fap"
        DESTINATION ${PLAYERS_FOLDER}/playerFap/sources/z80/resources
        COMPONENT ${OUTPUT_COMPONENT}
)

# MOD player.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerMod/sources/PlayerMod_CPC.asm
        DESTINATION ${PLAYERS_FOLDER}/playerMod/sources/z80
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerMod/sources/resources/ShowThem.asm
        DESTINATION ${PLAYERS_FOLDER}/playerMod/sources/z80/resources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/playerMod/sources/tester/PlayerMODTester_CPC.asm
        DESTINATION ${PLAYERS_FOLDER}/playerMod/sources/z80/tester
        COMPONENT ${OUTPUT_COMPONENT}
)

# Sfx.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/cpc/soundEffects/sources/PlayerSoundEffects.asm
        DESTINATION ${PLAYERS_FOLDER}/playerSoundEffects/sources/z80
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/soundEffects/sources/resources/SoundEffects.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/soundEffects/sources/resources/SoundEffects_playerconfig.asm
        DESTINATION ${PLAYERS_FOLDER}/playerSoundEffects/sources/z80/resources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/soundEffects/sources/tester/SoundEffectsTester_CPC.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/soundEffects/sources/tester/SoundEffectsTester_MSX.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/soundEffects/sources/tester/SoundEffectsTester_SPECTRUM_PENTAGON.asm
        DESTINATION ${PLAYERS_FOLDER}/playerSoundEffects/sources/z80/tester
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/doc/export/SoundEffects.md
        DESTINATION ${PLAYERS_FOLDER}/playerSoundEffects/doc
        COMPONENT ${OUTPUT_COMPONENT}
)

# Misc.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/doc/export/Events.md
        ${CMAKE_SOURCE_DIR}/doc/export/RAW.md
        ${CMAKE_SOURCE_DIR}/doc/export/RawLinear.md
        DESTINATION ${PLAYERS_FOLDER}/misc/doc
        COMPONENT ${OUTPUT_COMPONENT}
)

# Serial.
# ----------------------------------------------------------
install(FILES
        ${CMAKE_SOURCE_DIR}/doc/serial/PackedData.adoc
        DESTINATION ${PLAYERS_FOLDER}/serial/doc
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/dsk/SerialCpc.dsk
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/dsk/SerialCpc.dsk.hfe
        DESTINATION ${PLAYERS_FOLDER}/serial/z80/binary
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/LICENSE.txt
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/PsgCpc.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/PsgCpc_PlayCity.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/Serial.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/SerialAlbireo.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/SerialBase.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/SerialBooster.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/SerialUsifac.asm
        DESTINATION ${PLAYERS_FOLDER}/serial/z80/sources
        COMPONENT ${OUTPUT_COMPONENT}
)
install(FILES
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/tester/CpcAlbireo.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/tester/CpcBooster.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/tester/CpcPlaycityAlbireo.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/tester/CpcPlaycityBooster.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/tester/CpcPlaycityUsifac.asm
        ${CMAKE_SOURCE_DIR}/hardware/cpc/serial/sources/tester/CpcUsifac.asm
        DESTINATION ${PLAYERS_FOLDER}/serial/z80/sources/tester
        COMPONENT ${OUTPUT_COMPONENT}
)

# Main program.
# ----------------------------------------------------------
# Conditional for the main software, as the BUNDLE must be set only for Mac.
if (APPLE)
    install(TARGETS
            MainSoftware
            RUNTIME DESTINATION ${DESTINATION_FOLDER}
            BUNDLE DESTINATION ${DESTINATION_FOLDER}            # Necessary for mac. Only for the main software!
            COMPONENT ${OUTPUT_COMPONENT}
    )
else()
    install(TARGETS
            MainSoftware
            RUNTIME DESTINATION ${DESTINATION_FOLDER}
            COMPONENT ${OUTPUT_COMPONENT}
    )
endif()

# Command line tools.
# ----------------------------------------------------------
install(TARGETS
        SongToAkg
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToAkm
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToAky
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToFap
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToEvents
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToRaw
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToRawLinear
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToWav
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToYm
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToVgm
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToSoundEffects
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        SongToSamples
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
install(TARGETS
        Z80Profiler
        RUNTIME DESTINATION ${TOOLS_DESTINATION_FOLDER}
        COMPONENT ${OUTPUT_COMPONENT}
)
