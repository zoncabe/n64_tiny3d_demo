
#include "../../include/scene/scene.h"


void scene_init(Scene *scene)
{
    camera_init(&scene->camera);
    scene->light = light_create();
}