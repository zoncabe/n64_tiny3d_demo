#include <stdint.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/screen/screen.h"
#include "../../include/camera/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/time/time.h"
#include "../../include/scene/scene.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/player/player.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"


// global

Game game;


// function implementations

void game_init(Game *game)
{
	screen_init(&game->screen);

	rdpq_init();
	
	joypad_init();

	time_init(&game->timing);

	ui_init(&game->ui);

	t3d_init((T3DInitParams){});

    scene_init(&game->scene);
	
	game->state = INTRO;
}


void scene_draw(Game* game, Actor** actor, Scenery** scenery)
{
	screen_clear(&game->screen);
	
	light_set(&game->scene.light);

	t3d_matrix_push_pos(1);

	actor_draw(actor);
	
	scenery_draw(scenery);

	t3d_matrix_pop(1);

	ui_printDebugData(&game->ui, actor[0], game->timing);

	rdpq_detach_show();

	game->timing.syncPoint = rspq_syncpoint_new();
}	
