#include <libdragon.h>
#include "../../include/graphics/font.h"


rdpq_font_t *DroiSans;

void fonts_init()
{

    DroiSans = rdpq_font_load("rom:/fonts/DroidSans.font64");
    rdpq_text_register_font(DROID_SANS, DroiSans);

}