#include <libdragon.h>

#include "../../include/time/time.h"


// functions implementations

/* sets time data values to zero */
void time_init(TimeData *time)
{
    time->frame_time = 0.0f;
    time->frame_rate = 0.0f;
  	time->syncPoint = 0.0f;
}


/* sets timing data */
void time_setData(TimeData* time)
{
    time->frame_time = display_get_delta_time();
    time->frame_rate = display_get_fps();
}