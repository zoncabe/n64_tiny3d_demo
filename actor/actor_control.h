#ifndef ACTOR_CONTROLS_H
#define ACTOR_CONTROLS_H


// function prototypes

void actorControl_setJump(Actor* actor, ControllerData *control);
void actorControl_setRoll(Actor* actor, ControllerData *control);
void actorControl_moveWithStick(Actor* actor, ControllerData *control, float camera_angle_around, float camera_offset);
void actor_setControlData(Actor* actor, ControllerData *control, float camera_angle_around, float camera_offset);


// function implementations

void actorControl_setJump(Actor* actor, ControllerData *control)
{    
    if (control->pressed.a && actor->state != ROLLING && actor->state != JUMPING && actor->state != FALLING){
        
        actor->input.jump_hold = true;
        actor_setState(actor, JUMPING);
    }
    else if (control->held.a){
    }
    else{

        actor->input.jump_hold = false;    
    }
}

void actorControl_setRoll(Actor* actor, ControllerData *control)
{

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
   
    actorControl_setJump(actor, control);

    actorControl_moveWithStick(actor, control, camera_angle_around, camera_offset);

}

#endif