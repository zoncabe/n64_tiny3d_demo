#ifndef UI_H
#define UI_H

#define DROID_SANS 1


typedef struct {

    rdpq_font_t *font;
    int box_width;
    int box_height;

} UI;

extern UI ui;

void ui_init();
void ui_printDebugData(Actor* actor, TimeData time);


#endif 