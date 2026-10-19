; Hicks 4K 2019, Song part, encoded in the AKM (minimalist) format V0.


	dw Hicks4K2019_InstrumentIndexes	; Index table for the Instruments.
	dw 0	; Index table for the Arpeggios.
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw Hicks4K2019_Subsong0

; The Instrument indexes.
Hicks4K2019_InstrumentIndexes
	dw Hicks4K2019_Instrument0
	dw Hicks4K2019_Instrument1
	dw Hicks4K2019_Instrument2
	dw Hicks4K2019_Instrument3
	dw Hicks4K2019_Instrument4
	dw Hicks4K2019_Instrument5
	dw Hicks4K2019_Instrument6
	dw Hicks4K2019_Instrument7
	dw Hicks4K2019_Instrument8
	dw Hicks4K2019_Instrument9
	dw Hicks4K2019_Instrument10
	dw Hicks4K2019_Instrument11
	dw Hicks4K2019_Instrument12
	dw Hicks4K2019_Instrument13
	dw Hicks4K2019_Instrument14

; The Instrument.
Hicks4K2019_Instrument0
	db 255	; Speed.

Hicks4K2019_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument0Loop	; Loops.

Hicks4K2019_Instrument1
	db 0	; Speed.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument0Loop	; Loop to silence.

Hicks4K2019_Instrument2
	db 0	; Speed.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 93	; Volume: 7.
	dw -1	; Pitch: -1.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument0Loop	; Loop to silence.

Hicks4K2019_Instrument3
	db 6	; Speed.

Hicks4K2019_Instrument3Loop	db 248	; Volume: 15.
	db 1	; Noise.

	db 248	; Volume: 15.
	db 2	; Noise.

	db 248	; Volume: 15.
	db 3	; Noise.

	db 248	; Volume: 15.
	db 4	; Noise.

	db 248	; Volume: 15.
	db 5	; Noise.

	db 248	; Volume: 15.
	db 6	; Noise.

	db 248	; Volume: 15.
	db 7	; Noise.

	db 248	; Volume: 15.
	db 8	; Noise.

	db 248	; Volume: 15.
	db 9	; Noise.

	db 248	; Volume: 15.
	db 10	; Noise.

	db 248	; Volume: 15.
	db 11	; Noise.

	db 248	; Volume: 15.
	db 12	; Noise.

	db 248	; Volume: 15.
	db 13	; Noise.

	db 248	; Volume: 15.
	db 14	; Noise.

	db 248	; Volume: 15.
	db 15	; Noise.

	db 248	; Volume: 15.
	db 16	; Noise.

	db 248	; Volume: 15.
	db 17	; Noise.

	db 248	; Volume: 15.
	db 18	; Noise.

	db 248	; Volume: 15.
	db 19	; Noise.

	db 248	; Volume: 15.
	db 20	; Noise.

	db 248	; Volume: 15.
	db 21	; Noise.

	db 248	; Volume: 15.
	db 20	; Noise.

	db 248	; Volume: 15.
	db 19	; Noise.

	db 248	; Volume: 15.
	db 18	; Noise.

	db 248	; Volume: 15.
	db 17	; Noise.

	db 248	; Volume: 15.
	db 16	; Noise.

	db 248	; Volume: 15.
	db 15	; Noise.

	db 248	; Volume: 15.
	db 14	; Noise.

	db 248	; Volume: 15.
	db 13	; Noise.

	db 248	; Volume: 15.
	db 12	; Noise.

	db 248	; Volume: 15.
	db 11	; Noise.

	db 248	; Volume: 15.
	db 10	; Noise.

	db 248	; Volume: 15.
	db 9	; Noise.

	db 248	; Volume: 15.
	db 8	; Noise.

	db 248	; Volume: 15.
	db 7	; Noise.

	db 248	; Volume: 15.
	db 6	; Noise.

	db 248	; Volume: 15.
	db 5	; Noise.

	db 248	; Volume: 15.
	db 4	; Noise.

	db 248	; Volume: 15.
	db 3	; Noise.

	db 248	; Volume: 15.
	db 2	; Noise.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument3Loop	; Loops.

Hicks4K2019_Instrument4
	db 0	; Speed.

Hicks4K2019_Instrument4Loop	db 189	; Volume: 15.
	db 232	; Arpeggio: -12.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 232	; Arpeggio: -12.

	db 189	; Volume: 15.
	db 232	; Arpeggio: -12.

	db 61	; Volume: 15.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument4Loop	; Loops.

Hicks4K2019_Instrument5
	db 0	; Speed.

Hicks4K2019_Instrument5Loop	db 189	; Volume: 15.
	db 232	; Arpeggio: -12.

	db 125	; Volume: 15.
	dw -1	; Pitch: -1.

	db 125	; Volume: 15.
	dw -1	; Pitch: -1.

	db 189	; Volume: 15.
	db 232	; Arpeggio: -12.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument5Loop	; Loops.

