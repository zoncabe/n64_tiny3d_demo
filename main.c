#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>
#include <t3d/t3ddebug.h>


#define PLAYER_COUNT 1
#define ACTOR_COUNT 1
#define SCENERY_COUNT 2


#include "screen/screen.h"
#include "control/control.h"
#include "time/time.h"

#include "physics/physics.h"

#include "camera/camera.h"
#include "camera/camera_states.h"
#include "camera/camera_control.h"

#include "actor/actor.h"
#include "actor/actor_states.h"
#include "actor/actor_motion.h"
#include "actor/actor_control.h"

#include "physics/actor_collision/actor_collision_detection.h"
#include "physics/actor_collision/actor_collision_response.h"

#include "actor/actor_animation.h"

#include "scene/scene.h"
#include "scene/scenery.h"

#include "ui/ui.h"

#include "player/player.h"
#include "game/game.h"
#include "player/player_control.h"
#include "game/game_states.h"


Game game;

Player player[PLAYER_COUNT];

Actor actor[ACTOR_COUNT];

Scenery scenery[SCENERY_COUNT];


int main()
{
	// ======== Init ======== //

	//debug_init_isviewer();
	//debug_init_usblog();
	
	asset_init_compression(2);
	dfs_init(DFS_DEFAULT_LOCATION);
	
	game_init(&game);

	actor[0] = actor_create(0, "rom:/male_steroids.t3dm");

	scenery[0] = scenery_create(0, "rom:/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/n64logo.t3dm");

	actor[0].body.position.x = -200;
	actor[0].body.position.y = -200;


	// ======== Main Loop ======== //

	for(;;)
	{
		
		time_setData(&game.timing);
		
		player_setControllerData(&player[0]);

		game_setState(&game, player, actor, scenery);

	}

	// ======== Clean Up ======== //

	actor_delete(&actor[0]);

	scenery_delete(&scenery[0]);
	scenery_delete(&scenery[1]);

	t3d_destroy();

	return 0;
}
