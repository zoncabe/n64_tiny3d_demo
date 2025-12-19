#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/graphics/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_animation.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/ui/menu.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"
#include "../../include/render/render.h"
#include "../../include/assets/male_muscled.h"
#include "../../include/memory/memory.h"

void init_demoScene()
{	
    player[0] = player_create(0, "rom:/models/male_muscled.t3dm", &male_muscled_motion_settings, &male_muscled_animation_settings);
	player[0]->body.position =(Vector3){-195.0f, -200.0f, 0.0f};
	player[0]->body.rotation.z = 200;

	scenery[0] = scenery_create(0, "rom:/models/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/models/axis.t3dm");

	scenery[0]->position.z = -2;
	scenery_update(scenery[0]);
	scenery[1]->position.z = -2;
	scenery[1]->scale =(Vector3){2.0f, 2.0f, 2.0f};
	scenery_update(scenery[1]);
}