; A Harmless Grenade, Song part, encoded in the AKM (minimalist) format V0.


AHarmlessGrenade_Start
AHarmlessGrenade_StartDisarkGenerateExternalLabel

AHarmlessGrenade_DisarkPointerRegionStart0
	dw AHarmlessGrenade_InstrumentIndexes	; Index table for the Instruments.
AHarmlessGrenade_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Arpeggios.
AHarmlessGrenade_DisarkForceNonReferenceDuring2_2
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw AHarmlessGrenade_Subsong0
AHarmlessGrenade_DisarkPointerRegionEnd0

; The Instrument indexes.
AHarmlessGrenade_InstrumentIndexes
AHarmlessGrenade_DisarkPointerRegionStart3
	dw AHarmlessGrenade_Instrument0
	dw AHarmlessGrenade_Instrument1
AHarmlessGrenade_DisarkPointerRegionEnd3

; The Instrument.
AHarmlessGrenade_DisarkByteRegionStart4
AHarmlessGrenade_Instrument0
	db 255	; Speed.

AHarmlessGrenade_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart5
	dw AHarmlessGrenade_Instrument0Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd5

AHarmlessGrenade_Instrument1
	db 0	; Speed.

AHarmlessGrenade_Instrument1Loop	db 74
	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart6
	dw AHarmlessGrenade_Instrument1Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd6

AHarmlessGrenade_DisarkByteRegionEnd4
AHarmlessGrenade_ArpeggioIndexes
AHarmlessGrenade_DisarkPointerRegionStart7
AHarmlessGrenade_DisarkPointerRegionEnd7

AHarmlessGrenade_DisarkByteRegionStart8
AHarmlessGrenade_DisarkByteRegionEnd8

AHarmlessGrenade_PitchIndexes
AHarmlessGrenade_DisarkPointerRegionStart9
AHarmlessGrenade_DisarkPointerRegionEnd9

AHarmlessGrenade_DisarkByteRegionStart10
AHarmlessGrenade_DisarkByteRegionEnd10

; A Harmless Grenade, Subsong 0.
; ----------------------------------

AHarmlessGrenade_Subsong0
AHarmlessGrenade_Subsong0DisarkPointerRegionStart0
	dw AHarmlessGrenade_Subsong0_NoteIndexes	; Index table for the notes.
	dw AHarmlessGrenade_Subsong0_TrackIndexes	; Index table for the Tracks.
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd0

AHarmlessGrenade_Subsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 0	; Most used instrument.
	db 1	; Second most used instrument.

	db 0	; Most used wait.
	db 0	; Second most used wait.

	db 48	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.
AHarmlessGrenade_Subsong0DisarkByteRegionEnd1

; The Linker.
AHarmlessGrenade_Subsong0DisarkByteRegionStart2
; Pattern 0
AHarmlessGrenade_Subsong0_Loop
	db 170	; State byte.
	db 31	; New height.
	db 129	; New track (1) for channel 1, as a reference (index 1).
	db 128	; New track (0) for channel 2, as a reference (index 0).
	db 128	; New track (0) for channel 3, as a reference (index 0).

; Pattern 1
	db 40	; State byte.
	db 128	; New track (0) for channel 1, as a reference (index 0).
	db 129	; New track (1) for channel 2, as a reference (index 1).

; Pattern 2
	db 160	; State byte.
	db 128	; New track (0) for channel 2, as a reference (index 0).
	db 129	; New track (1) for channel 3, as a reference (index 1).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
AHarmlessGrenade_Subsong0DisarkByteRegionEnd2
AHarmlessGrenade_Subsong0DisarkPointerRegionStart3
	dw AHarmlessGrenade_Subsong0_Loop

AHarmlessGrenade_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
AHarmlessGrenade_Subsong0_TrackIndexes
AHarmlessGrenade_Subsong0DisarkPointerRegionStart4
	dw AHarmlessGrenade_Subsong0_Track0	; Track 0, index 0.
	dw AHarmlessGrenade_Subsong0_Track1	; Track 1, index 1.
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd4

AHarmlessGrenade_Subsong0DisarkByteRegionStart5
AHarmlessGrenade_Subsong0_Track0
	db 223	; Primary instrument (0). Same escaped note: 48. New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track1
	db 238	; Secondary instrument (1). New escaped note: 23. New wait (127).
	db 23	;   Escape note value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0DisarkByteRegionEnd5
; The note indexes.
AHarmlessGrenade_Subsong0_NoteIndexes
AHarmlessGrenade_Subsong0DisarkByteRegionStart6
AHarmlessGrenade_Subsong0DisarkByteRegionEnd6

