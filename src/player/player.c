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
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/game/game.h"


Player* player[PLAYER_COUNT];


void player_init(uint32_t id, Player* player, const char* model_path, PlayerMotionSettings* motion_settings, PlayerAnimationSettings* animation_settings)
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

		.motion_settings = *motion_settings,

		.armature.animation = {
			
			.settings = *animation_settings,
			.current = 0,
			.previous = 0,
			.speed = 0.0f,
			.action_blending_ratio = 0.0f,
			.footing_blending_ratio = 0.5f,
		},


		.motion_data = {

			.jump_timer = 0,

		}
	};	
}
	

void player_update()
{
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {

        player_setMotion(player[i]);
        player_setAnimation(player[i]);
    }
}