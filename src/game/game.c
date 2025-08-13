#include <stdint.h>
#include <t3d/t3dskeleton.h>
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
#include "../../include/ui/menu.h"
#include "../../include/player/player.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"
#include "../../include/render/render.h"
#include "../../include/memory/memory.h"


// global

Game game;


// function implementations

void game_init()
{
	asset_init_compression(2);

	dfs_init(DFS_DEFAULT_LOCATION);
	
	rdpq_init();
	
	joypad_init();
	
	viewport_init();
	
	time_init();
	
	ui_init();

	menu_mainInit();
	menu_pauseInit();
	
	game.state = MAIN_MENU;

	game.transition_timer = 1.0f;
}	

void game_close()
{
	scenery_delete(scenery[0]);
	scenery_delete(scenery[1]);
	scenery_delete(scenery[2]);
	scenery_delete(scenery[3]);

	menu_pauseClean();

	t3d_destroy();
}