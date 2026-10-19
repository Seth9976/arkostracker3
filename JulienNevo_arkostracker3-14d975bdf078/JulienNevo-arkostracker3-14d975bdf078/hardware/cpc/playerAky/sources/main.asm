        ;Tests the AKY player.

        ;This is NOT included to the release package.

        buildsna
        bankset 0

        ;Sound effects?
        ;PLY_AKY_MANAGE_SOUND_EFFECTS = 1
        ;If sound effects, the PSG number where to play SFX must be declared (>=1).
        ;PLY_AKY_SFX_PSG_NUMBER = 1

        ;Include digidrums replay? Only for AKY MultiPSG.
        ;PLY_AKY_USE_DIGIDRUMS = 1

        org #100
Start   equ $

        di
        ld hl,#c9fb
        ld (#38),hl

        ld hl,#c000
        ld de,#c001
        ld bc,#1000
        ld (hl),l
        ldir

        ld bc,#bc06
        out (c),c
        ld bc,#bd00+2
        out (c),c

        ld hl,Music_Start
        call PLY_AKY_Init
        ;call PLY_AKYst_Init
        ;ld de,PlayReturn
        ;call PLY_AKYsid_Init

        IFDEF PLY_AKY_USE_DIGIDRUMS
                ld hl,MainEvents
                ld de,MainSample
                ld a,1
                call PLY_AKY_InitDigidrums
        ENDIF

        IFDEF PLY_AKY_MANAGE_SOUND_EFFECTS
                ld hl,Main_SoundEffects
                call PLY_AKY_InitSoundEffects
        ENDIF

        ;Some dots on the screen to judge how much CPU takes the player.
        ld a,255
        ld hl,#d800 + 4 * #50
        ld (hl),a
        ld hl,#d800 + 5 * #50
        ld (hl),a
        ld hl,#d800 + 6 * #50
        ld (hl),a

        ;Hides the screen to show only the border.
        ;ld bc,#bc01
        ;out (c),c
        ;inc b
        ;out (c),0

Sync:   ld b,#f5
        in a,(c)
        rra
        jr nc,Sync + 2
Sync2:   ld b,#f5
        in a,(c)
        rra
        jr c,Sync2 + 2

        ;A test counter, if needed.
Counter: ld hl,864
        dec hl
        ld (Counter + 1),hl
        ld a,l
        or h
        jr nz,CounterEnd
;BRKCounter
        nop
CounterEnd:

        IFNDEF PLY_AKY_USE_DIGIDRUMS
                ei
                nop
                halt
                halt
                di
        ENDIF

        ld bc,#7f10
        out (c),c
        ld a,#4b
        out (c),a



        call PLY_AKY_Play
        ;call PLY_AKYst_Play
        ;ld (SaveSp + 1),sp

        ;        ld sp,RetTable
        ;        ld h,0                  ;H' is the line counter.
        ;exx
        ;jp PLY_AKYsid_Play
;PlayReturn
;SaveSp  ld sp,0

        ld bc,#7f10
        out (c),c
        ld a,#54
        out (c),a


        IFDEF PLY_AKY_MANAGE_SOUND_EFFECTS
SfxCounter: ld a,0
        inc a
        cp 100
        jr nz,SfxCounterNotEnded

        ld a,11          ;A = Sound effect number (>0!).
        ld c,0          ;C = The channel where to play the sound effect (0, 1, 2).
        ld b,0          ;B = Inverted volume (0 = full volume, 16 = no sound). Hardware sounds are also lowered.
        call PLY_AKY_PlaySoundEffect

        xor a
SfxCounterNotEnded:
        ld (SfxCounter + 1),a
        ENDIF

        jr Sync


Code1
        exx
                ld bc,#7f4c
                out (c),c
                ld c,#55
                out (c),c
                ds 3,0
                inc h
        exx
        jp (iy)
Code2
        exx
                ld bc,#7f4b
                out (c),c
                ld c,#55
                out (c),c
                ld sp,RetTable
                inc h
        exx
        jp (iy)


;Alternative code while sending PSG.
Code1Alt
        ld bc,#7f4c
        out (c),c
        ld c,#55
        out (c),c
        ds 3,0
        inc ixh
        jp (hl)         ;20
Code2Alt
        ld bc,#7f4b
        out (c),c
        ld c,#55
        out (c),c
        ld sp,RetTable
        inc ixh
        jp (hl)

;FIXME TEST
;IN:    H' = line counter
;       L  = #f6
;       IX = Return address
SidTopShelf
        exx
.volume         ld bc,#f48f
                out (c),c
                ld b,l
                out (c),c
                out (c),0
                inc h
        exx
        jp (iy)                         ;21


;SID for extra speed, but less convenient.
;IXH= counter.
;HL'= return
;BC' = used.
;E'  = #c0
SidAltTopShelf    
.volume ld bc,#f48f             ;#f400 + Value
        out (c),c
        ld b,#f6
        out (c),c               ;#f680
        out (c),e               ;#f6c0
        inc ixh
        jp (hl)                 ;18







RetTable
RetTable_PtCode1        dw Code1
RetTable_PtCode2        dw Code2






Music_Start:
        ;Includes here the Player Configuration source of the songs (you can generate them with AT3 while exporting the songs).
        ;If you don't have any, the player will use a default Configuration (full code used), which may not be optimal.
        ;If you have several songs, include all their configuration here, their flags will stack up!
        ;Warning, this must be included BEFORE the player is compiled.
        ;include "Mysong1_playerconfig.asm"
        ;include "Mysong2_playerconfig.asm"

        ;include "resources/HocusPocus_playerconfig.asm"
        ;include "resources/HocusPocus.asm"

        ;include "resources/MusicBoulesEtBits_playerconfig.asm"
        ;include "resources/MusicBoulesEtBits.asm"

        ;include "resources/MusicCarpet_playerconfig.asm"
        ;include "resources/MusicCarpet.asm"

        ;include "resources/HardOnlyWithNoiseEnvelope9.asm"
        ;include "resources/HardOnlyWithNoiseEnvelope9_playerconfig.asm"

        ;include "resources/SimpleSoftSoundChannel1To9.asm"

        ;include "resources/MusicEmpty_playerconfig.asm"
        ;include "resources/MusicEmpty.asm"

        ;include "resources/DigitestMusic_CPC_playerconfig.asm"       ;Includes the music.
        ;include "resources/DigitestMusic_CPC.asm"

        ;include "resources/Simple.asm"
        include "resources/aaaNewFormat.asm"
Music_End:

        IFDEF PLY_AKY_USE_DIGIDRUMS
                include "resources/DigitestEvents.asm"                       ;Includes the events and samples.
                include "resources/DigitestSamples.asm"
        ENDIF

Main_SoundEffects:
        IFDEF PLY_AKY_MANAGE_SOUND_EFFECTS
                ;include "resources/SoundEffectsDeadOnTime_playerconfig.asm"
                include "resources/SoundEffectsDeadOnTime.asm"
        ENDIF

Main_Player_Start:
        ;PLY_AKY_HARDWARE_PLAYCITY = 1
        ;PLY_AKY_HARDWARE_SPECNEXT = 1
        ;PLY_AKY_HARDWARE_TURBOSOUND = 1
        ;PLY_AKY_HARDWARE_FPGAPSG = 1
        ;PLY_AKY_HARDWARE_DARKY = 1

        PLY_AKY_HARDWARE_CPC = 1
        ;PLY_AKY_HARDWARE_MSX = 1

        ;PLY_AKY_REMOVE_HOOKS = 1
        ;PLY_AKYst_REMOVE_HOOKS = 1

        ;Want a ROM player (a player without automodification)?
        ;PLY_AKY_ROM = 1                         ;Must be set BEFORE the player is included.

        ;Declares the buffer for the ROM player, if you're using it.
        ;LIMITATION: the address of the buffer must be declared *before* including the player, but PLY_AKY_ROM_BufferSize is only known *after*.
        ;A bit annoying, but you can compile once, get the buffer size, and hardcode it to put the buffer wherever you want.
        IFDEF PLY_AKY_ROM
                PLY_AKY_ROM_Buffer = #c000                  ;Can be set anywhere.
        ENDIF

        include "PlayerAky.asm"                             ;Does NOT support sfx.
        ;include "PlayerAkyMultiPsg.asm"                    ;Support sfx.
        ;include "PlayerAkySid_CPC.asm"
        ;ALIGN 256
        ;include "PlayerAkySid_Tables_CPC.asm"

        ;include "PlayerAkyStabilized_CPC.asm"

Main_Player_End:

        print "Size of player: ", {hex}(Main_Player_End - Main_Player_Start)
        print "Size of music: ", {hex}(Music_End - Music_Start)
                IFDEF PLY_AKY_ROM
        print "Size of buffer in ROM: ", {hex}(PLY_AKY_ROM_BufferSize)
                ENDIF
        print "Total size (player and music): ", {hex}($ - Music_Start)
