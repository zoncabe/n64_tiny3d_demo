#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"
#include "../../include/player/player_animation.h"
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"


// custom T3D function for my engine
void t3d_skeleton_blend_3(const T3DSkeleton *skelRes, const T3DSkeleton *skelA, const T3DSkeleton *skelB, const T3DSkeleton *skelC, float factorB, float factorC)
{
	for (int i = 0; i < skelRes->skeletonRef->boneCount; i++)
	{
		T3DBone *boneRes = &skelRes->bones[i];
		T3DBone *boneA = &skelA->bones[i];
		T3DBone *boneB = &skelB->bones[i];
		T3DBone *boneC = &skelC->bones[i];

		t3d_quat_nlerp(&boneRes->rotation, &boneA->rotation, &boneB->rotation, factorB);
		t3d_vec3_lerp(&boneRes->position, &boneA->position, &boneB->position, factorB);
		t3d_vec3_lerp(&boneRes->scale, &boneA->scale, &boneB->scale, factorB);

		t3d_quat_nlerp(&boneRes->rotation, &boneRes->rotation, &boneC->rotation, factorC);
		t3d_vec3_lerp(&boneRes->position, &boneRes->position, &boneC->position, factorC);
		t3d_vec3_lerp(&boneRes->scale, &boneRes->scale, &boneC->scale, factorC);
	}
}

// function implementations

void playerAnimationSet_init(T3DModel *model, PlayerAnimationSet *set)
{
	set->breathing_idle = t3d_anim_create(model, "breathing-idle");
	
	set->standing_idle_left = t3d_anim_create(model, "standing-idle-left");
	set->standing_idle_right = t3d_anim_create(model, "standing-idle-right");
	
	//set->transition_left = t3d_anim_create(model, "transition-left");
	//set->transition_right = t3d_anim_create(model, "transition-right");

	set->walking = t3d_anim_create(model, "walking");
	set->running = t3d_anim_create(model, "running");
	set->sprinting = t3d_anim_create(model, "sprinting");
	
	//set->stand_to_rolling_left = t3d_anim_create(model, "stand-to-roll-left");
	//set->stand_to_rolling_right = t3d_anim_create(model, "stand-to-roll-right");
	
	set->run_to_rolling_right = t3d_anim_create(model, "run-to-roll-right");
	set->run_to_rolling_left = t3d_anim_create(model, "run-to-roll-left");

	set->jump_left = t3d_anim_create(model, "jump-left");
	set->jump_right = t3d_anim_create(model, "jump-right");

	set->falling_left = t3d_anim_create(model, "falling-idle-left");
	set->falling_right = t3d_anim_create(model, "falling-idle-right");

	set->land_left = t3d_anim_create(model, "land-left");
	set->land_right = t3d_anim_create(model, "land-right");

	t3d_anim_set_looping(&set->stand_to_rolling_left, false);
	t3d_anim_set_looping(&set->stand_to_rolling_right, false);

	t3d_anim_set_looping(&set->run_to_rolling_left, false);
	t3d_anim_set_looping(&set->run_to_rolling_right, false);

	t3d_anim_set_looping(&set->jump_left, false);
	t3d_anim_set_looping(&set->jump_right, false);

	t3d_anim_set_looping(&set->land_left, false);
	t3d_anim_set_looping(&set->land_right, false);
}

