#ifndef ACTOR_MOVEMENT_H
#define ACTOR_MOVEMENT_H


// function prototypes

void actor_setAcceleration (Actor *actor, float target_speed, float acceleration_rate);

void actor_setInertiaAcceleration (Actor *actor, float target_speed, float acceleration_rate);

void actor_setStopingAcceleration (Actor *actor);

void actor_setJumpAcceleration (Actor *actor, float target_speed, float acceleration_rate);

void actor_integrate (Actor *actor, float frame_time);



void actor_setAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->target_velocity.x = target_speed * sinf(rad(actor->target_yaw));
    actor->target_velocity.y = target_speed * -cosf(rad(actor->target_yaw));

    actor->body.acceleration.x = acceleration_rate * (actor->target_velocity.x - actor->body.velocity.x);
    actor->body.acceleration.y = acceleration_rate * (actor->target_velocity.y - actor->body.velocity.y);
}


void actor_setInertiaAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->target_velocity.x = target_speed * sinf(rad(actor->body.rotation.z));
    actor->target_velocity.y = target_speed * -cosf(rad(actor->body.rotation.z));

    actor->body.acceleration.x = acceleration_rate * (actor->target_velocity.x - actor->body.velocity.x);
    actor->body.acceleration.y = acceleration_rate * (actor->target_velocity.y - actor->body.velocity.y);
}


void actor_setStopingAcceleration (Actor *actor)
{
    actor->body.acceleration.x = actor->settings.idle_acceleration_rate * (0 - actor->body.velocity.x);
    actor->body.acceleration.y = actor->settings.idle_acceleration_rate * (0 - actor->body.velocity.y);
}


void actor_setJumpAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->body.acceleration.z = acceleration_rate * (target_speed - actor->body.velocity.z);
}


void actor_integrate (Actor *actor, float frame_time)
{

    if (actor->body.acceleration.x != 0 || actor->body.acceleration.y != 0 || actor->body.acceleration.z != 0){
        vector3_addScaledVector(&actor->body.velocity, &actor->body.acceleration, frame_time);
    }

	if (fabs(actor->body.velocity.x) < 10 && fabs(actor->body.velocity.y) < 10){
		actor->body.velocity.x = 0;
		actor->body.velocity.y = 0;
	}

    if (actor->body.velocity.x != 0 || actor->body.velocity.y != 0 || actor->body.velocity.z != 0) 
        vector3_addScaledVector(&actor->body.position, &actor->body.velocity, frame_time);

    if (actor->body.velocity.x != 0 || actor->body.velocity.y != 0) {

		actor->body.rotation.z = deg(atan2(-actor->body.velocity.x, -actor->body.velocity.y));

        Vector2 horizontal_velocity = {actor->body.velocity.x, actor->body.velocity.y};
        actor->horizontal_speed = vector2_magnitude(&horizontal_velocity);       
	}
}

#endif