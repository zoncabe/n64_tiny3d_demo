#ifndef ACTOR_CONTROLS_H
#define ACTOR_CONTROLS_H


// function prototypes

void jump(Actor* actor, ControllerData *data, float frame_time);
void roll(Actor* actor, ControllerData *data);
void move_with_stick(Actor* actor, ControllerData *data, float camera_angle_around);
void actorControl_setMotion(Actor* actor, ControllerData *data, float frame_time, float camera_angle_around);


// function implementations

void jump(Actor* actor, ControllerData *data, float frame_time)
{    
    if (data->pressed.a && actor->state != ROLL && actor->state != JUMP && actor->state != FALLING) {
        
        actor->input.jump_hold = true;
        actor->input.jump_released = false;
        actor_setState(actor, JUMP);
    }

    else if (data->held.a && actor->state == JUMP) {
        
        actor->input.jump_time_held += frame_time;
    }
    else {

        actor->input.jump_released = true;
        actor->input.jump_hold = false;    
    }
}

void roll(Actor* actor, ControllerData *data)
{

}

void move_with_stick(Actor *actor, ControllerData *data, float camera_angle_around)
{
    int deadzone = 8;
    float stick_magnitude = 0; 

    if (fabs(data->input.stick_x) >= deadzone || fabs(data->input.stick_y) >= deadzone) {

        Vector2 stick = {data->input.stick_x, data->input.stick_y};
        
        stick_magnitude = vector2_magnitude(&stick);
        actor->target_yaw = deg(atan2(data->input.stick_x, -data->input.stick_y) - rad(camera_angle_around));
    }

    
    if (stick_magnitude == 0 && actor->state != ROLL && actor->state != JUMP && actor->state != FALLING){
        actor_setState(actor, STAND_IDLE);
    }

    else if (stick_magnitude > 0 && stick_magnitude <= 64 && actor->state != ROLL && actor->state != JUMP && actor->state != FALLING){
        actor_setState(actor, WALKING);
    }

    else if (data->held.r && stick_magnitude > 64 && actor->state != ROLL && actor->state != JUMP && actor->state != FALLING){
        actor_setState(actor, SPRINTING);
    }

    else if (stick_magnitude > 64 && actor->state != ROLL && actor->state != JUMP && actor->state != FALLING){
        actor_setState(actor, RUNNING);
    }
}


void actorControl_setMotion(Actor* actor, ControllerData *data, float frame_time, float camera_angle_around)
{    
   
    jump(actor, data, frame_time);

    move_with_stick(actor, data, camera_angle_around);

}



#endif