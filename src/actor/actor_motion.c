#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_states.h"
#include "../../include/actor/actor_motion.h"


void actorMotion_setHorizontalAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->target_velocity.x = target_speed * sinf(rad(actor->target_yaw));
    actor->target_velocity.y = target_speed * -cosf(rad(actor->target_yaw));

    actor->body.acceleration.x = acceleration_rate * (actor->target_velocity.x - actor->body.velocity.x);
    actor->body.acceleration.y = acceleration_rate * (actor->target_velocity.y - actor->body.velocity.y);
}

void actorMotion_setHorizontalInertiaAcceleration(Actor *actor, float target_speed, float acceleration_rate)
{
    actor->target_velocity.x = target_speed * -sinf(rad(actor->body.rotation.z));
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

        Vector2 horizontal_velocity = {actor->body.velocity.x, actor->body.velocity.y};
        actor->horizontal_speed = vector2_magnitude(&horizontal_velocity);

        float target_yaw = deg(atan2(-actor->body.velocity.x, -actor->body.velocity.y));

        if (target_yaw > actor->body.rotation.z + 180) target_yaw -= 360;
        if (target_yaw < actor->body.rotation.z - 180) target_yaw += 360;
        
        
        if(actor->state == ROLLING) actor->body.rotation.z = deg(atan2(-actor->body.velocity.x, -actor->body.velocity.y));
        
        else if (target_yaw < actor->body.rotation.z - 1 || target_yaw > actor->body.rotation.z + 1) actor->body.rotation.z = lerpf(actor->body.rotation.z, target_yaw, actor->horizontal_speed / actor->settings.sprint_target_speed);
        else actor->body.rotation.z = target_yaw;

        if (actor->body.rotation.z > 180) actor->body.rotation.z -= 360;
        if (actor->body.rotation.z < -180) actor->body.rotation.z += 360;
	}
}

void actorMotion_setIdle(Actor *actor)
{
    actorMotion_setStopingAcceleration(actor);
    
    if  (fabs(actor->body.velocity.x) < 1 && fabs(actor->body.velocity.y) < 1){

        vector3_init(&actor->body.velocity);
        actor->horizontal_speed = 0;
    }
}

void actorMotion_setlocomotion(Actor *actor)
{
    switch (actor->state) {

        case WALKING: {

            actorMotion_setHorizontalAcceleration (actor, actor->horizontal_target_speed, actor->settings.walk_acceleration_rate);

            break;
        }
        case RUNNING: {

            actorMotion_setHorizontalAcceleration (actor, actor->horizontal_target_speed, actor->settings.run_acceleration_rate);

            break;
        }
        case SPRINTING: {
            
            actorMotion_setHorizontalAcceleration (actor, actor->horizontal_target_speed * 1.333333f, actor->settings.sprint_acceleration_rate);

            break;
        }
    }
}

void actorMotion_setWalking(Actor *actor)
{
    actorMotion_setHorizontalAcceleration (actor, actor->settings.walk_target_speed, actor->settings.walk_acceleration_rate);
}

void actorMotion_setRunning(Actor *actor)
{    
    actorMotion_setHorizontalAcceleration (actor, actor->settings.run_target_speed, actor->settings.run_acceleration_rate);
}

void actorMotion_setSprinting(Actor *actor)
{
    actorMotion_setHorizontalAcceleration (actor, actor->settings.sprint_target_speed, actor->settings.sprint_acceleration_rate);
}

void actorMotion_setRolling(Actor *actor, float frame_time)
{
    if (actor->input.roll_timer < actor->settings.roll_change_grip_time){

        actorMotion_setHorizontalInertiaAcceleration (actor, (actor->horizontal_speed), actor->settings.run_acceleration_rate);
        actor->input.roll_timer += frame_time;
    }

    else if (actor->input.roll_timer < actor->settings.roll_timer_max){ 
        
        actorMotion_setHorizontalAcceleration (actor, actor->horizontal_speed, actor->settings.roll_acceleration_grip_rate);
        actor->input.roll_timer += frame_time;
    }
    
    else {
        actor_setState(actor, actor->locomotion_state);
        actor->input.roll_timer = 0;
    }
}

void actorMotion_setJump(Actor *actor, float frame_time)
{
    actorMotion_setHorizontalAcceleration (actor, actor->horizontal_speed, actor->settings.aerial_control_rate);
    
    if (actor->input.jump_timer < actor->settings.jump_timer_max){
        
        actor->input.jump_timer += frame_time;
        
        if(actor->input.jump_hold){
            
            actor->input.jump_force += frame_time;
            vector3_scale(&actor->body.velocity, 0.96f);
        } 
    }
    
    else if (actor->input.jump_force > 0){
        
        actor->input.jump_timer += frame_time;

        actor->body.velocity = actor->input.jump_initial_velocity;
        vector3_scale(&actor->body.velocity, 0.8f);

        actor->body.velocity.z = actor->input.jump_force * actor->settings.jump_force_multiplier;
        if (actor->body.velocity.z < actor->settings.jump_minimum_speed) actor->body.velocity.z = actor->settings.jump_minimum_speed; 

        actor->input.jump_force = 0;
    }
    
    else if (actor->body.velocity.z > 0){

        actor->input.jump_timer += frame_time;
                
        actor->body.acceleration.z = ACTOR_GRAVITY;
    }
    
    else {
        
        actor->body.acceleration.z = ACTOR_GRAVITY;
        actor->input.jump_timer = 0;
        
        actor_setState(actor, FALLING);
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

        actor_setState(actor, actor->locomotion_state);

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
            //actorMotion_setlocomotion(actor);
            actorMotion_setWalking(actor);
            break;
        }
        case RUNNING: {
            //actorMotion_setlocomotion(actor);
            actorMotion_setRunning(actor);
            break;
        }
        case SPRINTING: {
            //actorMotion_setlocomotion(actor);
            actorMotion_setSprinting(actor);
            break;
        }
        case ROLLING: {
            actorMotion_setRolling(actor, frame_time);
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
