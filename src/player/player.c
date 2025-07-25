#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_motion.h"
#include "../../include/actor/actor_animation.h"
#include "../../include/graphics/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/graphics/viewport.h"
#include "../../include/time/time.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/game/game.h"

#include "../../include/player/player.h"
#include "../../include/control/player_control.h"


Player player[PLAYER_COUNT];


void player_init(Player* player)
{
}

void player_updateActor()
{
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {

        player_setActorControl(&player[i]);
        actor_setMotion(player[i].actor, timer.delta);
        actor_setAnimation(player[i].actor, timer.delta, &timer.syncPoint);
    }
}