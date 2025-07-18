#ifndef SCENERY_H
#define SCENERY_H

#include <t3d/t3dmodel.h>
#include "../../include/physics/math/vector3.h"

#define SCENERY_COUNT 2


// structures

typedef struct {

  	uint32_t id;

	rspq_block_t *dl;
	T3DModel *model;
	T3DMat4FP *matrix;
    
	Vector3 scale;
	Vector3 position;
	Vector3 rotation;

} Scenery;


// function prototypes

Scenery scenery_create(uint32_t id, const char *model_path);
void scenery_init(Scenery* scenery, uint32_t id, const char *model_path);
void scenery_set(Scenery *scenery);
void scenery_draw(Scenery *scenery);
void scenery_delete(Scenery *scenery);


#endif