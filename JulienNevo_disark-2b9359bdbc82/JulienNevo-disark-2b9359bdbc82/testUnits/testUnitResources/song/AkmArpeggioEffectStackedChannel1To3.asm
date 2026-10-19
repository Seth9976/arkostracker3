; New song, Song part, encoded in the AKM (minimalist) format V0.


TestStart
TestStartDisarkGenerateExternalLabel

TestDisarkPointerRegionStart0
	dw TestInstrumentIndexes	; Index table for the Instruments.
	dw TestArpeggioIndexes - 2	; Index table for the Arpeggios.
TestDisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw TestSubsong0
TestDisarkPointerRegionEnd0

; The Instrument indexes.
TestInstrumentIndexes
TestDisarkPointerRegionStart2
	dw TestInstrument0
	dw TestInstrument1
	dw TestInstrument2
TestDisarkPointerRegionEnd2

; The Instrument.
TestDisarkByteRegionStart3
TestInstrument0
	db 255	; Speed.

TestInstrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
TestDisarkPointerRegionStart4
	dw TestInstrument0Loop	; Loops.
TestDisarkPointerRegionEnd4

TestInstrument1
	db 0	; Speed.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

TestInstrument1Loop	db 41	; Volume: 10.

	db 4	; End the instrument.
TestDisarkPointerRegionStart5
	dw TestInstrument1Loop	; Loops.
TestDisarkPointerRegionEnd5

TestInstrument2
	db 0	; Speed.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 185	; Volume: 14.
	db 232	; Arpeggio: -12.

	db 53	; Volume: 13.

	db 177	; Volume: 12.
	db 48	; Arpeggio: 24.

	db 45	; Volume: 11.

TestInstrument2Loop	db 169	; Volume: 10.
	db 24	; Arpeggio: 12.

	db 169	; Volume: 10.
	db 232	; Arpeggio: -12.

	db 41	; Volume: 10.

	db 169	; Volume: 10.
	db 48	; Arpeggio: 24.

	db 4	; End the instrument.
TestDisarkPointerRegionStart6
	dw TestInstrument2Loop	; Loops.
TestDisarkPointerRegionEnd6

TestDisarkByteRegionEnd3
TestArpeggioIndexes
TestDisarkPointerRegionStart7
	dw TestArpeggio1
TestDisarkPointerRegionEnd7

TestDisarkByteRegionStart8
TestArpeggio1
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
	db 0	; Value: 0
	db 4	; Value: 2
	db 8	; Value: 4
	db 14	; Value: 7
	db 24	; Value: 12
	db 14	; Value: 7
	db 8	; Value: 4
	db 4	; Value: 2
	db 0 * 2 + 1	; Loops to index 0.
TestDisarkByteRegionEnd8

TestPitchIndexes
TestDisarkPointerRegionStart9
TestDisarkPointerRegionEnd9

TestDisarkByteRegionStart10
TestDisarkByteRegionEnd10

; New song, Subsong 0.
; ----------------------------------

TestSubsong0
TestSubsong0DisarkPointerRegionStart0
	dw TestSubsong0_NoteIndexes	; Index table for the notes.
	dw TestSubsong0_TrackIndexes	; Index table for the Tracks.
TestSubsong0DisarkPointerRegionEnd0

TestSubsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 0	; Most used instrument.
	db 2	; Second most used instrument.

	db 11	; Most used wait.
	db 0	; Second most used wait.

	db 0	; Default start note in tracks.
	db 1	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
TestSubsong0DisarkByteRegionEnd1

; The Linker.
TestSubsong0DisarkByteRegionStart2
; Pattern 0
TestSubsong0_Loop
	db 171	; State byte.
	db 16	; New speed (>0).
	db 12	; New height.
	db 130	; New track (0) for channel 1, as a reference (index 2).
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 1
	db 40	; State byte.
	db 128	; New track (1) for channel 1, as a reference (index 0).
	db 130	; New track (0) for channel 2, as a reference (index 2).

; Pattern 2
	db 160	; State byte.
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 130	; New track (0) for channel 3, as a reference (index 2).

; Pattern 3
	db 136	; State byte.
	db 129	; New track (2) for channel 1, as a reference (index 1).
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 4
	db 40	; State byte.
	db 128	; New track (1) for channel 1, as a reference (index 0).
	db 129	; New track (2) for channel 2, as a reference (index 1).

; Pattern 5
	db 160	; State byte.
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 129	; New track (2) for channel 3, as a reference (index 1).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
TestSubsong0DisarkByteRegionEnd2
TestSubsong0DisarkPointerRegionStart3
	dw TestSubsong0_Loop

TestSubsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
TestSubsong0_TrackIndexes
TestSubsong0DisarkPointerRegionStart4
	dw TestSubsong0_Track1	; Track 1, index 0.
	dw TestSubsong0_Track2	; Track 2, index 1.
	dw TestSubsong0_Track0	; Track 0, index 2.
TestSubsong0DisarkPointerRegionEnd4

TestSubsong0DisarkByteRegionStart5
TestSubsong0_Track0
	db 12	; Note with effects flag.
	db 64	; Note reference (0). Primary wait (11).
	db 22	;    Arpeggio table effect 1.
	db 208	; Primary instrument (0). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

TestSubsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

TestSubsong0_Track2
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (11).
	db 22	;    Arpeggio table effect 1.
	db 208	; Primary instrument (0). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

TestSubsong0DisarkByteRegionEnd5
; The note indexes.
TestSubsong0_NoteIndexes
TestSubsong0DisarkByteRegionStart6
	db 48	; Note for index 0.
TestSubsong0DisarkByteRegionEnd6

