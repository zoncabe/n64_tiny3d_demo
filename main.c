#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>
//#include <t3d/t3ddebug.h>

#include "include/time/time.h"
#include "include/physics/physics.h"

#include "include/control/control.h"

#include "include/graphics/lighting.h"
#include "include/camera/camera.h"
#include "include/graphics/viewport.h"

#include "include/actor/actor.h"
#include "include/actor/actor_animation.h"

#include "include/scene/scenery.h"

#include "include/ui/ui.h"

#include "include/player/player.h"
#include "include/control/player_control.h"

#include "include/game/game.h"
#include "include/game/game_states.h"

#include "include/graphics/render.h"

#include "include/memory/memory.h"


int main()
{
	// ======== Init ======== //

	//debug_init_isviewer();
	//debug_init_usblog();
	
	game_init();

	player[0].actor = actor_create(0, "rom:/male_steroids.t3dm");
	player[0].actor->body.position.y = -200;
	player[0].actor->body.position.x = -200;

	scenery[0] = scenery_create(0, "rom:/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/n64logo.t3dm");
	scenery[0]->position.z = -10;
	scenery[1]->position.z = -10;


	// ======== Main Loop ======== //

	for(;;)
	{
		time_update();
		timer.delta *= 2.0f; 
		
		player_setControllerData();
		
		gameState_update();

		render();
	}


	// ======== Clean Up ======== //

	actor_delete(player[0].actor);

	scenery_delete(scenery[0]);
	scenery_delete(scenery[1]);

	t3d_destroy();

	return 0;
}
