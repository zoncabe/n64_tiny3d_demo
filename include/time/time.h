#ifndef TIME_H
#define TIME_H


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

#endif