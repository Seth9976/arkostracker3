; New song, Song part, encoded in the AKM (minimalist) format V0.


TestStart
TestStartDisarkGenerateExternalLabel

TestDisarkPointerRegionStart0
	dw TestInstrumentIndexes	; Index table for the Instruments.
TestDisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Arpeggios.
	dw TestPitchIndexes - 2	; Index table for the Pitches.

; The subsongs references.
	dw TestSubsong0
TestDisarkPointerRegionEnd0

; The Instrument indexes.
TestInstrumentIndexes
TestDisarkPointerRegionStart2
	dw TestInstrument0
	dw TestInstrument1
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

TestDisarkByteRegionEnd3
TestArpeggioIndexes
TestDisarkPointerRegionStart6
TestDisarkPointerRegionEnd6

TestDisarkByteRegionStart7
TestDisarkByteRegionEnd7

TestPitchIndexes
TestDisarkPointerRegionStart8
	dw TestPitch1
	dw TestPitch2
TestDisarkPointerRegionEnd8

TestDisarkByteRegionStart9
TestPitch1
	db 0	; Speed

	db 0	; Value: 0
	db -2	; Value: -1
	db -4	; Value: -2
	db -2	; Value: -1
	db 0 * 2 + 1	; Loops to index 0.
TestPitch2
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
TestDisarkByteRegionEnd9

; New song, Subsong 0.
; ----------------------------------

TestSubsong0
TestSubsong0DisarkPointerRegionStart0
	dw TestSubsong0_NoteIndexes	; Index table for the notes.
	dw TestSubsong0_TrackIndexes	; Index table for the Tracks.
TestSubsong0DisarkPointerRegionEnd0

TestSubsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 0	; Second most used instrument.

	db 1	; Most used wait.
	db 2	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
TestSubsong0DisarkByteRegionEnd1

; The Linker.
TestSubsong0DisarkByteRegionStart2
; Pattern 0
TestSubsong0_Loop
	db 171	; State byte.
	db 32	; New speed (>0).
	db 79	; New height.
	db ((TestSubsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((TestSubsong0_Track0 - ($ + 1)) & 255)
	db ((TestSubsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 2, as an offset. Offset MSB, then LSB.
	db ((TestSubsong0_Track1 - ($ + 1)) & 255)
	db ((TestSubsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 3, as an offset. Offset MSB, then LSB.
	db ((TestSubsong0_Track2 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
TestSubsong0DisarkByteRegionEnd2
TestSubsong0DisarkPointerRegionStart3
	dw TestSubsong0_Loop

TestSubsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
TestSubsong0_TrackIndexes
TestSubsong0DisarkPointerRegionStart4
TestSubsong0DisarkPointerRegionEnd4

TestSubsong0DisarkByteRegionStart5
TestSubsong0_Track0
	db 12	; Note with effects flag.
	db 209	; Primary instrument (1). Note reference (1). New wait (3).
	db 3	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 29	; Effect only. 
	db 24	;    Pitch table effect 1.
	db 157	; Effect only. Secondary wait (2).
	db 8	;    Pitch table effect 0.
	db 157	; Effect only. Secondary wait (2).
	db 24	;    Pitch table effect 1.
	db 93	; Effect only. Primary wait (1).
	db 46	;    Force pitch speed effect 2.
	db 93	; Effect only. Primary wait (1).
	db 78	;    Force pitch speed effect 4.
	db 29	; Effect only. 
	db 254	;    Effect escape value, because >14.
	db 16	;    Force pitch speed effect 16.
	db 157	; Effect only. Secondary wait (2).
	db 14	;    Force pitch speed effect 0.
	db 157	; Effect only. Secondary wait (2).
	db 30	;    Force pitch speed effect 1.
	db 12	; Note with effects flag.
	db 17	; Primary instrument (1). Note reference (1). 
	db 0	;    Reset effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 40	;    Pitch table effect 2.
	db 94	; Primary instrument (1). New escaped note: 62. Primary wait (1).
	db 62	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 64. Primary wait (1).
	db 64	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (1).
	db 65	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 12	; Note with effects flag.
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (2).
	db 30	;    Force pitch speed effect 1.
	db 12	; Note with effects flag.
	db 16	; Primary instrument (1). Note reference (0). 
	db 46	;    Force pitch speed effect 2.
	db 12	; Note with effects flag.
	db 16	; Primary instrument (1). Note reference (0). 
	db 110	;    Force pitch speed effect 6.
	db 12	; Note with effects flag.
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (2).
	db 24	;    Pitch table effect 1.
	db 29	; Effect only. 
	db 244	;    Pitch up: 48.
	db 48	;    Pitch, LSB.
	db 128	;    Pitch, MSB.
	db 157	; Effect only. Secondary wait (2).
	db 244	;    Pitch down: 32.
	db 32	;    Pitch, LSB.
	db 0	;    Pitch, MSB.
	db 157	; Effect only. Secondary wait (2).
	db 8	;    Pitch table effect 0.
	db 93	; Effect only. Primary wait (1).
	db 24	;    Pitch table effect 1.
	db 12	; Note with effects flag.
	db 222	; Primary instrument (1). New escaped note: 48. New wait (0).
	db 48	;   Escape note value.
	db 0	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 93	; Effect only. Primary wait (1).
	db 24	;    Pitch table effect 1.
	db 93	; Effect only. Primary wait (1).
	db 40	;    Pitch table effect 2.
	db 93	; Effect only. Primary wait (1).
	db 24	;    Pitch table effect 1.
	db 29	; Effect only. 
	db 40	;    Pitch table effect 2.
	db 29	; Effect only. 
	db 40	;    Pitch table effect 2.
	db 239	; Secondary instrument (0). Same escaped note: 48. New wait (127).
	db 127	;   Escape wait value.

TestSubsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

TestSubsong0_Track2
	db 205	; New wait (127).
	db 127	;   Escape wait value.

TestSubsong0DisarkByteRegionEnd5
; The note indexes.
TestSubsong0_NoteIndexes
TestSubsong0DisarkByteRegionStart6
	db 67	; Note for index 0.
	db 60	; Note for index 1.
TestSubsong0DisarkByteRegionEnd6

