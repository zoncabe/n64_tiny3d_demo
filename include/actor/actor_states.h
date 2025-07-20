#ifndef ACTORSTATES_H
#define ACTORSTATES_H


#define STAND_IDLE 1
#define WALKING 2
#define RUNNING 3
#define SPRINTING 4
#define ROLLING 5
#define JUMPING 6
#define FALLING 7

void actor_setState(Actor *actor, uint8_t state);

#endif