#include <libdragon.h>
#include "../../include/graphics/shapes.h"


void shapes_drawSolidBox(
    float R, float G, float B, float A, 
    float pos_x, float pos_y, float size_x, float size_y)
{
    rdpq_set_prim_color(RGBA32(R, G, B, A));
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    //rdpq_mode_dithering(DITHER_NOISE_NOISE);
    rdpq_fill_rectangle(pos_x, pos_y, size_x, size_y);
}

void shapes_drawGradientBox(
    float R0, float G0, float B0, float A0,
    float R1, float G1, float B1, float A1,
    float R2, float G2, float B2, float A2,
    float R3, float G3, float B3, float A3, 
    float pos_x, float pos_y, 
    float size_x, float size_y)
{
    rdpq_set_mode_standard();
    rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_dithering(DITHER_NOISE_NOISE);

    float vtx[4][6] = {
        
        { pos_x, pos_y,                    R0, G0, B0, A0 },
        { pos_x + size_x, pos_y,           R1, G1, B1, A1 },
        { pos_x + size_x, pos_y + size_y,  R2, G2, B2, A2 },
        { pos_x, pos_y + size_y,           R3, G3, B3, A3 },
    };

    rdpq_triangle(&TRIFMT_SHADE, vtx[0], vtx[1], vtx[2]);
    rdpq_triangle(&TRIFMT_SHADE, vtx[0], vtx[2], vtx[3]);
}