#ifndef TIME_H
#define TIME_H

#include <libdragon.h>


// structures

typedef struct
{
    float frame_time;
    float frame_rate;

  	rspq_syncpoint_t syncPoint;

} TimeData;


// functions prototypes

void time_init(TimeData *time);
void time_setData(TimeData *time);


#endif