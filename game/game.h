#ifndef GAME_H
#define GAME_H

#define INTRO 0
#define MAIN_MENU 1
#define GAMEPLAY 2
#define PAUSE 3
#define GAME_OVER 4


typedef struct
{

    uint8_t state;
    Screen screen;
    TimeData timing;

    Scene scene;
	UI ui;

}Game;


void game_init(Game *game);


void game_init(Game *game)
{
	screen_initDisplay(&game->screen);
	screen_initT3dViewport(&game->screen);

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

	ui_printDebugData(&game->ui, actor);

	rdpq_detach_show();

	game->timing.syncPoint = rspq_syncpoint_new();
}	

#endif