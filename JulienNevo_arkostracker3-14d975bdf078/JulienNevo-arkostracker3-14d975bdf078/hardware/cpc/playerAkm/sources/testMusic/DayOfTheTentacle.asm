; Day of the Tentacle, Song part, encoded in the AKM (minimalist) format V0.


DayoftheTentacle_Start
DayoftheTentacle_StartDisarkGenerateExternalLabel

DayoftheTentacle_DisarkPointerRegionStart0
	dw DayoftheTentacle_InstrumentIndexes	; Index table for the Instruments.
	dw DayoftheTentacle_ArpeggioIndexes - 2	; Index table for the Arpeggios.
DayoftheTentacle_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw DayoftheTentacle_Subsong0
DayoftheTentacle_DisarkPointerRegionEnd0

; The Instrument indexes.
DayoftheTentacle_InstrumentIndexes
DayoftheTentacle_DisarkPointerRegionStart2
	dw DayoftheTentacle_Instrument0
	dw DayoftheTentacle_Instrument1
	dw DayoftheTentacle_Instrument2
	dw DayoftheTentacle_Instrument3
	dw DayoftheTentacle_Instrument4
	dw DayoftheTentacle_Instrument5
	dw DayoftheTentacle_Instrument6
	dw DayoftheTentacle_Instrument7
	dw DayoftheTentacle_Instrument8
	dw DayoftheTentacle_Instrument9
	dw DayoftheTentacle_Instrument10
	dw DayoftheTentacle_Instrument11
DayoftheTentacle_DisarkPointerRegionEnd2

; The Instrument.
DayoftheTentacle_DisarkByteRegionStart3
DayoftheTentacle_Instrument0
	db 255	; Speed.

DayoftheTentacle_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
DayoftheTentacle_DisarkPointerRegionStart4
	dw DayoftheTentacle_Instrument0Loop	; Loops.
DayoftheTentacle_DisarkPointerRegionEnd4

DayoftheTentacle_Instrument1
	db 0	; Speed.

	db 57	; Volume: 14.

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
DayoftheTentacle_DisarkPointerRegionStart5
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd5

DayoftheTentacle_Instrument2
	db 0	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 184	; Volume: 7.
	db 1	; Noise.

	db 4	; End the instrument.
DayoftheTentacle_DisarkPointerRegionStart6
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd6

DayoftheTentacle_Instrument3
	db 1	; Speed.

	db 57	; Volume: 14.

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
DayoftheTentacle_DisarkPointerRegionStart7
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd7

DayoftheTentacle_Instrument4
	db 0	; Speed.

	db 248	; Volume: 15.
	db 8	; Noise.

	db 240	; Volume: 14.
	db 2	; Noise.

	db 232	; Volume: 13.
	db 2	; Noise.

	db 224	; Volume: 12.
	db 2	; Noise.

	db 216	; Volume: 11.
	db 2	; Noise.

	db 208	; Volume: 10.
	db 2	; Noise.

	db 4	; End the instrument.
DayoftheTentacle_DisarkPointerRegionStart8
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd8

DayoftheTentacle_Instrument5
	db 0	; Speed.

	db 253	; Volume: 15.
	db 13	; Arpeggio: 6.
	db 1	; Noise: 1.
	dw 16	; Pitch: 16.

	db 253	; Volume: 15.
	db 12	; Arpeggio: 6.
	dw 32	; Pitch: 32.

	db 253	; Volume: 15.
	db 12	; Arpeggio: 6.
	dw 48	; Pitch: 48.

	db 253	; Volume: 15.
	db 12	; Arpeggio: 6.
	dw 64	; Pitch: 64.

	db 253	; Volume: 15.
	db 12	; Arpeggio: 6.
	dw 80	; Pitch: 80.

	db 249	; Volume: 14.
	db 12	; Arpeggio: 6.
	dw 96	; Pitch: 96.

	db 4	; End the instrument.
DayoftheTentacle_DisarkPointerRegionStart9
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd9

DayoftheTentacle_Instrument6
	db 10	; Speed.

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
DayoftheTentacle_DisarkPointerRegionStart10
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd10

