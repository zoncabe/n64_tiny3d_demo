#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"

#include "../../include/player/player.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_animation.h"

#include "../../include/physics/physics.h"
#include "../../include/scene/scenery.h"
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"

#include "../../include/scene/scenery.h"

#include "../../include/ui/ui.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"

#include "../../include/graphics/shapes.h"
#include "../../include/render/render.h"
#include "../../include/ui/menu.h"
#include "../../include/cutscene/intro.h"

#include "../../include/sound/sound.h"


void render_start()
{
	viewport_clear();	
}

void render_end()
{    
	rdpq_detach_show();	
}

void render_gameplayScene(Player** player, Scenery** scenery)
{	
	light_set(&light);
	
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {
		
		t3d_skeleton_use(&player[i]->armature.main);
		actor_draw(&player[i]->actor, &player[i]->body);
	}

	for (uint8_t i = 0; i < SCENERY_COUNT; i++) {
		
		scenery_draw(scenery[i]);
	};
}

void render()
{
	viewport.fb_index = (viewport.fb_index + 1) % FB_COUNT;
	
	render_start();

	switch(game.state){

		case INTRO:{
			intro_draw();
			break;
		}
		case MAIN_MENU:{			

    		rdpq_sync_pipe();

			ui_drawMainMenu();

			ui_drawDebugData();

			break;
		}
		case GAMEPLAY:{

			render_gameplayScene(player, scenery);

    		rdpq_sync_pipe();

			ui_drawDebugData();

			break;
		}
		case PAUSE:{
			
			render_gameplayScene(player, scenery);

    		rdpq_sync_pipe();
			
			ui_drawPauseMenu();

			ui_drawDebugData();

			break;
		}
		case GAME_OVER:{
			break;
		}
	}

	render_end();
}