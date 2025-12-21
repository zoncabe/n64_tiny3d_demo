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
	// Initialize lighting

	//directionalLight_init(&directional_light);
	
	pointLight_init(&point_light[0], (Vector3){1795.0f, 0.0f, 200.0f}, lamp_color, 1000.0f);
	pointLight_init(&point_light[1], (Vector3){-1795.0f, 0.0f, 200.0f}, lamp_color, 1000.0f);
	pointLight_init(&point_light[2], (Vector3){0.0f, 1795.0f, 200.0f}, lamp_color, 1000.0f);
	pointLight_init(&point_light[3], (Vector3){0.0f, -1795.0f, 200.0f}, lamp_color, 1000.0f);

	// Initialize player and scenery
    player[0] = player_create(0, "rom:/models/male_muscled.t3dm", &male_muscled_motion_settings, &male_muscled_animation_settings);
	player[0]->body.position =(Vector3){-195.0f, -200.0f, 0.0f};
	player[0]->body.rotation.z = 200;

	scenery[0] = scenery_create(0, "rom:/models/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/models/pole.t3dm");
	scenery[2] = scenery_create(2, "rom:/models/brew_flag.t3dm");
	scenery[3] = scenery_create(3, "rom:/models/pole.t3dm");
	scenery[4] = scenery_create(4, "rom:/models/sphere.t3dm");
	scenery[5] = scenery_create(5, "rom:/models/pole.t3dm");
	scenery[6] = scenery_create(6, "rom:/models/sphere.t3dm");
	scenery[7] = scenery_create(7, "rom:/models/pole.t3dm");
	scenery[8] = scenery_create(8, "rom:/models/sphere.t3dm");
	scenery[9] = scenery_create(9, "rom:/models/pole.t3dm");
	scenery[10] = scenery_create(10, "rom:/models/sphere.t3dm");

	scenery[0]->position.z = -2;
	scenery_update(scenery[0]);

	scenery[1]->position.z = -2;
	scenery[1]->scale.z = 2.4f;
	scenery_update(scenery[1]);

	scenery[2]->position = (Vector3){5.0f, 0.0f, 995.0f};
	scenery[2]->scale =(Vector3){2.0f, 2.0f, 2.0f};
	scenery_update(scenery[2]);

	scenery[3]->position = (Vector3){1895.0f, 0.0f, -2.0f};
	scenery_update(scenery[3]);
	scenery[4]->position = (Vector3){1895.0f, 0.0f, 600.0f};
	scenery[4]->rotation.x =270.0f;
	scenery_update(scenery[4]);

	scenery[5]->position = (Vector3){-1895.0f, 0.0f, -2.0f};
	scenery_update(scenery[5]);
	scenery[6]->position = (Vector3){-1895.0f, 0.0f, 600.0f};
	scenery[6]->rotation.x =270.0f;
	scenery_update(scenery[6]);

	scenery[7]->position = (Vector3){0.0f, 1895.0f, -2.0f};
	scenery_update(scenery[7]);
	scenery[8]->position = (Vector3){0.0f, 1895.0f, 600.0f};
	scenery[8]->rotation.x =270.0f;
	scenery_update(scenery[8]);	

	scenery[9]->position = (Vector3){0.0f, -1895.0f, -2.0f};
	scenery_update(scenery[9]);
	scenery[10]->position = (Vector3){0.0f, -1895.0f, 600.0f};
	scenery[10]->rotation.x =270.0f;
	scenery_update(scenery[10]);

}