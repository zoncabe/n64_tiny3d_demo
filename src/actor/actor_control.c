#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_states.h"
#include "../../include/actor/actor_control.h"


// function implementations

void actorControl_setJump(Actor* actor, ControllerData *control)
{    
    if (control->pressed.a && actor->state != ROLLING && actor->state != JUMPING && actor->state != FALLING){
        
        actor->input.jump_hold = true;
        actor->input.jump_initial_velocity = actor->body.velocity;
        actor_setState(actor, JUMPING);
    }
    
    else if (control->held.a) return;
    
    else actor->input.jump_hold = false;
}

void actorControl_setRoll(Actor* actor, ControllerData *control)
{
    if (control->pressed.b 
        && actor->state != ROLLING
        && actor->state != STAND_IDLE
        && actor->state != WALKING
        && actor->state != JUMPING
        && actor->state != FALLING){

        actor_setState(actor, ROLLING);
    }
}

void actorControl_moveWithStick(Actor *actor, ControllerData *control, float camera_angle_around, float camera_offset)
{
    int deadzone = 6;
    float stick_magnitude = 0; 

    if (fabs(control->input.stick_x) >= deadzone || fabs(control->input.stick_y) >= deadzone) {

        Vector2 stick = {control->input.stick_x, control->input.stick_y};
        
        stick_magnitude = vector2_magnitude(&stick);
        actor->target_yaw = deg(atan2(control->input.stick_x, -control->input.stick_y) - rad(camera_angle_around - (0.5 * camera_offset)));
    }

    
    if (stick_magnitude == 0 && actor->state != ROLLING && actor->state != JUMPING && actor->state != FALLING){
        actor_setState(actor, STAND_IDLE);
    }

    else if (stick_magnitude > 0 && stick_magnitude <= 65 && actor->state != ROLLING && actor->state != JUMPING && actor->state != FALLING){
        actor_setState(actor, WALKING);
    }

    else if (control->held.r && stick_magnitude > 65 && actor->state != ROLLING && actor->state != JUMPING && actor->state != FALLING){
        actor_setState(actor, SPRINTING);
    }

    else if (stick_magnitude > 65 && actor->state != ROLLING && actor->state != JUMPING && actor->state != FALLING){
        actor_setState(actor, RUNNING);
    }
}

void actor_setControlData(Actor* actor, ControllerData *control, float camera_angle_around, float camera_offset)
{    
    actorControl_setRoll(actor, control);
    
    actorControl_setJump(actor, control);
    
    actorControl_moveWithStick(actor, control, camera_angle_around, camera_offset);
}
