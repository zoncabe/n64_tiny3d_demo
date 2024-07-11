#ifndef LIGHT_H
#define LIGHT_H


typedef struct{

	uint8_t ambient_color[4];
	uint8_t directional_color[4];
	T3DVec3 direction;
	
} LightData;


void light_set(LightData *light);



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

#endif