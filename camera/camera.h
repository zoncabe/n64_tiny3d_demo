#ifndef CAMERA_H
#define CAMERA_H

#include "light.h"


// structures

typedef enum {
    ORBITAL,
	AIMING,

} CameraState;

typedef struct {

	float orbitational_acceleration_rate;
	Vector2 orbitational_max_velocity;

	float zoom_acceleration_rate;
	float zoom_deceleration_rate;
	float zoom_max_speed;

	float target_zoom;
	float target_zoom_aim;

	float offset_acceleration_rate;
	float offset_deceleration_rate;
	float offset_max_speed;

	float target_offset;
	float target_offset_aim;
	
	float max_pitch;

} CameraSettings;


typedef struct {

	T3DViewport viewport;

	Vector3 position;
	float offset_height;
	
	float distance_from_barycenter; // the barycenter is choosen and it's the center of the orbitational movement
	float angle_around_barycenter;
	float pitch;

	float horizontal_barycenter_distance;
	float vertical_barycenter_distance;

	Vector3 target; // target as in the place at which the camera must aim
	float target_distance; 
	float horizontal_target_distance;
	float vertical_target_distance;

	Vector2 orbitational_acceleration;
	Vector2 orbitational_velocity;
	Vector2 orbitational_target_velocity; // target as in intended velocity

	float offset_angle;

	float offset_acceleration;
	float offset_speed;
	int offset_direction;

	float zoom_acceleration;
	float zoom_speed;
	int zoom_direction;

	CameraSettings settings;
	
} Camera;


// functions prototypes


Camera camera_create();
void camera_getOrbitalPosition(Camera *camera, Vector3 barycenter, float frame_time);
void camera_set(Camera *camera, Screen* screen);


// function implementations

Camera camera_create()
{
    Camera camera = {
        .distance_from_barycenter = 1700,
        .target_distance = 1700,
        .angle_around_barycenter = 180,
        .pitch = 20,
        .offset_angle = 6,
        .offset_height = 180,

        .settings = {
            .orbitational_acceleration_rate = 15,
            .orbitational_max_velocity = {120, 160},

            .zoom_acceleration_rate = 60,
            .zoom_deceleration_rate = 20,
            .zoom_max_speed = 3400,

            .target_zoom = 1700,
            .target_zoom_aim = 470,

            .offset_acceleration_rate = 25,
            .offset_deceleration_rate = 45,
            .offset_max_speed = 80,

            .target_offset = 6,
            .target_offset_aim = 30,

            .max_pitch = 80,
        },
    };

    return camera;
}

void camera_getOrbitalPosition(Camera *camera, Vector3 barycenter, float frame_time)
{
	camera->orbitational_velocity.x += camera->orbitational_acceleration.x * frame_time;
    camera->orbitational_velocity.y += camera->orbitational_acceleration.y * frame_time;
	camera->zoom_speed += camera->zoom_acceleration * frame_time;
	camera->offset_speed += camera->offset_acceleration * frame_time;

	if (fabs(camera->orbitational_velocity.x) < 1 && fabs(camera->orbitational_velocity.y) < 1 && fabs(camera->zoom_speed) < 1 && fabs(camera->offset_speed) < 1)
	{
		camera->orbitational_velocity.x = 0;
		camera->orbitational_velocity.y = 0;
		camera->zoom_speed = 0;
		camera->offset_speed = 0;

	}

    camera->pitch += camera->orbitational_velocity.x * frame_time;
	camera->angle_around_barycenter += camera->orbitational_velocity.y * frame_time;
	
	camera->distance_from_barycenter += camera->zoom_direction * camera->zoom_speed * frame_time;
	camera->offset_angle += camera->offset_direction * camera->offset_speed * frame_time;

	if (camera->angle_around_barycenter > 360) camera->angle_around_barycenter -= 360;
    if (camera->angle_around_barycenter < 0) camera->angle_around_barycenter  += 360;

    if (camera->pitch > camera->settings.max_pitch) camera->pitch = camera->settings.max_pitch;
    if (camera->pitch < -camera->settings.max_pitch) camera->pitch = -camera->settings.max_pitch;

    camera->horizontal_barycenter_distance = camera->distance_from_barycenter * cosf(rad(camera->pitch));
	camera->vertical_barycenter_distance = camera->distance_from_barycenter * sinf(rad(camera->pitch));

	camera-> horizontal_target_distance = camera->target_distance * cosf(rad(camera->pitch));
	camera->vertical_target_distance = camera->target_distance * sinf(rad(camera->pitch + 180));

    camera->position.x = barycenter.x - (camera->horizontal_barycenter_distance * sinf(rad(camera->angle_around_barycenter - camera->offset_angle)));
    camera->position.y = barycenter.y - (camera->horizontal_barycenter_distance * cosf(rad(camera->angle_around_barycenter - camera->offset_angle)));
    camera->position.z = barycenter.z + camera->offset_height + camera->vertical_barycenter_distance;
	
	camera->target.x = barycenter.x - camera-> horizontal_target_distance * sinf(rad(camera->angle_around_barycenter + 180));
	camera->target.y = barycenter.y - camera-> horizontal_target_distance * cosf(rad(camera->angle_around_barycenter + 180));
	camera->target.z = barycenter.z + camera->offset_height + camera->vertical_target_distance;
}


void camera_set(Camera *camera, Screen* screen)
{
    t3d_viewport_set_projection(
        &screen->viewport, 
        T3D_DEG_TO_RAD(45.0f), 
        100.0f, 
        10000.0f
    );

    t3d_viewport_look_at(
        &screen->viewport, 
        &(T3DVec3){{camera->position.x, camera->position.y, camera->position.z}}, 
        &(T3DVec3){{camera->target.x, camera->target.y, camera->target.z}}, 
        &(T3DVec3){{0, 0, 1}}
    );
}


#endif
