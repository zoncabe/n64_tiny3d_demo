#ifndef TIME_H
#define TIME_H


// structures

typedef struct
{
    float counter;
    float delta;
    float rate;

  	rspq_syncpoint_t syncPoint;

} TimeData;

extern TimeData timer;


// functions prototypes

void time_init();
void time_update();


#endif