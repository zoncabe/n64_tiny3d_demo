#ifndef UI_H
#define UI_H


// sliding transition directions
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define UI_TRANSITION_NORM 10.0f
#define UI_TRANSITION_FAST 20.0f

void ui_init();
void ui_drawDebugData();
void ui_drawSlidingTransition(float progress, float r, float g, float b, uint8_t direction);
void ui_drawFadingTransition(float progress, float r, float g, float b);
void ui_drawMainMenu();
void ui_drawPauseMenu();



#endif 