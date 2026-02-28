#include <libdragon.h>
#include "../../include/physics/physics.h"
#include "../../include/graphics/sprites.h"

void sprite_setMode()
{
    rdpq_set_mode_standard();
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_alphacompare(1);
}

void sprite_init(Sprite *sprites, int count)
{
    for (int i = 0; i < count; i++)
        sprites[i].image = sprite_load(sprites[i].path);
}

void sprite_draw(Sprite *sprites, int count)
{
    for (int i = 0; i < count; i++)
        rdpq_sprite_blit(sprites[i].image, sprites[i].position.x, sprites[i].position.y,
            &(rdpq_blitparms_t){ .scale_x = sprites[i].scale.x, .scale_y = sprites[i].scale.y, .theta = sprites[i].rotation });
}