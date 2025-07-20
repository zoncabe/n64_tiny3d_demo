#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_COUNT 2


typedef struct {
    
    uint8_t id;
    uint8_t actor_id;
    
    ControllerData control;
    
} Player;

extern Player player[PLAYER_COUNT];


void player_init(Player* player);
void player_setControllerData(Player* player);


#endif