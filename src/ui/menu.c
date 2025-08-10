#include <libdragon.h>
#include "../../include/ui/menu.h"

Menu menu;


void menu_mainInit()
{
    menu.sprite.still = sprite_load("rom:/textures/still.ia8.sprite");
    menu.sprite.not_a = sprite_load("rom:/textures/not_a.ia8.sprite");
    menu.sprite.game = sprite_load("rom:/textures/game.ia8.sprite");
    
    menu.sprite.play = sprite_load("rom:/textures/play.ia8.sprite");
    menu.sprite.options = sprite_load("rom:/textures/options.ia8.sprite");
    menu.sprite.credits = sprite_load("rom:/textures/credits.ia8.sprite");

    menu.sprite.play_scale = 0.34f;
    menu.sprite.options_scale = 0.3f;
    menu.sprite.credits_scale = 0.3f;

    menu.sprite.select = sprite_load("rom:/textures/select.ia8.sprite");
    menu.sprite.back = sprite_load("rom:/textures/back.ia8.sprite");
    menu.sprite.move = sprite_load("rom:/textures/move.ia8.sprite");
    menu.sprite.abutton = sprite_load("rom:/textures/AButton.sprite");
    menu.sprite.bbutton = sprite_load("rom:/textures/BButton.sprite");
    menu.sprite.dupbutton = sprite_load("rom:/textures/DUp.sprite");
    menu.sprite.ddownbutton = sprite_load("rom:/textures/DDown.sprite");


    menu.sprite.gorilla = sprite_load("rom:/textures/gorilla.rgba32.sprite");

    menu.index = 0;
}

void menu_pauseInit()
{;
    menu.sprite.kontinue = sprite_load("rom:/textures/continue.ia8.sprite");
    menu.sprite.options = sprite_load("rom:/textures/options.ia8.sprite");
    menu.sprite.quit = sprite_load("rom:/textures/quit.ia8.sprite");

    menu.sprite.kontinue_scale = 0.33f;
    //menu.sprite.options_scale = 0.3f;
    menu.sprite.quit_scale = 0.3f;

    //menu.sprite.select = sprite_load("rom:/textures/select.ia8.sprite");
    //menu.sprite.back = sprite_load("rom:/textures/back.ia8.sprite");
    //menu.sprite.abutton = sprite_load("rom:/textures/AButton.sprite");
    //menu.sprite.bbutton = sprite_load("rom:/textures/BButton.sprite");

    //menu.index = 0;
}

void menu_pauseClean()
{
    sprite_free(menu.sprite.kontinue);
    sprite_free(menu.sprite.options);
    sprite_free(menu.sprite.quit);
    
    sprite_free(menu.sprite.select);
    sprite_free(menu.sprite.back);
    sprite_free(menu.sprite.abutton);
    sprite_free(menu.sprite.bbutton);
}
