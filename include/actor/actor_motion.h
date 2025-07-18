#ifndef ACTOR_MOVEMENT_H
#define ACTOR_MOVEMENT_H


#include "../../include/actor/actor.h"

#define ACTOR_GRAVITY -1800

#define JUMP_MINIMUM_SPEED 500
#define JUMP_FORCE_MULTIPLIER 3000


// function prototypes


void actor_setMotion(Actor *actor, float frame_time);

#endif