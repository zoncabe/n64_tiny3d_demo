#ifndef RENDER_H
#define RENDER_H


void actor_draw(Actor* actor);
void scenery_draw(Scenery** scenery);

void render_gameplayScene(Player* player, Scenery** scenery);

void render();

#endif