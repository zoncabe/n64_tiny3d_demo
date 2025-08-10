#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_states.h"
#include "../../include/player/player_animation.h"

#include "../../include/assets/male_muscled.h"



ActorSettings male_muscled_actor_settings = {
    
    .idle_acceleration_rate = MALE_MUSCLED_IDLE_ACCELERATION_RATE,
    .walk_acceleration_rate = MALE_MUSCLED_WALK_ACCELERATION_RATE,
    .run_acceleration_rate = MALE_MUSCLED_RUN_ACCELERATION_RATE,
    .sprint_acceleration_rate = MALE_MUSCLED_SPRINT_ACCELERATION_RATE,
    .roll_acceleration_grip_rate = MALE_MUSCLED_ROLL_ACCELERATION_GRIP_RATE,

    .jump_acceleration_rate = MALE_MUSCLED_JUMP_ACCELERATION_RATE,
    .aerial_control_rate = MALE_MUSCLED_AERIAL_CONTROL_RATE,

    .walk_target_speed = MALE_MUSCLED_WALK_TARGET_SPEED,
    .run_target_speed = MALE_MUSCLED_RUN_TARGET_SPEED,
    .sprint_target_speed = MALE_MUSCLED_SPRINT_TARGET_SPEED,

    .roll_change_grip_time = RUN_TO_ROLLING_ANIM_GRIP,
    .roll_timer_max = RUN_TO_ROLLING_ANIM_LENGHT,

    .jump_force_multiplier = MALE_MUSCLED_JUMP_FORCE_MULTIPLIER,  
    .jump_minimum_speed = MALE_MUSCLED_JUMP_MINIMUM_SPEED,

    .jump_timer_max = JUMP_ANIM_AIR,
};

AnimationSettings male_muscled_animation_settings = {

    .run_to_walk_ratio = MALE_MUSCLED_RUN_TO_WALK_RATIO,
    .walk_to_run_ratio = MALE_MUSCLED_WALK_TO_RUN_RATIO,

    .sprint_to_run_ratio = MALE_MUSCLED_SPRINT_TO_RUN_RATIO,
    .run_to_sprint_ratio = MALE_MUSCLED_RUN_TO_SPRINT_RATIO,

    .sprint_to_walk_ratio = MALE_MUSCLED_SPRINT_TO_WALK_RATIO,
    .walk_to_sprint_ratio = MALE_MUSCLED_WALK_TO_SPRINT_RATIO,

    .action_idle_max_blending_ratio = MALE_MUSCLED_ACTION_IDLE_MAX_BLENDING_RATIO,

    .walking_anim_length = MALE_MUSCLED_WALKING_ANIM_LENGTH,
    .walking_anim_length_half = MALE_MUSCLED_WALKING_ANIM_LENGTH_HALF,

    .running_anim_length_half = MALE_MUSCLED_RUNNING_ANIM_LENGTH_HALF,
    .running_anim_length = MALE_MUSCLED_RUNNING_ANIM_LENGTH,

    .sprinting_anim_length = MALE_MUSCLED_SPRINTING_ANIM_LENGTH,
    .sprinting_anim_length_half = MALE_MUSCLED_SPRINTING_ANIM_LENGTH_HALF,

    .run_to_rolling_anim_ground = MALE_MUSCLED_RUN_TO_ROLLING_ANIM_GROUND,
    .run_to_rolling_anim_grip = MALE_MUSCLED_RUN_TO_ROLLING_ANIM_GRIP,
    .run_to_rolling_anim_stand = MALE_MUSCLED_RUN_TO_ROLLING_ANIM_STAND,
    .run_to_rolling_anim_lenght = MALE_MUSCLED_RUN_TO_ROLLING_ANIM_LENGHT,

    .stand_to_rolling_anim_grip = MALE_MUSCLED_STAND_TO_ROLLING_ANIM_GRIP,
    .stand_to_rolling_anim_lenght = MALE_MUSCLED_STAND_TO_ROLLING_ANIM_LENGHT,

    .jump_anim_length = MALE_MUSCLED_JUMP_ANIM_LENGTH,
    .jump_anim_crouch = MALE_MUSCLED_JUMP_ANIM_CROUCH,
    .jump_anim_air = MALE_MUSCLED_JUMP_ANIM_AIR,
    .jump_max_blending_ratio = MALE_MUSCLED_JUMP_MAX_BLENDING_RATIO,
    .jump_footing_speed = MALE_MUSCLED_JUMP_FOOTING_SPEED,

    .land_anim_length = MALE_MUSCLED_LAND_ANIM_LENGTH,
    .land_anim_ground = MALE_MUSCLED_LAND_ANIM_GROUND,
    .land_anim_stand = MALE_MUSCLED_LAND_ANIM_STAND,
};
