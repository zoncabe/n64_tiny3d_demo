#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>

#include "config/screen.h"
#include "control/controls.h"
#include "time/time.h"

#include "physics/physics.h"

#include "camera/camera.h"
#include "camera/camera_states.h"
#include "camera/camera_control.h"

#include "actor/actor.h"
#include "actor/actor_states.h"
#include "actor/actor_control.h"

#include "scene/scenery.h"


int main()
{
	debug_init_isviewer();
	debug_init_usblog();
	asset_init_compression(2);

	dfs_init(DFS_DEFAULT_LOCATION);

	Screen screen;
	screen_init(&screen);

	rdpq_init();
	joypad_init();

	TimeData timing;
	time_init(&timing);

	ControllerData control;

	t3d_init((T3DInitParams){});

	//camera
	Camera camera = camera_create();

	//light
	LightData light = light_create();

	//actor
	Actor player = actor_create(0, "rom:/capsule.t3dm");
    actor_setState(&player, STAND_IDLE);

	//scenery
	Scenery ground = scenery_create(0, "rom:/ground.t3dm");

	for(;;)
	{
		// ======== Update ======== //

		controllerData_getInputs(&control);
		time_setData(&timing);
		
		actorControl_setMotion(&player, &control, timing.frame_time_s, camera.angle_around_barycenter);
		actor_integrate(&player, timing.frame_time_s);
		actor_setState(&player, player.state);
		actor_set(&player);

		cameraControl_setOrbitalMovement(&camera, &control);
		camera_getOrbitalPosition(&camera, player.body.position, timing.frame_time_s);
		camera_set(&camera, &screen);

		scenery_set(&ground);

		// ======== Draw ======== //
		
		screen_clear(&screen);
	
		light_set(&light);
    
		t3d_matrix_push_pos(1);

		actor_draw(&player);

		scenery_draw(&ground);
   
   		t3d_matrix_pop(1);

		rdpq_detach_show();
	}

	t3d_destroy();
	return 0;
}
