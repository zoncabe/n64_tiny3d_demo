#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_animation.h"
#include "../../include/player/player.h"
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"


// custom T3D function for my engine
void t3d_skeleton_blend_3_(const T3DSkeleton *skelRes, const T3DSkeleton *skelA, const T3DSkeleton *skelB, const T3DSkeleton *skelC, float factorB, float factorC)
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

void actorAnimation_initArmature(ActorArmature* armature, T3DModel *model)
{
	armature->main = t3d_skeleton_create_buffered(model, FB_COUNT);
	armature->blend = t3d_skeleton_clone(&armature->main, false);
	armature->blend2 = t3d_skeleton_clone(&armature->main, false);
}


void actorAnimation_initStandingLocomotionSet(ActorArmature* armature, T3DModel *model, ActorAnimationStandingLocomotionSet *set)
{
	set->breathing_idle = t3d_anim_create(model, "breathing-idle");
	
	set->standing_idle_left = t3d_anim_create(model, "standing-idle-left");
	set->standing_idle_right = t3d_anim_create(model, "standing-idle-right");
	
	//set->transition_left = t3d_anim_create(model, "transition-left");
	//set->transition_right = t3d_anim_create(model, "transition-right");

	set->walking = t3d_anim_create(model, "walking");
	set->running = t3d_anim_create(model, "running");
	set->sprinting = t3d_anim_create(model, "sprinting");

	t3d_anim_attach(&set->breathing_idle, &armature->main);
	
	t3d_anim_attach(&set->standing_idle_left, &armature->blend);
	t3d_anim_attach(&set->standing_idle_right, &armature->blend2);

	//t3d_anim_attach(&set->transition_left, &armature->blend);
	//t3d_anim_attach(&set->transition_right, &armature->blend2);

	t3d_anim_attach(&set->walking, &armature->blend);
	t3d_anim_attach(&set->running, &armature->main);
	t3d_anim_attach(&set->sprinting, &armature->blend);
}

void actorAnimation_initJumpSet(ActorArmature* armature, T3DModel *model, ActorAnimationJumpSet *set)
{
	set->jump_left = t3d_anim_create(model, "jump-left");
	set->jump_right = t3d_anim_create(model, "jump-right");

	set->falling_left = t3d_anim_create(model, "falling-idle-left");
	set->falling_right = t3d_anim_create(model, "falling-idle-right");

	set->land_left = t3d_anim_create(model, "land-left");
	set->land_right = t3d_anim_create(model, "land-right");

	t3d_anim_set_looping(&set->jump_left, false);
	t3d_anim_set_looping(&set->jump_right, false);

	t3d_anim_set_looping(&set->land_left, false);
	t3d_anim_set_looping(&set->land_right, false);

	t3d_anim_attach(&set->jump_left, &armature->blend);
	t3d_anim_attach(&set->jump_right, &armature->blend2);

	t3d_anim_attach(&set->falling_left, &armature->blend);
	t3d_anim_attach(&set->falling_right, &armature->blend2);

	t3d_anim_attach(&set->land_left, &armature->blend);
	t3d_anim_attach(&set->land_right, &armature->blend2);
}

void actorAnimation_initRollSet(ActorArmature* armature, T3DModel *model, ActorAnimationRollSet *set)
{	
	//set->stand_to_rolling_left = t3d_anim_create(model, "stand-to-roll-left");
	//set->stand_to_rolling_right = t3d_anim_create(model, "stand-to-roll-right");
	
	set->run_to_rolling_right = t3d_anim_create(model, "run-to-roll-right");
	set->run_to_rolling_left = t3d_anim_create(model, "run-to-roll-left");

	//t3d_anim_set_looping(&set->stand_to_rolling_left, false);
	//t3d_anim_set_looping(&set->stand_to_rolling_right, false);

	t3d_anim_set_looping(&set->run_to_rolling_left, false);
	t3d_anim_set_looping(&set->run_to_rolling_right, false);

	//t3d_anim_attach(&set->stand_to_rolling_left, &armature->blend);
	//t3d_anim_attach(&set->stand_to_rolling_right, &armature->blend2);

	t3d_anim_attach(&set->run_to_rolling_left, &armature->blend);
	t3d_anim_attach(&set->run_to_rolling_right, &armature->blend2);
}


