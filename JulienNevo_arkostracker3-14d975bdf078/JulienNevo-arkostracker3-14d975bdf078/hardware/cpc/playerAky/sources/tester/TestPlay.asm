        ;RAW test to play a sample.
        
        buildsna
        bankset 0

;PLY_AKY_SAMPLE_BYTE_PER_FRAME = 160; 320
;PLY_AKY_NOPS_TO_WAIT = 80; 21

;Perfect values.
PLY_AKY_SAMPLE_BYTE_PER_FRAME = 320
PLY_AKY_NOPS_TO_WAIT = 24

PLY_AKY_SAMPLE_BYTE_PER_FRAME = 320
PLY_AKY_NOPS_TO_WAIT = 24


        org #100
Start:  equ $

        di
        ld hl,#c9fb
        ld (#38),hl

        ld hl,#c000
        ld de,#c001
        ld bc,#1000
        ld (hl),l
        ldir

        ld bc,#f407
        out (c),c
        ld bc,#f6c0
        out (c),c
        out (c),0
        ld bc,#f400 + %00111111
        out (c),c
        ld bc,#f680
        out (c),c
        out (c),0

        ld ix,MainSample_Sample2
        ld l,(ix + 0)
        ld h,(ix + 1)
        ld (PLY_AKY_SPL_Sample + 1),hl
        ld (PLY_AKY_SPL_SampleLoop + 1),hl
        ld l,(ix + 2)
        ld h,(ix + 3)
        ld (PLY_AKY_SPL_SampleEnd + 1),hl

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

;        ld b,251
;TEST
;        djnz TEST

        call PLY_AKY_SPL_PlaySample
    
        ld bc,#7f10
        out (c),c
        ld a,#54
        out (c),a

        jr Sync


PLY_AKY_SPL_PlaySample
PLY_AKY_SPL_Sample ld hl,0

PLY_AKY_SPL_SampleVolumeRegister ld a,8     ;8/9/10.
    ;Selects the sample channel.
    ld b,#f4
    out (c),a
    ld bc,#f6c0
    out (c),c
    out (c),0

    ;Main sample loop at 16khz.

    exx
        ld hl,#f4f6
    exx
    ld de,PLY_AKY_SAMPLE_BYTE_PER_FRAME
    ld c,0   ;C = Increasing decimal step.

PLY_AKY_SPL_PlaySampleLoop
    ld a,(hl)           ;Reads from the sample.
    exx
        ld b,h
        out (c),a       ;Sends the byte from HL.
        ld b,l
        out (c),a       ;#f680 (a trick, our sample value has its 7th bit to 1).
        out (c),0       ;#f600
    exx

    ;Moves forward in the sample.
    ld a,c
PLY_AKY_SPL_StepDecimal add a,#80
    ld c,a
    ld a,l
PLY_AKY_SPL_StepInteger adc a,#00
    ld l,a
    jr nc,.forwardNoCarry
    inc h
.forwardNoCarry

    dec de
    ld a,e
    or d
    jr z,PLY_AKY_SPL_PlaySampleEnd

    ;Wastes time to reach 16 khz somehow. The loop should last 64 nops.
    ds PLY_AKY_NOPS_TO_WAIT
;    ld a,6
;.wasteTime  dec a
;    jr nz,.wasteTime
;    nop
    jr PLY_AKY_SPL_PlaySampleLoop

PLY_AKY_SPL_PlaySampleEnd
    ex de,hl        ;DE = advanced pointer on the sample.
    ;Are we beyond the sample range?
PLY_AKY_SPL_SampleEnd ld hl,0
    or a
    sbc hl,de
    jr nc,PLY_AKY_SPL_SetNewSamplePt
    ;End sample ended. Loop? If not 0, loops.
PLY_AKY_SPL_SampleLoop ld de,0

PLY_AKY_SPL_SetNewSamplePt
    ld (PLY_AKY_SPL_Sample + 1),de

    ret






Music_Start:

        include "../resources/aaaSamples.asm"
Music_End:
