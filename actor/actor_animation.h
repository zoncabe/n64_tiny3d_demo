#ifndef ACTOR_ANIMATION_H
#define ACTOR_ANIMATION_H


// animation lenght in frames on the prototype asset
// walking 31
// running 23
// sprinting 20

// convertion ratio between locomotion animation lenghts on the prototype asset

#define RTWratio 1.347826f    // run to walk 
#define WTRratio 0.741935f    // walk to run
#define STRratio 1.15f        // sprint to run
#define RTSratio 0.869565f    // run to sprint
#define STWratio 1.55f        // sprint to walk
#define WTSratio 0.645161f    // walk to sprint


// animation lenght in seconds on the prototype asset

#define WALKING_ANIM_LENGTH 1.033333f
#define RUNNING_ANIM_LENGTH 0.766666f
#define SPRINTING_ANIM_LENGTH 0.666666f

#define WALKING_ANIM_LENGTH_HALF 0.516666f
#define RUNNING_ANIM_LENGTH_HALF 0.383333f
#define SPRINTING_ANIM_LENGTH_HALF 0.333333f

#define ROLL_ANIM_LENGTH 5
#define JUMP_ANIM_LENGTH 6
#define LAND_ANIM_LENGTH 6


// function prototypes

void animationSet_init(T3DModel* model, AnimationSet* set);
void actorAnimation_init(Actor* actor);
void actorAnimation_setStandIdle(Actor* actor, const float frame_time);
void actorAnimation_setLocomotion(Actor* actor, const float frame_time);
void actorAnimation_setJump(Actor* actor, const float frame_time);
void actor_setAnimation(Actor* actor, const float frame_time, rspq_syncpoint_t* syncpoint);


// function implemenations

void animationSet_init(T3DModel* model, AnimationSet* set)
{
	set->breathing_idle = t3d_anim_create(model, "breathing-idle");
	set->transition_left = t3d_anim_create(model, "transition-left");
	set->transition_right = t3d_anim_create(model, "transition-right");

	set->action_idle_left = t3d_anim_create(model, "action-idle-left");
	set->action_idle_right = t3d_anim_create(model, "action-idle-right");

	set->walking = t3d_anim_create(model, "walking");
	set->running = t3d_anim_create(model, "running");
	set->sprinting = t3d_anim_create(model, "sprinting");

	set->idle_jump = t3d_anim_create(model, "idle-to-jump");
	set->action_jump_left = t3d_anim_create(model, "action-to-jump-left");
	set->action_jump_right = t3d_anim_create(model, "action-to-jump-right");

	set->falling_left = t3d_anim_create(model, "falling-idle-left");
	set->falling_right = t3d_anim_create(model, "falling-idle-right");

	set->idle_land = t3d_anim_create(model, "falling-to-idle");
	set->land_left = t3d_anim_create(model, "land-left");
	set->land_right = t3d_anim_create(model, "land-right");

	t3d_anim_set_looping(&set->idle_jump, false);
	t3d_anim_set_looping(&set->action_jump_left, false);
	t3d_anim_set_looping(&set->action_jump_right, false);

	t3d_anim_set_looping(&set->idle_land, false);
	t3d_anim_set_looping(&set->land_left, false);
	t3d_anim_set_looping(&set->land_right, false);
}

void animationSet_attach(T3DSkeleton* main, T3DSkeleton* blend, T3DSkeleton* blend2, AnimationSet* set)
{
	t3d_anim_attach(&set->breathing_idle, main);

	t3d_anim_attach(&set->transition_left, blend);
	t3d_anim_attach(&set->transition_right, blend);

	t3d_anim_attach(&set->action_idle_left, blend);
	t3d_anim_attach(&set->action_idle_right, blend2);
	
	t3d_anim_attach(&set->walking, blend);
	
	t3d_anim_attach(&set->running, main);
	
	t3d_anim_attach(&set->sprinting, blend);
	
	t3d_anim_attach(&set->action_jump_left, blend2);
	t3d_anim_attach(&set->action_jump_right, blend2);
	
	t3d_anim_attach(&set->falling_left, blend2);
	t3d_anim_attach(&set->falling_right, blend2);
	
	t3d_anim_attach(&set->land_left, blend2);
	t3d_anim_attach(&set->land_right, blend2);
}

void actorAnimation_init(Actor* actor)
{
	actor->armature.main = t3d_skeleton_create(actor->model);
	actor->armature.blend = t3d_skeleton_clone(&actor->armature.main, false);
	actor->armature.blend2 = t3d_skeleton_clone(&actor->armature.main, false);

	animationSet_init(actor->model, &actor->animation.set);

	animationSet_attach(&actor->armature.main, &actor->armature.blend, &actor->armature.blend2, &actor->animation.set);
}

