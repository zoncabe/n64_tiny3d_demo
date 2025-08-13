#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"
#include "../../include/player/player.h"
#include "../../include/player/player_motion.h"


void playerMotion_setHorizontalAcceleration(Player* player, float target_speed, float acceleration_rate)
{
    player->motion_data.target_velocity.x = target_speed * sinf(rad(player->motion_data.target_yaw));
    player->motion_data.target_velocity.y = target_speed * -cosf(rad(player->motion_data.target_yaw));

    player->body.acceleration.x = acceleration_rate * (player->motion_data.target_velocity.x - player->body.velocity.x);
    player->body.acceleration.y = acceleration_rate * (player->motion_data.target_velocity.y - player->body.velocity.y);
}

void playerMotion_setHorizontalInertiaAcceleration(Player* player, float target_speed, float acceleration_rate)
{
    player->motion_data.target_velocity.x = target_speed * -sinf(rad(player->body.rotation.z));
    player->motion_data.target_velocity.y = target_speed * -cosf(rad(player->body.rotation.z));

    player->body.acceleration.x = acceleration_rate * (player->motion_data.target_velocity.x - player->body.velocity.x);
    player->body.acceleration.y = acceleration_rate * (player->motion_data.target_velocity.y - player->body.velocity.y);
}

void playerMotion_setStopingAcceleration (Player* player)
{
    player->body.acceleration.x = player->motion_settings.idle_acceleration_rate * (0 - player->body.velocity.x);
    player->body.acceleration.y = player->motion_settings.idle_acceleration_rate * (0 - player->body.velocity.y);
}

void playerMotiion_setJumpAcceleration(Player* player, float target_speed, float acceleration_rate)
{
    player->body.acceleration.z = acceleration_rate * (target_speed - player->body.velocity.z);
}

void playerMotion_integrate (Player* player)
{
    if (player->body.acceleration.x != 0 || player->body.acceleration.y != 0 || player->body.acceleration.z != 0){
        vector3_addScaledVector(&player->body.velocity, &player->body.acceleration, timer.delta);
    }

	if (fabs(player->body.velocity.x) < 5 && fabs(player->body.velocity.y) < 5 && fabs(player->body.velocity.z) == 0){
		player->body.velocity.x = 0;
		player->body.velocity.y = 0;
	}

    if (player->body.velocity.x != 0 || player->body.velocity.y != 0 || player->body.velocity.z != 0) 
        vector3_addScaledVector(&player->body.position, &player->body.velocity, timer.delta);

    if (player->body.velocity.x != 0 || player->body.velocity.y != 0) {

        Vector2 horizontal_velocity = {player->body.velocity.x, player->body.velocity.y};
        player->motion_data.horizontal_speed = vector2_magnitude(&horizontal_velocity);

        float target_yaw = deg(atan2(-player->body.velocity.x, -player->body.velocity.y));

        if (target_yaw > player->body.rotation.z + 180) target_yaw -= 360;
        if (target_yaw < player->body.rotation.z - 180) target_yaw += 360;
        
        
        if(player->state.current == ROLLING) player->body.rotation.z = deg(atan2(-player->body.velocity.x, -player->body.velocity.y));
        
        else if (target_yaw < player->body.rotation.z - 1 || target_yaw > player->body.rotation.z + 1) player->body.rotation.z = lerpf(player->body.rotation.z, target_yaw, player->motion_data.horizontal_speed / player->motion_settings.sprint_target_speed);
        else player->body.rotation.z = target_yaw;

        if (player->body.rotation.z > 180) player->body.rotation.z -= 360;
        if (player->body.rotation.z < -180) player->body.rotation.z += 360;
	}
}

void playerMotion_setIdle(Player* player)
{
    playerMotion_setStopingAcceleration(player);
    
    if  (fabs(player->body.velocity.x) < 1 && fabs(player->body.velocity.y) < 1){

        vector3_init(&player->body.velocity);
        player->motion_data.horizontal_speed = 0;
    }
}

void playerMotion_setlocomotion(Player* player)
{
    switch (player->state.current) {

        case WALKING: {

            playerMotion_setHorizontalAcceleration (player, player->motion_data.horizontal_target_speed, player->motion_settings.walk_acceleration_rate);

            break;
        }
        case RUNNING: {

            playerMotion_setHorizontalAcceleration (player, player->motion_data.horizontal_target_speed, player->motion_settings.run_acceleration_rate);

            break;
        }
        case SPRINTING: {
            
            playerMotion_setHorizontalAcceleration (player, player->motion_data.horizontal_target_speed * 1.333333f, player->motion_settings.sprint_acceleration_rate);

            break;
        }
    }
}

