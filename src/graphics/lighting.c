#include <stdint.h>
#include <libdragon.h>
#include <rspq_profile.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dmath.h>

#include "../../include/physics/physics.h"
#include "../../include/graphics/lighting.h"


DirectionalLight directional_light;
PointLight point_light[POINT_LIGHT_COUNT];

color_t lamp_color = {250, 250, 230, 0xFF};

void directionalLight_init(DirectionalLight* light) {

    light->ambient_color[0] = 60;
    light->ambient_color[1] = 60;
    light->ambient_color[2] = 60;
    light->ambient_color[3] = 0xFF;

    light->color[0] = 255;
    light->color[1] = 255;
    light->color[2] = 255;
    light->color[3] = 0xFF;

    light->direction = (T3DVec3){{1.0f, -1.0f, 1.0f}};
    t3d_vec3_norm(&light->direction);
}

void directionalLight_set(DirectionalLight* light)
{
    t3d_light_set_directional(0, light->color, &light->direction);
    t3d_light_set_ambient(light->ambient_color);
    t3d_light_set_count(1);
}

void pointLight_init(PointLight* light, Vector3 position, color_t color, float strength) {

    light->position = (T3DVec3){{position.x, position.y, position.z}};
    light->color[0] = color.r;
    light->color[1] = color.g;
    light->color[2] = color.b;
    light->color[3] = color.a;
    light->strength = strength;
}

void pointLight_set(PointLight* light)
{
    t3d_light_set_count(POINT_LIGHT_COUNT);
    t3d_light_set_ambient((uint8_t[]){20, 20, 30, 0xFF});
    for (int i = 0; i < POINT_LIGHT_COUNT; i++) {

        t3d_light_set_point(i,
            light[i].color,
            &light[i].position,
            light[i].strength,
            false
        );
    }
}
