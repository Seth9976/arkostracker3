; New song, Song part, encoded in the AKM (minimalist) format V0.


	dw Newsong_InstrumentIndexes	; Index table for the Instruments.
	dw 0	; Index table for the Arpeggios.
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw Newsong_Subsong0

; The Instrument indexes.
Newsong_InstrumentIndexes
	dw Newsong_Instrument0

; The Instrument.
Newsong_Instrument0
	db 255	; Speed.

Newsong_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw Newsong_Instrument0Loop	; Loops.

Newsong_ArpeggioIndexes


Newsong_PitchIndexes


; New song, Subsong 0.
; ----------------------------------

Newsong_Subsong0
	dw Newsong_Subsong0_NoteIndexes	; Index table for the notes.
	dw Newsong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 0	; Most used instrument.
	db 0	; Second most used instrument.

	db 0	; Most used wait.
	db 0	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
Newsong_Subsong0_Loop
	db 170	; State byte.
	db 63	; New height.
	db 128	; New track (0) for channel 1, as a reference (index 0).
	db 128	; New track (0) for channel 2, as a reference (index 0).
	db 128	; New track (0) for channel 3, as a reference (index 0).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw Newsong_Subsong0_Loop

; The indexes of the tracks.
Newsong_Subsong0_TrackIndexes
	dw Newsong_Subsong0_Track0	; Track 0, index 0.

Newsong_Subsong0_Track0
	db 205	; New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
Newsong_Subsong0_NoteIndexes

