#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_states.h"
#include "../../include/actor/actor_animation.h"
#include "../../include/player/player.h"
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"


void playerAnimation_init(Player* player)
{
	actorAnimation_initArmature(&player->actor);
	actorAnimation_initStandingLocomotionSet(&player->actor);
	actorAnimation_initJumpSet(&player->actor);
	actorAnimation_initRollSet(&player->actor);
}


void playerAnimation_setStandingLocomotion(Player* player)
{
	if (player->actor.motion.data.horizontal_speed == 0){

		if (player->actor.animation.data.current != STANDING_IDLE){

			player->actor.animation.data.previous = player->actor.animation.data.current;
			player->actor.animation.data.current = STANDING_IDLE;
		}
		actorAnimation_setStandingIdle(&player->actor);
		actorAnimation_setLanding(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > 0 && player->actor.motion.data.horizontal_speed <= player->actor.motion.settings.walk_target_speed){

		if (player->actor.animation.data.current != WALKING){

			player->actor.animation.data.previous = player->actor.animation.data.current;
			player->actor.animation.data.current = WALKING;
		}

		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);

		actorAnimation_setStandingIdle(&player->actor);

	    actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setWalkingSpeed(&player->actor);
		actorAnimation_setWalking(&player->actor);

		actorAnimation_setLanding(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > player->actor.motion.settings.walk_target_speed && player->actor.motion.data.horizontal_speed <= player->actor.motion.settings.run_target_speed){

		if (player->actor.animation.data.current != RUNNING){

			player->actor.animation.data.previous = player->actor.animation.data.current;
			player->actor.animation.data.current = RUNNING;

			if (player->actor.animation.data.previous == WALKING) t3d_anim_set_time(&player->actor.animation.standing_locomotion.running, (player->actor.animation.standing_locomotion.walking.time * player->actor.animation.settings.standing_locomotion.walk_to_run_ratio));
			else if (player->actor.animation.data.previous == SPRINTING) t3d_anim_set_time(&player->actor.animation.standing_locomotion.walking, (player->actor.animation.standing_locomotion.sprinting.time * player->actor.animation.settings.standing_locomotion.sprint_to_walk_ratio));
		}

		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);

	    actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setRunningSpeed(&player->actor);
		actorAnimation_setRunning(&player->actor);
	
		actorAnimation_setLanding(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > player->actor.motion.settings.run_target_speed){
		if (player->actor.animation.data.current != SPRINTING){
			player->actor.animation.data.previous = player->actor.animation.data.current;
			player->actor.animation.data.current = SPRINTING;
			t3d_anim_set_time(&player->actor.animation.standing_locomotion.sprinting, (player->actor.animation.standing_locomotion.running.time * player->actor.animation.settings.standing_locomotion.run_to_sprint_ratio));
		}

		//actorAnimation_setFootingBlendingRatio(&player->actor, player->armature.animation.set.running.time, RUNNING_ANIM_LENGTH); 
		// workaround to get consistent footing blending :')
		t3d_anim_update(&player->actor.animation.standing_locomotion.walking, timer.delta);  
		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);

	    actorAnimation_setLocomotionBlendingRatio(&player->actor);		
		actorAnimation_setSprintingSpeed(&player->actor);
		actorAnimation_setSprinting(&player->actor);

		actorAnimation_setLanding(&player->actor);
	}
}

