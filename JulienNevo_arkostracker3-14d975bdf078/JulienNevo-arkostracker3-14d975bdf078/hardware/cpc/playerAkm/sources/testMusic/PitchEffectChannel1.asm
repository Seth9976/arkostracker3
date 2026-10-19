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

mySong_Instrument1Loop	db 41	; Volume: 10.

	db 4	; End the instrument.
	dw mySong_Instrument1Loop	; Loops.

; New song, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 0	; Second most used instrument.

	db 1	; Most used wait.
	db 10	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 75	; New height.
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
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 221	; New wait (7).
	db 7	;   Escape wait value.
	db 244	; Pitch up: 16.
	db 16	; Pitch, LSB.
	db 128	; Pitch, MSB.
	db 157	; Secondary wait (10).
	db 244	; Pitch up: 272.
	db 16	; Pitch, LSB.
	db 129	; Pitch, MSB.
	db 94	; Primary instrument (1). New escaped note: 24. Primary wait (1).
	db 24	;   Escape note value.
	db 221	; New wait (4).
	db 4	;   Escape wait value.
	db 244	; Pitch up: 4352.
	db 0	; Pitch, LSB.
	db 145	; Pitch, MSB.
	db 221	; New wait (2).
	db 2	;   Escape wait value.
	db 244	; Pitch up: 512.
	db 0	; Pitch, LSB.
	db 130	; Pitch, MSB.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 157	; Secondary wait (10).
	db 244	; Pitch down: 16.
	db 16	; Pitch, LSB.
	db 0	; Pitch, MSB.
	db 157	; Secondary wait (10).
	db 244	; Pitch down: 272.
	db 16	; Pitch, LSB.
	db 1	; Pitch, MSB.
	db 94	; Primary instrument (1). New escaped note: 72. Primary wait (1).
	db 72	;   Escape note value.
	db 221	; New wait (3).
	db 3	;   Escape wait value.
	db 244	; Pitch down: 4352.
	db 0	; Pitch, LSB.
	db 17	; Pitch, MSB.
	db 157	; Secondary wait (10).
	db 244	; Pitch down: 256.
	db 0	; Pitch, LSB.
	db 1	; Pitch, MSB.
	db 224	; Secondary instrument (0). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 48	; Note for index 0.

