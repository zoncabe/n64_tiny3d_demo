#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_states.h"


void actor_setState(Actor *actor, uint8_t state) 
{
    switch(state) {
        
        case STAND_IDLE: {
            if (actor->state == STAND_IDLE) return;
            actor->previous_state = actor->state;
            actor->state = STAND_IDLE;
            actor->locomotion_state = STAND_IDLE;
            break;
        }

        case WALKING: {
            if (actor->state == WALKING) return;
            actor->previous_state = actor->state;
            actor->state = WALKING;
            actor->locomotion_state = WALKING;
            break;
        }
        case RUNNING: {
            if (actor->state == RUNNING) return;
            actor->previous_state = actor->state;
            actor->state = RUNNING;
            actor->locomotion_state = RUNNING;
            break;
        }
        case SPRINTING: {
            if (actor->state == SPRINTING) return;
            actor->previous_state = actor->state;
            actor->state = SPRINTING;
            actor->locomotion_state = SPRINTING;
            break;
        }

        case ROLLING: {
            if (actor->state == ROLLING) return;
            actor->previous_state = actor->state;
            actor->state = ROLLING;
            break;
        }
        
        case JUMPING: {
            if (actor->state == JUMPING) return;
            actor->previous_state = actor->state;
            actor->state = JUMPING;
            actor->grounded = 0;
            //actor->grounding_height = -FLT_MAX;
            break;
        }
        case FALLING: {
            if (actor->state == FALLING ) return;
            actor->previous_state = actor->state;
            actor->state = FALLING;
            //actor->grounding_height = -FLT_MAX;
            break;
        }   
    }
}
