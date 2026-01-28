#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_COUNT 2


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
	
} PlayerAnimationSet;

typedef struct {

    float run_to_walk_ratio;
    float walk_to_run_ratio;

    float sprint_to_run_ratio;
    float run_to_sprint_ratio;

    float sprint_to_walk_ratio;
    float walk_to_sprint_ratio;

    float action_idle_max_blending_ratio;

    float walking_anim_length_half;
    float walking_anim_length;

    float running_anim_length_half;
    float running_anim_length;

    float sprinting_anim_length_half;
    float sprinting_anim_length;

    float run_to_rolling_anim_ground;
    float run_to_rolling_anim_grip;
    float run_to_rolling_anim_stand;
    float run_to_rolling_anim_lenght;

    float stand_to_rolling_anim_ground;
    float stand_to_rolling_anim_grip;
    float stand_to_rolling_anim_stand;
    float stand_to_rolling_anim_lenght;

    float jump_anim_length;
    float jump_anim_crouch;
    float jump_anim_air;
    float jump_max_blending_ratio;
    float jump_footing_speed;

    float land_anim_length;
    float land_anim_ground;
    float land_anim_stand;

} PlayerAnimationSettings;

typedef struct {

	PlayerAnimationSet set;
	PlayerAnimationSettings settings;

	uint8_t current;
	uint8_t previous;
	
	float locomotion_blending_ratio;
	float action_blending_ratio;
	float jump_blending_ratio;
	float roll_blending_ratio;
	float footing_blending_ratio;
	float speed;

} PlayerAnimation;

typedef struct{

	T3DSkeleton main;
	T3DSkeleton blend;
	T3DSkeleton blend2;

	PlayerAnimation animation;

} PlayerArmature;

typedef struct {

	uint8_t current;
		uint8_t previous;
		uint8_t locomotion;

} PlayerStateData;


typedef struct {

    ControllerData control;
    
	RigidBody body;

    Actor actor;

    PlayerArmature armature;

	ActorMotionSettings motion_settings;
    
	ActorMotionInput motion_input;

	ActorMotionData motion_data;
    
	ActorStateData state;
	
} Player;


extern Player* player[PLAYER_COUNT];

void player_init(Player* player, const char* model_path, ActorMotionSettings* motion_settings, PlayerAnimationSettings* animation_settings);

void player_update();



#endif