Hicks4K2019_Instrument6
	db 1	; Speed.

Hicks4K2019_Instrument6Loop	db 53	; Volume: 13.

	db 181	; Volume: 13.
	db 232	; Arpeggio: -12.

	db 186, 12	; Arpeggio: 12.

	db 186, 12	; Arpeggio: 12.

	db 58
	db 186, 3	; Arpeggio: 3.

	db 186, 3	; Arpeggio: 3.

	db 186, 7	; Arpeggio: 7.

	db 186, 7	; Arpeggio: 7.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument6Loop	; Loops.

Hicks4K2019_Instrument7
	db 0	; Speed.

Hicks4K2019_Instrument7Loop	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 181	; Volume: 13.
	db 25	; Arpeggio: 12.
	db 16	; Noise: 16.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 15	; Noise: 15.

	db 61	; Volume: 15.

	db 181	; Volume: 13.
	db 25	; Arpeggio: 12.
	db 14	; Noise: 14.

	db 61	; Volume: 15.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 13	; Noise: 13.

	db 181	; Volume: 13.
	db 25	; Arpeggio: 12.
	db 12	; Noise: 12.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument7Loop	; Loops.

Hicks4K2019_Instrument8
	db 0	; Speed.

Hicks4K2019_Instrument8Loop	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 6	; Noise: 6.

	db 181	; Volume: 13.
	db 25	; Arpeggio: 12.
	db 5	; Noise: 5.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 181	; Volume: 13.
	db 25	; Arpeggio: 12.
	db 3	; Noise: 3.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 2	; Noise: 2.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument8Loop	; Loops.

Hicks4K2019_Instrument9
	db 0	; Speed.

Hicks4K2019_Instrument9Loop	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument9Loop	; Loops.

Hicks4K2019_Instrument10
	db 12	; Speed.

Hicks4K2019_Instrument10Loop	db 49	; Volume: 12.

	db 53	; Volume: 13.

	db 57	; Volume: 14.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 45	; Volume: 11.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument10Loop	; Loops.

Hicks4K2019_Instrument11
	db 1	; Speed.

	db 173	; Volume: 11.
	db 232	; Arpeggio: -12.

	db 45	; Volume: 11.

	db 49	; Volume: 12.

	db 177	; Volume: 12.
	db 232	; Arpeggio: -12.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 177	; Volume: 12.
	db 232	; Arpeggio: -12.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 173	; Volume: 11.
	db 232	; Arpeggio: -12.

	db 41	; Volume: 10.

	db 41	; Volume: 10.

	db 165	; Volume: 9.
	db 232	; Arpeggio: -12.

	db 37	; Volume: 9.

Hicks4K2019_Instrument11Loop	db 97	; Volume: 8.
	dw -1	; Pitch: -1.

	db 225	; Volume: 8.
	db 232	; Arpeggio: -12.
	dw -1	; Pitch: -1.

	db 33	; Volume: 8.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument11Loop	; Loops.

Hicks4K2019_Instrument12
	db 0	; Speed.

Hicks4K2019_Instrument12Loop	db 42
	db 4	; End the instrument.
	dw Hicks4K2019_Instrument12Loop	; Loops.

Hicks4K2019_Instrument13
	db 1	; Speed.

