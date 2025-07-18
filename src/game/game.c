
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"


void game_init(Game *game)
{
	screen_init(&game->screen);

	rdpq_init();
	
	joypad_init();

	time_init(&game->timing);

	ui_init(&game->ui);

	t3d_init((T3DInitParams){});

    scene_init(&game->scene);
	
	game->state = GAMEPLAY;
}


void scene_draw(Game* game, Actor* actor, Scenery* scenery)
{
	screen_clear(&game->screen);
	
	light_set(&game->scene.light);

	t3d_matrix_push_pos(1);

	actor_draw(actor);
	
	scenery_draw(scenery);

	t3d_matrix_pop(1);

	ui_printDebugData(&game->ui, actor, game->timing);

	rdpq_detach_show();

	game->timing.syncPoint = rspq_syncpoint_new();
}	
