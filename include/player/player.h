#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_COUNT 2


typedef struct {

    uint8_t id;
    uint8_t actor_id;
    
    ControllerData control;

} Player;


void player_init(Player* player);
void player_setControllerData(Player* player);


#endif