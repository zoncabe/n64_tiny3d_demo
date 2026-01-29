#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_COUNT 2


typedef struct {

    ControllerData control;

    Actor actor;
	
} Player;


extern Player* player[PLAYER_COUNT];

void player_init(Player* player, ActorMotionSettings* motion_settings, ActorAnimationSettings* animation_settings);

void player_update();



#endif