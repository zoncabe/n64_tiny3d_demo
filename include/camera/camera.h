#ifndef CAMERA_H
#define CAMERA_H


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

	float distance_from_baricenter;
	
    float field_of_view;
	float field_of_view_aim;

	float offset_acceleration_rate;
	float offset_deceleration_rate;
	float offset_max_speed;

	float offset_angle;
	float offset_angle_aim;
	
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

	float field_of_view;
	
	float zoom_acceleration;
	float zoom_speed;
	int zoom_direction;

	float near_clipping;
	float far_clipping;

	CameraSettings settings;
} Camera;


// functions prototypes


void camera_init(Camera* camera);
void camera_updateOrbitalPosition(Camera *camera, Vector3* barycenter, float frame_time);


#endif
