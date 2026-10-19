        ;Tests the AKY player, for AMSTRAD CPC, to be used for an QUICK TESTING EXPORT.
        ;It does NOT include anything.
        ;It does NOT has a start address.

        ;MusicStart must be set.

        di
        ld hl,#c9fb
        ld (#38),hl
        ld sp,$

    	;Initializes the music.
        ld hl,MusicStart
        call PLY_AKY_Init

        ;Some dots on the screen to judge how much CPU takes the player.
        ld a,255
        ld hl,#c000 + 5 * #50
        ld (hl),a
        ld hl,#c000 + 6 * #50
        ld (hl),a
        ld hl,#c000 + 7 * #50
        ld (hl),a

        ld bc,#7f03
        out (c),c
        ld a,#4c
        out (c),a

Sync    ld b,#f5
        in a,(c)
        rra
        jr nc,Sync + 2

        ei
        nop
        halt
        halt
        di

        ld b,90
        djnz $

        ld bc,#7f10
        out (c),c
        ld a,#4b
        out (c),a
        
        call PLY_AKY_Play
        
        ld bc,#7f54
        out (c),c

        jr Sync