DayoftheTentacle_Instrument7
	db 9	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 240	; Volume: 14.
	db 2	; Noise.

	db 232	; Volume: 13.
	db 4	; Noise.

	db 224	; Volume: 12.
	db 5	; Noise.

	db 216	; Volume: 11.
	db 7	; Noise.

	db 208	; Volume: 10.
	db 8	; Noise.

	db 200	; Volume: 9.
	db 10	; Noise.

	db 192	; Volume: 8.
	db 12	; Noise.

	db 184	; Volume: 7.
	db 13	; Noise.

	db 176	; Volume: 6.
	db 15	; Noise.

	db 168	; Volume: 5.
	db 16	; Noise.

	db 160	; Volume: 4.
	db 18	; Noise.

	db 152	; Volume: 3.
	db 19	; Noise.

	db 144	; Volume: 2.
	db 21	; Noise.

	db 136	; Volume: 1.
	db 23	; Noise.

	db 4	; End the instrument.
DayoftheTentacle_DisarkPointerRegionStart11
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd11

DayoftheTentacle_Instrument8
	db 0	; Speed.

DayoftheTentacle_Instrument8Loop	db 61	; Volume: 15.

	db 4	; End the instrument.
DayoftheTentacle_DisarkPointerRegionStart12
	dw DayoftheTentacle_Instrument8Loop	; Loops.
DayoftheTentacle_DisarkPointerRegionEnd12

DayoftheTentacle_Instrument9
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
DayoftheTentacle_DisarkPointerRegionStart13
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd13

DayoftheTentacle_Instrument10
	db 2	; Speed.

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
DayoftheTentacle_DisarkPointerRegionStart14
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd14

DayoftheTentacle_Instrument11
	db 0	; Speed.

	db 61	; Volume: 15.

	db 125	; Volume: 15.
	dw 32	; Pitch: 32.

	db 125	; Volume: 15.
	dw 96	; Pitch: 96.

	db 125	; Volume: 15.
	dw 160	; Pitch: 160.

	db 125	; Volume: 15.
	dw 240	; Pitch: 240.

	db 125	; Volume: 15.
	dw 304	; Pitch: 304.

	db 125	; Volume: 15.
	dw 400	; Pitch: 400.

	db 125	; Volume: 15.
	dw 480	; Pitch: 480.

	db 125	; Volume: 15.
	dw 560	; Pitch: 560.

	db 4	; End the instrument.
DayoftheTentacle_DisarkPointerRegionStart15
	dw DayoftheTentacle_Instrument0Loop	; Loop to silence.
DayoftheTentacle_DisarkPointerRegionEnd15

DayoftheTentacle_DisarkByteRegionEnd3
DayoftheTentacle_ArpeggioIndexes
DayoftheTentacle_DisarkPointerRegionStart16
	dw DayoftheTentacle_Arpeggio1
	dw DayoftheTentacle_Arpeggio2
	dw DayoftheTentacle_Arpeggio3
	dw DayoftheTentacle_Arpeggio4
	dw DayoftheTentacle_Arpeggio5
	dw DayoftheTentacle_Arpeggio6
	dw DayoftheTentacle_Arpeggio7
	dw DayoftheTentacle_Arpeggio8
	dw DayoftheTentacle_Arpeggio9
	dw DayoftheTentacle_Arpeggio10
	dw DayoftheTentacle_Arpeggio11
DayoftheTentacle_DisarkPointerRegionEnd16

DayoftheTentacle_DisarkByteRegionStart17
DayoftheTentacle_Arpeggio1
	db 0	; Speed

	db 24	; Value: 12
	db 0	; Value: 0
	db 1 * 2 + 1	; Loops to index 1.
DayoftheTentacle_Arpeggio2
	db 1	; Speed

	db 0	; Value: 0
	db 24	; Value: 12
	db 24	; Value: 12
	db 0	; Value: 0
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio3
	db 0	; Speed

	db 0	; Value: 0
	db 8	; Value: 4
	db 14	; Value: 7
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio4
	db 0	; Speed

	db 0	; Value: 0
	db 6	; Value: 3
	db 16	; Value: 8
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio5
	db 0	; Speed

	db 0	; Value: 0
	db 6	; Value: 3
	db 14	; Value: 7
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio6
	db 0	; Speed

	db 0	; Value: 0
	db 6	; Value: 3
	db 20	; Value: 10
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio7
	db 0	; Speed

	db 0	; Value: 0
	db 8	; Value: 4
	db 10	; Value: 5
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio8
	db 0	; Speed

	db 0	; Value: 0
	db 10	; Value: 5
	db 18	; Value: 9
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio9
	db 0	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 24	; Value: 12
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio10
	db 0	; Speed

	db 0	; Value: 0
	db 10	; Value: 5
	db 14	; Value: 7
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_Arpeggio11
	db 0	; Speed

	db 0	; Value: 0
	db 10	; Value: 5
	db 20	; Value: 10
	db 0 * 2 + 1	; Loops to index 0.
