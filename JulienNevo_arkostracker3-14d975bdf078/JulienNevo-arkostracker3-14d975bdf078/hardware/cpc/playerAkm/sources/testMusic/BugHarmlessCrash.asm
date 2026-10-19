; A Harmless Grenade, Song part, encoded in the AKM (minimalist) format V0.


AHarmlessGrenade_Start
AHarmlessGrenade_StartDisarkGenerateExternalLabel

AHarmlessGrenade_DisarkPointerRegionStart0
	dw AHarmlessGrenade_InstrumentIndexes	; Index table for the Instruments.
AHarmlessGrenade_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Arpeggios.
AHarmlessGrenade_DisarkForceNonReferenceDuring2_2
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw AHarmlessGrenade_Subsong0
AHarmlessGrenade_DisarkPointerRegionEnd0

; The Instrument indexes.
AHarmlessGrenade_InstrumentIndexes
AHarmlessGrenade_DisarkPointerRegionStart3
	dw AHarmlessGrenade_Instrument0
	dw AHarmlessGrenade_Instrument1
	dw AHarmlessGrenade_Instrument2
	dw AHarmlessGrenade_Instrument3
	dw AHarmlessGrenade_Instrument4
AHarmlessGrenade_DisarkPointerRegionEnd3

; The Instrument.
AHarmlessGrenade_DisarkByteRegionStart4
AHarmlessGrenade_Instrument0
	db 255	; Speed.

AHarmlessGrenade_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart5
	dw AHarmlessGrenade_Instrument0Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd5

AHarmlessGrenade_Instrument1
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
AHarmlessGrenade_DisarkPointerRegionStart6
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd6

AHarmlessGrenade_Instrument2
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
AHarmlessGrenade_DisarkPointerRegionStart7
	dw AHarmlessGrenade_Instrument0Loop	; Loop to silence.
AHarmlessGrenade_DisarkPointerRegionEnd7

AHarmlessGrenade_Instrument3
	db 4	; Speed.

AHarmlessGrenade_Instrument3Loop	db 82
	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart8
	dw AHarmlessGrenade_Instrument3Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd8

AHarmlessGrenade_Instrument4
	db 0	; Speed.

AHarmlessGrenade_Instrument4Loop	db 61	; Volume: 15.

	db 4	; End the instrument.
AHarmlessGrenade_DisarkPointerRegionStart9
	dw AHarmlessGrenade_Instrument4Loop	; Loops.
AHarmlessGrenade_DisarkPointerRegionEnd9

AHarmlessGrenade_DisarkByteRegionEnd4
AHarmlessGrenade_ArpeggioIndexes
AHarmlessGrenade_DisarkPointerRegionStart10
AHarmlessGrenade_DisarkPointerRegionEnd10

AHarmlessGrenade_DisarkByteRegionStart11
AHarmlessGrenade_DisarkByteRegionEnd11

AHarmlessGrenade_PitchIndexes
AHarmlessGrenade_DisarkPointerRegionStart12
AHarmlessGrenade_DisarkPointerRegionEnd12

AHarmlessGrenade_DisarkByteRegionStart13
AHarmlessGrenade_DisarkByteRegionEnd13

; A Harmless Grenade, Subsong 0.
; ----------------------------------

AHarmlessGrenade_Subsong0
AHarmlessGrenade_Subsong0DisarkPointerRegionStart0
	dw AHarmlessGrenade_Subsong0_NoteIndexes	; Index table for the notes.
	dw AHarmlessGrenade_Subsong0_TrackIndexes	; Index table for the Tracks.
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd0

AHarmlessGrenade_Subsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 3	; Most used instrument.
	db 4	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 0	; Default start note in tracks.
	db 1	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
AHarmlessGrenade_Subsong0DisarkByteRegionEnd1

