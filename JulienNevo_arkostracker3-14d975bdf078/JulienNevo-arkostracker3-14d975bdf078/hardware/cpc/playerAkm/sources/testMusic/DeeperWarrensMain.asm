; Deeper Warrens, Song part, encoded in the AKM (minimalist) format V0.


	dw DeeperWarrens_InstrumentIndexes	; Index table for the Instruments.
	dw 0	; Index table for the Arpeggios.
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw DeeperWarrens_Subsong0

; The Instrument indexes.
DeeperWarrens_InstrumentIndexes
	dw DeeperWarrens_Instrument0
	dw DeeperWarrens_Instrument1
	dw DeeperWarrens_Instrument2
	dw DeeperWarrens_Instrument3
	dw DeeperWarrens_Instrument4
	dw DeeperWarrens_Instrument5
	dw DeeperWarrens_Instrument6

; The Instrument.
DeeperWarrens_Instrument0
	db 255	; Speed.

DeeperWarrens_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
	dw DeeperWarrens_Instrument0Loop	; Loops.

DeeperWarrens_Instrument1
	db 2	; Speed.

	db 161	; Volume: 8.
	db 1	; Arpeggio: 0.
	db 1	; Noise: 1.

	db 45	; Volume: 11.

DeeperWarrens_Instrument1Loop	db 113	; Volume: 12.
	dw -1	; Pitch: -1.

	db 113	; Volume: 12.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw -1	; Pitch: -1.

	db 109	; Volume: 11.
	dw 1	; Pitch: 1.

	db 109	; Volume: 11.
	dw -1	; Pitch: -1.

	db 113	; Volume: 12.
	dw 1	; Pitch: 1.

	db 4	; End the instrument.
	dw DeeperWarrens_Instrument1Loop	; Loops.

DeeperWarrens_Instrument2
	db 0	; Speed.

	db 189	; Volume: 15.
	db 31	; Arpeggio: 15.
	db 6	; Noise: 6.

	db 189	; Volume: 15.
	db 20	; Arpeggio: 10.

	db 189	; Volume: 15.
	db 12	; Arpeggio: 6.

	db 185	; Volume: 14.
	db 6	; Arpeggio: 3.

	db 57	; Volume: 14.

	db 4	; End the instrument.
	dw DeeperWarrens_Instrument0Loop	; Loop to silence.

DeeperWarrens_Instrument3
	db 0	; Speed.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 1	; Noise: 1.

	db 189	; Volume: 15.
	db 255	; Arpeggio: -1.
	db 1	; Noise: 1.

	db 189	; Volume: 15.
	db 250	; Arpeggio: -3.

	db 185	; Volume: 14.
	db 244	; Arpeggio: -6.

	db 181	; Volume: 13.
	db 238	; Arpeggio: -9.

	db 177	; Volume: 12.
	db 230	; Arpeggio: -13.

	db 173	; Volume: 11.
	db 228	; Arpeggio: -14.

	db 169	; Volume: 10.
	db 226	; Arpeggio: -15.

	db 4	; End the instrument.
	dw DeeperWarrens_Instrument0Loop	; Loop to silence.

DeeperWarrens_Instrument4
	db 0	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 232	; Volume: 13.
	db 1	; Noise.

	db 216	; Volume: 11.
	db 1	; Noise.

	db 200	; Volume: 9.
	db 1	; Noise.

	db 184	; Volume: 7.
	db 1	; Noise.

	db 168	; Volume: 5.
	db 1	; Noise.

	db 152	; Volume: 3.
	db 1	; Noise.

	db 136	; Volume: 1.
	db 1	; Noise.

	db 4	; End the instrument.
	dw DeeperWarrens_Instrument0Loop	; Loop to silence.

DeeperWarrens_Instrument5
	db 0	; Speed.

	db 232	; Volume: 13.
	db 5	; Noise.

	db 216	; Volume: 11.
	db 5	; Noise.

	db 208	; Volume: 10.
	db 5	; Noise.

	db 200	; Volume: 9.
	db 5	; Noise.

	db 184	; Volume: 7.
	db 5	; Noise.

	db 4	; End the instrument.
	dw DeeperWarrens_Instrument0Loop	; Loop to silence.

DeeperWarrens_Instrument6
	db 0	; Speed.

	db 181	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 3	; Noise: 3.

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

	db 4	; End the instrument.
	dw DeeperWarrens_Instrument0Loop	; Loop to silence.

DeeperWarrens_ArpeggioIndexes


DeeperWarrens_PitchIndexes


; Deeper Warrens, Subsong 0.
; ----------------------------------

