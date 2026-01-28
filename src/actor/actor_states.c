#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_states.h"


void actor_setState(ActorStateData *state, uint8_t new_state) 
{
    switch(new_state) {
        
        case STANDING_IDLE: {
            if (state->current == STANDING_IDLE) return;
            state->previous = state->current;
            state->current = STANDING_IDLE;
            state->locomotion = STANDING_IDLE;
            break;
        }

        case WALKING: {
            if (state->current == WALKING) return;
            state->previous = state->current;
            state->current = WALKING;
            state->locomotion = WALKING;
            break;
        }

        case RUNNING: {
            if (state->current == RUNNING) return;
            state->previous = state->current;
            state->current = RUNNING;
            state->locomotion = RUNNING;
            break;
        }

        case SPRINTING: {
            if (state->current == SPRINTING) return;
            state->previous = state->current;
            state->current = SPRINTING;
            state->locomotion = SPRINTING;
            break;
        }

        case ROLLING: {
            if (state->current == ROLLING) return;
            state->previous = state->current;
            state->current = ROLLING;
            break;
        }
        
        case JUMPING: {
            if (state->current == JUMPING) return;
            state->previous = state->current;
            state->current = JUMPING;
            break;
        }
        
        case FALLING: {
            if (state->current == FALLING ) return;
            state->previous = state->current;
            state->current = FALLING;
            break;
        }   
    }
}
