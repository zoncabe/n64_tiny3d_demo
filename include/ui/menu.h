#ifndef MENU_H
#define MENU_H


typedef struct {
    
    sprite_t* still;
    sprite_t* not_a;
    sprite_t* game;
    sprite_t* but_not_for_long;
    sprite_t* play;
    sprite_t* options;
    sprite_t* move;
    sprite_t* settings;
    sprite_t* kontinue;
    sprite_t* quit;
    sprite_t* exit;
    sprite_t* credits;
    sprite_t* help;

    float still_scale;
    float not_a_scale;
    float game_scale;
    float but_not_for_long_scale;
    float play_scale;
    float options_scale;
    float move_scale;
    float settings_scale;
    float kontinue_scale;
    float quit_scale;
    float exit_scale;
    float credits_scale;
    float help_scale;

    sprite_t* back;
    sprite_t* select;

    sprite_t* abutton;
    sprite_t* bbutton;
    sprite_t* dupbutton;
    sprite_t* ddownbutton;

    sprite_t* gorilla;

}MenuSprites;

typedef struct {
    
    MenuSprites sprite;
    int index;

}Menu;

extern Menu menu;

void menu_mainInit();
void menu_pauseInit();
void menu_pauseClean();

#endif