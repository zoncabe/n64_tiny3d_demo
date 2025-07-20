#ifndef LIGHT_H
#define LIGHT_H


typedef struct{

	uint8_t ambient_color[4];
	uint8_t directional_color[4];
	T3DVec3 direction;
	
} LightData;


LightData light_create();
void light_set(LightData *light);


#endif
