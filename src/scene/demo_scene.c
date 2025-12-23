#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/light/lighting.h"
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
#include "../../include/graphics/color.h"

color_t red = {255, 0, 0, 0xFF}, green = {0, 255, 0, 0xFF}, blue = {0, 0, 255, 0xFF};

float interpolator[4] = {0.0f, 0.75f, 1.5f, 2.25f};

color_t lamp[4];

void set_RGB_colors(color_t *color, float *interpolator)
{

    *interpolator += timer.delta;
    if (*interpolator >= 3.0f) *interpolator -= 3.0f;

    if (*interpolator < 1.0f) *color = color_lerp(&red, &blue, *interpolator);
    else if (*interpolator < 2.0f) *color = color_lerp(&blue, &green, *interpolator - 1.0f);
    else *color = color_lerp(&green, &red, *interpolator - 2.0f);
}

void change_lamp_colors()
{
	for (int i = 0; i < 4; i++) {
		set_RGB_colors(&lamp[i], &interpolator[i]);
		light_updatePoint(&light.point[i], light.point[i].position, lamp[i], light.point[i].size);
	}
}


color_t ambient_color = {10, 10, 10, 0xFF};

void init_demoScene()
{
	//light_initAmbient(ambient_color);
	//light_initDirectional(&light.directional[0], (T3DVec3){{1.0f, -1.0f, 1.0f}}, (color_t){200, 200, 220, 0xFF});
	
	light_initPoint(&light.point[0], (T3DVec3){{1895.0f, 0.0f, 600.0f}}, lamp[0], 800.0f);
	light_initPoint(&light.point[1], (T3DVec3){{-1895.0f, 0.0f, 600.0f}}, lamp[1], 800.0f);
	light_initPoint(&light.point[2], (T3DVec3){{0.0f, 1895.0f, 600.0f}}, lamp[2], 800.0f);
	light_initPoint(&light.point[3], (T3DVec3){{0.0f, -1895.0f, 600.0f}}, lamp[3], 800.0f);
	light_initPoint(&light.point[4], (T3DVec3){{0.0f, 1200.0f, 1800.0f}}, (color_t){255, 255, 255, 0xFF}, 1600.0f);
	light_initPoint(&light.point[5], (T3DVec3){{0.0f, -1200.0f, 1800.0f}}, (color_t){255, 255, 255, 0xFF}, 1600.0f);

    player[0] = player_create(0, "rom:/models/male_muscled.t3dm", &male_muscled_motion_settings, &male_muscled_animation_settings);
	player[0]->body.position =(Vector3){-195.0f, -200.0f, 0.0f};
	player[0]->body.rotation.z = 200;

	scenery[0] = scenery_create(0, "rom:/models/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/models/pole.t3dm");
	scenery[2] = scenery_create(2, "rom:/models/bandera_uruguay.t3dm");

	scenery[3] = scenery_create(3, "rom:/models/pole.t3dm");
	scenery[4] = scenery_create(4, "rom:/models/lamp.t3dm");
	scenery[5] = scenery_create(5, "rom:/models/pole.t3dm");
	scenery[6] = scenery_create(6, "rom:/models/lamp.t3dm");
	scenery[7] = scenery_create(7, "rom:/models/pole.t3dm");
	scenery[8] = scenery_create(8, "rom:/models/lamp.t3dm");
	scenery[9] = scenery_create(9, "rom:/models/pole.t3dm");
	scenery[10] = scenery_create(10, "rom:/models/lamp.t3dm");
	scenery[11] = scenery_create(11, "rom:/models/lamp.t3dm");
	scenery[12] = scenery_create(12, "rom:/models/lamp.t3dm");
	scenery[13] = scenery_create(13, "rom:/models/pole.t3dm");
	scenery[14] = scenery_create(14, "rom:/models/pole.t3dm");

	scenery[0]->position.z = -2;
	scenery_update(scenery[0]);

	scenery[1]->position.z = -2;
	scenery[1]->scale.z = 2.4f;
	scenery_update(scenery[1]);

	scenery[2]->position = (Vector3){5.0f, 0.0f, 995.0f};
	scenery[2]->scale =(Vector3){3.0f, 3.0f, 3.0f};
	scenery_update(scenery[2]);

	/*
	*/
	scenery[3]->position = (Vector3){1895.0f, 0.0f, -2.0f};
	scenery_update(scenery[3]);
	scenery[4]->position = (Vector3){1895.0f, 0.0f, 600.0f};
	scenery_update(scenery[4]);

	scenery[5]->position = (Vector3){-1895.0f, 0.0f, -2.0f};
	scenery_update(scenery[5]);
	scenery[6]->position = (Vector3){-1895.0f, 0.0f, 600.0f};
	scenery_update(scenery[6]);

	scenery[7]->position = (Vector3){0.0f, 1895.0f, -2.0f};
	scenery_update(scenery[7]);
	scenery[8]->position = (Vector3){0.0f, 1895.0f, 600.0f};
	scenery_update(scenery[8]);	
	
	scenery[9]->position = (Vector3){0.0f, -1895.0f, -2.0f};
	scenery_update(scenery[9]);
	scenery[10]->position = (Vector3){0.0f, -1895.0f, 600.0f};
	scenery_update(scenery[10]);

	scenery[13]->position = (Vector3){0.0f, 1200.0f, 3000.0f};
	scenery[13]->rotation.x = 180.0f;
	scenery[13]->scale.z = 1.8f;
	scenery_update(scenery[13]);
	scenery[11]->position = (Vector3){0.0f, 1200.0f, 1800.0f};
	scenery[11]->scale = (Vector3){3.0f, 3.0f, 3.0f};
	scenery_update(scenery[11]);

	scenery[14]->position = (Vector3){0.0f, -1200.0f, 3000.0f};
	scenery[14]->rotation.x = 180.0f;
	scenery[14]->scale.z = 1.8f;
	scenery_update(scenery[14]);
	scenery[12]->position = (Vector3){0.0f, -1200.0f, 1800.0f};
	scenery[12]->scale = (Vector3){3.0f, 3.0f, 3.0f};
	scenery_update(scenery[12]);

}