#include <stdint.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../../include/physics/physics.h"
#include "../../../include/control/control.h"
#include "../../../include/actor/actor.h"
#include "../../../include/physics/physics.h"
#include "../../../include/control/control.h"
#include "../../../include/actor/actor.h"
#include "../../../include/player/player_states.h"
#include "../../../include/physics/player_collision/player_collision_detection.h"
#include "../../../include/physics/player_collision/player_collision_response.h"


void actorCollision_pushTowardsNormal(Actor* actor, ActorContact* contact)
{
    // Calculate the necessary displacement vector in the direction of the contact normal
    Vector3 displacement_vector = vector3_returnScaled(&contact->data.normal, -contact->data.penetration);

    // Apply the displacement to the actor's position
    vector3_subtract(&actor->body.position, &displacement_vector);
}

// lighter solution to use together with the push towards normal function. gives almost same results, for now i will use the correct algorithm
void actorCollision_projectAcceleration(Actor* actor, ActorContact* contact)
{
    float t = vector3_returnDotProduct(&actor->body.acceleration, &contact->data.normal);
    vector3_addScaledVector(&actor->body.acceleration, &contact->data.normal, -t);
}

void actorCollision_projectVelocity(Actor* actor, ActorContact* contact)
{
    float t = vector3_returnDotProduct(&actor->body.velocity, &contact->data.normal);
    vector3_addScaledVector(&actor->body.velocity, &contact->data.normal, -t);
}

void actorCollision_solvePenetration(Actor* actor, ActorContact* contact, ActorCollider* collider)
{
    // Normalize the actor's velocity vector
    Vector3 velocity_normal = vector3_returnNormalized(&actor->body.velocity);

    // Calculate the intersection of the ray (contact point + velocity normal) with the plane
    float denominator = vector3_returnDotProduct(&velocity_normal, &contact->data.normal);
    float numerator = contact->displacement + collider->body.radius - vector3_returnDotProduct(&contact->data.point, &contact->data.normal);

    float t;
    if (fabs(denominator) > 0.0001f) t = numerator / denominator;
    else return;

    Vector3 axis_closest_at_contact = contact->data.point;
    vector3_addScaledVector(&axis_closest_at_contact, &velocity_normal, t);

    Vector3 displacement_vector = axis_closest_at_contact;
    vector3_subtract(&displacement_vector, &contact->axis_closest_to_contact);

    contact->velocity_penetration = displacement_vector;
    vector3_invert(&contact->velocity_penetration);

    vector3_add(&actor->body.position, &displacement_vector);
}

void actorCollision_collideAndSlide(Actor* actor, ActorContact* contact)
{
    float t = vector3_returnDotProduct(&contact->velocity_penetration, &contact->data.normal);
    Vector3 projection = contact->velocity_penetration;
    vector3_addScaledVector(&projection, &contact->data.normal, -t);
    
    vector3_add(&actor->body.position, &projection);
}

void actorCollision_setGroundResponse(Actor* actor)
{
    actor->grounded = true;
    actor->body.acceleration.z = 0;
    actor->body.velocity.z = 0;
    actor->grounding_height = actor->body.position.z;
    actor_setState(actor, actor->previous_state);
}

void actorCollision_setCeilingResponse(Actor* actor, ActorContact* contact)
{   
    if (actor->body.velocity.z > 0){
    vector3_scale(&actor->body.velocity, 1 - (contact->angle_of_incidence * 0.01));           // angle of incidence can be up to 90 degrees
    actor->body.velocity = vector3_reflect(&actor->body.velocity, &contact->data.normal);
    actor->body.velocity.z = 0.0f;
    }
    else {
        actor->body.velocity.x = 0.0f;
        actor->body.velocity.y = 0.0f;
    }
    actor_setState(actor, FALLING);
}

void actorCollision_setResponse(Actor* actor, ActorContact* contact, ActorCollider* collider)
{
    actorContact_setAngleOfIncidence(contact, &actor->body.velocity);
    actorCollision_solvePenetration(actor, contact, collider);

    if (contact->slope > 0 && contact->slope < 50) {
        actorCollision_setGroundResponse(actor);
        actorCollision_collideAndSlide(actor, contact);
    }
    else if (contact->slope > 95 && actor->grounded == false) {
        actorCollision_collideAndSlide(actor, contact);
        actorCollision_setCeilingResponse(actor, contact);    
    }
    else actorCollision_collideAndSlide(actor, contact);

    actorCollider_setVertical(collider, &actor->body.position);
}

void actorCollision_collideWithRoom(Actor* actor) {
    if (actor->body.position.x > 2450) actor->body.position.x = 2450;
    if (actor->body.position.x < -2450) actor->body.position.x = -2450;
    if (actor->body.position.y > 2450) actor->body.position.y = 2450;
    if (actor->body.position.y < -2450) actor->body.position.y = -2450;
    if (actor->body.position.z < 0) actor->body.position.z = 0;
}
