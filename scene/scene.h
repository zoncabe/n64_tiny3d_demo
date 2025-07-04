#ifndef SCENE_H
#define SCENE_H

typedef struct
{
	Camera camera;
	LightData light;

}Scene;


void scene_init(Scene *scene)
{
    camera_init(&scene->camera);
    scene->light = light_create();
}

#endif