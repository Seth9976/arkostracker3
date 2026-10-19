; "Burnin' Rubber" #1 1990 Ocean, Song part, encoded in the AKM (minimalist) format V0.



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

; The Instrument.
mySong_Instrument0
	db 255	; Speed.

mySong_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loops.

mySong_Instrument1
	db 0	; Speed.

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument2
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

	db 185	; Volume: 14.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 177	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 177	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 173	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 169	; Volume: 10.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 169	; Volume: 10.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 165	; Volume: 9.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 161	; Volume: 8.
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

	db 137	; Volume: 2.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 133	; Volume: 1.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument3
	db 0	; Speed.

	db 53	; Volume: 13.

	db 181	; Volume: 13.
	db 6	; Arpeggio: 3.

	db 177	; Volume: 12.
	db 14	; Arpeggio: 7.

	db 49	; Volume: 12.

	db 173	; Volume: 11.
	db 6	; Arpeggio: 3.

	db 169	; Volume: 10.
	db 14	; Arpeggio: 7.

	db 41	; Volume: 10.

	db 165	; Volume: 9.
	db 6	; Arpeggio: 3.

	db 161	; Volume: 8.
	db 14	; Arpeggio: 7.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 6	; Arpeggio: 3.

	db 153	; Volume: 6.
	db 14	; Arpeggio: 7.

	db 25	; Volume: 6.

	db 149	; Volume: 5.
	db 6	; Arpeggio: 3.

	db 149	; Volume: 5.
	db 14	; Arpeggio: 7.

	db 17	; Volume: 4.

	db 141	; Volume: 3.
	db 6	; Arpeggio: 3.

	db 141	; Volume: 3.
	db 14	; Arpeggio: 7.

	db 9	; Volume: 2.

	db 133	; Volume: 1.
	db 6	; Arpeggio: 3.

	db 133	; Volume: 1.
	db 14	; Arpeggio: 7.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument4
	db 0	; Speed.

	db 53	; Volume: 13.

	db 181	; Volume: 13.
	db 8	; Arpeggio: 4.

	db 177	; Volume: 12.
	db 18	; Arpeggio: 9.

	db 49	; Volume: 12.

	db 173	; Volume: 11.
	db 8	; Arpeggio: 4.

	db 169	; Volume: 10.
	db 18	; Arpeggio: 9.

	db 41	; Volume: 10.

	db 165	; Volume: 9.
	db 8	; Arpeggio: 4.

	db 161	; Volume: 8.
	db 18	; Arpeggio: 9.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 8	; Arpeggio: 4.

	db 153	; Volume: 6.
	db 18	; Arpeggio: 9.

	db 25	; Volume: 6.

	db 149	; Volume: 5.
	db 8	; Arpeggio: 4.

	db 149	; Volume: 5.
	db 18	; Arpeggio: 9.

	db 17	; Volume: 4.

	db 141	; Volume: 3.
	db 8	; Arpeggio: 4.

	db 141	; Volume: 3.
	db 18	; Arpeggio: 9.

	db 9	; Volume: 2.

	db 133	; Volume: 1.
	db 8	; Arpeggio: 4.

	db 133	; Volume: 1.
	db 18	; Arpeggio: 9.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument5
	db 0	; Speed.

	db 53	; Volume: 13.

	db 181	; Volume: 13.
	db 10	; Arpeggio: 5.

	db 177	; Volume: 12.
	db 18	; Arpeggio: 9.

	db 49	; Volume: 12.

	db 173	; Volume: 11.
	db 10	; Arpeggio: 5.

	db 169	; Volume: 10.
	db 18	; Arpeggio: 9.

	db 41	; Volume: 10.

	db 165	; Volume: 9.
	db 10	; Arpeggio: 5.

	db 161	; Volume: 8.
	db 18	; Arpeggio: 9.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 10	; Arpeggio: 5.

	db 153	; Volume: 6.
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

