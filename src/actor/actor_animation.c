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

void actorAnimation_initArmature(Actor* actor)
{
	actor->armature.main = t3d_skeleton_create_buffered(actor->model, FB_COUNT);
	actor->armature.blend = t3d_skeleton_clone(&actor->armature.main, false);
	actor->armature.blend2 = t3d_skeleton_clone(&actor->armature.main, false);
}

void actorAnimation_initStandingLocomotionSet(Actor* actor)
{
	actor->animation.standing_locomotion.breathing_idle = t3d_anim_create(actor->model, "breathing-idle");
	
	actor->animation.standing_locomotion.standing_idle_left = t3d_anim_create(actor->model, "standing-idle-left");
	actor->animation.standing_locomotion.standing_idle_right = t3d_anim_create(actor->model, "standing-idle-right");
	
	//actor->animation.standing_locomotion.transition_left = t3d_anim_create(actor->model, "transition-left");
	//actor->animation.standing_locomotion.transition_right = t3d_anim_create(actor->model, "transition-right");

	actor->animation.standing_locomotion.walking = t3d_anim_create(actor->model, "walking");
	actor->animation.standing_locomotion.running = t3d_anim_create(actor->model, "running");
	actor->animation.standing_locomotion.sprinting = t3d_anim_create(actor->model, "sprinting");

	t3d_anim_attach(&actor->animation.standing_locomotion.breathing_idle, &actor->armature.main);
	
	t3d_anim_attach(&actor->animation.standing_locomotion.standing_idle_left, &actor->armature.blend);
	t3d_anim_attach(&actor->animation.standing_locomotion.standing_idle_right, &actor->armature.blend2);

	//t3d_anim_attach(&actor->animation.standing_locomotion.transition_left, &actor->armature.blend);
	//t3d_anim_attach(&actor->animation.standing_locomotion.transition_right, &actor->armature.blend2);

	t3d_anim_attach(&actor->animation.standing_locomotion.walking, &actor->armature.blend);
	t3d_anim_attach(&actor->animation.standing_locomotion.running, &actor->armature.main);
	t3d_anim_attach(&actor->animation.standing_locomotion.sprinting, &actor->armature.blend);
}

void actorAnimation_initJumpSet(Actor* actor)
{
	actor->animation.jump.jump_left = t3d_anim_create(actor->model, "jump-left");
	actor->animation.jump.jump_right = t3d_anim_create(actor->model, "jump-right");

	actor->animation.jump.falling_left = t3d_anim_create(actor->model, "falling-idle-left");
	actor->animation.jump.falling_right = t3d_anim_create(actor->model, "falling-idle-right");

	actor->animation.jump.land_left = t3d_anim_create(actor->model, "land-left");
	actor->animation.jump.land_right = t3d_anim_create(actor->model, "land-right");

	t3d_anim_set_looping(&actor->animation.jump.jump_left, false);
	t3d_anim_set_looping(&actor->animation.jump.jump_right, false);

	t3d_anim_set_looping(&actor->animation.jump.land_left, false);
	t3d_anim_set_looping(&actor->animation.jump.land_right, false);

	t3d_anim_attach(&actor->animation.jump.jump_left, &actor->armature.blend);
	t3d_anim_attach(&actor->animation.jump.jump_right, &actor->armature.blend2);

	t3d_anim_attach(&actor->animation.jump.falling_left, &actor->armature.blend);
	t3d_anim_attach(&actor->animation.jump.falling_right, &actor->armature.blend2);

	t3d_anim_attach(&actor->animation.jump.land_left, &actor->armature.blend);
	t3d_anim_attach(&actor->animation.jump.land_right, &actor->armature.blend2);
}

