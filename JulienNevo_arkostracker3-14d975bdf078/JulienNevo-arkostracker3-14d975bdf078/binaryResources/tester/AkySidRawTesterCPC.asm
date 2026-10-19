        ;Tests the AKY SID player, for Amstrad CPC (old) to be used for an QUICK TESTING EXPORT.
        ;It does NOT include anything.
        ;It does NOT has a start address.

        ;Requires Rasm >= 3.0.8!

        ;MusicStart must be set.
        ;PlayerAkySidMacros_CPC is copy/paste inside.



PLY_AKY_SID_MICROCODE_DURATION equ 21
PLY_AKY_SID_DURATION_TIMER_CODE equ PLY_AKY_SID_MICROCODE_DURATION + 7              ;+7 for the LD IX,return and RET.



        ;Waits for "nopCount" NOPs, using various opcodes.
        ;WARNING, flags may be changed!
        MACRO AKY_SID_WAIT_NOPS nopCount
                IF {nopCount} < 0
                        FAIL "Negative nop count!"
                ENDIF

                localNop = {nopCount}

                WHILE localNop > 0
                        ; ********** These are too dangerous, depending on HL!!!!
                        ;IF localNop >= 12
                        ;        ex (sp),hl
                        ;        ex (sp),hl
                        ;        localNop = localNop - 12
                        ;ELSEIF localNop >= 6
                        ;        inc (hl)
                        ;        dec (hl)
                        ;        localNop = localNop - 6
                        IF localNop >= 5
                                cp (ix)
                                localNop = localNop - 5
                        ELSEIF localNop >= 3
                                jr $ + 2
                                localNop = localNop - 3
                        ELSEIF localNop >= 2
                                cp (hl)
                                localNop = localNop - 2
                        ELSE
                                nop
                                localNop = localNop - 1
                        ENDIF
                WEND
        ENDM


        ;Waits for 64-"pastNops" NOPs, and call the Timer Code via RET.
        ;IX is automatically set after the declaration of the macro.
        MACRO AKY_SID_WAIT_AND_CALL_TIMER_CODE pastNops
                IF {pastNops} < 3
                        FAIL "A bit low to wait. Normal?", {pastNops}
                ELSEIF {pastNops} > (64 - PLY_AKY_SID_DURATION_TIMER_CODE)
                        FAIL "Waited too much!", {pastNops}
                ENDIF

                AKY_SID_WAIT_NOPS 64 - PLY_AKY_SID_DURATION_TIMER_CODE - {pastNops}

                ld iy,$ + 4 + 1         ;Skips the ld and ret.
                ret
        ENDM

        ;Waits for 64-"pastNops" NOP, and call the Timer Code via RET.
        ;IX is automatically set to the given return address.
        MACRO AKY_SID_WAIT_AND_CALL_TIMER_CODE_AND_JUMP_TO returnAddress, pastNops
                IF {pastNops} < 3
                        FAIL "A bit low to wait. Normal?", {v}
                ELSEIF {pastNops} > (64 - PLY_AKY_SID_DURATION_TIMER_CODE)
                        FAIL "Waited too much!", {pastNops}
                ENDIF

                AKY_SID_WAIT_NOPS 64 - PLY_AKY_SID_DURATION_TIMER_CODE - {pastNops}

                ld iy,{returnAddress}
                ret
        ENDM




PLY_AKYsid_RET_TABLES   equ #a000               ;Can be put anywhere. See PLY_AKYsid_RET_TABLES_END in the player about where it ends.

Start   equ $

        di

        ld hl,#c9fb
        ld (#38),hl
        ld sp,$

        ld bc,#bc01
        out (c),c
        ld bc,#bd00
        out (c),c

        ;Initializes the music.
        ld hl,MusicStart
        ld de,PlayReturn
        call PLY_AKYsid_Init

        ;First accurate synchronization, we will then bypass all VSync, everything is cycle-accurate!
Sync    ld b,#f5
        in a,(c)
        rra
        jr nc,Sync + 2
Sync2
        in a,(c)
        rra
        jr c,Sync2

        ;Waits. Change this according to where you want to have your effect visible.
        ei
        nop
        halt
        halt
        halt
        halt
        halt
        ld bc,270
.wait   dec bc
        ld a,b
        or c
        jr nz,.wait

        di

        ld bc,#7f10
        out (c),c
        ld a,#4b
        out (c),a

        ;Calls the player, using JP, NOT call!
                ld sp,PLY_AKYsid_RET_TABLES
                ld hl,0 * 256 + #f6                  ;H' is the line counter.
        exx
        jp PLY_AKYsid_Play
PlayReturn
        ;Nops: 3.

        ;The player has finished. Here you can perform your effects while still being perfectly synced (good luck!).
        ;The trick is to call the SID code every 36 nops *at worst*.
        ;Please read CAREFULLY the notes in the player. Doing SID is very tricky.

        ;H' contains how many lines were accounted for during the player.
        ;Now waits till we have reached a certain line, this is useful if you want to synchronize an effect,
        ;but you may only want to reach 312 (the end of the frame) and loop again, if you've got nothing else to do.
        ;But as an example, we'll wait till the maximum player duration, so that we can synchronize an effect
        ;(this is what I did in the "Signal In Disarray" demo).
        exx
            ld a,h
        exx
        ld e,a
        ld d,0
;This is the maximum the player can reach... with a safety margin. Other songs may take longer, or shorter.
;Decrease this as much as you can, but if the program freezes, it means it is too low!
WAIT_LINE_COUNT = 80 ;72
        ld hl,WAIT_LINE_COUNT
        or a
        sbc hl,de

        ;This macro waits for a specific NOP count. Write here how many NOPs were *spent*,
        ;and it will wait for the right amount before calling the SID code.
        ;After this, your NOP count is 0.
        ;You can use the COUNTNOPS mnemonic of Rasm to help you count how many cycles are spent
        ;(check the numerous use in the player).
        AKY_SID_WAIT_AND_CALL_TIMER_CODE (17)

StabilizationLoop
        dec hl
        ld a,l
        or h
        jr z,WaitEndOfFrame

        ld bc,#7f55
        out (c),c
        ld c,#4c
        out (c),c

        ;This macro waits to reach a specific NOP count. Write here how many NOPs were *spent*,
        ;and it will wait for the right amount before calling the SID code.
        ;THEN, it will jump to the indicated address, where you know your NOP count is 0.
        AKY_SID_WAIT_AND_CALL_TIMER_CODE_AND_JUMP_TO StabilizationLoop, (6 + 13)

        ;Now waits for the end of the frame.
        ;You could also manage your line-accurate effect here.
WaitEndOfFrame
                ;Nops: 7

        ld hl,312 - WAIT_LINE_COUNT
        AKY_SID_WAIT_AND_CALL_TIMER_CODE (7 + 3)        ;The "7" wraps the code in StabilizationLoop above.

LineLoop
        dec hl
        ld a,l
        or h
        jr z,MainLoopEnd

        ;Some rasters to check the synchronization. If you remove them, remove the "+13" below.
        ld bc,#7f55
        out (c),c
        ld c,#44
        out (c),c

        AKY_SID_WAIT_AND_CALL_TIMER_CODE_AND_JUMP_TO LineLoop, (6 + 13)

MainLoopEnd
        exx
            ld h,0                  ;Resets the line counter.
        exx

        ;Some rasters to check the synchronization. If you remove them, remove the "+7" below.
        ld bc,#7f5c
        out (c),c

        AKY_SID_WAIT_AND_CALL_TIMER_CODE_AND_JUMP_TO PLY_AKYsid_Play, (11 + 7)


