        ;Tests the MOD player, for the AMSTRAD CPC old, to be used for an QUICK TESTING EXPORT.
        ;It does NOT include anything.
        ;It does NOT has a start address.

        ;MusicStart must be set.

        di
        ld hl,#c9fb
        ld (#38),hl
        ld sp,$

        ld hl,MusicStart
        call PLY_MOD_Init

        ld bc,#7f10
        out (c),c
MainLoop
        ld bc,#7f4b
        out (c),c

        call PLY_MOD_Play

        ld bc,#7f54
        out (c),c

        jr MainLoop
