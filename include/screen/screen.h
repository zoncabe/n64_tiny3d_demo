#ifndef SCREEN_H
#define SCREEN_H


typedef struct {

	T3DViewport t3d_viewport;

} Screen;


void screen_init(Screen* screen);
void screen_clear(Screen* screen);


#endif