#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_motion.h"
#include "../../include/actor/actor_states.h"
#include "../../include/player/player.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_animation.h"
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/game/game.h"


Player* player[PLAYER_COUNT];


void player_init(Player* player, ActorMotionSettings* motion_settings, ActorAnimationSettings* animation_settings)
{

    *player = (Player){};
	actor_init(&player->actor, motion_settings, animation_settings);	
}
	

void player_update()
{
    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {

		actor_setMotion(&player[i]->actor);
        player_setAnimation(player[i]);
    }
}