DeeperWarrens_Subsong0
	dw DeeperWarrens_Subsong0_NoteIndexes	; Index table for the notes.
	dw DeeperWarrens_Subsong0_TrackIndexes	; Index table for the Tracks.

	db 8	; Initial speed.

	db 6	; Most used instrument.
	db 5	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 28	; Default start note in tracks.
	db 1	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.

; The Linker.
; Pattern 0
DeeperWarrens_Subsong0_Loop
	db 170	; State byte.
	db 63	; New height.
	db 128	; New track (2) for channel 1, as a reference (index 0).
	db ((DeeperWarrens_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 2, as an offset. Offset MSB, then LSB.
	db ((DeeperWarrens_Subsong0_Track0 - ($ + 1)) & 255)
	db ((DeeperWarrens_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 3, as an offset. Offset MSB, then LSB.
	db ((DeeperWarrens_Subsong0_Track1 - ($ + 1)) & 255)

; Pattern 1
	db 0	; State byte.

; Pattern 2
	db 160	; State byte.
	db ((DeeperWarrens_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 2, as an offset. Offset MSB, then LSB.
	db ((DeeperWarrens_Subsong0_Track3 - ($ + 1)) & 255)
	db ((DeeperWarrens_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 3, as an offset. Offset MSB, then LSB.
	db ((DeeperWarrens_Subsong0_Track4 - ($ + 1)) & 255)

; Pattern 3
	db 0	; State byte.

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
	dw DeeperWarrens_Subsong0_Loop

; The indexes of the tracks.
DeeperWarrens_Subsong0_TrackIndexes
	dw DeeperWarrens_Subsong0_Track2	; Track 2, index 0.

DeeperWarrens_Subsong0_Track0
	db 12	; Note with effects flag
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 98	;    Volume effect, with inverted volume: 6.
	db 144	; Primary instrument (6). Note reference (0). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 144	; Primary instrument (6). Note reference (0). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 149	; Primary instrument (6). Note reference (5). Secondary wait (1).
	db 148	; Primary instrument (6). Note reference (4). Secondary wait (1).
	db 149	; Primary instrument (6). Note reference (5). Secondary wait (1).
	db 149	; Primary instrument (6). Note reference (5). Secondary wait (1).
	db 149	; Primary instrument (6). Note reference (5). Secondary wait (1).
	db 148	; Primary instrument (6). Note reference (4). Secondary wait (1).
	db 149	; Primary instrument (6). Note reference (5). Secondary wait (1).
	db 151	; Primary instrument (6). Note reference (7). Secondary wait (1).
	db 151	; Primary instrument (6). Note reference (7). Secondary wait (1).
	db 150	; Primary instrument (6). Note reference (6). Secondary wait (1).
	db 151	; Primary instrument (6). Note reference (7). Secondary wait (1).
	db 151	; Primary instrument (6). Note reference (7). Secondary wait (1).
	db 151	; Primary instrument (6). Note reference (7). Secondary wait (1).
	db 150	; Primary instrument (6). Note reference (6). Secondary wait (1).
	db 151	; Primary instrument (6). Note reference (7). Secondary wait (1).
	db 149	; Primary instrument (6). Note reference (5). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 144	; Primary instrument (6). Note reference (0). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 144	; Primary instrument (6). Note reference (0). Secondary wait (1).
	db 145	; Primary instrument (6). Note reference (1). Secondary wait (1).
	db 209	; Primary instrument (6). Note reference (1). New wait (127).
	db 127	;   Escape wait value.

DeeperWarrens_Subsong0_Track1
	db 12	; Note with effects flag
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 98	; Secondary instrument (5). Note reference (2). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 98	; Secondary instrument (5). Note reference (2). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 98	; Secondary instrument (5). Note reference (2). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 98	; Secondary instrument (5). Note reference (2). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 98	; Secondary instrument (5). Note reference (2). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 98	; Secondary instrument (5). Note reference (2). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 98	; Secondary instrument (5). Note reference (2). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 110	; Secondary instrument (5). New escaped note: 75. Primary wait (0).
	db 75	;   Escape note value.
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 104	; Secondary instrument (5). Note reference (8). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 208	; Primary instrument (6). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

DeeperWarrens_Subsong0_Track2
	db 12	; Note with effects flag
	db 207	; Same escaped note: 28. New wait (15).
	db 15	;   Escape wait value.
	db 98	;    Volume effect, with inverted volume: 6.
	db 14	; New escaped note: 35. 
	db 35	;   Escape note value.
	db 10	; Note reference (10). 
	db 206	; New escaped note: 28. New wait (127).
	db 28	;   Escape note value.
	db 127	;   Escape wait value.

DeeperWarrens_Subsong0_Track3
	db 12	; Note with effects flag
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 91	; Primary instrument (6). Note reference (11). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 91	; Primary instrument (6). Note reference (11). Primary wait (0).
	db 94	; Primary instrument (6). New escaped note: 47. Primary wait (0).
	db 47	;   Escape note value.
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (6). New escaped note: 56. Primary wait (0).
	db 56	;   Escape note value.
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 85	; Primary instrument (6). Note reference (5). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 94	; Primary instrument (6). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 87	; Primary instrument (6). Note reference (7). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 95	; Primary instrument (6). Same escaped note: 54. Primary wait (0).
	db 94	; Primary instrument (6). New escaped note: 52. Primary wait (0).
	db 52	;   Escape note value.
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 91	; Primary instrument (6). Note reference (11). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (6). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 91	; Primary instrument (6). Note reference (11). Primary wait (0).
	db 208	; Primary instrument (6). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

DeeperWarrens_Subsong0_Track4
	db 12	; Note with effects flag
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 98	;    Volume effect, with inverted volume: 6.
	db 66	; Note reference (2). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 122	; New instrument (2). Note reference (10). Primary wait (0).
	db 2	;   Escape instrument value.
	db 110	; Secondary instrument (5). New escaped note: 48. Primary wait (0).
	db 48	;   Escape note value.
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 130	; Note reference (2). Secondary wait (1).
	db 121	; New instrument (3). Note reference (9). Primary wait (0).
	db 3	;   Escape instrument value.
	db 111	; Secondary instrument (5). Same escaped note: 48. Primary wait (0).
	db 144	; Primary instrument (6). Note reference (0). Secondary wait (1).
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 66	; Note reference (2). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 121	; New instrument (3). Note reference (9). Primary wait (0).
	db 3	;   Escape instrument value.
	db 94	; Primary instrument (6). New escaped note: 39. Primary wait (0).
	db 39	;   Escape note value.
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 66	; Note reference (2). Primary wait (0).
	db 66	; Note reference (2). Primary wait (0).
	db 121	; New instrument (3). Note reference (9). Primary wait (0).
	db 3	;   Escape instrument value.
	db 95	; Primary instrument (6). Same escaped note: 39. Primary wait (0).
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 73	; Note reference (9). Primary wait (0).
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 66	; Note reference (2). Primary wait (0).
	db 110	; Secondary instrument (5). New escaped note: 72. Primary wait (0).
	db 72	;   Escape note value.
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 121	; New instrument (3). Note reference (9). Primary wait (0).
	db 3	;   Escape instrument value.
	db 94	; Primary instrument (6). New escaped note: 39. Primary wait (0).
	db 39	;   Escape note value.
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 86	; Primary instrument (6). Note reference (6). Primary wait (0).
	db 130	; Note reference (2). Secondary wait (1).
	db 121	; New instrument (3). Note reference (9). Primary wait (0).
	db 3	;   Escape instrument value.
	db 95	; Primary instrument (6). Same escaped note: 39. Primary wait (0).
	db 150	; Primary instrument (6). Note reference (6). Secondary wait (1).
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 66	; Note reference (2). Primary wait (0).
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 121	; New instrument (3). Note reference (9). Primary wait (0).
	db 3	;   Escape instrument value.
	db 84	; Primary instrument (6). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 114	; New instrument (4). Note reference (2). Primary wait (0).
	db 4	;   Escape instrument value.
	db 99	; Secondary instrument (5). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 178	; New instrument (2). Note reference (2). Secondary wait (1).
	db 2	;   Escape instrument value.
	db 74	; Note reference (10). Primary wait (0).
	db 74	; Note reference (10). Primary wait (0).
	db 80	; Primary instrument (6). Note reference (0). Primary wait (0).
	db 249	; New instrument (4). Note reference (9). New wait (127).
	db 4	;   Escape instrument value.
	db 127	;   Escape wait value.

; The note indexes.
DeeperWarrens_Subsong0_NoteIndexes
	db 37	; Note for index 0.
	db 25	; Note for index 1.
	db 36	; Note for index 2.
	db 41	; Note for index 3.
	db 44	; Note for index 4.
	db 32	; Note for index 5.
	db 42	; Note for index 6.
	db 30	; Note for index 7.
	db 34	; Note for index 8.
	db 45	; Note for index 9.
	db 33	; Note for index 10.
	db 49	; Note for index 11.

