#ifndef GAME_STATES_H
#define GAME_STATES_H

#define INTRO 0
#define MAIN_MENU 1
#define GAMEPLAY 2
#define PAUSE 3
#define GAME_OVER 4


// function prototypes

void gameState_setIntro();
void gameState_updateMainMenu();

void gameState_updateGameplay();
void gameState_updatePause();

void gameState_setGameOver();

void game_setState(u_int8_t new_state);
void game_updateState();


#endif