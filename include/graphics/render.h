#ifndef RENDER_H
#define RENDER_H


void actor_draw(Actor* actor);
void scenery_draw(Scenery** scenery);

void render_t3dScene(Player* player, Scenery** scenery);

void render();

#endif