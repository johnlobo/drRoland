; Fever (Country-esuqe Remix), Song part, encoded in the AKM (minimalist) format V0.


feverRemix_Start
feverRemix_StartDisarkGenerateExternalLabel

feverRemix_DisarkPointerRegionStart0
	dw feverRemix_InstrumentIndexes	; Index table for the Instruments.
feverRemix_DisarkForceNonReferenceDuring2_1
	dw 0	; Index table for the Arpeggios.
feverRemix_DisarkForceNonReferenceDuring2_2
	dw 0	; Index table for the Pitches.

; The subsongs references.
	dw feverRemix_Subsong0
	dw feverRemix_Subsong1
	dw feverRemix_Subsong2
feverRemix_DisarkPointerRegionEnd0

; The Instrument indexes.
feverRemix_InstrumentIndexes
feverRemix_DisarkPointerRegionStart3
	dw feverRemix_Instrument0
	dw feverRemix_Instrument1
	dw feverRemix_Instrument2
	dw feverRemix_Instrument3
	dw feverRemix_Instrument4
	dw feverRemix_Instrument5
	dw feverRemix_Instrument6
	dw feverRemix_Instrument7
feverRemix_DisarkPointerRegionEnd3

; The Instrument.
feverRemix_DisarkByteRegionStart4
feverRemix_Instrument0
	db 255	; Speed.

feverRemix_Instrument0Loop	db 0	; Volume: 0.

	db 4	; End the instrument.
feverRemix_DisarkPointerRegionStart5
	dw feverRemix_Instrument0Loop	; Loops.
feverRemix_DisarkPointerRegionEnd5

feverRemix_Instrument1
	db 4	; Speed.

	db 61	; Volume: 15.

	db 57	; Volume: 14.

	db 53	; Volume: 13.

	db 49	; Volume: 12.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

	db 45	; Volume: 11.

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
feverRemix_DisarkPointerRegionStart6
	dw feverRemix_Instrument0Loop	; Loop to silence.
feverRemix_DisarkPointerRegionEnd6

feverRemix_Instrument2
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
feverRemix_DisarkPointerRegionStart7
	dw feverRemix_Instrument0Loop	; Loop to silence.
feverRemix_DisarkPointerRegionEnd7

feverRemix_Instrument3
	db 0	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 232	; Volume: 13.
	db 1	; Noise.

	db 216	; Volume: 11.
	db 1	; Noise.

	db 192	; Volume: 8.
	db 1	; Noise.

	db 168	; Volume: 5.
	db 1	; Noise.

	db 4	; End the instrument.
feverRemix_DisarkPointerRegionStart8
	dw feverRemix_Instrument0Loop	; Loop to silence.
feverRemix_DisarkPointerRegionEnd8

feverRemix_Instrument4
	db 0	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 249	; Volume: 14.
	db 1	; Arpeggio: 0.
	db 2	; Noise: 2.
	dw -10	; Pitch: -10.

	db 241	; Volume: 12.
	db 1	; Arpeggio: 0.
	db 3	; Noise: 3.
	dw -30	; Pitch: -30.

	db 216	; Volume: 11.
	db 1	; Noise.

	db 80	; Volume: 10.

	db 208	; Volume: 10.
	db 1	; Noise.

	db 200	; Volume: 9.
	db 1	; Noise.

	db 192	; Volume: 8.
	db 1	; Noise.

	db 184	; Volume: 7.
	db 1	; Noise.

	db 176	; Volume: 6.
	db 1	; Noise.

	db 168	; Volume: 5.
	db 1	; Noise.

	db 160	; Volume: 4.
	db 1	; Noise.

	db 144	; Volume: 2.
	db 1	; Noise.

	db 136	; Volume: 1.
	db 1	; Noise.

	db 4	; End the instrument.
feverRemix_DisarkPointerRegionStart9
	dw feverRemix_Instrument0Loop	; Loop to silence.
feverRemix_DisarkPointerRegionEnd9

feverRemix_Instrument5
	db 0	; Speed.

	db 248	; Volume: 15.
	db 1	; Noise.

	db 121	; Volume: 14.
	dw 150	; Pitch: 150.

	db 117	; Volume: 13.
	dw 300	; Pitch: 300.

	db 113	; Volume: 12.
	dw 400	; Pitch: 400.

	db 109	; Volume: 11.
	dw 500	; Pitch: 500.

	db 105	; Volume: 10.
	dw 600	; Pitch: 600.

	db 4	; End the instrument.
