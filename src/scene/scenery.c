

#include "../../include/scene/scenery.h"
#include "../../include/physics/math/math_common.h"

//function implementations

Scenery scenery_create(uint32_t id, const char *model_path)
{
    Scenery scenery = {
        .id = id,
        .model = t3d_model_load(model_path),
        .matrix = malloc_uncached(sizeof(T3DMat4FP)), // needed for t3d

        .scale = {1.0f, 1.0f, 1.0f},
        .position = {0.0f, 0.0f, 0.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
    };

    t3d_matrix_set(scenery.matrix, true);
    t3d_mat4fp_identity(scenery.matrix);

    rspq_block_begin();
    t3d_model_draw(scenery.model);
    scenery.dl = rspq_block_end();

    return scenery;
}

void scenery_draw(Scenery *scenery)
{
    for (uint8_t i = 0; i < SCENERY_COUNT; i++) {

        t3d_mat4fp_from_srt_euler(scenery[i].matrix,
            (float[3]){scenery[i].scale.x, scenery[i].scale.y, scenery[i].scale.z},
            (float[3]){rad(scenery[i].rotation.x), rad(scenery[i].rotation.y), rad(scenery[i].rotation.z)},
            (float[3]){scenery[i].position.x, scenery[i].position.y, scenery[i].position.z}
        );
        t3d_matrix_set(scenery[i].matrix, true);
        rspq_block_run(scenery[i].dl);
	};
}

void scenery_delete(Scenery *scenery)
{
	t3d_model_free(scenery->model);
	rspq_block_free(scenery->dl);
}