mySong_Instrument6
	db 0	; Speed.

	db 53	; Volume: 13.

	db 181	; Volume: 13.
	db 8	; Arpeggio: 4.

	db 177	; Volume: 12.
	db 14	; Arpeggio: 7.

	db 49	; Volume: 12.

	db 173	; Volume: 11.
	db 8	; Arpeggio: 4.

	db 169	; Volume: 10.
	db 14	; Arpeggio: 7.

	db 41	; Volume: 10.

	db 165	; Volume: 9.
	db 8	; Arpeggio: 4.

	db 161	; Volume: 8.
	db 14	; Arpeggio: 7.

	db 33	; Volume: 8.

	db 157	; Volume: 7.
	db 8	; Arpeggio: 4.

	db 153	; Volume: 6.
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

mySong_Instrument7
	db 0	; Speed.

	db 53	; Volume: 13.

	db 181	; Volume: 13.
	db 24	; Arpeggio: 12.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 173	; Volume: 11.
	db 24	; Arpeggio: 12.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 165	; Volume: 9.
	db 24	; Arpeggio: 12.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 157	; Volume: 7.
	db 24	; Arpeggio: 12.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 149	; Volume: 5.
	db 24	; Arpeggio: 12.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 141	; Volume: 3.
	db 24	; Arpeggio: 12.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 133	; Volume: 1.
	db 24	; Arpeggio: 12.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument8
	db 0	; Speed.

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

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument9
	db 0	; Speed.

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

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument10
	db 0	; Speed.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

; "Burnin' Rubber" #1 1990 Ocean, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 1+1	; Initial speed.

	db 1	; Most used instrument.
	db 8	; Second most used instrument.

	db 0	; Most used wait.
	db 2	; Second most used wait.

	db 74	; Default start note in tracks.
	db 7	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 47	; New height.
	db 0	; New transposition on channel 1.
	db 140	; New track (0) for channel 1, as a reference (index 12).
	db 0	; New transposition on channel 2.
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 1
	db 160	; State byte.
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 2
	db 160	; State byte.
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 3
	db 168	; State byte.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 4
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 5
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 6
	db 168	; State byte.
	db 134	; New track (4) for channel 1, as a reference (index 6).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 7
	db 168	; State byte.
	db 135	; New track (5) for channel 1, as a reference (index 7).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 8
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 9
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 10
	db 168	; State byte.
	db 138	; New track (6) for channel 1, as a reference (index 10).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 11
	db 168	; State byte.
	db ((mySong_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track7 - ($ + 1)) & 255)
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 12
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 13
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 14
	db 168	; State byte.
	db 134	; New track (4) for channel 1, as a reference (index 6).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 15
	db 168	; State byte.
	db 135	; New track (5) for channel 1, as a reference (index 7).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 16
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 17
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 18
	db 168	; State byte.
	db ((mySong_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track8 - ($ + 1)) & 255)
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 19
	db 168	; State byte.
	db ((mySong_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track9 - ($ + 1)) & 255)
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 20
	db 168	; State byte.
	db ((mySong_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track10 - ($ + 1)) & 255)
	db 136	; New track (24) for channel 2, as a reference (index 8).
	db 137	; New track (30) for channel 3, as a reference (index 9).