feverRemix_DisarkPointerRegionStart10
	dw feverRemix_Instrument0Loop	; Loop to silence.
feverRemix_DisarkPointerRegionEnd10

feverRemix_Instrument6
	db 0	; Speed.

	db 61	; Volume: 15.

	db 189	; Volume: 15.
	db 14	; Arpeggio: 7.

	db 185	; Volume: 14.
	db 24	; Arpeggio: 12.

	db 57	; Volume: 14.

	db 181	; Volume: 13.
	db 14	; Arpeggio: 7.

	db 177	; Volume: 12.
	db 24	; Arpeggio: 12.

	db 45	; Volume: 11.

	db 173	; Volume: 11.
	db 14	; Arpeggio: 7.

	db 169	; Volume: 10.
	db 24	; Arpeggio: 12.

	db 41	; Volume: 10.

	db 165	; Volume: 9.
	db 14	; Arpeggio: 7.

	db 165	; Volume: 9.
	db 24	; Arpeggio: 12.

	db 33	; Volume: 8.

	db 161	; Volume: 8.
	db 14	; Arpeggio: 7.

	db 157	; Volume: 7.
	db 24	; Arpeggio: 12.

	db 29	; Volume: 7.

	db 153	; Volume: 6.
	db 14	; Arpeggio: 7.

	db 153	; Volume: 6.
	db 24	; Arpeggio: 12.

	db 21	; Volume: 5.

	db 149	; Volume: 5.
	db 14	; Arpeggio: 7.

	db 145	; Volume: 4.
	db 24	; Arpeggio: 12.

	db 17	; Volume: 4.

	db 141	; Volume: 3.
	db 14	; Arpeggio: 7.

	db 141	; Volume: 3.
	db 24	; Arpeggio: 12.

	db 9	; Volume: 2.

	db 137	; Volume: 2.
	db 14	; Arpeggio: 7.

	db 133	; Volume: 1.
	db 24	; Arpeggio: 12.

	db 5	; Volume: 1.

	db 4	; End the instrument.
feverRemix_DisarkPointerRegionStart11
	dw feverRemix_Instrument0Loop	; Loop to silence.
feverRemix_DisarkPointerRegionEnd11

feverRemix_Instrument7
	db 0	; Speed.

	db 61	; Volume: 15.

	db 61	; Volume: 15.

	db 185	; Volume: 14.
	db 232	; Arpeggio: -12.

	db 57	; Volume: 14.

	db 181	; Volume: 13.
	db 232	; Arpeggio: -12.

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

	db 4	; End the instrument.
feverRemix_DisarkPointerRegionStart12
	dw feverRemix_Instrument0Loop	; Loop to silence.
feverRemix_DisarkPointerRegionEnd12

feverRemix_DisarkByteRegionEnd4
feverRemix_ArpeggioIndexes
feverRemix_DisarkPointerRegionStart13
feverRemix_DisarkPointerRegionEnd13

feverRemix_DisarkByteRegionStart14
feverRemix_DisarkByteRegionEnd14

feverRemix_PitchIndexes
feverRemix_DisarkPointerRegionStart15
feverRemix_DisarkPointerRegionEnd15

feverRemix_DisarkByteRegionStart16
feverRemix_DisarkByteRegionEnd16

; Fever (Country-esuqe Remix), Subsong 0.
; ----------------------------------

feverRemix_Subsong0
feverRemix_Subsong0DisarkPointerRegionStart0
	dw feverRemix_Subsong0_NoteIndexes	; Index table for the notes.
	dw feverRemix_Subsong0_TrackIndexes	; Index table for the Tracks.
feverRemix_Subsong0DisarkPointerRegionEnd0

feverRemix_Subsong0DisarkByteRegionStart1
	db 6	; Initial speed.

	db 2	; Most used instrument.
	db 4	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 0	; Default start note in tracks.
	db 1	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
feverRemix_Subsong0DisarkByteRegionEnd1

; The Linker.
feverRemix_Subsong0DisarkByteRegionStart2
; Pattern 0
feverRemix_Subsong0_Loop
	db 171	; State byte.
	db 7	; New speed (>0).
	db 63	; New height.
	db ((feverRemix_Subsong0_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track0 - ($ + 1)) & 255)
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 1
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track2 - ($ + 2)) & #ff00) / 256	; New track (2) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track2 - ($ + 1)) & 255)

; Pattern 2
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track3 - ($ + 1)) & 255)

; Pattern 3
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track4 - ($ + 1)) & 255)

; Pattern 4
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track5 - ($ + 1)) & 255)