void playerMotion_setWalking(Player* player)
{
    playerMotion_setHorizontalAcceleration (player, player->motion_settings.walk_target_speed, player->motion_settings.walk_acceleration_rate);
}

void playerMotion_setRunning(Player* player)
{    
    playerMotion_setHorizontalAcceleration (player, player->motion_settings.run_target_speed, player->motion_settings.run_acceleration_rate);
}

void playerMotion_setSprinting(Player* player)
{
    playerMotion_setHorizontalAcceleration (player, player->motion_settings.sprint_target_speed, player->motion_settings.sprint_acceleration_rate);
}

void playerMotion_setRolling(Player* player)
{
    if (player->motion_data.roll_timer < player->motion_settings.roll_change_grip_time){

        playerMotion_setHorizontalInertiaAcceleration (player, (player->motion_data.horizontal_speed), player->motion_settings.run_acceleration_rate);
        player->motion_data.roll_timer += timer.delta;
    }

    else if (player->motion_data.roll_timer < player->motion_settings.roll_timer_max){ 
        
        playerMotion_setHorizontalAcceleration (player, player->motion_data.horizontal_speed, player->motion_settings.roll_acceleration_grip_rate);
        player->motion_data.roll_timer += timer.delta;
    }
    
    else {
        player_setState(player, player->state.locomotion);
        player->motion_data.roll_timer = 0;
    }
}

void playerMotion_setJump(Player* player)
{
    playerMotion_setHorizontalAcceleration (player, player->motion_data.horizontal_speed, player->motion_settings.aerial_control_rate);
    
    if (player->motion_data.jump_timer < player->motion_settings.jump_timer_max){
        
        player->motion_data.jump_timer += timer.delta;
        
        if(player->motion_input.jump_hold){
            
            player->motion_data.jump_force += timer.delta;
            vector3_scale(&player->body.velocity, 0.96f);
        } 
    }
    
    else if (player->motion_data.jump_force > 0){
        
        player->motion_data.jump_timer += timer.delta;

        player->body.velocity = player->motion_data.jump_initial_velocity;
        vector3_scale(&player->body.velocity, 0.8f);

        player->body.velocity.z = player->motion_data.jump_force * player->motion_settings.jump_force_multiplier;
        if (player->body.velocity.z < JUMP_MINIMUM_SPEED) player->body.velocity.z = JUMP_MINIMUM_SPEED;

        player->motion_data.jump_force = 0;
    }
    
    else if (player->body.velocity.z > 0){

        player->motion_data.jump_timer += timer.delta;
                
        player->body.acceleration.z = PLAYER_GRAVITY;
    }
    
    else {
        
        player->body.acceleration.z = PLAYER_GRAVITY;
        player->motion_data.jump_timer = 0;
        
        player_setState(player, FALLING);
        return;
    }
}

void playerMotion_setFalling(Player* player)
{
    player->motion_data.grounded = 0;
    playerMotion_setHorizontalAcceleration (player, player->motion_data.horizontal_speed, player->motion_settings.aerial_control_rate);
    player->body.acceleration.z = PLAYER_GRAVITY;

    if (player->body.velocity.z > FALL_MAX_SPEED) player->body.velocity.z = FALL_MAX_SPEED;

    if (player->body.position.z <= player->motion_data.grounding_height + 10) {

        player->motion_data.grounded = 1;
        player->body.acceleration.z = 0;
        player->body.velocity.z = 0;
        player->body.position.z = player->motion_data.grounding_height;

        player_setState(player, player->state.locomotion);

        return;
    }
}


void player_setMotion(Player *player)
{
   switch (player->state.current) {
    
        case STAND_IDLE: {
            playerMotion_setIdle(player);
            break;
        }
        case WALKING: {
            //playerMotion_setlocomotion(player);
            playerMotion_setWalking(player);
            break;
        }
        case RUNNING: {
            //playerMotion_setlocomotion(player);
            playerMotion_setRunning(player);
            break;
        }
        case SPRINTING: {
            //playerMotion_setlocomotion(player);
            playerMotion_setSprinting(player);
            break;
        }
        case ROLLING: {
            playerMotion_setRolling(player);
            break;
        }
        case JUMPING: {
            playerMotion_setJump(player);
            break;
        }
        case FALLING: {
            playerMotion_setFalling(player);
            break;
        }
    }

	playerMotion_integrate(player);
}
