#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#include "../../include/screen/screen.h"
#include "../../include/time/time.h"
#include "../../include/scene/scene.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"


typedef struct
{

    uint8_t state;
    Screen screen;
    TimeData timing;

    Scene scene;
	UI ui;

}Game;


void game_init(Game *game);
void scene_draw(Game* game, Actor* actor, Scenery* scenery);


#endif