; A Harmless Grenade, Song part, encoded in the AKM (minimalist) format V0.


AHarmlessGrenade_Start
AHarmlessGrenade_StartDisarkGenerateExternalLabel

AHarmlessGrenade_DisarkPointerRegionStart0
	dw AHarmlessGrenade_InstrumentIndexes	; Index table for the Instruments.
	dw AHarmlessGrenade_ArpeggioIndexes - 2	; Index table for the Arpeggios.
	dw AHarmlessGrenade_PitchIndexes - 2	; Index table for the Pitches.

; The subsongs references.
	dw AHarmlessGrenade_Subsong0
AHarmlessGrenade_DisarkPointerRegionEnd0

; The Instrument indexes.
AHarmlessGrenade_InstrumentIndexes
AHarmlessGrenade_DisarkPointerRegionStart1
	dw AHarmlessGrenade_Instrument0
	dw AHarmlessGrenade_Instrument1
	dw AHarmlessGrenade_Instrument2
	dw AHarmlessGrenade_Instrument3
	dw AHarmlessGrenade_Instrument4
	dw AHarmlessGrenade_Instrument5
	dw AHarmlessGrenade_Instrument6
	dw AHarmlessGrenade_Instrument7
	dw AHarmlessGrenade_Instrument8
	dw AHarmlessGrenade_Instrument9
	dw AHarmlessGrenade_Instrument10
	dw AHarmlessGrenade_Instrument11
	dw AHarmlessGrenade_Instrument12
	dw AHarmlessGrenade_Instrument13
	dw AHarmlessGrenade_Instrument14
	dw AHarmlessGrenade_Instrument15
	dw AHarmlessGrenade_Instrument16
	dw AHarmlessGrenade_Instrument17
	dw AHarmlessGrenade_Instrument18
	dw AHarmlessGrenade_Instrument19
AHarmlessGrenade_DisarkPointerRegionEnd1

; The Instrument.
AHarmlessGrenade_DisarkByteRegionStart2
AHarmlessGrenade_Instrument0
	db 255	; Speed.

AHarmlessGrenade_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart3
	dw AHarmlessGrenade_Instrument0Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd3

AHarmlessGrenade_Instrument1
	db 1	; Speed.

	db 210, 12	; Arpeggio: 12.

	db 178, 12	; Arpeggio: 12.

	db 178, 12	; Arpeggio: 12.

	db 82
	db 169	; Volume: 10.
	db 24	; Arpeggio: 12.

	db 41	; Volume: 10.

	db 169	; Volume: 10.
	db 24	; Arpeggio: 12.

	db 37	; Volume: 9.

	db 33	; Volume: 8.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart4
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd4

AHarmlessGrenade_Instrument2
	db 0	; Speed.

	db 189	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 2	; Noise: 2.

	db 253	; Volume: 15.
	db 1	; Arpeggio: 0.
	db 1	; Noise: 1.
	dw 32	; Pitch: 32.

	db 125	; Volume: 15.
	dw 48	; Pitch: 48.

	db 125	; Volume: 15.
	dw 68	; Pitch: 68.

	db 125	; Volume: 15.
	dw 116	; Pitch: 116.

	db 125	; Volume: 15.
	dw 228	; Pitch: 228.

	db 121	; Volume: 14.
	dw 180	; Pitch: 180.

	db 117	; Volume: 13.
	dw 292	; Pitch: 292.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart5
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd5

AHarmlessGrenade_Instrument3
	db 0	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 216	; Volume: 11.
	db 1	; Noise.

	db 184	; Volume: 7.
	db 1	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart6
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd6

AHarmlessGrenade_Instrument4
	db 0	; Speed.

	db 248	; Volume: 15.
	db 4	; Noise.

	db 200	; Volume: 9.
	db 1	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart7
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd7

AHarmlessGrenade_Instrument5
	db 0	; Speed.

AHarmlessGrenade_Instrument5Loop	db 248	; Volume: 15.
	db 1	; Noise.

	db 200	; Volume: 9.
	db 1	; Noise.

	db 176	; Volume: 6.
	db 1	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart8
	dw AHarmlessGrenade_Instrument5Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd8

AHarmlessGrenade_Instrument6
	db 3	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart9
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd9

