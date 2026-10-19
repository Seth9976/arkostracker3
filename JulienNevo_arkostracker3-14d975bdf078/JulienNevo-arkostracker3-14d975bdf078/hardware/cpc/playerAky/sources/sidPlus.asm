
        buildsna
        bankset 0




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
        



VECTOR_ADDRESS equ #3f00

SAR0 equ #6c00          ;16 bit Source Address Register.
PPR0 equ #6c02          ;8 bit Pause Prescaler Register.
DCSR equ #6c0f          ;To set the DMAs on/off.


        org #8000
        ;limit #3f00
        run $

        di
        ld hl,#c9fb
        ld (#38),hl
        ld sp,0

        call UnlockAsic

        ld bc,#7fb8             ;ASIC in #4000, AND low rom!
        out (c),c

        ;ld hl,AYEmpty
        ;ld (SAR0),hl           ;SAR0: address of DMA 0 AY-list (16 bit Source Address Register).
        xor a
        ld (PPR0),a            ;PPR0: Pause unit (8 bit Pause Prescaler Register).
       ; ld de,Ay1
       ; ld (SAR0),de
        
        ;When DCSR has DMA, the AY-list starts immediately AFTER THE LAST STOP!
        ;ld a,%00000001          ;DMA 0 set!
        ;ld (DCSR),a            ;DCSR.

        ;ld bc,#7fa0             ;Closes the Asic and ROM.
        ;out (c),c
        
                ;Sets the new pointer.
        
        ;ld de,Ay1
        ;ld (SAR0),de
        ;ld a,%00000001          ;DMA 0 set! In case a STOP has been reached before, or after first init.
        ;ld (DCSR),a             ;DCSR.

        ;ld hl,TablePsgInit
        ld hl,TablePsgInitSyncBuzz
        call SetPsgs
        
        ;jr $



MainLoop
Sync    ld b,#f5
        in a,(c)
        rra
        jr nc,Sync

        ei
        nop
        halt
        halt
        di

WaitCounter ld hl,1
        dec hl
        ld a,l
        or h
        jr z,PtInstrs
        ld (WaitCounter + 1),hl
        jr EndFrame
        

PtInstrs ld hl,InstructionsTable
.pastRead ld e,(hl)             ;Reads the data pointer.
        inc hl
        ld d,(hl)
        inc hl
        ld a,e
        or d
        jr nz,.noLoop
        ld hl,InstructionsTable
        jr .pastRead
.noLoop
        ld (SAR0),de
        ;Sets the new pointer.
        ld a,%00000001          ;DMA 0 set! In case a STOP has been reached before, or after first init.
        ld (DCSR),a             ;DCSR.

        ld c,(hl)               ;Reads the wait.
        inc hl
        ld b,(hl)
        inc hl
        ld (WaitCounter + 1),bc
        ld e,(hl)               ;Reads the PSG data.
        inc hl
        ld d,(hl)
        inc hl
        ld (PtInstrs + 1),hl

        ex de,hl
        call SetPsgs

EndFrame

        jr MainLoop


UnlockAsic
        ld b,#bc
        ld hl,AsicUnlockTable
.loop   ld a,(hl)
        cp ASIC_UNLOCK_END_VALUE
        ret z

        out (c),a
        inc hl
        jr .loop





;       HL = table, ended by 255.
SetPsgs
        ld a,(hl)
        cp 255
        ret z
        ld d,a
        inc hl
        ld e,(hl)
        inc hl
        call SetPsg
        jr SetPsgs


;       D = register, E = value.
SetPsg
        ld b,#f4
        out (c),d
        ld bc,#f6c0
        out (c),c
        out (c),0
        ld b,#f4
        out (c),e
        ld bc,#f680
        out (c),c
        out (c),0
        ret



ASIC_UNLOCK_END_VALUE equ 1         ;Sentinel end value.
AsicUnlockTable db 255,0,255,119,179,81,168,212,98,57,156,70,43,21,138,205,238
        db ASIC_UNLOCK_END_VALUE




;TablePsgInit
;        db 9, 15
;        db 255

TablePsgInitSyncBuzz
        db 9, 16
        db 13, 8
        ;db 2, 0x78
        ;db 3, 0x7
        ;db 2, 0xf0
        ;db 3, 0xe
        
        ;db 2, 0xbc
        ;db 3, 0x3

        db 2, lo(956)
        db 3, hi(956)

        ;db 2, lo(478)
        ;db 3, hi(478)

        ;db 7, %00111101
        db 7, %00111101

        db 11, 60
        db 12, 0
        db 255

WAIT_DURATION equ 20000

InstructionsTable
        dw Ay1SyncBuzz, WAIT_DURATION, TablePsg1SyncBuzz
        ;dw Ay1, WAIT_DURATION, TablePsg1
        ;dw Ay2, WAIT_DURATION, TablePsg2
        dw 0


;TablePsg1
;        db 7, %00111111
;        db 2, 239
;        db 3, 0

;        db 255

TablePsg1SyncBuzz
       
        db 255

        ALIGN 2
Ay1SyncBuzz
        ;dw 13 * 256 + 1 ;Down and stay down
        ;dw 13 * 256 + 4 ;Down and stay down
        ;dw 13 * 256 + 8
        ;dw #1000 + 28                ;Pause.
        ;dw #1000 + 58                ;Pause.
        ;dw #1000 + 116                ;Pause.
        ;dw #1000 + 238                ;Pause.
        ;dw #1000 + 478                ;Pause.

        dw #2fff                ;Repeat max!

        REPEAT 10
        dw 13 * 256 + 1 ;Down and stay down
        dw #1000 + 29                ;Pause.
        REND

        REPEAT 10
        dw 13 * 256 + 1 ;Down and stay down
        dw #1000 + 59                ;Pause.
        REND
        
        REPEAT 10
        dw 13 * 256 + 1 ;Down and stay down
        dw #1000 + 119                ;Pause.
        REND






        ;dw 13 * 256 + 1 ;Down and stay down
        ;dw #1000 + 238                ;Pause.
        
        ;dw 13 * 256 + 1 ;Down and stay down
        ;dw #1000 + 239               ;Pause.
        ;dw 13 * 256 + 4 ;Down and stay down
        ;dw #1000 + 238                ;Pause.
        ;dw 13 * 256 + 1 ;Down and stay down
        ;dw #1000 + 239               ;Pause.
        ;dw 13 * 256 + 1 ;Down and stay down
        ;dw #1000 + 238               ;Pause.
        
        
        dw #4001                ;Loop!
        dw #4020                ;Stop

Ay1
        dw #2fff                ;Repeat max!
        dw #090f                ;Volume F, middle channel.
        dw #1000 + 29                ;Pause.
        dw #0900                ;Volume 0, middle channel.
        dw #1000 + 29 - 1                ;Pause.
        dw #4001                ;Loop!
        dw #4020                ;Stop



TablePsg2
        db 7, %00111101
        db 2, #1c               ;284
        db 3, #1
        db 255
        ALIGN 2
Ay2
        dw #2fff                ;Repeat max!
        dw #090f                ;Volume F, middle channel.
        dw #1000 + 35                ;Pause.
        dw #0900                ;Volume 0, middle channel.
        dw #1000 + 34 - 1                ;Pause.
        dw #4001                ;Loop!
        dw #4020                ;Stop






AYList0
           


        ;dw #0302
        ;dw #0201
        ;dw #0700 + %00111101
        ;dw #0900 + 15
        ;dw #4020                ;Stop


        dw #0700 + %00111111


        dw #2fff                ;Repeat max!
        dw #090f                ;Volume F, middle channel.
        dw #1005                ;Pause.
        ;dw #4000                ;Nop.
        ;dw #4000                ;Nop.
        ;dw #4000                ;Nop.
        ;dw #4000                ;Nop.
        ;dw #4000                ;Nop.
        dw #0900                ;Volume 0, middle channel.
        dw #1004                ;Pause.
        ;dw #4000                ;Nop.
        ;dw #4000                ;Nop.
        ;dw #4000                ;Nop.
        ;dw #4000                ;Nop.

        dw #4001                ;Loop!

        dw #4020                ;Stop