void playerAnimationSet_attach(T3DSkeleton *main, T3DSkeleton *blend, T3DSkeleton *blend2, PlayerAnimationSet *set)
{
	t3d_anim_attach(&set->breathing_idle, main);
	
	t3d_anim_attach(&set->standing_idle_left, blend);
	t3d_anim_attach(&set->standing_idle_right, blend2);

	//t3d_anim_attach(&set->transition_left, blend);
	//t3d_anim_attach(&set->transition_right, blend2);

	t3d_anim_attach(&set->walking, blend);
	t3d_anim_attach(&set->running, main);
	t3d_anim_attach(&set->sprinting, blend);

	//t3d_anim_attach(&set->stand_to_rolling_left, blend);
	//t3d_anim_attach(&set->stand_to_rolling_right, blend2);
	
	t3d_anim_attach(&set->run_to_rolling_left, blend);
	t3d_anim_attach(&set->run_to_rolling_right, blend2);

	t3d_anim_attach(&set->jump_left, blend);
	t3d_anim_attach(&set->jump_right, blend2);

	t3d_anim_attach(&set->falling_left, blend);
	t3d_anim_attach(&set->falling_right, blend2);

	t3d_anim_attach(&set->land_left, blend);
	t3d_anim_attach(&set->land_right, blend2);
}

void playerAnimation_init(Player* player)
{
	player->armature.main = t3d_skeleton_create_buffered(player->actor.render_data.model, FB_COUNT);
	player->armature.blend = t3d_skeleton_clone(&player->armature.main, false);
	player->armature.blend2 = t3d_skeleton_clone(&player->armature.main, false);

	playerAnimationSet_init(player->actor.render_data.model, &player->armature.animation.set);

	playerAnimationSet_attach(&player->armature.main, &player->armature.blend, &player->armature.blend2, &player->armature.animation.set);
}


void playerAnimation_setLocomotionBlendingRatio(Player* player)
{
	if (player->motion_data.horizontal_speed == 0) player->armature.animation.locomotion_blending_ratio = 0;

	else if (player->motion_data.horizontal_speed <= player->motion_settings.walk_target_speed)
		player->armature.animation.locomotion_blending_ratio = (player->motion_data.horizontal_speed / player->motion_settings.walk_target_speed);

	else if (player->motion_data.horizontal_speed <= player->motion_settings.run_target_speed) 
		player->armature.animation.locomotion_blending_ratio = 1.0f - ((player->motion_data.horizontal_speed - player->motion_settings.walk_target_speed) / (player->motion_settings.run_target_speed - player->motion_settings.walk_target_speed));

	else
		player->armature.animation.locomotion_blending_ratio = ((player->motion_data.horizontal_speed - player->motion_settings.run_target_speed) / (player->motion_settings.sprint_target_speed - player->motion_settings.run_target_speed));

	if (player->armature.animation.locomotion_blending_ratio > 1.0f) player->armature.animation.locomotion_blending_ratio = 1.0f;
	if (player->armature.animation.locomotion_blending_ratio < 0.0f) player->armature.animation.locomotion_blending_ratio = 0.0f;
}

void playerAnimation_setFootingBlendingRatio(Player* player, float action_time, float action_lenght)
{
	float phase = 1 / action_lenght * action_time;

	if (phase <= 0.25f) player->armature.animation.footing_blending_ratio = 0.5f + 2.0f * phase;
	else if (phase <= 0.75f)player->armature.animation.footing_blending_ratio = 1.0f - 2.0f * (phase - 0.25f);
	else if (phase <= 1) player->armature.animation.footing_blending_ratio = 2.0f * (phase - 0.75f);
}

