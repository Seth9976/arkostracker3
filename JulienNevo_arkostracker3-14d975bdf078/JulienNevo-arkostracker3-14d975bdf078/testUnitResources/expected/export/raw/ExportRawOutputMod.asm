	org 256

; Header
	db 0	; Flag byte 1.
	db 0	; Flag byte 2.

; Linker
MySong_Subsong0_Linker:
MySong_Subsong0_Loop:	; Pattern 0.
	dw MySong_Subsong0_Track0, MySong_Subsong0_Track1, MySong_Subsong0_Track2

	dw 0, MySong_Subsong0_Loop	; End of Linker, with the loop.

; Tracks
MySong_Subsong0_Track0:
	db 48	; Note.
	db 1	; Instrument.

	db 50	; Note.
	db 1	; Instrument.

	db 128	; 1 empty cells.

	db 52	; Note.
	db 1	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 53	; Note.
	db 1	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 55	; Note.
	db 1	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 57	; Note.
	db 1	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 59	; Note.
	db 1	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 60	; Note.
	db 1	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

MySong_Subsong0_Track1:
	db 36	; Note.
	db 2	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 120	; No note.
	db 0	; No instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 38	; Note.
	db 2	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 53	; Note.
	db 3	; Instrument.

	db 128	; 1 empty cells.

	db 55	; Note.
	db -1	; Instrument.

	db 128	; 1 empty cells.

	db 57	; Note.
	db -1	; Instrument.

	db 128	; 1 empty cells.

	db 59	; Note.
	db -1	; Instrument.

	db 128	; 1 empty cells.

	db 60	; Note.
	db -1	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

MySong_Subsong0_Track2:
	db 48	; Note.
	db 0	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 48	; Note.
	db 5	; Instrument.

	db 48	; Note.
	db 5	; Instrument.

	db 48	; Note.
	db 5	; Instrument.

	db 48	; Note.
	db 5	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

	db 48	; Note.
	db 4	; Instrument.

	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.
	db 128	; 1 empty cells.

