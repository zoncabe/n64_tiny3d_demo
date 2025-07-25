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