void playerAnimation_setRollingBlendingRatio(Player* player)
{
	if (player->motion_data.roll_timer < player->armature.animation.settings.run_to_rolling_anim_ground && player->armature.animation.roll_blending_ratio <= 1.0f) 
		player->armature.animation.roll_blending_ratio += (timer.delta / player->armature.animation.settings.run_to_rolling_anim_ground);
	if (player->motion_data.roll_timer > player->armature.animation.settings.run_to_rolling_anim_stand && player->armature.animation.roll_blending_ratio > 0.0f) 
		player->armature.animation.roll_blending_ratio -= (timer.delta / (2 * (player->armature.animation.settings.run_to_rolling_anim_lenght - player->armature.animation.settings.run_to_rolling_anim_stand)));
	
	if (player->armature.animation.roll_blending_ratio > 1.0f) {
		
		player->armature.animation.roll_blending_ratio = 1.0f;

		if (player->armature.animation.footing_blending_ratio < 0.5f) 
			t3d_anim_set_time(&player->armature.animation.set.running, player->armature.animation.settings.running_anim_length_half - (player->armature.animation.settings.run_to_rolling_anim_lenght - player->armature.animation.settings.run_to_rolling_anim_stand) + timer.delta);
		if (player->armature.animation.footing_blending_ratio >= 0.5f) 
			t3d_anim_set_time(&player->armature.animation.set.walking, player->armature.animation.settings.running_anim_length_half - (player->armature.animation.settings.run_to_rolling_anim_lenght - player->armature.animation.settings.run_to_rolling_anim_stand) + timer.delta);

		t3d_anim_set_time(&player->armature.animation.set.walking, (player->armature.animation.set.running.time * player->armature.animation.settings.run_to_walk_ratio));
		t3d_anim_set_time(&player->armature.animation.set.sprinting, (player->armature.animation.set.running.time * player->armature.animation.settings.run_to_sprint_ratio));			
	}

	if (player->armature.animation.roll_blending_ratio < 0.0f) player->armature.animation.roll_blending_ratio = 0.0f;
}

void playerAnimation_setJumpBlendingRatio(Player* player)
{
	if (player->armature.animation.jump_blending_ratio == player->armature.animation.settings.jump_max_blending_ratio) return;
	if (player->armature.animation.jump_blending_ratio < player->armature.animation.settings.jump_max_blending_ratio) player->armature.animation.jump_blending_ratio += (timer.delta / (player->armature.animation.settings.jump_anim_air - timer.delta));
	if (player->armature.animation.jump_blending_ratio > player->armature.animation.settings.jump_max_blending_ratio) player->armature.animation.jump_blending_ratio = player->armature.animation.settings.jump_max_blending_ratio;
}

void playerAnimation_setLandingBlendingRatio(Player* player)
{
	if (player->armature.animation.set.land_left.time > player->armature.animation.settings.land_anim_ground) {
		
		if (player->armature.animation.jump_blending_ratio > 0) player->armature.animation.jump_blending_ratio -= (timer.delta / (player->armature.animation.settings.land_anim_length - player->armature.animation.settings.land_anim_ground));
		else player->armature.animation.jump_blending_ratio = 0;
	}
}

void playerAnimation_setWalkingSpeed(Player* player)
{
	t3d_anim_set_speed(&player->armature.animation.set.walking, player->armature.animation.locomotion_blending_ratio);
}

void playerAnimation_setRunningSpeed(Player* player)
{
	player->armature.animation.speed = (1.0f - ((1.0f - player->armature.animation.settings.walk_to_run_ratio) * player->armature.animation.locomotion_blending_ratio));
	t3d_anim_set_speed(&player->armature.animation.set.running, player->armature.animation.speed);
	t3d_anim_set_speed(&player->armature.animation.set.walking, (player->armature.animation.speed * player->armature.animation.settings.run_to_walk_ratio));
}

void playerAnimation_setSprintingSpeed(Player* player)
{
	player->armature.animation.speed = (player->armature.animation.settings.run_to_sprint_ratio + ((1.0f - player->armature.animation.settings.run_to_sprint_ratio) * player->armature.animation.locomotion_blending_ratio));
	t3d_anim_set_speed(&player->armature.animation.set.running, (player->armature.animation.speed * player->armature.animation.settings.sprint_to_run_ratio));
	t3d_anim_set_speed(&player->armature.animation.set.sprinting, player->armature.animation.speed);
	t3d_anim_set_speed(&player->armature.animation.set.walking, (player->armature.animation.speed * player->armature.animation.settings.sprint_to_walk_ratio));
}


