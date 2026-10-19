; "Jet Set Willy" menu 1984 Software Projects, Song part, encoded in the AKM (minimalist) format V0.



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

; The Instrument.
mySong_Instrument0
	db 255	; Speed.

mySong_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loops.

mySong_Instrument1
	db 0	; Speed.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 49	; Volume: 12.

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

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument2
	db 0	; Speed.

	db 57	; Volume: 14.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

; "Jet Set Willy" menu 1984 Software Projects, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 2	; Initial speed.

	db 1	; Most used instrument.
	db 2	; Second most used instrument.

	db 6	; Most used wait.
	db 0	; Second most used wait.

	db 26	; Default start note in tracks.
	db 0	; Default start instrument in tracks.
	db 21	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 83	; New height.
	db 0	; New transposition on channel 1.
	db 132	; New track (0) for channel 1, as a reference (index 4).
	db 0	; New transposition on channel 2.
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 134	; New track (74) for channel 3, as a reference (index 6).

; Pattern 1
	db 80	; State byte.
	db -2	; New transposition on channel 2.
	db -2	; New transposition on channel 3.

; Pattern 2
	db 248	; State byte.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track55 - ($ + 2)) & #ff00) / 256	; New track (55) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track55 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track75 - ($ + 2)) & #ff00) / 256	; New track (75) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track75 - ($ + 1)) & 255)

; Pattern 3
	db 168	; State byte.
	db ((mySong_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track2 - ($ + 1)) & 255)
	db 133	; New track (56) for channel 2, as a reference (index 5).
	db 140	; New track (76) for channel 3, as a reference (index 12).

