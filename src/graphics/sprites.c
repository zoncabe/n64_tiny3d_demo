#include <libdragon.h>
#include "../../include/graphics/sprites.h"


TextSprites text_sprites;
ControllerSprites controller_sprites;
IntroSprites intro_sprites;
TitleSprites title_sprites;

void introSprites_init()
{
    intro_sprites.n64logo = sprite_load("rom:/textures/n64logo.sprite");
    intro_sprites.libdragonlogo = sprite_load("rom:/textures/libdragon.sprite");
    intro_sprites.tiny3dlogo = sprite_load("rom:/textures/tiny3d.sprite");
    intro_sprites.zoncabe = sprite_load("rom:/textures/zoncabe.sprite");
}

void textSprites_init()
{
    text_sprites.not_a = sprite_load("rom:/textures/not_a.ia8.sprite");
    text_sprites.game = sprite_load("rom:/textures/game.ia8.sprite"); 
    text_sprites.play = sprite_load("rom:/textures/play.ia8.sprite");
    text_sprites.options = sprite_load("rom:/textures/options.ia8.sprite");
    text_sprites.credits = sprite_load("rom:/textures/credits.ia8.sprite");
    text_sprites.select = sprite_load("rom:/textures/select.ia8.sprite");
    text_sprites.move = sprite_load("rom:/textures/move.ia8.sprite");
    text_sprites.kontinue = sprite_load("rom:/textures/continue.ia8.sprite");
    text_sprites.quit = sprite_load("rom:/textures/quit.ia8.sprite");
    text_sprites.back = sprite_load("rom:/textures/back.ia8.sprite");
    
    text_sprites.play_scale = 0.34f;
    text_sprites.options_scale = 0.3f;
    text_sprites.credits_scale = 0.3f;
    text_sprites.kontinue_scale = 0.33f;
    text_sprites.quit_scale = 0.3f;
    
}

void controllerSprites_init()
{
    controller_sprites.abutton = sprite_load("rom:/textures/AButton.sprite");
    controller_sprites.bbutton = sprite_load("rom:/textures/BButton.sprite");
    controller_sprites.dupbutton = sprite_load("rom:/textures/DUp.sprite");
    controller_sprites.ddownbutton = sprite_load("rom:/textures/DDown.sprite");
}

void titleSprites_init()
{
    title_sprites.gorilla = sprite_load("rom:/textures/gorilla.rgba32.sprite");
}

void introSprites_Clean()
{
    sprite_free(intro_sprites.n64logo);
    sprite_free(intro_sprites.libdragonlogo);
    sprite_free(intro_sprites.tiny3dlogo);
}

void textSprites_Clean()
{
    sprite_free(text_sprites.not_a);
    sprite_free(text_sprites.game); 
    sprite_free(text_sprites.play);
    sprite_free(text_sprites.options);
    sprite_free(text_sprites.credits);
    sprite_free(text_sprites.select);
    sprite_free(text_sprites.move);
    sprite_free(text_sprites.kontinue);
    sprite_free(text_sprites.quit);
    sprite_free(text_sprites.back);
}

void controllerSprites_Clean()
{
    sprite_free(controller_sprites.abutton);
    sprite_free(controller_sprites.bbutton);
    sprite_free(controller_sprites.dupbutton);
    sprite_free(controller_sprites.ddownbutton);
}

void titleSprites_Clean()
{
    sprite_free(title_sprites.gorilla);
}

void sprite_setMode()
{
    rdpq_set_mode_standard();
	rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_alphacompare(1);
}

void sprite_draw(sprite_t *sprite, float pos_x, float pos_y, float rotation, float scale_x, float scale_y)
{ 
	rdpq_sprite_blit(sprite, pos_x, pos_y, &(rdpq_blitparms_t){.scale_x = scale_x, .scale_y = scale_y, .theta = rotation});
}
