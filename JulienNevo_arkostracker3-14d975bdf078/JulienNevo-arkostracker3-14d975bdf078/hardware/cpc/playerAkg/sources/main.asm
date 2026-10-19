        ;Tests the AKG player.

        ;This is NOT included to the release package.

        ;Uncomment this to build a SNApshot, handy for testing (RASM feature).
        buildsna
        bankset 0

        org #100

        di
        ld hl,#c9fb
        ld (#38),hl
        ld sp,#38

        ;Puts some markers to see the CPU.
        ld a,255
        ld hl,#c000 + 5 * #50
        ld (hl),a
        ld hl,#c000 + 6 * #50
        ld (hl),a
        ld hl,#c000 + 7 * #50
        ld (hl),a
        ld hl,#c000 + 8 * #50
        ld (hl),a
        ld hl,#c000 + 9 * #50
        ld (hl),a

InitSong:
        ld hl,Music
        xor a
        ;ld a,2
        call PLY_AKG_Init

Sync:   ld b,#f5
        in a,(c)
        rra
        jr nc,Sync + 2
        ei
        nop
        halt
        halt

        ;If 25 hz.
        ;halt
        ;halt
        ;halt
        ;halt
        ;halt
        ;halt

        di

        ld b,90
        djnz $

        ld bc,#7f10
        out (c),c
        ld a,#4b
        out (c),a

        ;A test counter, if needed.
Counter: ld hl,12+1
        dec hl
        ld (Counter + 1),hl
        ld a,l
        or h
        jr nz,CounterEnd
;BRKaaaaaaaa:
        nop
CounterEnd:

;aaaaaaaaaa:
        ;call PLY_AKG_Play
        call Player + 3
;aaaaaa
        ld bc,#7f10
        out (c),c
        ld a,#5c
        out (c),a
        ei
        nop
        halt
        di
        ld a,#54
        out (c),a

        ld a,5 + 64
        call Keyboard
        cp #7f
        jr z,InitSong           ;Reinit the song.
        jr Sync

        ;Any event? If yes, shows a nice color.
;        ld a,(PLY_AKG_Event)
;        or a
;        jr z,NoEvent
;        ld a,#4c
;        out (c),a
;NoEvent:


        jr Sync

;Checks a line of the keyboard.
;IN:    A = line + 64.
;OUT:   A = key mask.
Keyboard:
        ld bc,#f782
        out (c),c
        ld bc,#f40e
        out (c),c
        ld bc,#f6c0
        out (c),c
        out (c),0
        ld bc,#f792
        out (c),c
        dec b
        out (c),a
        ld b,#f4
        in a,(c)
        ld bc,#f782
        out (c),c
        dec b
        out (c),0
        ret



        ;PLY_CFG_ConfigurationIsPresent = 1
        ;PLY_CFG_UseSpeedTracks = 1
        ;PLY_CFG_UseEventTracks = 1
	;PLY_CFG_UseTranspositions = 1
	;PLY_CFG_UseHardwareSounds = 1
	;PLY_CFG_UseEffects = 1
	;PLY_CFG_UseRetrig = 1
	;PLY_CFG_UseInstrumentRetrig = 1
	;PLY_CFG_UseInstrumentLoopTo = 1
	;PLY_CFG_NoSoftNoHard = 1
	;PLY_CFG_NoSoftNoHard_Noise = 1
	;PLY_CFG_SoftOnly = 1
        ;PLY_CFG_SoftOnly_Noise = 1
	;PLY_CFG_SoftOnly_ForcedSoftwarePeriod = 1
        ;PLY_CFG_SoftOnly_SoftwareArpeggio = 1
	;PLY_CFG_SoftOnly_SoftwarePitch = 1
	;PLY_CFG_SoftToHard = 1
	;PLY_CFG_SoftToHard_Noise = 1
	;PLY_CFG_SoftToHard_ForcedSoftwarePeriod = 1
	;PLY_CFG_SoftToHard_SoftwareArpeggio = 1
	;PLY_CFG_SoftToHard_SoftwarePitch = 1
	;PLY_CFG_SoftToHard_HardwarePitch = 1
	;PLY_CFG_SoftToHard_Retrig = 1
	;PLY_CFG_HardOnly = 1
	;PLY_CFG_HardOnly_Noise = 1
	;PLY_CFG_HardOnly_ForcedHardwarePeriod = 1
	;PLY_CFG_HardOnly_HardwareArpeggio = 1
	;PLY_CFG_HardOnly_HardwarePitch = 1
	;PLY_CFG_HardOnly_Retrig = 1
	;PLY_CFG_HardToSoft = 1
	;PLY_CFG_HardToSoft_Noise = 1
	;PLY_CFG_HardToSoft_ForcedHardwarePeriod = 1
	;PLY_CFG_HardToSoft_HardwareArpeggio = 1
	;PLY_CFG_HardToSoft_HardwarePitch = 1
	;PLY_CFG_HardToSoft_SoftwarePitch = 1
	;PLY_CFG_HardToSoft_Retrig = 1
	;PLY_CFG_SoftAndHard = 1
        ;PLY_CFG_SoftAndHard_Noise = 1
	;PLY_CFG_SoftAndHard_ForcedSoftwarePeriod = 1
	;PLY_CFG_SoftAndHard_SoftwareArpeggio = 1
        ;PLY_CFG_SoftAndHard_SoftwarePitch = 1
	;PLY_CFG_SoftAndHard_ForcedHardwarePeriod = 1
	;PLY_CFG_SoftAndHard_HardwareArpeggio = 1
	;PLY_CFG_SoftAndHard_HardwarePitch = 1
	;PLY_CFG_SoftAndHard_Retrig = 1
	;PLY_CFG_SFX_LoopTo = 1
	;PLY_CFG_SFX_NoSoftNoHard = 1
	;PLY_CFG_SFX_NoSoftNoHard_Noise = 1
	;PLY_CFG_SFX_SoftOnly = 1
	;PLY_CFG_SFX_SoftOnly_Noise = 1
	;PLY_CFG_SFX_HardOnly = 1
	;PLY_CFG_SFX_HardOnly_Noise = 1
	;PLY_CFG_SFX_HardOnly_Retrig = 1
	;PLY_CFG_SFX_SoftAndHard = 1
	;PLY_CFG_SFX_SoftAndHard_Noise = 1
	;PLY_CFG_SFX_SoftAndHard_Retrig = 1

	;PLY_CFG_UseEffect_Legato = 1
	;PLY_CFG_UseEffect_Reset = 1
	;PLY_CFG_UseEffect_ForcePitchTableSpeed = 1
	;PLY_CFG_UseEffect_ForceArpeggioSpeed = 1
	;PLY_CFG_UseEffect_ForceInstrumentSpeed = 1
	;PLY_CFG_UseEffect_PitchGlide = 1
	;PLY_CFG_UseEffect_PitchUp = 1
	;PLY_CFG_UseEffect_PitchDown = 1
	;PLY_CFG_UseEffect_PitchTable = 1
	;PLY_CFG_UseEffect_Arpeggio3Notes = 1
	;PLY_CFG_UseEffect_Arpeggio4Notes = 1
	;PLY_CFG_UseEffect_ArpeggioTable = 1
	;PLY_CFG_UseEffect_SetVolume = 1
	;PLY_CFG_UseEffect_VolumeIn = 1
	;PLY_CFG_UseEffect_VolumeOut = 1





Music:
        ;include "resources/EdredonTiramisu_playerconfig.asm"
        ;include "resources/EdredonTiramisu.asm"

        ;include "resources/LightGrid_playerconfig.asm"
        ;include "resources/LightGrid.asm"

        include "resources/Music_AHarmlessGrenade_playerconfig.asm"
        include "resources/Music_AHarmlessGrenade.asm"

        ;include "resources/Music_Empty_playerconfig.asm"
        ;include "resources/Music_Empty.asm"

        ;include "resources/Music_ForceInstrumentSpeedChannel1_playerconfig.asm"
        ;include "resources/Music_ForceInstrumentSpeedChannel1.asm"

        ;include "resources/Music_ArpeggioEffectChannel1.asm"
        ;include "resources/Music_ArpeggioEffectChannel1_playerconfig.asm"

        ;include "resources/Music_SimpleSoftChannel1.asm"
        ;include "resources/Music_SimpleSoftChannel1_playerconfig.asm"

        ;include "resources/Music_SimpleSoftChannel1To3.asm"
        ;include "resources/Music_SimpleSoftChannel1To3_playerconfig.asm"

        ;include "resources/Music_SoftToHardChannel1To3.asm"
        ;include "resources/Music_SoftToHardChannel1To3_playerconfig.asm"

        ;include "resources/Roudoudou.asm"
        ;include "resources/Roudoudou_playerconfig.asm"

        ;include "resources/Enduro.asm"
        ;include "resources/Enduro_playerconfig.asm"

        ;include "resources/Music_Molusk.asm"
        ;include "resources/Music_Molusk_playerconfig.asm"

        ;include "resources/Music_MoluskDrumPatternChannel1.asm"
        ;include "resources/Music_MoluskDrumPatternChannel1_playerconfig.asm"

        ;include "resources/Music_HocusPocus.asm"
        ;include "resources/Music_HocusPocus_playerconfig.asm"

        ;include "resources/Music_GlideChannelAll.asm"
        ;include "resources/Music_GlideChannelAll_playerconfig.asm"

        ;include "resources/Music_GlideChannel1.asm"
        ;include "resources/Music_GlideChannel1_playerconfig.asm"

        ;include "resources/Music_Glide2Channel1.asm"
        ;include "resources/Music_Glide2Channel1_playerconfig.asm"

        ;include "resources/Music_PitchEffectChannel1.asm"
        ;include "resources/Music_PitchEffectChannel1_playerconfig.asm"

        ;include "resources/Music_TranspositionsShorter.asm"
        ;include "resources/Music_TranspositionsShorter_playerconfig.asm"
MusicEnd:

        ;PLY_AKG_HARDWARE_MSX = 1
        ;PLY_AKG_HARDWARE_PCW = 1

        ;PLY_AKG_MANAGE_SOUND_EFFECTS = 1

        ;PLY_AKG_REMOVE_HOOKS = 1
        ;PLY_AKG_REMOVE_STOP_SOUNDS = 1
        ;PLY_AKG_REMOVE_FULL_INIT_CODE = 1

        ;PLY_AKG_ROM = 1

        IFDEF PLY_AKG_Rom
                PLY_AKG_ROM_Buffer = #c000
        ENDIF

Player:

        include "PlayerAkg.asm"
PlayerEnd:


        print "Size of player: ", {hex}(PlayerEnd - Player)
        print "Size of music: ", {hex}(MusicEnd - Music)
        IFDEF PLY_AKG_Rom
                print "Size of ROM buffer: ", {hex}(PLY_AKG_ROM_BufferSize)
        ENDIF
