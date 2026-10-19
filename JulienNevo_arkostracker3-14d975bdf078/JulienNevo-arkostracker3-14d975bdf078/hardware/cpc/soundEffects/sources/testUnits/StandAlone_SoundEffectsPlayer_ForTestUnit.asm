        ;Used by Arkos Tracker 2 for testing the Stand alone sound effect player.

        ;NOTE: it has no ORG (added by the code that wants to use it) and no INCLUDE (does not work well with internal Rasm: the included source can be added just after).

Start:
        ;Defines hooks to be called conveniently from the Z80 emulator.

        ;Initializes the sound effects.
        ;IN:    HL must point on the table to the sound effects.
        call PLY_SE_InitSoundEffects            ;Start + 0
        ret                                     ;Start + 3

        ;Plays a sound effect (programs it, actually).
        ;IN:    A = Sound effect number (>0!).
        ;       C = The channel where to play the sound effect (0, 1, 2).
        ;       B = Inverted volume (0 = full volume, 16 = no sound). Hardware sounds are also lowered.
        call PLY_SE_PlaySoundEffect             ;Start + 4
        ret                                     ;Start + 7

        ;Plays the sound effect stream. This modifies the PSG registers.
        call PLY_SE_PlaySoundEffectsStream      ;Start + 8
        ret                                     ;Start + 11

        ;Stops a sound effect.
        ;IN:    A = The channel where to stop the sound effect (0, 1, 2).
        call PLY_SE_StopSoundEffectFromChannel  ;Start + 12
        ret                                     ;Start + 15
