#ifndef GAME_H
#define GAME_H


typedef struct
{
    uint8_t state;

}Game;

extern Game game;


void game_init();


#endif