void playerAnimation_setStandingIdle(Player* player)
{
	t3d_anim_update(&player->armature.animation.set.breathing_idle, timer.delta);
	t3d_anim_update(&player->armature.animation.set.standing_idle_left, timer.delta);
	t3d_anim_update(&player->armature.animation.set.standing_idle_right, timer.delta);
	t3d_skeleton_blend_3(&player->armature.main, 
		&player->armature.main, 
		&player->armature.blend, 
		&player->armature.blend2, 
		player->armature.animation.settings.action_idle_max_blending_ratio * player->armature.animation.footing_blending_ratio, 
		player->armature.animation.settings.action_idle_max_blending_ratio * (1 - player->armature.animation.footing_blending_ratio));
}

void playerAnimation_setWalking(Player* player)
{
	//playerAnimation_setLocomotionBlendingRatio(player);
	//playerAnimation_setWalkingSpeed(player);
	t3d_anim_update(&player->armature.animation.set.walking, timer.delta);
	t3d_skeleton_blend(&player->armature.main, &player->armature.main, &player->armature.blend, player->armature.animation.locomotion_blending_ratio);
}

void playerAnimation_setRunning(Player* player)
{
	//playerAnimation_setLocomotionBlendingRatio(player);
	//playerAnimation_setRunningSpeed(player);
	t3d_anim_update(&player->armature.animation.set.running, timer.delta);
	t3d_anim_update(&player->armature.animation.set.walking, timer.delta);
	t3d_skeleton_blend(&player->armature.main, &player->armature.main, &player->armature.blend, player->armature.animation.locomotion_blending_ratio);
}

void playerAnimation_setSprinting(Player* player)
{
	//playerAnimation_setLocomotionBlendingRatio(player);
	//playerAnimation_setSprintingSpeed(player);
	t3d_anim_update(&player->armature.animation.set.running, timer.delta);
	t3d_anim_update(&player->armature.animation.set.sprinting, timer.delta);
	t3d_skeleton_blend(&player->armature.main, &player->armature.main, &player->armature.blend, player->armature.animation.locomotion_blending_ratio);
}

void playerAnimation_setRunToRoll(Player* player)
{
	playerAnimation_setRollingBlendingRatio(player);

	if (player->armature.animation.footing_blending_ratio <= 0.5f){
				
		playerAnimation_setRollingBlendingRatio(player);
		t3d_anim_update(&player->armature.animation.set.run_to_rolling_right, timer.delta);
		t3d_skeleton_blend(&player->armature.main, 
			&player->armature.main,
			&player->armature.blend2,
			player->armature.animation.roll_blending_ratio
		);
	}
	
	if (player->armature.animation.footing_blending_ratio > 0.5f){
			
		playerAnimation_setRollingBlendingRatio(player);
		t3d_anim_update(&player->armature.animation.set.run_to_rolling_left, timer.delta);
		t3d_skeleton_blend(&player->armature.main, 
			&player->armature.main, 
			&player->armature.blend,
			player->armature.animation.roll_blending_ratio
		);
	}
}

void playerAnimation_setFallingIdle(Player* player)
{
	t3d_anim_update(&player->armature.animation.set.falling_left, timer.delta);
	t3d_anim_update(&player->armature.animation.set.falling_right, timer.delta);
	t3d_skeleton_blend_3(&player->armature.main, 
		&player->armature.main, 
		&player->armature.blend, 
		&player->armature.blend2, 
		(player->armature.animation.jump_blending_ratio * player->armature.animation.footing_blending_ratio), 
		(player->armature.animation.jump_blending_ratio * (1 - player->armature.animation.footing_blending_ratio))
	);
}

void playerAnimation_setJump(Player* player)
{
	if ((player->armature.animation.set.jump_left.time + timer.delta) < player->armature.animation.settings.jump_anim_length){

		playerAnimation_setJumpBlendingRatio(player);
		t3d_anim_update(&player->armature.animation.set.jump_left, timer.delta);
		t3d_anim_update(&player->armature.animation.set.jump_right, timer.delta);
		t3d_skeleton_blend_3(&player->armature.main, 
			&player->armature.main,
			&player->armature.blend, 
			&player->armature.blend2, 
			(player->armature.animation.jump_blending_ratio * player->armature.animation.footing_blending_ratio), 
			(player->armature.animation.jump_blending_ratio * fabs(1 - player->armature.animation.footing_blending_ratio))
		);
	}
	else playerAnimation_setFallingIdle(player);
}

