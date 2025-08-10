#ifndef ACTORSTATES_H
#define ACTORSTATES_H


#define STAND_IDLE 0
#define WALKING 1
#define RUNNING 2
#define SPRINTING 3
#define ROLLING 4
#define JUMPING 5
#define FALLING 6

void player_setState(Player* player, uint8_t state);

#endif