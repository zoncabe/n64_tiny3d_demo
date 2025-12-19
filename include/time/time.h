#ifndef TIME_H
#define TIME_H


// structures

typedef struct
{
    float counter;
    float delta;
    float rate;

    float intro_counter;
    float transition_counter;

} TimeData;

extern TimeData timer;


// functions prototypes

void time_init();
void time_update();


#endif