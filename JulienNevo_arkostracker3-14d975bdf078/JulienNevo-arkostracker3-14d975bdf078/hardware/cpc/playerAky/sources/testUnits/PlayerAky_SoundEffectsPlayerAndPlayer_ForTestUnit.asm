        ;Used by Arkos Tracker 2 for testing the sound effect player, but also with the real AKY player
        ;to emulate the full result.
        
        ;So, it is expected that the two files (sound effect player, lightweight player) are "stuck" just after.
        ;Don't forget to comment the include from the lightweight player, Rasm will not accept it.
        
        ;NOTE: it has no ORG (added by the code that wants to use it) and no INCLUDE (does not work well with internal Rasm: the included source can be added just after).
        
        ;The hooks have no RET after each calls. Not needed, because we test the addresses to stop the emulation.

Start:
        ;Defines hooks to be called conveniently from the Z80 emulator.
        
        ;IMPORTANT: enables the sound effects in the player. This must be declared BEFORE the player itself.
        PLY_AKY_MANAGE_SOUND_EFFECTS = 1
        ;If sound effects, the PSG number where to play SFX must be declared (>=1).
        PLY_AKY_SFX_PSG_NUMBER = 1
        
        ;Initializes the sound effects.
        ;IN:    HL must point on the table to the sound effects.
        call PLY_AKY_InitSoundEffects            ;Start + 0
        
        ;Plays a sound effect (programs it, actually).
        ;IN:    A = Sound effect number (>0!).
        ;       C = The channel where to play the sound effect (0, 1, 2).
        ;       B = Inverted volume (0 = full volume, 16 = no sound). Hardware sounds are also lowered.
        call PLY_AKY_PlaySoundEffect             ;Start + 3
        
        
        ;--------------------------------------
        ;Initializes the music player.
        ;IN:    HL = Address of the song.
        ;       A = Index of the subsong to play (>=0).
        call PLY_AKY_Init			;Start + 6
        
        ;Plays one frame of the song. It MUST have been initialized before.
        call PLY_AKY_Play			;Start + 9
