#ifndef SPRITES_H
#define SPRITES_H


typedef struct {
    
    sprite_t* n64logo;
    sprite_t* libdragonlogo;
    sprite_t* tiny3dlogo;
    sprite_t* zoncabe;

}IntroSprites;

typedef struct {
    
    sprite_t* not_a;
    sprite_t* game;
    sprite_t* play;
    sprite_t* options;
    sprite_t* move;
    sprite_t* kontinue;
    sprite_t* quit;
    sprite_t* exit;
    sprite_t* credits;

    sprite_t* back;
    sprite_t* select;
    
    float not_a_scale;
    float game_scale;
    float play_scale;
    float options_scale;
    float move_scale;
    float kontinue_scale;
    float quit_scale;
    float exit_scale;
    float credits_scale;

}TextSprites;

typedef struct {

    sprite_t* back;
    sprite_t* select;

    sprite_t* abutton;
    sprite_t* bbutton;
    sprite_t* dupbutton;
    sprite_t* ddownbutton;

}ControllerSprites;

typedef struct {
    
    sprite_t* gorilla;

}TitleSprites;

extern TextSprites text_sprites;
extern ControllerSprites controller_sprites;
extern IntroSprites intro_sprites;
extern TitleSprites title_sprites;

void introSprites_init();
void textSprites_init();
void controllerSprites_init();
void titleSprites_init();

void introSprites_Clean();
void textSprites_Clean();
void controllerSprites_Clean();
void titleSprites_Clean();

void sprite_setMode();
void sprite_draw(sprite_t *sprite, float pos_x, float pos_y, float rotation, float scale_x, float scale_y);


#endif