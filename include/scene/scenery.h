#ifndef SCENERY_H
#define SCENERY_H


#define SCENERY_COUNT 2


// structures

typedef struct {

  	uint32_t id;

	rspq_block_t *dl;
	T3DModel *model;
	T3DMat4FP *t3d_matrix;
    
	Vector3 scale;
	Vector3 position;
	Vector3 rotation;

} Scenery;


// function prototypes

void scenery_init(Scenery* scenery);
void scenery_set(Scenery *scenery);
void scenery_draw(Scenery *scenery);


#endif