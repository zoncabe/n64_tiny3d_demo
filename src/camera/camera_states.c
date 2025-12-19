#include <stdint.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>

#include "../../include/physics/physics.h"
#include "../../include/camera/camera.h"
#include "../../include/camera/camera_states.h"


// function implemetations

void camera_setState(Camera *camera, CameraState new_state) 
{
    switch(new_state) {

        case ORBITAL: {
            if (camera->state == ORBITAL) return;
            camera->state = ORBITAL;
            break;
        }

        case AIMING: {
            if (camera->state == AIMING) return;
            camera->state = AIMING;
            break;
        }
    }
}
