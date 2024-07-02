#ifndef SCENE_H
#define SCENE_H


// Array sizes
#define GLIST_LENGTH 4096
#define HEAP_LENGTH  1024


/*********************************
             Globals
*********************************/

extern Gfx glist[];
extern Gfx* glistp;


/* scene function prototypes */ 

void scene_init();
void scene_update();
void scene_render();
    
    
#endif