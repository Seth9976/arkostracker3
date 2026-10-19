; "Hydrofool" 1987 Gargoyle Games, Song part, encoded in the AKM (minimalist) format V0.



	dw mySong_InstrumentIndexes	; Index table for the Instruments.
	dw 0	; Index table for the Arpeggios.
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw mySong_Subsong0

; The Instrument indexes.
mySong_InstrumentIndexes
	dw mySong_Instrument0
	dw mySong_Instrument1
	dw mySong_Instrument2
	dw mySong_Instrument3
	dw mySong_Instrument4
	dw mySong_Instrument5
	dw mySong_Instrument6
	dw mySong_Instrument7
	dw mySong_Instrument8
	dw mySong_Instrument9
	dw mySong_Instrument10
	dw mySong_Instrument11
	dw mySong_Instrument12
	dw mySong_Instrument13
	dw mySong_Instrument14
	dw mySong_Instrument15
	dw mySong_Instrument16
	dw mySong_Instrument17
	dw mySong_Instrument18
	dw mySong_Instrument19
	dw mySong_Instrument20
	dw mySong_Instrument21

; The Instrument.
mySong_Instrument0
	db 255	; Speed.

mySong_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loops.

mySong_Instrument1
	db 0	; Speed.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument2
	db 0	; Speed.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument3
	db 0	; Speed.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 185	; Volume: 14.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 177	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 173	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 173	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 169	; Volume: 10.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 165	; Volume: 9.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 165	; Volume: 9.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 161	; Volume: 8.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 157	; Volume: 7.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 157	; Volume: 7.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 153	; Volume: 6.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 149	; Volume: 5.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 149	; Volume: 5.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 145	; Volume: 4.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 141	; Volume: 3.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 141	; Volume: 3.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 137	; Volume: 2.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 133	; Volume: 1.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument4
	db 0	; Speed.

mySong_Instrument4Loop	db 57	; Volume: 14.

	db 4	; End the instrument.
	dw mySong_Instrument4Loop	; Loops.

mySong_Instrument5
	db 0	; Speed.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument6
	db 0	; Speed.

mySong_Instrument6Loop	db 37	; Volume: 9.

	db 4	; End the instrument.
	dw mySong_Instrument6Loop	; Loops.

mySong_Instrument7
	db 0	; Speed.

mySong_Instrument7Loop	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 6	; Arpeggio: 3.

	db 57	; Volume: 14.

	db 4	; End the instrument.
	dw mySong_Instrument7Loop	; Loops.

mySong_Instrument8
	db 0	; Speed.

	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 6	; Arpeggio: 3.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 177	; Volume: 12.
	db 6	; Arpeggio: 3.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 169	; Volume: 10.
	db 6	; Arpeggio: 3.

	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 161	; Volume: 8.
	db 6	; Arpeggio: 3.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 153	; Volume: 6.
	db 6	; Arpeggio: 3.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 145	; Volume: 4.
	db 6	; Arpeggio: 3.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 137	; Volume: 2.
	db 6	; Arpeggio: 3.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument9
	db 0	; Speed.

mySong_Instrument9Loop	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 8	; Arpeggio: 4.

	db 57	; Volume: 14.

	db 4	; End the instrument.
	dw mySong_Instrument9Loop	; Loops.

mySong_Instrument10
	db 0	; Speed.

	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 8	; Arpeggio: 4.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 177	; Volume: 12.
	db 8	; Arpeggio: 4.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 169	; Volume: 10.
	db 8	; Arpeggio: 4.

	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 161	; Volume: 8.
	db 8	; Arpeggio: 4.

	db 29	; Volume: 7.

	db 29	; Volume: 7.

	db 153	; Volume: 6.
	db 8	; Arpeggio: 4.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 145	; Volume: 4.
	db 8	; Arpeggio: 4.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 137	; Volume: 2.
	db 8	; Arpeggio: 4.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument11
	db 0	; Speed.

mySong_Instrument11Loop	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 24	; Arpeggio: 12.

	db 4	; End the instrument.
	dw mySong_Instrument11Loop	; Loops.

mySong_Instrument12
	db 0	; Speed.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 181	; Volume: 13.
	db 24	; Arpeggio: 12.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 173	; Volume: 11.
	db 24	; Arpeggio: 12.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 165	; Volume: 9.
	db 24	; Arpeggio: 12.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 24	; Arpeggio: 12.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 149	; Volume: 5.
	db 24	; Arpeggio: 12.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 145	; Volume: 4.
	db 24	; Arpeggio: 12.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 137	; Volume: 2.
	db 24	; Arpeggio: 12.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument13
	db 0	; Speed.

mySong_Instrument13Loop	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 165	; Volume: 9.
	db 24	; Arpeggio: 12.

	db 4	; End the instrument.
	dw mySong_Instrument13Loop	; Loops.

mySong_Instrument14
	db 0	; Speed.

mySong_Instrument14Loop	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 6	; Arpeggio: 3.

	db 185	; Volume: 14.
	db 16	; Arpeggio: 8.

	db 4	; End the instrument.
	dw mySong_Instrument14Loop	; Loops.

mySong_Instrument15
	db 0	; Speed.

mySong_Instrument15Loop	db 49	; Volume: 12.

	db 177	; Volume: 12.
	db 6	; Arpeggio: 3.

	db 177	; Volume: 12.
	db 16	; Arpeggio: 8.

	db 4	; End the instrument.
	dw mySong_Instrument15Loop	; Loops.

mySong_Instrument16
	db 0	; Speed.

mySong_Instrument16Loop	db 37	; Volume: 9.

	db 165	; Volume: 9.
	db 6	; Arpeggio: 3.

	db 165	; Volume: 9.
	db 16	; Arpeggio: 8.

	db 4	; End the instrument.
	dw mySong_Instrument16Loop	; Loops.

mySong_Instrument17
	db 0	; Speed.

	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 6	; Arpeggio: 3.

	db 181	; Volume: 13.
	db 16	; Arpeggio: 8.

	db 49	; Volume: 12.

	db 177	; Volume: 12.
	db 6	; Arpeggio: 3.

	db 173	; Volume: 11.
	db 16	; Arpeggio: 8.

	db 41	; Volume: 10.

	db 169	; Volume: 10.
	db 6	; Arpeggio: 3.

	db 165	; Volume: 9.
	db 16	; Arpeggio: 8.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 6	; Arpeggio: 3.

	db 157	; Volume: 7.
	db 16	; Arpeggio: 8.

	db 25	; Volume: 6.

	db 149	; Volume: 5.
	db 6	; Arpeggio: 3.

	db 149	; Volume: 5.
	db 16	; Arpeggio: 8.

	db 17	; Volume: 4.

	db 141	; Volume: 3.
	db 6	; Arpeggio: 3.

	db 141	; Volume: 3.
	db 16	; Arpeggio: 8.

	db 9	; Volume: 2.

	db 133	; Volume: 1.
	db 6	; Arpeggio: 3.

	db 133	; Volume: 1.
	db 16	; Arpeggio: 8.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument18
	db 0	; Speed.

	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 10	; Arpeggio: 5.

	db 181	; Volume: 13.
	db 18	; Arpeggio: 9.

	db 49	; Volume: 12.

	db 177	; Volume: 12.
	db 10	; Arpeggio: 5.

	db 173	; Volume: 11.
	db 18	; Arpeggio: 9.

	db 41	; Volume: 10.

	db 169	; Volume: 10.
	db 10	; Arpeggio: 5.

	db 165	; Volume: 9.
	db 18	; Arpeggio: 9.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 10	; Arpeggio: 5.

	db 157	; Volume: 7.
	db 18	; Arpeggio: 9.

	db 25	; Volume: 6.

	db 149	; Volume: 5.
	db 10	; Arpeggio: 5.

	db 149	; Volume: 5.
	db 18	; Arpeggio: 9.

	db 17	; Volume: 4.

	db 141	; Volume: 3.
	db 10	; Arpeggio: 5.

	db 141	; Volume: 3.
	db 18	; Arpeggio: 9.

	db 9	; Volume: 2.

	db 133	; Volume: 1.
	db 10	; Arpeggio: 5.

	db 133	; Volume: 1.
	db 18	; Arpeggio: 9.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument19
	db 0	; Speed.

mySong_Instrument19Loop	db 37	; Volume: 9.

	db 165	; Volume: 9.
	db 10	; Arpeggio: 5.

	db 165	; Volume: 9.
	db 18	; Arpeggio: 9.

	db 4	; End the instrument.
	dw mySong_Instrument19Loop	; Loops.

