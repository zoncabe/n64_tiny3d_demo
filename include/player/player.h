#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_COUNT 1


typedef struct {
    
    uint8_t id;

    Actor *actor;
    
    ControllerData control;
    
} Player;


extern Player player[PLAYER_COUNT];


void player_init(Player* player);
void player_updateActor();



#endif