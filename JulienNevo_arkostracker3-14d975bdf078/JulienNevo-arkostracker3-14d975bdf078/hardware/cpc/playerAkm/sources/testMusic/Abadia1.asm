; "La Abadia del Crimen" 1987 Opera Soft, Song part, encoded in the AKM (minimalist) format V0.



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

mySong_Instrument1Loop	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 4	; End the instrument.
	dw mySong_Instrument1Loop	; Loops.

mySong_Instrument2
	db 0	; Speed.

	db 61	; Volume: 15.

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

	db 29	; Volume: 7.

	db 25	; Volume: 6.

	db 21	; Volume: 5.

	db 17	; Volume: 4.

	db 17	; Volume: 4.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument3
	db 0	; Speed.

	db 61	; Volume: 15.

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

	db 13	; Volume: 3.

	db 13	; Volume: 3.

	db 9	; Volume: 2.

	db 5	; Volume: 1.

	db 5	; Volume: 1.

	db 4	; End the instrument.
	dw mySong_Instrument0Loop	; Loop to silence.

mySong_Instrument4
	db 0	; Speed.

mySong_Instrument4Loop	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 21	; Volume: 5.

	db 4	; End the instrument.
	dw mySong_Instrument4Loop	; Loops.

mySong_Instrument5
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

	db 33	; Volume: 8.

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

; "La Abadia del Crimen" 1987 Opera Soft, Subsong 0.
; ----------------------------------

mySong_Subsong0
	dw mySong_Subsong0_NoteIndexes	; Index table for the notes.
	dw mySong_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 4	; Initial speed.

	db 1	; Most used instrument.
	db 5	; Second most used instrument.

	db 1	; Most used wait.
	db 3	; Second most used wait.

	db 70	; Default start note in tracks.
	db 4	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 13	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
mySong_Subsong0_Loop
	db 254	; State byte.
	db 23	; New height.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track0 - ($ + 1)) & 255)
	db -19	; New transposition on channel 2.
	db 129	; New track (3) for channel 2, as a reference (index 1).
	db 0	; New transposition on channel 3.
	db 128	; New track (44) for channel 3, as a reference (index 0).

; Pattern 1
	db 24	; State byte.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)
	db -21	; New transposition on channel 2.

; Pattern 2
	db 24	; State byte.
	db ((mySong_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track2 - ($ + 1)) & 255)
	db -20	; New transposition on channel 2.

; Pattern 3
	db 56	; State byte.
	db 129	; New track (3) for channel 1, as a reference (index 1).
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track23 - ($ + 1)) & 255)