DayoftheTentacle_DisarkByteRegionEnd17

DayoftheTentacle_PitchIndexes
DayoftheTentacle_DisarkPointerRegionStart18
DayoftheTentacle_DisarkPointerRegionEnd18

DayoftheTentacle_DisarkByteRegionStart19
DayoftheTentacle_DisarkByteRegionEnd19

; Day of the Tentacle, Subsong 0.
; ----------------------------------

DayoftheTentacle_Subsong0
DayoftheTentacle_Subsong0DisarkPointerRegionStart0
	dw DayoftheTentacle_Subsong0_NoteIndexes	; Index table for the notes.
	dw DayoftheTentacle_Subsong0_TrackIndexes	; Index table for the Tracks.
DayoftheTentacle_Subsong0DisarkPointerRegionEnd0

DayoftheTentacle_Subsong0DisarkByteRegionStart1
	db 2	; Initial speed.

	db 1	; Most used instrument.
	db 3	; Second most used instrument.

	db 1	; Most used wait.
	db 3	; Second most used wait.

	db 35	; Default start note in tracks.
	db 10	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
DayoftheTentacle_Subsong0DisarkByteRegionEnd1

; The Linker.
DayoftheTentacle_Subsong0DisarkByteRegionStart2
; Pattern 0
	db 170	; State byte.
	db 95	; New height.
	db ((DayoftheTentacle_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track0 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 2, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track1 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 3, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track2 - ($ + 1)) & 255)

; Pattern 1
	db 168	; State byte.
	db ((DayoftheTentacle_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 1, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track3 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 2, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track4 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 3, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track5 - ($ + 1)) & 255)

; Pattern 2
	db 170	; State byte.
	db 47	; New height.
	db ((DayoftheTentacle_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track6 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 2, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track7 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 3, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track8 - ($ + 1)) & 255)

; Pattern 3
	db 168	; State byte.
	db ((DayoftheTentacle_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track10 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 2, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track11 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 3, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track9 - ($ + 1)) & 255)

