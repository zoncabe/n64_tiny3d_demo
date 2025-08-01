#ifndef SHAPES_H
#define SHAPES_H

void shapes_drawSolidBox(
    float R, float G, float B, float A, 
    float pos_x, float pos_y, float size_x, float size_y
);

void shapes_drawGradientBox(
    float R0, float G0, float B0, float A0,
    float R1, float G1, float B1, float A1,
    float R2, float G2, float B2, float A2,
    float R3, float G3, float B3, float A3, 
    float pos_x, float pos_y, float size_x, float size_y
);


#endif