#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"

#include "../../include/player/player.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_motion.h"
#include "../../include/player/player_animation.h"

#include "../../include/physics/physics.h"
#include "../../include/scene/scenery.h"
#include "../../include/graphics/lighting.h"
#include "../../include/viewport/camera.h"
#include "../../include/viewport/viewport.h"

#include "../../include/scene/scenery.h"

#include "../../include/ui/ui.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"

#include "../../include/graphics/shapes.h"
#include "../../include/render/render.h"
#include "../../include/ui/menu.h"


void render_start()
{
	viewport_clear();	
}

void render_end()
{    
	rdpq_detach_show();
	timer.syncPoint = rspq_syncpoint_new();	
}

void render_mainMenu()
{
    rdpq_sync_pipe();

	shapes_drawGradientBox(

		0.788f, 0.475f, 0.098f, 1.0f,
		0.875f, 0.686f, 0.459f, 1.0f,
		0.875f, 0.686f, 0.459f, 1.0f,
		0.788f, 0.475f, 0.098f, 1.0f,

		0.0f,  0.0f,  320.0f,  240.0f
	);

	rdpq_set_mode_standard();
	rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_alphacompare(1);

	
	rdpq_sprite_blit(menu.sprite.still,  41, 27, &(rdpq_blitparms_t){.scale_x = 0.45f, .scale_y = 0.45f});
	rdpq_sprite_blit(menu.sprite.not_a, 100, 27, &(rdpq_blitparms_t){.scale_x = 0.45f, .scale_y = 0.45f});
	rdpq_sprite_blit(menu.sprite.game,   39, 55, &(rdpq_blitparms_t){.scale_x = 0.45f, .scale_y = 0.45f});

	if (menu.index == 0) {

		if (menu.sprite.play_scale < 0.34f) menu.sprite.play_scale += 0.01;
		rdpq_sprite_blit(menu.sprite.play, 45, 125, &(rdpq_blitparms_t){.scale_x = menu.sprite.play_scale, .scale_y = menu.sprite.play_scale,});	
	}
	else {
		if (menu.sprite.play_scale > 0.30f) menu.sprite.play_scale -= 0.015;
		rdpq_sprite_blit(menu.sprite.play, 45, 125, &(rdpq_blitparms_t){.scale_x = menu.sprite.play_scale, .scale_y = menu.sprite.play_scale,});	
	}

    if (menu.index == 1) {

		if (menu.sprite.options_scale < 0.34f) menu.sprite.options_scale += 0.01;
		rdpq_sprite_blit(menu.sprite.options, 45, 150, &(rdpq_blitparms_t){.scale_x = menu.sprite.options_scale, .scale_y = menu.sprite.options_scale});
	}
	else {

		if (menu.sprite.options_scale > 0.30f) menu.sprite.options_scale -= 0.015;
		rdpq_sprite_blit(menu.sprite.options, 45, 150, &(rdpq_blitparms_t){.scale_x = menu.sprite.options_scale, .scale_y = menu.sprite.options_scale});
	} 

    if (menu.index == 2) {

		if (menu.sprite.credits_scale < 0.34f) menu.sprite.credits_scale += 0.01;
		rdpq_sprite_blit(menu.sprite.credits, 45, 175, &(rdpq_blitparms_t){.scale_x = menu.sprite.credits_scale, .scale_y = menu.sprite.credits_scale});
	}
	else {

		if (menu.sprite.credits_scale > 0.30f) menu.sprite.credits_scale -= 0.015;
		rdpq_sprite_blit(menu.sprite.credits, 45, 175, &(rdpq_blitparms_t){.scale_x = menu.sprite.credits_scale, .scale_y = menu.sprite.credits_scale});
	}
	
	rdpq_sprite_blit(menu.sprite.dupbutton, 43, 217, &(rdpq_blitparms_t){.scale_x =   0.48f, .scale_y = 0.48f});
	rdpq_sprite_blit(menu.sprite.ddownbutton, 53, 217, &(rdpq_blitparms_t){.scale_x = 0.48f, .scale_y = 0.48f});
	rdpq_sprite_blit(menu.sprite.move, 65, 217, &(rdpq_blitparms_t){.scale_x = 0.32f, .scale_y = 0.32f});

	rdpq_sprite_blit(menu.sprite.abutton, 102, 216, &(rdpq_blitparms_t){.scale_x = 0.6f, .scale_y = 0.6f});
	rdpq_sprite_blit(menu.sprite.select, 115, 215, &(rdpq_blitparms_t){.scale_x = 0.32f, .scale_y = 0.32f});
	
	rdpq_sprite_blit(menu.sprite.gorilla, 170, 0, &(rdpq_blitparms_t){});
}

void render_gameplayScene(Player** player, Scenery** scenery)
{
	light_set(&light);

	t3d_matrix_push_pos(1);
    
	for (uint8_t i = 0; i < SCENERY_COUNT; i++) {
	
		scenery_draw(scenery[i]);
	};

    for (uint8_t i = 0; i < PLAYER_COUNT; i++) {
		
		actor_draw(&player[i]->actor, &player[i]->body);
	}

	t3d_matrix_pop(1);
}

