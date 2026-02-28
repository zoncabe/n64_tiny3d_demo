#include <libdragon.h>
#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/game/game.h"
#include "../../include/game/game_states.h"
#include "../../include/ui/menu.h"
#include "../../include/graphics/sprites.h"
#include "../../include/graphics/shapes.h"
#include "../../include/cutscene/intro.h"

#define INTRO_SPRITE_COUNT 4

Sprite intro_sprites[INTRO_SPRITE_COUNT] = {
	{ .path = "rom:/textures/n64logo.sprite",   .position = {0, 0}, .rotation = 0.0f, .scale = {1.0f, 1.0f} },
	{ .path = "rom:/textures/libdragon.sprite", .position = {0, 0}, .rotation = 0.0f, .scale = {1.0f, 1.0f} },
	{ .path = "rom:/textures/tiny3d.sprite",    .position = {0, 0}, .rotation = 0.0f, .scale = {1.0f, 1.0f} },
	{ .path = "rom:/textures/zoncabe.sprite",   .position = {0, 0}, .rotation = 0.0f, .scale = {1.0f, 1.0f} },
};

float intro_transitions[INTRO_SPRITE_COUNT + 1] = { 3.00f, 5.00f, 7.00f, 10.0f };

void intro_init()
{
	sprite_init(intro_sprites, INTRO_SPRITE_COUNT);
}

void intro_close()
{
}

void intro_draw()
{
	rdpq_sync_pipe();
	sprite_setMode();

	float t = game.timer.intro_counter;
	float start = 0.75f;

	for (int i = 0; i < INTRO_SPRITE_COUNT; i++) {
		float end = intro_transitions[i];

		if (t >= start && t < end) {
			sprite_draw(&intro_sprites[i], 1);

			float fade_progress = 0.0f;
			float local_t = t - start;
			float duration = end - start;

			if (local_t < 0.25f) {
				fade_progress = 1.0f - (local_t * 4.0f);
			}
			else if (local_t > (duration - (i == 3 ? 0.5f : 0.25f))) {
				float fade_speed = (i == 3) ? 2.0f : 4.0f;
				fade_progress = (t - (end - (1.0f / fade_speed))) * fade_speed;
			}

			if (fade_progress > 0.0f) {
				shapes_drawSolidBox(0.0f, 0.0f, 0.0f, fade_progress, 0.0f, 0.0f, 320.0f, 240.0f);
			}
		}

		start = end;
	}
}