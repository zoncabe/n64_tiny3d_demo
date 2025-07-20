#ifndef ACTOR_CONTROLS_H
#define ACTOR_CONTROLS_H


// function prototypes

void actorControl_setJump(Actor* actor, ControllerData *control);
void actorControl_setRoll(Actor* actor, ControllerData *control);
void actorControl_moveWithStick(Actor* actor, ControllerData *control, float camera_angle_around, float camera_offset);
void actor_setControlData(Actor* actor, ControllerData *control, float camera_angle_around, float camera_offset);


#endif