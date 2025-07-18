#ifndef CAMERA_STATES_H
#define CAMERA_STATES_H


#include "../../include/camera/camera.h"

// function prototypes

void set_orbital(Camera *camera);
void set_aiming(Camera *camera);
void camera_setState(Camera *camera, CameraState new_state);


#endif
