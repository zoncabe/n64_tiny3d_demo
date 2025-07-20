#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_motion.h"
#include "../../include/actor/actor_control.h"
#include "../../include/actor/actor_animation.h"
#include "../../include/physics/math/math_common.h"


// function implemenations

void actor_draw(Actor *actor)
{	
	for (uint8_t i = 0; i < ACTOR_COUNT; i++) {
				
		t3d_matrix_set(actor->t3d_matrix, true);
		t3d_mat4fp_from_srt_euler(actor[i].t3d_matrix,
			(float[3]){actor[i].scale.x, actor[i].scale.y, actor[i].scale.z},
			(float[3]){rad(actor[i].body.rotation.x), rad(actor[i].body.rotation.y), rad(actor[i].body.rotation.z)},
			(float[3]){actor[i].body.position.x, actor[i].body.position.y, actor[i].body.position.z}
		);
		rspq_block_run(actor[i].dl);
	};
}

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
			.idle_acceleration_rate = 9,
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

void actor_update(Actor *actor, ControllerData *control, float camera_angle_around, float camera_offset, float frame_time, rspq_syncpoint_t *syncpoint)
{
	actor_setControlData(actor, control, camera_angle_around, camera_offset);
	actor_setAnimation(actor, frame_time, syncpoint);
	actor_setMotion(actor, frame_time);
}