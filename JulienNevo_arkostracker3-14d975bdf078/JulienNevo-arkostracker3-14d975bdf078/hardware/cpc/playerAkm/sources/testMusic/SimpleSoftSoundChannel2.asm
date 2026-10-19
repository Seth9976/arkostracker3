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

	db 0	; Most used wait.
	db 7	; Second most used wait.

	db 48	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 63	; New height.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track0 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes

mySong_Subsong0_Track0
	db 159	; Primary instrument (1). Same escaped note: 48. Secondary wait (7).
	db 222	; Primary instrument (1). New escaped note: 50. New wait (6).
	db 50	;   Escape note value.
	db 6	;   Escape wait value.
	db 222	; Primary instrument (1). New escaped note: 52. New wait (5).
	db 52	;   Escape note value.
	db 5	;   Escape wait value.
	db 222	; Primary instrument (1). New escaped note: 53. New wait (4).
	db 53	;   Escape note value.
	db 4	;   Escape wait value.
	db 222	; Primary instrument (1). New escaped note: 55. New wait (3).
	db 55	;   Escape note value.
	db 3	;   Escape wait value.
	db 222	; Primary instrument (1). New escaped note: 57. New wait (2).
	db 57	;   Escape note value.
	db 2	;   Escape wait value.
	db 222	; Primary instrument (1). New escaped note: 59. New wait (1).
	db 59	;   Escape note value.
	db 1	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 60. Primary wait (0).
	db 60	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 62. Primary wait (0).
	db 62	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 64. Primary wait (0).
	db 64	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (0).
	db 65	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 67. Primary wait (0).
	db 67	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 69. Primary wait (0).
	db 69	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 71. Primary wait (0).
	db 71	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 72. New wait (127).
	db 72	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes

