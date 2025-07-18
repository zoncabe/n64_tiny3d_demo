#ifndef UI_H
#define UI_H

#include "../../include/actor/actor.h"
#include "../../include/time/time.h"

#define DROID_SANS 1


typedef struct {

    rdpq_font_t *font;
    int box_width;
    int box_height;

} UI;



void ui_init(UI* ui);
void ui_printDebugData(UI* ui, Actor* actor, TimeData time);


#endif 