void actorAnimation_setLocomotionBlendingRatio(ActorMotionData* motion_data, ActorMotionSettings* motion_settings, ActorAnimationData* animation_data)
{
	if (motion_data->horizontal_speed == 0) animation_data->locomotion_blending_ratio = 0;

	else if (motion_data->horizontal_speed <= motion_settings->walk_target_speed)
		animation_data->locomotion_blending_ratio = (motion_data->horizontal_speed / motion_settings->walk_target_speed);

	else if (motion_data->horizontal_speed <= motion_settings->run_target_speed) 
		animation_data->locomotion_blending_ratio = 1.0f - ((motion_data->horizontal_speed - motion_settings->walk_target_speed) / (motion_settings->run_target_speed - motion_settings->walk_target_speed));

	else
		animation_data->locomotion_blending_ratio = ((motion_data->horizontal_speed - motion_settings->run_target_speed) / (motion_settings->sprint_target_speed - motion_settings->run_target_speed));

	if (animation_data->locomotion_blending_ratio > 1.0f) animation_data->locomotion_blending_ratio = 1.0f;
	if (animation_data->locomotion_blending_ratio < 0.0f) animation_data->locomotion_blending_ratio = 0.0f;
}

void actorAnimation_setFootingBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, float action_time, float action_lenght)
{
	float phase = 1 / action_lenght * action_time;

	if (phase <= 0.25f) animation_data->footing_blending_ratio = 0.5f + 2.0f * phase;
	else if (phase <= 0.75f)animation_data->footing_blending_ratio = 1.0f - 2.0f * (phase - 0.25f);
	else if (phase <= 1) animation_data->footing_blending_ratio = 2.0f * (phase - 0.75f);
}

void actorAnimation_setRollingBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationRollSettings* roll_settings, ActorAnimationLocomotionSettings* locomotion_settings, ActorAnimationStandingLocomotionSet* locomotion_set)
{
	if (motion_data->roll_timer < roll_settings->run_to_rolling_anim_ground && animation_data->roll_blending_ratio <= 1.0f) 
		animation_data->roll_blending_ratio += (timer.delta / roll_settings->run_to_rolling_anim_ground);
	if (motion_data->roll_timer > roll_settings->run_to_rolling_anim_stand && animation_data->roll_blending_ratio > 0.0f) 
		animation_data->roll_blending_ratio -= (timer.delta / (2 * (roll_settings->run_to_rolling_anim_lenght - roll_settings->run_to_rolling_anim_stand)));
	
	if (animation_data->roll_blending_ratio > 1.0f) {
		
		animation_data->roll_blending_ratio = 1.0f;

		if (animation_data->footing_blending_ratio < 0.5f) 
			t3d_anim_set_time(&locomotion_set->running, locomotion_settings->running_anim_length_half - (roll_settings->run_to_rolling_anim_lenght - roll_settings->run_to_rolling_anim_stand) + timer.delta);
		if (animation_data->footing_blending_ratio >= 0.5f) 
			t3d_anim_set_time(&locomotion_set->walking, locomotion_settings->running_anim_length_half - (roll_settings->run_to_rolling_anim_lenght - roll_settings->run_to_rolling_anim_stand) + timer.delta);

		t3d_anim_set_time(&locomotion_set->walking, (locomotion_set->running.time * locomotion_settings->run_to_walk_ratio));
		t3d_anim_set_time(&locomotion_set->sprinting, (locomotion_set->running.time * locomotion_settings->run_to_sprint_ratio));			
	}

	if (animation_data->roll_blending_ratio < 0.0f) animation_data->roll_blending_ratio = 0.0f;
}

