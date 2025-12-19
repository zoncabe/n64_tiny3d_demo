#include <libdragon.h>
#include "../../include/time/time.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"
#include "../../include/ui/menu.h"
#include "../../include/graphics/sprites.h"


void intro_init()
{
    introSprites_init();
}

void intro_close()
{
    introSprites_Clean();
}

void intro_draw()
{
    rdpq_sync_pipe();
    sprite_setMode();
    
    if (timer.intro_counter < 3.0f){
        sprite_draw(intro_sprites.n64logo, 0, 0, 0.0f, 1.0f, 1.0f);
    }
    
    else if (timer.intro_counter < 6.0f) {
        sprite_draw(intro_sprites.libdragonlogo, 0, 0, 0.0f, 1.0f, 1.0f);
    }
    
    else if (timer.intro_counter < 9.0f) { 
        sprite_draw(intro_sprites.tiny3dlogo, 0, 0, 0.0f, 1.0f, 1.0f);
    }

    else {
        sprite_draw(intro_sprites.zoncabe, 0, 0, 0.0f, 1.0f, 1.0f);
    }
}