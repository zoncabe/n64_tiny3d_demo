#ifndef GAME_H
#define GAME_H

typedef struct
{

    float intro_counter;
    float intro_transition;
    float mainMenu_transition;
    float gameplay_transition;
    float pause_transition;
    float gameOver_transition;

} GameTimers;

typedef struct
{
    uint8_t state;
    uint8_t previous_state;
    bool state_transition;
    
    GameTimers timer;

    bool playing_intro;

} Game;

extern Game game;


void game_init();
void game_close();


#endif