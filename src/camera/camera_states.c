#include <stdint.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/graphics/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/graphics/viewport.h"
#include "../../include/camera/camera_states.h"


// function implemetations

void set_orbital(Camera *camera)
{
    if (camera->field_of_view < camera->settings.field_of_view) 
        camera->zoom_acceleration = camera->settings.zoom_acceleration_rate * (camera->settings.zoom_max_speed - camera->zoom_speed);
    
    else 
        camera->zoom_acceleration = (camera->settings.zoom_deceleration_rate + 10) * (0 - camera->zoom_speed);
    
    camera->zoom_direction = 1;
    
    if (camera->offset_angle > camera->settings.offset_angle) 
        camera->offset_acceleration = camera->settings.offset_acceleration_rate * (camera->settings.offset_max_speed  - camera->offset_speed);
    
    else camera->offset_acceleration = camera->settings.offset_deceleration_rate * (0 - camera->offset_speed);
    
    camera->offset_direction = -1;

    camera->orbitational_acceleration.x = camera->settings.orbitational_acceleration_rate * (camera->orbitational_target_velocity.x - camera->orbitational_velocity.x);
    camera->orbitational_acceleration.y = camera->settings.orbitational_acceleration_rate * (camera->orbitational_target_velocity.y - camera->orbitational_velocity.y);
}

// the set aiming not ready for it's prime yet :( 
void set_aiming(Camera *camera)
{
    if (camera->field_of_view > camera->settings.field_of_view_aim) 
        camera->zoom_acceleration = (camera->settings.zoom_acceleration_rate + 10) * (camera->settings.zoom_max_speed - camera->zoom_speed);
    
    else camera->zoom_acceleration = camera->settings.zoom_deceleration_rate * (0 - camera->zoom_speed);
    
    camera->zoom_direction = -1;

    if (camera->offset_angle < camera->settings.offset_angle_aim) 
        camera->offset_acceleration = camera->settings.offset_acceleration_rate * (camera->settings.offset_max_speed  - camera->offset_speed);
   
    else camera->offset_acceleration = camera->settings.offset_deceleration_rate * (0 - camera->offset_speed);

    camera->offset_direction = 1;

    camera->orbitational_acceleration.x = camera->settings.orbitational_acceleration_rate * ((camera->orbitational_target_velocity.x / 2) - camera->orbitational_velocity.x);
    camera->orbitational_acceleration.y = camera->settings.orbitational_acceleration_rate * ((camera->orbitational_target_velocity.y / 2) - camera->orbitational_velocity.y);
}

void camera_setState(Camera *camera, CameraState new_state) 
{
    switch(new_state) {

        case ORBITAL: {
            set_orbital(camera);
            break;
        }
        case AIMING: {
            set_aiming(camera);
            break;
        }
    }
}
