#ifndef GAME_H
#define GAME_H


typedef struct
{
    uint8_t state;
    uint8_t previous_state;
    
    bool playing_intro;

}Game;

extern Game game;


void game_init();
void game_close();


#endif