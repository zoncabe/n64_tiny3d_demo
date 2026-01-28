#ifndef ACTOR_H
#define ACTOR_H


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
	
} ActorAnimationStandingLocomotionSet;

typedef struct {

	T3DAnim jump_left;
	T3DAnim jump_right;

	T3DAnim falling_left;
	T3DAnim falling_right;	
	
	T3DAnim land_left;
	T3DAnim land_right;
	
} ActorAnimationJumpSet;

typedef struct {

	T3DAnim run_to_rolling_left;
	T3DAnim run_to_rolling_right;

	T3DAnim stand_to_rolling_left;
	T3DAnim stand_to_rolling_right;
	
} ActorAnimationRollSet;

typedef struct {
	
	float action_idle_max_blending_ratio;
	
    float run_to_walk_ratio;
    float walk_to_run_ratio;

    float sprint_to_run_ratio;
    float run_to_sprint_ratio;

    float sprint_to_walk_ratio;
    float walk_to_sprint_ratio;

    float walking_anim_length_half;
    float walking_anim_length;

    float running_anim_length_half;
    float running_anim_length;

    float sprinting_anim_length_half;
    float sprinting_anim_length;

} ActorAnimationLocomotionSettings;

typedef struct {

    float jump_max_blending_ratio;

    float jump_anim_length;
    float jump_anim_crouch;
    float jump_anim_air;
    float jump_footing_speed;

    float land_anim_length;
    float land_anim_ground;
    float land_anim_stand;

} ActorAnimationJumpSettings;

typedef struct {

    float run_to_rolling_anim_ground;
    float run_to_rolling_anim_grip;
    float run_to_rolling_anim_stand;
    float run_to_rolling_anim_lenght;

    float stand_to_rolling_anim_ground;
    float stand_to_rolling_anim_grip;
    float stand_to_rolling_anim_stand;
    float stand_to_rolling_anim_lenght;

} ActorAnimationRollSettings;

typedef struct {

	uint8_t current;
	uint8_t previous;
	
	float locomotion_blending_ratio;
	float action_blending_ratio;
	float jump_blending_ratio;
	float roll_blending_ratio;
	float footing_blending_ratio;
	float speed;

} ActorAnimationData;

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
	float jump_force_multiplier;
	float jump_minimum_speed;
	float jump_timer_max;

} ActorMotionSettings;

typedef struct {

	float target_yaw;

	Vector3 target_velocity;
	float horizontal_target_speed;
	float horizontal_speed;
	
	float roll_timer;
	
	Vector3 jump_initial_velocity;
	float jump_force;
	float jump_timer;

	bool grounded;
	float grounding_height;

} ActorMotionData;

typedef struct {

	float stick_magnitude;
	float stick_x;
	float stick_y;

	bool jump_hold;

} ActorMotionInput;

typedef struct {

	uint8_t current;
	uint8_t previous;
	uint8_t locomotion;

} ActorStateData;

typedef struct {
	
	rspq_block_t *dl;
	T3DModel *model;
	T3DMat4FP *t3d_matrix;
	Vector3 model_scale;

    ActorArmature armature;

} Actor;


void actor_init(Actor *actor, T3DSkeleton* armature, const char* model_path);

void actor_draw(Actor* actor, RigidBody* body);


#endif