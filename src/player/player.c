#include <stdint.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/screen/screen.h"
#include "../../include/camera/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/camera/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/time/time.h"
#include "../../include/scene/scene.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/game/game.h"

#include "../../include/player/player.h"


Player player[PLAYER_COUNT];


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