void render_pauseMenu()
{
    rdpq_sync_pipe();

	shapes_drawGradientBox(

		0.0f, 0.0f, 0.0f, 0.3f * game.transition_timer,
		0.0f, 0.0f, 0.0f, game.transition_timer,
		0.0f, 0.0f, 0.0f, game.transition_timer,
		0.0f, 0.0f, 0.0f, 0.3f * game.transition_timer,

		0.0f,  0.0f,  320.0f,  240.0f
	);

    rdpq_set_mode_standard();
	rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_alphacompare(1);

	if (menu.index == 0) {

		if (menu.sprite.kontinue_scale < 0.33f) menu.sprite.kontinue_scale += 0.01;
		rdpq_sprite_blit(menu.sprite.kontinue, 320 - (92 * game.transition_timer), 40, &(rdpq_blitparms_t){.scale_x = menu.sprite.kontinue_scale, .scale_y = menu.sprite.kontinue_scale,});
    }
	else {
		if (menu.sprite.kontinue_scale > 0.30f) menu.sprite.kontinue_scale -= 0.015;
		rdpq_sprite_blit(menu.sprite.kontinue, 320 - (92 * game.transition_timer), 40, &(rdpq_blitparms_t){.scale_x = menu.sprite.kontinue_scale, .scale_y = menu.sprite.kontinue_scale,});	
	}

    if (menu.index == 1) {

		if (menu.sprite.options_scale < 0.33f) menu.sprite.options_scale += 0.01;
		rdpq_sprite_blit(menu.sprite.options, 320 - (83 * game.transition_timer), 70, &(rdpq_blitparms_t){.scale_x = menu.sprite.options_scale, .scale_y = menu.sprite.options_scale});
	}
	else {

		if (menu.sprite.options_scale > 0.30f) menu.sprite.options_scale -= 0.015;
		rdpq_sprite_blit(menu.sprite.options, 320 - (83 * game.transition_timer), 70, &(rdpq_blitparms_t){.scale_x = menu.sprite.options_scale, .scale_y = menu.sprite.options_scale});
	} 

    if (menu.index == 2) {

		if (menu.sprite.quit_scale < 0.33f) menu.sprite.quit_scale += 0.01;
		rdpq_sprite_blit(menu.sprite.quit, 320 - (57 * game.transition_timer), 100, &(rdpq_blitparms_t){.scale_x = menu.sprite.quit_scale, .scale_y = menu.sprite.quit_scale});
	}
	else {

		if (menu.sprite.quit_scale > 0.30f) menu.sprite.quit_scale -= 0.015;
		rdpq_sprite_blit(menu.sprite.quit, 320 - (57 * game.transition_timer), 100, &(rdpq_blitparms_t){.scale_x = menu.sprite.quit_scale, .scale_y = menu.sprite.quit_scale});
	}
	

	rdpq_sprite_blit(menu.sprite.dupbutton, 320 - (85 * game.transition_timer), 186, &(rdpq_blitparms_t){.scale_x =   0.48f, .scale_y = 0.48f});
	rdpq_sprite_blit(menu.sprite.ddownbutton, 330 - (85 * game.transition_timer), 187, &(rdpq_blitparms_t){.scale_x = 0.48f, .scale_y = 0.48f});
	rdpq_sprite_blit(menu.sprite.move, 347 - (85 * game.transition_timer), 187, &(rdpq_blitparms_t){.scale_x = 0.32f, .scale_y = 0.32f});

	rdpq_sprite_blit(menu.sprite.abutton, 320 - (76 * game.transition_timer), 201, &(rdpq_blitparms_t){.scale_x = 0.6f, .scale_y = 0.6f});
	rdpq_sprite_blit(menu.sprite.bbutton, 320 - (76 * game.transition_timer), 216, &(rdpq_blitparms_t){.scale_x = 0.6f, .scale_y = 0.6f});
	
	rdpq_sprite_blit(menu.sprite.select, 338 - (76 * game.transition_timer), 200, &(rdpq_blitparms_t){.scale_x = 0.32f, .scale_y = 0.32f});
	rdpq_sprite_blit(menu.sprite.back,   338 - (76 * game.transition_timer), 215, &(rdpq_blitparms_t){.scale_x = 0.32f, .scale_y = 0.32f});

	
}

void render_transition()
{	
    rdpq_sync_pipe();

	
	switch(game.state){

		case INTRO:{
			break;
		}
		case MAIN_MENU:{

			shapes_drawSolidBox(0, 0, 0, (255 * game.transition_timer), 0, 0, 320, 241);
			break;
		}
		case GAMEPLAY:{

			break;
		}
		case PAUSE:{
			break;
		}
		case GAME_OVER:{
			break;
		}
	}
}
void render()
{
	render_start();

	switch(game.state){

		case INTRO:{
			break;
		}
		case MAIN_MENU:{

			if (game.previous_state == INTRO && game.transition_timer > 0.0f) game.transition_timer -= 0.6 * timer.delta;
			else if (game.transition_timer < 0.0f) game.transition_timer = 0.0f;
			

			render_mainMenu();
			if (game.transition_timer > 0.0f) render_transition();

			ui_printDebugData();

			break;
		}
		case GAMEPLAY:{

			if (game.transition_timer > 0.0f) game.transition_timer -= 20 * timer.delta;
			else if (game.transition_timer < 0.0f) game.transition_timer = 0.0f;

			render_gameplayScene(player, scenery);

    		rdpq_sync_pipe();

			if (game.transition_timer > 0.0f && game.previous_state == PAUSE) render_pauseMenu();
			else if (game.transition_timer > 0.0f) render_transition();

			ui_printDebugData();

			break;
		}
		case PAUSE:{

			if (game.transition_timer < 1.0f) game.transition_timer += 20 * timer.delta;
			if (game.transition_timer > 1.0f) game.transition_timer = 1.0f;
			
			render_gameplayScene(player, scenery);

    		rdpq_sync_pipe();

			render_pauseMenu();

			ui_printDebugData();

			break;
		}
		case GAME_OVER:{
			break;
		}
	}

	render_end();
}