; Pattern 4
	db 168	; State byte.
	db ((mySong_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track4 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track24 - ($ + 2)) & #ff00) / 256	; New track (24) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track24 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track45 - ($ + 2)) & #ff00) / 256	; New track (45) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track45 - ($ + 1)) & 255)

; Pattern 5
	db 168	; State byte.
	db ((mySong_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track5 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track25 - ($ + 2)) & #ff00) / 256	; New track (25) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track25 - ($ + 1)) & 255)
	db 128	; New track (44) for channel 3, as a reference (index 0).

; Pattern 6
	db 40	; State byte.
	db ((mySong_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track6 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track26 - ($ + 2)) & #ff00) / 256	; New track (26) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track26 - ($ + 1)) & 255)

; Pattern 7
	db 40	; State byte.
	db ((mySong_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track7 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track23 - ($ + 2)) & #ff00) / 256	; New track (23) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track23 - ($ + 1)) & 255)

; Pattern 8
	db 56	; State byte.
	db ((mySong_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track8 - ($ + 1)) & 255)
	db -19	; New transposition on channel 2.
	db 129	; New track (3) for channel 2, as a reference (index 1).

; Pattern 9
	db 24	; State byte.
	db ((mySong_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track1 - ($ + 1)) & 255)
	db -21	; New transposition on channel 2.

; Pattern 10
	db 24	; State byte.
	db ((mySong_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track2 - ($ + 1)) & 255)
	db -23	; New transposition on channel 2.

; Pattern 11
	db 56	; State byte.
	db 129	; New track (3) for channel 1, as a reference (index 1).
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track27 - ($ + 2)) & #ff00) / 256	; New track (27) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track27 - ($ + 1)) & 255)

; Pattern 12
	db 40	; State byte.
	db ((mySong_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track9 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track28 - ($ + 2)) & #ff00) / 256	; New track (28) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track28 - ($ + 1)) & 255)

; Pattern 13
	db 40	; State byte.
	db ((mySong_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track4 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track29 - ($ + 2)) & #ff00) / 256	; New track (29) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track29 - ($ + 1)) & 255)

; Pattern 14
	db 40	; State byte.
	db ((mySong_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track10 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track30 - ($ + 2)) & #ff00) / 256	; New track (30) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track30 - ($ + 1)) & 255)

; Pattern 15
	db 236	; State byte.
	db -12	; New transposition on channel 1.
	db 129	; New track (3) for channel 1, as a reference (index 1).
	db ((mySong_Subsong0_Track31 - ($ + 2)) & #ff00) / 256	; New track (31) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track31 - ($ + 1)) & 255)
	db -4	; New transposition on channel 3.
	db 129	; New track (3) for channel 3, as a reference (index 1).

; Pattern 16
	db 252	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track11 - ($ + 1)) & 255)
	db -4	; New transposition on channel 2.
	db 129	; New track (3) for channel 2, as a reference (index 1).
	db 0	; New transposition on channel 3.
	db 128	; New track (44) for channel 3, as a reference (index 0).

; Pattern 17
	db 56	; State byte.
	db ((mySong_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track12 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track32 - ($ + 2)) & #ff00) / 256	; New track (32) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track32 - ($ + 1)) & 255)

; Pattern 18
	db 56	; State byte.
	db ((mySong_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track13 - ($ + 1)) & 255)
	db 7	; New transposition on channel 2.
	db ((mySong_Subsong0_Track29 - ($ + 2)) & #ff00) / 256	; New track (29) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track29 - ($ + 1)) & 255)

; Pattern 19
	db 56	; State byte.
	db ((mySong_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track14 - ($ + 1)) & 255)
	db -9	; New transposition on channel 2.
	db 129	; New track (3) for channel 2, as a reference (index 1).

; Pattern 20
	db 56	; State byte.
	db ((mySong_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track15 - ($ + 1)) & 255)
	db 0	; New transposition on channel 2.
	db ((mySong_Subsong0_Track32 - ($ + 2)) & #ff00) / 256	; New track (32) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track32 - ($ + 1)) & 255)

; Pattern 21
	db 44	; State byte.
	db -7	; New transposition on channel 1.
	db ((mySong_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track8 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track33 - ($ + 2)) & #ff00) / 256	; New track (33) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track33 - ($ + 1)) & 255)

; Pattern 22
	db 44	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track16 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track34 - ($ + 2)) & #ff00) / 256	; New track (34) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track34 - ($ + 1)) & 255)

; Pattern 23
	db 44	; State byte.
	db -4	; New transposition on channel 1.
	db 129	; New track (3) for channel 1, as a reference (index 1).
	db ((mySong_Subsong0_Track35 - ($ + 2)) & #ff00) / 256	; New track (35) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track35 - ($ + 1)) & 255)

; Pattern 24
	db 172	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track17 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track36 - ($ + 2)) & #ff00) / 256	; New track (36) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track36 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track46 - ($ + 2)) & #ff00) / 256	; New track (46) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track46 - ($ + 1)) & 255)

; Pattern 25
	db 168	; State byte.
	db ((mySong_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track18 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track37 - ($ + 2)) & #ff00) / 256	; New track (37) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track37 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track47 - ($ + 2)) & #ff00) / 256	; New track (47) for channel 3, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track47 - ($ + 1)) & 255)

; Pattern 26
	db 168	; State byte.
	db ((mySong_Subsong0_Track19 - ($ + 2)) & #ff00) / 256	; New track (19) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track19 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track38 - ($ + 2)) & #ff00) / 256	; New track (38) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track38 - ($ + 1)) & 255)
	db 128	; New track (44) for channel 3, as a reference (index 0).

; Pattern 27
	db 44	; State byte.
	db -5	; New transposition on channel 1.
	db 129	; New track (3) for channel 1, as a reference (index 1).
	db ((mySong_Subsong0_Track39 - ($ + 2)) & #ff00) / 256	; New track (39) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track39 - ($ + 1)) & 255)

; Pattern 28
	db 44	; State byte.
	db 0	; New transposition on channel 1.
	db ((mySong_Subsong0_Track20 - ($ + 2)) & #ff00) / 256	; New track (20) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track20 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track40 - ($ + 2)) & #ff00) / 256	; New track (40) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track40 - ($ + 1)) & 255)

; Pattern 29
	db 40	; State byte.
	db ((mySong_Subsong0_Track21 - ($ + 2)) & #ff00) / 256	; New track (21) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track21 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track41 - ($ + 2)) & #ff00) / 256	; New track (41) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track41 - ($ + 1)) & 255)

; Pattern 30
	db 40	; State byte.
	db ((mySong_Subsong0_Track22 - ($ + 2)) & #ff00) / 256	; New track (22) for channel 1, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track22 - ($ + 1)) & 255)
	db ((mySong_Subsong0_Track42 - ($ + 2)) & #ff00) / 256	; New track (42) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track42 - ($ + 1)) & 255)

; Pattern 31
	db 236	; State byte.
	db -4	; New transposition on channel 1.
	db 129	; New track (3) for channel 1, as a reference (index 1).
	db ((mySong_Subsong0_Track43 - ($ + 2)) & #ff00) / 256	; New track (43) for channel 2, as an offset. Offset MSB, then LSB.
	db ((mySong_Subsong0_Track43 - ($ + 1)) & 255)
	db -7	; New transposition on channel 3.
	db 129	; New track (3) for channel 3, as a reference (index 1).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw mySong_Subsong0_Loop

; The indexes of the tracks.
mySong_Subsong0_TrackIndexes
	dw mySong_Subsong0_Track44	; Track 44, index 0.
	dw mySong_Subsong0_Track3	; Track 3, index 1.

mySong_Subsong0_Track0
	db 95	; Primary instrument (1). Same escaped note: 70. Primary wait (1).
	db 255	; New instrument (2). Same escaped note: 70. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 90	; Primary instrument (1). Note reference (10). Primary wait (1).
	db 10	; Note reference (10). 
	db 84	; Primary instrument (1). Note reference (4). Primary wait (1).
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track1
	db 90	; Primary instrument (1). Note reference (10). Primary wait (1).
	db 250	; New instrument (2). Note reference (10). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 0	; Note reference (0). 
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track2
	db 84	; Primary instrument (1). Note reference (4). Primary wait (1).
	db 244	; New instrument (2). Note reference (4). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 162	; Secondary instrument (5). Note reference (2). Secondary wait (3).
	db 166	; Secondary instrument (5). Note reference (6). Secondary wait (3).
	db 167	; Secondary instrument (5). Note reference (7). Secondary wait (3).
	db 225	; Secondary instrument (5). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track3
	db 144	; Primary instrument (1). Note reference (0). Secondary wait (3).
	db 240	; New instrument (3). Note reference (0). New wait (11).
	db 3	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 240	; New instrument (4). Note reference (0). New wait (127).
	db 4	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track4
	db 94	; Primary instrument (1). New escaped note: 63. Primary wait (1).
	db 63	;   Escape note value.
	db 255	; New instrument (2). Same escaped note: 63. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 172	; Secondary instrument (5). Note reference (12). Secondary wait (3).
	db 175	; Secondary instrument (5). Same escaped note: 63. Secondary wait (3).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (3).
	db 225	; Secondary instrument (5). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track5
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 240	; New instrument (2). Note reference (0). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 174	; Secondary instrument (5). New escaped note: 63. Secondary wait (3).
	db 63	;   Escape note value.
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (3).
	db 161	; Secondary instrument (5). Note reference (1). Secondary wait (3).
	db 238	; Secondary instrument (5). New escaped note: 59. New wait (127).
	db 59	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track6
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 241	; New instrument (2). Note reference (1). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (3).
	db 161	; Secondary instrument (5). Note reference (1). Secondary wait (3).
	db 167	; Secondary instrument (5). Note reference (7). Secondary wait (3).
	db 225	; Secondary instrument (5). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track7
	db 166	; Secondary instrument (5). Note reference (6). Secondary wait (3).
	db 167	; Secondary instrument (5). Note reference (7). Secondary wait (3).
	db 150	; Primary instrument (1). Note reference (6). Secondary wait (3).
	db 246	; New instrument (3). Note reference (6). New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track8
	db 95	; Primary instrument (1). Same escaped note: 70. Primary wait (1).
	db 255	; New instrument (2). Same escaped note: 70. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 106	; Secondary instrument (5). Note reference (10). Primary wait (1).
	db 111	; Secondary instrument (5). Same escaped note: 70. Primary wait (1).
	db 170	; Secondary instrument (5). Note reference (10). Secondary wait (3).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (1).
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track9
	db 108	; Secondary instrument (5). Note reference (12). Primary wait (1).
	db 110	; Secondary instrument (5). New escaped note: 63. Primary wait (1).
	db 63	;   Escape note value.
	db 172	; Secondary instrument (5). Note reference (12). Secondary wait (3).
	db 164	; Secondary instrument (5). Note reference (4). Secondary wait (3).
	db 172	; Secondary instrument (5). Note reference (12). Secondary wait (3).
	db 175	; Secondary instrument (5). Same escaped note: 63. Secondary wait (3).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track10
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 240	; New instrument (2). Note reference (0). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 84	; Primary instrument (1). Note reference (4). Primary wait (1).
	db 4	; Note reference (4). 
	db 97	; Secondary instrument (5). Note reference (1). Primary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (1).
	db 225	; Secondary instrument (5). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track11
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 240	; New instrument (2). Note reference (0). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 167	; Secondary instrument (5). Note reference (7). Secondary wait (3).
	db 161	; Secondary instrument (5). Note reference (1). Secondary wait (3).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (3).
	db 238	; Secondary instrument (5). New escaped note: 64. New wait (127).
	db 64	;   Escape note value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track12
	db 92	; Primary instrument (1). Note reference (12). Primary wait (1).
	db 252	; New instrument (2). Note reference (12). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 84	; Primary instrument (1). Note reference (4). Primary wait (1).
	db 4	; Note reference (4). 
	db 90	; Primary instrument (1). Note reference (10). Primary wait (1).
	db 202	; Note reference (10). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track13
	db 95	; Primary instrument (1). Same escaped note: 70. Primary wait (1).
	db 255	; New instrument (2). Same escaped note: 70. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 164	; Secondary instrument (5). Note reference (4). Secondary wait (3).
	db 170	; Secondary instrument (5). Note reference (10). Secondary wait (3).
	db 175	; Secondary instrument (5). Same escaped note: 70. Secondary wait (3).
	db 228	; Secondary instrument (5). Note reference (4). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track14
	db 90	; Primary instrument (1). Note reference (10). Primary wait (1).
	db 250	; New instrument (2). Note reference (10). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 164	; Secondary instrument (5). Note reference (4). Secondary wait (3).
	db 170	; Secondary instrument (5). Note reference (10). Secondary wait (3).
	db 92	; Primary instrument (1). Note reference (12). Primary wait (1).
	db 204	; Note reference (12). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track15
	db 174	; Secondary instrument (5). New escaped note: 53. Secondary wait (3).
	db 53	;   Escape note value.
	db 162	; Secondary instrument (5). Note reference (2). Secondary wait (3).
	db 166	; Secondary instrument (5). Note reference (6). Secondary wait (3).
	db 167	; Secondary instrument (5). Note reference (7). Secondary wait (3).
	db 161	; Secondary instrument (5). Note reference (1). Secondary wait (3).
	db 224	; Secondary instrument (5). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track16
	db 92	; Primary instrument (1). Note reference (12). Primary wait (1).
	db 252	; New instrument (2). Note reference (12). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (1).
	db 7	; Note reference (7). 
	db 86	; Primary instrument (1). Note reference (6). Primary wait (1).
	db 198	; Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track17
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 242	; New instrument (2). Note reference (2). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (3).
	db 161	; Secondary instrument (5). Note reference (1). Secondary wait (3).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (1).
	db 192	; Note reference (0). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track18
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 242	; New instrument (2). Note reference (2). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 174	; Secondary instrument (5). New escaped note: 63. Secondary wait (3).
	db 63	;   Escape note value.
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (3).
	db 95	; Primary instrument (1). Same escaped note: 63. Primary wait (1).
	db 207	; Same escaped note: 63. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track19
	db 162	; Secondary instrument (5). Note reference (2). Secondary wait (3).
	db 160	; Secondary instrument (5). Note reference (0). Secondary wait (3).
	db 174	; Secondary instrument (5). New escaped note: 54. Secondary wait (3).
	db 54	;   Escape note value.
	db 161	; Secondary instrument (5). Note reference (1). Secondary wait (3).
	db 162	; Secondary instrument (5). Note reference (2). Secondary wait (3).
	db 231	; Secondary instrument (5). Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track20
	db 174	; Secondary instrument (5). New escaped note: 50. Secondary wait (3).
	db 50	;   Escape note value.
	db 174	; Secondary instrument (5). New escaped note: 52. Secondary wait (3).
	db 52	;   Escape note value.
	db 174	; Secondary instrument (5). New escaped note: 54. Secondary wait (3).
	db 54	;   Escape note value.
	db 162	; Secondary instrument (5). Note reference (2). Secondary wait (3).
	db 166	; Secondary instrument (5). Note reference (6). Secondary wait (3).
	db 231	; Secondary instrument (5). Note reference (7). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track21
	db 81	; Primary instrument (1). Note reference (1). Primary wait (1).
	db 241	; New instrument (2). Note reference (1). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 87	; Primary instrument (1). Note reference (7). Primary wait (1).
	db 7	; Note reference (7). 
	db 86	; Primary instrument (1). Note reference (6). Primary wait (1).
	db 198	; Note reference (6). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track22
	db 39	; Secondary instrument (5). Note reference (7). 
	db 38	; Secondary instrument (5). Note reference (6). 
	db 103	; Secondary instrument (5). Note reference (7). Primary wait (1).
	db 97	; Secondary instrument (5). Note reference (1). Primary wait (1).
	db 96	; Secondary instrument (5). Note reference (0). Primary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 242	; New instrument (2). Note reference (2). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 54. Primary wait (1).
	db 54	;   Escape note value.
	db 207	; Same escaped note: 54. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track23
	db 85	; Primary instrument (1). Note reference (5). Primary wait (1).
	db 245	; New instrument (2). Note reference (5). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 174	; Secondary instrument (5). New escaped note: 50. Secondary wait (3).
	db 50	;   Escape note value.
	db 163	; Secondary instrument (5). Note reference (3). Secondary wait (3).
	db 168	; Secondary instrument (5). Note reference (8). Secondary wait (3).
	db 235	; Secondary instrument (5). Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track24
	db 153	; Primary instrument (1). Note reference (9). Secondary wait (3).
	db 249	; New instrument (3). Note reference (9). New wait (11).
	db 3	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 155	; Primary instrument (1). Note reference (11). Secondary wait (3).
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track25
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (3).
	db 248	; New instrument (3). Note reference (8). New wait (11).
	db 3	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (1).
	db 249	; New instrument (2). Note reference (9). New wait (127).
	db 2	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track26
	db 91	; Primary instrument (1). Note reference (11). Primary wait (1).
	db 251	; New instrument (2). Note reference (11). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 42. Primary wait (1).
	db 42	;   Escape note value.
	db 15	; Same escaped note: 42. 
	db 89	; Primary instrument (1). Note reference (9). Primary wait (1).
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track27
	db 85	; Primary instrument (1). Note reference (5). Primary wait (1).
	db 245	; New instrument (2). Note reference (5). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 174	; Secondary instrument (5). New escaped note: 50. Secondary wait (3).
	db 50	;   Escape note value.
	db 163	; Secondary instrument (5). Note reference (3). Secondary wait (3).
	db 174	; Secondary instrument (5). New escaped note: 47. Secondary wait (3).
	db 47	;   Escape note value.
	db 235	; Secondary instrument (5). Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track28
	db 243	; New instrument (0). Note reference (3). New wait (15).
	db 0	;   Escape instrument value.
	db 15	;   Escape wait value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (1).
	db 249	; New instrument (2). Note reference (9). New wait (127).
	db 2	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track29
	db 83	; Primary instrument (1). Note reference (3). Primary wait (1).
	db 243	; New instrument (2). Note reference (3). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (1).
	db 11	; Note reference (11). 
	db 94	; Primary instrument (1). New escaped note: 41. Primary wait (1).
	db 41	;   Escape note value.
	db 207	; Same escaped note: 41. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track30
	db 88	; Primary instrument (1). Note reference (8). Primary wait (1).
	db 248	; New instrument (2). Note reference (8). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 40. Primary wait (1).
	db 40	;   Escape note value.
	db 15	; Same escaped note: 40. 
	db 243	; New instrument (0). Note reference (3). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track31
	db 88	; Primary instrument (1). Note reference (8). Primary wait (1).
	db 248	; New instrument (2). Note reference (8). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 158	; Primary instrument (1). New escaped note: 34. Secondary wait (3).
	db 34	;   Escape note value.
	db 255	; New instrument (3). Same escaped note: 34. New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track32
	db 86	; Primary instrument (1). Note reference (6). Primary wait (1).
	db 246	; New instrument (2). Note reference (6). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 82	; Primary instrument (1). Note reference (2). Primary wait (1).
	db 2	; Note reference (2). 
	db 94	; Primary instrument (1). New escaped note: 53. Primary wait (1).
	db 53	;   Escape note value.
	db 207	; Same escaped note: 53. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track33
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (3).
	db 242	; New instrument (3). Note reference (2). New wait (11).
	db 3	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 53. Primary wait (1).
	db 53	;   Escape note value.
	db 255	; New instrument (2). Same escaped note: 53. New wait (127).
	db 2	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track34
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (1).
	db 51	;   Escape note value.
	db 255	; New instrument (2). Same escaped note: 51. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 50. Primary wait (1).
	db 50	;   Escape note value.
	db 15	; Same escaped note: 50. 
	db 94	; Primary instrument (1). New escaped note: 51. Primary wait (1).
	db 51	;   Escape note value.
	db 207	; Same escaped note: 51. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track35
	db 94	; Primary instrument (1). New escaped note: 53. Primary wait (1).
	db 53	;   Escape note value.
	db 255	; New instrument (2). Same escaped note: 53. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (1).
	db 8	; Note reference (8). 
	db 94	; Primary instrument (1). New escaped note: 50. Primary wait (1).
	db 50	;   Escape note value.
	db 207	; Same escaped note: 50. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track36
	db 83	; Primary instrument (1). Note reference (3). Primary wait (1).
	db 243	; New instrument (2). Note reference (3). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 158	; Primary instrument (1). New escaped note: 47. Secondary wait (3).
	db 47	;   Escape note value.
	db 255	; New instrument (3). Same escaped note: 47. New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track37
	db 206	; New escaped note: 47. New wait (7).
	db 47	;   Escape note value.
	db 7	;   Escape wait value.
	db 147	; Primary instrument (1). Note reference (3). Secondary wait (3).
	db 243	; New instrument (3). Note reference (3). New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track38
	db 195	; Note reference (3). New wait (7).
	db 7	;   Escape wait value.
	db 88	; Primary instrument (1). Note reference (8). Primary wait (1).
	db 248	; New instrument (3). Note reference (8). New wait (5).
	db 3	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 91	; Primary instrument (1). Note reference (11). Primary wait (1).
	db 203	; Note reference (11). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track39
	db 89	; Primary instrument (1). Note reference (9). Primary wait (1).
	db 249	; New instrument (2). Note reference (9). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 50. Primary wait (1).
	db 50	;   Escape note value.
	db 15	; Same escaped note: 50. 
	db 171	; Secondary instrument (5). Note reference (11). Secondary wait (3).
	db 233	; Secondary instrument (5). Note reference (9). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track40
	db 174	; Secondary instrument (5). New escaped note: 42. Secondary wait (3).
	db 42	;   Escape note value.
	db 174	; Secondary instrument (5). New escaped note: 40. Secondary wait (3).
	db 40	;   Escape note value.
	db 149	; Primary instrument (1). Note reference (5). Secondary wait (3).
	db 245	; New instrument (3). Note reference (5). New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track41
	db 197	; Note reference (5). New wait (7).
	db 7	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 39. Primary wait (1).
	db 39	;   Escape note value.
	db 255	; New instrument (2). Same escaped note: 39. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (1).
	db 197	; Note reference (5). New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track42
	db 94	; Primary instrument (1). New escaped note: 36. Primary wait (1).
	db 36	;   Escape note value.
	db 255	; New instrument (2). Same escaped note: 36. New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 94	; Primary instrument (1). New escaped note: 34. Primary wait (1).
	db 34	;   Escape note value.
	db 15	; Same escaped note: 34. 
	db 94	; Primary instrument (1). New escaped note: 36. Primary wait (1).
	db 36	;   Escape note value.
	db 207	; Same escaped note: 36. New wait (127).
	db 127	;   Escape wait value.

mySong_Subsong0_Track43
	db 85	; Primary instrument (1). Note reference (5). Primary wait (1).
	db 245	; New instrument (2). Note reference (5). New wait (5).
	db 2	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 89	; Primary instrument (1). Note reference (9). Primary wait (1).
	db 9	; Note reference (9). 
	db 158	; Primary instrument (1). New escaped note: 31. Secondary wait (3).
	db 31	;   Escape note value.
	db 255	; New instrument (3). Same escaped note: 31. New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track44
	db 243	; New instrument (0). Note reference (3). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track45
	db 152	; Primary instrument (1). Note reference (8). Secondary wait (3).
	db 248	; New instrument (3). Note reference (8). New wait (11).
	db 3	;   Escape instrument value.
	db 11	;   Escape wait value.
	db 243	; New instrument (0). Note reference (3). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track46
	db 243	; New instrument (0). Note reference (3). New wait (7).
	db 0	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 149	; Primary instrument (1). Note reference (5). Secondary wait (3).
	db 245	; New instrument (3). Note reference (5). New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.

mySong_Subsong0_Track47
	db 197	; Note reference (5). New wait (7).
	db 7	;   Escape wait value.
	db 243	; New instrument (0). Note reference (3). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

; The note indexes.
mySong_Subsong0_NoteIndexes
	db 62	; Note for index 0.
	db 60	; Note for index 1.
	db 55	; Note for index 2.
	db 48	; Note for index 3.
	db 67	; Note for index 4.
	db 38	; Note for index 5.
	db 57	; Note for index 6.
	db 58	; Note for index 7.
	db 46	; Note for index 8.
	db 43	; Note for index 9.
	db 69	; Note for index 10.
	db 45	; Note for index 11.
	db 65	; Note for index 12.

