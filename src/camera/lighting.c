#include <stdint.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>

#include "../../include/camera/lighting.h"


LightData light_create() {
    LightData light = {
        .ambient_color = {80, 80, 100, 0xFF},
        .directional_color = {0xEE, 0xAA, 0xAA, 0xFF},
        .direction = {{1.0f, 1.0f, 1.0f}}
    };

    t3d_vec3_norm(&light.direction);

    return light;
}

/* set light
temporary function until i learn how the lights work  */
void light_set(LightData *light)
{
    t3d_light_set_ambient(light->ambient_color);
    t3d_light_set_directional(0, light->directional_color, &light->direction);
    t3d_light_set_count(1);
}
