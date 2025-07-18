
#include "../../include/game/game_states.h"
#include "../../include/camera/camera_control.h"
#include "../../include/player/player_control.h"
#include "../../include/physics/actor_collision/actor_collision_response.h"
#include "../../include/actor/actor_animation.h"


void gameState_setIntro()
{}
void gameState_setMainMenu()
{}

void gameState_setGameplay(Game* game, Player* player, Actor* actor, Scenery* scenery)
{
	actor_update(&actor[0], &player[0].control, game->scene.camera.angle_around_barycenter, game->scene.camera.offset_angle, game->timing.frame_time, &game->timing.syncPoint);	
	
	actorCollision_collideWithRoom(&actor[0]);
	
	camera_update(&game->scene.camera, &player[0].control, &game->screen, &actor[0].body.position, game->timing.frame_time);

	scene_draw(game, actor, scenery);
}


void gameState_setPause(Game* game, Player* player, Actor* actor, Scenery* scenery)
{	
	scene_draw(game, actor, scenery);
}


void gameState_setGameOver()
{
}

void game_setState(Game* game, Player* player, Actor* actor, Scenery* scenery)
{
	playerControl_setGameState(game, player);
	
	switch(game->state)
	{
		case INTRO:{
			gameState_setIntro();
			break;
		}
		case MAIN_MENU:{
			gameState_setMainMenu();
			break;
		}
		case GAMEPLAY:{
			gameState_setGameplay(game, player, actor, scenery);
			break;
		}
		case PAUSE:{
			gameState_setPause(game, player, actor, scenery);
			break;
		}
		case GAME_OVER:{
			gameState_setGameOver();
			break;
		}
	}
}
