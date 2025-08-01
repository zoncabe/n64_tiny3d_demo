#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_motion.h"
#include "../../include/actor/actor_animation.h"
#include "../../include/player/player.h"
#include "../../include/control/player_control.h"


// function implemenations

void actor_init(Actor *actor)
{     
    *actor = (Actor){

		.scale = {1.0f, 1.0f, 1.0f},

		.body = {
			.position = {0.0f, 0.0f, 0.0f},
			.velocity = {0.0f, 0.0f, 0.0f},
			.rotation = {0.0f, 0.0f, 0.0f},
		},

		.settings = {
			.idle_acceleration_rate = 8,
			.walk_acceleration_rate = 3,
			.run_acceleration_rate = 5,
			.sprint_acceleration_rate = 8,
			.roll_acceleration_grip_rate = 2,

			.jump_acceleration_rate = 50,
			.aerial_control_rate = 0.5f,

			.walk_target_speed = 185,
			.run_target_speed = 390,
			.sprint_target_speed = 520,

			.roll_change_grip_time = RUN_TO_ROLLING_ANIM_GRIP,
			.roll_timer_max = RUN_TO_ROLLING_ANIM_LENGHT,

			.jump_force_multiplier = JUMP_FORCE_MULTIPLIER,  
			.jump_minimum_speed = JUMP_MINIMUM_SPEED,

			.jump_timer_max = JUMP_ANIM_AIR,

			.fall_max_speed = 1000,
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

		}
	};
}
