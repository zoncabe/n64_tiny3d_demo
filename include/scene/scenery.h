#ifndef SCENERY_H
#define SCENERY_H


#define SCENERY_COUNT 4


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
extern float flag_transform;
    

// function prototypes

void scenery_init(Scenery* scenery);
void scenery_set(Scenery* scenery);

void animate_flag(T3DModel* model, float transformOffset);

#endif