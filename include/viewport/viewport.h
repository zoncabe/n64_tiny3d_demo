#ifndef VIEWPORT_H
#define VIEWPORT_H


#define FB_COUNT 3

typedef struct {

	T3DViewport t3d_viewport;
	Camera camera;
	int fb_index;

} Viewport;

extern Viewport viewport;


void viewport_init();
void viewport_clear();
void viewport_setCamera();
void viewport_setOrbitalCamera();

#endif