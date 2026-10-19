; New song, Song part, encoded in the AKM (minimalist) format V0.


	dw mySong_InstrumentIndexes	; Index table for the Instruments.
	dw 0	; Index table for the Arpeggios.
	dw mySong_PitchIndexes - 2	; Index table for the Pitches.

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

mySong_ArpeggioIndexes


mySong_PitchIndexes
	dw mySong_Pitch1

mySong_Pitch1
	db 0	; Speed

	db 32	; Value: 16
	db 18	; Value: 9
	db 16	; Value: 8
	db 14	; Value: 7
	db 12	; Value: 6
	db 10	; Value: 5
	db 8	; Value: 4
	db 6	; Value: 3
	db 4	; Value: 2
	db 2	; Value: 1
	db 0	; Value: 0
	db 10 * 2 + 1	; Loops to index 10.

; New song, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 0	; Second most used instrument.

	db 1	; Most used wait.
	db 2	; Second most used wait.

	db 60	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 255	; State byte.
	db 32	; New speed (>0).
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
	db 12	; Note with effects flag
	db 95	; Primary instrument (1). Same escaped note: 60. Primary wait (1).
	db 24	;    Pitch table effect 1.
	db 94	; Primary instrument (1). New escaped note: 62. Primary wait (1).
	db 62	;   Escape note value.
	db 12	; Note with effects flag
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (2).
	db 110	;    Force pitch speed effect 6.
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (2).
	db 12	; Note with effects flag
	db 209	; Primary instrument (1). Note reference (1). New wait (3).
	db 3	;   Escape wait value.
	db 78	;    Force pitch speed effect 4.
	db 93	; Effect only. Primary wait (1).
	db 24	;    Pitch table effect 1.
	db 96	; Secondary instrument (0). Note reference (0). Primary wait (1).
	db 12	; Note with effects flag
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (2).
	db 25	;    Pitch table effect 1.
	db 110	;    Force pitch speed effect 6.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 221	; Effect only. New wait (0).
	db 0	;   Escape wait value.
	db 24	;    Pitch table effect 1.
	db 93	; Effect only. Primary wait (1).
	db 25	;    Pitch table effect 1.
	db 46	;    Force pitch speed effect 2.
	db 157	; Effect only. Secondary wait (2).
	db 25	;    Pitch table effect 1.
	db 94	;    Force pitch speed effect 5.
	db 224	; Secondary instrument (0). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 48	; Note for index 0.
	db 67	; Note for index 1.

