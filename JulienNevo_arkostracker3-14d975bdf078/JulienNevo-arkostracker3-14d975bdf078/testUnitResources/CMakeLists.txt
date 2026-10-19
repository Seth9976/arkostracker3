project(TestUnitResources VERSION 1.0.0)

set(TargetName ${PROJECT_NAME})

juce_add_binary_data(${TargetName}
        SOURCES
        ../binaryResources/RetrigInBars.png

        "music/soundtrakker/Kangaroo - Alienall.128"
        "music/soundtrakker/Kangaroo - Heppe2.128"
        "music/soundtrakker/Targhan - Deep Space (Resonance).128"
        "music/soundtrakker/Targhan - Golio.128"
        "music/soundtrakker/BSC - Space Debris.128"
        "music/soundtrakker/ResonanceWithHeader.128"

        "music/starkos/Targhan - DemoIzArt - End Part.sks"
        "music/starkos/Targhan - DemoIzArt - Twist Part.sks"
        "music/starkos/Targhan - Midline Process - Carpet.sks"
        "music/starkos/Targhan - Midline Process - Molusk.sks"
        "music/starkos/StarkosAll.sks"
        "music/starkos/TwistWithHeader.sks"

        music/at1/At1SongDemo.xml
        music/at1/At1Demo.aks
        music/at1/At1SongTJOutro.xml
        music/at2/At2AllInstrumentTypesChannel1To6.xml
        music/at2/At2AllInstrumentTypesChannel1To9.xml
        music/at2/At2AdeleSkyfall6ChannelsPattern0.xml
        music/at2/At2AllEffects.aks
        music/at2/At2AllEffectsChannel1.aks
        music/at2/At2AllEffectsChannel2.aks
        music/at2/At2AllEffectsChannel3.aks
        music/at2/At2AllInstrumentTypesChannel1.aks
        music/at2/At2AllInstrumentTypesChannel1To6.aks
        music/at2/At2AllInstrumentTypesChannel1To9.aks
        music/at2/At2AllInstrumentTypesChannel2.aks
        music/at2/At2AllInstrumentTypesChannel3.aks
        music/at2/At2AllSoundsLwAkm.aks
        music/at2/At2ArpeggioEffectCummulatedChannel1To3.aks
        music/at2/At2ArpeggioInlineConverter_Simple.xml
        music/at2/At2ArpeggioInlineConverter_TooMany.xml
        music/at2/At2DrumPatternMoluskChannel1.aks
        music/at2/At2Empty.aks
        music/at2/At2EventsNoRetrig.aks
        music/at2/At2ExportRawInput.xml
        music/at2/At2ForceArpeggioSpeedChannel1.aks
        music/at2/At2ForceInstrumentSpeedChannel1.aks
        music/at2/At2ForceInstrumentSpeedChannelAll.aks
        music/at2/At2GlideDown.aks
        music/at2/At2GlideEffect2Channel1.aks
        music/at2/At2GlideEffect2Channel2.aks
        music/at2/At2GlideEffect2Channel3.aks
        music/at2/At2GlideEffect2ChannelAll.aks
        music/at2/At2GlideEffectChannel1.aks
        music/at2/At2GlideEffectChannelAll.aks
        music/at2/At2GlideUpAndDown.aks
        music/at2/At2GlideUpAndDownShort.aks
        music/at2/At2GlideUp.aks
        music/at2/At2HocusHardBug.aks
        music/at2/At2HocusHardHighPitchBug.aks
        music/at2/At2HocusShorter.aks
        music/at2/At2InlineArpeggiosAndSpeedChannel1.aks
        music/at2/At2InlineArpeggiosAndSpeedChannel2.aks
        music/at2/At2InlineArpeggiosAndSpeedChannel3.aks
        music/at2/At2InlineArpeggiosChannelAll.aks
        music/at2/At2PitchDown.aks
        music/at2/At2PitchEffectChannel1.aks
        music/at2/At2PitchTableEffectAndForcePitchSpeedAndPitchAndResetChannel1.aks
        music/at2/At2PitchTableEffectAndForcePitchSpeedChannel1.aks
        music/at2/At2PitchTableEffectsChannel1.aks
        music/at2/At2PitchUp.aks
        music/at2/At2RetrigChannel1.aks
        music/at2/At2Sarkboteur.aks
        music/at2/At2SeveralSubsongs.aks
        music/at2/At2Simple.xml
        music/at2/At2Simple2.xml
        music/at2/At2SimpleSoftSoundChannel1.aks
        music/at2/At2SimpleSoftSoundChannel2.aks
        music/at2/At2SimpleSoftSoundChannel3.aks
        music/at2/At2SimpleSoftSoundChannel1To6.xml
        music/at2/At2SimpleSoftSoundChannel1To9.xml
        music/at2/At2SimpleSoftAndNoiseSoundChannel1To6.xml
        music/at2/At2SimpleSoftAndNoiseSoundChannel1To9.xml
        music/at2/At2SoftAndHardOnlyChannel1To6.xml
        music/at2/At2SoftAndHardOnlyChannel1To9.xml
        music/at2/At2Bug9ChannelsHardToSoft.xml
        music/at2/At2SoftwareOnly
        music/at2/At2SoftAndHard.aks
        music/at2/At2SongShortHardArp.xml
        music/at2/At2Speed.aks
        music/at2/At2SpeedAtBeginning.xml
        music/at2/At2TarghanAHarmlessGrenade.aks
        music/at2/At2TarghanAHarmlessGrenade_LoopAt4.aks
        music/at2/At2TarghanHocusPocus.aks
        music/at2/At2TheLastV8.aks
        music/at2/At2TheLastV8.xml
        music/at2/At2TheLastV86Channels.aks
        music/at2/At2Transpositions.aks
        music/at2/At2TranspositionsShorter.aks
        music/at2/At2TranspositionsVolumeOnly.aks
        music/at2/At2VolumeEffectsChannel1.aks
        music/at2/At2VolumeEffectsFullVolumeChannel1.aks
        music/at2/At2VolumeEffectsSetOnlyChannel1To3.aks
        music/at2/At2LegatoChannel1.aks
        music/at2/At2MoluskStart.aks
        music/at2/At2SimpleWithEvents.xml
        music/at2/At2SimpleWithEventsLoopPosition1.xml
        music/at2/At2EdredonAlcaloids.xml
        music/at2/At2SlapFight2Zipped.aks

        music/at3/At3AganamemnonShortNoPitches1Mhz.aks
        music/at3/At3AganamemnonShortNoPitches2Mhz.aks
        music/at3/At3_6subsongs.xml
        music/at3/At3_6subsongsMoreData.xml
        music/at3/At3ErrorSong2Subsongs.aks
        music/at3/At3HardOnlyAndNoise.xml
        music/at3/At3HardOnlyWithNoiseEnvelope9.xml
        music/at3/At3HardOnlyWithNoiseEnvelopeF.xml
        music/at3/At3HardToSoftAndNoise.xml
        music/at3/At3SoftAndHardAndNoise.xml
        music/at3/At3SoftToHardAndNoise.xml
        music/at3/At3TrackColors.xml
        music/at3/At3Sarkboteur.xml
        music/at3/At3HocusPocusShorterWithReadOnly.xml
        music/at3/At3HocusPocusShorterNamedTracks.xml
        music/at3/At3SimpleForYmExport.xml
        music/at3/At3_100Hz6channels.xml
        music/at3/At3_200Hz6ChannelsSquare.xml
        music/at3/At3EventTypes.xml
        music/at3/At3MidiTest.aks
        music/at3/At3MidiSimple.aks
        music/at3/At3MidiSimple2.aks
        music/at3/At3CrimeParkingIntro.aks
        music/at3/At3BoulesBits.aks
        music/at3/At3Midi2Psgs.aks
        music/at3/At3SimpleWithVolume.aks
        music/at3/At3SimpleWav.aks
        music/at3/At3LopEars.aks
        music/at3/At3TempoChange.aks
        music/at3/At3TheRivals1Mhz.xml
        music/at3/At3SecretRoomShort.xml
        music/at3/At3VolumeOutAndLegato.xml
        music/at3/At3SidExamplesCpc.xml

        music/akm/AkmBugHarmlessArpTableEffect.aks
        music/akm/AkmBugHarmlessPitchTableEffect.aks
        music/akm/AkmBugHarmlessCrash.aks
        music/akm/AkmBugUnknownEffect.aks
        music/akm/AkmManyArpeggios.aks
        music/akm/AkmManyPitches.aks

        music/chp/simple.chp
        music/chp/test.chp
        music/chp/AllSounds.chp
        music/chp/cngsoft/ABADIA1.CHP
        music/chp/cngsoft/ADDAMSF0.CHP
        music/chp/cngsoft/AMAUROTH.CHP
        music/chp/cngsoft/ARKANOID.CHP
        music/chp/cngsoft/ARKOID2A.CHP
        music/chp/cngsoft/bactron.chp
        music/chp/cngsoft/BOMBUZAL.CHP
        music/chp/cngsoft/burninr1.chp
        music/chp/cngsoft/CHIMERA2.CHP
        music/chp/cngsoft/hydrofol.chp
        music/chp/cngsoft/JSW1.CHP
        music/chp/cngsoft/THANATOS.CHP
        music/chp/cngsoft/THUNCATS.CHP

        music/furnace/6ChannelsStrangeInstruments.fur
        music/furnace/aeration.fur
        music/furnace/FurnaceSimple.fur
        music/furnace/TwoSubsongs.fur
        music/furnace/OneChannelSpeaker.fur

        music/vt2/2018_EA_demosong.vt2
        music/vt2/2018_nq_skrju_demosong.vt2
        music/vt2/Simple.vt2

        music/wyz/jinj_med.xml
        music/wyz/maryjane2.xml
        music/wyz/maryjane2Modified.xml
        music/wyz/pt10NtscZx.xml
        music/wyz/shampooCpc.xml
        music/wyz/gothic.xml
        music/wyz/gothicModified.xml
        music/wyz/knightmare_start.xml
        music/wyz/midnight_xprss.xml
        music/wyz/pt10.xml
        music/wyz/quezesto.xml
        music/wyz/RA_PSG.xml

        music/mod/BLUESHAD.MOD
        music/mod/EAGLES.MOD
        music/mod/ENDTHEME.MOD
        music/mod/transformer.mod
        music/mod/SARCOPHA.MOD
        "music/mod/Castle Master.mod"

        music/midi/Drums.mid
        music/midi/FourNotes.mid
        music/midi/FourNotesMidi0.mid
        music/midi/SimpleNotes.mid
        music/midi/TempoChange.mid
        music/midi/ThreeChannelsWithEachItsProgram.mid
        music/midi/TimeSignature3_4.mid
        music/midi/VolumeChange.mid
        music/midi/PulkoMidiCrash.mid
        "music/midi/Crownland - intro.mid"
        music/midi/SimpleExample.mid
        "music/midi/Hospital Music 3 V1_3.mid"

        music/ym/ym6InterleavedAganamemnon.ym
        music/ym/ym6NonInterleavedAganamemnon.ym
        music/ym/ym6InterleavedAganamemnon2MhzPsg.ym

        "instrument/at2/AT2Bass Jon Dunn.xml"
        "instrument/at2/AT2Fenyx Kell Laugh.xml"
        "instrument/at2/AT2What Is That.xml"

        expected/export/xml/AT3HarmlessGrenade.xml
        expected/export/xml/AT3HarmlessGrenadeWithoutSomeSfxs.xml
        expected/export/xml/AT3DiaEnd.xml
        expected/export/xml/AT3SidCapabilityAtariSt.xml
        expected/export/xml/AT3SidCapabilityCustom.xml
        expected/export/aky/At2SimpleAky.asm
        expected/export/aky/At2SimpleAky.bin
        expected/export/aky/At2HocusPocusAky.asm
        expected/export/aky/At2HocusPocusAky.bin
        expected/export/aky/At2GlideUpAky.asm
        expected/export/aky/HocusShorter.asm
        expected/export/aky/HarmlessGrenade.asm
        expected/export/aky/AT2AkyHocusHardHighPitchBug.bin
        expected/export/aky/At3SidExamplesCpc.asm
        expected/export/akg/AkgAt2Simple.asm
        expected/export/akg/AkgAt2Sarkboteur.asm
        expected/export/akg/AkgAt2Sarkboteur_playerconfig.asm
        expected/export/events/eventsSarkboteur.asm
        expected/export/events/eventsLoopPosition0.asm
        expected/export/events/eventsLoopPosition1.asm
        expected/export/events/At3EventTypes_all.asm
        expected/export/events/At3EventTypes_event.asm
        expected/export/events/At3EventTypes_sample.asm
        expected/export/midi/ExpectedMidiSeveralChannelsTempo.mid
        expected/export/midi/ExpectedMidiSimple.mid
        expected/export/midi/ExpectedMidiSimple2.mid
        expected/export/midi/ExpectedMidiCrimeParkingIntro.mid
        expected/export/midi/ExpectedMidiCrimeParkingIntroMoreTracks.mid
        expected/export/midi/ExpectedMidi2Psgs.mid
        expected/export/mod/ExportSimple.mod
        expected/export/mod/ExportSample.mod
        expected/export/mod/ExportMolusk.mod
        expected/export/mod/ExportLastV8.mod
        expected/export/mod/ExportTempoChange.mod
        expected/export/raw/ExportRawOutput.asm
        expected/export/raw/ExportRawOutputMod.asm
        expected/export/raw/ExportSarkboteur.asm
        expected/export/rawLinear/ExportRawLinearSimple.asm
        expected/export/rawLinear/ExportRawLinearSimpleWithTransposition.asm
        expected/export/rawLinear/ExportRawLinearSample.asm
        expected/export/rawLinear/ExportRawLinearSampleSpeed1.asm
        expected/export/rawLinear/ExportRawLinearWithLoop.asm
        expected/export/rawLinear/ExportRawLinear2Psgs.asm
        expected/export/sfx/sfxSoftOnlyWithLoop.asm
        expected/export/sfx/sfxSoftAll.asm
        expected/export/sfx/sfxFull.asm
        expected/export/sfx/sfxFullMinus.asm
        expected/export/txt/SarkboteurTxtExport.txt
        expected/export/vgm/HarmlessLoopAt4.vgm
        expected/export/vgm/HarmlessLoopAt4.vgz
        expected/export/vgm/LastV86Channels.vgz
        expected/export/ym/HarmlessInterleaved.ym
        expected/export/ym/HarmlessNonInterleaved.ym
        expected/export/ym/At3SimpleForYmExport.ym
        expected/export/ym/moluskYm3Interleaved.ym

        rasm/RasmAkyDiaEndInput.asm
        rasm/RasmAkyDiaEndResult.bin
        rasm/RasmUndef.asm
        rasm/testhead.bas
        rasm/BinarySongShortXmlInput.asm
        rasm/BinarySongShortXmlResult.bin
        ../hardware/cpc/playerAkg/sources/PlayerAkg.asm
        ../hardware/cpc/playerAkg/sources/PlayerAkg_SoundEffects.asm
        ../hardware/cpc/playerAky/sources/PlayerAky.asm
        ../hardware/cpc/playerAky/sources/PlayerAkyStabilized_CPC.asm
        ../hardware/cpc/playerAky/sources/PlayerAkyMultiPsg.asm
        ../hardware/cpc/playerAkm/sources/PlayerAkm.asm
        ../hardware/cpc/playerAkm/sources/PlayerAkm_SoundEffects.asm

        sfx/sfxWithHardware.xml

        fap/FapHarmlessGrenade.fap
        fap/FapHarmlessGrenade.ym
        fap/FapUltraSydFractal.fap
        fap/FapUltraSydFractal.ym

        wav/Analogstring.wav

        z80emulator/allInstructionSet.asm
        z80emulator/allInstructionSet.log

        z80profiler/ABADIA1_CHPZ80_Load500.BIN
        z80profiler/ABADIA1_CHPZ80_withHeader.BIN
)