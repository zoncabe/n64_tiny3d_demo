#ifndef MEMORY_H
#define MEMORY_H


Actor* actor_create(uint32_t id, const char *model_path);
void actor_delete(Actor *actor);

Scenery* scenery_create(uint32_t id, const char *model_path);
void scenery_delete(Scenery *scenery);


#endif