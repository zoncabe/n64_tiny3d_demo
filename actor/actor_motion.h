#ifndef ACTOR_MOVEMENT_H
#define ACTOR_MOVEMENT_H


#define ACTOR_GRAVITY -1000


// function prototypes

void actorMotion_setHorizontalAcceleration (Actor *actor, float target_speed, float acceleration_rate);

void actorMotion_setHorizontalInertiaAcceleration (Actor *actor, float target_speed, float acceleration_rate);

void actorMotion_setStopingAcceleration (Actor *actor);

void actorMotiion_setJumpAcceleration (Actor *actor, float target_speed, float acceleration_rate);

void actorMotion_integrate (Actor *actor, float frame_time);


void actorMotion_setHorizontalAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->target_velocity.x = target_speed * sinf(rad(actor->target_yaw));
    actor->target_velocity.y = target_speed * -cosf(rad(actor->target_yaw));

    actor->body.acceleration.x = acceleration_rate * (actor->target_velocity.x - actor->body.velocity.x);
    actor->body.acceleration.y = acceleration_rate * (actor->target_velocity.y - actor->body.velocity.y);
}

void actorMotion_setHorizontalInertiaAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->target_velocity.x = target_speed * sinf(rad(actor->body.rotation.z));
    actor->target_velocity.y = target_speed * -cosf(rad(actor->body.rotation.z));

    actor->body.acceleration.x = acceleration_rate * (actor->target_velocity.x - actor->body.velocity.x);
    actor->body.acceleration.y = acceleration_rate * (actor->target_velocity.y - actor->body.velocity.y);
}

void actorMotion_setStopingAcceleration (Actor *actor)
{
    actor->body.acceleration.x = actor->settings.idle_acceleration_rate * (0 - actor->body.velocity.x);
    actor->body.acceleration.y = actor->settings.idle_acceleration_rate * (0 - actor->body.velocity.y);
}

void actorMotiion_setJumpAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->body.acceleration.z = acceleration_rate * (target_speed - actor->body.velocity.z);
}

void actorMotion_integrate (Actor *actor, float frame_time)
{

    if (actor->body.acceleration.x != 0 || actor->body.acceleration.y != 0 || actor->body.acceleration.z != 0){
        vector3_addScaledVector(&actor->body.velocity, &actor->body.acceleration, frame_time);
    }

	if (fabs(actor->body.velocity.x) < 5 && fabs(actor->body.velocity.y) < 5 && fabs(actor->body.velocity.z) == 0){
		actor->body.velocity.x = 0;
		actor->body.velocity.y = 0;
	}

    if (actor->body.velocity.x != 0 || actor->body.velocity.y != 0 || actor->body.velocity.z != 0) 
        vector3_addScaledVector(&actor->body.position, &actor->body.velocity, frame_time);

    if (actor->body.velocity.x != 0 || actor->body.velocity.y != 0) {

        float target_yaw = deg(atan2(-actor->body.velocity.x, -actor->body.velocity.y));

        if (actor->body.rotation.z > 180) actor->body.rotation.z -= 360;
        if (actor->body.rotation.z < -180) actor->body.rotation.z += 360;

        if (target_yaw > actor->body.rotation.z + 180) target_yaw -= 360;
        if (target_yaw < actor->body.rotation.z - 180) target_yaw += 360;
        
        if (target_yaw < actor->body.rotation.z - 1 || target_yaw > actor->body.rotation.z + 1) 
            actor->body.rotation.z = lerpf(actor->body.rotation.z, target_yaw, 0.25f);
        else 
            actor->body.rotation.z = target_yaw;

        Vector2 horizontal_velocity = {actor->body.velocity.x, actor->body.velocity.y};
        actor->horizontal_speed = vector2_magnitude(&horizontal_velocity);       
	}
}

