#ifndef SCENERY_H
#define SCENERY_H


// structures

typedef struct {

  	uint32_t id;

	rspq_block_t *dl;
	T3DModel *model;
	T3DMat4FP *modelMat;
    
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


//function implementations

Scenery scenery_create(uint32_t id, const char *model_path)
{
    Scenery scenery = {
        .id = id,
        .model = t3d_model_load(model_path),
        .modelMat = malloc_uncached(sizeof(T3DMat4FP)), // needed for t3d

        .scale = {1.0f, 1.0f, 1.0f},
        .position = {0.0f, 0.0f, 0.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
    };

    t3d_matrix_set(scenery.modelMat, true);
    t3d_mat4fp_identity(scenery.modelMat);

    rspq_block_begin();
    t3d_model_draw(scenery.model);
    scenery.dl = rspq_block_end();

    return scenery;
}

void scenery_draw(Scenery *scenery)
{
    for (uint8_t i = 0; i < SCENERY_COUNT; i++) {

        t3d_mat4fp_from_srt_euler(scenery[i].modelMat,
            (float[3]){scenery[i].scale.x, scenery[i].scale.y, scenery[i].scale.z},
            (float[3]){rad(scenery[i].rotation.x), rad(scenery[i].rotation.y), rad(scenery[i].rotation.z)},
            (float[3]){scenery[i].position.x, scenery[i].position.y, scenery[i].position.z}
        );
        t3d_matrix_set(scenery[i].modelMat, true);
        rspq_block_run(scenery[i].dl);
	};
}

void scenery_delete(Scenery *scenery)
{
	t3d_model_free(scenery->model);
	rspq_block_free(scenery->dl);
}

#endif