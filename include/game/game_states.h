#ifndef GAME_STATES_H
#define GAME_STATES_H

#define INTRO 0
#define MAIN_MENU 1
#define GAMEPLAY 2
#define PAUSE 3
#define GAME_OVER 4


// function prototypes

void gameState_setIntro(Game* game);
void gameState_setMainMenu();

void gameState_setGameplay(Game* game, Player* player, Actor** actor, Scenery** scenery);
void gameState_setPause(Game* game, Player* player, Actor** actor, Scenery** scenery);

void gameState_setGameOver();

void game_setState(Game* game, Player* player, Actor** actor, Scenery** scenery);


#endif