Hicks4K2019_Instrument13Loop	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 28	; Arpeggio: 14.

	db 189	; Volume: 15.
	db 4	; Arpeggio: 2.

	db 189	; Volume: 15.
	db 32	; Arpeggio: 16.

	db 189	; Volume: 15.
	db 8	; Arpeggio: 4.

	db 189	; Volume: 15.
	db 38	; Arpeggio: 19.

	db 189	; Volume: 15.
	db 14	; Arpeggio: 7.

	db 189	; Volume: 15.
	db 48	; Arpeggio: 24.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 189	; Volume: 15.
	db 38	; Arpeggio: 19.

	db 189	; Volume: 15.
	db 14	; Arpeggio: 7.

	db 189	; Volume: 15.
	db 32	; Arpeggio: 16.

	db 189	; Volume: 15.
	db 8	; Arpeggio: 4.

	db 189	; Volume: 15.
	db 28	; Arpeggio: 14.

	db 189	; Volume: 15.
	db 4	; Arpeggio: 2.

	db 189	; Volume: 15.
	db 24	; Arpeggio: 12.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 14	; Arpeggio: 7.

	db 189	; Volume: 15.
	db 246	; Arpeggio: -5.

	db 189	; Volume: 15.
	db 8	; Arpeggio: 4.

	db 189	; Volume: 15.
	db 240	; Arpeggio: -8.

	db 189	; Volume: 15.
	db 4	; Arpeggio: 2.

	db 189	; Volume: 15.
	db 236	; Arpeggio: -10.

	db 189	; Volume: 15.
	db 246	; Arpeggio: -5.

	db 189	; Volume: 15.
	db 222	; Arpeggio: -17.

	db 189	; Volume: 15.
	db 240	; Arpeggio: -8.

	db 189	; Volume: 15.
	db 216	; Arpeggio: -20.

	db 189	; Volume: 15.
	db 236	; Arpeggio: -10.

	db 189	; Volume: 15.
	db 212	; Arpeggio: -22.

	db 189	; Volume: 15.
	db 232	; Arpeggio: -12.

	db 189	; Volume: 15.
	db 208	; Arpeggio: -24.

	db 189	; Volume: 15.
	db 236	; Arpeggio: -10.

	db 189	; Volume: 15.
	db 212	; Arpeggio: -22.

	db 189	; Volume: 15.
	db 240	; Arpeggio: -8.

	db 189	; Volume: 15.
	db 216	; Arpeggio: -20.

	db 189	; Volume: 15.
	db 246	; Arpeggio: -5.

	db 189	; Volume: 15.
	db 222	; Arpeggio: -17.

	db 189	; Volume: 15.
	db 4	; Arpeggio: 2.

	db 189	; Volume: 15.
	db 236	; Arpeggio: -10.

	db 189	; Volume: 15.
	db 8	; Arpeggio: 4.

	db 189	; Volume: 15.
	db 240	; Arpeggio: -8.

	db 189	; Volume: 15.
	db 14	; Arpeggio: 7.

	db 189	; Volume: 15.
	db 246	; Arpeggio: -5.

	db 4	; End the instrument.
	dw Hicks4K2019_Instrument13Loop	; Loops.

Hicks4K2019_Instrument14
	db 0	; Speed.

Hicks4K2019_Instrument14Loop	db 58
	db 4	; End the instrument.
	dw Hicks4K2019_Instrument14Loop	; Loops.

Hicks4K2019_ArpeggioIndexes


Hicks4K2019_PitchIndexes


; Hicks 4K 2019, Subsong 0.
; ----------------------------------

Hicks4K2019_Subsong0
	dw Hicks4K2019_Subsong0_NoteIndexes	; Index table for the notes.
	dw Hicks4K2019_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 8	; Initial speed.

	db 1	; Most used instrument.
	db 2	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 36	; Default start note in tracks.
	db 13	; Default start instrument in tracks.
	db 3	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
	db 170	; State byte.
	db 15	; New height.
	db 128	; New track (0) for channel 1, as a reference (index 0).
	db ((Hicks4K2019_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track1 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track3 - ($ + 1)) & 255)

; Pattern 1
	db 128	; State byte.
	db ((Hicks4K2019_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track17 - ($ + 1)) & 255)

; Pattern 2
	db 160	; State byte.
	db ((Hicks4K2019_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track4 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track5 - ($ + 1)) & 255)