; Pattern 21
	db 168	; State byte.
	db ((mySong_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track11 - ($ + 1)) & 255)
	db 142	; New track (25) for channel 2, as a reference (index 14).
	db ((mySong_Subsong0_Track31 - ($ + 2)) & #ff00) / 256	; New track (31) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track31 - ($ + 1)) & 255)

; Pattern 22
	db 168	; State byte.
	db ((mySong_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track12 - ($ + 1)) & 255)
	db 136	; New track (24) for channel 2, as a reference (index 8).
	db 137	; New track (30) for channel 3, as a reference (index 9).

; Pattern 23
	db 184	; State byte.
	db ((mySong_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track13 - ($ + 1)) & 255)
	db 9	; New transposition on channel 2.
	db 142	; New track (25) for channel 2, as a reference (index 14).
	db ((mySong_Subsong0_Track32 - ($ + 2)) & #ff00) / 256	; New track (32) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track32 - ($ + 1)) & 255)

; Pattern 24
	db 184	; State byte.
	db ((mySong_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track14 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 136	; New track (24) for channel 2, as a reference (index 8).
	db 137	; New track (30) for channel 3, as a reference (index 9).

; Pattern 25
	db 184	; State byte.
	db ((mySong_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track15 - ($ + 1)) & 255)
	db 2	; New transposition on channel 2.
	db 142	; New track (25) for channel 2, as a reference (index 14).
	db ((mySong_Subsong0_Track33 - ($ + 2)) & #ff00) / 256	; New track (33) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track33 - ($ + 1)) & 255)

; Pattern 26
	db 184	; State byte.
	db ((mySong_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track16 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 136	; New track (24) for channel 2, as a reference (index 8).
	db 137	; New track (30) for channel 3, as a reference (index 9).

; Pattern 27
	db 168	; State byte.
	db ((mySong_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track17 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track26 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track34 - ($ + 2)) & #ff00) / 256	; New track (34) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track34 - ($ + 1)) & 255)

; Pattern 28
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 29
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 30
	db 168	; State byte.
	db 134	; New track (4) for channel 1, as a reference (index 6).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 31
	db 168	; State byte.
	db 135	; New track (5) for channel 1, as a reference (index 7).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 32
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 33
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 34
	db 168	; State byte.
	db 138	; New track (6) for channel 1, as a reference (index 10).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 35
	db 168	; State byte.
	db ((mySong_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track18 - ($ + 1)) & 255)
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 36
	db 168	; State byte.
	db 139	; New track (19) for channel 1, as a reference (index 11).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 37
	db 168	; State byte.
	db 143	; New track (20) for channel 1, as a reference (index 15).
	db 144	; New track (27) for channel 2, as a reference (index 16).
	db 141	; New track (35) for channel 3, as a reference (index 13).

; Pattern 38
	db 168	; State byte.
	db 139	; New track (19) for channel 1, as a reference (index 11).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 39
	db 168	; State byte.
	db 143	; New track (20) for channel 1, as a reference (index 15).
	db 144	; New track (27) for channel 2, as a reference (index 16).
	db 141	; New track (35) for channel 3, as a reference (index 13).

; Pattern 40
	db 168	; State byte.
	db 139	; New track (19) for channel 1, as a reference (index 11).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 41
	db 168	; State byte.
	db 143	; New track (20) for channel 1, as a reference (index 15).
	db 144	; New track (27) for channel 2, as a reference (index 16).
	db 141	; New track (35) for channel 3, as a reference (index 13).

; Pattern 42
	db 168	; State byte.
	db 139	; New track (19) for channel 1, as a reference (index 11).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 43
	db 172	; State byte.
	db 2	; New transposition on channel 1.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 44
	db 248	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 2	; New transposition on channel 2.
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 2	; New transposition on channel 3.
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 45
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 46
	db 168	; State byte.
	db 134	; New track (4) for channel 1, as a reference (index 6).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 47
	db 168	; State byte.
	db 135	; New track (5) for channel 1, as a reference (index 7).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 48
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 49
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 50
	db 168	; State byte.
	db 138	; New track (6) for channel 1, as a reference (index 10).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 51
	db 168	; State byte.
	db ((mySong_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track7 - ($ + 1)) & 255)
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 52
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 53
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 54
	db 168	; State byte.
	db 134	; New track (4) for channel 1, as a reference (index 6).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 55
	db 168	; State byte.
	db 135	; New track (5) for channel 1, as a reference (index 7).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 56
	db 168	; State byte.
	db 132	; New track (2) for channel 1, as a reference (index 4).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 57
	db 168	; State byte.
	db 133	; New track (3) for channel 1, as a reference (index 5).
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

; Pattern 58
	db 168	; State byte.
	db 138	; New track (6) for channel 1, as a reference (index 10).
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 129	; New track (28) for channel 3, as a reference (index 1).

; Pattern 59
	db 172	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track21 - ($ + 2)) & #ff00) / 256	; New track (21) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track21 - ($ + 1)) & 255)
	db 130	; New track (23) for channel 2, as a reference (index 2).
	db 131	; New track (29) for channel 3, as a reference (index 3).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes
	dw mySong_Subsong0_Track22	; Track 22, index 0.
	dw mySong_Subsong0_Track28	; Track 28, index 1.
	dw mySong_Subsong0_Track23	; Track 23, index 2.
	dw mySong_Subsong0_Track29	; Track 29, index 3.
	dw mySong_Subsong0_Track2	; Track 2, index 4.
	dw mySong_Subsong0_Track3	; Track 3, index 5.
	dw mySong_Subsong0_Track4	; Track 4, index 6.
	dw mySong_Subsong0_Track5	; Track 5, index 7.
	dw mySong_Subsong0_Track24	; Track 24, index 8.
	dw mySong_Subsong0_Track30	; Track 30, index 9.
	dw mySong_Subsong0_Track6	; Track 6, index 10.
	dw mySong_Subsong0_Track19	; Track 19, index 11.
	dw mySong_Subsong0_Track0	; Track 0, index 12.
	dw mySong_Subsong0_Track35	; Track 35, index 13.
	dw mySong_Subsong0_Track25	; Track 25, index 14.
	dw mySong_Subsong0_Track20	; Track 20, index 15.
	dw mySong_Subsong0_Track27	; Track 27, index 16.

mySong_Subsong0_Track0
	db 243	; New instrument (0). Note reference (3). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 243	; New instrument (0). Note reference (3). New wait (41).
	db 0	;   Escape instrument value.
	db 41	;   Escape wait value.
	db 254	; New instrument (7). New escaped note: 57. New wait (127).
	db 57	;   Escape note value.
	db 7	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track2
	db 194	; Note reference (2). New wait (17).
	db 17	;   Escape wait value.
	db 78	; New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 196	; Note reference (4). New wait (22).
	db 22	;   Escape wait value.
	db 194	; Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track3
	db 196	; Note reference (4). New wait (5).
	db 5	;   Escape wait value.
	db 7	; Note reference (7). 
	db 138	; Note reference (10). Secondary wait (2).
	db 179	; New instrument (0). Note reference (3). Secondary wait (2).
	db 0	;   Escape instrument value.
	db 250	; New instrument (7). Note reference (10). New wait (1).
	db 7	;   Escape instrument value.
	db 1	;   Escape wait value.
	db 115	; New instrument (0). Note reference (3). Primary wait (0).
	db 0	;   Escape instrument value.
	db 250	; New instrument (7). Note reference (10). New wait (8).
	db 7	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 196	; Note reference (4). New wait (11).
	db 11	;   Escape wait value.
	db 206	; New escaped note: 60. New wait (127).
	db 60	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track4
	db 194	; Note reference (2). New wait (17).
	db 17	;   Escape wait value.
	db 78	; New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 196	; Note reference (4). New wait (22).
	db 22	;   Escape wait value.
	db 193	; Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track5
	db 139	; Note reference (11). Secondary wait (2).
	db 179	; New instrument (0). Note reference (3). Secondary wait (2).
	db 0	;   Escape instrument value.
	db 190	; New instrument (7). New escaped note: 56. Secondary wait (2).
	db 56	;   Escape note value.
	db 7	;   Escape instrument value.
	db 179	; New instrument (0). Note reference (3). Secondary wait (2).
	db 0	;   Escape instrument value.
	db 254	; New instrument (7). New escaped note: 57. New wait (5).
	db 57	;   Escape note value.
	db 7	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 194	; Note reference (2). New wait (23).
	db 23	;   Escape wait value.
	db 207	; Same escaped note: 57. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track6
	db 194	; Note reference (2). New wait (17).
	db 17	;   Escape wait value.
	db 78	; New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 196	; Note reference (4). New wait (16).
	db 16	;   Escape wait value.
	db 79	; Same escaped note: 68. Primary wait (0).
	db 196	; Note reference (4). New wait (4).
	db 4	;   Escape wait value.
	db 138	; Note reference (10). Secondary wait (2).
	db 199	; Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track7
	db 194	; Note reference (2). New wait (41).
	db 41	;   Escape wait value.
	db 206	; New escaped note: 57. New wait (127).
	db 57	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track8
	db 194	; Note reference (2). New wait (17).
	db 17	;   Escape wait value.
	db 78	; New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 196	; Note reference (4). New wait (16).
	db 16	;   Escape wait value.
	db 165	; Secondary instrument (8). Note reference (5). Secondary wait (2).
	db 168	; Secondary instrument (8). Note reference (8). Secondary wait (2).
	db 174	; Secondary instrument (8). New escaped note: 45. Secondary wait (2).
	db 45	;   Escape note value.
	db 225	; Secondary instrument (8). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track9
	db 160	; Secondary instrument (8). Note reference (0). Secondary wait (2).
	db 161	; Secondary instrument (8). Note reference (1). Secondary wait (2).
	db 160	; Secondary instrument (8). Note reference (0). Secondary wait (2).
	db 171	; Secondary instrument (8). Note reference (11). Secondary wait (2).
	db 174	; Secondary instrument (8). New escaped note: 57. Secondary wait (2).
	db 57	;   Escape note value.
	db 160	; Secondary instrument (8). Note reference (0). Secondary wait (2).
	db 175	; Secondary instrument (8). Same escaped note: 57. Secondary wait (2).
	db 174	; Secondary instrument (8). New escaped note: 60. Secondary wait (2).
	db 60	;   Escape note value.
	db 162	; Secondary instrument (8). Note reference (2). Secondary wait (2).
	db 174	; Secondary instrument (8). New escaped note: 57. Secondary wait (2).
	db 57	;   Escape note value.
	db 174	; Secondary instrument (8). New escaped note: 60. Secondary wait (2).
	db 60	;   Escape note value.
	db 162	; Secondary instrument (8). Note reference (2). Secondary wait (2).
	db 167	; Secondary instrument (8). Note reference (7). Secondary wait (2).
	db 170	; Secondary instrument (8). Note reference (10). Secondary wait (2).
	db 164	; Secondary instrument (8). Note reference (4). Secondary wait (2).
	db 238	; Secondary instrument (8). New escaped note: 72. New wait (127).
	db 72	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track10
	db 239	; Secondary instrument (8). Same escaped note: 74. New wait (17).
	db 17	;   Escape wait value.
	db 238	; Secondary instrument (8). New escaped note: 70. New wait (23).
	db 70	;   Escape note value.
	db 23	;   Escape wait value.
	db 164	; Secondary instrument (8). Note reference (4). Secondary wait (2).
	db 239	; Secondary instrument (8). Same escaped note: 70. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track11
	db 238	; Secondary instrument (8). New escaped note: 72. New wait (5).
	db 72	;   Escape note value.
	db 5	;   Escape wait value.
	db 36	; Secondary instrument (8). Note reference (4). 
	db 42	; Secondary instrument (8). Note reference (10). 
	db 231	; Secondary instrument (8). Note reference (7). New wait (11).
	db 11	;   Escape wait value.
	db 174	; Secondary instrument (8). New escaped note: 60. Secondary wait (2).
	db 60	;   Escape note value.
	db 167	; Secondary instrument (8). Note reference (7). Secondary wait (2).
	db 170	; Secondary instrument (8). Note reference (10). Secondary wait (2).
	db 167	; Secondary instrument (8). Note reference (7). Secondary wait (2).
	db 164	; Secondary instrument (8). Note reference (4). Secondary wait (2).
	db 238	; Secondary instrument (8). New escaped note: 72. New wait (127).
	db 72	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track12
	db 239	; Secondary instrument (8). Same escaped note: 74. New wait (17).
	db 17	;   Escape wait value.
	db 238	; Secondary instrument (8). New escaped note: 70. New wait (23).
	db 70	;   Escape note value.
	db 23	;   Escape wait value.
	db 174	; Secondary instrument (8). New escaped note: 74. Secondary wait (2).
	db 74	;   Escape note value.
	db 239	; Secondary instrument (8). Same escaped note: 74. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track13
	db 164	; Secondary instrument (8). Note reference (4). Secondary wait (2).
	db 179	; New instrument (0). Note reference (3). Secondary wait (2).
	db 0	;   Escape instrument value.
	db 162	; Secondary instrument (8). Note reference (2). Secondary wait (2).
	db 131	; Note reference (3). Secondary wait (2).
	db 170	; Secondary instrument (8). Note reference (10). Secondary wait (2).
	db 228	; Secondary instrument (8). Note reference (4). New wait (5).
	db 5	;   Escape wait value.
	db 226	; Secondary instrument (8). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track14
	db 239	; Secondary instrument (8). Same escaped note: 74. New wait (17).
	db 17	;   Escape wait value.
	db 238	; Secondary instrument (8). New escaped note: 70. New wait (23).
	db 70	;   Escape note value.
	db 23	;   Escape wait value.
	db 175	; Secondary instrument (8). Same escaped note: 70. Secondary wait (2).
	db 239	; Secondary instrument (8). Same escaped note: 70. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track15
	db 238	; Secondary instrument (8). New escaped note: 70. New wait (5).
	db 70	;   Escape note value.
	db 5	;   Escape wait value.
	db 36	; Secondary instrument (8). Note reference (4). 
	db 36	; Secondary instrument (8). Note reference (4). 
	db 234	; Secondary instrument (8). Note reference (10). New wait (11).
	db 11	;   Escape wait value.
	db 34	; Secondary instrument (8). Note reference (2). 
	db 162	; Secondary instrument (8). Note reference (2). Secondary wait (2).
	db 233	; Secondary instrument (8). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track16
	db 231	; Secondary instrument (8). Note reference (7). New wait (5).
	db 5	;   Escape wait value.
	db 41	; Secondary instrument (8). Note reference (9). 
	db 41	; Secondary instrument (8). Note reference (9). 
	db 233	; Secondary instrument (8). Note reference (9). New wait (17).
	db 17	;   Escape wait value.
	db 231	; Secondary instrument (8). Note reference (7). New wait (5).
	db 5	;   Escape wait value.
	db 233	; Secondary instrument (8). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track17
	db 249	; New instrument (9). Note reference (9). New wait (11).
	db 9	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 226	; Secondary instrument (8). Note reference (2). New wait (5).
	db 5	;   Escape wait value.
	db 238	; Secondary instrument (8). New escaped note: 61. New wait (23).
	db 61	;   Escape note value.
	db 23	;   Escape wait value.
	db 254	; New instrument (7). New escaped note: 57. New wait (127).
	db 57	;   Escape note value.
	db 7	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track18
	db 194	; Note reference (2). New wait (35).
	db 35	;   Escape wait value.
	db 242	; New instrument (10). Note reference (2). New wait (5).
	db 10	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 137	; Note reference (9). Secondary wait (2).
	db 199	; Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track19
	db 242	; New instrument (10). Note reference (2). New wait (127).
	db 10	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track20
	db 243	; New instrument (0). Note reference (3). New wait (35).
	db 0	;   Escape instrument value.
	db 35	;   Escape wait value.
	db 242	; New instrument (10). Note reference (2). New wait (5).
	db 10	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 137	; Note reference (9). Secondary wait (2).
	db 199	; Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track21
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track22
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 26. New wait (7).
	db 26	;   Escape note value.
	db 7	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 213	; Primary instrument (1). Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 36. New wait (1).
	db 36	;   Escape note value.
	db 1	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 21	; Primary instrument (1). Note reference (5). 
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 26. New wait (4).
	db 26	;   Escape note value.
	db 4	;   Escape wait value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 31	; Primary instrument (1). Same escaped note: 26. 
	db 198	; Note reference (6). New wait (5).
	db 5	;   Escape wait value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 36. New wait (1).
	db 36	;   Escape note value.
	db 1	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track23
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 26. New wait (7).
	db 26	;   Escape note value.
	db 7	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 213	; Primary instrument (1). Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 36. New wait (1).
	db 36	;   Escape note value.
	db 1	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 21	; Primary instrument (1). Note reference (5). 
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 220	; Primary instrument (1). Note reference (12). New wait (4).
	db 4	;   Escape wait value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 28	; Primary instrument (1). Note reference (12). 
	db 134	; Note reference (6). Secondary wait (2).
	db 94	; Primary instrument (1). New escaped note: 43. Primary wait (0).
	db 43	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 31. New wait (1).
	db 31	;   Escape note value.
	db 1	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 30	; Primary instrument (1). New escaped note: 33. 
	db 33	;   Escape note value.
	db 198	; Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track24
	db 94	; Primary instrument (1). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 34. New wait (7).
	db 34	;   Escape note value.
	db 7	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 34. New wait (1).
	db 34	;   Escape note value.
	db 1	;   Escape wait value.
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 34. New wait (7).
	db 34	;   Escape note value.
	db 7	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 34. New wait (4).
	db 34	;   Escape note value.
	db 4	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 34. New wait (1).
	db 34	;   Escape note value.
	db 1	;   Escape wait value.
	db 198	; Note reference (6). New wait (5).
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 34. New wait (127).
	db 34	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track25
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 220	; Primary instrument (1). Note reference (12). New wait (7).
	db 7	;   Escape wait value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 220	; Primary instrument (1). Note reference (12). New wait (1).
	db 1	;   Escape wait value.
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 220	; Primary instrument (1). Note reference (12). New wait (7).
	db 7	;   Escape wait value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 220	; Primary instrument (1). Note reference (12). New wait (4).
	db 4	;   Escape wait value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 220	; Primary instrument (1). Note reference (12). New wait (1).
	db 1	;   Escape wait value.
	db 134	; Note reference (6). Secondary wait (2).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 28	; Primary instrument (1). Note reference (12). 
	db 88	; Primary instrument (1). Note reference (8). Primary wait (0).
	db 220	; Primary instrument (1). Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track26
	db 94	; Primary instrument (1). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 33. New wait (7).
	db 33	;   Escape note value.
	db 7	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 33. New wait (1).
	db 33	;   Escape note value.
	db 1	;   Escape wait value.
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 33. New wait (7).
	db 33	;   Escape note value.
	db 7	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 33. New wait (4).
	db 33	;   Escape note value.
	db 4	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 33. New wait (1).
	db 33	;   Escape note value.
	db 1	;   Escape wait value.
	db 198	; Note reference (6). New wait (5).
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 36. Primary wait (0).
	db 36	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 24. New wait (1).
	db 24	;   Escape note value.
	db 1	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 37. Primary wait (0).
	db 37	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 25. New wait (127).
	db 25	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track27
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 26. New wait (7).
	db 26	;   Escape note value.
	db 7	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 213	; Primary instrument (1). Note reference (5). New wait (1).
	db 1	;   Escape wait value.
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 36. New wait (1).
	db 36	;   Escape note value.
	db 1	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 21	; Primary instrument (1). Note reference (5). 
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 26. New wait (4).
	db 26	;   Escape note value.
	db 4	;   Escape wait value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 31	; Primary instrument (1). Same escaped note: 26. 
	db 134	; Note reference (6). Secondary wait (2).
	db 94	; Primary instrument (1). New escaped note: 43. Primary wait (0).
	db 43	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 31. New wait (1).
	db 31	;   Escape note value.
	db 1	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (0).
	db 44	;   Escape note value.
	db 30	; Primary instrument (1). New escaped note: 32. 
	db 32	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 33. New wait (127).
	db 33	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track28
	db 240	; New instrument (4). Note reference (0). New wait (8).
	db 4	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 49	; New instrument (3). Note reference (1). 
	db 3	;   Escape instrument value.
	db 48	; New instrument (4). Note reference (0). 
	db 4	;   Escape instrument value.
	db 49	; New instrument (3). Note reference (1). 
	db 3	;   Escape instrument value.
	db 240	; New instrument (4). Note reference (0). New wait (5).
	db 4	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 241	; New instrument (3). Note reference (1). New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track29
	db 240	; New instrument (4). Note reference (0). New wait (8).
	db 4	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 49	; New instrument (3). Note reference (1). 
	db 3	;   Escape instrument value.
	db 240	; New instrument (4). Note reference (0). New wait (5).
	db 4	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 51	; New instrument (5). Note reference (3). 
	db 5	;   Escape instrument value.
	db 3	; Note reference (3). 
	db 1	; Note reference (1). 
	db 193	; Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track30
	db 240	; New instrument (5). Note reference (0). New wait (8).
	db 5	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 0	; Note reference (0). 
	db 0	; Note reference (0). 
	db 192	; Note reference (0). New wait (5).
	db 5	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (2).
	db 0	; Note reference (0). 
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track31
	db 240	; New instrument (6). Note reference (0). New wait (8).
	db 6	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 0	; Note reference (0). 
	db 0	; Note reference (0). 
	db 192	; Note reference (0). New wait (5).
	db 5	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (2).
	db 0	; Note reference (0). 
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track32
	db 240	; New instrument (4). Note reference (0). New wait (8).
	db 4	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 0	; Note reference (0). 
	db 0	; Note reference (0). 
	db 192	; Note reference (0). New wait (5).
	db 5	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (2).
	db 0	; Note reference (0). 
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track33
	db 251	; New instrument (3). Note reference (11). New wait (8).
	db 3	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 11	; Note reference (11). 
	db 11	; Note reference (11). 
	db 203	; Note reference (11). New wait (5).
	db 5	;   Escape wait value.
	db 139	; Note reference (11). Secondary wait (2).
	db 11	; Note reference (11). 
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track34
	db 254	; New instrument (5). New escaped note: 52. New wait (8).
	db 52	;   Escape note value.
	db 5	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 15	; Same escaped note: 52. 
	db 15	; Same escaped note: 52. 
	db 15	; Same escaped note: 52. 
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 243	; New instrument (0). Note reference (3). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track35
	db 240	; New instrument (4). Note reference (0). New wait (8).
	db 4	;   Escape instrument value.
	db 8	;   Escape wait value.
	db 49	; New instrument (3). Note reference (1). 
	db 3	;   Escape instrument value.
	db 240	; New instrument (4). Note reference (0). New wait (5).
	db 4	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 49	; New instrument (3). Note reference (1). 
	db 3	;   Escape instrument value.
	db 1	; Note reference (1). 
	db 48	; New instrument (4). Note reference (0). 
	db 4	;   Escape instrument value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 53	; Note for index 0.
	db 50	; Note for index 1.
	db 62	; Note for index 2.
	db 48	; Note for index 3.
	db 69	; Note for index 4.
	db 38	; Note for index 5.
	db 0	; Note for index 6.
	db 65	; Note for index 7.
	db 41	; Note for index 8.
	db 64	; Note for index 9.
	db 67	; Note for index 10.
	db 55	; Note for index 11.
	db 29	; Note for index 12.

