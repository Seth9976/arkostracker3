        ;Tests the AKY multiPSG player with digidrums, for the AMSTRAD CPC, to be used for an QUICK TESTING EXPORT.
        ;It does NOT include anything.
        ;It does NOT has a start address.

        ;MusicStart must be set.
        ;MusicEvents must be set.
        ;MusicSamples must be set.
        ;DIGICHANNEL_INDEX must be set.

        PLY_AKY_HARDWARE_CPC = 1
        PLY_AKY_USE_DIGIDRUMS = 1
        ;PLY_AKY_DIGIDRUM_PSG_NUMBER = 1      ;Optional, default value is 1.

        di
        ld hl,#c9fb
        ld (#38),hl
        ld sp,$

        ;Initializes the music.
        ld hl,MusicStart
        call PLY_AKY_Init

        ;Initializes the digidrums.
        ld hl,MusicEvents               ;Address of the events (digidrums).
        ld de,MusicSamples              ;Address of the sample table.
        ld a,DIGICHANNEL_INDEX          ;Channel (0, 1 (=middle), 2)
        call PLY_AKY_InitDigidrums

Sync:   ld b,#f5
        in a,(c)
        rra
        jr nc,Sync + 2
Sync2:  in a,(c)
        rra
        jr c,Sync2

        ld bc,#7f10
        out (c),c
        ld a,#4b
        out (c),a

        ;Plays a frame of the music. Digidrums are also triggered when necessary.
        call PLY_AKY_Play

        ld bc,#7f54
        out (c),c

        jr Sync
