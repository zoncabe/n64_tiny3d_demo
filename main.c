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

#include "include/screen/screen.h"
#include "include/camera/lighting.h"
#include "include/camera/camera.h"

#include "include/actor/actor.h"
#include "include/actor/actor_animation.h"

#include "include/scene/scene.h"
#include "include/scene/scenery.h"

#include "include/ui/ui.h"

#include "include/player/player.h"

#include "include/game/game.h"
#include "include/game/game_control.h"
#include "include/game/game_states.h"

#include "include/memory/memory.h"


int main()
{
	// ======== Init ======== //

	//debug_init_isviewer();
	//debug_init_usblog();
	
	asset_init_compression(2);
	dfs_init(DFS_DEFAULT_LOCATION);
	
	game_init(&game);

	actor[0] = actor_create(0, "rom:/male_steroids.t3dm");
	
	actor[0]->body.position.y = -200;
	actor[0]->body.position.x = -200;

	scenery[0] = scenery_create(0, "rom:/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/n64logo.t3dm");
	
	scenery[0]->position.z = -10;
	scenery[1]->position.z = -10;

	// ======== Main Loop ======== //

	for(;;)
	{
		
		time_setData(&game.timing);

		//game.timing.frame_time *= 2.0f;      // i use this as a workaround for my crappy pc not running ares fullspeed :')
		
		player_setControllerData(&player[0]);

		game_setState(&game, player, actor, scenery);

	}

	// ======== Clean Up ======== //

	actor_delete(actor[0]);

	scenery_delete(scenery[0]);
	scenery_delete(scenery[1]);

	t3d_destroy();

	return 0;
}
