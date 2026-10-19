; New song, Song part, encoded in the AKM (minimalist) format V0.


Newsong_Start
Newsong_StartDisarkGenerateExternalLabel

Newsong_DisarkPointerRegionStart0
	dw Newsong_InstrumentIndexes	; Index table for the Instruments.
Newsong_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Arpeggios.
	dw Newsong_PitchIndexes - 2	; Index table for the Pitches.

; The subsongs references.
	dw Newsong_Subsong0
Newsong_DisarkPointerRegionEnd0

; The Instrument indexes.
Newsong_InstrumentIndexes
Newsong_DisarkPointerRegionStart2
	dw Newsong_Instrument0
	dw Newsong_Instrument1
Newsong_DisarkPointerRegionEnd2

; The Instrument.
Newsong_DisarkByteRegionStart3
Newsong_Instrument0
	db 255	; Speed.

Newsong_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
Newsong_DisarkPointerRegionStart4
	dw Newsong_Instrument0Loop	; Loops.
Newsong_DisarkPointerRegionEnd4

Newsong_Instrument1
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
Newsong_DisarkPointerRegionStart5
	dw Newsong_Instrument0Loop	; Loop to silence.
Newsong_DisarkPointerRegionEnd5

Newsong_DisarkByteRegionEnd3
Newsong_ArpeggioIndexes
Newsong_DisarkPointerRegionStart6
Newsong_DisarkPointerRegionEnd6

Newsong_DisarkByteRegionStart7
Newsong_DisarkByteRegionEnd7

Newsong_PitchIndexes
Newsong_DisarkPointerRegionStart8
	dw Newsong_Pitch1
	dw Newsong_Pitch2
	dw Newsong_Pitch3
	dw Newsong_Pitch4
	dw Newsong_Pitch5
	dw Newsong_Pitch6
	dw Newsong_Pitch7
	dw Newsong_Pitch8
	dw Newsong_Pitch9
	dw Newsong_Pitch10
	dw Newsong_Pitch11
	dw Newsong_Pitch12
	dw Newsong_Pitch13
	dw Newsong_Pitch14
	dw Newsong_Pitch15
	dw Newsong_Pitch16
	dw Newsong_Pitch17
	dw Newsong_Pitch18
Newsong_DisarkPointerRegionEnd8

Newsong_DisarkByteRegionStart9
Newsong_Pitch1
	db 0	; Speed

	db -2	; Value: -1
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch2
	db 0	; Speed

	db -14	; Value: -7
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch3
	db 0	; Speed

	db -26	; Value: -13
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch4
	db 0	; Speed

	db -32	; Value: -16
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch5
	db 0	; Speed

	db -38	; Value: -19
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch6
	db 0	; Speed

	db -48	; Value: -24
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch7
	db 0	; Speed

	db -58	; Value: -29
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch8
	db 0	; Speed

	db -66	; Value: -33
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch9
	db 0	; Speed

	db -72	; Value: -36
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch10
	db 0	; Speed

	db -80	; Value: -40
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch11
	db 0	; Speed

	db -100	; Value: -50
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch12
	db 0	; Speed

	db -106	; Value: -53
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch13
	db 0	; Speed

	db -108	; Value: -54
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch14
	db 0	; Speed

	db -110	; Value: -55
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch15
	db 0	; Speed

	db -112	; Value: -56
	db -64	; Value: -32
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch16
	db 0	; Speed

	db -32	; Value: -16
	db -128	; Value: -64
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch17
	db 0	; Speed

	db -96	; Value: -48
	db -64	; Value: -32
	db -32	; Value: -16
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Pitch18
	db 0	; Speed

	db -10	; Value: -5
	db -32	; Value: -16
	db -64	; Value: -32
	db -96	; Value: -48
	db 0 * 2 + 1	; Loops to index 0.
Newsong_DisarkByteRegionEnd9

; New song, Subsong 0.
; ----------------------------------

Newsong_Subsong0
Newsong_Subsong0DisarkPointerRegionStart0
	dw Newsong_Subsong0_NoteIndexes	; Index table for the notes.
	dw Newsong_Subsong0_TrackIndexes	; Index table for the Tracks.
Newsong_Subsong0DisarkPointerRegionEnd0

Newsong_Subsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 0	; Second most used instrument.

	db 0	; Most used wait.
	db 0	; Second most used wait.

	db 0	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
Newsong_Subsong0DisarkByteRegionEnd1

; The Linker.
Newsong_Subsong0DisarkByteRegionStart2
; Pattern 0
Newsong_Subsong0_Loop
	db 171	; State byte.
	db 16	; New speed (>0).
	db 19	; New height.
	db ((Newsong_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Newsong_Subsong0_Track0 - ($ + 1)) & 255)
	db ((Newsong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Newsong_Subsong0_Track1 - ($ + 1)) & 255)
	db ((Newsong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Newsong_Subsong0_Track1 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
Newsong_Subsong0DisarkByteRegionEnd2
Newsong_Subsong0DisarkPointerRegionStart3
	dw Newsong_Subsong0_Loop

Newsong_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
Newsong_Subsong0_TrackIndexes
Newsong_Subsong0DisarkPointerRegionStart4
Newsong_Subsong0DisarkPointerRegionEnd4

Newsong_Subsong0DisarkByteRegionStart5
Newsong_Subsong0_Track0
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 24	;    Pitch table effect 1.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 40	;    Pitch table effect 2.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 56	;    Pitch table effect 3.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 72	;    Pitch table effect 4.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 88	;    Pitch table effect 5.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 104	;    Pitch table effect 6.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 120	;    Pitch table effect 7.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 136	;    Pitch table effect 8.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 152	;    Pitch table effect 9.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 168	;    Pitch table effect 10.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 184	;    Pitch table effect 11.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 200	;    Pitch table effect 12.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 216	;    Pitch table effect 13.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 232	;    Pitch table effect 14.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 248	;    Effect escape value, because >14.
	db 15	;    Pitch table effect 15.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 248	;    Effect escape value, because >14.
	db 16	;    Pitch table effect 16.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 248	;    Effect escape value, because >14.
	db 17	;    Pitch table effect 17.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 248	;    Effect escape value, because >14.
	db 18	;    Pitch table effect 18.
	db 12	; Note with effects flag.
	db 208	; Primary instrument (1). Note reference (0). New wait (127).
	db 127	;   Escape wait value.
	db 8	;    Pitch table effect 0.

Newsong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

Newsong_Subsong0DisarkByteRegionEnd5
; The note indexes.
Newsong_Subsong0_NoteIndexes
Newsong_Subsong0DisarkByteRegionStart6
	db 36	; Note for index 0.
Newsong_Subsong0DisarkByteRegionEnd6