; The Linker.
AHarmlessGrenade_Subsong0DisarkByteRegionStart2
; Pattern 0
AHarmlessGrenade_Subsong0_Loop
	db 170	; State byte.
	db 23	; New height.
	db ((AHarmlessGrenade_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track0 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 2, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track2 - ($ + 1)) & 255)
	db ((AHarmlessGrenade_Subsong0_Track1 - ($ + 2)) & #ff00) / 256	; New track (1) for channel 3, as an offset. Offset MSB, then LSB.
	db ((AHarmlessGrenade_Subsong0_Track1 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
AHarmlessGrenade_Subsong0DisarkByteRegionEnd2
AHarmlessGrenade_Subsong0DisarkPointerRegionStart3
	dw AHarmlessGrenade_Subsong0_Loop

AHarmlessGrenade_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
AHarmlessGrenade_Subsong0_TrackIndexes
AHarmlessGrenade_Subsong0DisarkPointerRegionStart4
AHarmlessGrenade_Subsong0DisarkPointerRegionEnd4

AHarmlessGrenade_Subsong0DisarkByteRegionStart5
AHarmlessGrenade_Subsong0_Track0
	db 12	; Note with effects flag.
	db 83	; Primary instrument (3). Note reference (3). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 83	; Primary instrument (3). Note reference (3). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 83	; Primary instrument (3). Note reference (3). Primary wait (0).
	db 93	; Effect only. Primary wait (0).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 254	; New instrument (0). New escaped note: 48. New wait (6).
	db 48	;   Escape note value.
	db 0	;   Escape instrument value.
	db 6	;   Escape wait value.
	db 80	; Primary instrument (3). Note reference (0). Primary wait (0).
	db 83	; Primary instrument (3). Note reference (3). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 83	; Primary instrument (3). Note reference (3). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 83	; Primary instrument (3). Note reference (3). Primary wait (0).
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.

AHarmlessGrenade_Subsong0_Track1
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (4). Note reference (0). Primary wait (0).
	db 0	;    Reset effect, with inverted volume: 0.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 96	; Secondary instrument (4). Note reference (0). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 96	; Secondary instrument (4). Note reference (0). Primary wait (0).
	db 93	; Effect only. Primary wait (0).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 254	; New instrument (0). New escaped note: 48. New wait (6).
	db 48	;   Escape note value.
	db 0	;   Escape instrument value.
	db 6	;   Escape wait value.
	db 96	; Secondary instrument (4). Note reference (0). Primary wait (0).
	db 12	; Note with effects flag.
	db 96	; Secondary instrument (4). Note reference (0). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 96	; Secondary instrument (4). Note reference (0). Primary wait (0).
	db 157	; Effect only. Secondary wait (1).
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.
	db 96	; Secondary instrument (4). Note reference (0). Primary wait (0).
	db 221	; Effect only. New wait (127).
	db 127	;   Escape wait value.
	db 244	;    Pitch down: 8192.
	db 0	;    Pitch, LSB.
	db 32	;    Pitch, MSB.

AHarmlessGrenade_Subsong0_Track2
	db 12	; Note with effects flag.
	db 194	; Note reference (2). New wait (2).
	db 2	;   Escape wait value.
	db 0	;    Reset effect, with inverted volume: 0.
	db 2	; Note reference (2). 
	db 130	; Note reference (2). Secondary wait (1).
	db 113	; New instrument (2). Note reference (1). Primary wait (0).
	db 2	;   Escape instrument value.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 50	;    Volume effect, with inverted volume: 3.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 66	;    Volume effect, with inverted volume: 4.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 82	;    Volume effect, with inverted volume: 5.
	db 12	; Note with effects flag.
	db 65	; Note reference (1). Primary wait (0).
	db 98	;    Volume effect, with inverted volume: 6.
	db 12	; Note with effects flag.
	db 114	; New instrument (1). Note reference (2). Primary wait (0).
	db 1	;   Escape instrument value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 2	; Note reference (2). 
	db 2	; Note reference (2). 
	db 194	; Note reference (2). New wait (127).
	db 127	;   Escape wait value.

AHarmlessGrenade_Subsong0DisarkByteRegionEnd5
; The note indexes.
AHarmlessGrenade_Subsong0_NoteIndexes
AHarmlessGrenade_Subsong0DisarkByteRegionStart6
	db 23	; Note for index 0.
	db 40	; Note for index 1.
	db 24	; Note for index 2.
	db 35	; Note for index 3.
AHarmlessGrenade_Subsong0DisarkByteRegionEnd6

