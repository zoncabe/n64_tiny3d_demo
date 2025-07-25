#ifndef LIGHT_H
#define LIGHT_H


typedef struct{

	uint8_t ambient_color[4];
	uint8_t directional_color[4];
	T3DVec3 direction;
	T3DVec3 size;
	
} LightData;

extern LightData light;

void light_init(LightData* light);
void light_set(LightData *light);


#endif
