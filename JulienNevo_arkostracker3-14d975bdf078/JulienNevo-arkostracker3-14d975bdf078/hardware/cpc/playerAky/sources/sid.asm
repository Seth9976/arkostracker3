        ;Raw SID test.


        ;dw 3822,3608,3405,3214,3034,2863,2703,2551,2408,2273,2145,2025                  ; Octave 0
        ;dw 1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012                  ; Octave 1
        ;dw 956,902,851,804,758,716,676,638,602,568,536,506                              ; Octave 2
        ;dw 478,451,426,402,379,358,338,319,301,284,268,253                              ; Octave 3
        ;dw 239,225,213,201,190,179,169,159,150,142,134,127                              ; Octave 4
        ;dw 119,113,106,100,95,89,84,80,75,71,67,63                                      ; Octave 5
        ;dw 60,56,53,50,47,45,42,40,38,36,34,32                                          ; Octave 6
        ;dw 30,28,27,25,24,22,21,20,19,18,17,16                                          ; Octave 7
        ;dw 15,14,13,13,12,11,11,10,9,9,8,8                                              ; Octave 8
        ;dw 7,7,7,6,6,6,5,5,5,4,4,4                                                      ; Octave 9
        ;dw 4,4,3,3,3,3,3,2 ;,2,2,2,2                                                    ; Octave 10
        

        buildsna
        bankset 0

        org #1000
        run $

        di
        ld hl,#c9fb
        ld (#38),hl

        ld de,PERIOD
        ;ld de,284             ;284 (#11c) = LA 220.               + 1 to have a nice desync. How to automatize that??
        ;ld de,239               ;#ef  ;C-4
        ;ld de,#be               ;190 = E-4
        ;ld de,142 + 1               ; 142 = LA 440
        ;ld de,71               ; 71 = LA 880

        ld h,#00
        ld l,e
        call SendPsg
        ld h,#01
        ld l,d
        call SendPsg

        ld hl,#0700 + %00111110
        ;ld hl,#0700 + %00111111
        call SendPsg

        ;Hardware env.
        ld hl,#0b24
        call SendPsg
        ld hl,#0c00
        call SendPsg
        ld hl,#0d08
        call SendPsg


        ld hl,#080f             ;Must be last.
        call SendPsg

        ld bc,#7f10
        out (c),c

        ld de,#f4f6
        ld c,#80

        ;jr $


        ld sp,RetTable : ret


;Test without RET table, but with calculation.


                ld de,#f4f6
                ld c,#80
        exx

        ld hl,0         ;Current addition.
        ;ld de,#0735 - 25     ;Step.
        ;ld de,#0736     ;Step.
        ld de,#0e6c + 59     ;Step.
        ld bc,#0f00     ;Two volumes to exchange.

        ld ix,MainLoop
MainLoop
;BRK1
        add hl,de
        jp nc,.noDeb
        ld a,b
        ld b,c
        ld c,a
        jr .afterAddition
.noDeb  ds 6,0
.afterAddition

        ld a,b
        exx
                ld b,d
                out (c),a
                ld b,e
                out (c),c
                out (c),0

                ld b,#7f
                ld a,#4b
                out (c),a
                ld a,#55
                out (c),a
        exx

        ds 64 - 45, 0

        jp (ix)






Code2End
        ld sp,RetTable
        jp Code2Real

Code1
        ds 3 + 3,0

        ld a,#f

        ld b,d
        out (c),a
        ld b,e
        out (c),c
        out (c),0

        ld b,#7f
        ld a,#55
        out (c),a
        ds 64-17 - 16,0
        ret

Code2
        ds 3 + 3,0
Code2Real
        ld a,#0                 ;**** FIXME TEST

        ld b,d
        out (c),a
        ld b,e
        out (c),c
        out (c),0

        ld b,#7f
        ld a,#4c
        out (c),a
        ds 64-17 - 16,0
        ret

RetTable
;period         -> /8 !!
;#11c (284)     -> 36 / 35. Perfect sync.       284 / 2 / 2 = 71, no carry. THEN 71 / 2 = 35 for count1, 36 for count2 because of Carry.
;#ef (239)      -> 30 / 30
;#be (190)      -> 24 / 24
;142            -> 18 / 18
;71             -> 9 / 9
;PERIOD = 284
;COUNT = 36
;COUNT2 = 35

PERIOD = 239
COUNT = 30
COUNT2 = 30

;PERIOD = 95
;COUNT = 12
;COUNT2 = 12

;PERIOD = 190
;COUNT = 24
;COUNT2 = 24

;PERIOD = 142
;COUNT = 18
;COUNT2 = 18


        REPEAT COUNT
                dw Code1
        REND
        REPEAT COUNT2 - 1
                dw Code2
        REND
        dw Code2End





;Sends a value to a PSG register.
;IN:    H = register
;       L = value
;MOD:   BC.
SendPsg
        ld b,#f4
        out (c),h       ;f400 + register.
        ld bc,#f6c0
        out (c),c       ;f6c0.
        out (c),0       ;f600.
        ld b,#f4
        out (c),l       ;f400 + value.
        ld bc,#f680
        out (c),c       ;f680
        out (c),0       ;f600.
        ret