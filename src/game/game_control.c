#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/screen/screen.h"
#include "../../include/camera/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/time/time.h"
#include "../../include/scene/scene.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/player/player.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"
#include "../../include/game/game_control.h"


void playerControl_skipIntro(Game* game, Player* player)
{
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {

        if (player[i].control.pressed.start) {

            if (game->state == INTRO) game->state = GAMEPLAY;
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
    playerControl_skipIntro(game, player);
    //playerControl_handleMainMenu(game, player);
    playerControl_setPause(game, player);
    //playerControl_handlePauseMenu(game, player);
    //playerControl_handleGameOverMenu(game, player);
}