void actorAnimation_initRollSet(Actor* actor)
{	
	//actor->animation.roll.stand_to_rolling_left = t3d_anim_create(actor->model, "stand-to-roll-left");
	//actor->animation.roll.stand_to_rolling_right = t3d_anim_create(actor->model, "stand-to-roll-right");
	
	actor->animation.roll.run_to_rolling_right = t3d_anim_create(actor->model, "run-to-roll-right");
	actor->animation.roll.run_to_rolling_left = t3d_anim_create(actor->model, "run-to-roll-left");

	//t3d_anim_set_looping(&actor->animation.roll.stand_to_rolling_left, false);
	//t3d_anim_set_looping(&actor->animation.roll.stand_to_rolling_right, false);

	t3d_anim_set_looping(&actor->animation.roll.run_to_rolling_left, false);
	t3d_anim_set_looping(&actor->animation.roll.run_to_rolling_right, false);

	//t3d_anim_attach(&actor->animation.roll.stand_to_rolling_left, &actor->armature.blend);
	//t3d_anim_attach(&actor->animation.roll.stand_to_rolling_right, &actor->armature.blend2);

	t3d_anim_attach(&actor->animation.roll.run_to_rolling_left, &actor->armature.blend);
	t3d_anim_attach(&actor->animation.roll.run_to_rolling_right, &actor->armature.blend2);
}

void actorAnimation_setLocomotionBlendingRatio(Actor* actor)
{
	if (actor->motion.data.horizontal_speed == 0) actor->animation.data.locomotion_blending_ratio = 0;

	else if (actor->motion.data.horizontal_speed <= actor->motion.settings.walk_target_speed)
		actor->animation.data.locomotion_blending_ratio = (actor->motion.data.horizontal_speed / actor->motion.settings.walk_target_speed);

	else if (actor->motion.data.horizontal_speed <= actor->motion.settings.run_target_speed) 
		actor->animation.data.locomotion_blending_ratio = 1.0f - ((actor->motion.data.horizontal_speed - actor->motion.settings.walk_target_speed) / (actor->motion.settings.run_target_speed - actor->motion.settings.walk_target_speed));

	else
		actor->animation.data.locomotion_blending_ratio = ((actor->motion.data.horizontal_speed - actor->motion.settings.run_target_speed) / (actor->motion.settings.sprint_target_speed - actor->motion.settings.run_target_speed));

	if (actor->animation.data.locomotion_blending_ratio > 1.0f) actor->animation.data.locomotion_blending_ratio = 1.0f;
	if (actor->animation.data.locomotion_blending_ratio < 0.0f) actor->animation.data.locomotion_blending_ratio = 0.0f;
}

void actorAnimation_setFootingBlendingRatio(Actor* actor, float action_time, float action_lenght)
{
	float phase = 1 / action_lenght * action_time;

	if (phase <= 0.25f) actor->animation.data.footing_blending_ratio = 0.5f + 2.0f * phase;
	else if (phase <= 0.75f) actor->animation.data.footing_blending_ratio = 1.0f - 2.0f * (phase - 0.25f);
	else if (phase <= 1) actor->animation.data.footing_blending_ratio = 2.0f * (phase - 0.75f);
}

void actorAnimation_setRollingBlendingRatio(Actor* actor)
{
	if (actor->motion.data.roll_timer < actor->animation.settings.roll.run_to_rolling_anim_ground && actor->animation.data.roll_blending_ratio <= 1.0f) 
		actor->animation.data.roll_blending_ratio += (timer.delta / actor->animation.settings.roll.run_to_rolling_anim_ground);
	if (actor->motion.data.roll_timer > actor->animation.settings.roll.run_to_rolling_anim_stand && actor->animation.data.roll_blending_ratio > 0.0f) 
		actor->animation.data.roll_blending_ratio -= (timer.delta / (2 * (actor->animation.settings.roll.run_to_rolling_anim_lenght - actor->animation.settings.roll.run_to_rolling_anim_stand)));
	
	if (actor->animation.data.roll_blending_ratio > 1.0f) {
		
		actor->animation.data.roll_blending_ratio = 1.0f;

		if (actor->animation.data.footing_blending_ratio < 0.5f) 
			t3d_anim_set_time(&actor->animation.standing_locomotion.running, actor->animation.settings.standing_locomotion.running_anim_length_half - (actor->animation.settings.roll.run_to_rolling_anim_lenght - actor->animation.settings.roll.run_to_rolling_anim_stand) + timer.delta);
		if (actor->animation.data.footing_blending_ratio >= 0.5f) 
			t3d_anim_set_time(&actor->animation.standing_locomotion.walking, actor->animation.settings.standing_locomotion.running_anim_length_half - (actor->animation.settings.roll.run_to_rolling_anim_lenght - actor->animation.settings.roll.run_to_rolling_anim_stand) + timer.delta);

		t3d_anim_set_time(&actor->animation.standing_locomotion.walking, (actor->animation.standing_locomotion.running.time * actor->animation.settings.standing_locomotion.run_to_walk_ratio));
		t3d_anim_set_time(&actor->animation.standing_locomotion.sprinting, (actor->animation.standing_locomotion.running.time * actor->animation.settings.standing_locomotion.run_to_sprint_ratio));			
	}

	if (actor->animation.data.roll_blending_ratio < 0.0f) actor->animation.data.roll_blending_ratio = 0.0f;
}

