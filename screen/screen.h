#ifndef SCREEN_H
#define SCREEN_H


typedef struct {
	
	surface_t depthBuffer; 
	T3DViewport t3d_viewport;

} Screen;


void screen_init(Screen* screen);
void screen_clear(Screen* screen);


void screen_init(Screen* screen)
{
	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
	screen->depthBuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());
	screen->t3d_viewport = t3d_viewport_create();
}

void screen_initDisplay(Screen* screen)
{
	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
	screen->depthBuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());
}

void screen_initT3dViewport(Screen* screen)
{
	screen->t3d_viewport = t3d_viewport_create();
}

void screen_clear(Screen* screen)
{
	rdpq_attach(display_get(), &screen->depthBuffer);
	t3d_frame_start();
	t3d_viewport_attach(&screen->t3d_viewport);

	t3d_screen_clear_color(RGBA32(154, 181, 198, 0xFF));
	t3d_screen_clear_depth();
}

void screen_clearDisplay(Screen* screen)
{
	rdpq_attach(display_get(), &screen->depthBuffer);
	t3d_screen_clear_color(RGBA32(154, 181, 198, 0xFF));
	t3d_screen_clear_depth();
}

void screen_clearT3dViewport(Screen* screen)
{
	t3d_frame_start();
	t3d_viewport_attach(&screen->t3d_viewport);
}


#endif