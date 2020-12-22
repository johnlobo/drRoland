DRROLANDSOUNDTRACK_START:
_DRROLANDSOUNDTRACK_START::
PLY_AKG_OPCODE_ADD_HL_BC_MSB: .db 65
PLY_AKG_FULL_INIT_CODE:
PLY_AKG_OFFSET1B:
PLY_AKG_USE_HOOKS:
PLY_AKG_STOP_SOUNDS: .db 84
PLY_AKG_BITFORSOUND:
PLY_AKG_OFFSET2B:
PLY_AKG_SOUNDEFFECTDATA_OFFSETINVERTEDVOLUME: .db 50
PLY_AKG_SOUNDEFFECTDATA_OFFSETCURRENTSTEP: .db 48
PLY_AKG_BITFORNOISE = .+1
PLY_AKG_SOUNDEFFECTDATA_OFFSETSPEED: .dw DRROLANDSOUNDTRACK_ARPEGGIOTABLE
    .dw DRROLANDSOUNDTRACK_ARPEGGIOTABLE
PLY_AKG_OPCODE_ADD_HL_BC_LSB = .+1
PLY_AKG_CHANNEL_SOUNDEFFECTDATASIZE: .dw DRROLANDSOUNDTRACK_ARPEGGIOTABLE
    .dw DRROLANDSOUNDTRACK_EFFECTBLOCKTABLE
    .dw DRROLANDSOUNDTRACK_SUBSONG0_START
    .dw DRROLANDSOUNDTRACK_SUBSONG1_START
    .dw DRROLANDSOUNDTRACK_SUBSONG2_START
    .dw DRROLANDSOUNDTRACK_SUBSONG3_START
    .dw DRROLANDSOUNDTRACK_SUBSONG4_START
    .dw DRROLANDSOUNDTRACK_SUBSONG5_START
    .dw DRROLANDSOUNDTRACK_SUBSONG6_START
    .dw DRROLANDSOUNDTRACK_SUBSONG7_START
DRROLANDSOUNDTRACK_ARPEGGIOTABLE:
DRROLANDSOUNDTRACK_PITCHTABLE:
DRROLANDSOUNDTRACK_INSTRUMENTTABLE: .dw DRROLANDSOUNDTRACK_EMPTYINSTRUMENT
    .dw DRROLANDSOUNDTRACK_INSTRUMENT1
    .dw DRROLANDSOUNDTRACK_INSTRUMENT2
PLY_AKG_OPCODE_INC_HL = .+1
    .dw DRROLANDSOUNDTRACK_INSTRUMENT3
    .dw DRROLANDSOUNDTRACK_INSTRUMENT4
DRROLANDSOUNDTRACK_EMPTYINSTRUMENT: .db 0
DRROLANDSOUNDTRACK_EMPTYINSTRUMENT_LOOP: .db 0
    .db 6
DRROLANDSOUNDTRACK_INSTRUMENT1: .db 1
    .db 249
PLY_AKG_OPCODE_DEC_HL: .db 241
    .db 233
    .db 225
    .db 217
    .db 209
    .db 201
    .db 193
    .db 185
    .db 177
    .db 169
    .db 161
    .db 153
PLY_AKG_OPCODE_SCF: .db 145
    .db 137
    .db 6
DRROLANDSOUNDTRACK_INSTRUMENT2: .db 1
    .db 248
    .db 1
    .db 232
    .db 1
    .db 216
    .db 1
    .db 192
PLY_AKG_OPCODE_SBC_HL_BC_LSB: .db 1
    .db 168
    .db 1
    .db 6
DRROLANDSOUNDTRACK_INSTRUMENT3: .db 5
    .db 249
    .db 241
    .db 233
    .db 225
    .db 217
    .db 217
    .db 217
    .db 217
    .db 217
    .db 217
    .db 217
    .db 217
    .db 201
    .db 193
    .db 185
    .db 177
    .db 169
    .db 161
    .db 153
    .db 145
    .db 137
    .db 6
DRROLANDSOUNDTRACK_INSTRUMENT4: .db 1
    .db 248
    .db 1
    .db 113
    .db 34
    .db 246
    .db 255
    .db 97
    .db 35
    .db 226
    .db 255
    .db 216
    .db 1
    .db 80
    .db 208
    .db 1
    .db 200
    .db 1
    .db 192
    .db 1
    .db 184
    .db 1
    .db 176
    .db 1
    .db 168
    .db 1
    .db 160
    .db 1
    .db 144
    .db 1
    .db 136
    .db 1
    .db 6
DRROLANDSOUNDTRACK_EFFECTBLOCKTABLE: .dw DRROLANDSOUNDTRACK_EFFECTBLOCK_P4P0
    .dw DRROLANDSOUNDTRACK_EFFECTBLOCK_P4P1
    .dw DRROLANDSOUNDTRACK_EFFECTBLOCK_P4P2
DRROLANDSOUNDTRACK_EFFECTBLOCK_P4P0: .db 4
    .db 0
DRROLANDSOUNDTRACK_EFFECTBLOCK_P4P1: .db 4
    .db 1
DRROLANDSOUNDTRACK_EFFECTBLOCK_P4P2: .db 4
    .db 2
DRROLANDSOUNDTRACK_SUBSONG0_START: .db 2
    .db 0
    .db 1
    .db 0
    .db 7
    .db 6
    .db 27
DRROLANDSOUNDTRACK_SUBSONG0_LINKER:
DRROLANDSOUNDTRACK_SUBSONG0_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK3
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK4
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK5
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK6
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK7
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK8
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK9
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK10
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
PLY_AKG_OPCODE_OR_A: .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK11
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK12
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK13
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK14
PLY_AKG_OPCODE_ADD_A_IMMEDIATE = .+1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK11
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK15
    .dw DRROLANDSOUNDTRACK_SUBSONG0_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG0_LINKER
DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK0: .db 48
PLY_AKG_OPCODE_SUB_IMMEDIATE: .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG0_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG0_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG0_LINKERBLOCK1: .db 48
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG0_SPEEDTRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG0_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG0_TRACK0: .db 237
    .db 1
    .db 0
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
PLY_AKG_OPCODE_SBC_HL_BC_MSB: .db 54
    .db 126
    .db 54
    .db 60
    .db 52
    .db 126
    .db 52
    .db 60
    .db 50
    .db 126
    .db 45
    .db 60
    .db 45
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 55
    .db 126
    .db 55
    .db 60
    .db 54
    .db 126
    .db 54
    .db 60
    .db 52
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK1: .db 61
    .db 5
    .db 230
    .db 1
    .db 0
    .db 126
    .db 38
    .db 60
    .db 37
    .db 126
    .db 37
    .db 60
    .db 38
    .db 61
    .db 10
    .db 25
    .db 126
    .db 25
    .db 60
    .db 26
    .db 126
    .db 26
    .db 60
    .db 21
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK2: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK3: .db 173
    .db 1
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 54
    .db 126
    .db 54
    .db 60
    .db 52
    .db 126
    .db 52
    .db 60
    .db 50
    .db 126
    .db 45
    .db 60
    .db 45
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 40
    .db 126
    .db 52
    .db 60
    .db 43
    .db 60
    .db 47
    .db 60
    .db 49
    .db 60
    .db 50
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK4: .db 61
    .db 5
    .db 166
    .db 1
    .db 126
    .db 38
    .db 60
    .db 37
    .db 126
    .db 37
    .db 60
    .db 38
    .db 61
    .db 10
    .db 35
    .db 61
    .db 10
    .db 33
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK5: .db 161
    .db 1
    .db 60
    .db 35
    .db 60
    .db 33
    .db 60
    .db 37
    .db 126
    .db 37
    .db 60
    .db 38
    .db 126
    .db 38
    .db 60
    .db 39
    .db 126
    .db 40
    .db 60
    .db 33
    .db 60
    .db 35
    .db 60
    .db 33
    .db 60
    .db 31
    .db 60
    .db 33
    .db 60
    .db 31
    .db 60
    .db 30
    .db 60
    .db 31
    .db 60
    .db 30
    .db 60
    .db 28
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK6: .db 61
    .db 5
    .db 159
    .db 1
    .db 126
    .db 31
    .db 60
    .db 30
    .db 126
    .db 30
    .db 60
    .db 28
    .db 254
    .db 21
    .db 60
    .db 23
    .db 60
    .db 21
    .db 60
    .db 19
    .db 60
    .db 21
    .db 60
    .db 19
    .db 60
    .db 18
    .db 60
    .db 19
    .db 60
    .db 18
    .db 60
    .db 16
    .db 126
    .db 21
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK7: .db 173
    .db 1
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 54
    .db 126
    .db 54
    .db 60
    .db 52
    .db 126
    .db 52
    .db 60
    .db 50
    .db 126
    .db 50
    .db 60
    .db 50
    .db 60
    .db 49
    .db 60
    .db 47
    .db 60
    .db 45
    .db 126
    .db 42
    .db 60
    .db 43
    .db 126
    .db 37
    .db 60
    .db 38
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK8: .db 61
    .db 23
    .db 159
    .db 1
    .db 254
    .db 33
    .db 254
    .db 21
    .db 254
    .db 26
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK9: .db 170
    .db 1
    .db 60
    .db 43
    .db 60
    .db 42
    .db 60
    .db 47
    .db 126
    .db 47
    .db 60
    .db 50
    .db 126
    .db 50
    .db 60
    .db 49
    .db 126
    .db 42
    .db 60
    .db 42
    .db 60
    .db 43
    .db 60
    .db 42
    .db 60
    .db 47
    .db 126
    .db 47
    .db 60
    .db 50
    .db 126
    .db 50
    .db 60
    .db 49
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK10: .db 61
    .db 5
    .db 166
    .db 1
    .db 126
    .db 38
    .db 60
    .db 35
    .db 126
    .db 35
    .db 60
    .db 34
    .db 61
    .db 10
    .db 38
    .db 126
    .db 38
    .db 60
    .db 35
    .db 126
    .db 35
    .db 60
    .db 34
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK11: .db 170
    .db 1
    .db 60
    .db 43
    .db 60
    .db 42
    .db 60
    .db 50
    .db 126
    .db 50
    .db 60
    .db 49
    .db 126
    .db 49
    .db 60
    .db 47
    .db 126
    .db 47
    .db 60
    .db 48
    .db 126
    .db 48
    .db 60
    .db 47
    .db 126
    .db 47
    .db 60
    .db 46
    .db 126
    .db 46
    .db 60
    .db 47
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK12: .db 61
    .db 11
    .db 162
    .db 1
    .db 126
    .db 34
    .db 60
    .db 35
    .db 126
    .db 35
    .db 60
    .db 28
    .db 126
    .db 28
    .db 60
    .db 30
    .db 126
    .db 30
    .db 60
    .db 18
    .db 126
    .db 18
    .db 60
    .db 23
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK13: .db 170
    .db 1
    .db 60
    .db 43
    .db 60
    .db 42
    .db 60
    .db 46
    .db 126
    .db 46
    .db 60
    .db 47
    .db 126
    .db 47
    .db 60
    .db 48
    .db 126
    .db 37
    .db 60
    .db 30
    .db 60
    .db 31
    .db 60
    .db 30
    .db 60
    .db 28
    .db 60
    .db 30
    .db 60
    .db 28
    .db 60
    .db 26
    .db 60
    .db 28
    .db 60
    .db 26
    .db 60
    .db 25
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK14: .db 61
    .db 5
    .db 158
    .db 1
    .db 126
    .db 30
    .db 60
    .db 30
    .db 126
    .db 30
    .db 60
    .db 37
    .db 254
    .db 18
    .db 60
    .db 19
    .db 60
    .db 18
    .db 60
    .db 16
    .db 60
    .db 18
    .db 60
    .db 16
    .db 60
    .db 14
    .db 60
    .db 16
    .db 60
    .db 14
    .db 60
    .db 13
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_TRACK15: .db 61
    .db 5
    .db 166
    .db 1
    .db 126
    .db 38
    .db 60
    .db 33
    .db 126
    .db 33
    .db 60
    .db 35
    .db 126
    .db 35
    .db 60
    .db 28
    .db 126
    .db 28
    .db 60
    .db 30
    .db 126
    .db 30
    .db 60
    .db 18
    .db 126
    .db 18
    .db 60
    .db 23
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG0_SPEEDTRACK0: .db 8
    .db 253
