#include <t3d/t3danim.h>

#include "../../include/sound/sound.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"
#include "../../include/time/time.h"
#include "../../include/scene/scenery.h"
#include "../../include/graphics/sprites.h"
#include "../../include/cutscene/intro.h"
#include "../../include/ui/ui.h"
#include "../../include/player/player.h"
#include "../../include/game/game.h"
#include "../../include/control/camera_control.h"
#include "../../include/game/game_states.h"
#include "../../include/graphics/vertex_shaders.h"
#include "../../include/render/render.h"


void playerCollision_collideWithRoom(Player* player) {
    if (player->actor.body.position.x > 2450) player->actor.body.position.x = 2450;
    if (player->actor.body.position.x < -2450) player->actor.body.position.x = -2450;
    if (player->actor.body.position.y > 2450) player->actor.body.position.y = 2450;
    if (player->actor.body.position.y < -2450) player->actor.body.position.y = -2450;
    if (player->actor.body.position.z < 0) player->actor.body.position.z = 0;
}


void gameState_updateIntro()
{	
	game.timer.intro_counter += timer.delta;
	
	if (game.timer.intro_counter >= INTRO_SCENE_LENGTH) {
		game_setState(MAIN_MENU);
		game.timer.intro_counter = 0.0f;
	}
}

void gameState_updateMainMenu()
{
	if (game.previous_state == PAUSE && game.timer.gameplay_transition < 1.0f) {
	
		game.timer.gameplay_transition += 10 * timer.delta;
		
		if (game.timer.gameplay_transition >= 1.0f) {
		
			game.timer.gameplay_transition = 1.0f;
			game.timer.pause_transition = 0.0f;
		}
	}
	
	else if (game.timer.mainMenu_transition > 0.0f) game.timer.mainMenu_transition -= 10 * timer.delta;
}

void gameState_updateGameplay()
{
	
	if (game.previous_state == MAIN_MENU && game.timer.mainMenu_transition < 1.0f) {
	
		game.timer.mainMenu_transition += 10 * timer.delta;
		if (game.timer.mainMenu_transition > 1.0f) game.timer.mainMenu_transition = 1.0f;
	}

	else {

		if (game.timer.gameplay_transition > 0.0f) game.timer.gameplay_transition -= 10 * timer.delta;
		if (game.timer.pause_transition > 0.0f) game.timer.pause_transition -= 20 * timer.delta;
		if (game.timer.pause_transition < 0.0f) game.timer.pause_transition = 0.0f;
		
		player_update();
		playerCollision_collideWithRoom(player[0]);
		viewport_setOrbitalCamera();
	}
}


void gameState_updatePause()
{
	if (game.timer.pause_transition < 1.0f) game.timer.pause_transition += 20 * timer.delta;
	if (game.timer.pause_transition > 1.0f) game.timer.pause_transition = 1.0f;
}


void gameState_updateGameOver()
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
			gameState_updateIntro();
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
			gameState_updateGameOver();
			break;
		}
	}
}
