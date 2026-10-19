project(TestUnitResources VERSION 1.0.0)

set(TargetName ${PROJECT_NAME})

juce_add_binary_data(${TargetName}
        SOURCES

        AllInstructions.asm
        player/PlayerAkg.asm
        player/PlayerAkg_SoundEffects.asm
        player/PlayerAky.asm
        player/PlayerAkyStabilized_CPC.asm
        player/PlayerAkyMultiPsg.asm
        player/PlayerAkyMultiPsg_SoundEffects.asm
        player/PlayerAkm.asm
        player/PlayerAkm_SoundEffects.asm
        player/PlayerLightweight.asm
        player/PlayerLightweight_SoundEffects.asm
        player/PlayerLightweight_SHARPMZ700.asm
        player/PlayerLightweight_SoundEffects_SHARPMZ700.asm
        player/PlayerSoundEffects.asm

        song/AkgEmpty.asm
        song/AkgHarmlessGrenade.asm
        song/AkyHarmlessGrenade.asm
        song/AkmAllSounds.asm
        song/AkmPitchTableAndForcePitchSpeedAndPitchAndResetChannel1.asm
        song/AkmArpeggioEffectStackedChannel1To3.asm
        song/LwEmpty.asm
        song/LwAllEffectsAndInstruments.asm
        song/SoundEffects.asm
)