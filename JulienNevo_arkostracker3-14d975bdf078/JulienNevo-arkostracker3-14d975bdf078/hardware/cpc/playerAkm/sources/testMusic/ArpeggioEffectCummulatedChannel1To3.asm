; New song, Song part, encoded in the AKM (minimalist) format V0.


	dw Newsong_InstrumentIndexes	; Index table for the Instruments.
	dw Newsong_ArpeggioIndexes - 2	; Index table for the Arpeggios.
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw Newsong_Subsong0

; The Instrument indexes.
Newsong_InstrumentIndexes
	dw Newsong_Instrument0
	dw Newsong_Instrument1
	dw Newsong_Instrument2

; The Instrument.
Newsong_Instrument0
	db 255	; Speed.

Newsong_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw Newsong_Instrument0Loop	; Loops.

Newsong_Instrument1
	db 0	; Speed.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

Newsong_Instrument1Loop	db 41	; Volume: 10.

	db 4	; End the instrument.
	dw Newsong_Instrument1Loop	; Loops.

Newsong_Instrument2
	db 0	; Speed.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 185	; Volume: 14.
	db 232	; Arpeggio: -12.

	db 53	; Volume: 13.

	db 177	; Volume: 12.
	db 48	; Arpeggio: 24.

	db 45	; Volume: 11.

Newsong_Instrument2Loop	db 169	; Volume: 10.
	db 24	; Arpeggio: 12.

	db 169	; Volume: 10.
	db 232	; Arpeggio: -12.

	db 41	; Volume: 10.

	db 169	; Volume: 10.
	db 48	; Arpeggio: 24.

	db 4	; End the instrument.
	dw Newsong_Instrument2Loop	; Loops.

Newsong_ArpeggioIndexes
	dw Newsong_Arpeggio1

Newsong_Arpeggio1
	db 3	; Speed

	db 0	; Value: 0
	db 4	; Value: 2
	db 8	; Value: 4
	db 14	; Value: 7
	db 24	; Value: 12
	db 14	; Value: 7
	db 8	; Value: 4
	db 4	; Value: 2
	db 0	; Value: 0
	db -10	; Value: -5
	db -16	; Value: -8
	db -20	; Value: -10
	db -34	; Value: -17
	db -40	; Value: -20
	db -44	; Value: -22
	db -48	; Value: -24
	db -44	; Value: -22
	db -40	; Value: -20
	db -34	; Value: -17
	db -20	; Value: -10
	db -16	; Value: -8
	db -10	; Value: -5
	db 0 * 2 + 1	; Loops to index 0.

Newsong_PitchIndexes


; New song, Subsong 0.
; ----------------------------------

Newsong_Subsong0
	dw Newsong_Subsong0_NoteIndexes	; Index table for the notes.
	dw Newsong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 6	; Initial speed.

	db 0	; Most used instrument.
	db 1	; Second most used instrument.

	db 0	; Most used wait.
	db 11	; Second most used wait.

	db 0	; Default start note in tracks.
	db 2	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
Newsong_Subsong0_Loop
	db 171	; State byte.
	db 16	; New speed (>0).
	db 12	; New height.
	db 129	; New track (0) for channel 1, as a reference (index 1).
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 1
	db 40	; State byte.
	db 128	; New track (1) for channel 1, as a reference (index 0).
	db 129	; New track (0) for channel 2, as a reference (index 1).

; Pattern 2
	db 160	; State byte.
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 129	; New track (0) for channel 3, as a reference (index 1).

; Pattern 3
	db 136	; State byte.
	db 130	; New track (2) for channel 1, as a reference (index 2).
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 4
	db 40	; State byte.
	db 128	; New track (1) for channel 1, as a reference (index 0).
	db 130	; New track (2) for channel 2, as a reference (index 2).

; Pattern 5
	db 160	; State byte.
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 130	; New track (2) for channel 3, as a reference (index 2).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw Newsong_Subsong0_Loop

; The indexes of the tracks.
Newsong_Subsong0_TrackIndexes
	dw Newsong_Subsong0_Track1	; Track 1, index 0.
	dw Newsong_Subsong0_Track0	; Track 0, index 1.
	dw Newsong_Subsong0_Track2	; Track 2, index 2.

Newsong_Subsong0_Track0
	db 12	; Note with effects flag
	db 160	; Secondary instrument (1). Note reference (0). Secondary wait (11).
	db 22	;    Arpeggio table effect 1.
	db 208	; Primary instrument (0). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

Newsong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

Newsong_Subsong0_Track2
	db 12	; Note with effects flag
	db 128	; Note reference (0). Secondary wait (11).
	db 22	;    Arpeggio table effect 1.
	db 208	; Primary instrument (0). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
Newsong_Subsong0_NoteIndexes
	db 48	; Note for index 0.

