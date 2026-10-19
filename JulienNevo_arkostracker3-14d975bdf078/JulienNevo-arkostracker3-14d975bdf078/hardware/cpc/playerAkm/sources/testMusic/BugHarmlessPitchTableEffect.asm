; A Harmless Grenade, Song part, encoded in the AKM (minimalist) format V0.


AHarmlessGrenade_Start
AHarmlessGrenade_StartDisarkGenerateExternalLabel

AHarmlessGrenade_DisarkPointerRegionStart0
	dw AHarmlessGrenade_InstrumentIndexes	; Index table for the Instruments.
AHarmlessGrenade_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Arpeggios.
	dw AHarmlessGrenade_PitchIndexes - 2	; Index table for the Pitches.

; The subsongs references.
	dw AHarmlessGrenade_Subsong0
AHarmlessGrenade_DisarkPointerRegionEnd0

; The Instrument indexes.
AHarmlessGrenade_InstrumentIndexes
AHarmlessGrenade_DisarkPointerRegionStart2
	dw AHarmlessGrenade_Instrument0
	dw AHarmlessGrenade_Instrument1
	dw AHarmlessGrenade_Instrument2
	dw AHarmlessGrenade_Instrument3
AHarmlessGrenade_DisarkPointerRegionEnd2

; The Instrument.
AHarmlessGrenade_DisarkByteRegionStart3
AHarmlessGrenade_Instrument0
	db 255	; Speed.

AHarmlessGrenade_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart4
	dw AHarmlessGrenade_Instrument0Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd4

AHarmlessGrenade_Instrument1
	db 0	; Speed.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 2	; Noise: 2.

	db 253	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 1	; Noise: 1.
	dw 32	; Pitch: 32.

	db 125	; Volume: 15.
	dw 48	; Pitch: 48.

	db 125	; Volume: 15.
	dw 68	; Pitch: 68.

	db 125	; Volume: 15.
	dw 116	; Pitch: 116.

	db 125	; Volume: 15.
	dw 228	; Pitch: 228.

	db 121	; Volume: 14.
	dw 180	; Pitch: 180.

	db 117	; Volume: 13.
	dw 292	; Pitch: 292.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart5
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd5

AHarmlessGrenade_Instrument2
	db 2	; Speed.

	db 61	; Volume: 15.

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
AHarmlessGrenade_DisarkPointerRegionStart6
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd6

AHarmlessGrenade_Instrument3
	db 0	; Speed.

AHarmlessGrenade_Instrument3Loop	db 74
	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart7
	dw AHarmlessGrenade_Instrument3Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd7

AHarmlessGrenade_DisarkByteRegionEnd3
AHarmlessGrenade_ArpeggioIndexes
AHarmlessGrenade_DisarkPointerRegionStart8
AHarmlessGrenade_DisarkPointerRegionEnd8

AHarmlessGrenade_DisarkByteRegionStart9
AHarmlessGrenade_DisarkByteRegionEnd9

AHarmlessGrenade_PitchIndexes
AHarmlessGrenade_DisarkPointerRegionStart10
	dw AHarmlessGrenade_Pitch1
AHarmlessGrenade_DisarkPointerRegionEnd10

AHarmlessGrenade_DisarkByteRegionStart11
AHarmlessGrenade_Pitch1
	db 1	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 0	; Value: 0
	db -2	; Value: -1
	db -8	; Value: -4
	db 4	; Value: 2
	db 2 * 2 + 1	; Loops to index 2.
AHarmlessGrenade_DisarkByteRegionEnd11

; A Harmless Grenade, Subsong 0.
; ----------------------------------

AHarmlessGrenade_Subsong0
AHarmlessGrenade_Subsong0DisarkPointerRegionStart0
	dw AHarmlessGrenade_Subsong0_NoteIndexes	; Index table for the notes.
	dw AHarmlessGrenade_Subsong0_TrackIndexes	; Index table for the Tracks.
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd0

AHarmlessGrenade_Subsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 2	; Most used instrument.
	db 1	; Second most used instrument.

	db 7	; Most used wait.
	db 0	; Second most used wait.

	db 0	; Default start note in tracks.
	db 3	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
AHarmlessGrenade_Subsong0DisarkByteRegionEnd1

; The Linker.
AHarmlessGrenade_Subsong0DisarkByteRegionStart2
; Pattern 0
AHarmlessGrenade_Subsong0_Loop
	db 170	; State byte.
	db 31	; New height.
	db ((AHarmlessGrenade_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track0 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 2, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track2 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track1 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
AHarmlessGrenade_Subsong0DisarkByteRegionEnd2
AHarmlessGrenade_Subsong0DisarkPointerRegionStart3
	dw AHarmlessGrenade_Subsong0_Loop

AHarmlessGrenade_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
AHarmlessGrenade_Subsong0_TrackIndexes
AHarmlessGrenade_Subsong0DisarkPointerRegionStart4
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd4

AHarmlessGrenade_Subsong0DisarkByteRegionStart5
AHarmlessGrenade_Subsong0_Track0
	db 12	; Note with effects flag
	db 80	; Primary instrument (2). Note reference (0). Primary wait (7).
	db 1	;    Reset effect, with inverted volume: 0.
	db 24	;    Pitch table effect 1.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (7).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (7).
	db 208	; Primary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track1
	db 12	; Note with effects flag
	db 224	; Secondary instrument (1). Note reference (0). New wait (3).
	db 3	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 80	; Primary instrument (2). Note reference (0). Primary wait (7).
	db 35	;    Volume effect, with inverted volume: 2.
	db 24	;    Pitch table effect 1.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (7).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (7).
	db 208	; Primary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track2
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0DisarkByteRegionEnd5
; The note indexes.
AHarmlessGrenade_Subsong0_NoteIndexes
AHarmlessGrenade_Subsong0DisarkByteRegionStart6
	db 55	; Note for index 0.
AHarmlessGrenade_Subsong0DisarkByteRegionEnd6