DRROLANDSOUNDTRACK_SUBSONG0_SPEEDTRACK1: .db 255
DRROLANDSOUNDTRACK_SUBSONG0_EVENTTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG1_START: .db 2
    .db 0
    .db 1
    .db 0
    .db 4
    .db 6
    .db 29
DRROLANDSOUNDTRACK_SUBSONG1_LINKER:
DRROLANDSOUNDTRACK_SUBSONG1_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG1_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK3
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK4
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG1_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK5
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK6
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG1_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK7
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK8
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG1_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK9
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK10
    .dw DRROLANDSOUNDTRACK_SUBSONG1_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG1_LINKERBLOCK0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_LINKER
DRROLANDSOUNDTRACK_SUBSONG1_LINKERBLOCK0: .db 48
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG1_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG1_TRACK0: .db 237
    .db 1
    .db 0
    .db 60
    .db 44
    .db 60
    .db 45
    .db 60
    .db 50
    .db 126
    .db 50
    .db 43
    .db 42
    .db 60
    .db 40
    .db 60
    .db 42
    .db 60
    .db 45
    .db 126
    .db 45
    .db 60
    .db 50
    .db 60
    .db 45
    .db 60
    .db 46
    .db 60
    .db 47
    .db 60
    .db 40
    .db 60
    .db 42
    .db 60
    .db 43
    .db 60
    .db 35
    .db 60
    .db 40
    .db 60
    .db 38
    .db 126
    .db 37
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK1: .db 61
    .db 5
    .db 218
    .db 1
    .db 0
    .db 60
    .db 30
    .db 60
    .db 33
    .db 60
    .db 26
    .db 60
    .db 30
    .db 60
    .db 33
    .db 60
    .db 26
    .db 60
    .db 30
    .db 60
    .db 33
    .db 60
    .db 18
    .db 60
    .db 21
    .db 60
    .db 26
    .db 60
    .db 19
    .db 60
    .db 23
    .db 60
    .db 28
    .db 60
    .db 19
    .db 60
    .db 23
    .db 60
    .db 28
    .db 60
    .db 21
    .db 60
    .db 25
    .db 60
    .db 28
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK2: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK3: .db 173
    .db 1
    .db 60
    .db 44
    .db 60
    .db 45
    .db 60
    .db 50
    .db 126
    .db 50
    .db 43
    .db 42
    .db 60
    .db 40
    .db 60
    .db 42
    .db 60
    .db 45
    .db 126
    .db 45
    .db 60
    .db 50
    .db 60
    .db 45
    .db 60
    .db 46
    .db 60
    .db 47
    .db 60
    .db 43
    .db 60
    .db 40
    .db 60
    .db 38
    .db 126
    .db 37
    .db 60
    .db 38
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK4: .db 149
    .db 1
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 26
    .db 60
    .db 30
    .db 60
    .db 33
    .db 60
    .db 26
    .db 60
    .db 30
    .db 60
    .db 33
    .db 60
    .db 26
    .db 60
    .db 30
    .db 60
    .db 33
    .db 60
    .db 18
    .db 60
    .db 21
    .db 60
    .db 26
    .db 60
    .db 19
    .db 60
    .db 23
    .db 60
    .db 28
    .db 60
    .db 30
    .db 126
    .db 31
    .db 60
    .db 30
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK5: .db 168
    .db 1
    .db 126
    .db 40
    .db 60
    .db 40
    .db 60
    .db 38
    .db 60
    .db 37
    .db 60
    .db 45
    .db 126
    .db 45
    .db 60
    .db 45
    .db 60
    .db 44
    .db 60
    .db 42
    .db 60
    .db 50
    .db 126
    .db 50
    .db 60
    .db 50
    .db 60
    .db 49
    .db 60
    .db 47
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 44
    .db 60
    .db 44
    .db 60
    .db 42
    .db 60
    .db 40
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK6: .db 61
    .db 5
    .db 137
    .db 1
    .db 126
    .db 21
    .db 60
    .db 21
    .db 126
    .db 21
    .db 60
    .db 14
    .db 126
    .db 26
    .db 60
    .db 26
    .db 126
    .db 26
    .db 60
    .db 28
    .db 254
    .db 16
    .db 254
    .db 28
    .db 126
    .db 16
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK7: .db 166
    .db 1
    .db 126
    .db 38
    .db 60
    .db 38
    .db 60
    .db 37
    .db 60
    .db 35
    .db 60
    .db 44
    .db 126
    .db 44
    .db 60
    .db 44
    .db 60
    .db 42
    .db 60
    .db 40
    .db 60
    .db 50
    .db 126
    .db 50
    .db 60
    .db 50
    .db 60
    .db 49
    .db 60
    .db 47
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 44
    .db 60
    .db 45
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK8: .db 156
    .db 1
    .db 254
    .db 16
    .db 126
    .db 28
    .db 60
    .db 28
    .db 60
    .db 32
    .db 60
    .db 35
    .db 60
    .db 28
    .db 60
    .db 32
    .db 60
    .db 35
    .db 60
    .db 28
    .db 60
    .db 32
    .db 60
    .db 35
    .db 60
    .db 28
    .db 60
    .db 32
    .db 60
    .db 35
    .db 60
    .db 28
    .db 60
    .db 35
    .db 60
    .db 38
    .db 60
    .db 28
    .db 60
    .db 33
    .db 60
    .db 37
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK9: .db 62
    .db 175
    .db 1
    .db 60
    .db 44
    .db 60
    .db 52
    .db 61
    .db 6
    .db 50
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 47
    .db 60
    .db 44
    .db 60
    .db 45
    .db 60
    .db 47
    .db 60
    .db 42
    .db 60
    .db 43
    .db 254
    .db 45
    .db 47
    .db 49
    .db 50
    .db 52
    .db 54
    .db 55
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_TRACK10: .db 156
    .db 1
    .db 60
    .db 35
    .db 60
    .db 38
    .db 60
    .db 28
    .db 60
    .db 32
    .db 60
    .db 35
    .db 60
    .db 28
    .db 60
    .db 32
    .db 60
    .db 35
    .db 60
    .db 33
    .db 126
    .db 38
    .db 60
    .db 37
    .db 126
    .db 39
    .db 60
    .db 40
    .db 61
    .db 10
    .db 43
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG1_SPEEDTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG1_EVENTTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG2_START: .db 2
    .db 0
    .db 1
    .db 0
    .db 3
    .db 6
    .db 26
DRROLANDSOUNDTRACK_SUBSONG2_LINKER:
DRROLANDSOUNDTRACK_SUBSONG2_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG2_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK3
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK4
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG2_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK5
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK6
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG2_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK7
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK8
    .dw DRROLANDSOUNDTRACK_SUBSONG2_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG2_LINKERBLOCK0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG2_LINKER
DRROLANDSOUNDTRACK_SUBSONG2_LINKERBLOCK0: .db 48
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG2_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG2_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG2_TRACK0: .db 232
    .db 1
    .db 0
    .db 41
    .db 43
    .db 62
    .db 45
    .db 43
    .db 60
    .db 43
    .db 62
    .db 45
    .db 43
    .db 60
    .db 48
    .db 126
    .db 43
    .db 60
    .db 43
    .db 126
    .db 40
    .db 41
    .db 43
    .db 62
    .db 45
    .db 43
    .db 60
    .db 43
    .db 62
    .db 45
    .db 43
    .db 60
    .db 50
    .db 60
    .db 50
    .db 60
    .db 43
    .db 60
    .db 43
    .db 60
    .db 40
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK1: .db 62
    .db 216
    .db 1
    .db 0
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 23
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 23
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 23
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 31
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK2: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK3: .db 169
    .db 1
    .db 60
    .db 43
    .db 60
    .db 45
    .db 60
    .db 43
    .db 60
    .db 43
    .db 60
    .db 45
    .db 60
    .db 43
    .db 60
    .db 48
    .db 126
    .db 43
    .db 60
    .db 50
    .db 126
    .db 43
    .db 60
    .db 52
    .db 62
    .db 50
    .db 48
    .db 60
    .db 43
    .db 62
    .db 48
    .db 47
    .db 60
    .db 48
    .db 126
    .db 36
    .db 60
    .db 36
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK4: .db 62
    .db 152
    .db 1
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 23
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 24
    .db 126
    .db 28
    .db 60
    .db 31
    .db 126
    .db 19
    .db 60
    .db 24
    .db 254
    .db 12
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK5: .db 62
    .db 180
    .db 1
    .db 62
    .db 50
    .db 48
    .db 60
    .db 52
    .db 62
    .db 50
    .db 48
    .db 60
    .db 50
    .db 126
    .db 43
    .db 60
    .db 43
    .db 254
    .db 52
    .db 62
    .db 50
    .db 48
    .db 60
    .db 52
    .db 62
    .db 50
    .db 48
    .db 60
    .db 53
    .db 126
    .db 50
    .db 60
    .db 50
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK6: .db 62
    .db 152
    .db 1
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 23
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 19
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 23
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 19
    .db 60
    .db 26
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK7: .db 60
    .db 176
    .db 1
    .db 52
    .db 62
    .db 50
    .db 48
    .db 60
    .db 52
    .db 62
    .db 50
    .db 48
    .db 60
    .db 53
    .db 60
    .db 52
    .db 60
    .db 50
    .db 60
    .db 55
    .db 126
    .db 53
    .db 60
    .db 52
    .db 62
    .db 50
    .db 48
    .db 60
    .db 43
    .db 48
    .db 62
    .db 47
    .db 60
    .db 48
    .db 126
    .db 36
    .db 60
    .db 36
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_TRACK8: .db 159
    .db 1
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 24
    .db 60
    .db 28
    .db 60
    .db 31
    .db 60
    .db 23
    .db 60
    .db 26
    .db 60
    .db 31
    .db 60
    .db 31
    .db 254
    .db 24
    .db 126
    .db 28
    .db 60
    .db 31
    .db 126
    .db 19
    .db 60
    .db 24
    .db 126
    .db 12
    .db 60
    .db 12
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG2_SPEEDTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG2_EVENTTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG3_START: .db 2
    .db 0
    .db 1
    .db 0
    .db 4
    .db 6
    .db 27