void playerAnimation_setRolling(Player* player)
{
	if (player->actor.animation.data.current != ROLLING){
		
		player->actor.animation.data.previous = player->actor.animation.data.current;
		player->actor.animation.data.current = ROLLING;
		
		t3d_anim_set_playing(&player->actor.animation.roll.running_to_roll_left, true);
		t3d_anim_set_time(&player->actor.animation.roll.running_to_roll_left, 0.0f);

		t3d_anim_set_playing(&player->actor.animation.roll.running_to_roll_right, true);
		t3d_anim_set_time(&player->actor.animation.roll.running_to_roll_right, 0.0f);
		player->actor.animation.data.action_blending_ratio = 0.0f;
	}

	if (player->actor.motion.data.horizontal_speed <= player->actor.motion.settings.run_target_speed){		

		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setRunningSpeed(&player->actor);
		player->actor.animation.standing_locomotion.walking.speed *= (1 - player->actor.animation.data.action_blending_ratio);
		player->actor.animation.standing_locomotion.running.speed *= (1 - player->actor.animation.data.action_blending_ratio);
		
		actorAnimation_setRunning(&player->actor);
		actorAnimation_setLanding(&player->actor);
		actorAnimation_setRunToRoll(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > player->actor.motion.settings.run_target_speed){

		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setSprintingSpeed(&player->actor);
		player->actor.animation.standing_locomotion.sprinting.speed *= (1 - player->actor.animation.data.action_blending_ratio);
		player->actor.animation.standing_locomotion.running.speed *= (1 - player->actor.animation.data.action_blending_ratio);

		actorAnimation_setSprinting(&player->actor);
		actorAnimation_setLanding(&player->actor);
		actorAnimation_setRunToRoll(&player->actor);
	}
}

void playerAnimation_setJumping(Player* player)
{
	if (player->actor.animation.data.current != JUMPING){

		player->actor.animation.data.previous = player->actor.animation.data.current;
		player->actor.animation.data.current = JUMPING;
		
		t3d_anim_set_playing(&player->actor.animation.jump.jump_left, true);
		t3d_anim_set_playing(&player->actor.animation.jump.jump_right, true);
		t3d_anim_set_time(&player->actor.animation.jump.jump_left, 0.0f);
		t3d_anim_set_time(&player->actor.animation.jump.jump_right, 0.0f);
		t3d_anim_set_time(&player->actor.animation.jump.falling_left, 0.0f);
		t3d_anim_set_time(&player->actor.animation.jump.falling_right, 0.0f);
	}

	if (player->actor.motion.data.horizontal_speed == 0){

		actorAnimation_setStandingIdle(&player->actor);	
		if (player->actor.animation.jump.jump_left.time < player->actor.animation.settings.jump.jump_anim_crouch) actorAnimation_setLanding(&player->actor);
		actorAnimation_setJump(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > 0 && player->actor.motion.data.horizontal_speed <= player->actor.motion.settings.walk_target_speed){
		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);
		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setWalkingSpeed(&player->actor);
		player->actor.animation.standing_locomotion.walking.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		
		actorAnimation_setStandingIdle(&player->actor);
		if (player->actor.animation.jump.jump_left.time < player->actor.animation.settings.jump.jump_anim_crouch) actorAnimation_setLanding(&player->actor);
		actorAnimation_setWalking(&player->actor);
		actorAnimation_setJump(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > player->actor.motion.settings.walk_target_speed && player->actor.motion.data.horizontal_speed <= player->actor.motion.settings.run_target_speed){
		
		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);
		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setRunningSpeed(&player->actor);
		player->actor.animation.standing_locomotion.walking.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		player->actor.animation.standing_locomotion.running.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		
		actorAnimation_setRunning(&player->actor);
		if (player->actor.animation.jump.jump_left.time < player->actor.animation.settings.jump.jump_anim_crouch) actorAnimation_setLanding(&player->actor);
		actorAnimation_setJump(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > player->actor.motion.settings.run_target_speed){

		//actorAnimation_setFootingBlendingRatio(&player->actor, player->armature.animation.set.running.time, RUNNING_ANIM_LENGTH);
		t3d_anim_update(&player->actor.animation.standing_locomotion.walking, timer.delta); // damn workaround
		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);
		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setSprintingSpeed(&player->actor);
		
		player->actor.animation.standing_locomotion.walking.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		player->actor.animation.standing_locomotion.running.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		player->actor.animation.standing_locomotion.sprinting.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);

		actorAnimation_setSprinting(&player->actor);
		if (player->actor.animation.jump.jump_left.time < player->actor.animation.settings.jump.jump_anim_crouch) actorAnimation_setLanding(&player->actor);
		actorAnimation_setJump(&player->actor);
	}
}

