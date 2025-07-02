#ifndef ACTORSTATES_H
#define ACTORSTATES_H


#define STAND_IDLE 1
#define WALKING 2
#define RUNNING 3
#define SPRINTING 4
#define ROLLING 5
#define JUMPING 6
#define FALLING 7


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

#endif