DRROLANDSOUNDTRACK_SUBSONG3_LINKER:
DRROLANDSOUNDTRACK_SUBSONG3_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG3_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK3
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK4
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG3_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK5
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK6
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG3_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK7
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK8
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG3_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK9
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK10
    .dw DRROLANDSOUNDTRACK_SUBSONG3_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG3_LINKERBLOCK0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_LINKER
DRROLANDSOUNDTRACK_SUBSONG3_LINKERBLOCK0: .db 48
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG3_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG3_TRACK0: .db 230
    .db 1
    .db 0
    .db 60
    .db 38
    .db 60
    .db 43
    .db 60
    .db 43
    .db 60
    .db 43
    .db 60
    .db 47
    .db 60
    .db 52
    .db 50
    .db 45
    .db 60
    .db 45
    .db 60
    .db 47
    .db 45
    .db 43
    .db 60
    .db 38
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 45
    .db 60
    .db 49
    .db 47
    .db 45
    .db 60
    .db 45
    .db 60
    .db 50
    .db 45
    .db 42
    .db 62
    .db 45
    .db 43
    .db 40
    .db 38
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK1: .db 62
    .db 211
    .db 1
    .db 0
    .db 60
    .db 31
    .db 60
    .db 31
    .db 60
    .db 19
    .db 60
    .db 31
    .db 60
    .db 31
    .db 60
    .db 19
    .db 60
    .db 30
    .db 60
    .db 30
    .db 60
    .db 23
    .db 60
    .db 31
    .db 60
    .db 31
    .db 60
    .db 21
    .db 60
    .db 31
    .db 60
    .db 31
    .db 60
    .db 21
    .db 60
    .db 30
    .db 60
    .db 30
    .db 60
    .db 30
    .db 126
    .db 31
    .db 60
    .db 30
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK2: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK3: .db 166
    .db 1
    .db 60
    .db 48
    .db 60
    .db 45
    .db 60
    .db 45
    .db 60
    .db 47
    .db 60
    .db 43
    .db 60
    .db 43
    .db 45
    .db 43
    .db 60
    .db 42
    .db 60
    .db 43
    .db 60
    .db 45
    .db 60
    .db 50
    .db 60
    .db 38
    .db 60
    .db 48
    .db 60
    .db 45
    .db 60
    .db 45
    .db 60
    .db 47
    .db 62
    .db 43
    .db 52
    .db 50
    .db 49
    .db 62
    .db 55
    .db 52
    .db 49
    .db 50
    .db 49
    .db 48
    .db 45
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK4: .db 62
    .db 161
    .db 1
    .db 126
    .db 33
    .db 60
    .db 35
    .db 126
    .db 31
    .db 60
    .db 33
    .db 126
    .db 33
    .db 60
    .db 33
    .db 254
    .db 33
    .db 126
    .db 33
    .db 60
    .db 35
    .db 254
    .db 28
    .db 254
    .db 30
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK5: .db 170
    .db 1
    .db 38
    .db 38
    .db 60
    .db 43
    .db 60
    .db 43
    .db 60
    .db 43
    .db 60
    .db 47
    .db 60
    .db 52
    .db 50
    .db 45
    .db 60
    .db 45
    .db 60
    .db 47
    .db 45
    .db 43
    .db 60
    .db 38
    .db 60
    .db 38
    .db 60
    .db 40
    .db 42
    .db 43
    .db 45
    .db 47
    .db 48
    .db 49
    .db 60
    .db 50
    .db 60
    .db 47
    .db 60
    .db 50
    .db 60
    .db 48
    .db 60
    .db 45
    .db 60
    .db 43
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK6: .db 62
    .db 147
    .db 1
    .db 60
    .db 31
    .db 60
    .db 31
    .db 60
    .db 19
    .db 60
    .db 31
    .db 60
    .db 31
    .db 60
    .db 26
    .db 60
    .db 36
    .db 60
    .db 36
    .db 60
    .db 35
    .db 126
    .db 23
    .db 60
    .db 24
    .db 254
    .db 22
    .db 60
    .db 23
    .db 60
    .db 28
    .db 60
    .db 26
    .db 60
    .db 36
    .db 60
    .db 36
    .db 60
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK7: .db 171
    .db 1
    .db 43
    .db 43
    .db 60
    .db 45
    .db 60
    .db 47
    .db 60
    .db 48
    .db 60
    .db 47
    .db 60
    .db 45
    .db 60
    .db 43
    .db 60
    .db 45
    .db 60
    .db 40
    .db 60
    .db 40
    .db 60
    .db 41
    .db 60
    .db 55
    .db 55
    .db 55
    .db 60
    .db 55
    .db 60
    .db 55
    .db 60
    .db 52
    .db 60
    .db 43
    .db 60
    .db 40
    .db 40
    .db 40
    .db 60
    .db 41
    .db 60
    .db 38
    .db 60
    .db 36
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK8: .db 62
    .db 140
    .db 1
    .db 60
    .db 24
    .db 60
    .db 24
    .db 60
    .db 12
    .db 60
    .db 24
    .db 60
    .db 24
    .db 60
    .db 12
    .db 60
    .db 24
    .db 60
    .db 21
    .db 60
    .db 26
    .db 254
    .db 31
    .db 60
    .db 31
    .db 60
    .db 31
    .db 60
    .db 24
    .db 254
    .db 19
    .db 126
    .db 19
    .db 60
    .db 24
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK9: .db 183
    .db 1
    .db 55
    .db 43
    .db 60
    .db 50
    .db 60
    .db 43
    .db 53
    .db 52
    .db 60
    .db 43
    .db 60
    .db 55
    .db 55
    .db 43
    .db 60
    .db 50
    .db 60
    .db 43
    .db 53
    .db 52
    .db 60
    .db 43
    .db 60
    .db 43
    .db 43
    .db 43
    .db 60
    .db 45
    .db 60
    .db 47
    .db 60
    .db 48
    .db 126
    .db 52
    .db 52
    .db 55
    .db 60
    .db 53
    .db 60
    .db 50
    .db 60
    .db 48
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_TRACK10: .db 62
    .db 159
    .db 1
    .db 126
    .db 31
    .db 60
    .db 24
    .db 254
    .db 31
    .db 126
    .db 31
    .db 60
    .db 24
    .db 254
    .db 12
    .db 60
    .db 24
    .db 60
    .db 24
    .db 60
    .db 24
    .db 254
    .db 31
    .db 126
    .db 31
    .db 60
    .db 24
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG3_SPEEDTRACK0: .db 22
    .db 253
DRROLANDSOUNDTRACK_SUBSONG3_EVENTTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG4_START: .db 2
    .db 0
    .db 1
    .db 1
    .db 1
    .db 6
    .db 15
DRROLANDSOUNDTRACK_SUBSONG4_LINKER: .dw DRROLANDSOUNDTRACK_SUBSONG4_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG4_TRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG4_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG4_LINKERBLOCK0
DRROLANDSOUNDTRACK_SUBSONG4_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG4_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG4_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG4_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG4_LINKERBLOCK1
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG4_LINKER_LOOP
DRROLANDSOUNDTRACK_SUBSONG4_LINKERBLOCK0: .db 26
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG4_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG4_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG4_LINKERBLOCK1: .db 1
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG4_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG4_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG4_TRACK0: .db 225
    .db 1
    .db 2
    .db 60
    .db 37
    .db 60
    .db 40
    .db 60
    .db 24
    .db 60
    .db 40
    .db 60
    .db 43
    .db 60
    .db 38
    .db 60
    .db 42
    .db 60
    .db 45
    .db 60
    .db 43
    .db 60
    .db 43
    .db 60
    .db 50
    .db 60
    .db 55
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG4_TRACK1: .db 62
    .db 225
    .db 2
    .db 1
    .db 126
    .db 33
    .db 126
    .db 33
    .db 126
    .db 33
    .db 126
    .db 33
    .db 126
    .db 33
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG4_TRACK2: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG4_SPEEDTRACK0: .db 8
    .db 253
DRROLANDSOUNDTRACK_SUBSONG4_EVENTTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG5_START: .db 2
    .db 0
    .db 1
    .db 1
    .db 1
    .db 6
    .db 20
DRROLANDSOUNDTRACK_SUBSONG5_LINKER: .dw DRROLANDSOUNDTRACK_SUBSONG5_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG5_TRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG5_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG5_LINKERBLOCK0
DRROLANDSOUNDTRACK_SUBSONG5_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG5_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG5_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG5_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG5_LINKERBLOCK1
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG5_LINKER_LOOP
DRROLANDSOUNDTRACK_SUBSONG5_LINKERBLOCK0: .db 26
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG5_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG5_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG5_LINKERBLOCK1: .db 1
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG5_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG5_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG5_TRACK0: .db 247
    .db 1
    .db 1
    .db 62
    .db 52
    .db 62
    .db 55
    .db 60
    .db 53
    .db 62
    .db 52
    .db 62
    .db 50
    .db 60
    .db 48
    .db 254
    .db 36
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG5_TRACK1: .db 62
    .db 220
    .db 2
    .db 1
    .db 126
    .db 28
    .db 126
    .db 28
    .db 126
    .db 28
    .db 126
    .db 28
    .db 126
    .db 28
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG5_TRACK2: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG5_SPEEDTRACK0: .db 8
    .db 253
DRROLANDSOUNDTRACK_SUBSONG5_EVENTTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG6_START: .db 2
    .db 0
    .db 1
    .db 0
    .db 0
    .db 6
    .db 0
