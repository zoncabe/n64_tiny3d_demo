#ifndef ACTOR_ANIMATION_H
#define ACTOR_ANIMATION_H


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

	set->walking_left = t3d_anim_create(model, "walking-left");
	
	set->running_left = t3d_anim_create(model, "running-10-left");

	set->sprinting_left = t3d_anim_create(model, "running-35-left");

	set->jump_left = t3d_anim_create(model, "jump-left");
	set->jump_right = t3d_anim_create(model, "jump-right");
	t3d_anim_set_looping(&set->jump_left, false);
	t3d_anim_set_looping(&set->jump_right, false);
	
	set->falling_left = t3d_anim_create(model, "falling-idle-left");
	set->falling_right = t3d_anim_create(model, "falling-idle-right");

	set->land_left = t3d_anim_create(model, "land-left");
	set->land_right = t3d_anim_create(model, "land-right");
	t3d_anim_set_looping(&set->land_left, false);
	t3d_anim_set_looping(&set->land_right, false);
}

void animationSet_attach(T3DSkeleton* main, T3DSkeleton* blend, AnimationSet* set)
{
	t3d_anim_attach(&set->breathing_idle, main);

	t3d_anim_attach(&set->transition_left, blend);
	t3d_anim_attach(&set->transition_right, blend);

	t3d_anim_attach(&set->action_idle_left, blend);
	t3d_anim_attach(&set->action_idle_right, blend);
	
	t3d_anim_attach(&set->walking_left, blend);
	
	t3d_anim_attach(&set->running_left, main);
	
	t3d_anim_attach(&set->sprinting_left, blend);
	
	t3d_anim_attach(&set->jump_left, blend);
	t3d_anim_attach(&set->jump_right, blend);
	
	t3d_anim_attach(&set->falling_left, blend);
	t3d_anim_attach(&set->falling_right, blend);
	
	t3d_anim_attach(&set->land_left, blend);
	t3d_anim_attach(&set->land_right, blend);
}

void actorAnimation_init(Actor* actor)
{
	actor->armature.main = t3d_skeleton_create(actor->model);
	actor->armature.blend = t3d_skeleton_clone(&actor->armature.main, false);

	animationSet_init(actor->model, &actor->animation.set);

	animationSet_attach(&actor->armature.main, &actor->armature.blend, &actor->animation.set);
}

// these are the ratio of convertion between the different locomotion animation lenghts for the prototype asset
// used to sync animation speed and time in order to blend properly

#define RTWratio 1.333333f                 // run to walk 
#define WTRratio 0.75f                     // walk to run
#define STRratio 1.142857f                 // sprint to run
#define RTSratio 0.875f                    // run to sprint
#define STWratio 1.523809f                 // sprint to walk
#define WTSratio 0.65625f                  // walk to sprint

/* animation lenght in frames/seconds, for the prototype asset

	walking
	32 / 1.06666666667
	
	running
	24 / 0.8
	
	sprinting
	21 / 0.7

	jump
	26 / 0.866666666667
	18 / 0.6 (feet leave floor) 

	land
	33 / 1.1
	9 / 0.3 (feet reach floor)
*/

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

