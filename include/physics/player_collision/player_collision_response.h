#ifndef ACTOR_COLLISION_RESPONSE_H
#define ACTOR_COLLISION_RESPONSE_H     


void actorCollision_pushTowardsNormal(Actor* actor, ActorContact* contact);

void actorCollision_projectAcceleration(Actor* actor, ActorContact* contact);

void actorCollision_projectVelocity(Actor* actor, ActorContact* contact);

void actorCollision_solvePenetration(Actor* actor, ActorContact* contact, ActorCollider* collider);

void actorCollision_collideAndSlide(Actor* actor, ActorContact* contact);

void actorCollision_setGroundResponse(Actor* actor);

void actorCollision_setCeilingResponse(Actor* actor, ActorContact* contact);

void actorCollision_setResponse(Actor* actor, ActorContact* contact, ActorCollider* collider);

void actorCollision_collideWithRoom(Actor* actor);


#endif