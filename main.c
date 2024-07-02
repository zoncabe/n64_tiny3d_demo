#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>

#include "controls/controls.h"
#include "time/time.h"

#include "physics/physics.h"

#include "actor/actor.h"
#include "actor/actor_states.h"
#include "actor/actor_control.h"
#include "actor/actor_collide.h"


int main()
{

	debug_init_isviewer();
	debug_init_usblog();
	asset_init_compression(2);

	dfs_init(DFS_DEFAULT_LOCATION);

	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
	surface_t depthBuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());

	rdpq_init();
	joypad_init();

	TimeData timing;
	time_init(&timing);

	ControllerData control;

	t3d_init((T3DInitParams){});

	//camera
	T3DViewport viewport = t3d_viewport_create();
	const T3DVec3 camPos = {{0,4.0f*64,3.0f*64}};
	const T3DVec3 camTarget = {{0,0,1.8f*64}};

	//light
	uint8_t colorAmbient[4] = {80, 80, 100, 0xFF};
	uint8_t colorDir[4]     = {0xEE, 0xAA, 0xAA, 0xFF};
	T3DVec3 lightDirVec = {{-1.0f, 1.0f, 1.0f}};
	t3d_vec3_norm(&lightDirVec);


	rspq_block_t *dl = NULL;
	Actor player = actor_create(0);
	player.model = t3d_model_load("rom:/capsule.t3dm");


	for(;;)
	{
	// ======== Update ======== //


	t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(85.0f), 0.1f, 1000.0f);
	t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,0,1}});

	controllerData_getInputs(&control);
	time_setData(&timing);

	actorControl_setMotion(&player, &control, timing.frame_time_s, 0.0f);

    actor_integrate(&player, timing.frame_time_s);
	actor_update(&player);

	// ======== Draw ======== //
	rdpq_attach(display_get(), &depthBuffer);
	t3d_frame_start();
	t3d_viewport_attach(&viewport);

	t3d_screen_clear_color(RGBA32(100, 80, 80, 0xFF));
	t3d_screen_clear_depth();

	t3d_light_set_ambient(colorAmbient);
	t3d_light_set_directional(0, colorDir, &lightDirVec);
	t3d_light_set_count(1);

	if(!dl) {
		rspq_block_begin();

		t3d_matrix_push(player.modelMat);
		// Draw the model, material settings (e.g. textures, color-combiner) are handled internally
		t3d_model_draw(player.model);
		t3d_matrix_pop(1);

		dl = rspq_block_end();
	}

	// for the actual draw, you can use the generic rspq-api.
	rspq_block_run(dl);

	rdpq_detach_show();
	}

	t3d_destroy();
	return 0;
}
