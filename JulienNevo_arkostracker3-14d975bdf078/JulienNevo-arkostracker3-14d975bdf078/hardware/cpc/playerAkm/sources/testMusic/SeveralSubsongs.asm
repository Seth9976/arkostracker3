; New song, Song part, encoded in the AKM (minimalist) format V0.


	dw mySong_InstrumentIndexes	; Index table for the Instruments.
	dw 0	; Index table for the Arpeggios.
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw mySong_Subsong0
	dw mySong_Subsong1
	dw mySong_Subsong2

; The Instrument indexes.
mySong_InstrumentIndexes
	dw mySong_Instrument0
	dw mySong_Instrument1
	dw mySong_Instrument2
	dw mySong_Instrument3

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

mySong_Instrument2
	db 0	; Speed.

	db 61	; Volume: 15.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument3
	db 0	; Speed.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

mySong_Instrument3Loop	db 45	; Volume: 11.

	db 4	; End the instrument.
	dw mySong_Instrument3Loop	; Loops.

mySong_ArpeggioIndexes


mySong_PitchIndexes


; New song, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 2	; Most used instrument.
	db 1	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

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
	db 160	; Secondary instrument (1). Note reference (0). Secondary wait (1).
	db 160	; Secondary instrument (1). Note reference (0). Secondary wait (1).
	db 160	; Secondary instrument (1). Note reference (0). Secondary wait (1).
	db 161	; Secondary instrument (1). Note reference (1). Secondary wait (1).
	db 238	; Secondary instrument (1). New escaped note: 52. New wait (3).
	db 52	;   Escape note value.
	db 3	;   Escape wait value.
	db 33	; Secondary instrument (1). Note reference (1). 
	db 160	; Secondary instrument (1). Note reference (0). Secondary wait (1).
	db 175	; Secondary instrument (1). Same escaped note: 52. Secondary wait (1).
	db 161	; Secondary instrument (1). Note reference (1). Secondary wait (1).
	db 161	; Secondary instrument (1). Note reference (1). Secondary wait (1).
	db 224	; Secondary instrument (1). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 48	; Note for index 0.
	db 50	; Note for index 1.

; New song, Subsong 1.
; ----------------------------------

mySong_Subsong1
	dw mySong_Subsong1_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong1_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 2	; Most used instrument.
	db 1	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 52	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong1_Loop
	db 254	; State byte.
	db 31	; New height.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong1_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong1_Track0 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong1_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong1_Track1 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong1_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong1_Track0 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong1_Loop

; The indexes of the tracks.
mySong_Subsong1_TrackIndexes

mySong_Subsong1_Track0
	db 205	; New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong1_Track1
	db 159	; Primary instrument (2). Same escaped note: 52. Secondary wait (1).
	db 159	; Primary instrument (2). Same escaped note: 52. Secondary wait (1).
	db 159	; Primary instrument (2). Same escaped note: 52. Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 54. Secondary wait (1).
	db 54	;   Escape note value.
	db 222	; Primary instrument (2). New escaped note: 56. New wait (3).
	db 56	;   Escape note value.
	db 3	;   Escape wait value.
	db 30	; Primary instrument (2). New escaped note: 54. 
	db 54	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 52. Secondary wait (1).
	db 52	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 56. Secondary wait (1).
	db 56	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 54. Secondary wait (1).
	db 54	;   Escape note value.
	db 159	; Primary instrument (2). Same escaped note: 54. Secondary wait (1).
	db 222	; Primary instrument (2). New escaped note: 52. New wait (127).
	db 52	;   Escape note value.
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong1_NoteIndexes
	db 48	; Note for index 0.
	db 50	; Note for index 1.

; New song, Subsong 2.
; ----------------------------------

mySong_Subsong2
	dw mySong_Subsong2_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong2_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 2	; Most used instrument.
	db 1	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 0	; Default start note in tracks.
	db 3	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong2_Loop
	db 254	; State byte.
	db 63	; New height.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong2_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong2_Track0 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong2_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong2_Track0 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong2_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong2_Track1 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong2_Loop

; The indexes of the tracks.
mySong_Subsong2_TrackIndexes

mySong_Subsong2_Track0
	db 205	; New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong2_Track1
	db 128	; Note reference (0). Secondary wait (1).
	db 129	; Note reference (1). Secondary wait (1).
	db 142	; New escaped note: 52. Secondary wait (1).
	db 52	;   Escape note value.
	db 142	; New escaped note: 53. Secondary wait (1).
	db 53	;   Escape note value.
	db 142	; New escaped note: 55. Secondary wait (1).
	db 55	;   Escape note value.
	db 142	; New escaped note: 53. Secondary wait (1).
	db 53	;   Escape note value.
	db 142	; New escaped note: 52. Secondary wait (1).
	db 52	;   Escape note value.
	db 129	; Note reference (1). Secondary wait (1).
	db 208	; Primary instrument (2). Note reference (0). New wait (3).
	db 3	;   Escape wait value.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 36. Primary wait (0).
	db 36	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 36. Primary wait (0).
	db 208	; Primary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong2_NoteIndexes
	db 48	; Note for index 0.
	db 50	; Note for index 1.