DRROLANDSOUNDTRACK_SUBSONG6_LINKER:
DRROLANDSOUNDTRACK_SUBSONG6_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG6_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG6_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG6_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG6_LINKERBLOCK0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG6_LINKER
DRROLANDSOUNDTRACK_SUBSONG6_LINKERBLOCK0: .db 1
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG6_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG6_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG6_TRACK0: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG6_SPEEDTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG6_EVENTTRACK0: .db 255
DRROLANDSOUNDTRACK_SUBSONG7_START: .db 2
    .db 0
    .db 1
    .db 0
    .db 19
    .db 6
    .db 27
DRROLANDSOUNDTRACK_SUBSONG7_LINKER:
DRROLANDSOUNDTRACK_SUBSONG7_LINKER_LOOP: .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK1
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK3
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK4
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK5
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK6
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK7
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK8
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK9
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK9
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK10
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK11
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK2
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK3
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK4
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK5
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK12
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK13
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK14
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK15
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_TRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_LINKER
DRROLANDSOUNDTRACK_SUBSONG7_LINKERBLOCK0: .db 64
    .db 0
    .db 0
    .db 0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_SPEEDTRACK0
    .dw DRROLANDSOUNDTRACK_SUBSONG7_EVENTTRACK0
DRROLANDSOUNDTRACK_SUBSONG7_TRACK0: .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK1: .db 196
    .db 3
    .db 0
    .db 60
    .db 132
    .db 1
    .db 60
    .db 19
    .db 60
    .db 20
    .db 60
    .db 21
    .db 60
    .db 20
    .db 60
    .db 19
    .db 60
    .db 18
    .db 60
    .db 4
    .db 60
    .db 4
    .db 60
    .db 19
    .db 60
    .db 20
    .db 60
    .db 21
    .db 60
    .db 20
    .db 60
    .db 19
    .db 60
    .db 18
    .db 60
    .db 4
    .db 60
    .db 16
    .db 60
    .db 8
    .db 60
    .db 20
    .db 60
    .db 9
    .db 60
    .db 20
    .db 60
    .db 10
    .db 60
    .db 11
    .db 60
    .db 4
    .db 60
    .db 16
    .db 60
    .db 8
    .db 60
    .db 20
    .db 60
    .db 9
    .db 60
    .db 20
    .db 60
    .db 10
    .db 60
    .db 11
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK2: .db 132
    .db 1
    .db 32
    .db 35
    .db 28
    .db 8
    .db 37
    .db 35
    .db 32
    .db 9
    .db 33
    .db 37
    .db 40
    .db 10
    .db 40
    .db 11
    .db 33
    .db 4
    .db 32
    .db 35
    .db 32
    .db 8
    .db 35
    .db 32
    .db 28
    .db 9
    .db 126
    .db 16
    .db 12
    .db 8
    .db 4
    .db 4
    .db 32
    .db 35
    .db 28
    .db 8
    .db 37
    .db 35
    .db 32
    .db 9
    .db 33
    .db 37
    .db 40
    .db 10
    .db 40
    .db 11
    .db 33
    .db 16
    .db 16
    .db 16
    .db 60
    .db 18
    .db 18
    .db 18
    .db 60
    .db 19
    .db 19
    .db 19
    .db 149
    .db 4
    .db 148
    .db 1
    .db 20
    .db 20
    .db 149
    .db 4
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK3: .db 132
    .db 1
    .db 32
    .db 35
    .db 28
    .db 8
    .db 37
    .db 35
    .db 32
    .db 9
    .db 33
    .db 37
    .db 40
    .db 10
    .db 40
    .db 11
    .db 33
    .db 4
    .db 32
    .db 35
    .db 32
    .db 8
    .db 35
    .db 32
    .db 28
    .db 9
    .db 126
    .db 149
    .db 4
    .db 126
    .db 132
    .db 1
    .db 32
    .db 35
    .db 28
    .db 8
    .db 37
    .db 35
    .db 32
    .db 9
    .db 33
    .db 37
    .db 40
    .db 10
    .db 40
    .db 11
    .db 33
    .db 47
    .db 45
    .db 41
    .db 39
    .db 60
    .db 40
    .db 43
    .db 39
    .db 36
    .db 38
    .db 35
    .db 31
    .db 33
    .db 31
    .db 27
    .db 25
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK4: .db 137
    .db 1
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 38
    .db 42
    .db 45
    .db 15
    .db 45
    .db 16
    .db 38
    .db 9
    .db 37
    .db 40
    .db 37
    .db 13
    .db 40
    .db 37
    .db 33
    .db 14
    .db 26
    .db 33
    .db 38
    .db 15
    .db 38
    .db 16
    .db 30
    .db 9
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 38
    .db 42
    .db 45
    .db 13
    .db 45
    .db 42
    .db 38
    .db 11
    .db 35
    .db 39
    .db 35
    .db 18
    .db 39
    .db 11
    .db 42
    .db 16
    .db 35
    .db 14
    .db 42
    .db 13
    .db 38
    .db 11
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK5: .db 137
    .db 1
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 25
    .db 126
    .db 9
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 26
    .db 126
    .db 16
    .db 37
    .db 40
    .db 33
    .db 16
    .db 42
    .db 40
    .db 37
    .db 14
    .db 38
    .db 13
    .db 33
    .db 12
    .db 42
    .db 11
    .db 40
    .db 4
    .db 35
    .db 39
    .db 42
    .db 16
    .db 35
    .db 38
    .db 42
    .db 9
    .db 44
    .db 4
    .db 41
    .db 6
    .db 38
    .db 8
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK6: .db 149
    .db 1
    .db 37
    .db 33
    .db 27
    .db 16
    .db 60
    .db 37
    .db 60
    .db 20
    .db 35
    .db 32
    .db 27
    .db 13
    .db 60
    .db 17
    .db 60
    .db 18
    .db 33
    .db 30
    .db 24
    .db 13
    .db 60
    .db 18
    .db 30
    .db 16
    .db 60
    .db 20
    .db 60
    .db 21
    .db 28
    .db 25
    .db 60
    .db 26
    .db 42
    .db 38
    .db 32
    .db 21
    .db 60
    .db 42
    .db 60
    .db 25
    .db 40
    .db 37
    .db 32
    .db 18
    .db 60
    .db 22
    .db 60
    .db 23
    .db 38
    .db 35
    .db 29
    .db 23
    .db 60
    .db 25
    .db 35
    .db 26
    .db 60
    .db 27
    .db 60
    .db 28
    .db 38
    .db 20
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK7: .db 149
    .db 1
    .db 37
    .db 33
    .db 27
    .db 16
    .db 60
    .db 37
    .db 60
    .db 20
    .db 35
    .db 32
    .db 27
    .db 13
    .db 60
    .db 17
    .db 60
    .db 18
    .db 33
    .db 30
    .db 24
    .db 13
    .db 60
    .db 18
    .db 30
    .db 16
    .db 60
    .db 20
    .db 60
    .db 21
    .db 28
    .db 25
    .db 60
    .db 26
    .db 42
    .db 38
    .db 32
    .db 21
    .db 60
    .db 42
    .db 60
    .db 25
    .db 40
    .db 37
    .db 32
    .db 18
    .db 60
    .db 22
    .db 60
    .db 23
    .db 38
    .db 35
    .db 29
    .db 23
    .db 60
    .db 25
    .db 35
    .db 26
    .db 213
    .db 4
    .db 1
    .db 219
    .db 1
    .db 0
    .db 213
    .db 4
    .db 1
    .db 220
    .db 1
    .db 0
    .db 38
    .db 20
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK8: .db 137
    .db 1
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 2
    .db 126
    .db 9
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 3
    .db 126
    .db 16
    .db 37
    .db 40
    .db 33
    .db 16
    .db 42
    .db 40
    .db 37
    .db 14
    .db 38
    .db 13
    .db 33
    .db 12
    .db 42
    .db 11
    .db 40
    .db 4
    .db 35
    .db 39
    .db 42
    .db 16
    .db 35
    .db 38
    .db 42
    .db 9
    .db 40
    .db 4
    .db 40
    .db 9
    .db 50
    .db 44
    .db 37
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK9: .db 137
    .db 1
    .db 60
    .db 9
    .db 60
    .db 13
    .db 60
    .db 13
    .db 60
    .db 14
    .db 60
    .db 14
    .db 60
    .db 15
    .db 149
    .db 4
    .db 144
    .db 1
    .db 60
    .db 9
    .db 60
    .db 9
    .db 60
    .db 13
    .db 60
    .db 13
    .db 60
    .db 14
    .db 60
    .db 14
    .db 60
    .db 15
    .db 149
    .db 4
    .db 144
    .db 1
    .db 60
    .db 9
    .db 60
    .db 9
    .db 60
    .db 13
    .db 60
    .db 13
    .db 60
    .db 14
    .db 60
    .db 14
    .db 60
    .db 15
    .db 149
    .db 4
    .db 144
    .db 1
    .db 60
    .db 24
    .db 60
    .db 23
    .db 60
    .db 22
    .db 60
    .db 21
    .db 60
    .db 20
    .db 60
    .db 19
    .db 60
    .db 18
    .db 149
    .db 4
    .db 145
    .db 1
    .db 149
    .db 4
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK10: .db 144
    .db 1
    .db 60
    .db 15
    .db 61
    .db 12
    .db 16
    .db 60
    .db 15
    .db 61
    .db 12
    .db 16
    .db 60
    .db 15
    .db 61
    .db 10
    .db 149
    .db 2
    .db 21
    .db 145
    .db 1
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK11: .db 132
    .db 1
    .db 60
    .db 35
    .db 60
    .db 44
    .db 60
    .db 40
    .db 60
    .db 2
    .db 60
    .db 33
    .db 60
    .db 42
    .db 60
    .db 38
    .db 60
    .db 1
    .db 49
    .db 32
    .db 49
    .db 44
    .db 60
    .db 40
    .db 60
    .db 0
    .db 60
    .db 31
    .db 55
    .db 43
    .db 60
    .db 40
    .db 60
    .db 9
    .db 60
    .db 33
    .db 60
    .db 40
    .db 60
    .db 37
    .db 60
    .db 8
    .db 60
    .db 32
    .db 60
    .db 40
    .db 60
    .db 37
    .db 24
    .db 7
    .db 213
    .db 2
    .db 2
    .db 21
    .db 21
    .db 21
    .db 21
    .db 21
    .db 21
    .db 213
    .db 4
    .db 0
    .db 213
    .db 2
    .db 2
    .db 213
    .db 4
    .db 0
    .db 213
    .db 2
    .db 2
    .db 213
    .db 4
    .db 0
    .db 21
    .db 21
    .db 213
    .db 2
    .db 2
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK12: .db 137
    .db 1
    .db 37
    .db 33
    .db 27
    .db 4
    .db 60
    .db 37
    .db 60
    .db 8
    .db 35
    .db 32
    .db 27
    .db 1
    .db 60
    .db 5
    .db 60
    .db 6
    .db 33
    .db 30
    .db 24
    .db 1
    .db 60
    .db 6
    .db 30
    .db 4
    .db 60
    .db 8
    .db 60
    .db 9
    .db 28
    .db 13
    .db 60
    .db 14
    .db 42
    .db 38
    .db 32
    .db 9
    .db 60
    .db 42
    .db 60
    .db 13
    .db 40
    .db 37
    .db 32
    .db 6
    .db 60
    .db 10
    .db 60
    .db 11
    .db 38
    .db 35
    .db 29
    .db 11
    .db 60
    .db 13
    .db 35
    .db 14
    .db 60
    .db 15
    .db 60
    .db 16
    .db 38
    .db 8
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK13: .db 137
    .db 1
    .db 37
    .db 33
    .db 27
    .db 4
    .db 60
    .db 37
    .db 60
    .db 8
    .db 35
    .db 32
    .db 27
    .db 1
    .db 60
    .db 5
    .db 60
    .db 6
    .db 33
    .db 30
    .db 24
    .db 1
    .db 60
    .db 6
    .db 30
    .db 4
    .db 60
    .db 8
    .db 60
    .db 9
    .db 28
    .db 13
    .db 60
    .db 14
    .db 42
    .db 38
    .db 32
    .db 9
    .db 60
    .db 42
    .db 60
    .db 13
    .db 40
    .db 37
    .db 32
    .db 6
    .db 60
    .db 10
    .db 60
    .db 11
    .db 38
    .db 35
    .db 29
    .db 11
    .db 60
    .db 13
    .db 35
    .db 14
    .db 213
    .db 4
    .db 1
    .db 207
    .db 1
    .db 0
    .db 213
    .db 4
    .db 1
    .db 208
    .db 1
    .db 0
    .db 38
    .db 8
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK14: .db 137
    .db 1
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 2
    .db 126
    .db 9
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 3
    .db 126
    .db 16
    .db 37
    .db 40
    .db 33
    .db 16
    .db 42
    .db 40
    .db 37
    .db 14
    .db 38
    .db 13
    .db 33
    .db 12
    .db 42
    .db 11
    .db 40
    .db 4
    .db 35
    .db 39
    .db 42
    .db 16
    .db 35
    .db 38
    .db 42
    .db 9
    .db 108
    .db 1
    .db 68
    .db 0
    .db 105
    .db 1
    .db 70
    .db 0
    .db 38
    .db 8
    .db 35
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_TRACK15: .db 137
    .db 1
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 149
    .db 2
    .db 126
    .db 137
    .db 1
    .db 37
    .db 40
    .db 33
    .db 13
    .db 42
    .db 40
    .db 37
    .db 14
    .db 126
    .db 149
    .db 2
    .db 126
    .db 144
    .db 1
    .db 37
    .db 40
    .db 33
    .db 37
    .db 42
    .db 40
    .db 37
    .db 14
    .db 38
    .db 42
    .db 33
    .db 38
    .db 42
    .db 37
    .db 40
    .db 42
    .db 45
    .db 45
    .db 42
    .db 45
    .db 47
    .db 62
    .db 45
    .db 213
    .db 2
    .db 2
    .db 196
    .db 1
    .db 0
    .db 213
    .db 2
    .db 2
    .db 201
    .db 1
    .db 0
    .db 61
    .db 127
