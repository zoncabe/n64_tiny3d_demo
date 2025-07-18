#ifndef SOUND_H
#define SOUND_H

#include <libdragon.h>

#define MUSIC_CHANNEL 0
#define SFX_CHANNEL 31

xm64player_t xmPlayer;
wav64_t sfx_boing;

const char* xmFileNames[1] = {
    "rom:/game/sound/ene.xm64",
};

const char* wavFileNames[1] = {
    "rom:/game/sound/boing.wav64",
};

void sound_load(void);

void sound_load(void)
{
	wav64_open(&sfx_boing, wavFileNames[0]);
    xm64player_open(&xmPlayer, xmFileNames[0]);
    xm64player_play(&xmPlayer, MUSIC_CHANNEL);
}

void sound_xm_switch(int songID);

void sound_xm_switch(int songID)
{
    xm64player_stop(&xmPlayer);
	xm64player_close(&xmPlayer);
	xm64player_open(&xmPlayer, xmFileNames[songID]);
	xm64player_set_loop(&xmPlayer, true);
	xm64player_set_vol(&xmPlayer, 0.3f);
	xm64player_play(&xmPlayer, MUSIC_CHANNEL);
}

void sound_xm_stop(void);

void sound_xm_stop(void)
{
	xm64player_stop(&xmPlayer);
	xm64player_close(&xmPlayer);
}

void sound_xm_update(bool isLooping, float volume);

void sound_xm_update(bool isLooping, float volume)
{
	xm64player_set_loop(&xmPlayer, isLooping);
	xm64player_set_vol(&xmPlayer, volume);
}

void sound_wav_close(void);

void sound_wav_close(void)
{
	wav64_close(&sfx_boing);
}

void sound_wav_bounce(void);

void sound_wav_bounce(void)
{
	wav64_play(&sfx_boing, SFX_CHANNEL);
}

void sound_update_buffer(void);

void sound_update_buffer(void)
{
    /*if (audio_can_write()){
		short *buf = audio_write_begin();
		mixer_poll(buf, audio_get_buffer_length());
		audio_write_end();
	}*/
	mixer_try_play();
}

void sound_cleanup(void);

void sound_cleanup(void)
{
	sound_wav_close();
	sound_xm_stop();
}

#endif // SOUND_H