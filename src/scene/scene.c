#include <stdint.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>

#include "../../include/physics/physics.h"
#include "../../include/screen/screen.h"
#include "../../include/camera/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/camera/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/scene/scene.h"


void scene_init(Scene *scene)
{
    camera_init(&scene->camera);
    scene->light = light_create();
}