DRROLANDSOUNDTRACK_SUBSONG7_SPEEDTRACK0: .db 12
    .db 253
DRROLANDSOUNDTRACK_SUBSONG7_EVENTTRACK0: .db 255
FX_SOUNDEFFECTS:
_FX_SOUNDEFFECTS:: .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw FX_SOUNDEFFECTS_SOUND4
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw FX_SOUNDEFFECTS_SOUND9
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw FX_SOUNDEFFECTS_SOUND14
    .dw FX_SOUNDEFFECTS_SOUND15
    .dw FX_SOUNDEFFECTS_SOUND16
    .dw DRROLANDSOUNDTRACK_START
FX_SOUNDEFFECTS_SOUND4: .db 0
FX_SOUNDEFFECTS_SOUND4_LOOP: .db 189
    .db 1
    .db 150
    .db 0
    .db 57
    .db 75
    .db 0
    .db 181
    .db 1
    .db 119
    .db 0
    .db 49
    .db 60
    .db 0
    .db 185
    .db 1
    .db 100
    .db 0
    .db 120
    .db 1
    .db 50
    .db 0
    .db 61
    .db 45
    .db 1
    .db 0
    .db 61
    .db 45
    .db 1
    .db 1
    .db 90
    .db 2
    .db 61
    .db 45
    .db 1
    .db 1
    .db 180
    .db 4
    .db 61
    .db 45
    .db 1
    .db 1
    .db 180
    .db 4
    .db 61
    .db 45
    .db 1
    .db 4
FX_SOUNDEFFECTS_SOUND9: .db 0
FX_SOUNDEFFECTS_SOUND9_LOOP: .db 61
    .db 95
    .db 0
    .db 57
    .db 106
    .db 0
    .db 53
    .db 119
    .db 0
    .db 53
    .db 134
    .db 0
    .db 49
    .db 150
    .db 0
    .db 49
    .db 169
    .db 0
    .db 45
    .db 190
    .db 0
    .db 45
    .db 169
    .db 0
    .db 41
    .db 150
    .db 0
    .db 41
    .db 134
    .db 0
    .db 37
    .db 119
    .db 0
    .db 33
    .db 106
    .db 0
    .db 29
    .db 95
    .db 0
    .db 25
    .db 60
    .db 0
    .db 21
    .db 53
    .db 0
    .db 17
    .db 47
    .db 0
    .db 4
FX_SOUNDEFFECTS_SOUND14: .db 0
FX_SOUNDEFFECTS_SOUND14_LOOP: .db 248
    .db 18
    .db 240
    .db 19
    .db 232
    .db 20
    .db 224
    .db 21
    .db 216
    .db 22
    .db 169
    .db 23
    .db 159
    .db 0
    .db 165
    .db 24
    .db 159
    .db 0
    .db 157
    .db 25
    .db 159
    .db 0
    .db 149
    .db 26
    .db 159
    .db 0
    .db 4
FX_SOUNDEFFECTS_SOUND15: .db 1
FX_SOUNDEFFECTS_SOUND15_LOOP: .db 61
    .db 12
    .db 1
    .db 57
    .db 253
    .db 0
    .db 53
    .db 239
    .db 0
    .db 49
    .db 225
    .db 0
    .db 4
FX_SOUNDEFFECTS_SOUND16: .db 0
FX_SOUNDEFFECTS_SOUND16_LOOP: .db 232
    .db 1
    .db 208
    .db 1
    .db 200
    .db 1
    .db 184
    .db 1
    .db 168
    .db 1
    .db 160
    .db 1
    .db 144
    .db 1
    .db 136
    .db 1
    .db 4
PLY_AKG_START: jp PLY_AKG_INIT
    jp PLY_AKG_PLAY
    jp PLY_AKG_INITTABLE1_END
_PLY_AKG_INITSOUNDEFFECTS::
PLY_AKG_INITSOUNDEFFECTS: ld (PLY_AKG_PTSOUNDEFFECTTABLE+1),hl
    ret 
_PLY_AKG_PLAYSOUNDEFFECT::
    ;Gets the address to the sound effect.
		pop  af          ;; AF = Return address
		pop  hl          ;; H Rubbish / L = Sound effect
		pop  bc          ;; B = Volume / C = Channel
		push af          ;; Save back return address in the stack to fullfill __z88dk_callee convention				
		ld   a, l        ;; A = Subsong index
PLY_AKG_PLAYSOUNDEFFECT: dec a
PLY_AKG_PTSOUNDEFFECTTABLE: ld hl,#0
    ld e,a
    ld d,#0
    add hl,de
    add hl,de
    ld e,(hl)
    inc hl
    ld d,(hl)
    ld a,(de)
    inc de
    ex af,af'
    ld a,b
    ld hl,#PLY_AKG_CHANNEL1_SOUNDEFFECTDATA
    ld b,#0
    sla c
    sla c
    sla c
    add hl,bc
    ld (hl),e
    inc hl
    ld (hl),d
    inc hl
    ld (hl),a
    inc hl
    ld (hl),#0
    inc hl
    ex af,af'
    ld (hl),a
    ret 
_PLY_AKG_STOPSOUNDEFFECTFROMCHANNEL::
PLY_AKG_STOPSOUNDEFFECTFROMCHANNEL: add a,a
    add a,a
    add a,a
    ld e,a
    ld d,#0
    ld hl,#PLY_AKG_CHANNEL1_SOUNDEFFECTDATA
    add hl,de
    ld (hl),d
    inc hl
    ld (hl),d
    ret 
PLY_AKG_PLAYSOUNDEFFECTSSTREAM: rla 
    rla 
    ld ix,#PLY_AKG_CHANNEL1_SOUNDEFFECTDATA
    ld iy,#PLY_AKG_PSGREG8
    ld hl,#PLY_AKG_PSGREG01_INSTR+1
    exx
    ld c,a
    call PLY_AKG_PSES_PLAY
    ld ix,#PLY_AKG_CHANNEL2_SOUNDEFFECTDATA
    ld iy,#PLY_AKG_PSGREG9
    exx
    ld hl,#PLY_AKG_PSGREG23_INSTR+1
    exx
    srl c
    call PLY_AKG_PSES_PLAY
    ld ix,#PLY_AKG_CHANNEL3_SOUNDEFFECTDATA
    ld iy,#PLY_AKG_PSGREG10
    exx
    ld hl,#PLY_AKG_PSGREG45_INSTR+1
    exx
    rr c
    call PLY_AKG_PSES_PLAY
    ld a,c
    ret 
PLY_AKG_PSES_PLAY: ld l,+0(ix)
    ld h,+1(ix)
    ld a,l
    or h
    ret z
PLY_AKG_PSES_READFIRSTBYTE: ld a,(hl)
    inc hl
    ld b,a
    rra 
    jr c,PLY_AKG_PSES_SOFTWAREORSOFTWAREANDHARDWARE
    rra 
    rra 
    jr c,PLY_AKG_PSES_S_ENDORLOOP
    call PLY_AKG_PSES_MANAGEVOLUMEFROMA_FILTER4BITS
    rl b
    call c,PLY_AKG_PSES_READNOISEANDOPENNOISECHANNEL
    jr PLY_AKG_PSES_SAVEPOINTERANDEXIT
PLY_AKG_PSES_S_ENDORLOOP: xor a
    ld +0(ix),a
    ld +1(ix),a
    ret 
