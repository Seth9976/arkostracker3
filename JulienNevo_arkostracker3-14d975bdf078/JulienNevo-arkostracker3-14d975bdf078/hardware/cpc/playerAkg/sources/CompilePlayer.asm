        ;Compiles the player and the music, using RASM.
        
        org #4041          ;Compile NOT in 0 to avoid possible clashes, "ld hl,0" -> "ld hl,start" type, cleaner. Disark will have to be given this address, though.
        
        ;This is the player. A "player config" file is added to compile only what is necessary for THIS song.
        ;include "Music_AHarmlessGrenade_playerconfig.asm"
        include "PlayerAkg.asm"
       