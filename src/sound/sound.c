#include <libdragon.h>
#include <t3d/t3danim.h>

#include "../../include/sound/sound.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"
#include "../../include/player/player_animation.h"

wav64_t sfx_footstepConcrete_01, sfx_footstepConcrete_02, sfx_footstepConcrete_03, sfx_footstepConcrete_04;

int leftFootStep, rightFootStep;


void sound_init()
{
	audio_init(48000, 4);
	mixer_init(3);
	wav64_init_compression(3);

	wav64_open(&sfx_footstepConcrete_01, "rom:/audio/concrete-footstep-1.wav64");
	wav64_open(&sfx_footstepConcrete_02, "rom:/audio/concrete-footstep-2.wav64");
	wav64_open(&sfx_footstepConcrete_03, "rom:/audio/concrete-footstep-3.wav64");
	wav64_open(&sfx_footstepConcrete_04, "rom:/audio/concrete-footstep-4.wav64");
}

void sound_setFoosteps(Player* player)
{
	if (player->armature.animation.current == WALKING) {

		if (player->armature.animation.set.walking.time < t3d_anim_get_length(&player->armature.animation.set.walking) * 0.5f) {

			if (rightFootStep) rightFootStep = 0;
			if (!leftFootStep) leftFootStep = (int)(rand() % 4) + 1;
			
			switch (leftFootStep)
			{
				case 1: wav64_play(&sfx_footstepConcrete_01, SFX_CHANNEL_1); break;
				case 2: wav64_play(&sfx_footstepConcrete_02, SFX_CHANNEL_1); break;
				case 3: wav64_play(&sfx_footstepConcrete_03, SFX_CHANNEL_1); break;
				case 4: wav64_play(&sfx_footstepConcrete_04, SFX_CHANNEL_1); break;
			}
		}
		
			
		if (player->armature.animation.set.walking.time >= t3d_anim_get_length(&player->armature.animation.set.walking) * 0.5f) {

			if (leftFootStep) leftFootStep = 0;
			if (!rightFootStep) rightFootStep = (int)(rand() % 4) + 1;
			
			switch (rightFootStep)
			{
				case 1: wav64_play(&sfx_footstepConcrete_01, SFX_CHANNEL_2); break;
				case 2: wav64_play(&sfx_footstepConcrete_02, SFX_CHANNEL_2); break;
				case 3: wav64_play(&sfx_footstepConcrete_03, SFX_CHANNEL_2); break;
				case 4: wav64_play(&sfx_footstepConcrete_04, SFX_CHANNEL_2); break;
			}
		}
	}

	if (player->armature.animation.current == RUNNING) {

		if (player->armature.animation.set.running.time < t3d_anim_get_length(&player->armature.animation.set.running) * 0.5f) {

			if (rightFootStep) rightFootStep = 0;
			if (!leftFootStep) leftFootStep = (int)(rand() % 4) + 1;
			
			switch (leftFootStep)
			{
				case 1: wav64_play(&sfx_footstepConcrete_01, SFX_CHANNEL_1); break;
				case 2: wav64_play(&sfx_footstepConcrete_02, SFX_CHANNEL_1); break;
				case 3: wav64_play(&sfx_footstepConcrete_03, SFX_CHANNEL_1); break;
				case 4: wav64_play(&sfx_footstepConcrete_04, SFX_CHANNEL_1); break;
			}
		}

		if (player->armature.animation.set.running.time >= t3d_anim_get_length(&player->armature.animation.set.running) * 0.5f) {

			if (leftFootStep) leftFootStep = 0;
			if (!rightFootStep) rightFootStep = (int)(rand() % 4) + 1;
			
			switch (rightFootStep)
			{
				case 1: wav64_play(&sfx_footstepConcrete_01, SFX_CHANNEL_2); break;
				case 2: wav64_play(&sfx_footstepConcrete_02, SFX_CHANNEL_2); break;
				case 3: wav64_play(&sfx_footstepConcrete_03, SFX_CHANNEL_2); break;
				case 4: wav64_play(&sfx_footstepConcrete_04, SFX_CHANNEL_2); break;
			}
		}
	}

	if (player->armature.animation.current == SPRINTING) {

		if (player->armature.animation.set.sprinting.time < t3d_anim_get_length(&player->armature.animation.set.sprinting) * 0.5f) {

			if (rightFootStep) rightFootStep = 0;
			if (!leftFootStep) leftFootStep = (rand() % 4) + 1;
			
			switch (leftFootStep)
			{
				case 1: wav64_play(&sfx_footstepConcrete_01, SFX_CHANNEL_1); break;
				case 2: wav64_play(&sfx_footstepConcrete_02, SFX_CHANNEL_1); break;
				case 3: wav64_play(&sfx_footstepConcrete_03, SFX_CHANNEL_1); break;
				case 4: wav64_play(&sfx_footstepConcrete_04, SFX_CHANNEL_1); break;
			}
		}

		if (player->armature.animation.set.sprinting.time >= t3d_anim_get_length(&player->armature.animation.set.sprinting) * 0.5f) {

			if (leftFootStep) leftFootStep = 0;
			if (!rightFootStep) rightFootStep = (rand() % 4) + 1;
			
			switch (rightFootStep)
			{
				case 1: wav64_play(&sfx_footstepConcrete_01, SFX_CHANNEL_2); break;
				case 2: wav64_play(&sfx_footstepConcrete_02, SFX_CHANNEL_2); break;
				case 3: wav64_play(&sfx_footstepConcrete_03, SFX_CHANNEL_2); break;
				case 4: wav64_play(&sfx_footstepConcrete_04, SFX_CHANNEL_2); break;
			}
		}
	}
	player->leftFootStep = leftFootStep;
	player->rightFootStep = rightFootStep;

}

void sound_play()
{
	sound_setFoosteps(player[0]);
	mixer_try_play();
}