#ifndef SCENERY_H
#define SCENERY_H


#define SCENERY_COUNT 15


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

extern Scenery* scenery[SCENERY_COUNT];
    

// function prototypes

void scenery_init(Scenery* scenery);

void scenery_set(Scenery* scenery,
				 float scale_x, float scale_y, float scale_z,
				 float pos_x, float pos_y, float pos_z,
				 float rot_x, float rot_y, float rot_z);

void scenery_update(Scenery* scenery);

void scenery_draw(Scenery* scenery);

#endif