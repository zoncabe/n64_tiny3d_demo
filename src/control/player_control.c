#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_states.h"
#include "../../include/actor/actor_motion.h"
#include "../../include/actor/actor_animation.h"

#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/graphics/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/graphics/viewport.h"
#include "../../include/time/time.h"
#include "../../include/scene/scenery.h"
#include "../../include/ui/ui.h"
#include "../../include/player/player.h"
#include "../../include/control/player_control.h"
#include "../../include/game/game.h"
#include "../../include/control/camera_control.h"
#include "../../include/physics/actor_collision/actor_collision_detection.h"
#include "../../include/physics/actor_collision/actor_collision_response.h"

#include "../../include/game/game_states.h"
#include "../../include/graphics/render.h"

#include "../../include/game/intro.h"


// function implementations

void playerControl_setJump(Player* player)
{    
    if (player->control.pressed.a && player->actor->state != ROLLING && player->actor->state != JUMPING && player->actor->state != FALLING){
        
        player->actor->input.jump_hold = true;
        player->actor->input.jump_initial_velocity = player->actor->body.velocity;
        actor_setState(player->actor, JUMPING);
    }
    
    else if (player->control.held.a) return;
    
    else player->actor->input.jump_hold = false;
}

void playerControl_setRoll(Player* player)
{
    if (player->control.pressed.b 
        && player->actor->state != ROLLING
        && player->actor->state != STAND_IDLE
        && player->actor->state != WALKING
        && player->actor->state != JUMPING
        && player->actor->state != FALLING){

        actor_setState(player->actor, ROLLING);
    }
}

void playerControl_moveWithStick(Player* player, float camera_angle_around, float camera_offset_angle)
{
    int deadzone = 6;
    float stick_magnitude = 0; 

    if (fabs(player->control.input.stick_x) >= deadzone || fabs(player->control.input.stick_y) >= deadzone) {

        Vector2 stick = {player->control.input.stick_x, player->control.input.stick_y};
        
        stick_magnitude = vector2_magnitude(&stick);
        player->actor->target_yaw = deg(atan2(player->control.input.stick_x, -player->control.input.stick_y) - rad(camera_angle_around - (0.5 * camera_offset_angle)));

        player->actor->horizontal_target_speed = stick_magnitude * 5;
    }

    
    if (stick_magnitude == 0 && player->actor->state != ROLLING && player->actor->state != JUMPING && player->actor->state != FALLING){
        actor_setState(player->actor, STAND_IDLE);
    }

    else if (stick_magnitude > 0 && stick_magnitude <= 65 && player->actor->state != ROLLING && player->actor->state != JUMPING && player->actor->state != FALLING){
        actor_setState(player->actor, WALKING);
    }

    else if (player->control.held.r && stick_magnitude > 65 && player->actor->state != ROLLING && player->actor->state != JUMPING && player->actor->state != FALLING){
        actor_setState(player->actor, SPRINTING);
    }

    else if (stick_magnitude > 65 && player->actor->state != ROLLING && player->actor->state != JUMPING && player->actor->state != FALLING){
        actor_setState(player->actor, RUNNING);
    }
}

void player_setActorControl(Player* player)
{
    playerControl_setRoll(player);
    playerControl_setJump(player);
    playerControl_moveWithStick(player, viewport.camera.angle_around_barycenter, viewport.camera.offset_angle);
}


void playerControl_skipIntro(Player* player)
{
    if (player->control.pressed.start) {

        if (game.state == INTRO) gameState_set(GAMEPLAY);
    }
}

void playerControl_handleMainMenu(Player* player)
{
}

void playerControl_setPause(Player* player)
{
    if (player->control.pressed.start) {

        if (game.state == PAUSE) gameState_set(GAMEPLAY);
        else if (game.state == GAMEPLAY) gameState_set(PAUSE);
    }
}

void playerControl_handlePauseMenu(Player* player)
{
}

void playerControl_handleGameOverMenu(Player* player)
{
}

void playerControl_setGameState(Player* player)
{
    //playerControl_skipIntro(&player[i]);
    //playerControl_handleMainMenu(&player[i]);
    playerControl_setPause(player);
    //playerControl_handlePauseMenu(&player[i]);
    //playerControl_handleGameOverMenu(&player[i]);
}


void player_setControllerData()
{
    joypad_poll();
    
    for (int i = 0; i < PLAYER_COUNT; i++) {
        
        controllerData_getInputs(&player[i].control, i);
        playerControl_setGameState(&player[i]);
    } 
}