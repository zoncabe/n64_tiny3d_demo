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
#include "include/viewport/camera.h"
#include "include/viewport/viewport.h"

#include "include/actor/actor.h"
#include "include/actor/actor_animation.h"

#include "include/scene/scenery.h"

#include "include/ui/ui.h"
#include "include/ui/menu.h"

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
	player[0].actor->body.position =(Vector3){-195.0f, -500.0f, 0.0f};
	player[0].actor->body.rotation.z = 200;
	
	player[1].actor = actor_create(1, "rom:/gorilla.t3dm");
	player[1].actor->body.position =(Vector3){195.0f, 500.0f, 0.0f};
	player[1].actor->body.rotation.z = 1;

	scenery[0] = scenery_create(0, "rom:/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/brew_flag.t3dm");
	scenery[2] = scenery_create(2, "rom:/pole.t3dm");
	scenery[3] = scenery_create(3, "rom:/n64logo.t3dm");

	scenery[0]->position.z = -3;
	scenery[3]->position.z = -3;

	scenery[1]->scale =(Vector3){2.0f, 2.0f, 2.0f};
	scenery[2]->scale =(Vector3){1.5f, 1.5f, 1.7f};
	scenery[3]->scale =(Vector3){0.7f, 0.7f, 0.7f};

	scenery[1]->position =(Vector3){   12.0f,  2000.0f,  600.0f};
	scenery[2]->position =(Vector3){  195.0f,  2000.0f,    0.0f};
    
	// ======== Main Loop ======== //

	for(;;)
	{
		time_update();
		timer.delta *= 2.0f; 
		
		player_setControllerData();
		
		game_updateState();

		render();
	}


	// ======== Clean Up ======== //

	actor_delete(player[0].actor);
	actor_delete(player[1].actor);

	scenery_delete(scenery[0]);
	scenery_delete(scenery[1]);
	scenery_delete(scenery[2]);
	scenery_delete(scenery[3]);

	menu_pauseClean();

	t3d_destroy();

	return 0;
}
