/*SCENE.C
handles the demo scene */


#include <nusys.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <float.h>

#include "scene.h"
#include "config.h"
#include "debug.h"
#include "time.h"

#include "physics.h"

#include "camera.h"
#include "camera_states.h"
#include "camera_control.h"

#include "actor.h"
#include "actor_states.h"
#include "actor_control.h"
#include "actor_collide.h"

#include "scenery.h"

#include "axis.h"
#include "textures.h"
#include "assets.h"


// Display list
Gfx glist[GLIST_LENGTH];
Gfx* glistp;


// globals

TimeData time_data;


Camera camera = {

    distance_from_barycenter: 1800,
    target_distance: 1800,
    angle_around_barycenter: 200,
    offset_angle: 6,
    rotation: {20, 0, 0,},
    offset_height: 180,
    
    settings: {

        orbitational_acceleration_rate: 15,
        orbitational_max_speed: {120, 100},

        zoom_acceleration_rate: 60,
        zoom_deceleration_rate: 20,
        zoom_max_speed: 3800,

        target_zoom: 1750,
        target_zoom_aim: 470,

	    offset_acceleration_rate: 25,
        offset_deceleration_rate: 45,
	    offset_max_speed: 80,

        target_offset: 6,
        target_offset_aim: 32,

	    max_pitch: 80,
    },
};


LightData light = {

    rotation: {57, 57, 57,},
};


Actor player = {

    mesh: gfx_capsule_mesh,

    scale: {1, 1, 1},
    grounding_height: 0,

    body: {
        position: {220, 230, 0,},
        velocity: {0, 0, 0,},
        rotation: {0, 0, 165,},
    },

    settings: {

        idle_acceleration_rate: 9,
        walk_acceleration_rate: 4,
        run_acceleration_rate: 6,
        roll_acceleration_rate: 20,
        roll_acceleration_grip_rate: 2,
        jump_acceleration_rate: 50,
        aerial_control_rate: 0.5,

        walk_target_speed: 350,
        run_target_speed: 700,
        sprint_target_speed: 900,
        idle_to_roll_target_speed: 300,
        idle_to_roll_grip_target_speed: 50,
        walk_to_roll_target_speed: 400,
        run_to_roll_target_speed: 780,
        sprint_to_roll_target_speed: 980,
        
        jump_target_speed: 550, 
        jump_timer_max: 0.20,
    },
};


Scenery axis = {

    scale: {1, 1, 1},
    position: {0, 0, 0},
    rotation: {0, 0, 0},

    mesh: gfx_axis,
};


Scenery box = {
    
    scale: {0.5f, 0.5f, 0.5f,},
    position: {500, 500, 25},
    rotation: {0.0f, 0.0f, 0.0f},
    mesh: gfx_cube_mesh,
};


Scenery ball = {


    scale: {0.5f, 0.5f, 0.5f,},
    position: {-500, -500, 25},
    rotation: {0, 0, 0},

    mesh: gfx_sphere_mesh,
};


Scenery ground = {

    scale: {1, 1, 1},
    position: {0, 0, 0},
    rotation: {0, 0, 0},

    mesh: gfx_ground_mesh,
};





void scene_set_dl()
{       
    scenery_set_dl(&axis);

    actor_set_dl(&player);

    scenery_set_dl(&box);
    
    scenery_set_dl(&ball);

    scenery_set_dl(&ground); 
}


/* print_debug_data      
sets debug information to be printed on screen */

void print_debug_data()
{
/*
    nuDebConTextPos(NU_DEB_CON_WINDOW0, 1, 1);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "velocity: %d, %d, %d", (int)player.body.velocity.x, (int)player.body.velocity.y, (int)player.body.velocity.z);
    
*/
}


/* scene_init
initializes the elements of the scene */

void scene_init(void)
{
    time_init(&time_data);
    actor_setState(&player, STAND_IDLE);
}


/* update_scene
handles the elements that modify the scene state */

void scene_update()
{
    //updates the frame timings
    time_setData(&time_data);
    
    // Read the controllers
    nuContDataGetEx(&contdata[0], 0);
    nuContDataGetEx(&contdata[1], 1);

    // Camera update
    cameraControl_setOrbitalMovement(&camera, &contdata[0], &contdata[1]);

    camera_getOrbitalPosition(&camera, player.body.position, time_data.frame_time);
    
    //Actor update

    actorControl_setMotion(&player, &contdata[0], time_data.frame_time, camera.angle_around_barycenter);

    actor_integrate(&player, time_data.frame_time);

    //actor_animate(&player);

    actor_collideWithPlayground(&player);
    
    actor_setState(&player, player.state);  
}


/* scene_render      
handles the system tasks to render the scene display list */

void scene_render(void)
{
    // Assign our glist pointer to our glist array for ease of access
    glistp = glist;

    // Initialize the RCP and framebuffer
    rcp_init();

    fb_clear(154, 181, 198);

    shading_set_options();
    
    camera_set_dl(&camera);

    light_set_dl(&light);

    scene_set_dl();  

    // Syncronize the RCP and CPU and specify that our display list has ended
    gDPFullSync(glistp++);
    gSPEndDisplayList(glistp++);
    
    // Ensure the chache lines are valid
    osWritebackDCache(&camera.projection, sizeof(camera.projection));
    osWritebackDCache(&camera.modeling, sizeof(camera.modeling));
    
    // Ensure we haven't gone over the display list size and start the graphics task
    debug_assert((glistp-glist) < GLIST_LENGTH);

    #if TV_TYPE != PAL
        // is this the command that actually draws stuff?
        nuGfxTaskStart(glist, (s32)(glistp - glist) * sizeof(Gfx), NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);
    #else
        nuGfxTaskStart(glist, (s32)(glistp - glist) * sizeof(Gfx), NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);
    #endif
    
    // Draw the menu (doesn't work on PAL)
    #if TV_TYPE != PAL
        nuDebConClear(NU_DEB_CON_WINDOW0);
        print_debug_data();
        nuDebConDisp(NU_SC_SWAPBUFFER);
    #endif
}
