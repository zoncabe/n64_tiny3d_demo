#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H


int input(int input);

void cameraControl_orbit_withStick(Camera *camera, ControllerData *data);
void cameraControl_orbit_withCButtons(Camera *camera, ControllerData *data);
void cameraControl_aim(Camera *camera, ControllerData *data);

void cameraControl_setOrbitalMovement(Camera *camera, ControllerData *data);


#endif