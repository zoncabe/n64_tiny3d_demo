#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/graphics/lighting.h"
#include "../../include/viewport/camera.h"
#include "../../include/viewport/viewport.h"
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
	//n64brew_logo();
	libdragon_logo();

	game_setState(MAIN_MENU);
}

void gameState_updateMainMenu()
{
}

void gameState_updateGameplay()
{
	flag_transform += timer.delta * 0.75;
	animate_flag(scenery[1]->model, flag_transform);
	player_updateActor();
	viewport_updateGameplayCamera();
}


void gameState_updatePause()
{	
}


void gameState_setGameOver()
{
}

void game_setState(u_int8_t new_state)
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
			game.previous_state = game.state;
            game.state = MAIN_MENU;
			break;
		}
		case GAMEPLAY:{
            if (game.state == GAMEPLAY) return;
			game.previous_state = game.state;
            game.state = GAMEPLAY;
			break;
		}
		case PAUSE:{
            if (game.state == PAUSE) return;
			game.previous_state = game.state;
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

void game_updateState()
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
