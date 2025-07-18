#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H


#include "../../include/camera/camera.h"
#include "../../include/control/control.h"
#include "../../include/screen/screen.h"




int input(int input);

void cameraControl_orbit_withStick(Camera *camera, ControllerData *data);
void cameraControl_orbit_withCButtons(Camera *camera, ControllerData *data);
void cameraControl_aim(Camera *camera, ControllerData *data);

void cameraControl_setOrbitalMovement(Camera *camera, ControllerData *data);
void camera_update(Camera *camera, ControllerData* control, Screen* screen, Vector3* barycenter, float frame_time);



#endif