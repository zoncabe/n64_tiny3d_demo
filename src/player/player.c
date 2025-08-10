#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_motion.h"
#include "../../include/player/player_animation.h"
#include "../../include/graphics/lighting.h"
#include "../../include/viewport/camera.h"
#include "../../include/viewport/viewport.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/game/game.h"


Player* player[PLAYER_COUNT];


void player_init(uint32_t id, Player* player, const char* model_path)
{

    *player = (Player){
		
		.id = id,

		.state.current = STAND_IDLE,

		.actor = {

			.render_data.model_scale = {1.0f, 1.0f, 1.0f}
		},

		.body = {
			.position = {0.0f, 0.0f, 0.0f},
			.velocity = {0.0f, 0.0f, 0.0f},
			.rotation = {0.0f, 0.0f, 0.0f},
		},

		.motion_settings = {
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
		},

		.armature.animation = {
			.current = 0,
			.previous = 0,
			.speed = 0.0f,
			.action_blending_ratio = 0.0f,
			.footing_blending_ratio = 0.5f,
		},


		.motion_input = {

			.jump_timer = 0,

		}
	};
	
	player->actor.render_data.model = t3d_model_load(model_path);
	player->actor.render_data.t3d_matrix = malloc_uncached(sizeof(T3DMat4FP));

    t3d_matrix_set(player->actor.render_data.t3d_matrix, true);
    t3d_mat4fp_identity(player->actor.render_data.t3d_matrix);
	
	playerAnimation_init(player);

	rspq_block_begin();
	t3d_model_draw_skinned(player->actor.render_data.model, &player->armature.main);
	player->actor.render_data.dl = rspq_block_end();
	
}
	

void player_update()
{
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {

        player_setMotion(player[i]);
        player_setAnimation(player[i], &timer.syncPoint);
    }
}