// custom T3D function, for my engine
void t3d_skeleton_blend_3(const T3DSkeleton *skelRes, const T3DSkeleton *skelA, const T3DSkeleton *skelB, const T3DSkeleton *skelC, float factorB, float factorC) 
{
  for(int i = 0; i < skelRes->skeletonRef->boneCount; i++) {
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

void actorAnimation_setLocomotionBlendingRatio(Actor* actor)
{

	if (actor->horizontal_speed == 0){
		
		actor->animation.blending_ratio = 0;
	}
	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){
		
		actor->animation.blending_ratio = (actor->horizontal_speed / actor->settings.walk_target_speed);
	}
	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){

		actor->animation.blending_ratio = 1.0f - ((actor->horizontal_speed - actor->settings.walk_target_speed) / (actor->settings.run_target_speed - actor->settings.walk_target_speed));
	}
	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		actor->animation.blending_ratio = ((actor->horizontal_speed - actor->settings.run_target_speed) / (actor->settings.sprint_target_speed - actor->settings.run_target_speed));		
	}

	if (actor->animation.blending_ratio > 1.0f) actor->animation.blending_ratio = 1.0f;
}



float actorAnimation_setActionIdleBlendingRatio(float action_time, float action_leght)
{
	float phase = (1 / action_leght) * action_time;

	if (phase <= 0.25f) return 0.5f + 2.0f * phase;
	else if (phase <= 0.75f) return 1.0f - 2.0f * (phase - 0.25f);
	else return 2.0f * (phase - 0.75f);
}