PLY_AKG_PSES_SAVEPOINTERANDEXIT: ld a,+3(ix)
    cp +4(ix)
    jr c,PLY_AKG_PSES_NOTREACHED
    ld +3(ix),#0
    .db 221
    .db 117
    .db 0
    .db 221
    .db 116
    .db 1
    ret 
PLY_AKG_PSES_NOTREACHED: inc +3(ix)
    ret 
PLY_AKG_PSES_SOFTWAREORSOFTWAREANDHARDWARE: rra 
    call PLY_AKG_PSES_MANAGEVOLUMEFROMA_FILTER4BITS
    rl b
    call c,PLY_AKG_PSES_READNOISEANDOPENNOISECHANNEL
    res 2,c
    call PLY_AKG_PSES_READSOFTWAREPERIOD
    jr PLY_AKG_PSES_SAVEPOINTERANDEXIT
PLY_AKG_PSES_READNOISEANDOPENNOISECHANNEL: ld a,(hl)
    ld (PLY_AKG_PSGREG6),a
    inc hl
    res 5,c
    ret 
PLY_AKG_PSES_READSOFTWAREPERIOD: ld a,(hl)
    inc hl
    exx
    ld (hl),a
    inc hl
    exx
    ld a,(hl)
    inc hl
    exx
    ld (hl),a
    exx
    ret 
PLY_AKG_PSES_MANAGEVOLUMEFROMA_FILTER4BITS: and #15
PLY_AKG_PSES_MANAGEVOLUMEFROMA_HARD: sub +2(ix)
    jr nc,PLY_AKG_PSES_MVFA_NOOVERFLOW
    xor a
PLY_AKG_PSES_MVFA_NOOVERFLOW: ld +0(iy),a
    ret 
PLY_AKG_CHANNEL1_SOUNDEFFECTDATA: .dw 0
PLY_AKG_CHANNEL1_SOUNDEFFECTINVERTEDVOLUME: .db 0
PLY_AKG_CHANNEL1_SOUNDEFFECTCURRENTSTEP: .db 0
PLY_AKG_CHANNEL1_SOUNDEFFECTSPEED: .db 0
    .db 0
    .db 0
    .db 0
PLY_AKG_CHANNEL2_SOUNDEFFECTDATA: .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
PLY_AKG_CHANNEL3_SOUNDEFFECTDATA: .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
    .db 0
_PLY_AKG_INIT::
        pop  af          ;; AF = Return address
		pop  hl          ;; HL = Music address
		pop  bc          ;; Rubbish  / C  = Subsong index (>=0)
		push af          ;; Save back return address in the stack to fullfill __z88dk_callee convention
		ld   a, c        ;; A = Subsong index
PLY_AKG_INIT: ld de,#4
    add hl,de
    inc hl
    inc hl
    inc hl
    inc hl
    ld de,#PLY_AKG_INSTRUMENTSTABLE+1
    ldi
    ldi
    ld c,(hl)
    inc hl
    ld b,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS1+1),bc
    ld (PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS2+1),bc
    add a,a
    ld e,a
    ld d,#0
    add hl,de
    ld a,(hl)
    inc hl
    ld h,(hl)
    ld l,a
    ld de,#5
    add hl,de
    ld de,#PLY_AKG_CHANNEL3_READCELLEND+1
    ldi
    ld de,#PLY_AKG_CHANNEL1_NOTE+1
    ldi
    ld (PLY_AKG_READLINKER+1),hl
    ld hl,#PLY_AKG_INITTABLE0
    ld bc,#1792
    call PLY_AKG_INIT_READWORDSANDFILL
    inc c
    ld hl,#PLY_AKG_INITTABLE0_END
    ld b,#3
    call PLY_AKG_INIT_READWORDSANDFILL
    ld hl,#PLY_AKG_INITTABLE1_END
    ld bc,#439
    call PLY_AKG_INIT_READWORDSANDFILL
    ld hl,(PLY_AKG_INSTRUMENTSTABLE+1)
    ld e,(hl)
    inc hl
    ld d,(hl)
    ex de,hl
    inc hl
    ld (PLY_AKG_ENDWITHOUTLOOP+1),hl
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),hl
    ld hl,#0
    ld (PLY_AKG_CHANNEL1_SOUNDEFFECTDATA),hl
    ld (PLY_AKG_CHANNEL2_SOUNDEFFECTDATA),hl
    ld (PLY_AKG_CHANNEL3_SOUNDEFFECTDATA),hl
    ret 
PLY_AKG_INIT_READWORDSANDFILL_LOOP: ld e,(hl)
    inc hl
    ld d,(hl)
    inc hl
    ld a,c
    ld (de),a
PLY_AKG_INIT_READWORDSANDFILL: djnz PLY_AKG_INIT_READWORDSANDFILL_LOOP
    ret 
PLY_AKG_INITTABLE0: .dw PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGERANDDECIMAL+1
    .dw PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGER
    .dw PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGERANDDECIMAL+1
    .dw PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGER
    .dw PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGERANDDECIMAL+1
    .dw PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGER
PLY_AKG_INITTABLE0_END:
PLY_AKG_INITTABLE1: .dw PLY_AKG_PATTERNDECREASINGHEIGHT+1
    .dw PLY_AKG_TICKDECREASINGCOUNTER+1
PLY_AKG_INITTABLE1_END:
PLY_AKG_INITTABLEORA:
PLY_AKG_INITTABLEORA_END:
_PLY_AKG_STOP::
PLY_AKG_STOP: ld (PLY_AKG_SAVESP+1),sp
    xor a
    ld l,a
    ld h,a
    ld (PLY_AKG_PSGREG8),a
    ld (PLY_AKG_PSGREG9),hl
    ld a,#63
    jp PLY_AKG_SENDPSGREGISTERS
_PLY_AKG_PLAY::
PLY_AKG_PLAY: ld (PLY_AKG_SAVESP+1),sp
PLY_AKG_TICKDECREASINGCOUNTER: ld a,#1
    dec a
    jp nz,PLY_AKG_SETSPEEDBEFOREPLAYSTREAMS
PLY_AKG_PATTERNDECREASINGHEIGHT: ld a,#1
    dec a
    jr nz,PLY_AKG_SETCURRENTLINEBEFOREREADLINE
PLY_AKG_READLINKER:
PLY_AKG_READLINKER_PTLINKER: ld sp,#0
    pop hl
    ld a,l
    or h
    jr nz,PLY_AKG_READLINKER_NOLOOP
    pop hl
    ld sp,hl
    pop hl
PLY_AKG_READLINKER_NOLOOP: ld (PLY_AKG_CHANNEL1_READTRACK+1),hl
    pop hl
    ld (PLY_AKG_CHANNEL2_READTRACK+1),hl
    pop hl
    ld (PLY_AKG_CHANNEL3_READTRACK+1),hl
    pop hl
    ld (PLY_AKG_READLINKER+1),sp
    ld sp,hl
    pop hl
    ld c,l
    pop hl
    pop hl
    ld (PLY_AKG_SPEEDTRACK_PTTRACK+1),hl
    xor a
    ld (PLY_AKG_READLINE+1),a
    ld (PLY_AKG_SPEEDTRACK_END+1),a
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    ld a,c
PLY_AKG_SETCURRENTLINEBEFOREREADLINE: ld (PLY_AKG_PATTERNDECREASINGHEIGHT+1),a
PLY_AKG_READLINE:
PLY_AKG_SPEEDTRACK_WAITCOUNTER: ld a,#0
    sub #1
    jr nc,PLY_AKG_SPEEDTRACK_MUSTWAIT
PLY_AKG_SPEEDTRACK_PTTRACK: ld hl,#0
    ld a,(hl)
    inc hl
    srl a
    jr c,PLY_AKG_SPEEDTRACK_STOREPOINTERANDWAITCOUNTER
    jr nz,PLY_AKG_SPEEDTRACK_NORMALVALUE
    ld a,(hl)
    inc hl
PLY_AKG_SPEEDTRACK_NORMALVALUE: ld (PLY_AKG_CHANNEL3_READCELLEND+1),a
    xor a
PLY_AKG_SPEEDTRACK_STOREPOINTERANDWAITCOUNTER: ld (PLY_AKG_SPEEDTRACK_PTTRACK+1),hl
PLY_AKG_SPEEDTRACK_MUSTWAIT: ld (PLY_AKG_READLINE+1),a
PLY_AKG_SPEEDTRACK_END:
PLY_AKG_CHANNEL1_WAITCOUNTER: ld a,#0
    sub #1
    jr c,PLY_AKG_CHANNEL1_READTRACK
    ld (PLY_AKG_SPEEDTRACK_END+1),a
    jp PLY_AKG_CHANNEL1_READCELLEND
PLY_AKG_CHANNEL1_READTRACK:
PLY_AKG_CHANNEL1_PTTRACK: ld hl,#0
    ld c,(hl)
    inc hl
    ld a,c
    and #63
    cp #60
    jr c,PLY_AKG_CHANNEL1_NOTE
    sub #60
    jp z,PLY_AKG_CHANNEL1_MAYBEEFFECTS
    dec a
    jr z,PLY_AKG_CHANNEL1_WAIT
    dec a
    jr z,PLY_AKG_CHANNEL1_SMALLWAIT
    ld a,(hl)
    inc hl
    jr PLY_AKG_CHANNEL1_AFTERNOTEKNOWN
PLY_AKG_CHANNEL1_SMALLWAIT: ld a,c
    rlca 
    rlca 
    and #3
    inc a
    ld (PLY_AKG_SPEEDTRACK_END+1),a
    jr PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL1_WAIT: ld a,(hl)
    ld (PLY_AKG_SPEEDTRACK_END+1),a
    inc hl
    jr PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL1_SAMEINSTRUMENT:
PLY_AKG_CHANNEL1_PTBASEINSTRUMENT: ld de,#0
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),de
    jr PLY_AKG_CHANNEL1_AFTERINSTRUMENT
PLY_AKG_CHANNEL1_NOTE:
PLY_AKG_BASENOTEINDEX: add a,#0
PLY_AKG_CHANNEL1_AFTERNOTEKNOWN: ld (PLY_AKG_CHANNEL1_TRACKNOTE+1),a
    rl c
    jr nc,PLY_AKG_CHANNEL1_SAMEINSTRUMENT
    ld a,(hl)
    inc hl
    exx
    ld l,a
    ld h,#0
    add hl,hl
PLY_AKG_INSTRUMENTSTABLE: ld de,#0
    add hl,de
    ld sp,hl
    pop hl
    ld a,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL1_INSTRUMENTSPEED+1),a
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL1_SAMEINSTRUMENT+1),hl
    exx
PLY_AKG_CHANNEL1_AFTERINSTRUMENT: ex de,hl
    xor a
    ld (PLY_AKG_CHANNEL1_INSTRUMENTSTEP+2),a
    ex de,hl
    rl c
    jp c,PLY_AKG_CHANNEL1_READEFFECTS
PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER: ld (PLY_AKG_CHANNEL1_READTRACK+1),hl
PLY_AKG_CHANNEL1_READCELLEND:
PLY_AKG_CHANNEL2_WAITCOUNTER: ld a,#0
    sub #1
    jr c,PLY_AKG_CHANNEL2_READTRACK
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    jp PLY_AKG_CHANNEL2_READCELLEND
PLY_AKG_CHANNEL2_READTRACK:
PLY_AKG_CHANNEL2_PTTRACK: ld hl,#0
    ld c,(hl)
    inc hl
    ld a,c
    and #63
    cp #60
    jr c,PLY_AKG_CHANNEL2_NOTE
    sub #60
    jp z,PLY_AKG_CHANNEL1_READEFFECTSEND
    dec a
    jr z,PLY_AKG_CHANNEL2_WAIT
    dec a
    jr z,PLY_AKG_CHANNEL2_SMALLWAIT
    ld a,(hl)
    inc hl
    jr PLY_AKG_CHANNEL2_AFTERNOTEKNOWN
PLY_AKG_CHANNEL2_SMALLWAIT: ld a,c
    rlca 
    rlca 
    and #3
    inc a
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    jr PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL2_WAIT: ld a,(hl)
    ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    inc hl
    jr PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL2_SAMEINSTRUMENT:
PLY_AKG_CHANNEL2_PTBASEINSTRUMENT: ld de,#0
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),de
    jr PLY_AKG_CHANNEL2_AFTERINSTRUMENT
PLY_AKG_CHANNEL2_NOTE: ld b,a
    ld a,(PLY_AKG_CHANNEL1_NOTE+1)
    add a,b
PLY_AKG_CHANNEL2_AFTERNOTEKNOWN: ld (PLY_AKG_CHANNEL2_TRACKNOTE+1),a
    rl c
    jr nc,PLY_AKG_CHANNEL2_SAMEINSTRUMENT
    ld a,(hl)
    inc hl
    exx
    ld e,a
    ld d,#0
    ld hl,(PLY_AKG_INSTRUMENTSTABLE+1)
    add hl,de
    add hl,de
    ld sp,hl
    pop hl
    ld a,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL2_INSTRUMENTSPEED+1),a
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL2_SAMEINSTRUMENT+1),hl
    exx
PLY_AKG_CHANNEL2_AFTERINSTRUMENT: ex de,hl
    xor a
    ld (PLY_AKG_CHANNEL2_INSTRUMENTSTEP+2),a
    ex de,hl
    rl c
    jp c,PLY_AKG_CHANNEL2_READEFFECTS
PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER: ld (PLY_AKG_CHANNEL2_READTRACK+1),hl
PLY_AKG_CHANNEL2_READCELLEND:
PLY_AKG_CHANNEL3_WAITCOUNTER: ld a,#0
    sub #1
    jr c,PLY_AKG_CHANNEL3_READTRACK
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    jp PLY_AKG_CHANNEL3_READCELLEND
PLY_AKG_CHANNEL3_READTRACK:
PLY_AKG_CHANNEL3_PTTRACK: ld hl,#0
    ld c,(hl)
    inc hl
    ld a,c
    and #63
    cp #60
    jr c,PLY_AKG_CHANNEL3_NOTE
    sub #60
    jp z,PLY_AKG_CHANNEL2_READEFFECTSEND
    dec a
    jr z,PLY_AKG_CHANNEL3_WAIT
    dec a
    jr z,PLY_AKG_CHANNEL3_SMALLWAIT
    ld a,(hl)
    inc hl
    jr PLY_AKG_CHANNEL3_AFTERNOTEKNOWN
PLY_AKG_CHANNEL3_SMALLWAIT: ld a,c
    rlca 
    rlca 
    and #3
    inc a
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    jr PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_WAIT: ld a,(hl)
    ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    inc hl
    jr PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_SAMEINSTRUMENT:
PLY_AKG_CHANNEL3_PTBASEINSTRUMENT: ld de,#0
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),de
    jr PLY_AKG_CHANNEL3_AFTERINSTRUMENT
PLY_AKG_CHANNEL3_NOTE: ld b,a
    ld a,(PLY_AKG_CHANNEL1_NOTE+1)
    add a,b
PLY_AKG_CHANNEL3_AFTERNOTEKNOWN: ld (PLY_AKG_CHANNEL3_TRACKNOTE+1),a
    rl c
    jr nc,PLY_AKG_CHANNEL3_SAMEINSTRUMENT
    ld a,(hl)
    inc hl
    exx
    ld e,a
    ld d,#0
    ld hl,(PLY_AKG_INSTRUMENTSTABLE+1)
    add hl,de
    add hl,de
    ld sp,hl
    pop hl
    ld a,(hl)
    inc hl
    ld (PLY_AKG_CHANNEL3_INSTRUMENTSPEED+1),a
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),hl
    ld (PLY_AKG_CHANNEL3_SAMEINSTRUMENT+1),hl
    exx
PLY_AKG_CHANNEL3_AFTERINSTRUMENT: ex de,hl
    xor a
    ld (PLY_AKG_CHANNEL3_INSTRUMENTSTEP+2),a
    ex de,hl
    rl c
    jp c,PLY_AKG_CHANNEL3_READEFFECTS
PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER: ld (PLY_AKG_CHANNEL3_READTRACK+1),hl
PLY_AKG_CHANNEL3_READCELLEND:
PLY_AKG_CURRENTSPEED: ld a,#0
PLY_AKG_SETSPEEDBEFOREPLAYSTREAMS: ld (PLY_AKG_TICKDECREASINGCOUNTER+1),a
PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGER = .+2
PLY_AKG_CHANNEL1_INVERTEDVOLUMEINTEGERANDDECIMAL: ld hl,#0
    ld a,h
    ld (PLY_AKG_CHANNEL1_GENERATEDCURRENTINVERTEDVOLUME+1),a
    ld de,#0
    ld hl,#0
PLY_AKG_CHANNEL1_SOUNDSTREAM_RELATIVEMODIFIERADDRESS: add hl,de
    ld (PLY_AKG_CHANNEL1_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS+1),hl
PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGER = .+2
PLY_AKG_CHANNEL2_INVERTEDVOLUMEINTEGERANDDECIMAL: ld hl,#0
    ld a,h
    ld (PLY_AKG_CHANNEL2_GENERATEDCURRENTINVERTEDVOLUME+1),a
    ld de,#0
    ld hl,#0
PLY_AKG_CHANNEL2_SOUNDSTREAM_RELATIVEMODIFIERADDRESS: add hl,de
    ld (PLY_AKG_CHANNEL2_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS+1),hl
PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGER = .+2
PLY_AKG_CHANNEL3_INVERTEDVOLUMEINTEGERANDDECIMAL: ld hl,#0
    ld a,h
    ld (PLY_AKG_CHANNEL3_GENERATEDCURRENTINVERTEDVOLUME+1),a
    ld de,#0
    ld hl,#0
PLY_AKG_CHANNEL3_SOUNDSTREAM_RELATIVEMODIFIERADDRESS: add hl,de
    ld (PLY_AKG_CHANNEL3_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS+1),hl
    ld sp,(PLY_AKG_SAVESP+1)
PLY_AKG_CHANNEL1_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS:
PLY_AKG_CHANNEL1_GENERATEDCURRENTPITCH: ld hl,#0
PLY_AKG_CHANNEL1_TRACKNOTE: ld de,#0
    exx
PLY_AKG_CHANNEL1_INSTRUMENTSTEP: .db 253
    .db 46
    .db 0
PLY_AKG_CHANNEL1_PTINSTRUMENT: ld hl,#0
PLY_AKG_CHANNEL1_GENERATEDCURRENTINVERTEDVOLUME: ld de,#57359
    call PLY_AKG_READINSTRUMENTCELL
    .db 253
    .db 125
    inc a
PLY_AKG_CHANNEL1_INSTRUMENTSPEED: cp #0
    jr c,PLY_AKG_CHANNEL1_SETINSTRUMENTSTEP
    ld (PLY_AKG_CHANNEL1_PTINSTRUMENT+1),hl
    xor a
PLY_AKG_CHANNEL1_SETINSTRUMENTSTEP: ld (PLY_AKG_CHANNEL1_INSTRUMENTSTEP+2),a
    ld a,e
    ld (PLY_AKG_PSGREG8),a
    srl d
    exx
    ld (PLY_AKG_PSGREG01_INSTR+1),hl
PLY_AKG_CHANNEL2_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS:
PLY_AKG_CHANNEL2_GENERATEDCURRENTPITCH: ld hl,#0
PLY_AKG_CHANNEL2_TRACKNOTE: ld de,#0
    exx
PLY_AKG_CHANNEL2_INSTRUMENTSTEP: .db 253
    .db 46
    .db 0
PLY_AKG_CHANNEL2_PTINSTRUMENT: ld hl,#0
PLY_AKG_CHANNEL2_GENERATEDCURRENTINVERTEDVOLUME: ld e,#15
    nop
    call PLY_AKG_READINSTRUMENTCELL
    .db 253
    .db 125
    inc a
PLY_AKG_CHANNEL2_INSTRUMENTSPEED: cp #0
    jr c,PLY_AKG_CHANNEL2_SETINSTRUMENTSTEP
    ld (PLY_AKG_CHANNEL2_PTINSTRUMENT+1),hl
    xor a
PLY_AKG_CHANNEL2_SETINSTRUMENTSTEP: ld (PLY_AKG_CHANNEL2_INSTRUMENTSTEP+2),a
    ld a,e
    ld (PLY_AKG_PSGREG9),a
    srl d
    exx
    ld (PLY_AKG_PSGREG23_INSTR+1),hl
PLY_AKG_CHANNEL3_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS:
PLY_AKG_CHANNEL3_GENERATEDCURRENTPITCH: ld hl,#0
PLY_AKG_CHANNEL3_TRACKNOTE: ld de,#0
    exx
PLY_AKG_CHANNEL3_INSTRUMENTSTEP: .db 253
    .db 46
    .db 0
PLY_AKG_CHANNEL3_PTINSTRUMENT: ld hl,#0
PLY_AKG_CHANNEL3_GENERATEDCURRENTINVERTEDVOLUME: ld e,#15
    nop
    call PLY_AKG_READINSTRUMENTCELL
    .db 253
    .db 125
    inc a
PLY_AKG_CHANNEL3_INSTRUMENTSPEED: cp #0
    jr c,PLY_AKG_CHANNEL3_SETINSTRUMENTSTEP
    ld (PLY_AKG_CHANNEL3_PTINSTRUMENT+1),hl
    xor a
