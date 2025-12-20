#ifndef SOUND_H
#define SOUND_H

#include <libdragon.h>

#define SFX_CHANNEL_1 0
#define SFX_CHANNEL_2 2
#define MUSIC_CHANNEL_1 4
#define MUSIC_CHANNEL_2 6

extern wav64_t reporte_universal;

void sound_init();
void sound_setMixer();
void sound_play();

#endif