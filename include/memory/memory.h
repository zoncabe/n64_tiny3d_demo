#ifndef MEMORY_H
#define MEMORY_H


Player* player_create(const char *model_path, ActorMotionSettings* motion_settings, PlayerAnimationSettings* animation_settings);

Scenery* scenery_create(const char *model_path);
void scenery_delete(Scenery *scenery);


#endif