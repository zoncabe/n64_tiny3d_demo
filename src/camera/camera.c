#include <t3d/t3d.h>

#include "../../include/physics/physics.h"
#include "../../include/graphics/lighting.h"
#include "../../include/camera/camera.h"


// function implementations

void camera_init(Camera* camera)
{
        camera->distance_from_barycenter = 200;
        camera->target_distance = 300;
        camera->angle_around_barycenter = 10;
        camera->pitch = 8;
        camera->offset_angle = 40;
        camera->offset_height = 140;
		camera->field_of_view = 60;
		camera->near_clipping = 100;
		camera->far_clipping = 5000;
		
        camera->settings.orbitational_acceleration_rate = 10;
        camera->settings.orbitational_max_velocity = (Vector2){150, 100};
        camera->settings.zoom_acceleration_rate = 30;
        camera->settings.zoom_deceleration_rate = 10;
        camera->settings.zoom_max_speed = 150;
        camera->settings.distance_from_baricenter = 200;
        camera->settings.field_of_view = 59;
	    camera->settings.field_of_view_aim = 50;
        camera->settings.offset_acceleration_rate = 25;
        camera->settings.offset_deceleration_rate = 45;
        camera->settings.offset_max_speed = 160;
        camera->settings.offset_angle = 40;
        camera->settings.offset_angle_aim = 30;
        camera->settings.max_pitch = 70;
}

void camera_updateOrbitalPosition(Camera *camera, Vector3* barycenter, float frame_time)
{
	camera->orbitational_velocity.x += camera->orbitational_acceleration.x * frame_time;
    camera->orbitational_velocity.y += camera->orbitational_acceleration.y * frame_time;
	camera->zoom_speed += camera->zoom_acceleration * frame_time;
	camera->offset_speed += camera->offset_acceleration * frame_time;

	if (fabs(camera->orbitational_velocity.x) < 1 && fabs(camera->orbitational_velocity.y) < 1 && fabs(camera->zoom_speed) < 1 && fabs(camera->offset_speed) < 1){
		camera->orbitational_velocity.x = 0;
		camera->orbitational_velocity.y = 0;
		camera->zoom_speed = 0;
		camera->offset_speed = 0;
	}

    camera->pitch += camera->orbitational_velocity.y * frame_time;
	camera->angle_around_barycenter += camera->orbitational_velocity.x * frame_time;
	
	camera->field_of_view += camera->zoom_direction * camera->zoom_speed * frame_time;
	camera->offset_angle += camera->offset_direction * camera->offset_speed * frame_time;

	if (camera->angle_around_barycenter > 360) camera->angle_around_barycenter -= 360;
    if (camera->angle_around_barycenter < 0) camera->angle_around_barycenter  += 360;

    if (camera->pitch > camera->settings.max_pitch) camera->pitch = camera->settings.max_pitch;
    if (camera->pitch < -camera->settings.max_pitch + 30) camera->pitch = -camera->settings.max_pitch + 30; // this hard coded + 20 is for the near plane to not enter the actor geometry during "camera collision"

    camera->horizontal_barycenter_distance = camera->distance_from_barycenter * cosf(rad(camera->pitch));
	camera->vertical_barycenter_distance = camera->distance_from_barycenter * sinf(rad(camera->pitch));

	camera-> horizontal_target_distance = camera->target_distance * cosf(rad(camera->pitch));
	camera->vertical_target_distance = camera->target_distance * sinf(rad(camera->pitch + 180));

    camera->position.x = barycenter->x - (camera->horizontal_barycenter_distance * sinf(rad(camera->angle_around_barycenter - camera->offset_angle)));
    camera->position.y = barycenter->y - (camera->horizontal_barycenter_distance * cosf(rad(camera->angle_around_barycenter - camera->offset_angle)));
    camera->position.z = barycenter->z + camera->offset_height + camera->vertical_barycenter_distance;
	
	/* this is a temporary brute force abomination to "collide" the camera with an horizontal plane at height 20 simulating the floor,
    will be modyfied when camera collision happens */
	/*
	*/
	camera->distance_from_barycenter = camera->settings.distance_from_baricenter;
	while (camera->position.z < 30)  {
		camera->distance_from_barycenter--; 
		camera->horizontal_barycenter_distance = camera->distance_from_barycenter * cosf(rad(camera->pitch));
		camera->vertical_barycenter_distance = camera->distance_from_barycenter * sinf(rad(camera->pitch));

		camera->position.x = barycenter->x - camera->horizontal_barycenter_distance * sinf(rad(camera->angle_around_barycenter - camera->offset_angle));
		camera->position.y = barycenter->y - camera->horizontal_barycenter_distance * cosf(rad(camera->angle_around_barycenter - camera->offset_angle));
		camera->position.z = barycenter->z + camera->offset_height + camera->vertical_barycenter_distance;
	}

	camera->target.x = barycenter->x - camera-> horizontal_target_distance * sinf(rad(camera->angle_around_barycenter + 180));
	camera->target.y = barycenter->y - camera-> horizontal_target_distance * cosf(rad(camera->angle_around_barycenter + 180));
	camera->target.z = barycenter->z + camera->offset_height + camera->vertical_target_distance;
}
