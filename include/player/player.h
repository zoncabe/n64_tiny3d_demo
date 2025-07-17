#ifndef PLAYER_H
#define PLAYER_H


typedef struct {

    uint8_t id;
    uint8_t actor_id;
    
    ControllerData control;

} Player;


void player_init(Player* player)
{
}

void player_setControllerData(Player* player)
{
    joypad_poll();
    
    for (int i = 0; i < PLAYER_COUNT; i++) {
        
        controllerData_getInputs(&player[i].control, i);
    } 
}

#endif