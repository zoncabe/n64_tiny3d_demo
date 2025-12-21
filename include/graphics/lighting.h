#ifndef LIGHT_H
#define LIGHT_H

#define POINT_LIGHT_COUNT 4

typedef struct{

	uint8_t ambient_color[4];
	uint8_t color[4];
	T3DVec3 direction;
	T3DVec3 size;
	
} DirectionalLight;

typedef struct {

	T3DVec3 position;
	uint8_t color[4];
	float  strength;

} PointLight;

extern DirectionalLight directional_light;
extern PointLight point_light[POINT_LIGHT_COUNT];

extern color_t lamp_color;

void directionalLight_init(DirectionalLight* light);
void directionalLight_set(DirectionalLight *light);
void pointLight_init(PointLight* light, Vector3 position, color_t color, float strength);
void pointLight_set(PointLight* light);

#endif
