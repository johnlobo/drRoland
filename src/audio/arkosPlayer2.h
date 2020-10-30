extern void PLY_AKM_INITSOUNDEFFECTS(void* sfx_song_data) __z88dk_fastcall;
extern void PLY_AKM_PLAYSOUNDEFFECT(u16 sfx_num, u8 volume, u8 channel) __z88dk_callee;
extern void PLY_AKM_STOPSOUNDEFFECTFROMCHANNEL(u8 channel) __z88dk_fastcall;

extern void PLY_AKM_INIT(void* songdata, u16 subSong) __z88dk_callee;
extern void PLY_AKM_PLAY();
extern void PLY_AKM_SLAY();
