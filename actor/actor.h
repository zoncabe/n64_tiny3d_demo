#ifndef ACTOR_H
#define ACTOR_H

/* ACTOR.H
here are all the structures and functions prototypes that involve the setting up of an actor */


// structures

typedef enum {

	EMPTY,
    STAND_IDLE,
    WALKING,
    RUNNING,
	SPRINTING,
	ROLL,
	JUMP,
	FALLING,

} ActorState;


typedef struct {

	float idle_acceleration_rate;
	float walk_acceleration_rate;
	float run_acceleration_rate;
	float roll_acceleration_rate;
	float roll_acceleration_grip_rate;
	float jump_acceleration_rate;
	float aerial_control_rate;

	float walk_target_speed;
	float run_target_speed;
	float sprint_target_speed;
	float idle_to_roll_target_speed;
	float idle_to_roll_grip_target_speed;
	float walk_to_roll_target_speed;
	float run_to_roll_target_speed;
	float sprint_to_roll_target_speed;
	float jump_target_speed;
	
	float jump_timer_max;

}ActorSettings;


typedef struct {

	float stick_magnitude;
	float stick_x;
	float stick_y;
	float time_held;
	int hold;
	int released;

}Actorinput;


typedef struct {

	uint32_t id;
	
	Vector3 scale;
	RigidBody body;
	
	Vector3 target_rotation;
	Vector3 target_velocity;

	float horizontal_speed;

	bool grounded;
	float grounding_height;

	ActorState previous_state;
	ActorState state;

	ActorSettings settings;
	Actorinput input;


	rspq_block_t *dl;
	T3DMat4FP *modelMat;
	T3DModel *model;

} Actor;


Actor actor_create(uint32_t id);
void actor_update(Actor *actor);
void actor_draw(Actor *actor);
void actor_delete(Actor *actor);
void actor_animate(Actor *actor);



Actor actor_create(uint32_t id)
{
    Actor actor = {
        .id = id,
        .scale = {1.0f, 1.0f, 1.0f},
        .grounding_height = 0,
        .body = {
            .position = {0, 0, 0},
            .velocity = {0, 0, 0},
            .rotation = {0, 0, 0},
        },
        .settings = {
            .idle_acceleration_rate = 9,
            .walk_acceleration_rate = 4,
            .run_acceleration_rate = 6,
            .roll_acceleration_rate = 20,
            .roll_acceleration_grip_rate = 2,
            .jump_acceleration_rate = 50,
            .aerial_control_rate = 0.5,
            .walk_target_speed = 350,
            .run_target_speed = 700,
            .sprint_target_speed = 900,
            .idle_to_roll_target_speed = 300,
            .idle_to_roll_grip_target_speed = 50,
            .walk_to_roll_target_speed = 400,
            .run_to_roll_target_speed = 780,
            .sprint_to_roll_target_speed = 980,
            .jump_target_speed = 550,
            .jump_timer_max = 0.20,
        },
        .modelMat = malloc_uncached(sizeof(T3DMat4FP)) // needed for t3d
    };

    t3d_mat4fp_identity(actor.modelMat);

    return actor;
}



void actor_update(Actor *actor)
{	
	t3d_mat4fp_from_srt_euler(actor->modelMat,
		(float[3]){actor->scale.x, actor->scale.y, actor->scale.z},
		(float[3]){rad(actor->body.rotation.x), rad(actor->body.rotation.y), rad(actor->body.rotation.z)},
		(float[3]){actor->body.position.x, actor->body.position.y, actor->body.position.z}
	);
}


void actor_draw(Actor *actor) 
{
	t3d_matrix_set(actor->modelMat, true);
	rspq_block_run(actor->dl);
}


void actor_delete(Actor *actor) 
{
	free_uncached(actor->modelMat);
}

void actor_animate(Actor *actor)
{
	if (actor->horizontal_speed > 1) actor->body.rotation.x = actor->horizontal_speed * 0.01f;
	else actor->body.rotation.x = 0;
}


#endif