AHarmlessGrenade_Instrument7
	db 2	; Speed.

	db 61	; Volume: 15.

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
AHarmlessGrenade_DisarkPointerRegionStart10
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd10

AHarmlessGrenade_Instrument8
	db 0	; Speed.

AHarmlessGrenade_Instrument8Loop	db 74
	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart11
	dw AHarmlessGrenade_Instrument8Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd11

AHarmlessGrenade_Instrument9
	db 0	; Speed.

	db 248	; Volume: 15.
	db 2	; Noise.

	db 57	; Volume: 14.

	db 245	; Volume: 13.
	db 1	; Arpeggio: 0.
	db 1	; Noise: 1.
	dw 208	; Pitch: 208.

	db 237	; Volume: 11.
	db 1	; Arpeggio: 0.
	db 1	; Noise: 1.
	dw 400	; Pitch: 400.

	db 216	; Volume: 11.
	db 1	; Noise.

	db 216	; Volume: 11.
	db 3	; Noise.

	db 208	; Volume: 10.
	db 4	; Noise.

	db 200	; Volume: 9.
	db 1	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart12
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd12

AHarmlessGrenade_Instrument10
	db 4	; Speed.

AHarmlessGrenade_Instrument10Loop	db 82
	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart13
	dw AHarmlessGrenade_Instrument10Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd13

AHarmlessGrenade_Instrument11
	db 1	; Speed.

AHarmlessGrenade_Instrument11Loop	db 194, 12	; Arpeggio: 12.

	db 194, 12	; Arpeggio: 12.

	db 120	; Volume: 15.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart14
	dw AHarmlessGrenade_Instrument11Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd14

AHarmlessGrenade_Instrument12
	db 0	; Speed.

AHarmlessGrenade_Instrument12Loop	db 61	; Volume: 15.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart15
	dw AHarmlessGrenade_Instrument12Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd15

AHarmlessGrenade_Instrument13
	db 0	; Speed.

	db 61	; Volume: 15.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart16
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd16

AHarmlessGrenade_Instrument14
	db 0	; Speed.

AHarmlessGrenade_Instrument14Loop	db 58
	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart17
	dw AHarmlessGrenade_Instrument14Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd17

AHarmlessGrenade_Instrument15
	db 1	; Speed.

	db 61	; Volume: 15.

AHarmlessGrenade_Instrument15Loop	db 121	; Volume: 14.
	dw -5	; Pitch: -5.

	db 49	; Volume: 12.

	db 109	; Volume: 11.
	dw 5	; Pitch: 5.

	db 61	; Volume: 15.

	db 117	; Volume: 13.
	dw -7	; Pitch: -7.

	db 37	; Volume: 9.

	db 105	; Volume: 10.
	dw 32	; Pitch: 32.

	db 45	; Volume: 11.

	db 49	; Volume: 12.

	db 57	; Volume: 14.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart18
	dw AHarmlessGrenade_Instrument15Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd18

AHarmlessGrenade_Instrument16
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
AHarmlessGrenade_DisarkPointerRegionStart19
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd19

AHarmlessGrenade_Instrument17
	db 0	; Speed.

	db 232	; Volume: 13.
	db 9	; Noise.

	db 216	; Volume: 11.
	db 9	; Noise.

	db 208	; Volume: 10.
	db 9	; Noise.

	db 200	; Volume: 9.
	db 9	; Noise.

	db 184	; Volume: 7.
	db 9	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart20
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd20

AHarmlessGrenade_Instrument18
	db 0	; Speed.

	db 232	; Volume: 13.
	db 17	; Noise.

	db 216	; Volume: 11.
	db 17	; Noise.

	db 208	; Volume: 10.
	db 17	; Noise.

	db 200	; Volume: 9.
	db 17	; Noise.

	db 184	; Volume: 7.
	db 17	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart21
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd21

AHarmlessGrenade_Instrument19
	db 0	; Speed.

	db 232	; Volume: 13.
	db 25	; Noise.

	db 216	; Volume: 11.
	db 25	; Noise.

	db 208	; Volume: 10.
	db 25	; Noise.

	db 200	; Volume: 9.
	db 25	; Noise.

	db 184	; Volume: 7.
	db 25	; Noise.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart22
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd22