void actorAnimation_setJumpBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* animation_settings)
{
	if (animation_data->jump_blending_ratio == animation_settings->jump_max_blending_ratio) return;
	if (animation_data->jump_blending_ratio < animation_settings->jump_max_blending_ratio) animation_data->jump_blending_ratio += (timer.delta / (animation_settings->jump_anim_air - timer.delta));
	if (animation_data->jump_blending_ratio > animation_settings->jump_max_blending_ratio) animation_data->jump_blending_ratio = animation_settings->jump_max_blending_ratio;
}

void actorAnimation_setLandingBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* animation_settings, ActorAnimationJumpSet* set)
{
	if (set->land_left.time > animation_settings->land_anim_ground) {
		
		if (animation_data->jump_blending_ratio > 0) animation_data->jump_blending_ratio -= (timer.delta / (animation_settings->land_anim_length - animation_settings->land_anim_ground));
		else animation_data->jump_blending_ratio = 0;
	}
}

void actorAnimation_setWalkingSpeed(ActorAnimationData* animation_data, ActorAnimationStandingLocomotionSet* set)
{
	t3d_anim_set_speed(&set->walking, animation_data->locomotion_blending_ratio);
}

void actorAnimation_setRunningSpeed(ActorAnimationData* animation_data, ActorAnimationLocomotionSettings* animation_settings, ActorAnimationStandingLocomotionSet* set)
{
	animation_data->speed = (1.0f - ((1.0f - animation_settings->walk_to_run_ratio) * animation_data->locomotion_blending_ratio));
	t3d_anim_set_speed(&set->running, animation_data->speed);
	t3d_anim_set_speed(&set->walking, (animation_data->speed * animation_settings->run_to_walk_ratio));
}

void actorAnimation_setSprintingSpeed(ActorAnimationData* animation_data, ActorAnimationLocomotionSettings* animation_settings, ActorAnimationStandingLocomotionSet* set)
{
	animation_data->speed = (animation_settings->run_to_sprint_ratio + ((1.0f - animation_settings->run_to_sprint_ratio) * animation_data->locomotion_blending_ratio));
	t3d_anim_set_speed(&set->running, (animation_data->speed * animation_settings->sprint_to_run_ratio));
	t3d_anim_set_speed(&set->sprinting, animation_data->speed);
	t3d_anim_set_speed(&set->walking, (animation_data->speed * animation_settings->sprint_to_walk_ratio));
}


void actorAnimation_setStandingLocomotion(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data, ActorAnimationLocomotionSettings* settings)
{
	t3d_anim_update(&set->breathing_idle, timer.delta);
	t3d_anim_update(&set->standing_idle_left, timer.delta);
	t3d_anim_update(&set->standing_idle_right, timer.delta);
	t3d_skeleton_blend_3_(&armature->main, 
		&armature->main, 
		&armature->blend, 
		&armature->blend2, 
		settings->action_idle_max_blending_ratio * animation_data->footing_blending_ratio, 
		settings->action_idle_max_blending_ratio * (1 - animation_data->footing_blending_ratio));
}

void actorAnimation_setStandingIdle(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data, ActorAnimationLocomotionSettings* settings)
{
	t3d_anim_update(&set->breathing_idle, timer.delta);
	t3d_anim_update(&set->standing_idle_left, timer.delta);
	t3d_anim_update(&set->standing_idle_right, timer.delta);
	t3d_skeleton_blend_3_(&armature->main, 
		&armature->main, 
		&armature->blend, 
		&armature->blend2, 
		settings->action_idle_max_blending_ratio * animation_data->footing_blending_ratio, 
		settings->action_idle_max_blending_ratio * (1 - animation_data->footing_blending_ratio));
}

