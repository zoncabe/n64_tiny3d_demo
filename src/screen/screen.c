
#include <libdragon.h>

#include "../../include/screen/screen.h"


void screen_init(Screen* screen)
{
	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
	screen->t3d_viewport = t3d_viewport_create();
}

void screen_clear(Screen* screen)
{
	rdpq_attach(display_get(), display_get_zbuf());
	t3d_frame_start();
	t3d_viewport_attach(&screen->t3d_viewport);

	t3d_screen_clear_color(RGBA32(154, 181, 198, 0xFF));
	t3d_screen_clear_depth();
}