AHarmlessGrenade_DisarkByteRegionEnd2
AHarmlessGrenade_ArpeggioIndexes
AHarmlessGrenade_DisarkPointerRegionStart23
	dw AHarmlessGrenade_Arpeggio1
	dw AHarmlessGrenade_Arpeggio2
AHarmlessGrenade_DisarkPointerRegionEnd23

AHarmlessGrenade_DisarkByteRegionStart24
AHarmlessGrenade_Arpeggio1
	db 0	; Speed

	db 0	; Value: 0
	db 24	; Value: 12
	db 18	; Value: 9
	db -24	; Value: -12
	db 36	; Value: 18
	db 0 * 2 + 1	; Loops to index 0.
AHarmlessGrenade_Arpeggio2
	db 0	; Speed

	db 0	; Value: 0
	db 12	; Value: 6
	db -6	; Value: -3
	db -24	; Value: -12
	db -12	; Value: -6
	db 0	; Value: 0
	db 24	; Value: 12
	db 0 * 2 + 1	; Loops to index 0.
AHarmlessGrenade_DisarkByteRegionEnd24

AHarmlessGrenade_PitchIndexes
AHarmlessGrenade_DisarkPointerRegionStart25
	dw AHarmlessGrenade_Pitch1
AHarmlessGrenade_DisarkPointerRegionEnd25

AHarmlessGrenade_DisarkByteRegionStart26
AHarmlessGrenade_Pitch1
	db 1	; Speed

	db 0	; Value: 0
	db 0	; Value: 0
	db 0	; Value: 0
	db -2	; Value: -1
	db -8	; Value: -4
	db 4	; Value: 2
	db 2 * 2 + 1	; Loops to index 2.
AHarmlessGrenade_DisarkByteRegionEnd26

; A Harmless Grenade, Subsong 0.
; ----------------------------------

AHarmlessGrenade_Subsong0
AHarmlessGrenade_Subsong0DisarkPointerRegionStart0
	dw AHarmlessGrenade_Subsong0_NoteIndexes	; Index table for the notes.
	dw AHarmlessGrenade_Subsong0_TrackIndexes	; Index table for the Tracks.
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd0

AHarmlessGrenade_Subsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 1	; Most used instrument.
	db 2	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 21	; Default start note in tracks.
	db 10	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
AHarmlessGrenade_Subsong0DisarkByteRegionEnd1

; The Linker.
AHarmlessGrenade_Subsong0DisarkByteRegionStart2
; Pattern 0
AHarmlessGrenade_Subsong0_Loop
	db 250	; State byte.
	db 31	; New height.
	db 132	; New track (0) for channel 1, as a reference (index 4).
	db 0	; New transposition on channel 2.
	db 128	; New track (22) for channel 2, as a reference (index 0).
	db 0	; New transposition on channel 3.
	db 128	; New track (22) for channel 3, as a reference (index 0).

; Pattern 1
	db 160	; State byte.
	db 133	; New track (1) for channel 2, as a reference (index 5).
	db 133	; New track (1) for channel 3, as a reference (index 5).

; Pattern 2
	db 128	; State byte.
	db ((AHarmlessGrenade_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track2 - ($ + 1)) & 255)

; Pattern 3
	db 0	; State byte.

; Pattern 4
	db 168	; State byte.
	db ((AHarmlessGrenade_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 1, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track3 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 2, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track5 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track4 - ($ + 1)) & 255)

; Pattern 5
	db 170	; State byte.
	db 23	; New height.
	db 136	; New track (6) for channel 1, as a reference (index 8).
	db 135	; New track (8) for channel 2, as a reference (index 7).
	db 137	; New track (7) for channel 3, as a reference (index 9).

; Pattern 6
	db 170	; State byte.
	db 7	; New height.
	db ((AHarmlessGrenade_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track9 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 2, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track10 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track11 - ($ + 1)) & 255)

; Pattern 7
	db 170	; State byte.
	db 23	; New height.
	db 136	; New track (6) for channel 1, as a reference (index 8).
	db 135	; New track (8) for channel 2, as a reference (index 7).
	db 137	; New track (7) for channel 3, as a reference (index 9).

; Pattern 8
	db 170	; State byte.
	db 7	; New height.
	db ((AHarmlessGrenade_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track12 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 2, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track13 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track14 - ($ + 1)) & 255)

