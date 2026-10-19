        ;Tests the AKG player, for the AMSTRAD CPC, to be used for an QUICK TESTING EXPORT.
        ;It does NOT include anything.
        ;It does NOT has a start address.

        ;MusicStart must be set.

        di
        ld hl,#c9fb
        ld (#38),hl
        ld sp,$

        ld hl,MusicStart
        xor a                   ;Subsong 0.
        call PLY_AKG_Init

        ;Some dots on the screen to judge how much CPU takes the player.
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

        ;Calls the player, shows some colors to see the consumed CPU.
        ld bc,#7f10
        out (c),c
        ld a,#4b
        out (c),a

        call PLY_AKG_Play

        ld bc,#7f54
        out (c),c

        jr Sync
