#ifndef PLAYER_CONTROLS_H
#define PLAYER_CONTROLS_H


void playerControl_skipIntro(Game* game, Player* player)
{
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {

        if (player[i].control.pressed.start) {

            if (game->state == INTRO) game->state = MAIN_MENU;
        }
    }
}

void playerControl_handleMainMenu(Game* game, Player* player)
{
}

void playerControl_setPause(Game* game, Player* player)
{
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {

        if (player[i].control.pressed.start) {

            if (game->state == PAUSE) game->state = GAMEPLAY;
            else if (game->state == GAMEPLAY) game->state = PAUSE;
        }
    }
}

void playerControl_handlePauseMenu(Game* game, Player* player)
{
}

void playerControl_handleGameOverMenu(Game* game, Player* player)
{
}

void playerControl_setGameState(Game* game, Player* player)
{
    //playerControl_skipIntro(game, player);
    //playerControl_handleMainMenu(game, player);
    playerControl_setPause(game, player);
    //playerControl_handlePauseMenu(game, player);
    //playerControl_handleGameOverMenu(game, player);
}

#endif