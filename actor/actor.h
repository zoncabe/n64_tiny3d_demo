#ifndef ACTOR_H
#define ACTOR_H


// structures

typedef struct {

	float idle_acceleration_rate;
	float walk_acceleration_rate;
	float run_acceleration_rate;
	float sprint_acceleration_rate;
	float roll_acceleration_rate;
	float roll_acceleration_grip_rate;
	float jump_acceleration_rate;
	float aerial_control_rate;

	float walk_target_speed;
	float run_target_speed;
	float sprint_target_speed;
	float idle_to_roll_target_speed;
	float idle_to_roll_grip_target_speed;
	float walk_to_roll_target_speed;
	float run_to_roll_target_speed;
	float sprint_to_roll_target_speed;
	float jump_max_speed;
	
	float jump_timer_max;
	float run_sync_timer_max;

}ActorSettings;


typedef struct {

	float stick_magnitude;
	float stick_x;
	float stick_y;
	float run_sync_timer;
	float jump_timer;
	float jump_force;
	bool jump_hold;
	bool jump_released;

}Actorinput;


typedef struct{

	T3DSkeleton main;
	T3DSkeleton blend;
	T3DSkeleton blend2;

} ActorArmature;


typedef struct {

	T3DAnim breathing_idle;

	T3DAnim transition_left;
	T3DAnim transition_right;

	T3DAnim action_idle_left;
	T3DAnim action_idle_right; 
	
	T3DAnim walking;

	T3DAnim running;

	T3DAnim sprinting;
	
	T3DAnim action_roll_left;
	T3DAnim action_roll_right;

	T3DAnim idle_roll;

	T3DAnim action_jump_left;
	T3DAnim action_jump_right;

	T3DAnim idle_jump;

	T3DAnim falling_left;
	T3DAnim falling_right;	
	
	T3DAnim land_left;
	T3DAnim land_right;
	
	T3DAnim idle_land;
	
} AnimationSet;


typedef struct {

	AnimationSet set;

	uint8_t current;
	uint8_t previous;
	
	float blending_ratio;
	float speed;
	
	bool transition;

} ActorAnimation;


typedef struct {

	uint32_t id;
	
	rspq_block_t *dl;
	T3DModel *model;
	T3DMat4FP *transform_matrix;
	Vector3 scale;
	
	char model_path;
	ActorArmature armature;
	ActorAnimation animation;

	RigidBody body;

	float target_yaw;
	float horizontal_target_speed;
	Vector3 target_velocity;

	float horizontal_speed;
	bool grounded;
	float grounding_height;

	uint8_t locomotion_state;
	uint8_t previous_state;
	uint8_t state;

	ActorSettings settings;
	Actorinput input;

} Actor;


// function prototypes

void actor_draw(Actor *actor);
void actor_delete(Actor *actor);


// function implemenations

void actor_draw(Actor *actor)
{	
	for (uint8_t i = 0; i < ACTOR_COUNT; i++) {
				
		t3d_matrix_set(actor->transform_matrix, true);
		t3d_mat4fp_from_srt_euler(actor[i].transform_matrix,
			(float[3]){actor[i].scale.x, actor[i].scale.y, actor[i].scale.z},
			(float[3]){rad(actor[i].body.rotation.x), rad(actor[i].body.rotation.y), rad(actor[i].body.rotation.z)},
			(float[3]){actor[i].body.position.x, actor[i].body.position.y, actor[i].body.position.z}
		);
		rspq_block_run(actor[i].dl);
	};
}

// lol i will finish this someday
void actor_delete(Actor *actor) 
{
	t3d_skeleton_destroy(&actor->armature.main);
	t3d_skeleton_destroy(&actor->armature.blend);
	
	t3d_anim_destroy(&actor->animation.set.breathing_idle);
	t3d_anim_destroy(&actor->animation.set.running);
	t3d_anim_destroy(&actor->animation.set.action_jump_left);
	t3d_anim_destroy(&actor->animation.set.falling_left);
	t3d_anim_destroy(&actor->animation.set.land_left);
	
	t3d_model_free(actor->model);
	rspq_block_free(actor->dl);
}

#endif