; Pattern 9
	db 170	; State byte.
	db 23	; New height.
	db 136	; New track (6) for channel 1, as a reference (index 8).
	db 135	; New track (8) for channel 2, as a reference (index 7).
	db 137	; New track (7) for channel 3, as a reference (index 9).

; Pattern 10
	db 170	; State byte.
	db 7	; New height.
	db ((AHarmlessGrenade_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track9 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 2, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track10 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track11 - ($ + 1)) & 255)

; Pattern 11
	db 170	; State byte.
	db 31	; New height.
	db 138	; New track (15) for channel 1, as a reference (index 10).
	db 139	; New track (16) for channel 2, as a reference (index 11).
	db ((AHarmlessGrenade_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track17 - ($ + 1)) & 255)

; Pattern 12
	db 128	; State byte.
	db ((AHarmlessGrenade_Subsong0_Track20 - ($ + 2)) & #ff00) / 256	; New track (20) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track20 - ($ + 1)) & 255)

; Pattern 13
	db 130	; State byte.
	db 27	; New height.
	db ((AHarmlessGrenade_Subsong0_Track17 - ($ + 2)) & #ff00) / 256	; New track (17) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track17 - ($ + 1)) & 255)

; Pattern 14
	db 170	; State byte.
	db 3	; New height.
	db 128	; New track (22) for channel 1, as a reference (index 0).
	db 129	; New track (23) for channel 2, as a reference (index 1).
	db 128	; New track (22) for channel 3, as a reference (index 0).

; Pattern 15
	db 170	; State byte.
	db 31	; New height.
	db ((AHarmlessGrenade_Subsong0_Track18 - ($ + 2)) & #ff00) / 256	; New track (18) for channel 1, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track18 - ($ + 1)) & 255)
	db 130	; New track (19) for channel 2, as a reference (index 2).
	db 131	; New track (21) for channel 3, as a reference (index 3).

; Pattern 16
	db 0	; State byte.

; Pattern 17
	db 8	; State byte.
	db 140	; New track (24) for channel 1, as a reference (index 12).

; Pattern 18
	db 0	; State byte.

; Pattern 19
	db 70	; State byte.
	db 15	; New height.
	db 2	; New transposition on channel 1.
	db 2	; New transposition on channel 3.

; Pattern 20
	db 254	; State byte.
	db 3	; New height.
	db 0	; New transposition on channel 1.
	db 128	; New track (22) for channel 1, as a reference (index 0).
	db 2	; New transposition on channel 2.
	db 129	; New track (23) for channel 2, as a reference (index 1).
	db 0	; New transposition on channel 3.
	db 134	; New track (25) for channel 3, as a reference (index 6).

; Pattern 21
	db 80	; State byte.
	db 10	; New transposition on channel 2.
	db 4	; New transposition on channel 3.

; Pattern 22
	db 80	; State byte.
	db 20	; New transposition on channel 2.
	db 8	; New transposition on channel 3.

; Pattern 23
	db 80	; State byte.
	db 36	; New transposition on channel 2.
	db 14	; New transposition on channel 3.

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
AHarmlessGrenade_Subsong0DisarkByteRegionEnd2
AHarmlessGrenade_Subsong0DisarkPointerRegionStart3
	dw AHarmlessGrenade_Subsong0_Loop

AHarmlessGrenade_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
AHarmlessGrenade_Subsong0_TrackIndexes
AHarmlessGrenade_Subsong0DisarkPointerRegionStart4
	dw AHarmlessGrenade_Subsong0_Track22	; Track 22, index 0.
	dw AHarmlessGrenade_Subsong0_Track23	; Track 23, index 1.
	dw AHarmlessGrenade_Subsong0_Track19	; Track 19, index 2.
	dw AHarmlessGrenade_Subsong0_Track21	; Track 21, index 3.
	dw AHarmlessGrenade_Subsong0_Track0	; Track 0, index 4.
	dw AHarmlessGrenade_Subsong0_Track1	; Track 1, index 5.
	dw AHarmlessGrenade_Subsong0_Track25	; Track 25, index 6.
	dw AHarmlessGrenade_Subsong0_Track8	; Track 8, index 7.
	dw AHarmlessGrenade_Subsong0_Track6	; Track 6, index 8.
	dw AHarmlessGrenade_Subsong0_Track7	; Track 7, index 9.
	dw AHarmlessGrenade_Subsong0_Track15	; Track 15, index 10.
	dw AHarmlessGrenade_Subsong0_Track16	; Track 16, index 11.
	dw AHarmlessGrenade_Subsong0_Track24	; Track 24, index 12.
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd4

AHarmlessGrenade_Subsong0DisarkByteRegionStart5
AHarmlessGrenade_Subsong0_Track0
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 146	; Primary instrument (1). Note reference (2). Secondary wait (1).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 29. Primary wait (0).
	db 29	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 32. Primary wait (0).
	db 32	;   Escape note value.
	db 85	; Primary instrument (1). Note reference (5). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 29. Primary wait (0).
	db 29	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 218	; Primary instrument (1). Note reference (10). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track2
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (3). Note reference (0). Primary wait (0).
	db 3	;   Escape instrument value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 64	; Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 64	; Note reference (0). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (4). Note reference (0). Primary wait (0).
	db 4	;   Escape instrument value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 112	; New instrument (3). Note reference (0). Primary wait (0).
	db 3	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 64	; Note reference (0). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (5). Note reference (0). Primary wait (0).
	db 5	;   Escape instrument value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 112	; New instrument (3). Note reference (0). Primary wait (0).
	db 3	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 112	; New instrument (4). Note reference (0). Primary wait (0).
	db 4	;   Escape instrument value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (6). Note reference (0). Primary wait (0).
	db 6	;   Escape instrument value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 112	; New instrument (4). Note reference (0). Primary wait (0).
	db 4	;   Escape instrument value.
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 112	; New instrument (6). Note reference (0). Primary wait (0).
	db 6	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (3). Note reference (0). Primary wait (0).
	db 3	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 112	; New instrument (4). Note reference (0). Primary wait (0).
	db 4	;   Escape instrument value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 112	; New instrument (3). Note reference (0). Primary wait (0).
	db 3	;   Escape instrument value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (4). Note reference (0). Primary wait (0).
	db 4	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 112	; New instrument (5). Note reference (0). Primary wait (0).
	db 5	;   Escape instrument value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 112	; New instrument (4). Note reference (0). Primary wait (0).
	db 4	;   Escape instrument value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (3). Note reference (0). Primary wait (0).
	db 3	;   Escape instrument value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 112	; New instrument (5). Note reference (0). Primary wait (0).
	db 5	;   Escape instrument value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 64	; Note reference (0). Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 112	; New instrument (3). Note reference (0). Primary wait (0).
	db 3	;   Escape instrument value.
	db 66	;    Volume effect, with inverted volume: 4.
	db 12	; Note with effects flag.
	db 112	; New instrument (4). Note reference (0). Primary wait (0).
	db 4	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 240	; New instrument (6). Note reference (0). New wait (127).
	db 6	;   Escape instrument value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track3
	db 12	; Note with effects flag.
	db 254	; New instrument (7). New escaped note: 79. New wait (7).
	db 79	;   Escape note value.
	db 7	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 33	;    Reset effect, with inverted volume: 2.
	db 24	;    Pitch table effect 1.
	db 14	; New escaped note: 77. 
	db 77	;   Escape note value.
	db 14	; New escaped note: 72. 
	db 72	;   Escape note value.
	db 206	; New escaped note: 76. New wait (127).
	db 76	;   Escape note value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track4
	db 12	; Note with effects flag.
	db 224	; Secondary instrument (2). Note reference (0). New wait (3).
	db 3	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 254	; New instrument (7). New escaped note: 75. New wait (7).
	db 75	;   Escape note value.
	db 7	;   Escape instrument value.
	db 7	;   Escape wait value.
	db 35	;    Volume effect, with inverted volume: 2.
	db 24	;    Pitch table effect 1.
	db 14	; New escaped note: 71. 
	db 71	;   Escape note value.
	db 14	; New escaped note: 77. 
	db 77	;   Escape note value.
	db 206	; New escaped note: 79. New wait (127).
	db 79	;   Escape note value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track5
	db 242	; New instrument (8). Note reference (2). New wait (127).
	db 8	;   Escape instrument value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track6
	db 12	; Note with effects flag.
	db 69	; Note reference (5). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 69	; Note reference (5). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 69	; Note reference (5). Primary wait (0).
	db 93	; Effect only. Primary wait (0).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 241	; New instrument (0). Note reference (1). New wait (6).
	db 0	;   Escape instrument value.
	db 6	;   Escape wait value.
	db 114	; New instrument (10). Note reference (2). Primary wait (0).
	db 10	;   Escape instrument value.
	db 69	; Note reference (5). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 69	; Note reference (5). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 69	; Note reference (5). Primary wait (0).
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.

AHarmlessGrenade_Subsong0_Track7
	db 12	; Note with effects flag.
	db 114	; New instrument (12). Note reference (2). Primary wait (0).
	db 12	;   Escape instrument value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 66	; Note reference (2). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 66	; Note reference (2). Primary wait (0).
	db 93	; Effect only. Primary wait (0).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 241	; New instrument (0). Note reference (1). New wait (6).
	db 0	;   Escape instrument value.
	db 6	;   Escape wait value.
	db 114	; New instrument (12). Note reference (2). Primary wait (0).
	db 12	;   Escape instrument value.
	db 12	; Note with effects flag.
	db 66	; Note reference (2). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 66	; Note reference (2). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 66	; Note reference (2). Primary wait (0).
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.

AHarmlessGrenade_Subsong0_Track8
	db 12	; Note with effects flag.
	db 224	; Secondary instrument (2). Note reference (0). New wait (2).
	db 2	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 32	; Secondary instrument (2). Note reference (0). 
	db 160	; Secondary instrument (2). Note reference (0). Secondary wait (1).
	db 118	; New instrument (9). Note reference (6). Primary wait (0).
	db 9	;   Escape instrument value.
	db 12	; Note with effects flag.
	db 70	; Note reference (6). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 70	; Note reference (6). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 70	; Note reference (6). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 70	; Note reference (6). Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 12	; Note with effects flag.
	db 70	; Note reference (6). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 70	; Note reference (6). Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 32	; Secondary instrument (2). Note reference (0). 
	db 32	; Secondary instrument (2). Note reference (0). 
	db 224	; Secondary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track9
	db 143	; Same escaped note: 21. Secondary wait (1).
	db 202	; Note reference (10). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track10
	db 243	; New instrument (9). Note reference (3). New wait (3).
	db 9	;   Escape instrument value.
	db 3	;   Escape wait value.
	db 160	; Secondary instrument (2). Note reference (0). Secondary wait (1).
	db 67	; Note reference (3). Primary wait (0).
	db 224	; Secondary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track11
	db 191	; New instrument (12). Same escaped note: 21. Secondary wait (1).
	db 12	;   Escape instrument value.
	db 202	; Note reference (10). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track12
	db 142	; New escaped note: 19. Secondary wait (1).
	db 19	;   Escape note value.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 4096.
	db 0	;    Pitch, LSB.
	db 16	;    Pitch, MSB.
	db 206	; New escaped note: 16. New wait (127).
	db 16	;   Escape note value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track13
	db 12	; Note with effects flag.
	db 224	; Secondary instrument (2). Note reference (0). New wait (3).
	db 3	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 12	; Note with effects flag.
	db 115	; New instrument (4). Note reference (3). Primary wait (0).
	db 4	;   Escape instrument value.
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 115	; New instrument (6). Note reference (3). Primary wait (0).
	db 6	;   Escape instrument value.
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 243	; New instrument (3). Note reference (3). New wait (127).
	db 3	;   Escape instrument value.
	db 127	;   Escape wait value.
	db 34	;    Volume effect, with inverted volume: 2.

AHarmlessGrenade_Subsong0_Track14
	db 190	; New instrument (12). New escaped note: 19. Secondary wait (1).
	db 19	;   Escape note value.
	db 12	;   Escape instrument value.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 4096.
	db 0	;    Pitch, LSB.
	db 16	;    Pitch, MSB.
	db 206	; New escaped note: 16. New wait (127).
	db 16	;   Escape note value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track15
	db 254	; New instrument (14). New escaped note: 39. New wait (5).
	db 39	;   Escape note value.
	db 14	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 195	; Note reference (3). New wait (9).
	db 9	;   Escape wait value.
	db 247	; New instrument (8). Note reference (7). New wait (5).
	db 8	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 196	; Note reference (4). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track16
	db 224	; Secondary instrument (2). Note reference (0). New wait (2).
	db 2	;   Escape wait value.
	db 160	; Secondary instrument (2). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 243	; New instrument (9). Note reference (3). New wait (3).
	db 9	;   Escape instrument value.
	db 3	;   Escape wait value.
	db 224	; Secondary instrument (2). Note reference (0). New wait (2).
	db 2	;   Escape wait value.
	db 32	; Secondary instrument (2). Note reference (0). 
	db 32	; Secondary instrument (2). Note reference (0). 
	db 160	; Secondary instrument (2). Note reference (0). Secondary wait (1).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 195	; Note reference (3). New wait (3).
	db 3	;   Escape wait value.
	db 160	; Secondary instrument (2). Note reference (0). Secondary wait (1).
	db 67	; Note reference (3). Primary wait (0).
	db 160	; Secondary instrument (2). Note reference (0). Secondary wait (1).
	db 224	; Secondary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track17
	db 12	; Note with effects flag.
	db 177	; New instrument (13). Note reference (1). Secondary wait (1).
	db 13	;   Escape instrument value.
	db 64	;    Reset effect, with inverted volume: 4.
	db 136	; Note reference (8). Secondary wait (1).
	db 142	; New escaped note: 55. Secondary wait (1).
	db 55	;   Escape note value.
	db 139	; Note reference (11). Secondary wait (1).
	db 137	; Note reference (9). Secondary wait (1).
	db 12	; Note with effects flag.
	db 129	; Note reference (1). Secondary wait (1).
	db 50	;    Volume effect, with inverted volume: 3.
	db 129	; Note reference (1). Secondary wait (1).
	db 136	; Note reference (8). Secondary wait (1).
	db 142	; New escaped note: 54. Secondary wait (1).
	db 54	;   Escape note value.
	db 139	; Note reference (11). Secondary wait (1).
	db 12	; Note with effects flag.
	db 137	; Note reference (9). Secondary wait (1).
	db 34	;    Volume effect, with inverted volume: 2.
	db 129	; Note reference (1). Secondary wait (1).
	db 129	; Note reference (1). Secondary wait (1).
	db 136	; Note reference (8). Secondary wait (1).
	db 143	; Same escaped note: 54. Secondary wait (1).
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track18
	db 244	; New instrument (11). Note reference (4). New wait (5).
	db 11	;   Escape instrument value.
	db 5	;   Escape wait value.
	db 192	; Note reference (0). New wait (9).
	db 9	;   Escape wait value.
	db 206	; New escaped note: 18. New wait (5).
	db 18	;   Escape note value.
	db 5	;   Escape wait value.
	db 206	; New escaped note: 15. New wait (127).
	db 15	;   Escape note value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track19
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 113	; New instrument (16). Note reference (1). Primary wait (0).
	db 16	;   Escape instrument value.
	db 65	; Note reference (1). Primary wait (0).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 65	; Note reference (1). Primary wait (0).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 115	; New instrument (9). Note reference (3). Primary wait (0).
	db 9	;   Escape instrument value.
	db 113	; New instrument (16). Note reference (1). Primary wait (0).
	db 16	;   Escape instrument value.
	db 65	; Note reference (1). Primary wait (0).
	db 65	; Note reference (1). Primary wait (0).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 113	; New instrument (17). Note reference (1). Primary wait (0).
	db 17	;   Escape instrument value.
	db 65	; Note reference (1). Primary wait (0).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 65	; Note reference (1). Primary wait (0).
	db 65	; Note reference (1). Primary wait (0).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 65	; Note reference (1). Primary wait (0).
	db 113	; New instrument (18). Note reference (1). Primary wait (0).
	db 18	;   Escape instrument value.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 65	; Note reference (1). Primary wait (0).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 115	; New instrument (9). Note reference (3). Primary wait (0).
	db 9	;   Escape instrument value.
	db 113	; New instrument (18). Note reference (1). Primary wait (0).
	db 18	;   Escape instrument value.
	db 113	; New instrument (19). Note reference (1). Primary wait (0).
	db 19	;   Escape instrument value.
	db 65	; Note reference (1). Primary wait (0).
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 65	; Note reference (1). Primary wait (0).
	db 115	; New instrument (9). Note reference (3). Primary wait (0).
	db 9	;   Escape instrument value.
	db 96	; Secondary instrument (2). Note reference (0). Primary wait (0).
	db 113	; New instrument (19). Note reference (1). Primary wait (0).
	db 19	;   Escape instrument value.
	db 224	; Secondary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track20
	db 12	; Note with effects flag.
	db 177	; New instrument (15). Note reference (1). Secondary wait (1).
	db 15	;   Escape instrument value.
	db 32	;    Reset effect, with inverted volume: 2.
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 141	; Secondary wait (1).
	db 205	; New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track21
	db 12	; Note with effects flag.
	db 177	; New instrument (7). Note reference (1). Secondary wait (1).
	db 7	;   Escape instrument value.
	db 33	;    Reset effect, with inverted volume: 2.
	db 22	;    Arpeggio table effect 1.
	db 136	; Note reference (8). Secondary wait (1).
	db 142	; New escaped note: 55. Secondary wait (1).
	db 55	;   Escape note value.
	db 139	; Note reference (11). Secondary wait (1).
	db 137	; Note reference (9). Secondary wait (1).
	db 129	; Note reference (1). Secondary wait (1).
	db 129	; Note reference (1). Secondary wait (1).
	db 136	; Note reference (8). Secondary wait (1).
	db 142	; New escaped note: 54. Secondary wait (1).
	db 54	;   Escape note value.
	db 139	; Note reference (11). Secondary wait (1).
	db 137	; Note reference (9). Secondary wait (1).
	db 129	; Note reference (1). Secondary wait (1).
	db 129	; Note reference (1). Secondary wait (1).
	db 136	; Note reference (8). Secondary wait (1).
	db 143	; Same escaped note: 54. Secondary wait (1).
	db 201	; Note reference (9). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track22
	db 241	; New instrument (0). Note reference (1). New wait (127).
	db 0	;   Escape instrument value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track23
	db 12	; Note with effects flag.
	db 206	; New escaped note: 60. New wait (127).
	db 60	;   Escape note value.
	db 127	;   Escape wait value.
	db 244	;    Pitch down: 20480.
	db 0	;    Pitch, LSB.
	db 80	;    Pitch, MSB.

AHarmlessGrenade_Subsong0_Track24
	db 12	; Note with effects flag.
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 28. Primary wait (0).
	db 28	;   Escape note value.
	db 95	; Primary instrument (1). Same escaped note: 28. Primary wait (0).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 31. Primary wait (0).
	db 31	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 28. Primary wait (0).
	db 28	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 31. Primary wait (0).
	db 31	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 87	; Primary instrument (1). Note reference (7). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 32. Primary wait (0).
	db 32	;   Escape note value.
	db 94	; Primary instrument (1). New escaped note: 33. Primary wait (0).
	db 33	;   Escape note value.
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 84	; Primary instrument (1). Note reference (4). Primary wait (0).
	db 90	; Primary instrument (1). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (1). New escaped note: 25. Primary wait (0).
	db 25	;   Escape note value.
	db 80	; Primary instrument (1). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (1). Note reference (2). Primary wait (0).
	db 222	; Primary instrument (1). New escaped note: 22. New wait (127).
	db 22	;   Escape note value.
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0_Track25
	db 12	; Note with effects flag.
	db 254	; New instrument (12). New escaped note: 72. New wait (127).
	db 72	;   Escape note value.
	db 12	;   Escape instrument value.
	db 127	;   Escape wait value.
	db 81	;    Reset effect, with inverted volume: 5.
	db 245	;    Pitch down: 512.
	db 0	;    Pitch, LSB.
	db 2	;    Pitch, MSB.
	db 38	;    Arpeggio table effect 2.

AHarmlessGrenade_Subsong0DisarkByteRegionEnd5
; The note indexes.
AHarmlessGrenade_Subsong0_NoteIndexes
AHarmlessGrenade_Subsong0DisarkByteRegionStart6
	db 24	; Note for index 0.
	db 48	; Note for index 1.
	db 23	; Note for index 2.
	db 36	; Note for index 3.
	db 27	; Note for index 4.
	db 35	; Note for index 5.
	db 40	; Note for index 6.
	db 30	; Note for index 7.
	db 51	; Note for index 8.
	db 57	; Note for index 9.
	db 26	; Note for index 10.
	db 58	; Note for index 11.
AHarmlessGrenade_Subsong0DisarkByteRegionEnd6