void actorAnimation_setJumpBlendingRatio(Actor* actor)
{
	if (actor->animation.data.jump_blending_ratio == actor->animation.settings.jump.jump_max_blending_ratio) return;
	if (actor->animation.data.jump_blending_ratio < actor->animation.settings.jump.jump_max_blending_ratio) actor->animation.data.jump_blending_ratio += (timer.delta / (actor->animation.settings.jump.jump_anim_air - timer.delta));
	if (actor->animation.data.jump_blending_ratio > actor->animation.settings.jump.jump_max_blending_ratio) actor->animation.data.jump_blending_ratio = actor->animation.settings.jump.jump_max_blending_ratio;
}

void actorAnimation_setLandingBlendingRatio(Actor* actor)
{
	if (actor->animation.jump.land_left.time > actor->animation.settings.jump.land_anim_ground) {
		
		if (actor->animation.data.jump_blending_ratio > 0) actor->animation.data.jump_blending_ratio -= (timer.delta / (actor->animation.settings.jump.land_anim_length - actor->animation.settings.jump.land_anim_ground));
		else actor->animation.data.jump_blending_ratio = 0;
	}
}

void actorAnimation_setWalkingSpeed(Actor* actor)
{
	t3d_anim_set_speed(&actor->animation.standing_locomotion.walking, actor->animation.data.locomotion_blending_ratio);
}

void actorAnimation_setRunningSpeed(Actor* actor)
{
	actor->animation.data.speed = (1.0f - ((1.0f - actor->animation.settings.standing_locomotion.walk_to_run_ratio) * actor->animation.data.locomotion_blending_ratio));
	t3d_anim_set_speed(&actor->animation.standing_locomotion.running, actor->animation.data.speed);
	t3d_anim_set_speed(&actor->animation.standing_locomotion.walking, (actor->animation.data.speed * actor->animation.settings.standing_locomotion.run_to_walk_ratio));
}

void actorAnimation_setSprintingSpeed(Actor* actor)
{
	actor->animation.data.speed = (actor->animation.settings.standing_locomotion.run_to_sprint_ratio + ((1.0f - actor->animation.settings.standing_locomotion.run_to_sprint_ratio) * actor->animation.data.locomotion_blending_ratio));
	t3d_anim_set_speed(&actor->animation.standing_locomotion.running, (actor->animation.data.speed * actor->animation.settings.standing_locomotion.sprint_to_run_ratio));
	t3d_anim_set_speed(&actor->animation.standing_locomotion.sprinting, actor->animation.data.speed);
	t3d_anim_set_speed(&actor->animation.standing_locomotion.walking, (actor->animation.data.speed * actor->animation.settings.standing_locomotion.sprint_to_walk_ratio));
}

void actorAnimation_setStandingIdle(Actor* actor)
{
	t3d_anim_update(&actor->animation.standing_locomotion.breathing_idle, timer.delta);
	t3d_anim_update(&actor->animation.standing_locomotion.standing_idle_left, timer.delta);
	t3d_anim_update(&actor->animation.standing_locomotion.standing_idle_right, timer.delta);
	t3d_skeleton_blend_3_(&actor->armature.main, 
		&actor->armature.main, 
		&actor->armature.blend, 
		&actor->armature.blend2, 
		actor->animation.settings.standing_locomotion.action_idle_max_blending_ratio * actor->animation.data.footing_blending_ratio, 
		actor->animation.settings.standing_locomotion.action_idle_max_blending_ratio * (1 - actor->animation.data.footing_blending_ratio));
}

void actorAnimation_setWalking(Actor* actor)
{
	t3d_anim_update(&actor->animation.standing_locomotion.walking, timer.delta);
	t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.data.locomotion_blending_ratio);
}

void actorAnimation_setRunning(Actor* actor)
{
	t3d_anim_update(&actor->animation.standing_locomotion.running, timer.delta);
	t3d_anim_update(&actor->animation.standing_locomotion.walking, timer.delta);
	t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.data.locomotion_blending_ratio);
}

void actorAnimation_setSprinting(Actor* actor)
{
	t3d_anim_update(&actor->animation.standing_locomotion.running, timer.delta);
	t3d_anim_update(&actor->animation.standing_locomotion.sprinting, timer.delta);
	t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.data.locomotion_blending_ratio);
}

void actorAnimation_setRunToRoll(Actor* actor)
{
	actorAnimation_setRollingBlendingRatio(actor);

	if (actor->animation.data.footing_blending_ratio <= 0.5f){
				
		t3d_anim_update(&actor->animation.roll.run_to_rolling_right, timer.delta);
		t3d_skeleton_blend(&actor->armature.main,
			&actor->armature.main,
			&actor->armature.blend2,
			actor->animation.data.roll_blending_ratio
		);
	}
	
	if (actor->animation.data.footing_blending_ratio > 0.5f){
			
		t3d_anim_update(&actor->animation.roll.run_to_rolling_left, timer.delta);
		t3d_skeleton_blend(&actor->armature.main, 
			&actor->armature.main, 
			&actor->armature.blend,
			actor->animation.data.roll_blending_ratio
		);
	}
}

void actorAnimation_setFallingIdle(Actor* actor)
{
	t3d_anim_update(&actor->animation.jump.falling_left, timer.delta);
	t3d_anim_update(&actor->animation.jump.falling_right, timer.delta);
	t3d_skeleton_blend_3_(&actor->armature.main, 
		&actor->armature.main, 
		&actor->armature.blend, 
		&actor->armature.blend2, 
		(actor->animation.data.jump_blending_ratio * actor->animation.data.footing_blending_ratio), 
		(actor->animation.data.jump_blending_ratio * (1 - actor->animation.data.footing_blending_ratio))
	);
}

void actorAnimation_setJump(Actor* actor)
{
	if ((actor->animation.jump.jump_left.time + timer.delta) < actor->animation.settings.jump.jump_anim_length){

		actorAnimation_setJumpBlendingRatio(actor);
		t3d_anim_update(&actor->animation.jump.jump_left, timer.delta);
		t3d_anim_update(&actor->animation.jump.jump_right, timer.delta);
		t3d_skeleton_blend_3_(&actor->armature.main, 
			&actor->armature.main,
			&actor->armature.blend, 
			&actor->armature.blend2, 
			(actor->animation.data.jump_blending_ratio * actor->animation.data.footing_blending_ratio), 
			(actor->animation.data.jump_blending_ratio * fabs(1 - actor->animation.data.footing_blending_ratio))
		);
	}
	else actorAnimation_setFallingIdle(actor);
}

void actorAnimation_setLanding(Actor* actor)
{		
	actorAnimation_setLandingBlendingRatio(actor);
	t3d_anim_update(&actor->animation.jump.land_left, timer.delta);
	t3d_anim_update(&actor->animation.jump.land_right, timer.delta);
	t3d_skeleton_blend_3_(&actor->armature.main, 
		&actor->armature.main, 
		&actor->armature.blend, 
		&actor->armature.blend2, 
		(actor->animation.data.jump_blending_ratio * actor->animation.data.footing_blending_ratio), 
		(actor->animation.data.jump_blending_ratio * (1 - actor->animation.data.footing_blending_ratio))
	);
}