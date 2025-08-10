#ifndef MEMORY_H
#define MEMORY_H


Actor* actor_create(uint32_t id, PlayerArmature* armature, const char *model_path);
void actor_delete(Actor *actor);

Player* player_create(uint32_t id, const char *model_path);

Scenery* scenery_create(uint32_t id, const char *model_path);
void scenery_delete(Scenery *scenery);


#endif