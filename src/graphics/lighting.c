#include <stdint.h>
#include <libdragon.h>
#include <rspq_profile.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dmath.h>

#include "../../include/physics/physics.h"
#include "../../include/graphics/lighting.h"


Lights lights;


void light_initAmbient(color_t color)
{
    lights.ambient_color = color;
}

void light_initDirectional(DirectionalLight* light, T3DVec3 direction, color_t color) {

    light->direction = direction;
    light->color = color;
    t3d_vec3_norm(&light->direction);
}

void light_initPoint(PointLight* light, T3DVec3 position, color_t color, float strength) {

    light->position = position;
    light->color = color;
    light->strength = strength;
}

void light_setDirectional(Lights* lights)
{
    for (int i = 0; i < DIRECTIONAL_LIGHT_COUNT; i++){

        t3d_light_set_directional(i, &lights->directional[i].color.r, &lights->directional[i].direction);
    }
}

void light_setPoint(Lights* lights)
{
    for (int i = 0; i < POINT_LIGHT_COUNT; i++) {

        t3d_light_set_point(i, &lights->point[i].color.r, &lights->point[i].position, lights->point[i].strength, false);
    }
}

void light_set(Lights* lights)
{
    t3d_light_set_ambient(&lights->ambient_color.r);
    light_setDirectional(lights);
    light_setPoint(lights);
    t3d_light_set_count(DIRECTIONAL_LIGHT_COUNT + POINT_LIGHT_COUNT);
}
