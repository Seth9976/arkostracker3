; New song, Song part, encoded in the AKM (minimalist) format V0.


TestStart
TestStartDisarkGenerateExternalLabel

TestDisarkPointerRegionStart0
	dw TestInstrumentIndexes	; Index table for the Instruments.
TestDisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Arpeggios.
TestDisarkForceNonReferenceDuring2_2
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw TestSubsong0
TestDisarkPointerRegionEnd0

; The Instrument indexes.
TestInstrumentIndexes
TestDisarkPointerRegionStart3
	dw TestInstrument0
	dw TestInstrument1
	dw TestInstrument2
	dw TestInstrument3
	dw TestInstrument4
TestDisarkPointerRegionEnd3

; The Instrument.
TestDisarkByteRegionStart4
TestInstrument0
	db 255	; Speed.

TestInstrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
TestDisarkPointerRegionStart5
	dw TestInstrument0Loop	; Loops.
TestDisarkPointerRegionEnd5

TestInstrument1
	db 2	; Speed.

	db 61	; Volume: 15.

TestInstrument1Loop	db 185	; Volume: 14.
	db 24	; Arpeggio: 12.

	db 181	; Volume: 13.
	db 233	; Arpeggio: -12.
	db 1	; Noise: 1.

	db 241	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 9	; Noise: 9.
	dw -52	; Pitch: -52.

	db 113	; Volume: 12.
	dw 44	; Pitch: 44.

	db 237	; Volume: 11.
	db 25	; Arpeggio: 12.
	db 31	; Noise: 31.
	dw -8	; Pitch: -8.

	db 233	; Volume: 10.
	db 24	; Arpeggio: 12.
	dw 8	; Pitch: 8.

	db 4	; End the instrument.
TestDisarkPointerRegionStart6
	dw TestInstrument1Loop	; Loops.
TestDisarkPointerRegionEnd6

TestInstrument2
	db 0	; Speed.

TestInstrument2Loop	db 66
	db 194, 4	; Arpeggio: 4.

	db 202, 7	; Arpeggio: 7.

	db 206, 4	; Arpeggio: 4.
	dw -48	; Pitch: -48.

	db 206, 7	; Arpeggio: 7.
	dw 48	; Pitch: 48.

	db 4	; End the instrument.
TestDisarkPointerRegionStart7
	dw TestInstrument2Loop	; Loops.
TestDisarkPointerRegionEnd7

TestInstrument3
	db 0	; Speed.

	db 248	; Volume: 15.
	db 12	; Noise.

	db 240	; Volume: 14.
	db 14	; Noise.

	db 232	; Volume: 13.
	db 13	; Noise.

	db 216	; Volume: 11.
	db 12	; Noise.

	db 216	; Volume: 11.
	db 11	; Noise.

	db 208	; Volume: 10.
	db 10	; Noise.

	db 4	; End the instrument.
TestDisarkPointerRegionStart8
	dw TestInstrument0Loop	; Loop to silence.
TestDisarkPointerRegionEnd8

TestInstrument4
	db 6	; Speed.

TestInstrument4Loop	db 3 : dw 1	; Hardware period: 1.

	db 7 : dw -39	; Pitch: -39.
	dw 1	; Hardware period: 1.

	db 7 : dw 32	; Pitch: 32.
	dw 2	; Hardware period: 2.

	db 131, 1	; Arpeggio: 1.
	dw 2	; Hardware period: 2.

	db 135, 2	; Arpeggio: 2.
	dw -2	; Pitch: -2.
	dw 3	; Hardware period: 3.

	db 135, -5	; Arpeggio: -5.
	dw 3	; Pitch: 3.
	dw 3	; Hardware period: 3.

	db 4	; End the instrument.
TestDisarkPointerRegionStart9
	dw TestInstrument4Loop	; Loops.
TestDisarkPointerRegionEnd9

TestDisarkByteRegionEnd4
TestArpeggioIndexes
TestDisarkPointerRegionStart10
TestDisarkPointerRegionEnd10

TestDisarkByteRegionStart11
TestDisarkByteRegionEnd11

TestPitchIndexes
TestDisarkPointerRegionStart12
TestDisarkPointerRegionEnd12

TestDisarkByteRegionStart13
TestDisarkByteRegionEnd13

; New song, Subsong 0.
; ----------------------------------

TestSubsong0
TestSubsong0DisarkPointerRegionStart0
	dw TestSubsong0_NoteIndexes	; Index table for the notes.
	dw TestSubsong0_TrackIndexes	; Index table for the Tracks.
TestSubsong0DisarkPointerRegionEnd0

TestSubsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 3	; Most used instrument.
	db 1	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.
TestSubsong0DisarkByteRegionEnd1

; The Linker.
TestSubsong0DisarkByteRegionStart2
; Pattern 0
TestSubsong0_Loop
	db 170	; State byte.
	db 63	; New height.
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
	db 96	; Secondary instrument (1). Note reference (0). Primary wait (0).
	db 110	; Secondary instrument (1). New escaped note: 50. Primary wait (0).
	db 50	;   Escape note value.
	db 174	; Secondary instrument (1). New escaped note: 52. Secondary wait (1).
	db 52	;   Escape note value.
	db 174	; Secondary instrument (1). New escaped note: 53. Secondary wait (1).
	db 53	;   Escape note value.
	db 226	; Secondary instrument (1). Note reference (2). New wait (6).
	db 6	;   Escape wait value.
	db 192	; Note reference (0). New wait (2).
	db 2	;   Escape wait value.
	db 254	; New instrument (2). New escaped note: 38. New wait (6).
	db 38	;   Escape note value.
	db 2	;   Escape instrument value.
	db 6	;   Escape wait value.
	db 176	; New instrument (0). Note reference (0). Secondary wait (1).
	db 0	;   Escape instrument value.
	db 80	; Primary instrument (3). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (3). Note reference (2). Primary wait (0).
	db 81	; Primary instrument (3). Note reference (1). Primary wait (0).
	db 158	; Primary instrument (3). New escaped note: 60. Secondary wait (1).
	db 60	;   Escape note value.
	db 95	; Primary instrument (3). Same escaped note: 60. Primary wait (0).
	db 81	; Primary instrument (3). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (3). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 210	; Primary instrument (3). Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 240	; New instrument (4). Note reference (0). New wait (7).
	db 4	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 14	; New escaped note: 53. 
	db 53	;   Escape note value.
	db 193	; Note reference (1). New wait (9).
	db 9	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
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
	db 48	; Note for index 0.
	db 59	; Note for index 1.
	db 55	; Note for index 2.
TestSubsong0DisarkByteRegionEnd6

