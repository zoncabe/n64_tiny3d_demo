#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/graphics/lighting.h"
#include "../../include/viewport/camera.h"
#include "../../include/control/camera_control.h"
#include "../../include/viewport/viewport.h"
#include "../../include/player/player.h"

const resolution_t WIDESCREEN = {.width = 424, .height = 240, .interlaced = INTERLACE_OFF};

Viewport viewport;

void viewport_init()
{
	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
	viewport.t3d_viewport = t3d_viewport_create();
	t3d_init((T3DInitParams){});
    camera_init(&viewport.camera);
    light_init(&light);
}

void viewport_clear()
{
	rdpq_attach(display_get(), display_get_zbuf());
	t3d_frame_start();
	t3d_viewport_attach(&viewport.t3d_viewport);

	t3d_screen_clear_color(RGBA32(154, 181, 198, 0xFF));
	t3d_screen_clear_depth();
}

void viewport_setGameplayCamera()
{
    t3d_viewport_set_projection(
        &viewport.t3d_viewport, 
        T3D_DEG_TO_RAD(viewport.camera.field_of_view), 
        viewport.camera.near_clipping,
		viewport.camera.far_clipping
    );

    t3d_viewport_look_at(
        &viewport.t3d_viewport, 
        &(T3DVec3){{viewport.camera.position.x, viewport.camera.position.y, viewport.camera.position.z}}, 
        &(T3DVec3){{viewport.camera.target.x, viewport.camera.target.y, viewport.camera.target.z}}, 
        &(T3DVec3){{0, 0, 1}}
    );
}

void viewport_updateGameplayCamera()
{
    cameraControl_setOrbitalMovement(&viewport.camera, &player[0].control);
    camera_updateOrbitalPosition(&viewport.camera, &player[0].actor->body.position, timer.delta);
    viewport_setGameplayCamera();
}