; Pattern 5
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track6 - ($ + 2)) & #ff00) / 256	; New track (6) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track6 - ($ + 1)) & 255)

; Pattern 6
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track7 - ($ + 2)) & #ff00) / 256	; New track (7) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track7 - ($ + 1)) & 255)

; Pattern 7
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track8 - ($ + 2)) & #ff00) / 256	; New track (8) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track8 - ($ + 1)) & 255)

; Pattern 8
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track9 - ($ + 2)) & #ff00) / 256	; New track (9) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track9 - ($ + 1)) & 255)

; Pattern 9
	db 0	; State byte.

; Pattern 10
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track10 - ($ + 2)) & #ff00) / 256	; New track (10) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track10 - ($ + 1)) & 255)

; Pattern 11
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track11 - ($ + 2)) & #ff00) / 256	; New track (11) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track11 - ($ + 1)) & 255)

; Pattern 12
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track12 - ($ + 2)) & #ff00) / 256	; New track (12) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track12 - ($ + 1)) & 255)

; Pattern 13
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track3 - ($ + 2)) & #ff00) / 256	; New track (3) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track3 - ($ + 1)) & 255)

; Pattern 14
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track4 - ($ + 2)) & #ff00) / 256	; New track (4) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track4 - ($ + 1)) & 255)

; Pattern 15
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track5 - ($ + 2)) & #ff00) / 256	; New track (5) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track5 - ($ + 1)) & 255)

; Pattern 16
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track13 - ($ + 2)) & #ff00) / 256	; New track (13) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track13 - ($ + 1)) & 255)

; Pattern 17
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track14 - ($ + 2)) & #ff00) / 256	; New track (14) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track14 - ($ + 1)) & 255)

; Pattern 18
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track15 - ($ + 2)) & #ff00) / 256	; New track (15) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track15 - ($ + 1)) & 255)

