#include <libdragon.h>
#include "../../include/ui/menu.h"

Menu menu;


void menu_mainInit()
{
    menu.sprite.still = sprite_load("rom:/still.ia8.sprite");
    menu.sprite.not_a = sprite_load("rom:/not_a.ia8.sprite");
    menu.sprite.game = sprite_load("rom:/game.ia8.sprite");
    
    menu.sprite.play = sprite_load("rom:/play.ia8.sprite");
    menu.sprite.options = sprite_load("rom:/options.ia8.sprite");
    menu.sprite.credits = sprite_load("rom:/credits.ia8.sprite");

    menu.sprite.play_scale = 0.34f;
    menu.sprite.options_scale = 0.3f;
    menu.sprite.credits_scale = 0.3f;

    menu.sprite.select = sprite_load("rom:/select.ia8.sprite");
    menu.sprite.back = sprite_load("rom:/back.ia8.sprite");
    menu.sprite.move = sprite_load("rom:/move.ia8.sprite");
    menu.sprite.abutton = sprite_load("rom:/AButton.sprite");
    menu.sprite.bbutton = sprite_load("rom:/BButton.sprite");
    menu.sprite.dupbutton = sprite_load("rom:/DUp.sprite");
    menu.sprite.ddownbutton = sprite_load("rom:/DDown.sprite");


    menu.sprite.gorilla = sprite_load("rom:/gorilla.rgba32.sprite");

    menu.index = 0;
}

void menu_pauseInit()
{;
    menu.sprite.kontinue = sprite_load("rom:/continue.ia8.sprite");
    menu.sprite.options = sprite_load("rom:/options.ia8.sprite");
    menu.sprite.quit = sprite_load("rom:/quit.ia8.sprite");

    menu.sprite.kontinue_scale = 0.33f;
    //menu.sprite.options_scale = 0.3f;
    menu.sprite.quit_scale = 0.3f;

    //menu.sprite.select = sprite_load("rom:/select.ia8.sprite");
    //menu.sprite.back = sprite_load("rom:/back.ia8.sprite");
    //menu.sprite.abutton = sprite_load("rom:/AButton.sprite");
    //menu.sprite.bbutton = sprite_load("rom:/BButton.sprite");

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