mySong_Instrument20
	db 0	; Speed.

	db 57	; Volume: 14.

	db 185	; Volume: 14.
	db 8	; Arpeggio: 4.

	db 181	; Volume: 13.
	db 14	; Arpeggio: 7.

	db 49	; Volume: 12.

	db 177	; Volume: 12.
	db 8	; Arpeggio: 4.

	db 173	; Volume: 11.
	db 14	; Arpeggio: 7.

	db 41	; Volume: 10.

	db 169	; Volume: 10.
	db 8	; Arpeggio: 4.

	db 165	; Volume: 9.
	db 14	; Arpeggio: 7.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 8	; Arpeggio: 4.

	db 157	; Volume: 7.
	db 14	; Arpeggio: 7.

	db 25	; Volume: 6.

	db 149	; Volume: 5.
	db 8	; Arpeggio: 4.

	db 149	; Volume: 5.
	db 14	; Arpeggio: 7.

	db 17	; Volume: 4.

	db 141	; Volume: 3.
	db 8	; Arpeggio: 4.

	db 141	; Volume: 3.
	db 14	; Arpeggio: 7.

	db 9	; Volume: 2.

	db 133	; Volume: 1.
	db 8	; Arpeggio: 4.

	db 133	; Volume: 1.
	db 14	; Arpeggio: 7.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument21
	db 0	; Speed.

mySong_Instrument21Loop	db 37	; Volume: 9.

	db 165	; Volume: 9.
	db 8	; Arpeggio: 4.

	db 165	; Volume: 9.
	db 14	; Arpeggio: 7.

	db 4	; End the instrument.
	dw mySong_Instrument21Loop	; Loops.