void playerAnimation_setLanding(Player* player)
{		
	playerAnimation_setLandingBlendingRatio(player);
	t3d_anim_update(&player->armature.animation.set.land_left, timer.delta);
	t3d_anim_update(&player->armature.animation.set.land_right, timer.delta);
	t3d_skeleton_blend_3(&player->armature.main, 
		&player->armature.main, 
		&player->armature.blend, 
		&player->armature.blend2, 
		(player->armature.animation.jump_blending_ratio * player->armature.animation.footing_blending_ratio), 
		(player->armature.animation.jump_blending_ratio * (1 - player->armature.animation.footing_blending_ratio))
	);
}


void playerAnimation_setStandingLocomotion(Player* player)
{
	if (player->motion_data.horizontal_speed == 0){

		if (player->armature.animation.current != STAND_IDLE){

			player->armature.animation.previous = player->armature.animation.current;
			player->armature.animation.current = STAND_IDLE;
		}
		playerAnimation_setStandingIdle(player);
		playerAnimation_setLanding(player);
	}

	else if (player->motion_data.horizontal_speed > 0 && player->motion_data.horizontal_speed <= player->motion_settings.walk_target_speed){

		if (player->armature.animation.current != WALKING){

			player->armature.animation.previous = player->armature.animation.current;
			player->armature.animation.current = WALKING;
		}

		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);

		playerAnimation_setStandingIdle(player);

	    playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setWalkingSpeed(player);
		playerAnimation_setWalking(player);

		playerAnimation_setLanding(player);
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.walk_target_speed && player->motion_data.horizontal_speed <= player->motion_settings.run_target_speed){

		if (player->armature.animation.current != RUNNING){

			player->armature.animation.previous = player->armature.animation.current;
			player->armature.animation.current = RUNNING;

			if (player->armature.animation.previous == WALKING) t3d_anim_set_time(&player->armature.animation.set.running, (player->armature.animation.set.walking.time * player->armature.animation.settings.walk_to_run_ratio));
			else if (player->armature.animation.previous == SPRINTING) t3d_anim_set_time(&player->armature.animation.set.walking, (player->armature.animation.set.sprinting.time * player->armature.animation.settings.sprint_to_walk_ratio));
		}

		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);

	    playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setRunningSpeed(player);
		playerAnimation_setRunning(player);
	
		playerAnimation_setLanding(player);
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.run_target_speed){

		if (player->armature.animation.current != SPRINTING){
			player->armature.animation.previous = player->armature.animation.current;
			player->armature.animation.current = SPRINTING;
			t3d_anim_set_time(&player->armature.animation.set.sprinting, (player->armature.animation.set.running.time * player->armature.animation.settings.run_to_sprint_ratio));
		}

		//playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.running.time, RUNNING_ANIM_LENGTH); 
		// workaround to get consistent footing blending :')
		t3d_anim_update(&player->armature.animation.set.walking, timer.delta);  
		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);

	    playerAnimation_setLocomotionBlendingRatio(player);		
		playerAnimation_setSprintingSpeed(player);
		playerAnimation_setSprinting(player);

		playerAnimation_setLanding(player);
	}
}

