#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"


void player_setState(Player *player, uint8_t state) 
{
    switch(state) {
        
        case STAND_IDLE: {
            if (player->state.current == STAND_IDLE) return;
            player->state.previous = player->state.current;
            player->state.current = STAND_IDLE;
            player->state.locomotion = STAND_IDLE;
            break;
        }

        case WALKING: {
            if (player->state.current == WALKING) return;
            player->state.previous = player->state.current;
            player->state.current = WALKING;
            player->state.locomotion = WALKING;
            break;
        }

        case RUNNING: {
            if (player->state.current == RUNNING) return;
            player->state.previous = player->state.current;
            player->state.current = RUNNING;
            player->state.locomotion = RUNNING;
            break;
        }

        case SPRINTING: {
            if (player->state.current == SPRINTING) return;
            player->state.previous = player->state.current;
            player->state.current = SPRINTING;
            player->state.locomotion = SPRINTING;
            break;
        }

        case ROLLING: {
            if (player->state.current == ROLLING) return;
            player->state.previous = player->state.current;
            player->state.current = ROLLING;
            break;
        }
        
        case JUMPING: {
            if (player->state.current == JUMPING) return;
            player->state.previous = player->state.current;
            player->state.current = JUMPING;
            player->motion_data.grounded = false;
            //player->motion_-data.grounding_height = -FLT_MAX;
            break;
        }
        
        case FALLING: {
            if (player->state.current == FALLING ) return;
            player->state.previous = player->state.current;
            player->state.current = FALLING;
            //player->motion_-data.grounding_height = -FLT_MAX;
            break;
        }   
    }
}