void playerAnimation_setFalling(Player* player)
{
	if (player->actor.animation.data.current != FALLING){

		player->actor.animation.data.previous = player->actor.animation.data.current;
		player->actor.animation.data.current = FALLING;

		t3d_anim_set_playing(&player->actor.animation.jump.land_left, true);
		t3d_anim_set_playing(&player->actor.animation.jump.land_right, true);
		t3d_anim_set_time(&player->actor.animation.jump.land_left, 0.0f);
		t3d_anim_set_time(&player->actor.animation.jump.land_right, 0.0f);
	}

	if (player->actor.motion.data.horizontal_speed == 0){

		actorAnimation_setStandingIdle(&player->actor);

		// workaround until collision happens
		if (player->actor.body.position.z < LAND_ANIM_STARTING_HEIGHT) actorAnimation_setLanding(&player->actor);
		else actorAnimation_setFallingIdle(&player->actor);
	}
	
	else if (player->actor.motion.data.horizontal_speed > 0 && player->actor.motion.data.horizontal_speed <= player->actor.motion.settings.walk_target_speed){
		
		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);
		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setWalkingSpeed(&player->actor);
		player->actor.animation.standing_locomotion.walking.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);

		actorAnimation_setStandingIdle(&player->actor);
		actorAnimation_setWalking(&player->actor);
		if (player->actor.body.position.z < LAND_ANIM_STARTING_HEIGHT) actorAnimation_setLanding(&player->actor);
		else actorAnimation_setFallingIdle(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > player->actor.motion.settings.walk_target_speed && player->actor.motion.data.horizontal_speed <= player->actor.motion.settings.run_target_speed){
		
		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);
		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setRunningSpeed(&player->actor);
		player->actor.animation.standing_locomotion.walking.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		player->actor.animation.standing_locomotion.running.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);

		actorAnimation_setRunning(&player->actor);
		if (player->actor.body.position.z < LAND_ANIM_STARTING_HEIGHT) actorAnimation_setLanding(&player->actor);
		else actorAnimation_setFallingIdle(&player->actor);
	}

	else if (player->actor.motion.data.horizontal_speed > player->actor.motion.settings.run_target_speed){

		//actorAnimation_setFootingBlendingRatio(&player->actor, player->armature.animation.set.running.time, RUNNING_ANIM_LENGTH);
		t3d_anim_update(&player->actor.animation.standing_locomotion.walking, timer.delta);
		actorAnimation_setFootingBlendingRatio(&player->actor, player->actor.animation.standing_locomotion.walking.time, player->actor.animation.settings.standing_locomotion.walking_anim_length);
		actorAnimation_setLocomotionBlendingRatio(&player->actor);
		actorAnimation_setSprintingSpeed(&player->actor);
		
		player->actor.animation.standing_locomotion.walking.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		player->actor.animation.standing_locomotion.running.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		player->actor.animation.standing_locomotion.sprinting.speed *= player->actor.animation.settings.jump.jump_footing_speed * (1 - player->actor.animation.data.jump_blending_ratio);
		
		actorAnimation_setSprinting(&player->actor);
		if (player->actor.body.position.z < LAND_ANIM_STARTING_HEIGHT) actorAnimation_setLanding(&player->actor);
		else actorAnimation_setFallingIdle(&player->actor);
	}
}

void player_setAnimation(Player* player)
{
	switch (player->actor.state.current)
	{
		case STANDING_IDLE:
		case WALKING:
		case RUNNING:
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

	t3d_skeleton_update(&player->actor.armature.main);
}