void playerAnimation_setRolling(Player* player)
{
	if (player->armature.animation.current != ROLLING){
		
		player->armature.animation.previous = player->armature.animation.current;
		player->armature.animation.current = ROLLING;
		
		t3d_anim_set_playing(&player->armature.animation.set.run_to_rolling_left, true);
		t3d_anim_set_time(&player->armature.animation.set.run_to_rolling_left, 0.0f);

		t3d_anim_set_playing(&player->armature.animation.set.run_to_rolling_right, true);
		t3d_anim_set_time(&player->armature.animation.set.run_to_rolling_right, 0.0f);
		player->armature.animation.action_blending_ratio = 0.0f;
	}
	
	if (player->motion_data.horizontal_speed <= player->motion_settings.run_target_speed){		
		
		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setRunningSpeed(player);
		player->armature.animation.set.walking.speed *= (1 - player->armature.animation.action_blending_ratio);
		player->armature.animation.set.running.speed *= (1 - player->armature.animation.action_blending_ratio);
		
		playerAnimation_setRunning(player);
		playerAnimation_setLanding(player);
		playerAnimation_setRunToRoll(player);
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.run_target_speed){

		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setSprintingSpeed(player);
		player->armature.animation.set.sprinting.speed *= (1 - player->armature.animation.action_blending_ratio);
		player->armature.animation.set.running.speed *= (1 - player->armature.animation.action_blending_ratio);

		playerAnimation_setSprinting(player);
		playerAnimation_setLanding(player);
		playerAnimation_setRunToRoll(player);
	}
}

void playerAnimation_setJumping(Player* player)
{
	if (player->armature.animation.current != JUMPING){

		player->armature.animation.previous = player->armature.animation.current;
		player->armature.animation.current = JUMPING;
		
		t3d_anim_set_playing(&player->armature.animation.set.jump_left, true);
		t3d_anim_set_playing(&player->armature.animation.set.jump_right, true);
		t3d_anim_set_time(&player->armature.animation.set.jump_left, 0.0f);
		t3d_anim_set_time(&player->armature.animation.set.jump_right, 0.0f);
		t3d_anim_set_time(&player->armature.animation.set.falling_left, 0.0f);
		t3d_anim_set_time(&player->armature.animation.set.falling_right, 0.0f);
	}

	if (player->motion_data.horizontal_speed == 0){

		playerAnimation_setStandingIdle(player);	
		if (player->armature.animation.set.jump_left.time < player->armature.animation.settings.jump_anim_crouch) playerAnimation_setLanding(player);
		playerAnimation_setJump(player);
	}

	else if (player->motion_data.horizontal_speed > 0 && player->motion_data.horizontal_speed <= player->motion_settings.walk_target_speed){

		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);
		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setWalkingSpeed(player);
		player->armature.animation.set.walking.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		
		playerAnimation_setStandingIdle(player);
		if (player->armature.animation.set.jump_left.time < player->armature.animation.settings.jump_anim_crouch) playerAnimation_setLanding(player);
		playerAnimation_setWalking(player);
		playerAnimation_setJump(player);
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.walk_target_speed && player->motion_data.horizontal_speed <= player->motion_settings.run_target_speed){
		
		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);
		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setRunningSpeed(player);
		player->armature.animation.set.walking.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		player->armature.animation.set.running.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		
		playerAnimation_setRunning(player);
		if (player->armature.animation.set.jump_left.time < player->armature.animation.settings.jump_anim_crouch) playerAnimation_setLanding(player);
		playerAnimation_setJump(player);
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.run_target_speed){

		//playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.running.time, RUNNING_ANIM_LENGTH);
		t3d_anim_update(&player->armature.animation.set.walking, timer.delta); // damn workaround
		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);
		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setSprintingSpeed(player);
		player->armature.animation.set.walking.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		player->armature.animation.set.running.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		player->armature.animation.set.sprinting.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		
		playerAnimation_setSprinting(player);
		if (player->armature.animation.set.jump_left.time < player->armature.animation.settings.jump_anim_crouch) playerAnimation_setLanding(player);
		playerAnimation_setJump(player);
	}
}

