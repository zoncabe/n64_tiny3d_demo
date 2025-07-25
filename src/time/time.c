#include <libdragon.h>

#include "../../include/time/time.h"


TimeData timer;


// functions implementations

/* sets time data values to zero */
void time_init()
{
    timer.counter = 1.0f;
    timer.delta = 0.0f;
    timer.rate = 0.0f;
  	timer.syncPoint = 0.0f;
}


/* sets timing data */
void time_update()
{
    timer.delta = display_get_delta_time();
    timer.rate = display_get_fps();
}