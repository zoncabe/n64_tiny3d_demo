#include <libdragon.h>
#include <t3d/t3danim.h>

#include "../../include/sound/sound.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"
#include "../../include/player/player_animation.h"

#define NUM_CHANNELS 16
#define FOOTSTEP_TRACK_COUNT 3
#define FOOTSTEPS_MAX_VOLUME 0.6f
#define FOOTSTEPS_MIN_VOLUME 0.3f

wav64_t sfx_footstepConcrete_01,
sfx_footstepConcrete_02,
sfx_footstepConcrete_03;

wav64_t reporte_universal;

int leftFootStep, rightFootStep;


void sound_init()
{
	audio_init(48000, 4);
	mixer_init(NUM_CHANNELS);
	wav64_init_compression(3);

	wav64_open(&sfx_footstepConcrete_01, "rom:/audio/concrete-footstep-1.wav64");
	wav64_open(&sfx_footstepConcrete_02, "rom:/audio/concrete-footstep-2.wav64");
	wav64_open(&sfx_footstepConcrete_03, "rom:/audio/concrete-footstep-3.wav64");
}


void sound_playFootstepTrack(int track, int channel)
{
	switch (track)
	{
		case 1: wav64_play(&sfx_footstepConcrete_01, channel); break;
		case 2: wav64_play(&sfx_footstepConcrete_02, channel); break;
		case 3: wav64_play(&sfx_footstepConcrete_03, channel); break;
	}
}

void sound_setFoostepVolume()
{
	float speed_sound_multiplier = player[0]->motion_data.horizontal_speed / player[0]->motion_settings.sprint_target_speed;
	mixer_ch_set_vol(SFX_CHANNEL_1, FOOTSTEPS_MAX_VOLUME * speed_sound_multiplier, FOOTSTEPS_MAX_VOLUME * speed_sound_multiplier);
}


void sound_setFoosteps(Player* player)
{
	sound_setFoostepVolume();
	if (player->armature.animation.current == WALKING) {

		if ((!leftFootStep) 
			&& player->armature.animation.set.walking.time >= t3d_anim_get_length(&player->armature.animation.set.walking) * 0.25f 
			&& player->armature.animation.set.walking.time < t3d_anim_get_length(&player->armature.animation.set.walking) * 0.75f) {

			leftFootStep = (int)(rand() % FOOTSTEP_TRACK_COUNT) + 1;
			sound_playFootstepTrack(leftFootStep, SFX_CHANNEL_1);
			if (rightFootStep) rightFootStep = 0;
		}
		
			
		if ((!rightFootStep) && player->armature.animation.set.walking.time >= t3d_anim_get_length(&player->armature.animation.set.walking) * 0.75f) {

			rightFootStep = (int)(rand() % FOOTSTEP_TRACK_COUNT) + 1;
			sound_playFootstepTrack(rightFootStep, SFX_CHANNEL_1);
			if (leftFootStep) leftFootStep = 0;
		}
	}

	 else if (player->armature.animation.current == RUNNING) {

		if ((!leftFootStep) 
			&& player->armature.animation.set.running.time >= t3d_anim_get_length(&player->armature.animation.set.running) * 0.25f
			&& player->armature.animation.set.running.time < t3d_anim_get_length(&player->armature.animation.set.running) * 0.75f) {

			leftFootStep = (int)(rand() % FOOTSTEP_TRACK_COUNT) + 1;
			sound_playFootstepTrack(leftFootStep, SFX_CHANNEL_1);
			if (rightFootStep) rightFootStep = 0;
		}

		if ((!rightFootStep) && player->armature.animation.set.running.time >= t3d_anim_get_length(&player->armature.animation.set.running) * 0.75f) {

			rightFootStep = (int)(rand() % FOOTSTEP_TRACK_COUNT) + 1;
			sound_playFootstepTrack(rightFootStep, SFX_CHANNEL_1);
			if (leftFootStep) leftFootStep = 0;
		}
	}

	else if (player->armature.animation.current == SPRINTING) {

		if ((!leftFootStep) 
			&& player->armature.animation.set.sprinting.time >= t3d_anim_get_length(&player->armature.animation.set.sprinting) * 0.25f
			&& player->armature.animation.set.sprinting.time < t3d_anim_get_length(&player->armature.animation.set.sprinting) * 0.75f) {

			leftFootStep = (int)(rand() % FOOTSTEP_TRACK_COUNT) + 1;
			sound_playFootstepTrack(leftFootStep, SFX_CHANNEL_1);
			if (rightFootStep) rightFootStep = 0;
		}

		if ((!rightFootStep) && player->armature.animation.set.sprinting.time >= t3d_anim_get_length(&player->armature.animation.set.sprinting) * 0.75f) {

			rightFootStep = (int)(rand() % FOOTSTEP_TRACK_COUNT) + 1;
			sound_playFootstepTrack(rightFootStep, SFX_CHANNEL_1);
			if (leftFootStep) leftFootStep = 0;
		}
	}

}

void sound_setMixer()
{
	sound_setFoosteps(player[0]);
}

void sound_play()
{
	mixer_try_play();
}