#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_motion.h"
#include "../../include/actor/actor_animation.h"

#include "../../include/physics/physics.h"
#include "../../include/scene/scenery.h"
#include "../../include/graphics/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/graphics/viewport.h"

#include "../../include/scene/scenery.h"

#include "../../include/player/player.h"
#include "../../include/control/player_control.h"

#include "../../include/ui/ui.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"

#include "../../include/graphics/shapes.h"
#include "../../include/graphics/render.h"


void actor_draw(Actor* actor)
{
	t3d_matrix_set(actor->t3d_matrix, true);
	t3d_mat4fp_from_srt_euler(actor->t3d_matrix,
		(float[3]){actor->scale.x, actor->scale.y, actor->scale.z},
		(float[3]){rad(actor->body.rotation.x), rad(actor->body.rotation.y), rad(actor->body.rotation.z)},
		(float[3]){actor->body.position.x, actor->body.position.y, actor->body.position.z}
	);
	rspq_block_run(actor->dl);
}

void scenery_draw(Scenery **scenery)
{
    for (uint8_t i = 0; i < SCENERY_COUNT; i++) {

        t3d_mat4fp_from_srt_euler(scenery[i]->t3d_matrix,
            (float[3]){scenery[i]->scale.x, scenery[i]->scale.y, scenery[i]->scale.z},
            (float[3]){rad(scenery[i]->rotation.x), rad(scenery[i]->rotation.y), rad(scenery[i]->rotation.z)},
            (float[3]){scenery[i]->position.x, scenery[i]->position.y, scenery[i]->position.z}
        );
        t3d_matrix_set(scenery[i]->t3d_matrix, true);
        rspq_block_run(scenery[i]->dl);
	};
}

void render_start()
{
	viewport_clear();	
}

void render_t3dScene(Player* player, Scenery** scenery)
{
	light_set(&light);

	t3d_matrix_push_pos(1);
    
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {
	
		actor_draw(player->actor);
	}

	scenery_draw(scenery);
    
	t3d_matrix_pop(1);

	ui_printDebugData(player[0].actor, timer);
}

void render_transition()
{
	if (game.state == GAMEPLAY && timer.counter > 0){
		
		timer.counter -= timer.delta; // * 0.66666f; // temporary fade in counter
		
		if (timer.counter > 0) shapes_drawSquare(0, 0, 0, (255 * timer.counter), 0, 0, 320, 240);
	}
}

void render_end()
{    
	rdpq_detach_show();
	timer.syncPoint = rspq_syncpoint_new();	
}

void render()
{
	switch(game.state){

		case INTRO:{
			break;
		}
		case MAIN_MENU:{
			break;
		}
		case GAMEPLAY:{

			render_start();
			render_t3dScene(player, scenery);
			render_transition();
			render_end();
			break;
		}
		case PAUSE:{

			render_start();
			render_t3dScene(player, scenery);
			render_transition();
			render_end();
			break;
		}
		case GAME_OVER:{
			break;
		}
	}
}