; Pattern 4
DayoftheTentacle_Subsong0_Loop
	db 170	; State byte.
	db 71	; New height.
	db ((DayoftheTentacle_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track12 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 2, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track13 - ($ + 1)) & 255)
	db ((DayoftheTentacle_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 3, as an offset. Offset MSB, then LSB.
	db ((DayoftheTentacle_Subsong0_Track14 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
DayoftheTentacle_Subsong0DisarkByteRegionEnd2
DayoftheTentacle_Subsong0DisarkPointerRegionStart3
	dw DayoftheTentacle_Subsong0_Loop

DayoftheTentacle_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
DayoftheTentacle_Subsong0_TrackIndexes
DayoftheTentacle_Subsong0DisarkPointerRegionStart4
DayoftheTentacle_Subsong0DisarkPointerRegionEnd4

DayoftheTentacle_Subsong0DisarkByteRegionStart5
DayoftheTentacle_Subsong0_Track0
	db 12	; Note with effects flag.
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 22	;    Arpeggio table effect 1.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 210	; Primary instrument (1). Note reference (2). New wait (5).
	db 5	;   Escape wait value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (3).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (1).
	db 147	; Primary instrument (1). Note reference (3). Secondary wait (3).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (1).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 18	; Primary instrument (1). Note reference (2). 
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (1).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (3).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (1).
	db 158	; Primary instrument (1). New escaped note: 43. Secondary wait (3).
	db 43	;   Escape note value.
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track1
	db 176	; New instrument (2). Note reference (0). Secondary wait (3).
	db 2	;   Escape instrument value.
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 64	; Note reference (0). Primary wait (1).
	db 64	; Note reference (0). Primary wait (1).
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track2
	db 12	; Note with effects flag.
	db 161	; Secondary instrument (3). Note reference (1). Secondary wait (3).
	db 38	;    Arpeggio table effect 2.
	db 96	; Secondary instrument (3). Note reference (0). Primary wait (1).
	db 161	; Secondary instrument (3). Note reference (1). Secondary wait (3).
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 226	; Secondary instrument (3). Note reference (2). New wait (5).
	db 5	;   Escape wait value.
	db 101	; Secondary instrument (3). Note reference (5). Primary wait (1).
	db 162	; Secondary instrument (3). Note reference (2). Secondary wait (3).
	db 100	; Secondary instrument (3). Note reference (4). Primary wait (1).
	db 163	; Secondary instrument (3). Note reference (3). Secondary wait (3).
	db 98	; Secondary instrument (3). Note reference (2). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 99	; Secondary instrument (3). Note reference (3). Primary wait (1).
	db 161	; Secondary instrument (3). Note reference (1). Secondary wait (3).
	db 96	; Secondary instrument (3). Note reference (0). Primary wait (1).
	db 161	; Secondary instrument (3). Note reference (1). Secondary wait (3).
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 46	; Secondary instrument (3). New escaped note: 27. 
	db 27	;   Escape note value.
	db 111	; Secondary instrument (3). Same escaped note: 27. Primary wait (1).
	db 100	; Secondary instrument (3). Note reference (4). Primary wait (1).
	db 111	; Secondary instrument (3). Same escaped note: 27. Primary wait (1).
	db 100	; Secondary instrument (3). Note reference (4). Primary wait (1).
	db 99	; Secondary instrument (3). Note reference (3). Primary wait (1).
	db 100	; Secondary instrument (3). Note reference (4). Primary wait (1).
	db 99	; Secondary instrument (3). Note reference (3). Primary wait (1).
	db 110	; Secondary instrument (3). New escaped note: 33. Primary wait (1).
	db 33	;   Escape note value.
	db 98	; Secondary instrument (3). Note reference (2). Primary wait (1).
	db 224	; Secondary instrument (3). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track3
	db 12	; Note with effects flag.
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 22	;    Arpeggio table effect 1.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 210	; Primary instrument (1). Note reference (2). New wait (5).
	db 5	;   Escape wait value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (3).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (1).
	db 147	; Primary instrument (1). Note reference (3). Secondary wait (3).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (1).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (1).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (1).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (1).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (1).
	db 94	; Primary instrument (1). New escaped note: 43. Primary wait (1).
	db 43	;   Escape note value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (1).
	db 94	; Primary instrument (1). New escaped note: 48. Primary wait (1).
	db 48	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 50. Primary wait (1).
	db 50	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 52. New wait (127).
	db 52	;   Escape note value.
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track4
	db 176	; New instrument (5). Note reference (0). Secondary wait (3).
	db 5	;   Escape instrument value.
	db 112	; New instrument (2). Note reference (0). Primary wait (1).
	db 2	;   Escape instrument value.
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 176	; New instrument (4). Note reference (0). Secondary wait (3).
	db 4	;   Escape instrument value.
	db 112	; New instrument (2). Note reference (0). Primary wait (1).
	db 2	;   Escape instrument value.
	db 128	; Note reference (0). Secondary wait (3).
	db 112	; New instrument (5). Note reference (0). Primary wait (1).
	db 5	;   Escape instrument value.
	db 176	; New instrument (2). Note reference (0). Secondary wait (3).
	db 2	;   Escape instrument value.
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 112	; New instrument (5). Note reference (0). Primary wait (1).
	db 5	;   Escape instrument value.
	db 176	; New instrument (4). Note reference (0). Secondary wait (3).
	db 4	;   Escape instrument value.
	db 112	; New instrument (2). Note reference (0). Primary wait (1).
	db 2	;   Escape instrument value.
	db 128	; Note reference (0). Secondary wait (3).
	db 112	; New instrument (4). Note reference (0). Primary wait (1).
	db 4	;   Escape instrument value.
	db 176	; New instrument (5). Note reference (0). Secondary wait (3).
	db 5	;   Escape instrument value.
	db 64	; Note reference (0). Primary wait (1).
	db 176	; New instrument (2). Note reference (0). Secondary wait (3).
	db 2	;   Escape instrument value.
	db 112	; New instrument (5). Note reference (0). Primary wait (1).
	db 5	;   Escape instrument value.
	db 176	; New instrument (4). Note reference (0). Secondary wait (3).
	db 4	;   Escape instrument value.
	db 112	; New instrument (2). Note reference (0). Primary wait (1).
	db 2	;   Escape instrument value.
	db 128	; Note reference (0). Secondary wait (3).
	db 112	; New instrument (5). Note reference (0). Primary wait (1).
	db 5	;   Escape instrument value.
	db 176	; New instrument (4). Note reference (0). Secondary wait (3).
	db 4	;   Escape instrument value.
	db 64	; Note reference (0). Primary wait (1).
	db 176	; New instrument (2). Note reference (0). Secondary wait (3).
	db 2	;   Escape instrument value.
	db 112	; New instrument (4). Note reference (0). Primary wait (1).
	db 4	;   Escape instrument value.
	db 128	; Note reference (0). Secondary wait (3).
	db 64	; Note reference (0). Primary wait (1).
	db 128	; Note reference (0). Secondary wait (3).
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track5
	db 12	; Note with effects flag.
	db 161	; Secondary instrument (3). Note reference (1). Secondary wait (3).
	db 38	;    Arpeggio table effect 2.
	db 96	; Secondary instrument (3). Note reference (0). Primary wait (1).
	db 161	; Secondary instrument (3). Note reference (1). Secondary wait (3).
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 226	; Secondary instrument (3). Note reference (2). New wait (5).
	db 5	;   Escape wait value.
	db 101	; Secondary instrument (3). Note reference (5). Primary wait (1).
	db 162	; Secondary instrument (3). Note reference (2). Secondary wait (3).
	db 100	; Secondary instrument (3). Note reference (4). Primary wait (1).
	db 163	; Secondary instrument (3). Note reference (3). Secondary wait (3).
	db 98	; Secondary instrument (3). Note reference (2). Primary wait (1).
	db 160	; Secondary instrument (3). Note reference (0). Secondary wait (3).
	db 99	; Secondary instrument (3). Note reference (3). Primary wait (1).
	db 12	; Note with effects flag.
	db 182	; New instrument (9). Note reference (6). Secondary wait (3).
	db 9	;   Escape instrument value.
	db 54	;    Arpeggio table effect 3.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (3). Note reference (0). Primary wait (1).
	db 38	;    Arpeggio table effect 2.
	db 12	; Note with effects flag.
	db 134	; Note reference (6). Secondary wait (3).
	db 54	;    Arpeggio table effect 3.
	db 12	; Note with effects flag.
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 38	;    Arpeggio table effect 2.
	db 12	; Note with effects flag.
	db 136	; Note reference (8). Secondary wait (3).
	db 70	;    Arpeggio table effect 4.
	db 12	; Note with effects flag.
	db 97	; Secondary instrument (3). Note reference (1). Primary wait (1).
	db 38	;    Arpeggio table effect 2.
	db 12	; Note with effects flag.
	db 136	; Note reference (8). Secondary wait (3).
	db 70	;    Arpeggio table effect 4.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (3). Note reference (0). Primary wait (1).
	db 38	;    Arpeggio table effect 2.
	db 12	; Note with effects flag.
	db 72	; Note reference (8). Primary wait (1).
	db 86	;    Arpeggio table effect 5.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (3). Note reference (0). Primary wait (1).
	db 38	;    Arpeggio table effect 2.
	db 103	; Secondary instrument (3). Note reference (7). Primary wait (1).
	db 12	; Note with effects flag.
	db 72	; Note reference (8). Primary wait (1).
	db 86	;    Arpeggio table effect 5.
	db 12	; Note with effects flag.
	db 103	; Secondary instrument (3). Note reference (7). Primary wait (1).
	db 38	;    Arpeggio table effect 2.
	db 106	; Secondary instrument (3). Note reference (10). Primary wait (1).
	db 12	; Note with effects flag.
	db 72	; Note reference (8). Primary wait (1).
	db 102	;    Arpeggio table effect 6.
	db 12	; Note with effects flag.
	db 110	; Secondary instrument (3). New escaped note: 43. Primary wait (1).
	db 43	;   Escape note value.
	db 38	;    Arpeggio table effect 2.
	db 101	; Secondary instrument (3). Note reference (5). Primary wait (1).
	db 12	; Note with effects flag.
	db 72	; Note reference (8). Primary wait (1).
	db 102	;    Arpeggio table effect 6.
	db 12	; Note with effects flag.
	db 110	; Secondary instrument (3). New escaped note: 50. Primary wait (1).
	db 50	;   Escape note value.
	db 38	;    Arpeggio table effect 2.
	db 238	; Secondary instrument (3). New escaped note: 52. New wait (127).
	db 52	;   Escape note value.
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track6
	db 12	; Note with effects flag.
	db 246	; New instrument (6). Note reference (6). New wait (11).
	db 6	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 54	;    Arpeggio table effect 3.
	db 12	; Note with effects flag.
	db 182	; New instrument (10). Note reference (6). Secondary wait (3).
	db 10	;   Escape instrument value.
	db 118	;    Arpeggio table effect 7.
	db 198	; Note reference (6). New wait (5).
	db 5	;   Escape wait value.
	db 6	; Note reference (6). 
	db 6	; Note reference (6). 
	db 12	; Note with effects flag.
	db 9	; Note reference (9). 
	db 134	;    Arpeggio table effect 8.
	db 78	; New escaped note: 53. Primary wait (1).
	db 53	;   Escape note value.
	db 12	; Note with effects flag.
	db 206	; New escaped note: 52. New wait (127).
	db 52	;   Escape note value.
	db 127	;   Escape wait value.
	db 70	;    Arpeggio table effect 4.

DayoftheTentacle_Subsong0_Track7
	db 12	; Note with effects flag.
	db 240	; New instrument (7). Note reference (0). New wait (127).
	db 7	;   Escape instrument value.
	db 127	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.

DayoftheTentacle_Subsong0_Track8
	db 12	; Note with effects flag.
	db 241	; New instrument (8). Note reference (1). New wait (127).
	db 8	;   Escape instrument value.
	db 127	;   Escape wait value.
	db 150	;    Arpeggio table effect 9.

DayoftheTentacle_Subsong0_Track9
	db 12	; Note with effects flag.
	db 244	; New instrument (8). Note reference (4). New wait (9).
	db 8	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 150	;    Arpeggio table effect 9.
	db 2	; Note reference (2). 
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track10
	db 12	; Note with effects flag.
	db 249	; New instrument (6). Note reference (9). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 166	;    Arpeggio table effect 10.
	db 12	; Note with effects flag.
	db 14	; New escaped note: 50. 
	db 50	;   Escape note value.
	db 182	;    Arpeggio table effect 11.
	db 12	; Note with effects flag.
	db 206	; New escaped note: 48. New wait (127).
	db 48	;   Escape note value.
	db 127	;   Escape wait value.
	db 54	;    Arpeggio table effect 3.

DayoftheTentacle_Subsong0_Track11
	db 240	; New instrument (7). Note reference (0). New wait (27).
	db 7	;   Escape instrument value.
	db 27	;   Escape wait value.
	db 126	; New instrument (11). New escaped note: 59. Primary wait (1).
	db 59	;   Escape note value.
	db 11	;   Escape instrument value.
	db 201	; Note reference (9). New wait (5).
	db 5	;   Escape wait value.
	db 201	; Note reference (9). New wait (2).
	db 2	;   Escape wait value.
	db 11	; Note reference (11). 
	db 199	; Note reference (7). New wait (127).
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track12
	db 12	; Note with effects flag.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.

DayoftheTentacle_Subsong0_Track13
	db 255	; New instrument (11). Same escaped note: 35. New wait (127).
	db 11	;   Escape instrument value.
	db 127	;   Escape wait value.

DayoftheTentacle_Subsong0_Track14
	db 12	; Note with effects flag.
	db 193	; Note reference (1). New wait (127).
	db 127	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.

DayoftheTentacle_Subsong0DisarkByteRegionEnd5
; The note indexes.
DayoftheTentacle_Subsong0_NoteIndexes
DayoftheTentacle_Subsong0DisarkByteRegionStart6
	db 36	; Note for index 0.
	db 24	; Note for index 1.
	db 34	; Note for index 2.
	db 31	; Note for index 3.
	db 29	; Note for index 4.
	db 46	; Note for index 5.
	db 60	; Note for index 6.
	db 38	; Note for index 7.
	db 62	; Note for index 8.
	db 55	; Note for index 9.
	db 39	; Note for index 10.
	db 41	; Note for index 11.
DayoftheTentacle_Subsong0DisarkByteRegionEnd6

