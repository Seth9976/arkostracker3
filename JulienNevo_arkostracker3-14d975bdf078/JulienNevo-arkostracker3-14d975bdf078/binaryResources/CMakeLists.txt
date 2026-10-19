project(BinaryResourcesMain VERSION 1.0.0)

set(TargetName ${PROJECT_NAME})

juce_add_binary_data(${TargetName}
        #HEADER_NAME BinaryDataMain
        SOURCES

        LogoWithTextBelow.png
        Logo512.png

        LTWave.ttf
        UbuntuMono-B.ttf
        UbuntuMono-R.ttf

        ActivityIndicator.png

        IconNew.png
        IconRename.png
        IconDelete.png
        IconDeleteOn.png
        IconCollapsed1234.png

        IconTitlebarClose.png
        IconTitlebarMinimize.png
        IconTitlebarMaximize.png
        IconDecSmall.png
        IconIncSmall.png

        IconPlayPattern.png
        IconPlayPatternFromStart.png
        IconPlaySong.png
        IconPlaySongFromStart.png
        IconStop.png

        IconZoomX.png
        IconFolder.png
        IconDisk.png

        IconLink.png
        IconLinkedTo.png

        IconShrink.png
        IconMeters.png

        Lock.png

        LinkHardOnly.png
        LinkHardToSoft.png
        LinkNoSoftNoHard.png
        LinkSoftAndHard.png
        LinkSoftOnly.png
        LinkSoftToHard.png

        LinkerNew.png
        LinkerRepeat.png

        PanelArpeggioList.png
        PanelArpeggioTable.png
        PanelDummy.png
        PanelInstrument.png
        PanelInstrumentList.png
        PanelPattern.png
        PanelPitchList.png
        PanelPitchTable.png

        HardwareEnvelope8.png
        HardwareEnvelope9.png
        HardwareEnvelopeA.png
        HardwareEnvelopeB.png
        HardwareEnvelopeC.png
        HardwareEnvelopeD.png
        HardwareEnvelopeE.png
        HardwareEnvelopeF.png

        ArrowDown.png
        ArrowUp.png

        IconMinus.png
        IconPlus.png
        IconRetrigOn.png
        IconRetrigOff.png
        IconRecordOn.png
        IconRecordOff.png
        IconStep.png
        IconWriteInstrumentOn.png
        IconWriteInstrumentOff.png
        IconLockOff.png
        IconLockOn.png
        IconWriteNoOverwrite.png
        IconWriteOverwrite.png
        IconArpeggioOn.png
        IconArpeggioOff.png
        IconPitchOn.png
        IconPitchOff.png
        IconToolboxOn.png
        IconToolboxOff.png
        IconLoopOn.png
        IconLoopOff.png
        IconForward.png
        IconBack.png
        IconFollowOff.png
        IconFollowOn.png
        IconFollowOffIfRecord.png
        IconLockLengthOn.png
        IconLockLengthOff.png
        IconWarning.png

        InstrumentTypePsg.png
        InstrumentTypeSample.png

        TrackHeaderEvent.png
        TrackHeaderSpeed.png
        TinyIconName.png
        TinyIconLinked.png
        TinyIconLinkedTo.png

        RetrigInBars.png

        SampleLoopStart.png
        SampleLoopEnd.png
        SerialIdle.png
        SerialTransmitting.png

        # For quick testing export.
        tester/AkgRawTesterCPC.asm
        tester/AkgWrapperBasicInterruptionsCPC.asm
        tester/AkyRawTesterCPC.asm
        tester/AkyDigidrumsRawTesterCPC.asm
        tester/AkyPlayCity9ChannelsRawTesterCPC.asm
        tester/AkySidRawTesterCPC.asm
        tester/ModRawTesterCPC.asm
        ../hardware/cpc/playerAkg/sources/PlayerAkg.asm
        ../hardware/cpc/playerAkg/sources/PlayerAkg_SoundEffects.asm
        ../hardware/cpc/playerAky/sources/PlayerAky.asm
        ../hardware/cpc/playerAky/sources/PlayerAkyMultiPsg.asm
        ../hardware/cpc/playerAky/sources/PlayerAkyMultiPsg_Digidrums.asm
        ../hardware/cpc/playerAky/sources/PlayerAkySid_CPC.asm
        ../hardware/cpc/playerMod/sources/PlayerMod_CPC.asm

        dsk/BasicCpcInterruptionsTemplate.dsk
)