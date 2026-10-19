
        buildsna
        bankset 0

        org #100

        di
        ld hl,#c9fb
        ld (#38),hl
        ld sp,#38

        ld hl,Music
        call PLY_MOD_Init

MainLoop:
        ld bc,#7f10
        out (c),c
        ld a,#4b
        out (c),a

        call PLY_MOD_Play

        ld bc,#7f10
        out (c),c
        ld a,#54
        out (c),a

        jr MainLoop

Player:
        include "PlayerMod_CPC.asm"

        ;display "Size of player: ", /H, ($ - Player)
Music:
        ;include "resources/SimpleModAt3.asm"
        ;include "resources/ShowThem.asm"
        ;include "resources/OneNote.asm"
        include "resources/Castle.asm"
        ;include "resources/Simple.asm"

        print "End: ", {hex}$
