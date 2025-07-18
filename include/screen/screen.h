#ifndef SCREEN_H
#define SCREEN_H


#include <t3d/t3d.h>


typedef struct {

	T3DViewport t3d_viewport;

} Screen;


void screen_init(Screen* screen);
void screen_clear(Screen* screen);


#endif