void actorAnimation_setStandingLocomotion(Actor* actor, const float frame_time)
{

	if (actor->horizontal_speed == 0){
			
		if (actor->animation.current != STAND_IDLE) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = STAND_IDLE;
			t3d_anim_set_time(&actor->animation.set.walking_left, (0.0f));
		}
		
		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
		if (actor->animation.blending_ratio > 0) actor->animation.blending_ratio = 0; 
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){

		if (actor->animation.current != WALKING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = WALKING;
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		t3d_anim_set_speed(&actor->animation.set.walking_left, actor->animation.blending_ratio);
	
		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
		t3d_anim_update(&actor->animation.set.walking_left, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){

		if (actor->animation.current != RUNNING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = RUNNING;
			
			if (actor->animation.previous == WALKING) t3d_anim_set_time(&actor->animation.set.running_left, (actor->animation.set.walking_left.time * WTRratio));
			else if (actor->animation.previous == SPRINTING) t3d_anim_set_time(&actor->animation.set.walking_left, (actor->animation.set.sprinting_left.time * STWratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed  = (1.0f - ((1.0f - WTRratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running_left, actor->animation.speed );
		t3d_anim_set_speed(&actor->animation.set.walking_left, (actor->animation.speed  * RTWratio));

		t3d_anim_update(&actor->animation.set.running_left, frame_time);
		t3d_anim_update(&actor->animation.set.walking_left, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		if (actor->animation.current != SPRINTING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = SPRINTING;
			t3d_anim_set_time(&actor->animation.set.sprinting_left, (actor->animation.set.running_left.time * RTSratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed = (RTSratio + ((1.0f - RTSratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running_left, (actor->animation.speed * STRratio));
		t3d_anim_set_speed(&actor->animation.set.sprinting_left, actor->animation.speed);

		t3d_anim_update(&actor->animation.set.running_left, frame_time);
		t3d_anim_update(&actor->animation.set.sprinting_left, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

}

void actorAnimation_setJump(Actor* actor, const float frame_time)
{
if (actor->horizontal_speed == 0){
			
	if (actor->animation.current != STAND_IDLE) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = STAND_IDLE;
			t3d_anim_set_time(&actor->animation.set.walking_left, (0.0f));
		}
		
		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
		if (actor->animation.blending_ratio > 0) actor->animation.blending_ratio = 0; 
	}

	else if (actor->horizontal_speed > 0 && actor->horizontal_speed <= actor->settings.walk_target_speed){

		if (actor->animation.current != WALKING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = WALKING;
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		t3d_anim_set_speed(&actor->animation.set.walking_left, actor->animation.blending_ratio);
	
		t3d_anim_update(&actor->animation.set.breathing_idle, frame_time);
		t3d_anim_update(&actor->animation.set.walking_left, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.walk_target_speed && actor->horizontal_speed <= actor->settings.run_target_speed){

		if (actor->animation.current != RUNNING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = RUNNING;
			
			if (actor->animation.previous == WALKING) t3d_anim_set_time(&actor->animation.set.running_left, (actor->animation.set.walking_left.time * WTRratio));
			else if (actor->animation.previous == SPRINTING) t3d_anim_set_time(&actor->animation.set.walking_left, (actor->animation.set.sprinting_left.time * STWratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed  = (1.0f - ((1.0f - WTRratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running_left, actor->animation.speed );
		t3d_anim_set_speed(&actor->animation.set.walking_left, (actor->animation.speed  * RTWratio));

		t3d_anim_update(&actor->animation.set.running_left, frame_time);
		t3d_anim_update(&actor->animation.set.walking_left, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	else if (actor->horizontal_speed > actor->settings.run_target_speed){

		if (actor->animation.current != SPRINTING) {
			actor->animation.previous = actor->animation.current;
			actor->animation.current = SPRINTING;
			t3d_anim_set_time(&actor->animation.set.sprinting_left, (actor->animation.set.running_left.time * RTSratio));
		}

		actorAnimation_setLocomotionBlendingRatio(actor);

		actor->animation.speed = (RTSratio + ((1.0f - RTSratio) * actor->animation.blending_ratio));

		t3d_anim_set_speed(&actor->animation.set.running_left, (actor->animation.speed * STRratio));
		t3d_anim_set_speed(&actor->animation.set.sprinting_left, actor->animation.speed);

		t3d_anim_update(&actor->animation.set.running_left, frame_time);
		t3d_anim_update(&actor->animation.set.sprinting_left, frame_time);
		t3d_skeleton_blend(&actor->armature.main, &actor->armature.main, &actor->armature.blend, actor->animation.blending_ratio);
	}

	t3d_anim_update(&actor->animation.set.falling_left, frame_time);
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

			//.idle_to_roll_target_speed = 300,
			//.idle_to_roll_grip_target_speed = 50,
			//.walk_to_roll_target_speed = 500,
			//.run_to_roll_target_speed = 780,
			//.sprint_to_roll_target_speed = 980,

			.jump_target_speed = 400, 
			.jump_timer_max = 0.13
        },

		.animation = {
			.current = 1,
			.previous = 1,
			.speed = 0.0f,
			.blending_ratio = 0.0f,
			.transition = false,
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
	actor_setControlData(actor, control, camera_angle_around, camera_offset, frame_time);
	actor_setAnimation(actor, frame_time, syncpoint);
	actor_setMotion(actor, frame_time);
}


#endif