
#include "../../include/player/player.h"


void player_init(Player* player)
{
}

void player_setControllerData(Player* player)
{
    joypad_poll();
    
    for (int i = 0; i < PLAYER_COUNT; i++) {
        
        controllerData_getInputs(&player[i].control, i);
    } 
}
