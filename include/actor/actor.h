#ifndef ACTOR_H
#define ACTOR_H


// structures

typedef struct {

	float value_0;
	float value_1;
	float value_2;
	float value_3;
	float value_4;
	float value_5;
	float value_6;
	float value_7;
	float value_8;

}ActorDebug;

typedef struct {

	float idle_acceleration_rate;
	float walk_acceleration_rate;
	float run_acceleration_rate;
	float sprint_acceleration_rate;
	float roll_acceleration_grip_rate;
	
	float walk_target_speed;
	float run_target_speed;
	float sprint_target_speed;
	
	float roll_change_grip_time;
	float roll_timer_max;
	
	float aerial_control_rate;
	float jump_acceleration_rate;
	float jump_max_speed;
	float jump_timer_max;

}ActorSettings;

typedef struct {

	float stick_magnitude;
	float stick_x;
	float stick_y;
	float roll_timer;

	Vector3 jump_initial_velocity;
	float jump_timer;
	float jump_force;
	bool jump_hold;

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

	T3DAnim standing_idle_left;
	T3DAnim standing_idle_right; 
	
	T3DAnim walking;

	T3DAnim running;

	T3DAnim sprinting;
	
	T3DAnim run_to_rolling_left;
	T3DAnim run_to_rolling_right;

	T3DAnim stand_to_rolling_left;
	T3DAnim stand_to_rolling_right;

	T3DAnim jump_left;
	T3DAnim jump_right;

	T3DAnim falling_left;
	T3DAnim falling_right;	
	
	T3DAnim land_left;
	T3DAnim land_right;
	
} AnimationSet;

typedef struct {

	AnimationSet set;

	uint8_t current;
	uint8_t previous;
	
	float locomotion_blending_ratio;
	float action_blending_ratio;
	float jump_blending_ratio;
	float roll_blending_ratio;
	float footing_blending_ratio;
	float speed;
	
	bool transition;
	bool short_jump;

} ActorAnimation;


typedef struct {

	uint32_t id;
	ActorDebug debug_data;
	
	rspq_block_t *dl;
	T3DModel *model;
	T3DMat4FP *transform_matrix;
	uint32_t matrix_index;
	Vector3 scale;
	
	char model_path;
	ActorArmature armature;
	ActorAnimation animation;

	RigidBody body;

	float target_yaw;
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
	t3d_anim_destroy(&actor->animation.set.jump_left);
	t3d_anim_destroy(&actor->animation.set.falling_left);
	t3d_anim_destroy(&actor->animation.set.land_left);
	
	t3d_model_free(actor->model);
	rspq_block_free(actor->dl);
}

#endif