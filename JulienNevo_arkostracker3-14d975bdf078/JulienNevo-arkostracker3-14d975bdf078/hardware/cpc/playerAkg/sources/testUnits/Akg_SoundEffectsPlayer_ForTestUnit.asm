        ;Used by Arkos Tracker 2 for testing the sound effect player for the AKG player.
        ;Uses the AKG sound effect and makes sure the result is put at specific address for easy access by the Z80 emulator.

        ;This is a generic solution for testing the sound effect, so it can be used in any test unit.

        ;NOTE: it has no ORG (added by the code that wants to use it) and no INCLUDE (does not work well with internal Rasm: the included source can be added just after).

;This is where the registers will be encoded.
;We don't start at 0, if was afraid of the "0 - 1 + 1" behavior.
PLY_AKG_PSGReg01_Instr:          equ #10 - 1     ;-1 because there is a +1 to skip the instruction.
PLY_AKG_PSGReg23_Instr:          equ #12 - 1
PLY_AKG_PSGReg45_Instr:          equ #14 - 1
PLY_AKG_PSGReg6:                 equ #16
PLY_AKG_MixerRegister:           equ #17
PLY_AKG_PSGReg8:                 equ #18
PLY_AKG_PSGReg9:                 equ #19
PLY_AKG_PSGReg10:                equ #1a
PLY_AKG_PSGHardwarePeriod_Instr: equ #1b - 1     ;-1 because there is a +1 to skip the instruction.
PLY_AKG_PSGReg13_Instr:          equ #1d - 1     ;Idem.
PLY_AKG_PSGReg13_OldValue:       equ #1e - 1     ;Idem.



Start:
        ;Defines hooks to be called conveniently from the Z80 emulator.

        ;Initializes the sound effects.
        ;IN:    HL must point on the table to the sound effects.
        call PLY_AKG_InitSoundEffects            ;Start + 0
        ret                                     ;Start + 3

        ;Plays a sound effect (programs it, actually).
        ;IN:    A = Sound effect number (>0!).
        ;       C = The channel where to play the sound effect (0, 1, 2).
        ;       B = Inverted volume (0 = full volume, 16 = no sound). Hardware sounds are also lowered.
        call PLY_AKG_PlaySoundEffect            ;Start + 4
        ret                                     ;Start + 7

        ;Plays the sound effect stream. This modified the PSG registers (sort of, see the constants above).
        ;IN:    A = R7.
        call PLY_AKG_PlaySoundEffectsStream     ;Start + 8
        ld (PLY_AKG_MixerRegister),a            ;Start + 11
        ret                                     ;Start + 14

        ;Stops a sound effect.
        ;IN:    A = The channel where to stop the sound effect (0, 1, 2).
        call PLY_AKG_StopSoundEffectFromChannel ;Start + 12
        ret                                     ;Start + 15


		;include "../PlayerAkg_SoundEffects.asm"		;Only for testing outside C++ test units.