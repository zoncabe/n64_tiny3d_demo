#ifndef MEMORY_H
#define MEMORY_H


Player* player_create(uint32_t id, const char *model_path, PlayerMotionSettings* motion_settings, PlayerAnimationSettings* animation_settings);

Scenery* scenery_create(uint32_t id, const char *model_path);
void scenery_delete(Scenery *scenery);


#endif