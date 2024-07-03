#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H

/* CAMERA_CONTROLS.H
here are all the camera control related functions */


int input(int input);

void orbit_withStick(Camera *camera, ControllerData *data);
void orbit_withCButtons(Camera *camera, ControllerData *data);
void aim(Camera *camera, ControllerData *data);

void cameraControl_setOrbitalMovement(Camera *camera, ControllerData *data_0);



/* input
 auxiliary function for 8 directional movement*/

int input(int input){
    if (input == 0) {return 0;}
    else {return 1;}
}


/* camera_move_stick
changes the camera variables depending on controller input*/

void orbit_withStick(Camera *camera, ControllerData *data)
{
    int deadzone = 8;
    float stick_x = 0;
    float stick_y = 0;

    if (fabs(data->input.stick_x) >= deadzone || fabs(data->input.stick_y) >= deadzone) {
        stick_x = data->input.stick_x;
        stick_y = data->input.stick_y;
    }

    if (stick_x == 0 && stick_y == 0) {
        camera->orbitational_target_velocity.x = 0;
        camera->orbitational_target_velocity.y = 0;
    }
    
    else if (stick_x != 0 || stick_y != 0) {
        camera->orbitational_target_velocity.x = stick_y;
        camera->orbitational_target_velocity.y = stick_x;
    }
}


void orbit_withCButtons(Camera *camera, ControllerData *data)
{
    float input_x = 0;
    float input_y = 0;

    if ((data->held.c_right) || (data->held.c_left) || (data->held.c_up) || (data->held.c_down)){
        
        input_x = input(data->held.c_right) - input(data->held.c_left);
        input_y = input(data->held.c_up) - input(data->held.c_down);
    }

    if (input_x == 0) camera->orbitational_target_velocity.y = 0; 
    else camera->orbitational_target_velocity.y = input_x * camera->settings.orbitational_max_velocity.y;

	if (input_y == 0) camera->orbitational_target_velocity.x = 0; 
    else camera->orbitational_target_velocity.x = input_y * camera->settings.orbitational_max_velocity.x;

}


void aim(Camera *camera, ControllerData *data)
{
    if (data->held.z) camera_setState (camera, AIMING);
    else camera_setState (camera, ORBITAL);
}


void cameraControl_setOrbitalMovement(Camera *camera, ControllerData *data_0)
{
    //orbit_withStick(camera, data_1);
    orbit_withCButtons(camera, data_0);
    aim(camera, data_0);
}

#endif