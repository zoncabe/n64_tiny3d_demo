

#include "../../../include/physics/body/rigid_body.h"

void rigidBody_init(RigidBody* body)
{
    body->position.x = 0.0f;
    body->position.y = 0.0f;
    body->position.z = 0.0f;

    body->velocity.x = 0.0f;
    body->velocity.y = 0.0f;
    body->velocity.z = 0.0f;

    body->rotation.x = 0.0f;
    body->rotation.y = 0.0f;
    body->rotation.z = 0.0f;

}