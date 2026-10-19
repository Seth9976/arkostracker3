; New song, Song part, encoded in the AKM (minimalist) format V0.


Newsong_Start
Newsong_StartDisarkGenerateExternalLabel

Newsong_DisarkPointerRegionStart0
	dw Newsong_InstrumentIndexes	; Index table for the Instruments.
	dw Newsong_ArpeggioIndexes - 2	; Index table for the Arpeggios.
Newsong_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Pitches.

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
	dw Newsong_Arpeggio1
	dw Newsong_Arpeggio2
	dw Newsong_Arpeggio3
	dw Newsong_Arpeggio4
	dw Newsong_Arpeggio5
	dw Newsong_Arpeggio6
	dw Newsong_Arpeggio7
	dw Newsong_Arpeggio8
	dw Newsong_Arpeggio9
	dw Newsong_Arpeggio10
	dw Newsong_Arpeggio11
	dw Newsong_Arpeggio12
	dw Newsong_Arpeggio13
	dw Newsong_Arpeggio14
	dw Newsong_Arpeggio15
	dw Newsong_Arpeggio16
	dw Newsong_Arpeggio17
	dw Newsong_Arpeggio18
	dw Newsong_Arpeggio19
	dw Newsong_Arpeggio20
	dw Newsong_Arpeggio21
	dw Newsong_Arpeggio22
	dw Newsong_Arpeggio23
	dw Newsong_Arpeggio24
	dw Newsong_Arpeggio25
	dw Newsong_Arpeggio26
Newsong_DisarkPointerRegionEnd6

Newsong_DisarkByteRegionStart7
Newsong_Arpeggio1
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 2	; Value: 1
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio2
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 4	; Value: 2
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio3
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 6	; Value: 3
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio4
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 8	; Value: 4
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio5
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 10	; Value: 5
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio6
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 12	; Value: 6
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio7
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 14	; Value: 7
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio8
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 16	; Value: 8
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio9
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 18	; Value: 9
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio10
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 20	; Value: 10
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio11
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 22	; Value: 11
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio12
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 24	; Value: 12
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio13
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 26	; Value: 13
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio14
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 28	; Value: 14
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio15
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 30	; Value: 15
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio16
	db 0	; Speed

	db 0	; Value: 0
	db 2	; Value: 1
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio17
	db 0	; Speed

	db 0	; Value: 0
	db 4	; Value: 2
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio18
	db 0	; Speed

	db 0	; Value: 0
	db 6	; Value: 3
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio19
	db 0	; Speed

	db 0	; Value: 0
	db 8	; Value: 4
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio20
	db 0	; Speed

	db 0	; Value: 0
	db 10	; Value: 5
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio21
	db 0	; Speed

	db 0	; Value: 0
	db 12	; Value: 6
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio22
	db 0	; Speed

	db 0	; Value: 0
	db 14	; Value: 7
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio23
	db 0	; Speed

	db 0	; Value: 0
	db 16	; Value: 8
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio24
	db 0	; Speed

	db 0	; Value: 0
	db 18	; Value: 9
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio25
	db 0	; Speed

	db 0	; Value: 0
	db 20	; Value: 10
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_Arpeggio26
	db 0	; Speed

	db 0	; Value: 0
	db 22	; Value: 11
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
Newsong_DisarkByteRegionEnd7

Newsong_PitchIndexes
Newsong_DisarkPointerRegionStart8
Newsong_DisarkPointerRegionEnd8

Newsong_DisarkByteRegionStart9
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
	db 25	; New height.
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
	db 22	;    Arpeggio table effect 1.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 38	;    Arpeggio table effect 2.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 54	;    Arpeggio table effect 3.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 70	;    Arpeggio table effect 4.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 86	;    Arpeggio table effect 5.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 102	;    Arpeggio table effect 6.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 118	;    Arpeggio table effect 7.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 134	;    Arpeggio table effect 8.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 150	;    Arpeggio table effect 9.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 166	;    Arpeggio table effect 10.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 182	;    Arpeggio table effect 11.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 198	;    Arpeggio table effect 12.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 214	;    Arpeggio table effect 13.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 230	;    Arpeggio table effect 14.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 15	;    Arpeggio table effect 15.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 16	;    Arpeggio table effect 16.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 17	;    Arpeggio table effect 17.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 18	;    Arpeggio table effect 18.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 19	;    Arpeggio table effect 19.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 20	;    Arpeggio table effect 20.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 21	;    Arpeggio table effect 21.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 22	;    Arpeggio table effect 22.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 23	;    Arpeggio table effect 23.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 24	;    Arpeggio table effect 24.
	db 12	; Note with effects flag.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 246	;    Effect escape value, because >14.
	db 25	;    Arpeggio table effect 25.
	db 12	; Note with effects flag.
	db 208	; Primary instrument (1). Note reference (0). New wait (127).
	db 127	;   Escape wait value.
	db 246	;    Effect escape value, because >14.
	db 26	;    Arpeggio table effect 26.

Newsong_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

Newsong_Subsong0DisarkByteRegionEnd5
; The note indexes.
Newsong_Subsong0_NoteIndexes
Newsong_Subsong0DisarkByteRegionStart6
	db 48	; Note for index 0.
Newsong_Subsong0DisarkByteRegionEnd6