; Pattern 4
	db 168	; State byte.
	db ((mySong_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track3 - ($ + 1)) & 255)
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db ((mySong_Subsong0_Track77 - ($ + 2)) & #ff00) / 256	; New track (77) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track77 - ($ + 1)) & 255)

; Pattern 5
	db 152	; State byte.
	db 141	; New track (4) for channel 1, as a reference (index 13).
	db -1	; New transposition on channel 2.
	db 130	; New track (78) for channel 3, as a reference (index 2).

; Pattern 6
	db 184	; State byte.
	db ((mySong_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track5 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 142	; New track (57) for channel 2, as a reference (index 14).
	db 137	; New track (79) for channel 3, as a reference (index 9).

; Pattern 7
	db 184	; State byte.
	db ((mySong_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track6 - ($ + 1)) & 255)
	db 3	; New transposition on channel 2.
	db 133	; New track (56) for channel 2, as a reference (index 5).
	db ((mySong_Subsong0_Track80 - ($ + 2)) & #ff00) / 256	; New track (80) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track80 - ($ + 1)) & 255)

; Pattern 8
	db 184	; State byte.
	db ((mySong_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track7 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 129	; New track (58) for channel 2, as a reference (index 1).
	db ((mySong_Subsong0_Track81 - ($ + 2)) & #ff00) / 256	; New track (81) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track81 - ($ + 1)) & 255)

; Pattern 9
	db 184	; State byte.
	db ((mySong_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track8 - ($ + 1)) & 255)
	db 3	; New transposition on channel 2.
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db ((mySong_Subsong0_Track82 - ($ + 2)) & #ff00) / 256	; New track (82) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track82 - ($ + 1)) & 255)

; Pattern 10
	db 216	; State byte.
	db ((mySong_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track9 - ($ + 1)) & 255)
	db 1	; New transposition on channel 2.
	db -1	; New transposition on channel 3.
	db 130	; New track (78) for channel 3, as a reference (index 2).

; Pattern 11
	db 248	; State byte.
	db ((mySong_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track10 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track59 - ($ + 2)) & #ff00) / 256	; New track (59) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track59 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track83 - ($ + 2)) & #ff00) / 256	; New track (83) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track83 - ($ + 1)) & 255)

; Pattern 12
	db 168	; State byte.
	db ((mySong_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track11 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track60 - ($ + 2)) & #ff00) / 256	; New track (60) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track60 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track84 - ($ + 2)) & #ff00) / 256	; New track (84) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track84 - ($ + 1)) & 255)

; Pattern 13
	db 232	; State byte.
	db ((mySong_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track12 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track61 - ($ + 2)) & #ff00) / 256	; New track (61) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track61 - ($ + 1)) & 255)
	db 22	; New transposition on channel 3.
	db 140	; New track (76) for channel 3, as a reference (index 12).

; Pattern 14
	db 248	; State byte.
	db ((mySong_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track13 - ($ + 1)) & 255)
	db -2	; New transposition on channel 2.
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track85 - ($ + 2)) & #ff00) / 256	; New track (85) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track85 - ($ + 1)) & 255)

; Pattern 15
	db 188	; State byte.
	db 3	; New transposition on channel 1.
	db 132	; New track (0) for channel 1, as a reference (index 4).
	db 0	; New transposition on channel 2.
	db 138	; New track (62) for channel 2, as a reference (index 10).
	db 136	; New track (86) for channel 3, as a reference (index 8).

; Pattern 16
	db 188	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track14 - ($ + 1)) & 255)
	db -2	; New transposition on channel 2.
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db 135	; New track (87) for channel 3, as a reference (index 7).

; Pattern 17
	db 188	; State byte.
	db 3	; New transposition on channel 1.
	db 132	; New track (0) for channel 1, as a reference (index 4).
	db 0	; New transposition on channel 2.
	db 138	; New track (62) for channel 2, as a reference (index 10).
	db 136	; New track (86) for channel 3, as a reference (index 8).

; Pattern 18
	db 188	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track15 - ($ + 1)) & 255)
	db 2	; New transposition on channel 2.
	db ((mySong_Subsong0_Track55 - ($ + 2)) & #ff00) / 256	; New track (55) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track55 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track88 - ($ + 2)) & #ff00) / 256	; New track (88) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track88 - ($ + 1)) & 255)

; Pattern 19
	db 184	; State byte.
	db ((mySong_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track16 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 139	; New track (63) for channel 2, as a reference (index 11).
	db ((mySong_Subsong0_Track89 - ($ + 2)) & #ff00) / 256	; New track (89) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track89 - ($ + 1)) & 255)

; Pattern 20
	db 152	; State byte.
	db ((mySong_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track17 - ($ + 1)) & 255)
	db 6	; New transposition on channel 2.
	db ((mySong_Subsong0_Track90 - ($ + 2)) & #ff00) / 256	; New track (90) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track90 - ($ + 1)) & 255)

; Pattern 21
	db 184	; State byte.
	db ((mySong_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track18 - ($ + 1)) & 255)
	db 5	; New transposition on channel 2.
	db 133	; New track (56) for channel 2, as a reference (index 5).
	db ((mySong_Subsong0_Track91 - ($ + 2)) & #ff00) / 256	; New track (91) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track91 - ($ + 1)) & 255)

; Pattern 22
	db 248	; State byte.
	db ((mySong_Subsong0_Track19 - ($ + 2)) & #ff00) / 256	; New track (19) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track19 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db 6	; New transposition on channel 3.
	db ((mySong_Subsong0_Track82 - ($ + 2)) & #ff00) / 256	; New track (82) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track82 - ($ + 1)) & 255)

; Pattern 23
	db 216	; State byte.
	db ((mySong_Subsong0_Track20 - ($ + 2)) & #ff00) / 256	; New track (20) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track20 - ($ + 1)) & 255)
	db 4	; New transposition on channel 2.
	db 5	; New transposition on channel 3.
	db 130	; New track (78) for channel 3, as a reference (index 2).

; Pattern 24
	db 248	; State byte.
	db ((mySong_Subsong0_Track21 - ($ + 2)) & #ff00) / 256	; New track (21) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track21 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track64 - ($ + 2)) & #ff00) / 256	; New track (64) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track64 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track92 - ($ + 2)) & #ff00) / 256	; New track (92) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track92 - ($ + 1)) & 255)

; Pattern 25
	db 232	; State byte.
	db ((mySong_Subsong0_Track22 - ($ + 2)) & #ff00) / 256	; New track (22) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track22 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track65 - ($ + 2)) & #ff00) / 256	; New track (65) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track65 - ($ + 1)) & 255)
	db 4	; New transposition on channel 3.
	db 135	; New track (87) for channel 3, as a reference (index 7).

; Pattern 26
	db 232	; State byte.
	db ((mySong_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track23 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track66 - ($ + 2)) & #ff00) / 256	; New track (66) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track66 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track93 - ($ + 2)) & #ff00) / 256	; New track (93) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track93 - ($ + 1)) & 255)

; Pattern 27
	db 184	; State byte.
	db ((mySong_Subsong0_Track24 - ($ + 2)) & #ff00) / 256	; New track (24) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track24 - ($ + 1)) & 255)
	db -8	; New transposition on channel 2.
	db 129	; New track (58) for channel 2, as a reference (index 1).
	db 131	; New track (94) for channel 3, as a reference (index 3).

; Pattern 28
	db 8	; State byte.
	db ((mySong_Subsong0_Track25 - ($ + 2)) & #ff00) / 256	; New track (25) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track25 - ($ + 1)) & 255)

; Pattern 29
	db 8	; State byte.
	db ((mySong_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track26 - ($ + 1)) & 255)

; Pattern 30
	db 8	; State byte.
	db ((mySong_Subsong0_Track27 - ($ + 2)) & #ff00) / 256	; New track (27) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track27 - ($ + 1)) & 255)

; Pattern 31
	db 8	; State byte.
	db ((mySong_Subsong0_Track28 - ($ + 2)) & #ff00) / 256	; New track (28) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track28 - ($ + 1)) & 255)

; Pattern 32
	db 8	; State byte.
	db ((mySong_Subsong0_Track29 - ($ + 2)) & #ff00) / 256	; New track (29) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track29 - ($ + 1)) & 255)

; Pattern 33
	db 12	; State byte.
	db 10	; New transposition on channel 1.
	db ((mySong_Subsong0_Track28 - ($ + 2)) & #ff00) / 256	; New track (28) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track28 - ($ + 1)) & 255)

; Pattern 34
	db 252	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track30 - ($ + 2)) & #ff00) / 256	; New track (30) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track30 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db -5	; New transposition on channel 3.
	db 134	; New track (74) for channel 3, as a reference (index 6).

; Pattern 35
	db 8	; State byte.
	db ((mySong_Subsong0_Track31 - ($ + 2)) & #ff00) / 256	; New track (31) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track31 - ($ + 1)) & 255)

; Pattern 36
	db 248	; State byte.
	db ((mySong_Subsong0_Track32 - ($ + 2)) & #ff00) / 256	; New track (32) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track32 - ($ + 1)) & 255)
	db -8	; New transposition on channel 2.
	db 129	; New track (58) for channel 2, as a reference (index 1).
	db 0	; New transposition on channel 3.
	db 131	; New track (94) for channel 3, as a reference (index 3).

; Pattern 37
	db 8	; State byte.
	db ((mySong_Subsong0_Track33 - ($ + 2)) & #ff00) / 256	; New track (33) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track33 - ($ + 1)) & 255)

; Pattern 38
	db 8	; State byte.
	db ((mySong_Subsong0_Track34 - ($ + 2)) & #ff00) / 256	; New track (34) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track34 - ($ + 1)) & 255)

; Pattern 39
	db 248	; State byte.
	db ((mySong_Subsong0_Track35 - ($ + 2)) & #ff00) / 256	; New track (35) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track35 - ($ + 1)) & 255)
	db 3	; New transposition on channel 2.
	db 139	; New track (63) for channel 2, as a reference (index 11).
	db -24	; New transposition on channel 3.
	db 137	; New track (79) for channel 3, as a reference (index 9).

; Pattern 40
	db 248	; State byte.
	db ((mySong_Subsong0_Track36 - ($ + 2)) & #ff00) / 256	; New track (36) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track36 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track67 - ($ + 2)) & #ff00) / 256	; New track (67) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track67 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track95 - ($ + 2)) & #ff00) / 256	; New track (95) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track95 - ($ + 1)) & 255)

; Pattern 41
	db 168	; State byte.
	db ((mySong_Subsong0_Track37 - ($ + 2)) & #ff00) / 256	; New track (37) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track37 - ($ + 1)) & 255)
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db ((mySong_Subsong0_Track77 - ($ + 2)) & #ff00) / 256	; New track (77) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track77 - ($ + 1)) & 255)

; Pattern 42
	db 152	; State byte.
	db 141	; New track (4) for channel 1, as a reference (index 13).
	db -1	; New transposition on channel 2.
	db 130	; New track (78) for channel 3, as a reference (index 2).

; Pattern 43
	db 184	; State byte.
	db ((mySong_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track5 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 142	; New track (57) for channel 2, as a reference (index 14).
	db 137	; New track (79) for channel 3, as a reference (index 9).

; Pattern 44
	db 184	; State byte.
	db ((mySong_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track6 - ($ + 1)) & 255)
	db 3	; New transposition on channel 2.
	db 133	; New track (56) for channel 2, as a reference (index 5).
	db ((mySong_Subsong0_Track80 - ($ + 2)) & #ff00) / 256	; New track (80) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track80 - ($ + 1)) & 255)

; Pattern 45
	db 168	; State byte.
	db ((mySong_Subsong0_Track38 - ($ + 2)) & #ff00) / 256	; New track (38) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track38 - ($ + 1)) & 255)
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db ((mySong_Subsong0_Track96 - ($ + 2)) & #ff00) / 256	; New track (96) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track96 - ($ + 1)) & 255)

; Pattern 46
	db 220	; State byte.
	db 3	; New transposition on channel 1.
	db 141	; New track (4) for channel 1, as a reference (index 13).
	db 2	; New transposition on channel 2.
	db 3	; New transposition on channel 3.
	db 130	; New track (78) for channel 3, as a reference (index 2).

; Pattern 47
	db 252	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track39 - ($ + 2)) & #ff00) / 256	; New track (39) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track39 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track68 - ($ + 2)) & #ff00) / 256	; New track (68) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track68 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track97 - ($ + 2)) & #ff00) / 256	; New track (97) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track97 - ($ + 1)) & 255)

; Pattern 48
	db 248	; State byte.
	db ((mySong_Subsong0_Track40 - ($ + 2)) & #ff00) / 256	; New track (40) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track40 - ($ + 1)) & 255)
	db 7	; New transposition on channel 2.
	db 139	; New track (63) for channel 2, as a reference (index 11).
	db 7	; New transposition on channel 3.
	db 137	; New track (79) for channel 3, as a reference (index 9).

; Pattern 49
	db 248	; State byte.
	db ((mySong_Subsong0_Track41 - ($ + 2)) & #ff00) / 256	; New track (41) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track41 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track67 - ($ + 2)) & #ff00) / 256	; New track (67) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track67 - ($ + 1)) & 255)
	db 3	; New transposition on channel 3.
	db ((mySong_Subsong0_Track89 - ($ + 2)) & #ff00) / 256	; New track (89) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track89 - ($ + 1)) & 255)

; Pattern 50
	db 236	; State byte.
	db 2	; New transposition on channel 1.
	db ((mySong_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track13 - ($ + 1)) & 255)
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db 2	; New transposition on channel 3.
	db 135	; New track (87) for channel 3, as a reference (index 7).

; Pattern 51
	db 188	; State byte.
	db 5	; New transposition on channel 1.
	db 132	; New track (0) for channel 1, as a reference (index 4).
	db 2	; New transposition on channel 2.
	db 138	; New track (62) for channel 2, as a reference (index 10).
	db 136	; New track (86) for channel 3, as a reference (index 8).

; Pattern 52
	db 188	; State byte.
	db 2	; New transposition on channel 1.
	db ((mySong_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track14 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db 135	; New track (87) for channel 3, as a reference (index 7).

; Pattern 53
	db 188	; State byte.
	db 5	; New transposition on channel 1.
	db 132	; New track (0) for channel 1, as a reference (index 4).
	db 2	; New transposition on channel 2.
	db 138	; New track (62) for channel 2, as a reference (index 10).
	db 136	; New track (86) for channel 3, as a reference (index 8).

; Pattern 54
	db 252	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track42 - ($ + 2)) & #ff00) / 256	; New track (42) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track42 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 142	; New track (57) for channel 2, as a reference (index 14).
	db 29	; New transposition on channel 3.
	db 140	; New track (76) for channel 3, as a reference (index 12).

; Pattern 55
	db 232	; State byte.
	db ((mySong_Subsong0_Track43 - ($ + 2)) & #ff00) / 256	; New track (43) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track43 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track69 - ($ + 2)) & #ff00) / 256	; New track (69) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track69 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db 135	; New track (87) for channel 3, as a reference (index 7).

; Pattern 56
	db 168	; State byte.
	db ((mySong_Subsong0_Track44 - ($ + 2)) & #ff00) / 256	; New track (44) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track44 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track70 - ($ + 2)) & #ff00) / 256	; New track (70) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track70 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track98 - ($ + 2)) & #ff00) / 256	; New track (98) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track98 - ($ + 1)) & 255)

; Pattern 57
	db 184	; State byte.
	db ((mySong_Subsong0_Track45 - ($ + 2)) & #ff00) / 256	; New track (45) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track45 - ($ + 1)) & 255)
	db -7	; New transposition on channel 2.
	db ((mySong_Subsong0_Track68 - ($ + 2)) & #ff00) / 256	; New track (68) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track68 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track99 - ($ + 2)) & #ff00) / 256	; New track (99) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track99 - ($ + 1)) & 255)

; Pattern 58
	db 248	; State byte.
	db ((mySong_Subsong0_Track46 - ($ + 2)) & #ff00) / 256	; New track (46) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track46 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 133	; New track (56) for channel 2, as a reference (index 5).
	db 24	; New transposition on channel 3.
	db 140	; New track (76) for channel 3, as a reference (index 12).

; Pattern 59
	db 232	; State byte.
	db ((mySong_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track3 - ($ + 1)) & 255)
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db -24	; New transposition on channel 3.
	db 130	; New track (78) for channel 3, as a reference (index 2).

; Pattern 60
	db 24	; State byte.
	db 141	; New track (4) for channel 1, as a reference (index 13).
	db -1	; New transposition on channel 2.

; Pattern 61
	db 216	; State byte.
	db ((mySong_Subsong0_Track47 - ($ + 2)) & #ff00) / 256	; New track (47) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track47 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track100 - ($ + 2)) & #ff00) / 256	; New track (100) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track100 - ($ + 1)) & 255)

; Pattern 62
	db 216	; State byte.
	db ((mySong_Subsong0_Track48 - ($ + 2)) & #ff00) / 256	; New track (48) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track48 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.
	db -24	; New transposition on channel 3.
	db 130	; New track (78) for channel 3, as a reference (index 2).

; Pattern 63
	db 24	; State byte.
	db ((mySong_Subsong0_Track49 - ($ + 2)) & #ff00) / 256	; New track (49) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track49 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.

; Pattern 64
	db 24	; State byte.
	db ((mySong_Subsong0_Track48 - ($ + 2)) & #ff00) / 256	; New track (48) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track48 - ($ + 1)) & 255)
	db -5	; New transposition on channel 2.

; Pattern 65
	db 248	; State byte.
	db ((mySong_Subsong0_Track50 - ($ + 2)) & #ff00) / 256	; New track (50) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track50 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track71 - ($ + 2)) & #ff00) / 256	; New track (71) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track71 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track101 - ($ + 2)) & #ff00) / 256	; New track (101) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track101 - ($ + 1)) & 255)

; Pattern 66
	db 168	; State byte.
	db ((mySong_Subsong0_Track51 - ($ + 2)) & #ff00) / 256	; New track (51) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track51 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track72 - ($ + 2)) & #ff00) / 256	; New track (72) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track72 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track102 - ($ + 2)) & #ff00) / 256	; New track (102) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track102 - ($ + 1)) & 255)

; Pattern 67
	db 168	; State byte.
	db ((mySong_Subsong0_Track52 - ($ + 2)) & #ff00) / 256	; New track (52) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track52 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track73 - ($ + 2)) & #ff00) / 256	; New track (73) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track73 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track103 - ($ + 2)) & #ff00) / 256	; New track (103) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track103 - ($ + 1)) & 255)

; Pattern 68
	db 232	; State byte.
	db ((mySong_Subsong0_Track53 - ($ + 2)) & #ff00) / 256	; New track (53) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track53 - ($ + 1)) & 255)
	db 128	; New track (54) for channel 2, as a reference (index 0).
	db -5	; New transposition on channel 3.
	db 134	; New track (74) for channel 3, as a reference (index 6).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes
	dw mySong_Subsong0_Track54	; Track 54, index 0.
	dw mySong_Subsong0_Track58	; Track 58, index 1.
	dw mySong_Subsong0_Track78	; Track 78, index 2.
	dw mySong_Subsong0_Track94	; Track 94, index 3.
	dw mySong_Subsong0_Track0	; Track 0, index 4.
	dw mySong_Subsong0_Track56	; Track 56, index 5.
	dw mySong_Subsong0_Track74	; Track 74, index 6.
	dw mySong_Subsong0_Track87	; Track 87, index 7.
	dw mySong_Subsong0_Track86	; Track 86, index 8.
	dw mySong_Subsong0_Track79	; Track 79, index 9.
	dw mySong_Subsong0_Track62	; Track 62, index 10.
	dw mySong_Subsong0_Track63	; Track 63, index 11.
	dw mySong_Subsong0_Track76	; Track 76, index 12.
	dw mySong_Subsong0_Track4	; Track 4, index 13.
	dw mySong_Subsong0_Track57	; Track 57, index 14.

mySong_Subsong0_Track0
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 51. Primary wait (6).
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track2
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 214	; Primary instrument (1). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track3
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track4
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track5
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track6
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 214	; Primary instrument (1). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track7
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track8
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 44. Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 44. Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 44. Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track9
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 54. Primary wait (6).
	db 54	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 54. Primary wait (6).
	db 54	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 54. Primary wait (6).
	db 54	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 222	; Primary instrument (1). New escaped note: 54. New wait (127).
	db 54	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track10
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 44. Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 44. Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track11
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 51. Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track12
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 51. Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 47. Primary wait (6).
	db 47	;   Escape note value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 47. Primary wait (6).
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track13
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 51. Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track14
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track15
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 54. Primary wait (6).
	db 54	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 54. New wait (127).
	db 54	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track16
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 211	; Primary instrument (1). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track17
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 44. Primary wait (6).
	db 44	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 222	; Primary instrument (1). New escaped note: 38. New wait (127).
	db 38	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track18
	db 94	; Primary instrument (1). New escaped note: 38. Primary wait (6).
	db 38	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 38. Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 38. Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 38. Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 42. Primary wait (6).
	db 42	;   Escape note value.
	db 212	; Primary instrument (1). Note reference (4). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track19
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 217	; Primary instrument (1). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track20
	db 94	; Primary instrument (1). New escaped note: 34. Primary wait (6).
	db 34	;   Escape note value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 60. Primary wait (6).
	db 60	;   Escape note value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 60. Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 60. Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 223	; Primary instrument (1). Same escaped note: 60. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track21
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 217	; Primary instrument (1). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track22
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track23
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 222	; Primary instrument (1). New escaped note: 59. New wait (127).
	db 59	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track24
	db 94	; Primary instrument (1). New escaped note: 61. Primary wait (6).
	db 61	;   Escape note value.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 214	; Primary instrument (1). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track25
	db 64	; Note reference (0). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 214	; Primary instrument (1). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track26
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (6).
	db 65	;   Escape note value.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track27
	db 64	; Note reference (0). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 212	; Primary instrument (1). Note reference (4). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track28
	db 94	; Primary instrument (1). New escaped note: 40. Primary wait (6).
	db 40	;   Escape note value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 222	; Primary instrument (1). New escaped note: 61. New wait (127).
	db 61	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track29
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (6).
	db 65	;   Escape note value.
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track30
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 61. Primary wait (6).
	db 61	;   Escape note value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 64. Primary wait (6).
	db 64	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 61. Primary wait (6).
	db 61	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 67. Primary wait (6).
	db 67	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 64. Primary wait (6).
	db 64	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 70. Primary wait (6).
	db 70	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 67. Primary wait (6).
	db 67	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 73. Primary wait (6).
	db 73	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 70. Primary wait (6).
	db 70	;   Escape note value.
	db 222	; Primary instrument (1). New escaped note: 77. New wait (127).
	db 77	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track31
	db 94	; Primary instrument (1). New escaped note: 73. Primary wait (6).
	db 73	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 67. Primary wait (6).
	db 67	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 70. Primary wait (6).
	db 70	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 64. Primary wait (6).
	db 64	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 67. Primary wait (6).
	db 67	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 61. Primary wait (6).
	db 61	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 64. Primary wait (6).
	db 64	;   Escape note value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 61. Primary wait (6).
	db 61	;   Escape note value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 214	; Primary instrument (1). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track32
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 40. Primary wait (6).
	db 40	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 38. Primary wait (6).
	db 38	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 215	; Primary instrument (1). Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track33
	db 94	; Primary instrument (1). New escaped note: 37. Primary wait (6).
	db 37	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 40. Primary wait (6).
	db 40	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 38. Primary wait (6).
	db 38	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 215	; Primary instrument (1). Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track34
	db 94	; Primary instrument (1). New escaped note: 37. Primary wait (6).
	db 37	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 39. Primary wait (6).
	db 39	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 38. Primary wait (6).
	db 38	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 215	; Primary instrument (1). Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track35
	db 94	; Primary instrument (1). New escaped note: 37. Primary wait (6).
	db 37	;   Escape note value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 38. Primary wait (6).
	db 38	;   Escape note value.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 38. Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track36
	db 94	; Primary instrument (1). New escaped note: 40. Primary wait (6).
	db 40	;   Escape note value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 40. Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 40. Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 40. Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 218	; Primary instrument (1). Note reference (10). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track37
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track38
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track39
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track40
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 220	; Primary instrument (1). Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track41
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (6).
	db 51	;   Escape note value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 51. Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track42
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 54. Primary wait (6).
	db 54	;   Escape note value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 54. Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 217	; Primary instrument (1). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track43
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 213	; Primary instrument (1). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track44
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track45
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 212	; Primary instrument (1). Note reference (4). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track46
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 88	; Primary instrument (1). Note reference (8). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 214	; Primary instrument (1). Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track47
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (6).
	db 65	;   Escape note value.
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 69. Primary wait (6).
	db 69	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (6).
	db 65	;   Escape note value.
	db 220	; Primary instrument (1). Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track48
	db 94	; Primary instrument (1). New escaped note: 61. Primary wait (6).
	db 61	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 64. Primary wait (6).
	db 64	;   Escape note value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 61. Primary wait (6).
	db 61	;   Escape note value.
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 89	; Primary instrument (1). Note reference (9). Primary wait (6).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (6).
	db 83	; Primary instrument (1). Note reference (3). Primary wait (6).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (6).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 216	; Primary instrument (1). Note reference (8). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track49
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (6).
	db 65	;   Escape note value.
	db 92	; Primary instrument (1). Note reference (12). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 69. Primary wait (6).
	db 69	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 65. Primary wait (6).
	db 65	;   Escape note value.
	db 220	; Primary instrument (1). Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track50
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 64	; Note reference (0). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 219	; Primary instrument (1). Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track51
	db 64	; Note reference (0). Primary wait (6).
	db 94	; Primary instrument (1). New escaped note: 38. Primary wait (6).
	db 38	;   Escape note value.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (6).
	db 91	; Primary instrument (1). Note reference (11). Primary wait (6).
	db 95	; Primary instrument (1). Same escaped note: 38. Primary wait (6).
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track52
	db 192	; Note reference (0). New wait (41).
	db 41	;   Escape wait value.
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track53
	db 209	; Primary instrument (1). Note reference (1). New wait (41).
	db 41	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track54
	db 239	; Secondary instrument (2). Same escaped note: 26. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track55
	db 238	; Secondary instrument (2). New escaped note: 22. New wait (41).
	db 22	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 19. New wait (127).
	db 19	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track56
	db 238	; Secondary instrument (2). New escaped note: 21. New wait (40).
	db 21	;   Escape note value.
	db 40	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 239	; Secondary instrument (2). Same escaped note: 21. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track57
	db 239	; Secondary instrument (2). Same escaped note: 26. New wait (41).
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 19. New wait (127).
	db 19	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track58
	db 238	; Secondary instrument (2). New escaped note: 29. New wait (82).
	db 29	;   Escape note value.
	db 82	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track59
	db 238	; Secondary instrument (2). New escaped note: 25. New wait (20).
	db 25	;   Escape note value.
	db 20	;   Escape wait value.
	db 46	; Secondary instrument (2). New escaped note: 24. 
	db 24	;   Escape note value.
	db 238	; Secondary instrument (2). New escaped note: 23. New wait (127).
	db 23	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track60
	db 238	; Secondary instrument (2). New escaped note: 24. New wait (41).
	db 24	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 29. New wait (20).
	db 29	;   Escape note value.
	db 20	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 32. New wait (127).
	db 32	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track61
	db 238	; Secondary instrument (2). New escaped note: 31. New wait (41).
	db 31	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 19. New wait (127).
	db 19	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track62
	db 205	; New wait (20).
	db 20	;   Escape wait value.
	db 46	; Secondary instrument (2). New escaped note: 29. 
	db 29	;   Escape note value.
	db 46	; Secondary instrument (2). New escaped note: 32. 
	db 32	;   Escape note value.
	db 238	; Secondary instrument (2). New escaped note: 29. New wait (127).
	db 29	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track63
	db 238	; Secondary instrument (2). New escaped note: 18. New wait (41).
	db 18	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 19. New wait (127).
	db 19	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track64
	db 238	; Secondary instrument (2). New escaped note: 31. New wait (41).
	db 31	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 28. New wait (20).
	db 28	;   Escape note value.
	db 20	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 26. New wait (127).
	db 26	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track65
	db 238	; Secondary instrument (2). New escaped note: 25. New wait (61).
	db 25	;   Escape note value.
	db 61	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 239	; Secondary instrument (2). Same escaped note: 25. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track66
	db 239	; Secondary instrument (2). Same escaped note: 26. New wait (41).
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 19. New wait (20).
	db 19	;   Escape note value.
	db 20	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 20. New wait (127).
	db 20	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track67
	db 238	; Secondary instrument (2). New escaped note: 19. New wait (41).
	db 19	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 21. New wait (127).
	db 21	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track68
	db 238	; Secondary instrument (2). New escaped note: 29. New wait (41).
	db 29	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 28. New wait (20).
	db 28	;   Escape note value.
	db 20	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 26. New wait (127).
	db 26	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track69
	db 238	; Secondary instrument (2). New escaped note: 28. New wait (62).
	db 28	;   Escape note value.
	db 62	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 29. New wait (127).
	db 29	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track70
	db 239	; Secondary instrument (2). Same escaped note: 26. New wait (20).
	db 20	;   Escape wait value.
	db 46	; Secondary instrument (2). New escaped note: 28. 
	db 28	;   Escape note value.
	db 46	; Secondary instrument (2). New escaped note: 25. 
	db 25	;   Escape note value.
	db 238	; Secondary instrument (2). New escaped note: 26. New wait (127).
	db 26	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track71
	db 239	; Secondary instrument (2). Same escaped note: 26. New wait (62).
	db 62	;   Escape wait value.
	db 239	; Secondary instrument (2). Same escaped note: 26. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track72
	db 205	; New wait (41).
	db 41	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track73
	db 239	; Secondary instrument (2). Same escaped note: 26. New wait (40).
	db 40	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 47	; Secondary instrument (2). Same escaped note: 26. 
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track74
	db 238	; Secondary instrument (2). New escaped note: 38. New wait (127).
	db 38	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track75
	db 238	; Secondary instrument (2). New escaped note: 34. New wait (41).
	db 34	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 31. New wait (127).
	db 31	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track76
	db 238	; Secondary instrument (2). New escaped note: 33. New wait (40).
	db 33	;   Escape note value.
	db 40	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 239	; Secondary instrument (2). Same escaped note: 33. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track77
	db 238	; Secondary instrument (2). New escaped note: 38. New wait (62).
	db 38	;   Escape note value.
	db 62	;   Escape wait value.
	db 229	; Secondary instrument (2). Note reference (5). New wait (12).
	db 12	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 229	; Secondary instrument (2). Note reference (5). New wait (5).
	db 5	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track78
	db 229	; Secondary instrument (2). Note reference (5). New wait (61).
	db 61	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 229	; Secondary instrument (2). Note reference (5). New wait (12).
	db 12	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 229	; Secondary instrument (2). Note reference (5). New wait (5).
	db 5	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track79
	db 229	; Secondary instrument (2). Note reference (5). New wait (41).
	db 41	;   Escape wait value.
	db 233	; Secondary instrument (2). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track80
	db 229	; Secondary instrument (2). Note reference (5). New wait (41).
	db 41	;   Escape wait value.
	db 227	; Secondary instrument (2). Note reference (3). New wait (20).
	db 20	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 60. New wait (127).
	db 60	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track81
	db 226	; Secondary instrument (2). Note reference (2). New wait (20).
	db 20	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track82
	db 192	; Note reference (0). New wait (62).
	db 62	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 56. New wait (12).
	db 56	;   Escape note value.
	db 12	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 239	; Secondary instrument (2). Same escaped note: 56. New wait (5).
	db 5	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track83
	db 238	; Secondary instrument (2). New escaped note: 56. New wait (62).
	db 56	;   Escape note value.
	db 62	;   Escape wait value.
	db 227	; Secondary instrument (2). Note reference (3). New wait (19).
	db 19	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track84
	db 227	; Secondary instrument (2). Note reference (3). New wait (41).
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 56. New wait (20).
	db 56	;   Escape note value.
	db 20	;   Escape wait value.
	db 226	; Secondary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track85
	db 192	; Note reference (0). New wait (62).
	db 62	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 60. New wait (127).
	db 60	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track86
	db 238	; Secondary instrument (2). New escaped note: 61. New wait (62).
	db 61	;   Escape note value.
	db 62	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 59. New wait (127).
	db 59	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track87
	db 238	; Secondary instrument (2). New escaped note: 60. New wait (61).
	db 60	;   Escape note value.
	db 61	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 239	; Secondary instrument (2). Same escaped note: 60. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track88
	db 238	; Secondary instrument (2). New escaped note: 60. New wait (40).
	db 60	;   Escape note value.
	db 40	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 47	; Secondary instrument (2). Same escaped note: 60. 
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track89
	db 238	; Secondary instrument (2). New escaped note: 60. New wait (41).
	db 60	;   Escape note value.
	db 41	;   Escape wait value.
	db 233	; Secondary instrument (2). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track90
	db 238	; Secondary instrument (2). New escaped note: 56. New wait (41).
	db 56	;   Escape note value.
	db 41	;   Escape wait value.
	db 227	; Secondary instrument (2). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track91
	db 225	; Secondary instrument (2). Note reference (1). New wait (40).
	db 40	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 225	; Secondary instrument (2). Note reference (1). New wait (19).
	db 19	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 225	; Secondary instrument (2). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track92
	db 236	; Secondary instrument (2). Note reference (12). New wait (41).
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 61. New wait (20).
	db 61	;   Escape note value.
	db 20	;   Escape wait value.
	db 236	; Secondary instrument (2). Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track93
	db 238	; Secondary instrument (2). New escaped note: 65. New wait (41).
	db 65	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 64. New wait (20).
	db 64	;   Escape note value.
	db 20	;   Escape wait value.
	db 236	; Secondary instrument (2). Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track94
	db 238	; Secondary instrument (2). New escaped note: 33. New wait (82).
	db 33	;   Escape note value.
	db 82	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track95
	db 238	; Secondary instrument (2). New escaped note: 31. New wait (41).
	db 31	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 33. New wait (127).
	db 33	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track96
	db 226	; Secondary instrument (2). Note reference (2). New wait (20).
	db 20	;   Escape wait value.
	db 192	; Note reference (0). New wait (41).
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 60. New wait (12).
	db 60	;   Escape note value.
	db 12	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 239	; Secondary instrument (2). Same escaped note: 60. New wait (5).
	db 5	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track97
	db 238	; Secondary instrument (2). New escaped note: 60. New wait (41).
	db 60	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 61. New wait (20).
	db 61	;   Escape note value.
	db 20	;   Escape wait value.
	db 236	; Secondary instrument (2). Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track98
	db 233	; Secondary instrument (2). Note reference (9). New wait (19).
	db 19	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 233	; Secondary instrument (2). Note reference (9). New wait (20).
	db 20	;   Escape wait value.
	db 229	; Secondary instrument (2). Note reference (5). New wait (19).
	db 19	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 229	; Secondary instrument (2). Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track99
	db 227	; Secondary instrument (2). Note reference (3). New wait (41).
	db 41	;   Escape wait value.
	db 229	; Secondary instrument (2). Note reference (5). New wait (20).
	db 20	;   Escape wait value.
	db 233	; Secondary instrument (2). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track100
	db 238	; Secondary instrument (2). New escaped note: 33. New wait (61).
	db 33	;   Escape note value.
	db 61	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 239	; Secondary instrument (2). Same escaped note: 33. New wait (12).
	db 12	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 238	; Secondary instrument (2). New escaped note: 30. New wait (5).
	db 30	;   Escape note value.
	db 5	;   Escape wait value.
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track101
	db 238	; Secondary instrument (2). New escaped note: 33. New wait (41).
	db 33	;   Escape note value.
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 38. New wait (127).
	db 38	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track102
	db 238	; Secondary instrument (2). New escaped note: 33. New wait (40).
	db 33	;   Escape note value.
	db 40	;   Escape wait value.
	db 128	; Note reference (0). Secondary wait (0).
	db 111	; Secondary instrument (2). Same escaped note: 33. Primary wait (6).
	db 110	; Secondary instrument (2). New escaped note: 38. Primary wait (6).
	db 38	;   Escape note value.
	db 110	; Secondary instrument (2). New escaped note: 33. Primary wait (6).
	db 33	;   Escape note value.
	db 110	; Secondary instrument (2). New escaped note: 29. Primary wait (6).
	db 29	;   Escape note value.
	db 110	; Secondary instrument (2). New escaped note: 33. Primary wait (6).
	db 33	;   Escape note value.
	db 238	; Secondary instrument (2). New escaped note: 29. New wait (127).
	db 29	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track103
	db 192	; Note reference (0). New wait (41).
	db 41	;   Escape wait value.
	db 238	; Secondary instrument (2). New escaped note: 33. New wait (127).
	db 33	;   Escape note value.
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 48	; Note for index 0.
	db 50	; Note for index 1.
	db 53	; Note for index 2.
	db 55	; Note for index 3.
	db 45	; Note for index 4.
	db 57	; Note for index 5.
	db 52	; Note for index 6.
	db 46	; Note for index 7.
	db 43	; Note for index 8.
	db 58	; Note for index 9.
	db 49	; Note for index 10.
	db 41	; Note for index 11.
	db 62	; Note for index 12.

