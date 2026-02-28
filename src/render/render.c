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
#include "../../include/graphics/sprites.h"
#include "../../include/render/render.h"
#include "../../include/ui/menu.h"
#include "../../include/cutscene/intro.h"

#include "../../include/sound/sound.h"


void render_start()
{
	viewport.fb_index = (viewport.fb_index + 1) % FB_COUNT;	
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
		
		t3d_skeleton_use(&player[i]->actor.armature.main);
		actor_draw(&player[i]->actor, &player[i]->actor.body);
	}

	for (uint8_t i = 0; i < SCENERY_COUNT; i++) {
		
		scenery_draw(scenery[i]);
	};
}

void render()
{
	
	render_start();

	switch(game.state){

		case INTRO:{
			intro_draw();
			break;
		}
		case MAIN_MENU:{			

			if (game.previous_state == PAUSE && game.timer.gameplay_transition < 1.0f) {
			
				render_gameplayScene(player, scenery);
				rdpq_sync_pipe();
				ui_drawPauseMenu();
				ui_drawFadingTransition(game.timer.gameplay_transition, 0.0f, 0.0f, 0.0f);
			}
			else {
	
				rdpq_sync_pipe();
				
				ui_drawMainMenu();
				
				if (game.timer.mainMenu_transition > 0.0f) 
				ui_drawFadingTransition(game.timer.mainMenu_transition, 0.0f, 0.0f, 0.0f);
				
				ui_drawDebugData();
			}				
			break;
		}
		case GAMEPLAY:{

			if (game.previous_state == MAIN_MENU && game.timer.mainMenu_transition < 1.0f) {
			
				rdpq_sync_pipe();
				ui_drawMainMenu();
				ui_drawFadingTransition(game.timer.mainMenu_transition, 0.0f, 0.0f, 0.0f);
			}
			else{

				render_gameplayScene(player, scenery);
				
				rdpq_sync_pipe();
				
				if (game.timer.gameplay_transition > 0.0f) 
				ui_drawFadingTransition(game.timer.gameplay_transition, 0.0f, 0.0f, 0.0f);
				
				if (game.timer.pause_transition > 0.0f) ui_drawPauseMenu();
				
				ui_drawDebugData();
			}
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