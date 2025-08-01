#ifndef GAME_H
#define GAME_H


typedef struct
{
    uint8_t state;
    uint8_t previous_state;
    
    float transition_timer;

}Game;

extern Game game;


void game_init();


#endif