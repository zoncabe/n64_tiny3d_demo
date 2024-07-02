#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H

/* CAMERA_CONTROLS.H
here are all the camera control related functions */


int input(u32 input);

void orbit_withStick(Camera *camera, NUContData *contdata);
void orbit_withCButtons(Camera *camera, NUContData *contdata);
void aim(Camera *camera, NUContData *contdata);

void cameraControl_setOrbitalMovement(Camera *camera, NUContData *contdata_0, NUContData *contdata_1);



/* input
 auxiliary function for 8 directional movement*/

int input(u32 input){
    if (input == 0) {return 0;}
    else {return 1;}
}


/* camera_move_stick
changes the camera variables depending on controller input*/

void orbit_withStick(Camera *camera, NUContData *contdata)
{
    int deadzone = 8;
    float stick_x = 0;
    float stick_y = 0;

    if (fabs(contdata->stick_x) >= deadzone || fabs(contdata->stick_y) >= deadzone) {
        stick_x = contdata->stick_x;
        stick_y = contdata->stick_y;
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


void orbit_withCButtons(Camera *camera, NUContData *contdata)
{
    float input_x = 0;
    float input_y = 0;

    if ((contdata->button & R_CBUTTONS) || (contdata->button & L_CBUTTONS) || (contdata->button & U_CBUTTONS) || (contdata->button & D_CBUTTONS)){
        
        input_x = input(contdata->button & R_CBUTTONS) - input(contdata->button & L_CBUTTONS);
        input_y = input(contdata->button & U_CBUTTONS) - input(contdata->button & D_CBUTTONS);
    }

    if (input_x == 0) camera->orbitational_target_velocity.y = 0; 
    else camera->orbitational_target_velocity.y = input_x * camera->settings.orbitational_max_velocity.y;

	if (input_y == 0) camera->orbitational_target_velocity.x = 0; 
    else camera->orbitational_target_velocity.x = input_y * camera->settings.orbitational_max_velocity.x;

}


void aim(Camera *camera, NUContData *contdata)
{
    if (contdata->button & Z_TRIG) camera_setState (camera, AIMING);
    else camera_setState (camera, ORBITAL);
}


void cameraControl_setOrbitalMovement(Camera *camera, NUContData *contdata_0, NUContData *contdata_1)
{
    //orbit_withStick(camera, contdata_1);
    orbit_withCButtons(camera, contdata_0);
    aim(camera, contdata_0);
}

#endif