; Pattern 19
	db 8	; State byte.
	db ((feverRemix_Subsong0_Track16 - ($ + 2)) & #ff00) / 256	; New track (16) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong0_Track16 - ($ + 1)) & 255)

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
feverRemix_Subsong0DisarkByteRegionEnd2
feverRemix_Subsong0DisarkPointerRegionStart3
	dw feverRemix_Subsong0_Loop

feverRemix_Subsong0DisarkPointerRegionEnd3
; The indexes of the tracks.
feverRemix_Subsong0_TrackIndexes
feverRemix_Subsong0DisarkPointerRegionStart4
	dw feverRemix_Subsong0_Track1	; Track 1, index 0.
feverRemix_Subsong0DisarkPointerRegionEnd4

feverRemix_Subsong0DisarkByteRegionStart5
feverRemix_Subsong0_Track0
	db 12	; Note with effects flag.
	db 139	; Note reference (11). Secondary wait (1).
	db 2	;    Volume effect, with inverted volume: 0.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 46. Secondary wait (1).
	db 46	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 47. Secondary wait (1).
	db 47	;   Escape note value.
	db 147	; Primary instrument (2). Note reference (3). Secondary wait (1).
	db 159	; Primary instrument (2). Same escaped note: 47. Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 46. Secondary wait (1).
	db 46	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 46. Secondary wait (1).
	db 46	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 47. Secondary wait (1).
	db 47	;   Escape note value.
	db 147	; Primary instrument (2). Note reference (3). Secondary wait (1).
	db 159	; Primary instrument (2). Same escaped note: 47. Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 46. Secondary wait (1).
	db 46	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 35. Secondary wait (1).
	db 35	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 47. Secondary wait (1).
	db 47	;   Escape note value.
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 159	; Primary instrument (2). Same escaped note: 47. Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 37. Secondary wait (1).
	db 37	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 38. Secondary wait (1).
	db 38	;   Escape note value.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 35. Secondary wait (1).
	db 35	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 47. Secondary wait (1).
	db 47	;   Escape note value.
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 159	; Primary instrument (2). Same escaped note: 47. Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 37. Secondary wait (1).
	db 37	;   Escape note value.
	db 222	; Primary instrument (2). New escaped note: 38. New wait (127).
	db 38	;   Escape note value.
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track2
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 37. Primary wait (0).
	db 37	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 214	; Primary instrument (2). Note reference (6). New wait (3).
	db 3	;   Escape wait value.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 39. Primary wait (0).
	db 39	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 37. Primary wait (0).
	db 37	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 45. Primary wait (0).
	db 159	; Primary instrument (2). Same escaped note: 45. Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 46. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 46. Primary wait (0).
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 47. Primary wait (0).
	db 47	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 47. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 47. Primary wait (0).
	db 227	; Secondary instrument (4). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track3
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 37. Primary wait (0).
	db 37	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 214	; Primary instrument (2). Note reference (6). New wait (3).
	db 3	;   Escape wait value.
	db 35	; Secondary instrument (4). Note reference (3). 
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 55. Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 37. Primary wait (0).
	db 37	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 74. Primary wait (0).
	db 74	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 72. Primary wait (0).
	db 72	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 66. Secondary wait (1).
	db 66	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 70. Primary wait (0).
	db 70	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 63. Primary wait (0).
	db 63	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 58. Primary wait (0).
	db 58	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 58. Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 222	; Primary instrument (2). New escaped note: 52. New wait (127).
	db 52	;   Escape note value.
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track4
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 72. Primary wait (0).
	db 72	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 42. Primary wait (0).
	db 42	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 72. Primary wait (0).
	db 72	;   Escape note value.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 53. Primary wait (0).
	db 53	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 42. Primary wait (0).
	db 42	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 72. Primary wait (0).
	db 72	;   Escape note value.
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 72. Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 210	; Primary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track5
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 222	; Primary instrument (2). New escaped note: 41. New wait (3).
	db 41	;   Escape note value.
	db 3	;   Escape wait value.
	db 30	; Primary instrument (2). New escaped note: 52. 
	db 52	;   Escape note value.
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 30	; Primary instrument (2). New escaped note: 41. 
	db 41	;   Escape note value.
	db 30	; Primary instrument (2). New escaped note: 53. 
	db 53	;   Escape note value.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 39. Primary wait (0).
	db 39	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 71. Primary wait (0).
	db 71	;   Escape note value.
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 33. Primary wait (0).
	db 33	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 210	; Primary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track6
	db 83	; Primary instrument (2). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 144	; Primary instrument (2). Note reference (0). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 47. Primary wait (0).
	db 47	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 44. Secondary wait (1).
	db 44	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 51. Primary wait (0).
	db 51	;   Escape note value.
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 47. Secondary wait (1).
	db 47	;   Escape note value.
	db 83	; Primary instrument (2). Note reference (3). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 52. Secondary wait (1).
	db 52	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 53. Primary wait (0).
	db 53	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 147	; Primary instrument (2). Note reference (3). Secondary wait (1).
	db 149	; Primary instrument (2). Note reference (5). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 52. Primary wait (0).
	db 52	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 158	; Primary instrument (2). New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 49. Secondary wait (1).
	db 49	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 50. Primary wait (0).
	db 50	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 56. Primary wait (0).
	db 56	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 50. Secondary wait (1).
	db 50	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 52. Primary wait (0).
	db 52	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 158	; Primary instrument (2). New escaped note: 53. Secondary wait (1).
	db 53	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 54. Secondary wait (1).
	db 54	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 47. Primary wait (0).
	db 47	;   Escape note value.
	db 210	; Primary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track7
	db 83	; Primary instrument (2). Note reference (3). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 144	; Primary instrument (2). Note reference (0). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 47. Primary wait (0).
	db 47	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 44. Secondary wait (1).
	db 44	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 51. Primary wait (0).
	db 51	;   Escape note value.
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 47. Secondary wait (1).
	db 47	;   Escape note value.
	db 83	; Primary instrument (2). Note reference (3). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 52. Secondary wait (1).
	db 52	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 53. Primary wait (0).
	db 53	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 147	; Primary instrument (2). Note reference (3). Secondary wait (1).
	db 149	; Primary instrument (2). Note reference (5). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 52. Primary wait (0).
	db 52	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 158	; Primary instrument (2). New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 49. Secondary wait (1).
	db 49	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 50. Primary wait (0).
	db 50	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 56. Primary wait (0).
	db 56	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 50. Secondary wait (1).
	db 50	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 52. Primary wait (0).
	db 52	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 53. Primary wait (0).
	db 53	;   Escape note value.
	db 12	; Note with effects flag.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 47. Primary wait (0).
	db 47	;   Escape note value.
	db 210	; Primary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track8
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 222	; Primary instrument (2). New escaped note: 41. New wait (3).
	db 41	;   Escape note value.
	db 3	;   Escape wait value.
	db 30	; Primary instrument (2). New escaped note: 29. 
	db 29	;   Escape note value.
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 30	; Primary instrument (2). New escaped note: 41. 
	db 41	;   Escape note value.
	db 30	; Primary instrument (2). New escaped note: 30. 
	db 30	;   Escape note value.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 39. Primary wait (0).
	db 39	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 77. Primary wait (0).
	db 77	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 71. Primary wait (0).
	db 71	;   Escape note value.
	db 208	; Primary instrument (2). Note reference (0). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track9
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 41. Secondary wait (1).
	db 41	;   Escape note value.
	db 159	; Primary instrument (2). Same escaped note: 41. Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 42. Primary wait (0).
	db 42	;   Escape note value.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 41. Secondary wait (1).
	db 41	;   Escape note value.
	db 159	; Primary instrument (2). Same escaped note: 41. Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 42. Primary wait (0).
	db 42	;   Escape note value.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 41. Secondary wait (1).
	db 41	;   Escape note value.
	db 159	; Primary instrument (2). Same escaped note: 41. Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 42. Primary wait (0).
	db 42	;   Escape note value.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 51. Secondary wait (1).
	db 51	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 50. Secondary wait (1).
	db 50	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 49. Secondary wait (1).
	db 49	;   Escape note value.
	db 147	; Primary instrument (2). Note reference (3). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 47. Secondary wait (1).
	db 47	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 46. Secondary wait (1).
	db 46	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 44. Primary wait (0).
	db 44	;   Escape note value.
	db 227	; Secondary instrument (4). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track10
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 222	; Primary instrument (2). New escaped note: 42. New wait (13).
	db 42	;   Escape note value.
	db 13	;   Escape wait value.
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 31	; Primary instrument (2). Same escaped note: 42. 
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 223	; Primary instrument (2). Same escaped note: 42. New wait (11).
	db 11	;   Escape wait value.
	db 12	; Note with effects flag.
	db 115	; New instrument (3). Note reference (3). Primary wait (0).
	db 3	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 222	; Primary instrument (2). New escaped note: 44. New wait (127).
	db 44	;   Escape note value.
	db 127	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.

feverRemix_Subsong0_Track11
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 146	; Primary instrument (2). Note reference (2). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 71. Secondary wait (1).
	db 71	;   Escape note value.
	db 145	; Primary instrument (2). Note reference (1). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 29. Secondary wait (1).
	db 29	;   Escape note value.
	db 148	; Primary instrument (2). Note reference (4). Secondary wait (1).
	db 149	; Primary instrument (2). Note reference (5). Secondary wait (1).
	db 154	; Primary instrument (2). Note reference (10). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 28. Primary wait (0).
	db 28	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 76. Primary wait (0).
	db 76	;   Escape note value.
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 76. Primary wait (0).
	db 158	; Primary instrument (2). New escaped note: 71. Secondary wait (1).
	db 71	;   Escape note value.
	db 145	; Primary instrument (2). Note reference (1). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 27. Secondary wait (1).
	db 27	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 58. Primary wait (0).
	db 58	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 82. Primary wait (0).
	db 82	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 70. Secondary wait (1).
	db 70	;   Escape note value.
	db 145	; Primary instrument (2). Note reference (1). Secondary wait (1).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 148	; Primary instrument (2). Note reference (4). Secondary wait (1).
	db 145	; Primary instrument (2). Note reference (1). Secondary wait (1).
	db 144	; Primary instrument (2). Note reference (0). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 35. Secondary wait (1).
	db 35	;   Escape note value.
	db 152	; Primary instrument (2). Note reference (8). Secondary wait (1).
	db 145	; Primary instrument (2). Note reference (1). Secondary wait (1).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 51. Primary wait (0).
	db 51	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 34. Primary wait (0).
	db 34	;   Escape note value.
	db 12	; Note with effects flag.
	db 115	; New instrument (3). Note reference (3). Primary wait (0).
	db 3	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 67	; Note reference (3). Primary wait (0).
	db 67	; Note reference (3). Primary wait (0).
	db 67	; Note reference (3). Primary wait (0).
	db 67	; Note reference (3). Primary wait (0).
	db 67	; Note reference (3). Primary wait (0).
	db 67	; Note reference (3). Primary wait (0).
	db 12	; Note with effects flag.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 12	; Note with effects flag.
	db 195	; Note reference (3). New wait (127).
	db 127	;   Escape wait value.
	db 34	;    Volume effect, with inverted volume: 2.

feverRemix_Subsong0_Track12
	db 12	; Note with effects flag.
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 37. Primary wait (0).
	db 37	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 214	; Primary instrument (2). Note reference (6). New wait (3).
	db 3	;   Escape wait value.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 39. Primary wait (0).
	db 39	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 37. Primary wait (0).
	db 37	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 151	; Primary instrument (2). Note reference (7). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 45. Primary wait (0).
	db 45	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 45. Primary wait (0).
	db 159	; Primary instrument (2). Same escaped note: 45. Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 46. Primary wait (0).
	db 46	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 46. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 46. Primary wait (0).
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 47. Primary wait (0).
	db 47	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 47. Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 47. Primary wait (0).
	db 227	; Secondary instrument (4). Note reference (3). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track13
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 144	; Primary instrument (2). Note reference (0). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 28. Secondary wait (1).
	db 28	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 32. Secondary wait (1).
	db 32	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 33. Primary wait (0).
	db 33	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 51. Primary wait (0).
	db 51	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 28. Secondary wait (1).
	db 28	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 33. Primary wait (0).
	db 33	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 35. Secondary wait (1).
	db 35	;   Escape note value.
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 149	; Primary instrument (2). Note reference (5). Secondary wait (1).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 158	; Primary instrument (2). New escaped note: 33. Secondary wait (1).
	db 33	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 37. Secondary wait (1).
	db 37	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 56. Primary wait (0).
	db 56	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 38. Secondary wait (1).
	db 38	;   Escape note value.
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 158	; Primary instrument (2). New escaped note: 41. Secondary wait (1).
	db 41	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 42. Secondary wait (1).
	db 42	;   Escape note value.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 210	; Primary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track14
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 144	; Primary instrument (2). Note reference (0). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 54. Primary wait (0).
	db 54	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 28. Secondary wait (1).
	db 28	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 32. Secondary wait (1).
	db 32	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 33. Primary wait (0).
	db 33	;   Escape note value.
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 51. Primary wait (0).
	db 51	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 28. Secondary wait (1).
	db 28	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 33. Primary wait (0).
	db 33	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 57. Primary wait (0).
	db 57	;   Escape note value.
	db 155	; Primary instrument (2). Note reference (11). Secondary wait (1).
	db 158	; Primary instrument (2). New escaped note: 35. Secondary wait (1).
	db 35	;   Escape note value.
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 55. Primary wait (0).
	db 55	;   Escape note value.
	db 153	; Primary instrument (2). Note reference (9). Secondary wait (1).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 150	; Primary instrument (2). Note reference (6). Secondary wait (1).
	db 149	; Primary instrument (2). Note reference (5). Secondary wait (1).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 88	; Primary instrument (2). Note reference (8). Primary wait (0).
	db 158	; Primary instrument (2). New escaped note: 33. Secondary wait (1).
	db 33	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 37. Secondary wait (1).
	db 37	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 56. Primary wait (0).
	db 56	;   Escape note value.
	db 158	; Primary instrument (2). New escaped note: 38. Secondary wait (1).
	db 38	;   Escape note value.
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 12	; Note with effects flag.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 94	; Primary instrument (2). New escaped note: 42. Primary wait (0).
	db 42	;   Escape note value.
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 99	; Secondary instrument (4). Note reference (3). Primary wait (0).
	db 18	;    Volume effect, with inverted volume: 1.
	db 12	; Note with effects flag.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 210	; Primary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track15
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 222	; Primary instrument (2). New escaped note: 41. New wait (3).
	db 41	;   Escape note value.
	db 3	;   Escape wait value.
	db 30	; Primary instrument (2). New escaped note: 29. 
	db 29	;   Escape note value.
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 30	; Primary instrument (2). New escaped note: 41. 
	db 41	;   Escape note value.
	db 30	; Primary instrument (2). New escaped note: 30. 
	db 30	;   Escape note value.
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 41. Primary wait (0).
	db 41	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 39. Primary wait (0).
	db 39	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 38. Primary wait (0).
	db 38	;   Escape note value.
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 66. Primary wait (0).
	db 66	;   Escape note value.
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 82	; Primary instrument (2). Note reference (2). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 71. Primary wait (0).
	db 71	;   Escape note value.
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 68. Primary wait (0).
	db 68	;   Escape note value.
	db 94	; Primary instrument (2). New escaped note: 33. Primary wait (0).
	db 33	;   Escape note value.
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 35. Primary wait (0).
	db 35	;   Escape note value.
	db 210	; Primary instrument (2). Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong0_Track16
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 222	; Primary instrument (2). New escaped note: 41. New wait (3).
	db 41	;   Escape note value.
	db 3	;   Escape wait value.
	db 51	; New instrument (5). Note reference (3). 
	db 5	;   Escape instrument value.
	db 86	; Primary instrument (2). Note reference (6). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 89	; Primary instrument (2). Note reference (9). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 31	; Primary instrument (2). Same escaped note: 41. 
	db 3	; Note reference (3). 
	db 87	; Primary instrument (2). Note reference (7). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 41. Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 84	; Primary instrument (2). Note reference (4). Primary wait (0).
	db 90	; Primary instrument (2). Note reference (10). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 80	; Primary instrument (2). Note reference (0). Primary wait (0).
	db 81	; Primary instrument (2). Note reference (1). Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 94	; Primary instrument (2). New escaped note: 72. Primary wait (0).
	db 72	;   Escape note value.
	db 95	; Primary instrument (2). Same escaped note: 72. Primary wait (0).
	db 85	; Primary instrument (2). Note reference (5). Primary wait (0).
	db 95	; Primary instrument (2). Same escaped note: 72. Primary wait (0).
	db 222	; Primary instrument (2). New escaped note: 74. New wait (2).
	db 74	;   Escape note value.
	db 2	;   Escape wait value.
	db 94	; Primary instrument (2). New escaped note: 72. Primary wait (0).
	db 72	;   Escape note value.
	db 12	; Note with effects flag.
	db 115	; New instrument (3). Note reference (3). Primary wait (0).
	db 3	;   Escape instrument value.
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 91	; Primary instrument (2). Note reference (11). Primary wait (0).
	db 2	;    Volume effect, with inverted volume: 0.
	db 12	; Note with effects flag.
	db 67	; Note reference (3). Primary wait (0).
	db 34	;    Volume effect, with inverted volume: 2.
	db 12	; Note with effects flag.
	db 214	; Primary instrument (2). Note reference (6). New wait (127).
	db 127	;   Escape wait value.
	db 2	;    Volume effect, with inverted volume: 0.

feverRemix_Subsong0DisarkByteRegionEnd5
; The note indexes.
feverRemix_Subsong0_NoteIndexes
feverRemix_Subsong0DisarkByteRegionStart6
	db 64	; Note for index 0.
	db 67	; Note for index 1.
	db 62	; Note for index 2.
	db 48	; Note for index 3.
	db 60	; Note for index 4.
	db 69	; Note for index 5.
	db 36	; Note for index 6.
	db 43	; Note for index 7.
	db 59	; Note for index 8.
	db 40	; Note for index 9.
	db 65	; Note for index 10.
	db 31	; Note for index 11.
feverRemix_Subsong0DisarkByteRegionEnd6

; Fever (Country-esuqe Remix), Subsong 1.
; ----------------------------------

feverRemix_Subsong1
feverRemix_Subsong1DisarkPointerRegionStart0
	dw feverRemix_Subsong1_NoteIndexes	; Index table for the notes.
	dw feverRemix_Subsong1_TrackIndexes	; Index table for the Tracks.
feverRemix_Subsong1DisarkPointerRegionEnd0

feverRemix_Subsong1DisarkByteRegionStart1
	db 6	; Initial speed.

	db 2	; Most used instrument.
	db 4	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 47	; Default start note in tracks.
	db 6	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
feverRemix_Subsong1DisarkByteRegionEnd1

; The Linker.
feverRemix_Subsong1DisarkByteRegionStart2
; Pattern 0
	db 170	; State byte.
	db 8	; New height.
	db ((feverRemix_Subsong1_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong1_Track0 - ($ + 1)) & 255)
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 1
feverRemix_Subsong1_Loop
	db 10	; State byte.
	db 0	; New height.
	db 128	; New track (1) for channel 1, as a reference (index 0).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
feverRemix_Subsong1DisarkByteRegionEnd2
feverRemix_Subsong1DisarkPointerRegionStart3
	dw feverRemix_Subsong1_Loop

feverRemix_Subsong1DisarkPointerRegionEnd3
; The indexes of the tracks.
feverRemix_Subsong1_TrackIndexes
feverRemix_Subsong1DisarkPointerRegionStart4
	dw feverRemix_Subsong1_Track1	; Track 1, index 0.
feverRemix_Subsong1DisarkPointerRegionEnd4

feverRemix_Subsong1DisarkByteRegionStart5
feverRemix_Subsong1_Track0
	db 143	; Same escaped note: 47. Secondary wait (1).
	db 142	; New escaped note: 46. Secondary wait (1).
	db 46	;   Escape note value.
	db 142	; New escaped note: 45. Secondary wait (1).
	db 45	;   Escape note value.
	db 142	; New escaped note: 44. Secondary wait (1).
	db 44	;   Escape note value.
	db 199	; Note reference (7). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong1_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong1DisarkByteRegionEnd5
; The note indexes.
feverRemix_Subsong1_NoteIndexes
feverRemix_Subsong1DisarkByteRegionStart6
	db 64	; Note for index 0.
	db 67	; Note for index 1.
	db 62	; Note for index 2.
	db 48	; Note for index 3.
	db 60	; Note for index 4.
	db 69	; Note for index 5.
	db 36	; Note for index 6.
	db 43	; Note for index 7.
	db 59	; Note for index 8.
	db 40	; Note for index 9.
	db 65	; Note for index 10.
	db 31	; Note for index 11.
feverRemix_Subsong1DisarkByteRegionEnd6

; Fever (Country-esuqe Remix), Subsong 2.
; ----------------------------------

feverRemix_Subsong2
feverRemix_Subsong2DisarkPointerRegionStart0
	dw feverRemix_Subsong2_NoteIndexes	; Index table for the notes.
	dw feverRemix_Subsong2_TrackIndexes	; Index table for the Tracks.
feverRemix_Subsong2DisarkPointerRegionEnd0

feverRemix_Subsong2DisarkByteRegionStart1
	db 6	; Initial speed.

	db 2	; Most used instrument.
	db 4	; Second most used instrument.

	db 0	; Most used wait.
	db 1	; Second most used wait.

	db 53	; Default start note in tracks.
	db 7	; Default start instrument in tracks.
	db 0	; Default start wait in tracks.

	db 12	; Are there effects? 12 if yes, 13 if not. Don't ask.
feverRemix_Subsong2DisarkByteRegionEnd1

; The Linker.
feverRemix_Subsong2DisarkByteRegionStart2
; Pattern 0
	db 171	; State byte.
	db 5	; New speed (>0).
	db 18	; New height.
	db ((feverRemix_Subsong2_Track0 - ($ + 2)) & #ff00) / 256	; New track (0) for channel 1, as an offset. Offset MSB, then LSB.
	db ((feverRemix_Subsong2_Track0 - ($ + 1)) & 255)
	db 128	; New track (1) for channel 2, as a reference (index 0).
	db 128	; New track (1) for channel 3, as a reference (index 0).

; Pattern 1
feverRemix_Subsong2_Loop
	db 10	; State byte.
	db 0	; New height.
	db 128	; New track (1) for channel 1, as a reference (index 0).

	db 1	; End of the Song.
	db 0	; Speed to 0, meaning "end of song".
feverRemix_Subsong2DisarkByteRegionEnd2
feverRemix_Subsong2DisarkPointerRegionStart3
	dw feverRemix_Subsong2_Loop

feverRemix_Subsong2DisarkPointerRegionEnd3
; The indexes of the tracks.
feverRemix_Subsong2_TrackIndexes
feverRemix_Subsong2DisarkPointerRegionStart4
	dw feverRemix_Subsong2_Track1	; Track 1, index 0.
feverRemix_Subsong2DisarkPointerRegionEnd4

feverRemix_Subsong2DisarkByteRegionStart5
feverRemix_Subsong2_Track0
	db 143	; Same escaped note: 53. Secondary wait (1).
	db 143	; Same escaped note: 53. Secondary wait (1).
	db 143	; Same escaped note: 53. Secondary wait (1).
	db 142	; New escaped note: 55. Secondary wait (1).
	db 55	;   Escape note value.
	db 143	; Same escaped note: 55. Secondary wait (1).
	db 143	; Same escaped note: 55. Secondary wait (1).
	db 142	; New escaped note: 57. Secondary wait (1).
	db 57	;   Escape note value.
	db 143	; Same escaped note: 57. Secondary wait (1).
	db 143	; Same escaped note: 57. Secondary wait (1).
	db 194	; Note reference (2). New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong2_Track1
	db 205	; New wait (127).
	db 127	;   Escape wait value.

feverRemix_Subsong2DisarkByteRegionEnd5
; The note indexes.
feverRemix_Subsong2_NoteIndexes
feverRemix_Subsong2DisarkByteRegionStart6
	db 64	; Note for index 0.
	db 67	; Note for index 1.
	db 62	; Note for index 2.
	db 48	; Note for index 3.
	db 60	; Note for index 4.
	db 69	; Note for index 5.
	db 36	; Note for index 6.
	db 43	; Note for index 7.
	db 59	; Note for index 8.
	db 40	; Note for index 9.
	db 65	; Note for index 10.
	db 31	; Note for index 11.
feverRemix_Subsong2DisarkByteRegionEnd6

