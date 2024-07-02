#ifndef ACTOR_COLLIDE_H
#define ACTOR_COLLIDE_H


void actor_collideWithPlayground(Actor *actor);


void actor_collideWithPlayground(Actor *actor)
{
    if (actor->body.position.x >  1870) actor->body.position.x =  1870;
    if (actor->body.position.x < -1870) actor->body.position.x = -1870;
    if (actor->body.position.y >  1870) actor->body.position.y =  1870;
    if (actor->body.position.y < -1870) actor->body.position.y = -1870;
}
#endif