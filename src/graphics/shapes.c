#include <libdragon.h>
#include "../../include/graphics/shapes.h"


void shapes_drawSquare(float R, float G, float B, float A, float pos_x, float pos_y, float size_x, float size_y)
{
    rdpq_set_prim_color(RGBA32(R, G, B, A));
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_fill_rectangle(pos_x, pos_y, size_x, size_y);
}