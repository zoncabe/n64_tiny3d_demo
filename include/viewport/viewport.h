#ifndef VIEWPORT_H
#define VIEWPORT_H


typedef struct {

	T3DViewport t3d_viewport;
	Camera camera;

} Viewport;

extern Viewport viewport;


void viewport_init();
void viewport_clear();
void viewport_setGameplayCamera();
void viewport_updateGameplayCamera();

#endif