; "Hydrofool" 1987 Gargoyle Games, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 1	; Initial speed.

	db 16	; Most used instrument.
	db 4	; Second most used instrument.

	db 0	; Most used wait.
	db 4	; Second most used wait.

	db 79	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 79	; New height.
	db 0	; New transposition on channel 1.
	db 137	; New track (0) for channel 1, as a reference (index 9).
	db 0	; New transposition on channel 2.
	db 128	; New track (53) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 1
	db 136	; State byte.
	db 134	; New track (1) for channel 1, as a reference (index 6).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 2
	db 136	; State byte.
	db ((mySong_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track2 - ($ + 1)) & 255)
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 3
	db 136	; State byte.
	db 136	; New track (3) for channel 1, as a reference (index 8).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 4
	db 136	; State byte.
	db 137	; New track (0) for channel 1, as a reference (index 9).
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 5
	db 136	; State byte.
	db 134	; New track (1) for channel 1, as a reference (index 6).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 6
	db 152	; State byte.
	db ((mySong_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track4 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 7
	db 152	; State byte.
	db ((mySong_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track5 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 8
	db 216	; State byte.
	db ((mySong_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track6 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.
	db 5	; New transposition on channel 3.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 9
	db 136	; State byte.
	db ((mySong_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track7 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 10
	db 152	; State byte.
	db ((mySong_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track8 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 11
	db 140	; State byte.
	db 12	; New transposition on channel 1.
	db 136	; New track (3) for channel 1, as a reference (index 8).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 12
	db 156	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track9 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 13
	db 136	; State byte.
	db ((mySong_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track10 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 14
	db 152	; State byte.
	db ((mySong_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track11 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 15
	db 136	; State byte.
	db ((mySong_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track12 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 16
	db 152	; State byte.
	db 135	; New track (13) for channel 1, as a reference (index 7).
	db -7	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 17
	db 136	; State byte.
	db ((mySong_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track14 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 18
	db 136	; State byte.
	db 135	; New track (13) for channel 1, as a reference (index 7).
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 19
	db 136	; State byte.
	db ((mySong_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track15 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 20
	db 220	; State byte.
	db -5	; New transposition on channel 1.
	db 135	; New track (13) for channel 1, as a reference (index 7).
	db 0	; New transposition on channel 2.
	db 0	; New transposition on channel 3.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 21
	db 140	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track16 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 22
	db 136	; State byte.
	db ((mySong_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track17 - ($ + 1)) & 255)
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 23
	db 136	; State byte.
	db ((mySong_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track18 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 24
	db 216	; State byte.
	db 135	; New track (13) for channel 1, as a reference (index 7).
	db -7	; New transposition on channel 2.
	db 5	; New transposition on channel 3.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 25
	db 136	; State byte.
	db ((mySong_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track14 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 26
	db 136	; State byte.
	db 135	; New track (13) for channel 1, as a reference (index 7).
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 27
	db 136	; State byte.
	db ((mySong_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track15 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 28
	db 152	; State byte.
	db ((mySong_Subsong0_Track19 - ($ + 2)) & #ff00) / 256	; New track (19) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track19 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 29
	db 140	; State byte.
	db -5	; New transposition on channel 1.
	db 134	; New track (1) for channel 1, as a reference (index 6).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 30
	db 140	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track20 - ($ + 2)) & #ff00) / 256	; New track (20) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track20 - ($ + 1)) & 255)
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 31
	db 136	; State byte.
	db ((mySong_Subsong0_Track21 - ($ + 2)) & #ff00) / 256	; New track (21) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track21 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 32
	db 216	; State byte.
	db ((mySong_Subsong0_Track22 - ($ + 2)) & #ff00) / 256	; New track (22) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track22 - ($ + 1)) & 255)
	db -1	; New transposition on channel 2.
	db 0	; New transposition on channel 3.
	db 129	; New track (60) for channel 3, as a reference (index 1).

; Pattern 33
	db 8	; State byte.
	db ((mySong_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track23 - ($ + 1)) & 255)

; Pattern 34
	db 8	; State byte.
	db ((mySong_Subsong0_Track24 - ($ + 2)) & #ff00) / 256	; New track (24) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track24 - ($ + 1)) & 255)

; Pattern 35
	db 8	; State byte.
	db ((mySong_Subsong0_Track25 - ($ + 2)) & #ff00) / 256	; New track (25) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track25 - ($ + 1)) & 255)

; Pattern 36
	db 92	; State byte.
	db 15	; New transposition on channel 1.
	db ((mySong_Subsong0_Track22 - ($ + 2)) & #ff00) / 256	; New track (22) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track22 - ($ + 1)) & 255)
	db -10	; New transposition on channel 2.
	db 3	; New transposition on channel 3.

; Pattern 37
	db 12	; State byte.
	db 3	; New transposition on channel 1.
	db ((mySong_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track23 - ($ + 1)) & 255)

; Pattern 38
	db 8	; State byte.
	db ((mySong_Subsong0_Track24 - ($ + 2)) & #ff00) / 256	; New track (24) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track24 - ($ + 1)) & 255)

; Pattern 39
	db 8	; State byte.
	db ((mySong_Subsong0_Track25 - ($ + 2)) & #ff00) / 256	; New track (25) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track25 - ($ + 1)) & 255)

; Pattern 40
	db 92	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track26 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.
	db 6	; New transposition on channel 3.

; Pattern 41
	db 8	; State byte.
	db ((mySong_Subsong0_Track27 - ($ + 2)) & #ff00) / 256	; New track (27) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track27 - ($ + 1)) & 255)

; Pattern 42
	db 8	; State byte.
	db ((mySong_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track26 - ($ + 1)) & 255)

; Pattern 43
	db 8	; State byte.
	db ((mySong_Subsong0_Track27 - ($ + 2)) & #ff00) / 256	; New track (27) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track27 - ($ + 1)) & 255)

; Pattern 44
	db 24	; State byte.
	db ((mySong_Subsong0_Track28 - ($ + 2)) & #ff00) / 256	; New track (28) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track28 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.

; Pattern 45
	db 8	; State byte.
	db ((mySong_Subsong0_Track29 - ($ + 2)) & #ff00) / 256	; New track (29) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track29 - ($ + 1)) & 255)

; Pattern 46
	db 8	; State byte.
	db ((mySong_Subsong0_Track28 - ($ + 2)) & #ff00) / 256	; New track (28) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track28 - ($ + 1)) & 255)

; Pattern 47
	db 8	; State byte.
	db ((mySong_Subsong0_Track29 - ($ + 2)) & #ff00) / 256	; New track (29) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track29 - ($ + 1)) & 255)

; Pattern 48
	db 200	; State byte.
	db 137	; New track (0) for channel 1, as a reference (index 9).
	db 0	; New transposition on channel 3.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 49
	db 136	; State byte.
	db 134	; New track (1) for channel 1, as a reference (index 6).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 50
	db 136	; State byte.
	db ((mySong_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track2 - ($ + 1)) & 255)
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 51
	db 136	; State byte.
	db 136	; New track (3) for channel 1, as a reference (index 8).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 52
	db 136	; State byte.
	db 137	; New track (0) for channel 1, as a reference (index 9).
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 53
	db 136	; State byte.
	db 134	; New track (1) for channel 1, as a reference (index 6).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 54
	db 152	; State byte.
	db ((mySong_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track4 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 55
	db 152	; State byte.
	db ((mySong_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track5 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 56
	db 216	; State byte.
	db ((mySong_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track6 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.
	db 5	; New transposition on channel 3.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 57
	db 136	; State byte.
	db ((mySong_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track7 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 58
	db 152	; State byte.
	db ((mySong_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track8 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 59
	db 140	; State byte.
	db 12	; New transposition on channel 1.
	db 136	; New track (3) for channel 1, as a reference (index 8).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 60
	db 156	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track9 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 61
	db 136	; State byte.
	db ((mySong_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track10 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 62
	db 152	; State byte.
	db ((mySong_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track11 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 63
	db 136	; State byte.
	db ((mySong_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track12 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 64
	db 216	; State byte.
	db 142	; New track (30) for channel 1, as a reference (index 14).
	db -1	; New transposition on channel 2.
	db 0	; New transposition on channel 3.
	db 129	; New track (60) for channel 3, as a reference (index 1).

; Pattern 65
	db 8	; State byte.
	db ((mySong_Subsong0_Track31 - ($ + 2)) & #ff00) / 256	; New track (31) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track31 - ($ + 1)) & 255)

; Pattern 66
	db 8	; State byte.
	db 142	; New track (30) for channel 1, as a reference (index 14).

; Pattern 67
	db 8	; State byte.
	db ((mySong_Subsong0_Track32 - ($ + 2)) & #ff00) / 256	; New track (32) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track32 - ($ + 1)) & 255)

; Pattern 68
	db 8	; State byte.
	db 142	; New track (30) for channel 1, as a reference (index 14).

; Pattern 69
	db 8	; State byte.
	db ((mySong_Subsong0_Track31 - ($ + 2)) & #ff00) / 256	; New track (31) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track31 - ($ + 1)) & 255)

; Pattern 70
	db 8	; State byte.
	db ((mySong_Subsong0_Track33 - ($ + 2)) & #ff00) / 256	; New track (33) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track33 - ($ + 1)) & 255)

; Pattern 71
	db 8	; State byte.
	db ((mySong_Subsong0_Track34 - ($ + 2)) & #ff00) / 256	; New track (34) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track34 - ($ + 1)) & 255)

; Pattern 72
	db 88	; State byte.
	db ((mySong_Subsong0_Track35 - ($ + 2)) & #ff00) / 256	; New track (35) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track35 - ($ + 1)) & 255)
	db -10	; New transposition on channel 2.
	db 3	; New transposition on channel 3.

; Pattern 73
	db 8	; State byte.
	db ((mySong_Subsong0_Track36 - ($ + 2)) & #ff00) / 256	; New track (36) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track36 - ($ + 1)) & 255)

; Pattern 74
	db 8	; State byte.
	db ((mySong_Subsong0_Track37 - ($ + 2)) & #ff00) / 256	; New track (37) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track37 - ($ + 1)) & 255)

; Pattern 75
	db 8	; State byte.
	db ((mySong_Subsong0_Track38 - ($ + 2)) & #ff00) / 256	; New track (38) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track38 - ($ + 1)) & 255)

; Pattern 76
	db 8	; State byte.
	db ((mySong_Subsong0_Track35 - ($ + 2)) & #ff00) / 256	; New track (35) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track35 - ($ + 1)) & 255)

; Pattern 77
	db 8	; State byte.
	db ((mySong_Subsong0_Track36 - ($ + 2)) & #ff00) / 256	; New track (36) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track36 - ($ + 1)) & 255)

; Pattern 78
	db 8	; State byte.
	db ((mySong_Subsong0_Track37 - ($ + 2)) & #ff00) / 256	; New track (37) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track37 - ($ + 1)) & 255)

; Pattern 79
	db 8	; State byte.
	db ((mySong_Subsong0_Track38 - ($ + 2)) & #ff00) / 256	; New track (38) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track38 - ($ + 1)) & 255)

; Pattern 80
	db 248	; State byte.
	db 138	; New track (39) for channel 1, as a reference (index 10).
	db 0	; New transposition on channel 2.
	db 141	; New track (54) for channel 2, as a reference (index 13).
	db 5	; New transposition on channel 3.
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 81
	db 168	; State byte.
	db ((mySong_Subsong0_Track40 - ($ + 2)) & #ff00) / 256	; New track (40) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track40 - ($ + 1)) & 255)
	db 133	; New track (55) for channel 2, as a reference (index 5).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 82
	db 136	; State byte.
	db ((mySong_Subsong0_Track41 - ($ + 2)) & #ff00) / 256	; New track (41) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track41 - ($ + 1)) & 255)
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 83
	db 136	; State byte.
	db ((mySong_Subsong0_Track42 - ($ + 2)) & #ff00) / 256	; New track (42) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track42 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 84
	db 168	; State byte.
	db 138	; New track (39) for channel 1, as a reference (index 10).
	db ((mySong_Subsong0_Track56 - ($ + 2)) & #ff00) / 256	; New track (56) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track56 - ($ + 1)) & 255)
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 85
	db 168	; State byte.
	db ((mySong_Subsong0_Track43 - ($ + 2)) & #ff00) / 256	; New track (43) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track43 - ($ + 1)) & 255)
	db 133	; New track (55) for channel 2, as a reference (index 5).
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 86
	db 136	; State byte.
	db ((mySong_Subsong0_Track44 - ($ + 2)) & #ff00) / 256	; New track (44) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track44 - ($ + 1)) & 255)
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 87
	db 136	; State byte.
	db ((mySong_Subsong0_Track45 - ($ + 2)) & #ff00) / 256	; New track (45) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track45 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 88
	db 188	; State byte.
	db 2	; New transposition on channel 1.
	db 138	; New track (39) for channel 1, as a reference (index 10).
	db 2	; New transposition on channel 2.
	db 141	; New track (54) for channel 2, as a reference (index 13).
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 89
	db 188	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track46 - ($ + 2)) & #ff00) / 256	; New track (46) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track46 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track57 - ($ + 2)) & #ff00) / 256	; New track (57) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track57 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 90
	db 188	; State byte.
	db 2	; New transposition on channel 1.
	db 138	; New track (39) for channel 1, as a reference (index 10).
	db 2	; New transposition on channel 2.
	db 141	; New track (54) for channel 2, as a reference (index 13).
	db 131	; New track (58) for channel 3, as a reference (index 3).

; Pattern 91
	db 188	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track46 - ($ + 2)) & #ff00) / 256	; New track (46) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track46 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track57 - ($ + 2)) & #ff00) / 256	; New track (57) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track57 - ($ + 1)) & 255)
	db 130	; New track (59) for channel 3, as a reference (index 2).

; Pattern 92
	db 232	; State byte.
	db 139	; New track (47) for channel 1, as a reference (index 11).
	db 128	; New track (53) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 132	; New track (61) for channel 3, as a reference (index 4).

; Pattern 93
	db 8	; State byte.
	db 140	; New track (48) for channel 1, as a reference (index 12).

; Pattern 94
	db 8	; State byte.
	db 139	; New track (47) for channel 1, as a reference (index 11).

; Pattern 95
	db 8	; State byte.
	db 140	; New track (48) for channel 1, as a reference (index 12).

; Pattern 96
	db 24	; State byte.
	db ((mySong_Subsong0_Track49 - ($ + 2)) & #ff00) / 256	; New track (49) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track49 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.

; Pattern 97
	db 8	; State byte.
	db ((mySong_Subsong0_Track50 - ($ + 2)) & #ff00) / 256	; New track (50) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track50 - ($ + 1)) & 255)

; Pattern 98
	db 88	; State byte.
	db ((mySong_Subsong0_Track51 - ($ + 2)) & #ff00) / 256	; New track (51) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track51 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db -5	; New transposition on channel 3.

; Pattern 99
	db 8	; State byte.
	db ((mySong_Subsong0_Track52 - ($ + 2)) & #ff00) / 256	; New track (52) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track52 - ($ + 1)) & 255)

; Pattern 100
	db 88	; State byte.
	db 139	; New track (47) for channel 1, as a reference (index 11).
	db 0	; New transposition on channel 2.
	db 0	; New transposition on channel 3.

; Pattern 101
	db 8	; State byte.
	db 140	; New track (48) for channel 1, as a reference (index 12).

; Pattern 102
	db 8	; State byte.
	db 139	; New track (47) for channel 1, as a reference (index 11).

; Pattern 103
	db 8	; State byte.
	db 140	; New track (48) for channel 1, as a reference (index 12).

; Pattern 104
	db 24	; State byte.
	db ((mySong_Subsong0_Track49 - ($ + 2)) & #ff00) / 256	; New track (49) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track49 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.

; Pattern 105
	db 8	; State byte.
	db ((mySong_Subsong0_Track50 - ($ + 2)) & #ff00) / 256	; New track (50) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track50 - ($ + 1)) & 255)

; Pattern 106
	db 88	; State byte.
	db ((mySong_Subsong0_Track51 - ($ + 2)) & #ff00) / 256	; New track (51) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track51 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db -5	; New transposition on channel 3.

; Pattern 107
	db 8	; State byte.
	db ((mySong_Subsong0_Track52 - ($ + 2)) & #ff00) / 256	; New track (52) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track52 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes
	dw mySong_Subsong0_Track53	; Track 53, index 0.
	dw mySong_Subsong0_Track60	; Track 60, index 1.
	dw mySong_Subsong0_Track59	; Track 59, index 2.
	dw mySong_Subsong0_Track58	; Track 58, index 3.
	dw mySong_Subsong0_Track61	; Track 61, index 4.
	dw mySong_Subsong0_Track55	; Track 55, index 5.
	dw mySong_Subsong0_Track1	; Track 1, index 6.
	dw mySong_Subsong0_Track13	; Track 13, index 7.
	dw mySong_Subsong0_Track3	; Track 3, index 8.
	dw mySong_Subsong0_Track0	; Track 0, index 9.
	dw mySong_Subsong0_Track39	; Track 39, index 10.
	dw mySong_Subsong0_Track47	; Track 47, index 11.
	dw mySong_Subsong0_Track48	; Track 48, index 12.
	dw mySong_Subsong0_Track54	; Track 54, index 13.
	dw mySong_Subsong0_Track30	; Track 30, index 14.

mySong_Subsong0_Track0
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 241	; New instrument (6). Note reference (1). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 179	; New instrument (5). Note reference (3). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 135	; Note reference (7). Secondary wait (4).
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 131	; Note reference (3). Secondary wait (4).
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 194	; Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 130	; Note reference (2). Secondary wait (4).
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 132	; Note reference (4). Secondary wait (4).
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 133	; Note reference (5). Secondary wait (4).
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 132	; Note reference (4). Secondary wait (4).
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 194	; Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track2
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 181	; New instrument (5). Note reference (5). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 245	; New instrument (6). Note reference (5). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 133	; Note reference (5). Secondary wait (4).
	db 169	; Secondary instrument (4). Note reference (9). Secondary wait (4).
	db 137	; Note reference (9). Secondary wait (4).
	db 174	; Secondary instrument (4). New escaped note: 53. Secondary wait (4).
	db 53	;   Escape note value.
	db 207	; Same escaped note: 53. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track3
	db 254	; New instrument (6). New escaped note: 53. New wait (127).
	db 53	;   Escape note value.
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track4
	db 192	; Note reference (0). New wait (9).
	db 9	;   Escape wait value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 181	; New instrument (5). Note reference (5). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 132	; Note reference (4). Secondary wait (4).
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 133	; Note reference (5). Secondary wait (4).
	db 169	; Secondary instrument (4). Note reference (9). Secondary wait (4).
	db 137	; Note reference (9). Secondary wait (4).
	db 57	; New instrument (6). Note reference (9). 
	db 6	;   Escape instrument value.
	db 174	; Secondary instrument (4). New escaped note: 55. Secondary wait (4).
	db 55	;   Escape note value.
	db 191	; New instrument (5). Same escaped note: 55. Secondary wait (4).
	db 5	;   Escape instrument value.
	db 174	; Secondary instrument (4). New escaped note: 53. Secondary wait (4).
	db 53	;   Escape note value.
	db 207	; Same escaped note: 53. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track5
	db 169	; Secondary instrument (4). Note reference (9). Secondary wait (4).
	db 185	; New instrument (5). Note reference (9). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 249	; New instrument (6). Note reference (9). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track6
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 244	; New instrument (6). Note reference (4). New wait (19).
	db 6	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 178	; New instrument (5). Note reference (2). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 50	; New instrument (6). Note reference (2). 
	db 6	;   Escape instrument value.
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 183	; New instrument (5). Note reference (7). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 247	; New instrument (6). Note reference (7). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track7
	db 247	; New instrument (6). Note reference (7). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 241	; New instrument (6). Note reference (1). New wait (19).
	db 6	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 179	; New instrument (5). Note reference (3). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 243	; New instrument (6). Note reference (3). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 183	; New instrument (5). Note reference (7). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 247	; New instrument (6). Note reference (7). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track8
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 130	; Note reference (2). Secondary wait (4).
	db 242	; New instrument (6). Note reference (2). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track9
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 183	; New instrument (5). Note reference (7). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 247	; New instrument (6). Note reference (7). New wait (19).
	db 6	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 179	; New instrument (5). Note reference (3). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 51	; New instrument (6). Note reference (3). 
	db 6	;   Escape instrument value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 241	; New instrument (6). Note reference (1). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track10
	db 241	; New instrument (6). Note reference (1). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 166	; Secondary instrument (4). Note reference (6). Secondary wait (4).
	db 182	; New instrument (5). Note reference (6). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 246	; New instrument (6). Note reference (6). New wait (19).
	db 6	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 241	; New instrument (6). Note reference (1). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 179	; New instrument (5). Note reference (3). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 243	; New instrument (6). Note reference (3). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track11
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 241	; New instrument (6). Note reference (1). New wait (19).
	db 6	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 179	; New instrument (5). Note reference (3). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 243	; New instrument (6). Note reference (3). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track12
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 183	; New instrument (5). Note reference (7). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 247	; New instrument (6). Note reference (7). New wait (19).
	db 6	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 178	; New instrument (5). Note reference (2). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 242	; New instrument (6). Note reference (2). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track13
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 244	; New instrument (6). Note reference (4). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 181	; New instrument (5). Note reference (5). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 132	; Note reference (4). Secondary wait (4).
	db 48	; New instrument (0). Note reference (0). 
	db 0	;   Escape instrument value.
	db 168	; Secondary instrument (4). Note reference (8). Secondary wait (4).
	db 248	; New instrument (5). Note reference (8). New wait (127).
	db 5	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track14
	db 248	; New instrument (6). Note reference (8). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 168	; Secondary instrument (4). Note reference (8). Secondary wait (4).
	db 184	; New instrument (5). Note reference (8). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 135	; Note reference (7). Secondary wait (4).
	db 55	; New instrument (6). Note reference (7). 
	db 6	;   Escape instrument value.
	db 166	; Secondary instrument (4). Note reference (6). Secondary wait (4).
	db 182	; New instrument (5). Note reference (6). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 54	; New instrument (6). Note reference (6). 
	db 6	;   Escape instrument value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 241	; New instrument (6). Note reference (1). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track15
	db 248	; New instrument (6). Note reference (8). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 168	; Secondary instrument (4). Note reference (8). Secondary wait (4).
	db 184	; New instrument (5). Note reference (8). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 135	; Note reference (7). Secondary wait (4).
	db 55	; New instrument (6). Note reference (7). 
	db 6	;   Escape instrument value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 178	; New instrument (5). Note reference (2). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 50	; New instrument (6). Note reference (2). 
	db 6	;   Escape instrument value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 171	; Secondary instrument (4). Note reference (11). Secondary wait (4).
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track16
	db 244	; New instrument (6). Note reference (4). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 133	; Note reference (5). Secondary wait (4).
	db 53	; New instrument (6). Note reference (5). 
	db 6	;   Escape instrument value.
	db 171	; Secondary instrument (4). Note reference (11). Secondary wait (4).
	db 187	; New instrument (5). Note reference (11). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 59	; New instrument (6). Note reference (11). 
	db 6	;   Escape instrument value.
	db 169	; Secondary instrument (4). Note reference (9). Secondary wait (4).
	db 185	; New instrument (5). Note reference (9). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 249	; New instrument (6). Note reference (9). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track17
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 133	; Note reference (5). Secondary wait (4).
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 132	; Note reference (4). Secondary wait (4).
	db 244	; New instrument (6). Note reference (4). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 183	; New instrument (5). Note reference (7). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 194	; Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track18
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 129	; Note reference (1). Secondary wait (4).
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 130	; Note reference (2). Secondary wait (4).
	db 242	; New instrument (6). Note reference (2). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 52	; New instrument (6). Note reference (4). 
	db 6	;   Escape instrument value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 181	; New instrument (5). Note reference (5). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 169	; Secondary instrument (4). Note reference (9). Secondary wait (4).
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track19
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 178	; New instrument (5). Note reference (2). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 242	; New instrument (6). Note reference (2). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 165	; Secondary instrument (4). Note reference (5). Secondary wait (4).
	db 133	; Note reference (5). Secondary wait (4).
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 132	; Note reference (4). Secondary wait (4).
	db 171	; Secondary instrument (4). Note reference (11). Secondary wait (4).
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track20
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 178	; New instrument (5). Note reference (2). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 242	; New instrument (6). Note reference (2). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 164	; Secondary instrument (4). Note reference (4). Secondary wait (4).
	db 180	; New instrument (5). Note reference (4). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 162	; Secondary instrument (4). Note reference (2). Secondary wait (4).
	db 130	; Note reference (2). Secondary wait (4).
	db 48	; New instrument (0). Note reference (0). 
	db 0	;   Escape instrument value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 241	; New instrument (5). Note reference (1). New wait (127).
	db 5	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track21
	db 241	; New instrument (6). Note reference (1). New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 161	; Secondary instrument (4). Note reference (1). Secondary wait (4).
	db 177	; New instrument (5). Note reference (1). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 131	; Note reference (3). Secondary wait (4).
	db 51	; New instrument (6). Note reference (3). 
	db 6	;   Escape instrument value.
	db 167	; Secondary instrument (4). Note reference (7). Secondary wait (4).
	db 183	; New instrument (5). Note reference (7). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 55	; New instrument (6). Note reference (7). 
	db 6	;   Escape instrument value.
	db 163	; Secondary instrument (4). Note reference (3). Secondary wait (4).
	db 179	; New instrument (5). Note reference (3). Secondary wait (4).
	db 5	;   Escape instrument value.
	db 243	; New instrument (6). Note reference (3). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track22
	db 254	; New instrument (7). New escaped note: 49. New wait (1).
	db 49	;   Escape note value.
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 49. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (7). Same escaped note: 49. New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 49. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (7). New escaped note: 61. New wait (1).
	db 61	;   Escape note value.
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 61. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (19).
	db 0	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 254	; New instrument (7). New escaped note: 49. New wait (1).
	db 49	;   Escape note value.
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 49. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track23
	db 245	; New instrument (9). Note reference (5). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 245	; New instrument (10). Note reference (5). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 245	; New instrument (9). Note reference (5). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 245	; New instrument (10). Note reference (5). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 250	; New instrument (9). Note reference (10). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (10). Note reference (10). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (19).
	db 0	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 245	; New instrument (9). Note reference (5). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 245	; New instrument (10). Note reference (5). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track24
	db 252	; New instrument (9). Note reference (12). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 252	; New instrument (10). Note reference (12). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 252	; New instrument (9). Note reference (12). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 252	; New instrument (10). Note reference (12). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (9). New escaped note: 76. New wait (1).
	db 76	;   Escape note value.
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 76. New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 252	; New instrument (9). Note reference (12). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 252	; New instrument (10). Note reference (12). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (9). Same escaped note: 76. New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 76. New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 245	; New instrument (9). Note reference (5). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 245	; New instrument (10). Note reference (5). New wait (127).
	db 10	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track25
	db 192	; Note reference (0). New wait (9).
	db 9	;   Escape wait value.
	db 245	; New instrument (9). Note reference (5). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 245	; New instrument (10). Note reference (5). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 250	; New instrument (9). Note reference (10). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (10). Note reference (10). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 245	; New instrument (9). Note reference (5). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 245	; New instrument (10). Note reference (5). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 250	; New instrument (9). Note reference (10). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (10). Note reference (10). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 245	; New instrument (9). Note reference (5). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 245	; New instrument (10). Note reference (5). New wait (127).
	db 10	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track26
	db 255	; New instrument (7). Same escaped note: 79. New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 79. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (7). Same escaped note: 79. New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 79. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 247	; New instrument (7). Note reference (7). New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 247	; New instrument (8). Note reference (7). New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 242	; New instrument (9). Note reference (2). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 242	; New instrument (10). Note reference (2). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (9). New escaped note: 77. New wait (1).
	db 77	;   Escape note value.
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 77. New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (7). New escaped note: 79. New wait (1).
	db 79	;   Escape note value.
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 79. New wait (127).
	db 8	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track27
	db 254	; New instrument (9). New escaped note: 77. New wait (1).
	db 77	;   Escape note value.
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 77. New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (9). Same escaped note: 77. New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 77. New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 242	; New instrument (9). Note reference (2). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 242	; New instrument (10). Note reference (2). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 244	; New instrument (9). Note reference (4). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 244	; New instrument (10). Note reference (4). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (9). New escaped note: 75. New wait (1).
	db 75	;   Escape note value.
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 75. New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (9). New escaped note: 77. New wait (1).
	db 77	;   Escape note value.
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 77. New wait (127).
	db 10	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track28
	db 255	; New instrument (7). Same escaped note: 79. New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 79. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (7). Same escaped note: 79. New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (8). Same escaped note: 79. New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 247	; New instrument (7). Note reference (7). New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 247	; New instrument (8). Note reference (7). New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (9). New escaped note: 77. New wait (1).
	db 77	;   Escape note value.
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 77. New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 242	; New instrument (9). Note reference (2). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 242	; New instrument (10). Note reference (2). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (9). New escaped note: 75. New wait (1).
	db 75	;   Escape note value.
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 255	; New instrument (10). Same escaped note: 75. New wait (127).
	db 10	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track29
	db 192	; Note reference (0). New wait (9).
	db 9	;   Escape wait value.
	db 244	; New instrument (9). Note reference (4). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 244	; New instrument (10). Note reference (4). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 244	; New instrument (9). Note reference (4). New wait (1).
	db 9	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 244	; New instrument (10). Note reference (4). New wait (7).
	db 10	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 250	; New instrument (7). Note reference (10). New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (8). Note reference (10). New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 246	; New instrument (7). Note reference (6). New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 246	; New instrument (8). Note reference (6). New wait (7).
	db 8	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 250	; New instrument (7). Note reference (10). New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (8). Note reference (10). New wait (127).
	db 8	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track30
	db 254	; New instrument (11). New escaped note: 76. New wait (1).
	db 76	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 252	; New instrument (12). Note reference (12). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (11). Same escaped note: 76. New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 252	; New instrument (12). Note reference (12). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 83. New wait (1).
	db 83	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 71. New wait (7).
	db 71	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 81. New wait (1).
	db 81	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 86. New wait (1).
	db 86	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (12). Note reference (10). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 85. New wait (1).
	db 85	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 73. New wait (127).
	db 73	;   Escape note value.
	db 12	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track31
	db 192	; Note reference (0). New wait (19).
	db 19	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 81. New wait (1).
	db 81	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 83. New wait (1).
	db 83	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 71. New wait (7).
	db 71	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (19).
	db 0	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 85. New wait (1).
	db 85	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 73. New wait (7).
	db 73	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 81. New wait (1).
	db 81	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (127).
	db 12	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track32
	db 192	; Note reference (0). New wait (9).
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 90. New wait (1).
	db 90	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 78. New wait (7).
	db 78	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 88. New wait (1).
	db 88	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 76. New wait (7).
	db 76	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 86. New wait (1).
	db 86	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (12). Note reference (10). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 85. New wait (1).
	db 85	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 73. New wait (7).
	db 73	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track33
	db 254	; New instrument (11). New escaped note: 76. New wait (1).
	db 76	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 252	; New instrument (12). Note reference (12). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (11). Same escaped note: 76. New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 252	; New instrument (12). Note reference (12). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 83. New wait (1).
	db 83	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 71. New wait (7).
	db 71	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 81. New wait (1).
	db 81	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 90. New wait (1).
	db 90	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 78. New wait (7).
	db 78	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 88. New wait (1).
	db 88	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 76. New wait (127).
	db 76	;   Escape note value.
	db 12	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track34
	db 254	; New instrument (11). New escaped note: 93. New wait (1).
	db 93	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 81. New wait (7).
	db 81	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (11). Same escaped note: 81. New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 255	; New instrument (11). Same escaped note: 81. New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (5).
	db 12	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 243	; New instrument (13). Note reference (3). New wait (11).
	db 13	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 255	; New instrument (11). Same escaped note: 81. New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (5).
	db 12	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 243	; New instrument (13). Note reference (3). New wait (11).
	db 13	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track35
	db 254	; New instrument (11). New escaped note: 88. New wait (1).
	db 88	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 76. New wait (7).
	db 76	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 88. New wait (1).
	db 88	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 76. New wait (7).
	db 76	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 93. New wait (1).
	db 93	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 81. New wait (7).
	db 81	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 91. New wait (1).
	db 91	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 79. New wait (7).
	db 79	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 88. New wait (1).
	db 88	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 76. New wait (7).
	db 76	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 89. New wait (1).
	db 89	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 77. New wait (127).
	db 77	;   Escape note value.
	db 12	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track36
	db 192	; Note reference (0). New wait (9).
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 86. New wait (1).
	db 86	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (12). Note reference (10). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 88. New wait (1).
	db 88	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 76. New wait (7).
	db 76	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 84. New wait (1).
	db 84	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 246	; New instrument (12). Note reference (6). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 86. New wait (1).
	db 86	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 250	; New instrument (12). Note reference (10). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 83. New wait (1).
	db 83	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 71. New wait (127).
	db 71	;   Escape note value.
	db 12	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track37
	db 254	; New instrument (11). New escaped note: 84. New wait (1).
	db 84	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 246	; New instrument (12). Note reference (6). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 81. New wait (1).
	db 81	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 83. New wait (1).
	db 83	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 254	; New instrument (12). New escaped note: 71. New wait (7).
	db 71	;   Escape note value.
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (9).
	db 0	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 81. New wait (1).
	db 81	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 243	; New instrument (12). Note reference (3). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 254	; New instrument (11). New escaped note: 79. New wait (1).
	db 79	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 247	; New instrument (12). Note reference (7). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track38
	db 254	; New instrument (11). New escaped note: 84. New wait (1).
	db 84	;   Escape note value.
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 246	; New instrument (12). Note reference (6). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 246	; New instrument (11). Note reference (6). New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 251	; New instrument (12). Note reference (11). New wait (7).
	db 12	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 246	; New instrument (11). Note reference (6). New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 251	; New instrument (12). Note reference (11). New wait (5).
	db 12	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 251	; New instrument (13). Note reference (11). New wait (11).
	db 13	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 246	; New instrument (11). Note reference (6). New wait (1).
	db 11	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 251	; New instrument (12). Note reference (11). New wait (5).
	db 12	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 251	; New instrument (13). Note reference (11). New wait (11).
	db 13	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track39
	db 174	; Secondary instrument (4). New escaped note: 51. Secondary wait (4).
	db 51	;   Escape note value.
	db 191	; New instrument (5). Same escaped note: 51. Secondary wait (4).
	db 5	;   Escape instrument value.
	db 174	; Secondary instrument (4). New escaped note: 39. Secondary wait (4).
	db 39	;   Escape note value.
	db 143	; Same escaped note: 39. Secondary wait (4).
	db 175	; Secondary instrument (4). Same escaped note: 39. Secondary wait (4).
	db 143	; Same escaped note: 39. Secondary wait (4).
	db 255	; New instrument (6). Same escaped note: 39. New wait (9).
	db 6	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 175	; Secondary instrument (4). Same escaped note: 39. Secondary wait (4).
	db 191	; New instrument (5). Same escaped note: 39. Secondary wait (4).
	db 5	;   Escape instrument value.
	db 63	; New instrument (6). Same escaped note: 39. 
	db 6	;   Escape instrument value.
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track40
	db 126	; New instrument (14). New escaped note: 87. Primary wait (0).
	db 87	;   Escape note value.
	db 14	;   Escape instrument value.
	db 206	; New escaped note: 91. New wait (2).
	db 91	;   Escape note value.
	db 2	;   Escape wait value.
	db 78	; New escaped note: 86. Primary wait (0).
	db 86	;   Escape note value.
	db 14	; New escaped note: 90. 
	db 90	;   Escape note value.
	db 126	; New instrument (15). New escaped note: 85. Primary wait (0).
	db 85	;   Escape note value.
	db 15	;   Escape instrument value.
	db 14	; New escaped note: 89. 
	db 89	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 84. Primary wait (0).
	db 84	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 88. 
	db 88	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 83. Primary wait (0).
	db 83	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 87. 
	db 87	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 82. Primary wait (0).
	db 82	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 86. 
	db 86	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 81. Primary wait (0).
	db 81	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 85. 
	db 85	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 80. Primary wait (0).
	db 80	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 84. 
	db 84	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 79. Primary wait (0).
	db 79	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 83. 
	db 83	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 78. Primary wait (0).
	db 78	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 82. 
	db 82	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 77. Primary wait (0).
	db 77	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 81. 
	db 81	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 76. Primary wait (0).
	db 76	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 80. 
	db 80	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 75. Primary wait (0).
	db 75	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 79. 
	db 79	;   Escape note value.
	db 90	; Primary instrument (16). Note reference (10). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 78. 
	db 78	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 73. Primary wait (0).
	db 73	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 77. 
	db 77	;   Escape note value.
	db 86	; Primary instrument (16). Note reference (6). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 76. 
	db 76	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 71. Primary wait (0).
	db 71	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 75. 
	db 75	;   Escape note value.
	db 81	; Primary instrument (16). Note reference (1). Primary wait (0).
	db 26	; Primary instrument (16). Note reference (10). 
	db 83	; Primary instrument (16). Note reference (3). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 73. 
	db 73	;   Escape note value.
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 214	; Primary instrument (16). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track41
	db 87	; Primary instrument (16). Note reference (7). Primary wait (0).
	db 222	; Primary instrument (16). New escaped note: 71. New wait (2).
	db 71	;   Escape note value.
	db 2	;   Escape wait value.
	db 94	; Primary instrument (16). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 17	; Primary instrument (16). Note reference (1). 
	db 82	; Primary instrument (16). Note reference (2). Primary wait (0).
	db 19	; Primary instrument (16). Note reference (3). 
	db 92	; Primary instrument (16). Note reference (12). Primary wait (0).
	db 24	; Primary instrument (16). Note reference (8). 
	db 84	; Primary instrument (16). Note reference (4). Primary wait (0).
	db 23	; Primary instrument (16). Note reference (7). 
	db 85	; Primary instrument (16). Note reference (5). Primary wait (0).
	db 31	; Primary instrument (16). Same escaped note: 66. 
	db 94	; Primary instrument (16). New escaped note: 61. Primary wait (0).
	db 61	;   Escape note value.
	db 18	; Primary instrument (16). Note reference (2). 
	db 91	; Primary instrument (16). Note reference (11). Primary wait (0).
	db 28	; Primary instrument (16). Note reference (12). 
	db 94	; Primary instrument (16). New escaped note: 59. Primary wait (0).
	db 59	;   Escape note value.
	db 20	; Primary instrument (16). Note reference (4). 
	db 89	; Primary instrument (16). Note reference (9). Primary wait (0).
	db 21	; Primary instrument (16). Note reference (5). 
	db 121	; New instrument (14). Note reference (9). Primary wait (0).
	db 14	;   Escape instrument value.
	db 5	; Note reference (5). 
	db 79	; Same escaped note: 59. Primary wait (0).
	db 4	; Note reference (4). 
	db 123	; New instrument (15). Note reference (11). Primary wait (0).
	db 15	;   Escape instrument value.
	db 12	; Note reference (12). 
	db 94	; Primary instrument (16). New escaped note: 61. Primary wait (0).
	db 61	;   Escape note value.
	db 18	; Primary instrument (16). Note reference (2). 
	db 85	; Primary instrument (16). Note reference (5). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 66. 
	db 66	;   Escape note value.
	db 84	; Primary instrument (16). Note reference (4). Primary wait (0).
	db 23	; Primary instrument (16). Note reference (7). 
	db 92	; Primary instrument (16). Note reference (12). Primary wait (0).
	db 24	; Primary instrument (16). Note reference (8). 
	db 82	; Primary instrument (16). Note reference (2). Primary wait (0).
	db 19	; Primary instrument (16). Note reference (3). 
	db 95	; Primary instrument (16). Same escaped note: 66. Primary wait (0).
	db 17	; Primary instrument (16). Note reference (1). 
	db 87	; Primary instrument (16). Note reference (7). Primary wait (0).
	db 222	; Primary instrument (16). New escaped note: 71. New wait (127).
	db 71	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track42
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 214	; Primary instrument (16). Note reference (6). New wait (2).
	db 2	;   Escape wait value.
	db 83	; Primary instrument (16). Note reference (3). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 73. 
	db 73	;   Escape note value.
	db 81	; Primary instrument (16). Note reference (1). Primary wait (0).
	db 26	; Primary instrument (16). Note reference (10). 
	db 94	; Primary instrument (16). New escaped note: 71. Primary wait (0).
	db 71	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 75. 
	db 75	;   Escape note value.
	db 86	; Primary instrument (16). Note reference (6). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 76. 
	db 76	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 73. Primary wait (0).
	db 73	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 77. 
	db 77	;   Escape note value.
	db 90	; Primary instrument (16). Note reference (10). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 78. 
	db 78	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 75. Primary wait (0).
	db 75	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 79. 
	db 79	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 76. Primary wait (0).
	db 76	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 80. 
	db 80	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 77. Primary wait (0).
	db 77	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 81. 
	db 81	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 78. Primary wait (0).
	db 78	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 82. 
	db 82	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 79. Primary wait (0).
	db 79	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 83. 
	db 83	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 80. Primary wait (0).
	db 80	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 84. 
	db 84	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 81. Primary wait (0).
	db 81	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 85. 
	db 85	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 82. Primary wait (0).
	db 82	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 86. 
	db 86	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 83. Primary wait (0).
	db 83	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 87. 
	db 87	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 84. Primary wait (0).
	db 84	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 88. 
	db 88	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 85. Primary wait (0).
	db 85	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 89. 
	db 89	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 86. Primary wait (0).
	db 86	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 90. 
	db 90	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 87. Primary wait (0).
	db 87	;   Escape note value.
	db 222	; Primary instrument (16). New escaped note: 91. New wait (127).
	db 91	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track43
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track44
	db 120	; New instrument (14). Note reference (8). Primary wait (0).
	db 14	;   Escape instrument value.
	db 198	; Note reference (6). New wait (2).
	db 2	;   Escape wait value.
	db 120	; New instrument (15). Note reference (8). Primary wait (0).
	db 15	;   Escape instrument value.
	db 6	; Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 22	; Primary instrument (16). Note reference (6). 
	db 88	; Primary instrument (16). Note reference (8). Primary wait (0).
	db 214	; Primary instrument (16). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track45
	db 87	; Primary instrument (16). Note reference (7). Primary wait (0).
	db 209	; Primary instrument (16). Note reference (1). New wait (2).
	db 2	;   Escape wait value.
	db 94	; Primary instrument (16). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 19	; Primary instrument (16). Note reference (3). 
	db 82	; Primary instrument (16). Note reference (2). Primary wait (0).
	db 24	; Primary instrument (16). Note reference (8). 
	db 92	; Primary instrument (16). Note reference (12). Primary wait (0).
	db 23	; Primary instrument (16). Note reference (7). 
	db 84	; Primary instrument (16). Note reference (4). Primary wait (0).
	db 31	; Primary instrument (16). Same escaped note: 66. 
	db 85	; Primary instrument (16). Note reference (5). Primary wait (0).
	db 18	; Primary instrument (16). Note reference (2). 
	db 94	; Primary instrument (16). New escaped note: 61. Primary wait (0).
	db 61	;   Escape note value.
	db 28	; Primary instrument (16). Note reference (12). 
	db 91	; Primary instrument (16). Note reference (11). Primary wait (0).
	db 20	; Primary instrument (16). Note reference (4). 
	db 94	; Primary instrument (16). New escaped note: 59. Primary wait (0).
	db 59	;   Escape note value.
	db 21	; Primary instrument (16). Note reference (5). 
	db 89	; Primary instrument (16). Note reference (9). Primary wait (0).
	db 30	; Primary instrument (16). New escaped note: 61. 
	db 61	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 27	; Primary instrument (16). Note reference (11). 
	db 94	; Primary instrument (16). New escaped note: 56. Primary wait (0).
	db 56	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 59. 
	db 59	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 25	; Primary instrument (16). Note reference (9). 
	db 94	; Primary instrument (16). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 57. 
	db 57	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 53. Primary wait (0).
	db 53	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 56. 
	db 56	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 52. Primary wait (0).
	db 52	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 55. 
	db 55	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 51. Primary wait (0).
	db 51	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 54. 
	db 54	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 50. Primary wait (0).
	db 50	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 53. 
	db 53	;   Escape note value.
	db 94	; Primary instrument (16). New escaped note: 49. Primary wait (0).
	db 49	;   Escape note value.
	db 30	; Primary instrument (16). New escaped note: 52. 
	db 52	;   Escape note value.
	db 80	; Primary instrument (16). Note reference (0). Primary wait (0).
	db 222	; Primary instrument (16). New escaped note: 51. New wait (127).
	db 51	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track46
	db 192	; Note reference (0). New wait (39).
	db 39	;   Escape wait value.
	db 114	; New instrument (14). Note reference (2). Primary wait (0).
	db 14	;   Escape instrument value.
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 114	; New instrument (15). Note reference (2). Primary wait (0).
	db 15	;   Escape instrument value.
	db 131	; Note reference (3). Secondary wait (4).
	db 114	; New instrument (14). Note reference (2). Primary wait (0).
	db 14	;   Escape instrument value.
	db 3	; Note reference (3). 
	db 114	; New instrument (15). Note reference (2). Primary wait (0).
	db 15	;   Escape instrument value.
	db 131	; Note reference (3). Secondary wait (4).
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track47
	db 250	; New instrument (17). Note reference (10). New wait (9).
	db 17	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 10	; Note reference (10). 
	db 26	; Primary instrument (16). Note reference (10). 
	db 54	; New instrument (18). Note reference (6). 
	db 18	;   Escape instrument value.
	db 246	; New instrument (19). Note reference (6). New wait (19).
	db 19	;   Escape instrument value.
	db 19	;   Escape wait value.
	db 243	; New instrument (17). Note reference (3). New wait (9).
	db 17	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 211	; Primary instrument (16). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track48
	db 241	; New instrument (18). Note reference (1). New wait (9).
	db 18	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 1	; Note reference (1). 
	db 49	; New instrument (19). Note reference (1). 
	db 19	;   Escape instrument value.
	db 49	; New instrument (20). Note reference (1). 
	db 20	;   Escape instrument value.
	db 241	; New instrument (21). Note reference (1). New wait (127).
	db 21	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track49
	db 241	; New instrument (18). Note reference (1). New wait (9).
	db 18	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 1	; Note reference (1). 
	db 49	; New instrument (19). Note reference (1). 
	db 19	;   Escape instrument value.
	db 54	; New instrument (17). Note reference (6). 
	db 17	;   Escape instrument value.
	db 214	; Primary instrument (16). Note reference (6). New wait (19).
	db 19	;   Escape wait value.
	db 241	; New instrument (18). Note reference (1). New wait (9).
	db 18	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 241	; New instrument (19). Note reference (1). New wait (127).
	db 19	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track50
	db 250	; New instrument (17). Note reference (10). New wait (9).
	db 17	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 10	; Note reference (10). 
	db 26	; Primary instrument (16). Note reference (10). 
	db 54	; New instrument (18). Note reference (6). 
	db 18	;   Escape instrument value.
	db 246	; New instrument (19). Note reference (6). New wait (127).
	db 19	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track51
	db 241	; New instrument (18). Note reference (1). New wait (9).
	db 18	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 1	; Note reference (1). 
	db 49	; New instrument (19). Note reference (1). 
	db 19	;   Escape instrument value.
	db 54	; New instrument (17). Note reference (6). 
	db 17	;   Escape instrument value.
	db 214	; Primary instrument (16). Note reference (6). New wait (19).
	db 19	;   Escape wait value.
	db 241	; New instrument (18). Note reference (1). New wait (9).
	db 18	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 243	; New instrument (17). Note reference (3). New wait (127).
	db 17	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track52
	db 192	; Note reference (0). New wait (9).
	db 9	;   Escape wait value.
	db 51	; New instrument (17). Note reference (3). 
	db 17	;   Escape instrument value.
	db 3	; Note reference (3). 
	db 19	; Primary instrument (16). Note reference (3). 
	db 3	; Note reference (3). 
	db 19	; Primary instrument (16). Note reference (3). 
	db 240	; New instrument (0). Note reference (0). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track53
	db 254	; New instrument (2). New escaped note: 34. New wait (9).
	db 34	;   Escape note value.
	db 2	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 14	; New escaped note: 46. 
	db 46	;   Escape note value.
	db 62	; New instrument (3). New escaped note: 0. 
	db 0	;   Escape note value.
	db 3	;   Escape instrument value.
	db 62	; New instrument (2). New escaped note: 34. 
	db 34	;   Escape note value.
	db 2	;   Escape instrument value.
	db 15	; Same escaped note: 34. 
	db 14	; New escaped note: 46. 
	db 46	;   Escape note value.
	db 62	; New instrument (3). New escaped note: 0. 
	db 0	;   Escape note value.
	db 3	;   Escape instrument value.
	db 254	; New instrument (2). New escaped note: 34. New wait (127).
	db 34	;   Escape note value.
	db 2	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track54
	db 254	; New instrument (2). New escaped note: 27. New wait (9).
	db 27	;   Escape note value.
	db 2	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 15	; Same escaped note: 27. 
	db 207	; Same escaped note: 27. New wait (19).
	db 19	;   Escape wait value.
	db 15	; Same escaped note: 27. 
	db 254	; New instrument (3). New escaped note: 0. New wait (127).
	db 0	;   Escape note value.
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track55
	db 192	; Note reference (0). New wait (59).
	db 59	;   Escape wait value.
	db 254	; New instrument (3). New escaped note: 0. New wait (9).
	db 0	;   Escape note value.
	db 3	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 207	; Same escaped note: 0. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track56
	db 254	; New instrument (3). New escaped note: 0. New wait (9).
	db 0	;   Escape note value.
	db 3	;   Escape instrument value.
	db 9	;   Escape wait value.
	db 15	; Same escaped note: 0. 
	db 207	; Same escaped note: 0. New wait (19).
	db 19	;   Escape wait value.
	db 15	; Same escaped note: 0. 
	db 207	; Same escaped note: 0. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track57
	db 254	; New instrument (3). New escaped note: 0. New wait (59).
	db 0	;   Escape note value.
	db 3	;   Escape instrument value.
	db 59	;   Escape wait value.
	db 207	; Same escaped note: 0. New wait (9).
	db 9	;   Escape wait value.
	db 207	; Same escaped note: 0. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track58
	db 242	; New instrument (1). Note reference (2). New wait (1).
	db 1	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 206	; New escaped note: 53. New wait (7).
	db 53	;   Escape note value.
	db 7	;   Escape wait value.
	db 197	; Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 50. New wait (7).
	db 50	;   Escape note value.
	db 7	;   Escape wait value.
	db 203	; Note reference (11). New wait (1).
	db 1	;   Escape wait value.
	db 192	; Note reference (0). New wait (7).
	db 7	;   Escape wait value.
	db 194	; Note reference (2). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 53. New wait (7).
	db 53	;   Escape note value.
	db 7	;   Escape wait value.
	db 197	; Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 50. New wait (7).
	db 50	;   Escape note value.
	db 7	;   Escape wait value.
	db 203	; Note reference (11). New wait (1).
	db 1	;   Escape wait value.
	db 192	; Note reference (0). New wait (7).
	db 7	;   Escape wait value.
	db 194	; Note reference (2). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 53. New wait (7).
	db 53	;   Escape note value.
	db 7	;   Escape wait value.
	db 197	; Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 50. New wait (127).
	db 50	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track59
	db 251	; New instrument (1). Note reference (11). New wait (1).
	db 1	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 192	; Note reference (0). New wait (7).
	db 7	;   Escape wait value.
	db 194	; Note reference (2). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 53. New wait (7).
	db 53	;   Escape note value.
	db 7	;   Escape wait value.
	db 197	; Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 50. New wait (7).
	db 50	;   Escape note value.
	db 7	;   Escape wait value.
	db 203	; Note reference (11). New wait (1).
	db 1	;   Escape wait value.
	db 192	; Note reference (0). New wait (7).
	db 7	;   Escape wait value.
	db 194	; Note reference (2). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 53. New wait (7).
	db 53	;   Escape note value.
	db 7	;   Escape wait value.
	db 197	; Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 50. New wait (7).
	db 50	;   Escape note value.
	db 7	;   Escape wait value.
	db 203	; Note reference (11). New wait (1).
	db 1	;   Escape wait value.
	db 192	; Note reference (0). New wait (7).
	db 7	;   Escape wait value.
	db 197	; Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 207	; Same escaped note: 50. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track60
	db 252	; New instrument (1). Note reference (12). New wait (1).
	db 1	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 206	; New escaped note: 52. New wait (7).
	db 52	;   Escape note value.
	db 7	;   Escape wait value.
	db 206	; New escaped note: 59. New wait (1).
	db 59	;   Escape note value.
	db 1	;   Escape wait value.
	db 206	; New escaped note: 47. New wait (7).
	db 47	;   Escape note value.
	db 7	;   Escape wait value.
	db 206	; New escaped note: 57. New wait (1).
	db 57	;   Escape note value.
	db 1	;   Escape wait value.
	db 206	; New escaped note: 45. New wait (7).
	db 45	;   Escape note value.
	db 7	;   Escape wait value.
	db 204	; Note reference (12). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 52. New wait (7).
	db 52	;   Escape note value.
	db 7	;   Escape wait value.
	db 206	; New escaped note: 59. New wait (1).
	db 59	;   Escape note value.
	db 1	;   Escape wait value.
	db 206	; New escaped note: 47. New wait (7).
	db 47	;   Escape note value.
	db 7	;   Escape wait value.
	db 206	; New escaped note: 57. New wait (1).
	db 57	;   Escape note value.
	db 1	;   Escape wait value.
	db 206	; New escaped note: 45. New wait (7).
	db 45	;   Escape note value.
	db 7	;   Escape wait value.
	db 204	; Note reference (12). New wait (1).
	db 1	;   Escape wait value.
	db 206	; New escaped note: 52. New wait (7).
	db 52	;   Escape note value.
	db 7	;   Escape wait value.
	db 206	; New escaped note: 57. New wait (1).
	db 57	;   Escape note value.
	db 1	;   Escape wait value.
	db 206	; New escaped note: 45. New wait (127).
	db 45	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track61
	db 241	; New instrument (1). Note reference (1). New wait (1).
	db 1	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 201	; Note reference (9). New wait (7).
	db 7	;   Escape wait value.
	db 193	; Note reference (1). New wait (1).
	db 1	;   Escape wait value.
	db 201	; Note reference (9). New wait (7).
	db 7	;   Escape wait value.
	db 193	; Note reference (1). New wait (1).
	db 1	;   Escape wait value.
	db 201	; Note reference (9). New wait (7).
	db 7	;   Escape wait value.
	db 193	; Note reference (1). New wait (1).
	db 1	;   Escape wait value.
	db 201	; Note reference (9). New wait (7).
	db 7	;   Escape wait value.
	db 193	; Note reference (1). New wait (1).
	db 1	;   Escape wait value.
	db 201	; Note reference (9). New wait (7).
	db 7	;   Escape wait value.
	db 206	; New escaped note: 82. New wait (1).
	db 82	;   Escape note value.
	db 1	;   Escape wait value.
	db 193	; Note reference (1). New wait (7).
	db 7	;   Escape wait value.
	db 193	; Note reference (1). New wait (1).
	db 1	;   Escape wait value.
	db 201	; Note reference (9). New wait (7).
	db 7	;   Escape wait value.
	db 193	; Note reference (1). New wait (1).
	db 1	;   Escape wait value.
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 48	; Note for index 0.
	db 70	; Note for index 1.
	db 65	; Note for index 2.
	db 69	; Note for index 3.
	db 63	; Note for index 4.
	db 62	; Note for index 5.
	db 72	; Note for index 6.
	db 67	; Note for index 7.
	db 68	; Note for index 8.
	db 58	; Note for index 9.
	db 74	; Note for index 10.
	db 60	; Note for index 11.
	db 64	; Note for index 12.