void actorAnimation_setWalking(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data)
{
	t3d_anim_update(&set->walking, timer.delta);
	t3d_skeleton_blend(&armature->main, &armature->main, &armature->blend, animation_data->locomotion_blending_ratio);
}

void actorAnimation_setRunning(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data)
{
	t3d_anim_update(&set->running, timer.delta);
	t3d_anim_update(&set->walking, timer.delta);
	t3d_skeleton_blend(&armature->main, &armature->main, &armature->blend, animation_data->locomotion_blending_ratio);
}

void actorAnimation_setSprinting(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data)
{
	t3d_anim_update(&set->running, timer.delta);
	t3d_anim_update(&set->sprinting, timer.delta);
	t3d_skeleton_blend(&armature->main, &armature->main, &armature->blend, animation_data->locomotion_blending_ratio);
}

void actorAnimation_setRunToRoll(ActorArmature* armature, ActorAnimationRollSet* roll_set, ActorAnimationStandingLocomotionSet* locomotion_set, ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationRollSettings* roll_settings, ActorAnimationLocomotionSettings* locomotion_settings)
{
	actorAnimation_setRollingBlendingRatio(motion_data, animation_data, roll_settings, locomotion_settings, locomotion_set);

	if (animation_data->footing_blending_ratio <= 0.5f){
				
		t3d_anim_update(&roll_set->run_to_rolling_right, timer.delta);
		t3d_skeleton_blend(&armature->main,
			&armature->main,
			&armature->blend2,
			animation_data->roll_blending_ratio
		);
	}
	
	if (animation_data->footing_blending_ratio > 0.5f){
			
		t3d_anim_update(&roll_set->run_to_rolling_left, timer.delta);
		t3d_skeleton_blend(&armature->main, 
			&armature->main, 
			&armature->blend,
			animation_data->roll_blending_ratio
		);
	}
}

void actorAnimation_setFallingIdle(ActorArmature *armature, ActorAnimationJumpSet* set, ActorAnimationData* animation_data)
{
	t3d_anim_update(&set->falling_left, timer.delta);
	t3d_anim_update(&set->falling_right, timer.delta);
	t3d_skeleton_blend_3_(&armature->main, 
		&armature->main, 
		&armature->blend, 
		&armature->blend2, 
		(animation_data->jump_blending_ratio * animation_data->footing_blending_ratio), 
		(animation_data->jump_blending_ratio * (1 - animation_data->footing_blending_ratio))
	);
}

void actorAnimation_setJump(ActorArmature *armature, ActorAnimationJumpSet* set, ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* settings)
{
	if ((set->jump_left.time + timer.delta) < settings->jump_anim_length){

		actorAnimation_setJumpBlendingRatio(motion_data, animation_data, settings);
		t3d_anim_update(&set->jump_left, timer.delta);
		t3d_anim_update(&set->jump_right, timer.delta);
		t3d_skeleton_blend_3_(&armature->main, 
			&armature->main,
			&armature->blend, 
			&armature->blend2, 
			(animation_data->jump_blending_ratio * animation_data->footing_blending_ratio), 
			(animation_data->jump_blending_ratio * fabs(1 - animation_data->footing_blending_ratio))
		);
	}
	else actorAnimation_setFallingIdle(armature, set, animation_data);
}

void actorAnimation_setLanding(ActorArmature *armature, ActorAnimationJumpSet* set, ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* settings)
{		
	actorAnimation_setLandingBlendingRatio(motion_data, animation_data, settings, set);
	t3d_anim_update(&set->land_left, timer.delta);
	t3d_anim_update(&set->land_right, timer.delta);
	t3d_skeleton_blend_3_(&armature->main, 
		&armature->main, 
		&armature->blend, 
		&armature->blend2, 
		(animation_data->jump_blending_ratio * animation_data->footing_blending_ratio), 
		(animation_data->jump_blending_ratio * (1 - animation_data->footing_blending_ratio))
	);
}