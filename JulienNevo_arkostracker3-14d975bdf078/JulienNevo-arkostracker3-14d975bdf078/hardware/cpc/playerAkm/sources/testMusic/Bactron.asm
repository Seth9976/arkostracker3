; "Bactron" 1986 Loriciels, Song part, encoded in the AKM (minimalist) format V0.



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

	db 53	; Volume: 13.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 41	; Volume: 10.

	db 41	; Volume: 10.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 29	; Volume: 7.

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

mySong_Instrument2
	db 0	; Speed.

mySong_Instrument2Loop	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 4	; End the instrument.
	dw mySong_Instrument2Loop	; Loops.

mySong_Instrument3
	db 0	; Speed.

mySong_Instrument3Loop	db 61	; Volume: 15.

	db 4	; End the instrument.
	dw mySong_Instrument3Loop	; Loops.

mySong_Instrument4
	db 0	; Speed.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 185	; Volume: 14.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 185	; Volume: 14.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 177	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 177	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 173	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 173	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 169	; Volume: 10.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 165	; Volume: 9.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 165	; Volume: 9.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 161	; Volume: 8.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 161	; Volume: 8.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 157	; Volume: 7.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 153	; Volume: 6.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 153	; Volume: 6.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 149	; Volume: 5.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 149	; Volume: 5.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 145	; Volume: 4.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 141	; Volume: 3.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 141	; Volume: 3.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 137	; Volume: 2.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 137	; Volume: 2.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 133	; Volume: 1.
	db 1	; Arpeggio: 0.
	db 28	; Noise: 28.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument5
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

	db 161	; Volume: 8.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 157	; Volume: 7.
	db 1	; Arpeggio: 0.
	db 4	; Noise: 4.

	db 153	; Volume: 6.
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

; "Bactron" 1986 Loriciels, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 5	; Initial speed.

	db 1	; Most used instrument.
	db 5	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 49	; Default start note in tracks.
	db 4	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
	db 254	; State byte.
	db 23	; New height.
	db 0	; New transposition on channel 1.
	db 129	; New track (0) for channel 1, as a reference (index 1).
	db 0	; New transposition on channel 2.
	db 128	; New track (12) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 129	; New track (0) for channel 3, as a reference (index 1).

; Pattern 1
	db 0	; State byte.

; Pattern 2
	db 0	; State byte.

; Pattern 3
	db 0	; State byte.

; Pattern 4
mySong_Subsong0_Loop
	db 136	; State byte.
	db 130	; New track (1) for channel 1, as a reference (index 2).
	db 131	; New track (19) for channel 3, as a reference (index 3).

; Pattern 5
	db 0	; State byte.

; Pattern 6
	db 84	; State byte.
	db 5	; New transposition on channel 1.
	db 5	; New transposition on channel 2.
	db 5	; New transposition on channel 3.

; Pattern 7
	db 84	; State byte.
	db 0	; New transposition on channel 1.
	db 0	; New transposition on channel 2.
	db 0	; New transposition on channel 3.