PLY_AKG_CHANNEL3_SETINSTRUMENTSTEP: ld (PLY_AKG_CHANNEL3_INSTRUMENTSTEP+2),a
    ld a,e
    ld (PLY_AKG_PSGREG10),a
    ld a,d
    exx
    ld (PLY_AKG_PSGREG45_INSTR+1),hl
    call PLY_AKG_PLAYSOUNDEFFECTSSTREAM
PLY_AKG_SENDPSGREGISTERS: ld bc,#63104
    ld e,#192
    out (c),e
    exx
    ld bc,#62465
PLY_AKG_PSGREG01_INSTR: ld hl,#0
    .db 237
    .db 113
    exx
    .db 237
    .db 113
    exx
    out (c),l
    exx
    out (c),c
    out (c),e
    exx
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),h
    exx
    out (c),c
    out (c),e
    exx
PLY_AKG_PSGREG23_INSTR: ld hl,#0
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),l
    exx
    out (c),c
    out (c),e
    exx
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),h
    exx
    out (c),c
    out (c),e
    exx
PLY_AKG_PSGREG45_INSTR: ld hl,#0
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),l
    exx
    out (c),c
    out (c),e
    exx
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),h
    exx
    out (c),c
    out (c),e
    exx
PLY_AKG_PSGREG6 = .+1
PLY_AKG_PSGREG8 = .+2
PLY_AKG_PSGREG6_8_INSTR: ld hl,#0
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),l
    exx
    out (c),c
    out (c),e
    exx
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),a
    exx
    out (c),c
    out (c),e
    exx
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),h
    exx
    out (c),c
    out (c),e
    exx
PLY_AKG_PSGREG9 = .+1
PLY_AKG_PSGREG10 = .+2
PLY_AKG_PSGREG9_10_INSTR: ld hl,#0
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),l
    exx
    out (c),c
    out (c),e
    exx
    inc c
    out (c),c
    exx
    .db 237
    .db 113
    exx
    out (c),h
    exx
    out (c),c
    out (c),e
    exx
PLY_AKG_SAVESP: ld sp,#0
    ret 
PLY_AKG_CHANNEL1_MAYBEEFFECTS: ld (PLY_AKG_SPEEDTRACK_END+1),a
    bit 6,c
    jp z,PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL1_READEFFECTS: ld iy,#PLY_AKG_CHANNEL1_SOUNDSTREAM_RELATIVEMODIFIERADDRESS
    ld ix,#PLY_AKG_CHANNEL1_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS
    ld de,#PLY_AKG_CHANNEL1_BEFOREEND_STORECELLPOINTER
    jr PLY_AKG_CHANNEL3_READEFFECTSEND
PLY_AKG_CHANNEL1_READEFFECTSEND:
PLY_AKG_CHANNEL2_MAYBEEFFECTS: ld (PLY_AKG_CHANNEL1_READCELLEND+1),a
    bit 6,c
    jp z,PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL2_READEFFECTS: ld iy,#PLY_AKG_CHANNEL2_SOUNDSTREAM_RELATIVEMODIFIERADDRESS
    ld ix,#PLY_AKG_CHANNEL2_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS
    ld de,#PLY_AKG_CHANNEL2_BEFOREEND_STORECELLPOINTER
    jr PLY_AKG_CHANNEL3_READEFFECTSEND
PLY_AKG_CHANNEL2_READEFFECTSEND:
PLY_AKG_CHANNEL3_MAYBEEFFECTS: ld (PLY_AKG_CHANNEL2_READCELLEND+1),a
    bit 6,c
    jp z,PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_READEFFECTS: ld iy,#PLY_AKG_CHANNEL3_SOUNDSTREAM_RELATIVEMODIFIERADDRESS
    ld ix,#PLY_AKG_CHANNEL3_PLAYINSTRUMENT_RELATIVEMODIFIERADDRESS
    ld de,#PLY_AKG_CHANNEL3_BEFOREEND_STORECELLPOINTER
PLY_AKG_CHANNEL3_READEFFECTSEND:
PLY_AKG_CHANNEL_READEFFECTS: ld (PLY_AKG_CHANNEL_READEFFECTS_ENDJUMP+1),de
    ex de,hl
    ld a,(de)
    inc de
    sla a
    jr c,PLY_AKG_CHANNEL_READEFFECTS_RELATIVEADDRESS
    exx
    ld l,a
    ld h,#0
PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS1: ld de,#0
    add hl,de
    ld e,(hl)
    inc hl
    ld d,(hl)
PLY_AKG_CHANNEL_RE_EFFECTADDRESSKNOWN: ld a,(de)
    inc de
    ld (PLY_AKG_CHANNEL_RE_EFFECTRETURN+1),a
    and #254
    ld l,a
    ld h,#0
    ld sp,#PLY_AKG_EFFECTTABLE
    add hl,sp
    ld sp,hl
    ret 
PLY_AKG_CHANNEL_RE_EFFECTRETURN:
PLY_AKG_CHANNEL_RE_READNEXTEFFECTINBLOCK: ld a,#0
    rra 
    jr c,PLY_AKG_CHANNEL_RE_EFFECTADDRESSKNOWN
    exx
    ex de,hl
PLY_AKG_CHANNEL_READEFFECTS_ENDJUMP: jp 0
PLY_AKG_CHANNEL_READEFFECTS_RELATIVEADDRESS: srl a
    exx
    ld h,a
    exx
    ld a,(de)
    inc de
    exx
    ld l,a
PLY_AKG_CHANNEL_READEFFECTS_EFFECTBLOCKS2: ld de,#0
    add hl,de
    jr PLY_AKG_CHANNEL_RE_EFFECTADDRESSKNOWN
PLY_AKG_READINSTRUMENTCELL: ld a,(hl)
    inc hl
    ld b,a
    rra 
    jp c,PLY_AKG_S_OR_H_OR_SAH_OR_ENDWITHLOOP
    rra 
    jr c,PLY_AKG_STH_OR_ENDWITHOUTLOOP
    rra 
PLY_AKG_NOSOFTNOHARD: and #15
    sub e
    jr nc,PLY_AKG_NOSOFTNOHARD+6
    xor a
    ld e,a
    rl b
    jr nc,PLY_AKG_NSNH_NONOISE
    ld a,(hl)
    inc hl
    ld (PLY_AKG_PSGREG6),a
    set 2,d
    res 5,d
    ret 
PLY_AKG_NSNH_NONOISE: set 2,d
    ret 
PLY_AKG_SOFT: and #15
    sub e
    jr nc,PLY_AKG_SOFTONLY_HARDONLY_TESTSIMPLE_COMMON-1
    xor a
    ld e,a
PLY_AKG_SOFTONLY_HARDONLY_TESTSIMPLE_COMMON: rl b
    jr nc,PLY_AKG_S_NOTSIMPLE
    ld c,#0
    jr PLY_AKG_S_AFTERSIMPLETEST
PLY_AKG_S_NOTSIMPLE: ld b,(hl)
    ld c,b
    inc hl
PLY_AKG_S_AFTERSIMPLETEST: call PLY_AKG_H_OR_ENDWITHLOOP
    ret 
PLY_AKG_ENDWITHOUTLOOP:
PLY_AKG_EMPTYINSTRUMENTDATAPT: ld hl,#0
    inc hl
    xor a
    ld b,a
    jr PLY_AKG_NOSOFTNOHARD
PLY_AKG_STH_OR_ENDWITHOUTLOOP: rra 
    jr PLY_AKG_ENDWITHOUTLOOP
PLY_AKG_S_OR_H_OR_SAH_OR_ENDWITHLOOP: rra 
    jr c,PLY_AKG_H_OR_ENDWITHLOOP
    rra 
    jp nc,PLY_AKG_SOFT
PLY_AKG_H_OR_ENDWITHLOOP:
PLY_AKG_S_OR_H_CHECKIFSIMPLEFIRST_CALCULATEPERIOD: exx
    ex de,hl
    add hl,hl
    ld bc,#PLY_AKG_PERIODTABLE
    add hl,bc
    ld a,(hl)
    inc hl
    ld h,(hl)
    ld l,a
    add hl,de
    exx
    rl b
    rl b
    rl b
    ret 
PLY_AKG_EFFECTTABLE: .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw PLY_AKG_EFFECT_VOLUME
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
    .dw DRROLANDSOUNDTRACK_START
PLY_AKG_EFFECT_VOLUME: ld a,(de)
    inc de
    ld -11(iy),a
    jp PLY_AKG_CHANNEL_RE_EFFECTRETURN
PLY_AKG_PERIODTABLE: .dw 3822
    .dw 3608
    .dw 3405
    .dw 3214
    .dw 3034
    .dw 2863
    .dw 2703
    .dw 2551
    .dw 2408
    .dw 2273
    .dw 2145
    .dw 2025
    .dw 1911
    .dw 1804
    .dw 1703
    .dw 1607
    .dw 1517
    .dw 1432
    .dw 1351
    .dw 1276
    .dw 1204
    .dw 1136
    .dw 1073
    .dw 1012
    .dw 956
    .dw 902
    .dw 851
    .dw 804
    .dw 758
    .dw 716
    .dw 676
    .dw 638
    .dw 602
    .dw 568
    .dw 536
    .dw 506
    .dw 478
    .dw 451
    .dw 426
    .dw 402
    .dw 379
    .dw 358
    .dw 338
    .dw 319
    .dw 301
    .dw 284
    .dw 268
    .dw 253
    .dw 239
    .dw 225
    .dw 213
    .dw 201
    .dw 190
    .dw 179
    .dw 169
    .dw 159
    .dw 150
    .dw 142
    .dw 134
    .dw 127
    .dw 119
    .dw 113
    .dw 106
    .dw 100
    .dw 95
    .dw 89
    .dw 84
    .dw 80
    .dw 75
    .dw 71
    .dw 67
    .dw 63
    .dw 60
    .dw 56
    .dw 53
    .dw 50
    .dw 47
    .dw 45
    .dw 42
    .dw 40
    .dw 38
    .dw 36
    .dw 34
    .dw 32
    .dw 30
    .dw 28
    .dw 27
    .dw 25
    .dw 24
    .dw 22
    .dw 21
    .dw 20
    .dw 19
    .dw 18
    .dw 17
    .dw 16
    .dw 15
    .dw 14
    .dw 13
    .dw 13
    .dw 12
    .dw 11
    .dw 11
    .dw 10
    .dw 9
    .dw 9
    .dw 8
    .dw 8
    .dw 7
    .dw 7
    .dw 7
    .dw 6
    .dw 6
    .dw 6
    .dw 5
    .dw 5
    .dw 5
    .dw 4
    .dw 4
    .dw 4
    .dw 4
    .dw 4
    .dw 3
    .dw 3
    .dw 3
    .dw 3
    .dw 3
    .dw 2