void actorMotion_setIdle(Actor *actor)
{
    actorMotion_setStopingAcceleration(actor);
    
    if  (fabs(actor->body.velocity.x) < 1 && fabs(actor->body.velocity.y) < 1){

        vector3_init(&actor->body.velocity);
        actor->horizontal_speed = 0;    
        actor->target_yaw = actor->body.rotation.z;
    }
}

void actorMotion_setWalking(Actor *actor)
{
    //actorMotion_setHorizontalAcceleration (actor, actor->horizontal_target_speed, actor->settings.walk_acceleration_rate);
    actorMotion_setHorizontalAcceleration (actor, actor->settings.walk_target_speed, actor->settings.walk_acceleration_rate);
}

void actorMotion_setRunning(Actor *actor)
{    
    //actorMotion_setHorizontalAcceleration (actor, actor->horizontal_target_speed, actor->settings.run_acceleration_rate);
    actorMotion_setHorizontalAcceleration (actor, actor->settings.run_target_speed, actor->settings.run_acceleration_rate);
}

void actorMotion_setSprinting(Actor *actor)
{
    //actorMotion_setHorizontalAcceleration (actor, actor->horizontal_target_speed * 1.15f, actor->settings.run_acceleration_rate);
    actorMotion_setHorizontalAcceleration (actor, actor->settings.sprint_target_speed, actor->settings.sprint_acceleration_rate);
}

void actorMotion_setJump(Actor *actor, float frame_time)
{
          
    if (actor->input.jump_hold && actor->input.jump_timer < actor->settings.jump_timer_max){

        //actorMotiion_setJumpAcceleration (actor, actor->settings.jump_max_speed, actor->settings.jump_acceleration_rate);
        actorMotion_setHorizontalAcceleration (actor, actor->horizontal_speed, actor->settings.aerial_control_rate);

        actor->input.jump_timer += frame_time;
        actor->input.jump_force = actor->input.jump_timer;
    } 
    

    else if (actor->input.jump_force > 0){
        
        actorMotion_setHorizontalAcceleration (actor, actor->horizontal_speed, actor->settings.aerial_control_rate);
        actor->body.velocity.z = actor->input.jump_force * 2000;
        if (actor->body.velocity.z < 200) actor->body.velocity.z = 200;
        actor->input.jump_force = 0;
    }
    
    else if (actor->body.velocity.z > 0){
        
        actorMotion_setHorizontalAcceleration (actor, actor->horizontal_speed, actor->settings.aerial_control_rate);
        actor->body.acceleration.z = ACTOR_GRAVITY;
    }
    
    else {
        
        actorMotion_setHorizontalAcceleration (actor, actor->horizontal_speed, actor->settings.aerial_control_rate);
        actor->body.acceleration.z = ACTOR_GRAVITY;
        actor->input.jump_timer = 0;
        
        actor->state = FALLING;
        return;
    }
}

void actorMotion_setFalling(Actor *actor)
{
    actor->grounded = 0;
    actorMotion_setHorizontalAcceleration (actor, actor->horizontal_speed, actor->settings.aerial_control_rate);
    actor->body.acceleration.z = ACTOR_GRAVITY;

    if (actor->body.position.z <= actor->grounding_height) {

        actor->grounded = 1;
        actor->body.acceleration.z = 0;
        actor->body.velocity.z = 0;
        actor->body.position.z = actor->grounding_height;

        actor->state = actor->locomotion_state;

        return;
    }
}

void actor_setMotion(Actor *actor, float frame_time)
{
   switch (actor->state) {
    
        case STAND_IDLE: {
            actorMotion_setIdle(actor);
            break;
        }
        case WALKING: {
            actorMotion_setWalking(actor);
            break;
        }
        case RUNNING: {
            actorMotion_setRunning(actor);
            break;
        }
        case SPRINTING: {
            actorMotion_setSprinting(actor);
            break;
        }
        case JUMPING: {
            actorMotion_setJump(actor, frame_time);
            break;
        }
        case FALLING: {
            actorMotion_setFalling(actor);
            break;
        }
    }

	actorMotion_integrate(actor, frame_time);
}

#endif