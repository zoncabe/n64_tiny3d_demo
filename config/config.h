#ifndef UNFLEX_HELPER_H
#define UNFLEX_HELPER_H


/*********************************
         Configuration Macros
*********************************/

// TV Types
#define NTSC    0
#define PAL     1
#define MPAL    2

// TV setting
#define TV_TYPE NTSC

// Rendering resolution
#define SCREEN_WD 320
#define SCREEN_HT 240


/*********************************
             Globals
*********************************/

extern Gfx rspinit_dl[];
extern Gfx rdpinit_dl[];

extern NUContData contdata[2];


/*********************************
            Functions
*********************************/

void rcp_init();
void fb_clear(u8 r, u8 g, u8 b);
void shading_set_options();

#endif