void actorAnimation_setStandingLocomotion(Actor* actor, const float frame_time)
{

	if (actor->horizontal_speed == 0){
			
		if (actor->animation.current != STAND_IDLE) {

			actor->animation.previous = actor->animation.current;
			actor->animation.current = STAND_IDLE;
			if (actor->animation.blending_ratio > 0) actor->animation.blending_ratio = 0; 
			//t3d_anim_set_time(&actor->animation.set.walking, (0.0f));
		}
		
		float action_blending_ratio = actorAnimation_setActionIdleBlendingRatio(actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
		t3d_anim_update(&actor->animation.set.action_idle_left, frame_time);
		t3d_anim_update(&actor->animation.set.action_idle_right, frame_time);
		t3d_skeleton_blend_3(&actor->armature.main, &actor->armature.main, &actor->armature.blend, &actor->armature.blend2, 0.9f * action_blending_ratio, 0.9f * fabs(1 - action_blending_ratio));
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){

		if (actor->animation.current != WALKING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = WALKING;
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		t3d_anim_set_speed(&actor->animation.set.walking, actor->animation.blending_ratio);
		

		float action_blending_ratio = actorAnimation_setActionIdleBlendingRatio(actor->animation.set.walking.time, WALKING_ANIM_LENGTH);

		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
		t3d_anim_update(&actor->animation.set.action_idle_left, frame_time);
		t3d_anim_update(&actor->animation.set.action_idle_right, frame_time);
		t3d_skeleton_blend_3(&actor->armature.main, &actor->armature.main, &actor->armature.blend, &actor->armature.blend2, 0.9f * action_blending_ratio, 0.9f * fabs(1 - action_blending_ratio));

		t3d_anim_update(&actor->animation.set.walking, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){

		if (actor->animation.current != RUNNING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = RUNNING;
			
			if (actor->animation.previous == WALKING) t3d_anim_set_time(&actor->animation.set.running, (actor->animation.set.walking.time * WTRratio));
			else if (actor->animation.previous == SPRINTING) t3d_anim_set_time(&actor->animation.set.walking, (actor->animation.set.sprinting.time * STWratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed  = (1.0f - ((1.0f - WTRratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running, actor->animation.speed );
		t3d_anim_set_speed(&actor->animation.set.walking, (actor->animation.speed  * RTWratio));

		t3d_anim_update(&actor->animation.set.running, frame_time);
		t3d_anim_update(&actor->animation.set.walking, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		if (actor->animation.current != SPRINTING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = SPRINTING;
			t3d_anim_set_time(&actor->animation.set.sprinting, (actor->animation.set.running.time * RTSratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed = (RTSratio + ((1.0f - RTSratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running, (actor->animation.speed * STRratio));
		t3d_anim_set_speed(&actor->animation.set.sprinting, actor->animation.speed);

		t3d_anim_update(&actor->animation.set.running, frame_time);
		t3d_anim_update(&actor->animation.set.sprinting, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

}

void actorAnimation_setJump(Actor* actor, const float frame_time)
{
	if (actor->horizontal_speed == 0){
			
		if (actor->animation.current != STAND_IDLE) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = STAND_IDLE;
			t3d_anim_set_time(&actor->animation.set.walking, (0.0f));
			if (actor->animation.blending_ratio > 0) actor->animation.blending_ratio = 0; 
		}
		
		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){

		if (actor->animation.current != WALKING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = WALKING;
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		t3d_anim_set_speed(&actor->animation.set.walking, actor->animation.blending_ratio);
	
		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
		t3d_anim_update(&actor->animation.set.walking, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){

		if (actor->animation.current != RUNNING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = RUNNING;
			
			if (actor->animation.previous == WALKING) t3d_anim_set_time(&actor->animation.set.running, (actor->animation.set.walking.time * WTRratio));
			else if (actor->animation.previous == SPRINTING) t3d_anim_set_time(&actor->animation.set.walking, (actor->animation.set.sprinting.time * STWratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed  = (1.0f - ((1.0f - WTRratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running, actor->animation.speed );
		t3d_anim_set_speed(&actor->animation.set.walking, (actor->animation.speed  * RTWratio));

		t3d_anim_update(&actor->animation.set.running, frame_time);
		t3d_anim_update(&actor->animation.set.walking, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		if (actor->animation.current != SPRINTING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = SPRINTING;
			t3d_anim_set_time(&actor->animation.set.sprinting, (actor->animation.set.running.time * RTSratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed = (RTSratio + ((1.0f - RTSratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running, (actor->animation.speed * STRratio));
		t3d_anim_set_speed(&actor->animation.set.sprinting, actor->animation.speed);

		t3d_anim_update(&actor->animation.set.running, frame_time);
		t3d_anim_update(&actor->animation.set.sprinting, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}
}

void actor_setAnimation(Actor* actor, const float frame_time, rspq_syncpoint_t* syncpoint)
{
    switch(actor->state) {

        case STAND_IDLE: {
			actorAnimation_setStandingLocomotion(actor, frame_time);
            break;
        }

        case WALKING: {
			actorAnimation_setStandingLocomotion(actor, frame_time);
            break;
        }

        case RUNNING: {
			actorAnimation_setStandingLocomotion(actor, frame_time);
            break;
        }

        case SPRINTING: {
			actorAnimation_setStandingLocomotion(actor, frame_time);
            break;
        }

        case JUMPING: {
			actorAnimation_setJump(actor, frame_time);
			if (actor->animation.current != JUMPING) {
				actor->animation.previous = actor->animation.current;
				actor->animation.current = JUMPING;
			}
            break;
        }
		
        case FALLING: {
			actorAnimation_setJump(actor, frame_time);
			if (actor->animation.current != FALLING) {
				actor->animation.previous = actor->animation.current;
				actor->animation.current = FALLING;
			}
            break;
        }
    }
	
	if(syncpoint)rspq_syncpoint_wait(*syncpoint);
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

			//.roll_acceleration_rate = 20,
			//.roll_acceleration_grip_rate = 2,

			.jump_acceleration_rate = 50,
			.aerial_control_rate = 0.5,

			.walk_target_speed = 175,
			.run_target_speed = 330,
			.sprint_target_speed = 480,

			.run_sync_timer_max = 5.0f,

			//.idle_to_roll_target_speed = 300,
			//.idle_to_roll_grip_target_speed = 50,
			//.walk_to_roll_target_speed = 500,
			//.run_to_roll_target_speed = 780,
			//.sprint_to_roll_target_speed = 980,

			.jump_max_speed = 400,
			.jump_timer_max = 0.2f,
        },

		.animation = {
			.current = 1,
			.previous = 1,
			.speed = 0.0f,
			.blending_ratio = 0.0f,
			.transition = false,
		},

		.input = {

			.jump_timer = 0,
			.run_sync_timer = 0,

		}
    };
	
	actorAnimation_init(&actor);
    
	rspq_block_begin();
    t3d_model_draw_skinned(actor.model, &actor.armature.main);
    actor.dl = rspq_block_end();

    return actor;
}

void actor_update(Actor* actor, ControllerData *control, float camera_angle_around, float camera_offset, float frame_time, rspq_syncpoint_t* syncpoint)
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