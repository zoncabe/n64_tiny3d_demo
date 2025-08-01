#include <stdint.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>

#include "../../include/graphics/lighting.h"


LightData light;


void light_init(LightData* light) {

    light->ambient_color[0] = 60;
    light->ambient_color[1] = 60;
    light->ambient_color[2] = 60;
    light->ambient_color[3] = 0xFF;

    light->directional_color[0] = 255;
    light->directional_color[1] = 255;
    light->directional_color[2] = 255;
    light->directional_color[3] = 0xFF;

    light->direction = (T3DVec3){{1.0f, -1.0f, 1.0f}};
    t3d_vec3_norm(&light->direction);
}

/* set light
temporary function until i learn how the lights work  */
void light_set(LightData* light)
{
    t3d_light_set_ambient(light->ambient_color);
    t3d_light_set_directional(0, light->directional_color, &light->direction);
    t3d_light_set_count(1);
}
