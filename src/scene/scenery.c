#include <t3d/t3dmodel.h>

#include "../../include/physics/physics.h"
#include "../../include/scene/scenery.h"


// global

Scenery* scenery[SCENERY_COUNT];


//function implementations

void scenery_draw(Scenery **scenery)
{
    for (uint8_t i = 0; i < SCENERY_COUNT; i++) {

        t3d_mat4fp_from_srt_euler(scenery[i]->t3d_matrix,
            (float[3]){scenery[i]->scale.x, scenery[i]->scale.y, scenery[i]->scale.z},
            (float[3]){rad(scenery[i]->rotation.x), rad(scenery[i]->rotation.y), rad(scenery[i]->rotation.z)},
            (float[3]){scenery[i]->position.x, scenery[i]->position.y, scenery[i]->position.z}
        );
        t3d_matrix_set(scenery[i]->t3d_matrix, true);
        rspq_block_run(scenery[i]->dl);
	};
}

void scenery_init(Scenery* scenery)
{
    *scenery = (Scenery){

        .scale = {1.0f, 1.0f, 1.0f},
        .position = {0.0f, 0.0f, 0.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
    };
}
