#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/ui/ui.h"
#include "../../include/ui/menu.h"
#include "../../include/player/player.h"
#include "../../include/light/lighting.h"
#include "../../include/graphics/font.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"
#include "../../include/scene/scenery.h"                                                             
#include "../../include/game/game.h"
#include "../../include/player/player.h"
#include "../../include/graphics/shapes.h"
#include "../../include/graphics/sprites.h"
#include "../../include/graphics/font.h"


void ui_init()
{
	fonts_init();
	textSprites_init();
	controllerSprites_init();
	titleSprites_init();
}

void ui_drawDebugData()
{
    rdpq_text_printf(NULL, DROID_SANS, 270, 20, "%d FPS", (int)(timer.rate));
}

void ui_drawMainMenu()
{
	shapes_drawGradientBox(

		0.788f, 0.475f, 0.098f, 1.0f,
		0.875f, 0.686f, 0.459f, 1.0f,
		0.875f, 0.686f, 0.459f, 1.0f,
		0.788f, 0.475f, 0.098f, 1.0f,

		0.0f,  0.0f,  320.0f,  240.0f
	);

	sprite_setMode();

    sprite_draw(text_sprites.not_a,  41, 18, 0.0f, 0.65f, 0.65f);
    sprite_draw(text_sprites.game,   39, 55, 0.0f, 0.45f, 0.45f);


    if (menu.index == 0) {
		if (text_sprites.play_scale < 0.34f) text_sprites.play_scale += 0.01;
		sprite_draw(text_sprites.play, 45, 125, 0.0f, text_sprites.play_scale, text_sprites.play_scale);
	} else {
		if (text_sprites.play_scale > 0.30f) text_sprites.play_scale -= 0.015;
		sprite_draw(text_sprites.play, 45, 125, 0.0f, text_sprites.play_scale, text_sprites.play_scale);
	}

    if (menu.index == 1) {
        if (text_sprites.options_scale < 0.34f) text_sprites.options_scale += 0.01;
        sprite_draw(text_sprites.options, 45, 150, 0.0f, text_sprites.options_scale, text_sprites.options_scale);
    } else {
        if (text_sprites.options_scale > 0.30f) text_sprites.options_scale -= 0.015;
        sprite_draw(text_sprites.options, 45, 150, 0.0f, text_sprites.options_scale, text_sprites.options_scale);
    }

    if (menu.index == 2) {
        if (text_sprites.credits_scale < 0.34f) text_sprites.credits_scale += 0.01;
        sprite_draw(text_sprites.credits, 45, 175, 0.0f, text_sprites.credits_scale, text_sprites.credits_scale);
    } else {
        if (text_sprites.credits_scale > 0.30f) text_sprites.credits_scale -= 0.015;
        sprite_draw(text_sprites.credits, 45, 175, 0.0f, text_sprites.credits_scale, text_sprites.credits_scale);
    }

    sprite_draw(text_sprites.move,        65, 217, 0.0f, 0.32f, 0.32f);
    sprite_draw(text_sprites.select, 115, 215, 0.0f, 0.32f, 0.32f);

    sprite_draw(controller_sprites.dupbutton,   43, 217, 0.0f, 0.48f, 0.48f);
    sprite_draw(controller_sprites.ddownbutton, 53, 217, 0.0f, 0.48f, 0.48f);
    sprite_draw(controller_sprites.abutton, 102, 216, 0.0f, 0.6f, 0.6f);

    sprite_draw(title_sprites.gorilla, 170, 0, 0.0f, 1.0f, 1.0f);
}

void ui_drawPauseMenu()
{
	shapes_drawGradientBox(

		0.0f, 0.0f, 0.0f, 0.3f * timer.transition_counter,
		0.0f, 0.0f, 0.0f, timer.transition_counter,
		0.0f, 0.0f, 0.0f, timer.transition_counter,
		0.0f, 0.0f, 0.0f, 0.3f * timer.transition_counter,

		0.0f,  0.0f,  320.0f,  240.0f
	);

	sprite_setMode();

	if (menu.index == 0) {

    if (text_sprites.kontinue_scale < 0.33f) text_sprites.kontinue_scale += 0.01;
    sprite_draw(text_sprites.kontinue, 320 - (92 * timer.transition_counter), 40, 0.0f, text_sprites.kontinue_scale, text_sprites.kontinue_scale);
	}
	else {
		if (text_sprites.kontinue_scale > 0.30f) text_sprites.kontinue_scale -= 0.015;
		sprite_draw(text_sprites.kontinue, 320 - (92 * timer.transition_counter), 40, 0.0f, text_sprites.kontinue_scale, text_sprites.kontinue_scale);
	}

	if (menu.index == 1) {
		if (text_sprites.options_scale < 0.33f) text_sprites.options_scale += 0.01;
		sprite_draw(text_sprites.options, 320 - (83 * timer.transition_counter), 70, 0.0f, text_sprites.options_scale, text_sprites.options_scale);
	}
	else {
		if (text_sprites.options_scale > 0.30f) text_sprites.options_scale -= 0.015;
		sprite_draw(text_sprites.options, 320 - (83 * timer.transition_counter), 70, 0.0f, text_sprites.options_scale, text_sprites.options_scale);
	}

	if (menu.index == 2) {
		if (text_sprites.quit_scale < 0.33f) text_sprites.quit_scale += 0.01;
		sprite_draw(text_sprites.quit, 320 - (57 * timer.transition_counter), 100, 0.0f, text_sprites.quit_scale, text_sprites.quit_scale);
	}
	else {
		if (text_sprites.quit_scale > 0.30f) text_sprites.quit_scale -= 0.015;
		sprite_draw(text_sprites.quit, 320 - (57 * timer.transition_counter), 100, 0.0f, text_sprites.quit_scale, text_sprites.quit_scale);
	}

	sprite_draw(text_sprites.move,        347 - (85 * timer.transition_counter), 187, 0.0f, 0.32f, 0.32f);
	sprite_draw(text_sprites.select, 338 - (76 * timer.transition_counter), 200, 0.0f, 0.32f, 0.32f);
	sprite_draw(text_sprites.back,   338 - (76 * timer.transition_counter), 215, 0.0f, 0.32f, 0.32f);

	sprite_draw(controller_sprites.dupbutton,   320 - (85 * timer.transition_counter), 186, 0.0f, 0.48f, 0.48f);
	sprite_draw(controller_sprites.ddownbutton, 330 - (85 * timer.transition_counter), 187, 0.0f, 0.48f, 0.48f);
	sprite_draw(controller_sprites.abutton, 320 - (76 * timer.transition_counter), 201, 0.0f, 0.6f, 0.6f);
	sprite_draw(controller_sprites.bbutton, 320 - (76 * timer.transition_counter), 216, 0.0f, 0.6f, 0.6f);
}