; Pattern 3
	db 160	; State byte.
	db ((Hicks4K2019_Subsong0_Track34 - ($ + 2)) & #ff00) / 256	; New track (34) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track34 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track35 - ($ + 2)) & #ff00) / 256	; New track (35) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track35 - ($ + 1)) & 255)

; Pattern 4
	db 240	; State byte.
	db -3	; New transposition on channel 2.
	db 132	; New track (6) for channel 2, as a reference (index 4).
	db -3	; New transposition on channel 3.
	db 129	; New track (7) for channel 3, as a reference (index 1).

; Pattern 5
	db 160	; State byte.
	db 130	; New track (36) for channel 2, as a reference (index 2).
	db 131	; New track (37) for channel 3, as a reference (index 3).

; Pattern 6
	db 240	; State byte.
	db -8	; New transposition on channel 2.
	db 132	; New track (6) for channel 2, as a reference (index 4).
	db -8	; New transposition on channel 3.
	db 129	; New track (7) for channel 3, as a reference (index 1).

; Pattern 7
	db 160	; State byte.
	db 130	; New track (36) for channel 2, as a reference (index 2).
	db 131	; New track (37) for channel 3, as a reference (index 3).

; Pattern 8
	db 240	; State byte.
	db 4	; New transposition on channel 2.
	db 132	; New track (6) for channel 2, as a reference (index 4).
	db 4	; New transposition on channel 3.
	db 129	; New track (7) for channel 3, as a reference (index 1).

; Pattern 9
	db 160	; State byte.
	db 130	; New track (36) for channel 2, as a reference (index 2).
	db 131	; New track (37) for channel 3, as a reference (index 3).

; Pattern 10
	db 241	; State byte.
	db 7	; New speed (>0).
	db 0	; New transposition on channel 2.
	db ((Hicks4K2019_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track15 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((Hicks4K2019_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track16 - ($ + 1)) & 255)

; Pattern 11
	db 161	; State byte.
	db 6	; New speed (>0).
	db ((Hicks4K2019_Subsong0_Track20 - ($ + 2)) & #ff00) / 256	; New track (20) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track20 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track21 - ($ + 2)) & #ff00) / 256	; New track (21) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track21 - ($ + 1)) & 255)

; Pattern 12
	db 171	; State byte.
	db 11	; New speed (>0).
	db 24	; New height.
	db ((Hicks4K2019_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track17 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track18 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track19 - ($ + 2)) & #ff00) / 256	; New track (19) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track19 - ($ + 1)) & 255)

; Pattern 13
	db 170	; State byte.
	db 35	; New height.
	db ((Hicks4K2019_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track2 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track8 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track9 - ($ + 1)) & 255)

; Pattern 14
	db 170	; State byte.
	db 39	; New height.
	db ((Hicks4K2019_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track10 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track11 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track12 - ($ + 1)) & 255)

; Pattern 15
	db 170	; State byte.
	db 35	; New height.
	db ((Hicks4K2019_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track2 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track8 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track9 - ($ + 1)) & 255)

; Pattern 16
	db 170	; State byte.
	db 20	; New height.
	db ((Hicks4K2019_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track10 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track11 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track12 - ($ + 1)) & 255)

; Pattern 17
	db 170	; State byte.
	db 53	; New height.
	db ((Hicks4K2019_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track23 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track22 - ($ + 2)) & #ff00) / 256	; New track (22) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track22 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track24 - ($ + 2)) & #ff00) / 256	; New track (24) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track24 - ($ + 1)) & 255)

; Pattern 18
	db 171	; State byte.
	db 24	; New speed (>0).
	db 24	; New height.
	db ((Hicks4K2019_Subsong0_Track25 - ($ + 2)) & #ff00) / 256	; New track (25) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track25 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track26 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track27 - ($ + 2)) & #ff00) / 256	; New track (27) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track27 - ($ + 1)) & 255)

; Pattern 19
	db 160	; State byte.
	db ((Hicks4K2019_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track13 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track14 - ($ + 1)) & 255)

; Pattern 20
	db 170	; State byte.
	db 11	; New height.
	db ((Hicks4K2019_Subsong0_Track28 - ($ + 2)) & #ff00) / 256	; New track (28) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track28 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track29 - ($ + 2)) & #ff00) / 256	; New track (29) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track29 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track30 - ($ + 2)) & #ff00) / 256	; New track (30) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track30 - ($ + 1)) & 255)

; Pattern 21
Hicks4K2019_Subsong0_Loop
	db 170	; State byte.
	db 127	; New height.
	db ((Hicks4K2019_Subsong0_Track31 - ($ + 2)) & #ff00) / 256	; New track (31) for channel 1, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track31 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track32 - ($ + 2)) & #ff00) / 256	; New track (32) for channel 2, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track32 - ($ + 1)) & 255)
	db ((Hicks4K2019_Subsong0_Track33 - ($ + 2)) & #ff00) / 256	; New track (33) for channel 3, as an offset. Offset MSB, then LSB.
	db ((Hicks4K2019_Subsong0_Track33 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw Hicks4K2019_Subsong0_Loop

; The indexes of the tracks.
Hicks4K2019_Subsong0_TrackIndexes
	dw Hicks4K2019_Subsong0_Track0	; Track 0, index 0.
	dw Hicks4K2019_Subsong0_Track7	; Track 7, index 1.
	dw Hicks4K2019_Subsong0_Track36	; Track 36, index 2.
	dw Hicks4K2019_Subsong0_Track37	; Track 37, index 3.
	dw Hicks4K2019_Subsong0_Track6	; Track 6, index 4.

Hicks4K2019_Subsong0_Track0
	db 12	; Note with effects flag
	db 94	; Primary instrument (1). New escaped note: 84. Primary wait (0).
	db 84	;   Escape note value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 94	; Primary instrument (1). New escaped note: 82. Primary wait (0).
	db 82	;   Escape note value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.

Hicks4K2019_Subsong0_Track1
	db 12	; Note with effects flag
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 97	; Secondary instrument (2). Note reference (1). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 110	; Secondary instrument (2). New escaped note: 84. Primary wait (0).
	db 84	;   Escape note value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 97	; Secondary instrument (2). Note reference (1). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 97	; Secondary instrument (2). Note reference (1). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 97	; Secondary instrument (2). Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 97	; Secondary instrument (2). Note reference (1). Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 12	; Note with effects flag
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 104	; Secondary instrument (2). Note reference (8). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 103	; Secondary instrument (2). Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 110	; Secondary instrument (2). New escaped note: 82. Primary wait (0).
	db 82	;   Escape note value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag
	db 103	; Secondary instrument (2). Note reference (7). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 232	; Secondary instrument (2). Note reference (8). New wait (127).
	db 127	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.

Hicks4K2019_Subsong0_Track2
	db 12	; Note with effects flag
	db 190	; New instrument (7). New escaped note: 66. Secondary wait (1).
	db 66	;   Escape note value.
	db 7	;   Escape instrument value.
	db 146	;    Volume effect, with inverted volume: 9.
	db 221	; Effect only. New wait (2).
	db 2	;   Escape wait value.
	db 130	;    Volume effect, with inverted volume: 8.
	db 93	; Effect only. Primary wait (0).
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 29	; Effect only. 
	db 82	;    Volume effect, with inverted volume: 5.
	db 157	; Effect only. Secondary wait (1).
	db 66	;    Volume effect, with inverted volume: 4.
	db 157	; Effect only. Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 93	; Effect only. Primary wait (0).
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 12	; Note with effects flag
	db 78	; New escaped note: 65. Primary wait (0).
	db 65	;   Escape note value.
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 221	; Effect only. New wait (5).
	db 5	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 221	; Effect only. New wait (3).
	db 3	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 114	;    Volume effect, with inverted volume: 7.

Hicks4K2019_Subsong0_Track3
	db 12	; Note with effects flag
	db 240	; New instrument (3). Note reference (0). New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.
	db 162	;    Volume effect, with inverted volume: 10.

Hicks4K2019_Subsong0_Track4
	db 12	; Note with effects flag
	db 242	; New instrument (4). Note reference (2). New wait (2).
	db 4	;   Escape instrument value.
	db 2	;   Escape wait value.
	db 130	;    Volume effect, with inverted volume: 8.
	db 221	; Effect only. New wait (3).
	db 3	;   Escape wait value.
	db 130	;    Volume effect, with inverted volume: 8.
	db 29	; Effect only. 
	db 114	;    Volume effect, with inverted volume: 7.
	db 29	; Effect only. 
	db 98	;    Volume effect, with inverted volume: 6.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.

Hicks4K2019_Subsong0_Track5
	db 12	; Note with effects flag
	db 50	; New instrument (5). Note reference (2). 
	db 5	;   Escape instrument value.
	db 146	;    Volume effect, with inverted volume: 9.
	db 29	; Effect only. 
	db 130	;    Volume effect, with inverted volume: 8.
	db 29	; Effect only. 
	db 114	;    Volume effect, with inverted volume: 7.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.

Hicks4K2019_Subsong0_Track6
	db 12	; Note with effects flag
	db 242	; New instrument (4). Note reference (2). New wait (5).
	db 4	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 29	; Effect only. 
	db 66	;    Volume effect, with inverted volume: 4.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.

Hicks4K2019_Subsong0_Track7
	db 12	; Note with effects flag
	db 242	; New instrument (5). Note reference (2). New wait (6).
	db 5	;   Escape instrument value.
	db 6	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.
	db 29	; Effect only. 
	db 82	;    Volume effect, with inverted volume: 5.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.

Hicks4K2019_Subsong0_Track8
	db 244	; New instrument (6). Note reference (4). New wait (16).
	db 6	;   Escape instrument value.
	db 16	;   Escape wait value.
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track9
	db 205	; New wait (2).
	db 2	;   Escape wait value.
	db 29	; Effect only. 
	db 114	;    Volume effect, with inverted volume: 7.
	db 157	; Effect only. Secondary wait (1).
	db 130	;    Volume effect, with inverted volume: 8.
	db 157	; Effect only. Secondary wait (1).
	db 146	;    Volume effect, with inverted volume: 9.
	db 12	; Note with effects flag
	db 126	; New instrument (8). New escaped note: 63. Primary wait (0).
	db 63	;   Escape note value.
	db 8	;   Escape instrument value.
	db 162	;    Volume effect, with inverted volume: 10.
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 29	; Effect only. 
	db 50	;    Volume effect, with inverted volume: 3.
	db 157	; Effect only. Secondary wait (1).
	db 66	;    Volume effect, with inverted volume: 4.
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 93	; Effect only. Primary wait (0).
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 146	;    Volume effect, with inverted volume: 9.

Hicks4K2019_Subsong0_Track10
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 221	; Effect only. New wait (4).
	db 4	;   Escape wait value.
	db 146	;    Volume effect, with inverted volume: 9.
	db 221	; Effect only. New wait (5).
	db 5	;   Escape wait value.
	db 162	;    Volume effect, with inverted volume: 10.
	db 12	; Note with effects flag
	db 126	; New instrument (7). New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 7	;   Escape instrument value.
	db 98	;    Volume effect, with inverted volume: 6.
	db 157	; Effect only. Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 157	; Effect only. Secondary wait (1).
	db 66	;    Volume effect, with inverted volume: 4.
	db 157	; Effect only. Secondary wait (1).
	db 50	;    Volume effect, with inverted volume: 3.
	db 221	; Effect only. New wait (2).
	db 2	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.
	db 29	; Effect only. 
	db 82	;    Volume effect, with inverted volume: 5.
	db 157	; Effect only. Secondary wait (1).
	db 98	;    Volume effect, with inverted volume: 6.
	db 157	; Effect only. Secondary wait (1).
	db 114	;    Volume effect, with inverted volume: 7.
	db 157	; Effect only. Secondary wait (1).
	db 130	;    Volume effect, with inverted volume: 8.
	db 221	; Effect only. New wait (3).
	db 3	;   Escape wait value.
	db 146	;    Volume effect, with inverted volume: 9.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 162	;    Volume effect, with inverted volume: 10.

Hicks4K2019_Subsong0_Track11
	db 250	; New instrument (6). Note reference (10). New wait (18).
	db 6	;   Escape instrument value.
	db 18	;   Escape wait value.
	db 201	; Note reference (9). New wait (10).
	db 10	;   Escape wait value.
	db 196	; Note reference (4). New wait (4).
	db 4	;   Escape wait value.
	db 206	; New escaped note: 26. New wait (127).
	db 26	;   Escape note value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track12
	db 12	; Note with effects flag
	db 126	; New instrument (8). New escaped note: 71. Primary wait (0).
	db 71	;   Escape note value.
	db 8	;   Escape instrument value.
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 157	; Effect only. Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 157	; Effect only. Secondary wait (1).
	db 66	;    Volume effect, with inverted volume: 4.
	db 157	; Effect only. Secondary wait (1).
	db 50	;    Volume effect, with inverted volume: 3.
	db 221	; Effect only. New wait (4).
	db 4	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 157	; Effect only. Secondary wait (1).
	db 98	;    Volume effect, with inverted volume: 6.
	db 157	; Effect only. Secondary wait (1).
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 12	; Note with effects flag
	db 139	; Note reference (11). Secondary wait (1).
	db 98	;    Volume effect, with inverted volume: 6.
	db 157	; Effect only. Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 221	; Effect only. New wait (2).
	db 2	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.
	db 29	; Effect only. 
	db 82	;    Volume effect, with inverted volume: 5.
	db 29	; Effect only. 
	db 66	;    Volume effect, with inverted volume: 4.
	db 221	; Effect only. New wait (5).
	db 5	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.

Hicks4K2019_Subsong0_Track13
	db 254	; New instrument (14). New escaped note: 26. New wait (11).
	db 26	;   Escape note value.
	db 14	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 206	; New escaped note: 29. New wait (4).
	db 29	;   Escape note value.
	db 4	;   Escape wait value.
	db 196	; Note reference (4). New wait (3).
	db 3	;   Escape wait value.
	db 206	; New escaped note: 36. New wait (127).
	db 36	;   Escape note value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track14
	db 12	; Note with effects flag
	db 197	; Note reference (5). New wait (11).
	db 11	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.
	db 206	; New escaped note: 53. New wait (4).
	db 53	;   Escape note value.
	db 4	;   Escape wait value.
	db 12	; Note with effects flag
	db 206	; New escaped note: 51. New wait (3).
	db 51	;   Escape note value.
	db 3	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.

Hicks4K2019_Subsong0_Track15
	db 12	; Note with effects flag
	db 242	; New instrument (9). Note reference (2). New wait (7).
	db 9	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.
	db 34	;    Volume effect, with inverted volume: 2.

Hicks4K2019_Subsong0_Track16
	db 12	; Note with effects flag
	db 242	; New instrument (5). Note reference (2). New wait (7).
	db 5	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.
	db 12	; Note with effects flag
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.

Hicks4K2019_Subsong0_Track17
	db 205	; New wait (127).
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track18
	db 12	; Note with effects flag
	db 254	; New instrument (9). New escaped note: 29. New wait (12).
	db 29	;   Escape note value.
	db 9	;   Escape instrument value.
	db 12	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 93	; Effect only. Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 93	; Effect only. Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 93	; Effect only. Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 93	; Effect only. Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 93	; Effect only. Primary wait (0).
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 93	; Effect only. Primary wait (0).
	db 146	;    Volume effect, with inverted volume: 9.
	db 93	; Effect only. Primary wait (0).
	db 162	;    Volume effect, with inverted volume: 10.
	db 93	; Effect only. Primary wait (0).
	db 178	;    Volume effect, with inverted volume: 11.
	db 12	; Note with effects flag
	db 246	; New instrument (0). Note reference (6). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.

Hicks4K2019_Subsong0_Track19
	db 12	; Note with effects flag
	db 254	; New instrument (5). New escaped note: 29. New wait (12).
	db 29	;   Escape note value.
	db 5	;   Escape instrument value.
	db 12	;   Escape wait value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 93	; Effect only. Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 93	; Effect only. Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 93	; Effect only. Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 93	; Effect only. Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 93	; Effect only. Primary wait (0).
	db 114	;    Volume effect, with inverted volume: 7.
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 93	; Effect only. Primary wait (0).
	db 146	;    Volume effect, with inverted volume: 9.
	db 93	; Effect only. Primary wait (0).
	db 162	;    Volume effect, with inverted volume: 10.
	db 93	; Effect only. Primary wait (0).
	db 178	;    Volume effect, with inverted volume: 11.
	db 246	; New instrument (0). Note reference (6). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track20
	db 12	; Note with effects flag
	db 255	; New instrument (9). Same escaped note: 36. New wait (7).
	db 9	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 202	; Note reference (10). New wait (127).
	db 127	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.

Hicks4K2019_Subsong0_Track21
	db 12	; Note with effects flag
	db 255	; New instrument (5). Same escaped note: 36. New wait (7).
	db 5	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag
	db 202	; Note reference (10). New wait (127).
	db 127	;   Escape wait value.
	db 18	;    Volume effect, with inverted volume: 1.

Hicks4K2019_Subsong0_Track22
	db 205	; New wait (8).
	db 8	;   Escape wait value.
	db 254	; New instrument (6). New escaped note: 39. New wait (4).
	db 39	;   Escape note value.
	db 6	;   Escape instrument value.
	db 4	;   Escape wait value.
	db 195	; Note reference (3). New wait (12).
	db 12	;   Escape wait value.
	db 196	; Note reference (4). New wait (4).
	db 4	;   Escape wait value.
	db 157	; Effect only. Secondary wait (1).
	db 18	;    Volume effect, with inverted volume: 1.
	db 157	; Effect only. Secondary wait (1).
	db 34	;    Volume effect, with inverted volume: 2.
	db 157	; Effect only. Secondary wait (1).
	db 50	;    Volume effect, with inverted volume: 3.
	db 157	; Effect only. Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 114	;    Volume effect, with inverted volume: 7.
	db 221	; Effect only. New wait (7).
	db 7	;   Escape wait value.
	db 242	;    Volume effect, with inverted volume: 15.
	db 246	; New instrument (0). Note reference (6). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track23
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 12	; Note with effects flag
	db 249	; New instrument (7). Note reference (9). New wait (2).
	db 7	;   Escape instrument value.
	db 2	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 157	; Effect only. Secondary wait (1).
	db 66	;    Volume effect, with inverted volume: 4.
	db 157	; Effect only. Secondary wait (1).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 142	; New escaped note: 39. Secondary wait (1).
	db 39	;   Escape note value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 29	; Effect only. 
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag
	db 195	; Note reference (3). New wait (7).
	db 7	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 157	; Effect only. Secondary wait (1).
	db 18	;    Volume effect, with inverted volume: 1.
	db 157	; Effect only. Secondary wait (1).
	db 34	;    Volume effect, with inverted volume: 2.
	db 93	; Effect only. Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag
	db 244	; New instrument (10). Note reference (4). New wait (14).
	db 10	;   Escape instrument value.
	db 14	;   Escape wait value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 157	; Effect only. Secondary wait (1).
	db 50	;    Volume effect, with inverted volume: 3.
	db 157	; Effect only. Secondary wait (1).
	db 66	;    Volume effect, with inverted volume: 4.
	db 157	; Effect only. Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 93	; Effect only. Primary wait (0).
	db 130	;    Volume effect, with inverted volume: 8.
	db 93	; Effect only. Primary wait (0).
	db 162	;    Volume effect, with inverted volume: 10.
	db 93	; Effect only. Primary wait (0).
	db 194	;    Volume effect, with inverted volume: 12.
	db 246	; New instrument (0). Note reference (6). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track24
	db 157	; Effect only. Secondary wait (1).
	db 82	;    Volume effect, with inverted volume: 5.
	db 221	; Effect only. New wait (2).
	db 2	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.
	db 29	; Effect only. 
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 157	; Effect only. Secondary wait (1).
	db 50	;    Volume effect, with inverted volume: 3.
	db 157	; Effect only. Secondary wait (1).
	db 34	;    Volume effect, with inverted volume: 2.
	db 93	; Effect only. Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 221	; Effect only. New wait (8).
	db 8	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 93	; Effect only. Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 93	; Effect only. Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 93	; Effect only. Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 93	; Effect only. Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 93	; Effect only. Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 93	; Effect only. Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 157	; Effect only. Secondary wait (1).
	db 114	;    Volume effect, with inverted volume: 7.
	db 157	; Effect only. Secondary wait (1).
	db 130	;    Volume effect, with inverted volume: 8.
	db 157	; Effect only. Secondary wait (1).
	db 146	;    Volume effect, with inverted volume: 9.
	db 93	; Effect only. Primary wait (0).
	db 162	;    Volume effect, with inverted volume: 10.
	db 93	; Effect only. Primary wait (0).
	db 178	;    Volume effect, with inverted volume: 11.
	db 93	; Effect only. Primary wait (0).
	db 194	;    Volume effect, with inverted volume: 12.
	db 93	; Effect only. Primary wait (0).
	db 210	;    Volume effect, with inverted volume: 13.
	db 93	; Effect only. Primary wait (0).
	db 226	;    Volume effect, with inverted volume: 14.
	db 246	; New instrument (0). Note reference (6). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track25
	db 12	; Note with effects flag
	db 254	; New instrument (11). New escaped note: 69. New wait (5).
	db 69	;   Escape note value.
	db 11	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 11	; Note reference (11). 
	db 192	; Note reference (0). New wait (4).
	db 4	;   Escape wait value.
	db 203	; Note reference (11). New wait (3).
	db 3	;   Escape wait value.
	db 206	; New escaped note: 67. New wait (127).
	db 67	;   Escape note value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track26
	db 12	; Note with effects flag
	db 254	; New instrument (12). New escaped note: 14. New wait (11).
	db 14	;   Escape note value.
	db 12	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 206	; New escaped note: 17. New wait (4).
	db 17	;   Escape note value.
	db 4	;   Escape wait value.
	db 206	; New escaped note: 15. New wait (127).
	db 15	;   Escape note value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track27
	db 12	; Note with effects flag
	db 5	; Note reference (5). 
	db 162	;    Volume effect, with inverted volume: 10.
	db 29	; Effect only. 
	db 146	;    Volume effect, with inverted volume: 9.
	db 29	; Effect only. 
	db 130	;    Volume effect, with inverted volume: 8.
	db 206	; New escaped note: 53. New wait (2).
	db 53	;   Escape note value.
	db 2	;   Escape wait value.
	db 157	; Effect only. Secondary wait (1).
	db 114	;    Volume effect, with inverted volume: 7.
	db 14	; New escaped note: 51. 
	db 51	;   Escape note value.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.

Hicks4K2019_Subsong0_Track28
	db 12	; Note with effects flag
	db 206	; New escaped note: 62. New wait (127).
	db 62	;   Escape note value.
	db 127	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.

Hicks4K2019_Subsong0_Track29
	db 243	; New instrument (14). Note reference (3). New wait (127).
	db 14	;   Escape instrument value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track30
	db 12	; Note with effects flag
	db 69	; Note reference (5). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 197	; Note reference (5). New wait (127).
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track31
	db 12	; Note with effects flag
	db 197	; Note reference (5). New wait (127).
	db 127	;   Escape wait value.
	db 146	;    Volume effect, with inverted volume: 9.

Hicks4K2019_Subsong0_Track32
	db 254	; New instrument (12). New escaped note: 14. New wait (127).
	db 14	;   Escape note value.
	db 12	;   Escape instrument value.
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track33
	db 12	; Note with effects flag
	db 131	; Note reference (3). Secondary wait (1).
	db 146	;    Volume effect, with inverted volume: 9.
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.

Hicks4K2019_Subsong0_Track34
	db 205	; New wait (2).
	db 2	;   Escape wait value.
	db 221	; Effect only. New wait (4).
	db 4	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.
	db 221	; Effect only. New wait (3).
	db 3	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.

Hicks4K2019_Subsong0_Track35
	db 77	; Primary wait (0).
	db 221	; Effect only. New wait (5).
	db 5	;   Escape wait value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 29	; Effect only. 
	db 98	;    Volume effect, with inverted volume: 6.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 114	;    Volume effect, with inverted volume: 7.

Hicks4K2019_Subsong0_Track36
	db 205	; New wait (4).
	db 4	;   Escape wait value.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.

Hicks4K2019_Subsong0_Track37
	db 13
	db 221	; Effect only. New wait (8).
	db 8	;   Escape wait value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 66	;    Volume effect, with inverted volume: 4.

; The note indexes.
Hicks4K2019_Subsong0_NoteIndexes
	db 72	; Note for index 0.
	db 77	; Note for index 1.
	db 37	; Note for index 2.
	db 38	; Note for index 3.
	db 27	; Note for index 4.
	db 50	; Note for index 5.
	db 48	; Note for index 6.
	db 80	; Note for index 7.
	db 79	; Note for index 8.
	db 34	; Note for index 9.
	db 32	; Note for index 10.
	db 70	; Note for index 11.

