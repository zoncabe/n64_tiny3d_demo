#ifndef GAME_H
#define GAME_H


typedef struct
{

    uint8_t state;
    Screen screen;
    TimeData timing;

    Scene scene;
	UI ui;

}Game;

extern Game game;


void game_init(Game *game);
void scene_draw(Game* game, Actor** actor, Scenery** scenery);


#endif