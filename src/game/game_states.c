#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/graphics/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/graphics/viewport.h"
#include "../../include/time/time.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/player/player.h"
#include "../../include/game/game.h"
#include "../../include/control/camera_control.h"
#include "../../include/game/game_states.h"
#include "../../include/graphics/render.h"
#include "../../include/game/intro.h"


void gameState_setIntro()
{
	n64brew_logo();
	libdragon_logo();

	gameState_set(GAMEPLAY);
}

void gameState_updateMainMenu()
{
}

void gameState_updateGameplay()
{
	player_updateActor();
	viewport_update();
}


void gameState_updatePause()
{	
}


void gameState_setGameOver()
{
}

void gameState_set(u_int8_t new_state)
{
	switch(new_state)
	{
		case INTRO:{
            if (game.state == INTRO) return;
            game.state = INTRO;
			break;
		}
		case MAIN_MENU:{
            if (game.state == MAIN_MENU) return;
            game.state = MAIN_MENU;
			break;
		}
		case GAMEPLAY:{
            if (game.state == GAMEPLAY) return;
            game.state = GAMEPLAY;
			break;
		}
		case PAUSE:{
            if (game.state == PAUSE) return;
            game.state = PAUSE;
			break;
		}
		case GAME_OVER:{
            if (game.state == GAME_OVER) return;
            game.state = GAME_OVER;
			break;
		}
	}
}

void gameState_update()
{	
	switch(game.state)
	{
		case INTRO:{
			gameState_setIntro();
			break;
		}
		case MAIN_MENU:{
			gameState_updateMainMenu();
			break;
		}
		case GAMEPLAY:{
			gameState_updateGameplay();
			break;
		}
		case PAUSE:{
			gameState_updatePause();
			break;
		}
		case GAME_OVER:{
			gameState_setGameOver();
			break;
		}
	}
}