; Pattern 8
	db 168	; State byte.
	db ((mySong_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track2 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track13 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track20 - ($ + 2)) & #ff00) / 256	; New track (20) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track20 - ($ + 1)) & 255)

; Pattern 9
	db 168	; State byte.
	db ((mySong_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track3 - ($ + 1)) & 255)
	db 132	; New track (14) for channel 2, as a reference (index 4).
	db ((mySong_Subsong0_Track21 - ($ + 2)) & #ff00) / 256	; New track (21) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track21 - ($ + 1)) & 255)

; Pattern 10
	db 168	; State byte.
	db ((mySong_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track4 - ($ + 1)) & 255)
	db 128	; New track (12) for channel 2, as a reference (index 0).
	db ((mySong_Subsong0_Track22 - ($ + 2)) & #ff00) / 256	; New track (22) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track22 - ($ + 1)) & 255)

; Pattern 11
	db 168	; State byte.
	db ((mySong_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track5 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track15 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track23 - ($ + 1)) & 255)

; Pattern 12
	db 252	; State byte.
	db 5	; New transposition on channel 1.
	db ((mySong_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track4 - ($ + 1)) & 255)
	db 5	; New transposition on channel 2.
	db 128	; New track (12) for channel 2, as a reference (index 0).
	db 5	; New transposition on channel 3.
	db ((mySong_Subsong0_Track22 - ($ + 2)) & #ff00) / 256	; New track (22) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track22 - ($ + 1)) & 255)

; Pattern 13
	db 252	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track6 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track16 - ($ + 1)) & 255)
	db 0	; New transposition on channel 3.
	db ((mySong_Subsong0_Track24 - ($ + 2)) & #ff00) / 256	; New track (24) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track24 - ($ + 1)) & 255)

; Pattern 14
	db 168	; State byte.
	db ((mySong_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track7 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track13 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track25 - ($ + 2)) & #ff00) / 256	; New track (25) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track25 - ($ + 1)) & 255)

; Pattern 15
	db 168	; State byte.
	db ((mySong_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track8 - ($ + 1)) & 255)
	db 132	; New track (14) for channel 2, as a reference (index 4).
	db ((mySong_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track26 - ($ + 1)) & 255)

; Pattern 16
	db 168	; State byte.
	db ((mySong_Subsong0_Track27 - ($ + 2)) & #ff00) / 256	; New track (27) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track27 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track17 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track9 - ($ + 1)) & 255)

; Pattern 17
	db 168	; State byte.
	db 130	; New track (1) for channel 1, as a reference (index 2).
	db 128	; New track (12) for channel 2, as a reference (index 0).
	db 131	; New track (19) for channel 3, as a reference (index 3).

; Pattern 18
	db 236	; State byte.
	db -7	; New transposition on channel 1.
	db ((mySong_Subsong0_Track27 - ($ + 2)) & #ff00) / 256	; New track (27) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track27 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track17 - ($ + 1)) & 255)
	db -7	; New transposition on channel 3.
	db ((mySong_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track9 - ($ + 1)) & 255)

; Pattern 19
	db 236	; State byte.
	db 0	; New transposition on channel 1.
	db 130	; New track (1) for channel 1, as a reference (index 2).
	db 128	; New track (12) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 131	; New track (19) for channel 3, as a reference (index 3).

; Pattern 20
	db 168	; State byte.
	db ((mySong_Subsong0_Track28 - ($ + 2)) & #ff00) / 256	; New track (28) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track28 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track18 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track10 - ($ + 1)) & 255)

; Pattern 21
	db 168	; State byte.
	db ((mySong_Subsong0_Track29 - ($ + 2)) & #ff00) / 256	; New track (29) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track29 - ($ + 1)) & 255)
	db 132	; New track (14) for channel 2, as a reference (index 4).
	db ((mySong_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track11 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes
	dw mySong_Subsong0_Track12	; Track 12, index 0.
	dw mySong_Subsong0_Track0	; Track 0, index 1.
	dw mySong_Subsong0_Track1	; Track 1, index 2.
	dw mySong_Subsong0_Track19	; Track 19, index 3.
	dw mySong_Subsong0_Track14	; Track 14, index 4.

mySong_Subsong0_Track0
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 224	; Secondary instrument (5). Note reference (0). New wait (17).
	db 17	;   Escape wait value.
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 214	; Primary instrument (1). Note reference (6). New wait (4).
	db 4	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 216	; Primary instrument (1). Note reference (8). New wait (2).
	db 2	;   Escape wait value.
	db 28	; Primary instrument (1). Note reference (12). 
	db 214	; Primary instrument (1). Note reference (6). New wait (4).
	db 4	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track2
	db 220	; Primary instrument (1). Note reference (12). New wait (4).
	db 4	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 43. Primary wait (0).
	db 43	;   Escape note value.
	db 158	; Primary instrument (1). New escaped note: 44. Secondary wait (1).
	db 44	;   Escape note value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 61. Secondary wait (1).
	db 61	;   Escape note value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 30	; Primary instrument (1). New escaped note: 38. 
	db 38	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 158	; Primary instrument (1). New escaped note: 42. Secondary wait (1).
	db 42	;   Escape note value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 149	; Primary instrument (1). Note reference (5). Secondary wait (1).
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track3
	db 214	; Primary instrument (1). Note reference (6). New wait (4).
	db 4	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track4
	db 210	; Primary instrument (1). Note reference (2). New wait (4).
	db 4	;   Escape wait value.
	db 210	; Primary instrument (1). Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 210	; Primary instrument (1). Note reference (2). New wait (4).
	db 4	;   Escape wait value.
	db 210	; Primary instrument (1). Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track5
	db 210	; Primary instrument (1). Note reference (2). New wait (4).
	db 4	;   Escape wait value.
	db 210	; Primary instrument (1). Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 150	; Primary instrument (1). Note reference (6). Secondary wait (1).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 35. Secondary wait (1).
	db 35	;   Escape note value.
	db 95	; Primary instrument (1). Same escaped note: 35. Primary wait (0).
	db 151	; Primary instrument (1). Note reference (7). Secondary wait (1).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (1).
	db 216	; Primary instrument (1). Note reference (8). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track6
	db 210	; Primary instrument (1). Note reference (2). New wait (4).
	db 4	;   Escape wait value.
	db 210	; Primary instrument (1). Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 156	; Primary instrument (1). Note reference (12). Secondary wait (1).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 42. Secondary wait (1).
	db 42	;   Escape note value.
	db 95	; Primary instrument (1). Same escaped note: 42. Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 43. Secondary wait (1).
	db 43	;   Escape note value.
	db 95	; Primary instrument (1). Same escaped note: 43. Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 44. Secondary wait (1).
	db 44	;   Escape note value.
	db 223	; Primary instrument (1). Same escaped note: 44. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track7
	db 213	; Primary instrument (1). Note reference (5). New wait (4).
	db 4	;   Escape wait value.
	db 213	; Primary instrument (1). Note reference (5). New wait (2).
	db 2	;   Escape wait value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 61. Secondary wait (1).
	db 61	;   Escape note value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 209	; Primary instrument (1). Note reference (1). New wait (4).
	db 4	;   Escape wait value.
	db 209	; Primary instrument (1). Note reference (1). New wait (2).
	db 2	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 149	; Primary instrument (1). Note reference (5). Secondary wait (1).
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track8
	db 210	; Primary instrument (1). Note reference (2). New wait (4).
	db 4	;   Escape wait value.
	db 210	; Primary instrument (1). Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 154	; Primary instrument (1). Note reference (10). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track9
	db 191	; New instrument (3). Same escaped note: 49. Secondary wait (1).
	db 3	;   Escape instrument value.
	db 66	; Note reference (2). Primary wait (0).
	db 129	; Note reference (1). Secondary wait (1).
	db 66	; Note reference (2). Primary wait (0).
	db 142	; New escaped note: 55. Secondary wait (1).
	db 55	;   Escape note value.
	db 65	; Note reference (1). Primary wait (0).
	db 138	; Note reference (10). Secondary wait (1).
	db 65	; Note reference (1). Primary wait (0).
	db 130	; Note reference (2). Secondary wait (1).
	db 65	; Note reference (1). Primary wait (0).
	db 142	; New escaped note: 50. Secondary wait (1).
	db 50	;   Escape note value.
	db 65	; Note reference (1). Primary wait (0).
	db 142	; New escaped note: 49. Secondary wait (1).
	db 49	;   Escape note value.
	db 142	; New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 251	; New instrument (0). Note reference (11). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track10
	db 181	; New instrument (3). Note reference (5). Secondary wait (1).
	db 3	;   Escape instrument value.
	db 68	; Note reference (4). Primary wait (0).
	db 129	; Note reference (1). Secondary wait (1).
	db 68	; Note reference (4). Primary wait (0).
	db 142	; New escaped note: 56. Secondary wait (1).
	db 56	;   Escape note value.
	db 130	; Note reference (2). Secondary wait (1).
	db 187	; New instrument (0). Note reference (11). Secondary wait (1).
	db 0	;   Escape instrument value.
	db 190	; New instrument (3). New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 3	;   Escape instrument value.
	db 78	; New escaped note: 50. Primary wait (0).
	db 50	;   Escape note value.
	db 142	; New escaped note: 43. Secondary wait (1).
	db 43	;   Escape note value.
	db 78	; New escaped note: 50. Primary wait (0).
	db 50	;   Escape note value.
	db 142	; New escaped note: 42. Secondary wait (1).
	db 42	;   Escape note value.
	db 142	; New escaped note: 38. Secondary wait (1).
	db 38	;   Escape note value.
	db 251	; New instrument (0). Note reference (11). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track11
	db 178	; New instrument (3). Note reference (2). Secondary wait (1).
	db 3	;   Escape instrument value.
	db 65	; Note reference (1). Primary wait (0).
	db 142	; New escaped note: 50. Secondary wait (1).
	db 50	;   Escape note value.
	db 65	; Note reference (1). Primary wait (0).
	db 142	; New escaped note: 49. Secondary wait (1).
	db 49	;   Escape note value.
	db 142	; New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 187	; New instrument (0). Note reference (11). Secondary wait (1).
	db 0	;   Escape instrument value.
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track12
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 3	; Note reference (3). 
	db 32	; Secondary instrument (5). Note reference (0). 
	db 3	; Note reference (3). 
	db 32	; Secondary instrument (5). Note reference (0). 
	db 131	; Note reference (3). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track13
	db 206	; New escaped note: 30. New wait (2).
	db 30	;   Escape note value.
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 143	; Same escaped note: 30. Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 14	; New escaped note: 28. 
	db 28	;   Escape note value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 143	; Same escaped note: 28. Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track14
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 131	; Note reference (3). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 251	; New instrument (0). Note reference (11). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track15
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 131	; Note reference (3). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 131	; Note reference (3). Secondary wait (1).
	db 67	; Note reference (3). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 142	; New escaped note: 91. Secondary wait (1).
	db 91	;   Escape note value.
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track16
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 131	; Note reference (3). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 142	; New escaped note: 30. Secondary wait (1).
	db 30	;   Escape note value.
	db 79	; Same escaped note: 30. Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 142	; New escaped note: 98. Secondary wait (1).
	db 98	;   Escape note value.
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (1).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track17
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 3	; Note reference (3). 
	db 32	; Secondary instrument (5). Note reference (0). 
	db 3	; Note reference (3). 
	db 32	; Secondary instrument (5). Note reference (0). 
	db 131	; Note reference (3). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track18
	db 195	; Note reference (3). New wait (2).
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (5). Note reference (0). 
	db 131	; Note reference (3). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 32	; Secondary instrument (5). Note reference (0). 
	db 3	; Note reference (3). 
	db 32	; Secondary instrument (5). Note reference (0). 
	db 131	; Note reference (3). Secondary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track19
	db 214	; Primary instrument (1). Note reference (6). New wait (4).
	db 4	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 216	; Primary instrument (1). Note reference (8). New wait (2).
	db 2	;   Escape wait value.
	db 28	; Primary instrument (1). Note reference (12). 
	db 214	; Primary instrument (1). Note reference (6). New wait (4).
	db 4	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (1).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track20
	db 220	; Primary instrument (1). Note reference (12). New wait (4).
	db 4	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 43. Primary wait (0).
	db 43	;   Escape note value.
	db 158	; Primary instrument (1). New escaped note: 44. Secondary wait (1).
	db 44	;   Escape note value.
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 148	; Primary instrument (1). Note reference (4). Secondary wait (1).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 30	; Primary instrument (1). New escaped note: 38. 
	db 38	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 158	; Primary instrument (1). New escaped note: 42. Secondary wait (1).
	db 42	;   Escape note value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (0).
	db 153	; Primary instrument (1). Note reference (9). Secondary wait (1).
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track21
	db 214	; Primary instrument (1). Note reference (6). New wait (4).
	db 4	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (1).
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track22
	db 209	; Primary instrument (1). Note reference (1). New wait (4).
	db 4	;   Escape wait value.
	db 209	; Primary instrument (1). Note reference (1). New wait (2).
	db 2	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 209	; Primary instrument (1). Note reference (1). New wait (4).
	db 4	;   Escape wait value.
	db 209	; Primary instrument (1). Note reference (1). New wait (2).
	db 2	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 210	; Primary instrument (1). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track23
	db 209	; Primary instrument (1). Note reference (1). New wait (4).
	db 4	;   Escape wait value.
	db 209	; Primary instrument (1). Note reference (1). New wait (2).
	db 2	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 150	; Primary instrument (1). Note reference (6). Secondary wait (1).
	db 86	; Primary instrument (1). Note reference (6). Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 35. Secondary wait (1).
	db 35	;   Escape note value.
	db 95	; Primary instrument (1). Same escaped note: 35. Primary wait (0).
	db 151	; Primary instrument (1). Note reference (7). Secondary wait (1).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (1).
	db 216	; Primary instrument (1). Note reference (8). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track24
	db 209	; Primary instrument (1). Note reference (1). New wait (4).
	db 4	;   Escape wait value.
	db 209	; Primary instrument (1). Note reference (1). New wait (2).
	db 2	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 156	; Primary instrument (1). Note reference (12). Secondary wait (1).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 42. Secondary wait (1).
	db 42	;   Escape note value.
	db 95	; Primary instrument (1). Same escaped note: 42. Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 43. Secondary wait (1).
	db 43	;   Escape note value.
	db 95	; Primary instrument (1). Same escaped note: 43. Primary wait (0).
	db 158	; Primary instrument (1). New escaped note: 44. Secondary wait (1).
	db 44	;   Escape note value.
	db 223	; Primary instrument (1). Same escaped note: 44. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track25
	db 212	; Primary instrument (1). Note reference (4). New wait (4).
	db 4	;   Escape wait value.
	db 212	; Primary instrument (1). Note reference (4). New wait (2).
	db 2	;   Escape wait value.
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 148	; Primary instrument (1). Note reference (4). Secondary wait (1).
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 217	; Primary instrument (1). Note reference (9). New wait (4).
	db 4	;   Escape wait value.
	db 217	; Primary instrument (1). Note reference (9). New wait (2).
	db 2	;   Escape wait value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (0).
	db 153	; Primary instrument (1). Note reference (9). Secondary wait (1).
	db 209	; Primary instrument (1). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track26
	db 209	; Primary instrument (1). Note reference (1). New wait (4).
	db 4	;   Escape wait value.
	db 209	; Primary instrument (1). Note reference (1). New wait (2).
	db 2	;   Escape wait value.
	db 81	; Primary instrument (1). Note reference (1). Primary wait (0).
	db 145	; Primary instrument (1). Note reference (1). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track27
	db 190	; New instrument (2). New escaped note: 61. Secondary wait (1).
	db 61	;   Escape note value.
	db 2	;   Escape instrument value.
	db 68	; Note reference (4). Primary wait (0).
	db 142	; New escaped note: 69. Secondary wait (1).
	db 69	;   Escape note value.
	db 68	; Note reference (4). Primary wait (0).
	db 142	; New escaped note: 67. Secondary wait (1).
	db 67	;   Escape note value.
	db 78	; New escaped note: 69. Primary wait (0).
	db 69	;   Escape note value.
	db 142	; New escaped note: 66. Secondary wait (1).
	db 66	;   Escape note value.
	db 78	; New escaped note: 69. Primary wait (0).
	db 69	;   Escape note value.
	db 132	; Note reference (4). Secondary wait (1).
	db 79	; Same escaped note: 69. Primary wait (0).
	db 137	; Note reference (9). Secondary wait (1).
	db 79	; Same escaped note: 69. Primary wait (0).
	db 142	; New escaped note: 61. Secondary wait (1).
	db 61	;   Escape note value.
	db 129	; Note reference (1). Secondary wait (1).
	db 251	; New instrument (0). Note reference (11). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track28
	db 190	; New instrument (2). New escaped note: 71. Secondary wait (1).
	db 71	;   Escape note value.
	db 2	;   Escape instrument value.
	db 78	; New escaped note: 76. Primary wait (0).
	db 76	;   Escape note value.
	db 142	; New escaped note: 69. Secondary wait (1).
	db 69	;   Escape note value.
	db 78	; New escaped note: 76. Primary wait (0).
	db 76	;   Escape note value.
	db 142	; New escaped note: 68. Secondary wait (1).
	db 68	;   Escape note value.
	db 132	; Note reference (4). Secondary wait (1).
	db 187	; New instrument (0). Note reference (11). Secondary wait (1).
	db 0	;   Escape instrument value.
	db 177	; New instrument (2). Note reference (1). Secondary wait (1).
	db 2	;   Escape instrument value.
	db 73	; Note reference (9). Primary wait (0).
	db 142	; New escaped note: 55. Secondary wait (1).
	db 55	;   Escape note value.
	db 73	; Note reference (9). Primary wait (0).
	db 138	; Note reference (10). Secondary wait (1).
	db 142	; New escaped note: 50. Secondary wait (1).
	db 50	;   Escape note value.
	db 251	; New instrument (0). Note reference (11). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track29
	db 180	; New instrument (2). Note reference (4). Secondary wait (1).
	db 2	;   Escape instrument value.
	db 78	; New escaped note: 69. Primary wait (0).
	db 69	;   Escape note value.
	db 137	; Note reference (9). Secondary wait (1).
	db 79	; Same escaped note: 69. Primary wait (0).
	db 142	; New escaped note: 61. Secondary wait (1).
	db 61	;   Escape note value.
	db 129	; Note reference (1). Secondary wait (1).
	db 187	; New instrument (0). Note reference (11). Secondary wait (1).
	db 0	;   Escape instrument value.
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (0).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 0	; Note for index 0.
	db 57	; Note for index 1.
	db 52	; Note for index 2.
	db 23	; Note for index 3.
	db 64	; Note for index 4.
	db 59	; Note for index 5.
	db 33	; Note for index 6.
	db 36	; Note for index 7.
	db 37	; Note for index 8.
	db 62	; Note for index 9.
	db 54	; Note for index 10.
	db 48	; Note for index 11.
	db 40	; Note for index 12.

