; New song, Song part, encoded in the AKM (minimalist) format V0.



	dw mySong_InstrumentIndexes	; Index table for the Instruments.
	dw 0	; Index table for the Arpeggios.
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw mySong_Subsong0

; The Instrument indexes.
mySong_InstrumentIndexes
	dw mySong_Instrument0
	dw mySong_Instrument1

; The Instrument.
mySong_Instrument0
	db 255	; Speed.

mySong_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loops.

mySong_Instrument1
	db 0	; Speed.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

; New song, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 0	; Second most used instrument.

	db 1	; Most used wait.
	db 3	; Second most used wait.

	db 48	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 4	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 31	; New height.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track0 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes

mySong_Subsong0_Track0
	db 141	; Secondary wait (3).
	db 159	; Primary instrument (1). Same escaped note: 48. Secondary wait (3).
	db 12	; Note with effects flag
	db 158	; Primary instrument (1). New escaped note: 49. Secondary wait (3).
	db 49	;   Escape note value.
	db 16	; Reset effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 158	; Primary instrument (1). New escaped note: 50. Secondary wait (3).
	db 50	;   Escape note value.
	db 32	; Reset effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (1).
	db 51	;   Escape note value.
	db 48	; Reset effect, with inverted volume: 3.
	db 93	; Primary wait (1).
	db 0	; Reset effect, with inverted volume: 0.
	db 158	; Primary instrument (1). New escaped note: 52. Secondary wait (3).
	db 52	;   Escape note value.
	db 12	; Note with effects flag
	db 94	; Primary instrument (1). New escaped note: 53. Primary wait (1).
	db 53	;   Escape note value.
	db 240	; Reset effect, with inverted volume: 15.
	db 93	; Primary wait (1).
	db 32	; Reset effect, with inverted volume: 2.
	db 94	; Primary instrument (1). New escaped note: 54. Primary wait (1).
	db 54	;   Escape note value.
	db 221	; New wait (127).
	db 127	;   Escape wait value.
	db 0	; Reset effect, with inverted volume: 0.

mySong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes

