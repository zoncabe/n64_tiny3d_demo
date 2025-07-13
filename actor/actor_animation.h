#ifndef ACTOR_ANIMATION_H
#define ACTOR_ANIMATION_H

// animation lenght in frames on the prototype asset
// walking 31
// running 23
// sprinting 20
// jump 19 / low 4 / air  10
// land 32 / floor 8 / standing 24
// rolling 35 / grip 24

// convertion ratio between locomotion animation lenghts on the prototype asset

#define RTWratio 1.347826f // run to walk
#define WTRratio 0.741935f // walk to run
#define STRratio 1.15f	   // sprint to run
#define RTSratio 0.869565f // run to sprint
#define STWratio 1.55f	   // sprint to walk
#define WTSratio 0.645161f // walk to sprint

// animation lenght in seconds on the prototype asset

#define WALKING_ANIM_LENGTH 1.033333f
#define WALKING_ANIM_LENGTH_HALF 0.516666f

#define RUNNING_ANIM_LENGTH_HALF 0.4f
#define RUNNING_ANIM_LENGTH 0.766666f

#define SPRINTING_ANIM_LENGTH 0.666666f
#define SPRINTING_ANIM_LENGTH_HALF 0.333333f

#define RUN_TO_ROLLING_ANIM_GROUND 0.3f
#define RUN_TO_ROLLING_ANIM_GRIP 0.6f
#define RUN_TO_ROLLING_ANIM_STAND 0.9f
#define RUN_TO_ROLLING_ANIM_LENGHT 1.166666f

#define STAND_TO_ROLLING_ANIM_GRIP 1.433333f
#define STAND_TO_ROLLING_ANIM_LENGHT 2.066666f

#define JUMP_ANIM_LENGTH 0.633333f
#define JUMP_ANIM_CROUCH 0.1f
#define JUMP_ANIM_AIR 0.233333f
#define JUMP_MAX_BLENDING_RATIO 0.8f

#define LAND_ANIM_LENGTH 0.9f
#define LAND_ANIM_GROUND 0.266666f
#define LAND_ANIM_STAND 0.833333f



// function prototypes

void animationSet_init(T3DModel *model, AnimationSet *set);
void actorAnimation_init(Actor *actor);
void actor_setAnimation(Actor *actor, const float frame_time, rspq_syncpoint_t *syncpoint);

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

// function implemenations

void animationSet_init(T3DModel *model, AnimationSet *set)
{
	set->breathing_idle = t3d_anim_create(model, "breathing-idle");
	set->transition_left = t3d_anim_create(model, "transition-left");
	set->transition_right = t3d_anim_create(model, "transition-right");

	set->standing_idle_left = t3d_anim_create(model, "standing-idle-left");
	set->standing_idle_right = t3d_anim_create(model, "standing-idle-right");

	set->walking = t3d_anim_create(model, "walking");
	set->running = t3d_anim_create(model, "running");
	set->sprinting = t3d_anim_create(model, "sprinting");

	set->jump_left = t3d_anim_create(model, "jump-left");
	set->jump_right = t3d_anim_create(model, "jump-right");

	set->falling_left = t3d_anim_create(model, "falling-idle-left");
	set->falling_right = t3d_anim_create(model, "falling-idle-right");

	set->run_to_rolling_left = t3d_anim_create(model, "run-to-roll-left");
	set->run_to_rolling_right = t3d_anim_create(model, "run-to-roll-right");

	set->stand_to_rolling_left = t3d_anim_create(model, "stand-to-roll-left");
	set->stand_to_rolling_right = t3d_anim_create(model, "stand-to-roll-right");

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

void animationSet_attach(T3DSkeleton *main, T3DSkeleton *blend, T3DSkeleton *blend2, AnimationSet *set)
{
	t3d_anim_attach(&set->breathing_idle, main);

	t3d_anim_attach(&set->transition_left, blend);
	t3d_anim_attach(&set->transition_right, blend2);

	t3d_anim_attach(&set->standing_idle_left, blend);
	t3d_anim_attach(&set->standing_idle_right, blend2);

	t3d_anim_attach(&set->walking, blend);

	t3d_anim_attach(&set->running, main);

	t3d_anim_attach(&set->sprinting, blend);

	t3d_anim_attach(&set->stand_to_rolling_left, blend);
	t3d_anim_attach(&set->stand_to_rolling_right, blend2);
	
	t3d_anim_attach(&set->run_to_rolling_left, blend);
	t3d_anim_attach(&set->run_to_rolling_right, blend2);

	t3d_anim_attach(&set->jump_left, blend);
	t3d_anim_attach(&set->jump_right, blend2);

	t3d_anim_attach(&set->falling_left, blend);
	t3d_anim_attach(&set->falling_right, blend2);

	t3d_anim_attach(&set->land_left, blend);
	t3d_anim_attach(&set->land_right, blend2);
}

void actorAnimation_init(Actor *actor)
{
	//actor->armature.main =  t3d_skeleton_create_buffered(modelPlayer, display_get_num_buffers()); 
	actor->armature.main = t3d_skeleton_create(actor->model);
	actor->armature.blend = t3d_skeleton_clone(&actor->armature.main, false);
	actor->armature.blend2 = t3d_skeleton_clone(&actor->armature.main, false);

	animationSet_init(actor->model, &actor->animation.set);

	animationSet_attach(&actor->armature.main, &actor->armature.blend, &actor->armature.blend2, &actor->animation.set);
}

void actorAnimation_setLocomotionBlendingRatio(Actor *actor)
{
	if (actor->horizontal_speed == 0) actor->animation.locomotion_blending_ratio = 0;

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed) actor->animation.locomotion_blending_ratio = (actor->horizontal_speed / actor->settings.walk_target_speed);

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed) actor->animation.locomotion_blending_ratio = 1.0f - ((actor->horizontal_speed - actor->settings.walk_target_speed) / (actor->settings.run_target_speed - actor->settings.walk_target_speed));

	else if (actor->horizontal_speed > actor->settings.run_target_speed) actor->animation.locomotion_blending_ratio = ((actor->horizontal_speed - actor->settings.run_target_speed) / (actor->settings.sprint_target_speed - actor->settings.run_target_speed));

	if (actor->animation.locomotion_blending_ratio > 1.0f) actor->animation.locomotion_blending_ratio = 1.0f;
	if (actor->animation.locomotion_blending_ratio < 0.0f) actor->animation.locomotion_blending_ratio = 0.0f;
}

void actorAnimation_setFootingBlendingRatio(Actor *actor, float action_time, float action_lenght)
{
	float phase = 1 / action_lenght * action_time;

	if (phase <= 0.25f)
		actor->animation.footing_blending_ratio = 0.5f + 2.0f * phase;
	else if (phase <= 0.75f)
		actor->animation.footing_blending_ratio = 1.0f - 2.0f * (phase - 0.25f);
	else if (phase <= 1)
		actor->animation.footing_blending_ratio = 2.0f * (phase - 0.75f);
}

void actorAnimation_setRollingBlendingRatio(Actor *actor, float frame_time)
{

	if (actor->input.roll_timer < RUN_TO_ROLLING_ANIM_GROUND && actor->animation.action_blending_ratio <= 1.0f) actor->animation.action_blending_ratio += (frame_time * 3);
	
	if (actor->input.roll_timer > RUN_TO_ROLLING_ANIM_STAND && actor->animation.action_blending_ratio > 0.0f) actor->animation.action_blending_ratio -= (frame_time * 1.875f);

	if (actor->animation.action_blending_ratio > 1.0f) {
		
		actor->animation.action_blending_ratio = 1.0f;

		//if (actor->animation.footing_blending_ratio >= 0.5f) t3d_anim_set_time(&actor->animation.set.running, RUN_TO_ROLLING_ANIM_LENGHT);
		//if (actor->animation.footing_blending_ratio < 0.5f) t3d_anim_set_time(&actor->animation.set.running, (0.4f));
	}

	if (actor->animation.action_blending_ratio < 0.0f) actor->animation.action_blending_ratio = 0.0f;
}

void actorAnimation_setJumpBlendingRatio(Actor *actor, float frame_time)
{
	if (actor->animation.action_blending_ratio < 0.7f) actor->animation.action_blending_ratio += (frame_time * 3);
	if (actor->animation.locomotion_blending_ratio > 1.0f) actor->animation.locomotion_blending_ratio = 1.0f;
}

void actorAnimation_setLandingBlendingRatio(Actor *actor, float frame_time)
{
	if (actor->animation.action_blending_ratio > 0) actor->animation.action_blending_ratio -= (frame_time * 0.7f);
	
	else actor->animation.action_blending_ratio = 0;
}

void actorAnimation_setWalkingSpeed(Actor *actor)
{
	t3d_anim_set_speed(&actor->animation.set.walking, actor->animation.locomotion_blending_ratio);
}

void actorAnimation_setRunningSpeed(Actor *actor)
{
	actor->animation.speed = (1.0f - ((1.0f - WTRratio) * actor->animation.locomotion_blending_ratio));
	t3d_anim_set_speed(&actor->animation.set.running, actor->animation.speed);
	t3d_anim_set_speed(&actor->animation.set.walking, (actor->animation.speed * RTWratio));
}

void actorAnimation_setSprintingSpeed(Actor *actor)
{
	actor->animation.speed = (RTSratio + ((1.0f - RTSratio) * actor->animation.locomotion_blending_ratio));
	t3d_anim_set_speed(&actor->animation.set.running, (actor->animation.speed * STRratio));
	t3d_anim_set_speed(&actor->animation.set.sprinting, actor->animation.speed);
	t3d_anim_set_speed(&actor->animation.set.walking, (actor->animation.speed * STWratio));
}


void actorAnimation_setStandingIdle(Actor *actor, float frame_time)
{
	t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
	t3d_anim_update(&actor->animation.set.standing_idle_left, frame_time);
	t3d_anim_update(&actor->animation.set.standing_idle_right, frame_time);
	t3d_skeleton_blend_3(&actor->armature.main, &actor->armature.main, &actor->armature.blend, &actor->armature.blend2, 0.9f * actor->animation.footing_blending_ratio, 0.9f * fabs(1 - actor->animation.footing_blending_ratio));
}

void actorAnimation_setWalking(Actor *actor, float frame_time)
{
	actorAnimation_setLocomotionBlendingRatio(actor);
	t3d_anim_update(&actor->animation.set.walking, frame_time);
	t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.locomotion_blending_ratio);
}

void actorAnimation_setRunning(Actor *actor, float frame_time)
{
	actorAnimation_setLocomotionBlendingRatio(actor);
	t3d_anim_update(&actor->animation.set.running, frame_time);
	t3d_anim_update(&actor->animation.set.walking, frame_time);
	t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.locomotion_blending_ratio);
}

void actorAnimation_setSprinting(Actor *actor, float frame_time)
{
	actorAnimation_setLocomotionBlendingRatio(actor);
	t3d_anim_update(&actor->animation.set.running, frame_time);
	t3d_anim_update(&actor->animation.set.sprinting, frame_time);
	t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.locomotion_blending_ratio);
}

void actorAnimation_setRunToRolling(Actor *actor, float frame_time)
{
	actorAnimation_setRollingBlendingRatio(actor, frame_time);
	
	if (actor->animation.action_blending_ratio > 0.0f){

		
		if (actor->animation.footing_blending_ratio <= 0.5f){
			
			if (actor->animation.set.run_to_rolling_right.isPlaying && (actor->animation.set.run_to_rolling_right.time + frame_time) < (RUN_TO_ROLLING_ANIM_LENGHT)){
				
				actorAnimation_setRollingBlendingRatio(actor, frame_time);
				t3d_anim_update(&actor->animation.set.run_to_rolling_right, frame_time);
				t3d_skeleton_blend(&actor->armature.main, 
					&actor->armature.main, 
					&actor->armature.blend2,
					actor->animation.action_blending_ratio
				);
			}
		}
		
		if (actor->animation.footing_blending_ratio > 0.5f){
			
			if (actor->animation.set.run_to_rolling_left.isPlaying  && (actor->animation.set.run_to_rolling_left.time + frame_time) < (RUN_TO_ROLLING_ANIM_LENGHT)){
				
				actorAnimation_setRollingBlendingRatio(actor, frame_time);
				t3d_anim_update(&actor->animation.set.run_to_rolling_left, frame_time);
				t3d_skeleton_blend(&actor->armature.main, 
					&actor->armature.main, 
					&actor->armature.blend,
					actor->animation.action_blending_ratio
				);
			}
		}
	}
}

void actorAnimation_setFallingIdle(Actor *actor, float frame_time)
{
	t3d_anim_update(&actor->animation.set.falling_left, frame_time);
	t3d_anim_update(&actor->animation.set.falling_right, frame_time);
	t3d_skeleton_blend_3(&actor->armature.main, &actor->armature.main, &actor->armature.blend, &actor->armature.blend2, (actor->animation.action_blending_ratio * actor->animation.footing_blending_ratio), (actor->animation.action_blending_ratio * fabs(1 - actor->animation.footing_blending_ratio)));
}

void actorAnimation_setJump(Actor *actor, float frame_time)
{
	if (actor->animation.set.jump_left.isPlaying && (actor->animation.set.jump_left.time + frame_time) < (JUMP_ANIM_LENGTH)){

		actorAnimation_setJumpBlendingRatio(actor, frame_time);
		t3d_anim_update(&actor->animation.set.jump_left, frame_time);
		t3d_anim_update(&actor->animation.set.jump_right, frame_time);
		t3d_skeleton_blend_3(&actor->armature.main, 
			&actor->armature.main,
			&actor->armature.blend, 
			&actor->armature.blend2, 
			(actor->animation.action_blending_ratio * actor->animation.footing_blending_ratio), 
			(actor->animation.action_blending_ratio * fabs(1 - actor->animation.footing_blending_ratio)));
	}

	else actorAnimation_setFallingIdle(actor, frame_time);
}

void actorAnimation_setLanding(Actor *actor, float frame_time)
{		
	if (actor->animation.set.land_left.isPlaying){
			
		actorAnimation_setLandingBlendingRatio(actor, frame_time);
		t3d_anim_update(&actor->animation.set.land_left, frame_time);
		t3d_anim_update(&actor->animation.set.land_right, frame_time);
		t3d_skeleton_blend_3(&actor->armature.main, &actor->armature.main, &actor->armature.blend, &actor->armature.blend2, (actor->animation.action_blending_ratio * actor->animation.footing_blending_ratio), (actor->animation.action_blending_ratio * fabs(1 - actor->animation.footing_blending_ratio)));
	}
}


void actorAnimation_setStandingLocomotion(Actor *actor, const float frame_time)
{
	if (actor->horizontal_speed == 0){

		if (actor->animation.current != STAND_IDLE){

			actor->animation.previous = actor->animation.current;
			actor->animation.current = STAND_IDLE;
		}
		actorAnimation_setStandingIdle(actor, frame_time);
		actorAnimation_setLanding(actor, frame_time);
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){

		if (actor->animation.current != WALKING){

			actor->animation.previous = actor->animation.current;
			actor->animation.current = WALKING;
		}
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);
		actorAnimation_setWalkingSpeed(actor);

		actorAnimation_setStandingIdle(actor, frame_time);
		actorAnimation_setWalking(actor, frame_time);
		actorAnimation_setLanding(actor, frame_time);
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){

		if (actor->animation.current != RUNNING){

			actor->animation.previous = actor->animation.current;
			actor->animation.current = RUNNING;

			if (actor->animation.previous == WALKING) t3d_anim_set_time(&actor->animation.set.running, (actor->animation.set.walking.time * WTRratio));
			else if (actor->animation.previous == SPRINTING) t3d_anim_set_time(&actor->animation.set.walking, (actor->animation.set.sprinting.time * STWratio));
		}
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);
		actorAnimation_setRunningSpeed(actor);

		actorAnimation_setRunning(actor, frame_time);
		actorAnimation_setLanding(actor, frame_time);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		if (actor->animation.current != SPRINTING){
			actor->animation.previous = actor->animation.current;
			actor->animation.current = SPRINTING;
			t3d_anim_set_time(&actor->animation.set.sprinting, (actor->animation.set.running.time * RTSratio));
		}
		//actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.running.time, RUNNING_ANIM_LENGTH); 
		// workaround to get consistent footing blending :')
		t3d_anim_update(&actor->animation.set.walking, frame_time);  
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);
		actorAnimation_setSprintingSpeed(actor);

		actorAnimation_setSprinting(actor, frame_time);
		actorAnimation_setLanding(actor, frame_time);
	}
}

void actorAnimation_setRolling(Actor *actor, const float frame_time)
{
	if (actor->animation.current != ROLLING){
		
		actor->animation.previous = actor->animation.current;
		actor->animation.current = ROLLING;
		
		t3d_anim_set_playing(&actor->animation.set.run_to_rolling_left, true);
		t3d_anim_set_time(&actor->animation.set.run_to_rolling_left, 0.0f);

		t3d_anim_set_playing(&actor->animation.set.run_to_rolling_right, true);
		t3d_anim_set_time(&actor->animation.set.run_to_rolling_right, 0.0f);
		actor->animation.action_blending_ratio = 0.0f;
	}
	
	if (actor->horizontal_speed <= actor->settings.run_target_speed){		
		
		actorAnimation_setRunningSpeed(actor);
		
		actorAnimation_setRunning(actor, frame_time);
		actorAnimation_setLanding(actor, frame_time);
		actorAnimation_setRunToRolling(actor, frame_time);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		actor->animation.set.running.speed = fabs(1 - actor->animation.action_blending_ratio);
		actor->animation.set.sprinting.speed = fabs(1 - actor->animation.action_blending_ratio);

		actorAnimation_setSprinting(actor, frame_time);
		actorAnimation_setLanding(actor, frame_time);
		actorAnimation_setRunToRolling(actor, frame_time);
	}
}

void actorAnimation_setJumping(Actor *actor, const float frame_time)
{
	if (actor->animation.current != JUMPING){

		actor->animation.previous = actor->animation.current;
		actor->animation.current = JUMPING;
		
		t3d_anim_set_playing(&actor->animation.set.jump_left, true);
		t3d_anim_set_playing(&actor->animation.set.jump_right, true);
		t3d_anim_set_time(&actor->animation.set.jump_left, 0.0f);
		t3d_anim_set_time(&actor->animation.set.jump_right, 0.0f);
		t3d_anim_set_time(&actor->animation.set.falling_left, 0.0f);
		t3d_anim_set_time(&actor->animation.set.falling_right, 0.0f);
	}

	if (actor->horizontal_speed == 0){

		if (actor->animation.set.land_left.isPlaying && actor->animation.set.jump_left.time < JUMP_ANIM_CROUCH){

			actorAnimation_setLandingBlendingRatio(actor, frame_time);
			actorAnimation_setLanding(actor, frame_time);
		}

		
		actorAnimation_setStandingIdle(actor, frame_time);	
		actorAnimation_setLanding(actor, frame_time);
		actorAnimation_setJump(actor, frame_time);
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){

		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		if (actor->animation.set.jump_left.time < JUMP_ANIM_CROUCH){

			actorAnimation_setLanding(actor, frame_time);
		}

		actorAnimation_setWalkingSpeed(actor);
		actor->animation.set.walking.speed *= (1 - actor->animation.action_blending_ratio);

		actorAnimation_setStandingIdle(actor, frame_time);
		actorAnimation_setWalking(actor, frame_time);
		actorAnimation_setJump(actor, frame_time);
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){
		
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		if (actor->animation.set.jump_left.time < JUMP_ANIM_CROUCH){
		
			actorAnimation_setLanding(actor, frame_time);
		}

		actorAnimation_setRunningSpeed(actor);
		actor->animation.set.walking.speed *= (1 - actor->animation.action_blending_ratio);
		actor->animation.set.running.speed *= (1 - actor->animation.action_blending_ratio);

		actorAnimation_setRunning(actor, frame_time);
		actorAnimation_setJump(actor, frame_time);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		if (actor->animation.set.jump_left.time < JUMP_ANIM_CROUCH){
		
			actorAnimation_setLanding(actor, frame_time);
		}

		//actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.running.time, RUNNING_ANIM_LENGTH);
		t3d_anim_update(&actor->animation.set.walking, frame_time); // damn workaround
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		actorAnimation_setSprintingSpeed(actor);
		actor->animation.set.walking.speed *= (1 - actor->animation.action_blending_ratio);
		actor->animation.set.running.speed *= (1 - actor->animation.action_blending_ratio);
		actor->animation.set.sprinting.speed *= (1 - actor->animation.action_blending_ratio);

		actorAnimation_setSprinting(actor, frame_time);
		actorAnimation_setJump(actor, frame_time);
	}
}

void actorAnimation_setFalling(Actor *actor, const float frame_time)
{
	if (actor->animation.current != FALLING){

		actor->animation.previous = actor->animation.current;
		actor->animation.current = FALLING;

		t3d_anim_set_playing(&actor->animation.set.land_left, true);
		t3d_anim_set_playing(&actor->animation.set.land_right, true);
		t3d_anim_set_time(&actor->animation.set.land_left, 0.0f);
		t3d_anim_set_time(&actor->animation.set.land_right, 0.0f);
	}

	if (actor->horizontal_speed == 0){

		actorAnimation_setStandingIdle(actor, frame_time);

		// workaround until collision happens
		if (actor->body.position.z < 80) actorAnimation_setLanding(actor, frame_time);

		else actorAnimation_setFallingIdle(actor, frame_time);
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){
		
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		actorAnimation_setWalkingSpeed(actor);
		actor->animation.set.walking.speed *= (1 - actor->animation.action_blending_ratio);

		actorAnimation_setStandingIdle(actor, frame_time);

		t3d_anim_update(&actor->animation.set.walking, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.locomotion_blending_ratio);
		
		if (actor->body.position.z < 80) actorAnimation_setLanding(actor, frame_time);

		else actorAnimation_setFallingIdle(actor, frame_time);
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){
		
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		actorAnimation_setRunningSpeed(actor);
		actor->animation.set.walking.speed *= (1 - actor->animation.action_blending_ratio);
		actor->animation.set.running.speed *= (1 - actor->animation.action_blending_ratio);

		actorAnimation_setRunning(actor, frame_time);
		
		if (actor->body.position.z < 80) actorAnimation_setLanding(actor, frame_time);
		
		else actorAnimation_setFallingIdle(actor, frame_time);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		//actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.running.time, RUNNING_ANIM_LENGTH);
		t3d_anim_update(&actor->animation.set.walking, frame_time);
		actorAnimation_setFootingBlendingRatio(actor, actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		actorAnimation_setSprintingSpeed(actor);
		actor->animation.set.walking.speed *= (1 - actor->animation.action_blending_ratio);
		actor->animation.set.running.speed *= (1 - actor->animation.action_blending_ratio);
		actor->animation.set.sprinting.speed *= (1 - actor->animation.action_blending_ratio);

		actorAnimation_setSprinting(actor, frame_time);

		if (actor->body.position.z < 80) actorAnimation_setLanding(actor, frame_time);
		
		else actorAnimation_setFallingIdle(actor, frame_time);
	}
}

void actor_setAnimation(Actor *actor, const float frame_time, rspq_syncpoint_t *syncpoint)
{
	switch (actor->state)
	{

	case STAND_IDLE:
	{
		actorAnimation_setStandingLocomotion(actor, frame_time);
		break;
	}

	case WALKING:
	{
		actorAnimation_setStandingLocomotion(actor, frame_time);
		break;
	}

	case RUNNING:
	{
		actorAnimation_setStandingLocomotion(actor, frame_time);
		break;
	}

	case SPRINTING:
	{
		actorAnimation_setStandingLocomotion(actor, frame_time);
		break;
	}

	case ROLLING:
	{
		actorAnimation_setRolling(actor, frame_time);
		break;
	}

	case JUMPING:
	{
		actorAnimation_setJumping(actor, frame_time);
		if (actor->animation.current != JUMPING)
		{
			actor->animation.previous = actor->animation.current;
			actor->animation.current = JUMPING;
		}
		break;
	}

	case FALLING:
	{
		actorAnimation_setFalling(actor, frame_time);
		if (actor->animation.current != FALLING)
		{
			actor->animation.previous = actor->animation.current;
			actor->animation.current = FALLING;
		}
		break;
	}
	}

	if (syncpoint)
		rspq_syncpoint_wait(*syncpoint);
	t3d_skeleton_update(&actor->armature.main);
}

// TEMPORARY(?) PLACE FOR THESE FUNCTIONS UNTIL I SOLVE THE MAIN STRUCTURE FOR THE PROJECT
// ALSO THIS ACTOR CREATE FUNCTION ONLY WORKS FOR THE PROTOTYPE ASSET

Actor actor_create(uint32_t id, const char *model_path)
{
	Actor actor = {

		.id = id,
		.model = t3d_model_load(model_path),
		.transform_matrix = malloc_uncached(sizeof(T3DMat4FP)), // needed for t3d

		.scale = {1.0f, 1.0f, 1.0f},

		.body = {
			.position = {0.0f, 0.0f, 0.0f},
			.velocity = {0.0f, 0.0f, 0.0f},
			.rotation = {0.0f, 0.0f, 0.0f},
		},

		.settings = {
			.idle_acceleration_rate = 8,
			.walk_acceleration_rate = 4,
			.run_acceleration_rate = 6,
			.sprint_acceleration_rate = 8,
			.roll_acceleration_grip_rate = 2,

			.jump_acceleration_rate = 50,
			.aerial_control_rate = 0.5f,

			.walk_target_speed = 175,
			.run_target_speed = 330,
			.sprint_target_speed = 480,

			.roll_change_grip_time = RUN_TO_ROLLING_ANIM_GRIP,
			.roll_timer_max = RUN_TO_ROLLING_ANIM_LENGHT,

			.jump_max_speed = 400,
			.jump_timer_max = JUMP_ANIM_AIR,
		},

		.animation = {
			.current = 1,
			.previous = 1,
			.speed = 0.0f,
			.action_blending_ratio = 0.0f,
			.footing_blending_ratio = 0.5f,
			.transition = false,
		},

		.input = {

			.jump_timer = 0,

		}};

	actorAnimation_init(&actor);

	rspq_block_begin();
	t3d_model_draw_skinned(actor.model, &actor.armature.main);
	actor.dl = rspq_block_end();

	return actor;
}

void actor_update(Actor *actor, ControllerData *control, float camera_angle_around, float camera_offset, float frame_time, rspq_syncpoint_t *syncpoint)
{
	actor_setControlData(actor, control, camera_angle_around, camera_offset);
	actor_setAnimation(actor, frame_time, syncpoint);
	actor_setMotion(actor, frame_time);
}

/* speed range

	if (actor->horizontal_speed == 0){
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){
	}
*/
/* animation switch

	switch(actor->animation.current) {

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
#endif