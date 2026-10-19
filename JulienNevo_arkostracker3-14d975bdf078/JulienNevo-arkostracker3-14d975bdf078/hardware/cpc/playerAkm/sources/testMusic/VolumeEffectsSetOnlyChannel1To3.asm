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

mySong_Instrument1Loop	db 49	; Volume: 12.

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

	db 2	; Most used wait.
	db 1	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 33	; New height.
	db 0	; New transposition on channel 1.
	db 129	; New track (0) for channel 1, as a reference (index 1).
	db 0	; New transposition on channel 2.
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 1
	db 40	; State byte.
	db 128	; New track (1) for channel 1, as a reference (index 0).
	db 129	; New track (0) for channel 2, as a reference (index 1).

; Pattern 2
	db 160	; State byte.
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 129	; New track (0) for channel 3, as a reference (index 1).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes
	dw mySong_Subsong0_Track1	; Track 1, index 0.
	dw mySong_Subsong0_Track0	; Track 0, index 1.

mySong_Subsong0_Track0
	db 80	; Primary instrument (1). Note reference (0). Primary wait (2).
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (2).
	db 18	; Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (2).
	db 34	; Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (2).
	db 50	; Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (1).
	db 66	; Volume effect, with inverted volume: 4.
	db 157	; Secondary wait (1).
	db 2	; Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (1).
	db 82	; Volume effect, with inverted volume: 5.
	db 157	; Secondary wait (1).
	db 2	; Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (2).
	db 130	; Volume effect, with inverted volume: 8.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (2).
	db 194	; Volume effect, with inverted volume: 12.
	db 12	; Note with effects flag
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (1).
	db 226	; Volume effect, with inverted volume: 14.
	db 29
	db 2	; Volume effect, with inverted volume: 0.
	db 29
	db 98	; Volume effect, with inverted volume: 6.
	db 29
	db 2	; Volume effect, with inverted volume: 0.
	db 221	; New wait (127).
	db 127	;   Escape wait value.
	db 242	; Volume effect, with inverted volume: 15.

mySong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 60	; Note for index 0.

