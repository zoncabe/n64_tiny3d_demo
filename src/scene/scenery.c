#include <t3d/t3dmodel.h>

#include "../../include/physics/physics.h"
#include "../../include/scene/scenery.h"


// global

Scenery* scenery[SCENERY_COUNT];


//function implementations

void scenery_init(Scenery* scenery)
{
    *scenery = (Scenery){

        .scale = {1.0f, 1.0f, 1.0f},
        .position = {0.0f, 0.0f, 0.0f},
        .rotation = {0.0f, 0.0f, 0.0f},
    };
}

void scenery_set(Scenery* scenery,
                 float scale_x, float scale_y, float scale_z,
                 float pos_x, float pos_y, float pos_z,
                 float rot_x, float rot_y, float rot_z)
{
    t3d_mat4fp_from_srt_euler(scenery->t3d_matrix,
        (float[3]){scale_x, scale_y, scale_z},
        (float[3]){rad(rot_x), rad(rot_y), rad(rot_z)},
        (float[3]){pos_x, pos_y, pos_z}
    );
}

void scenery_update(Scenery* scenery)
{
    t3d_mat4fp_from_srt_euler(scenery->t3d_matrix,
        (float[3]){scenery->scale.x, scenery->scale.y, scenery->scale.z},
        (float[3]){rad(scenery->rotation.x), rad(scenery->rotation.y), rad(scenery->rotation.z)},
        (float[3]){scenery->position.x, scenery->position.y, scenery->position.z}
    );
}

void scenery_draw(Scenery* scenery)
{
	rspq_block_run(scenery->dl);
}
