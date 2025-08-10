#ifndef ACTOR_H
#define ACTOR_H


// structures

typedef struct {

	rspq_block_t *dl;
	T3DModel *model;
	T3DMat4FP *t3d_matrix;
	char* model_address;
	Vector3 model_scale;
	
} ActorRenderData;

typedef struct {
 
	uint32_t id;
	
	ActorRenderData render_data;

} Actor;


// function prototypes

void actor_init(Actor *actor, T3DSkeleton* armature, const char* model_path);

void actor_draw(Actor* actor, RigidBody* body);


#endif