void playerAnimation_setFalling(Player* player)
{
	if (player->armature.animation.current != FALLING){

		player->armature.animation.previous = player->armature.animation.current;
		player->armature.animation.current = FALLING;

		t3d_anim_set_playing(&player->armature.animation.set.land_left, true);
		t3d_anim_set_playing(&player->armature.animation.set.land_right, true);
		t3d_anim_set_time(&player->armature.animation.set.land_left, 0.0f);
		t3d_anim_set_time(&player->armature.animation.set.land_right, 0.0f);
	}

	if (player->motion_data.horizontal_speed == 0){

		playerAnimation_setStandingIdle(player);

		// workaround until collision happens
		if (player->body.position.z < LAND_ANIM_STARTING_HEIGHT) playerAnimation_setLanding(player);
		else playerAnimation_setFallingIdle(player);
	}

	else if (player->motion_data.horizontal_speed > 0 && player->motion_data.horizontal_speed <= player->motion_settings.walk_target_speed){
		
		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);
		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setWalkingSpeed(player);
		player->armature.animation.set.walking.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);

		playerAnimation_setStandingIdle(player);
		playerAnimation_setWalking(player);
		if (player->body.position.z < LAND_ANIM_STARTING_HEIGHT) playerAnimation_setLanding(player);
		else playerAnimation_setFallingIdle(player);
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.walk_target_speed && player->motion_data.horizontal_speed <= player->motion_settings.run_target_speed){
		
		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);
		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setRunningSpeed(player);
		player->armature.animation.set.walking.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		player->armature.animation.set.running.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);

		playerAnimation_setRunning(player);
		if (player->body.position.z < LAND_ANIM_STARTING_HEIGHT) playerAnimation_setLanding(player);
		else playerAnimation_setFallingIdle(player);
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.run_target_speed){

		//playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.running.time, RUNNING_ANIM_LENGTH);
		t3d_anim_update(&player->armature.animation.set.walking, timer.delta);
		playerAnimation_setFootingBlendingRatio(player, player->armature.animation.set.walking.time, player->armature.animation.settings.walking_anim_length);
		playerAnimation_setLocomotionBlendingRatio(player);
		playerAnimation_setSprintingSpeed(player);
		player->armature.animation.set.walking.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		player->armature.animation.set.running.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);
		player->armature.animation.set.sprinting.speed *= player->armature.animation.settings.jump_footing_speed * (1 - player->armature.animation.jump_blending_ratio);

		playerAnimation_setSprinting(player);
		if (player->body.position.z < LAND_ANIM_STARTING_HEIGHT) playerAnimation_setLanding(player);
		else playerAnimation_setFallingIdle(player);
	}
}

void player_setAnimation(Player* player)
{
	switch (player->state.current)
	{
		case STAND_IDLE:
		{
			playerAnimation_setStandingLocomotion(player);
			break;
		}

		case WALKING:
		{
			playerAnimation_setStandingLocomotion(player);
			break;
		}

		case RUNNING:
		{
			playerAnimation_setStandingLocomotion(player);
			break;
		}

		case SPRINTING:
		{
			playerAnimation_setStandingLocomotion(player);
			break;
		}

		case ROLLING:
		{
			playerAnimation_setRolling(player);
			break;
		}

		case JUMPING:
		{
			playerAnimation_setJumping(player);
			break;
		}

		case FALLING:
		{
			playerAnimation_setFalling(player);
			break;
		}
	}

	t3d_skeleton_update(&player->armature.main);
}


/* speed range

	if (player->motion_data.horizontal_speed == 0){
	}

	else if (player->motion_data.horizontal_speed > 0 && player->motion_data.horizontal_speed <= player->motion_settings.walk_target_speed){
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.walk_target_speed && player->motion_data.horizontal_speed <= player->motion_settings.run_target_speed){
	}

	else if (player->motion_data.horizontal_speed > player->motion_settings.run_target_speed){
	}
*/
/* animation switch

	switch(player->armature.animation.current) {

		case STAND_IDLE: {
			break;
		}

		case WALKING: {
			break;
		}

		case RUNNING: {
			break;
		}

		case SPRINTING: {
			break;
		}

		case JUMPING: {
			break;
		}

		case FALLING: {
			break;
		}
	}
*/

