#include <stdint.h>
#include <t3d/t3dskeleton.h>
#include <t3d/t3danim.h>

#include "../../../include/physics/physics.h"
#include "../../../include/control/control.h"
#include "../../../include/actor/actor.h"
#include "../../../include/physics/physics.h"
#include "../../../include/physics/player_collision/player_collision_detection.h"


void actorCollider_init(ActorCollider* collider)
{
    collider->body.radius = collider->settings.body_radius;
    collider->body.length = collider->settings.body_height;
}

void actorCollider_setVertical(ActorCollider* collider, Vector3* position)
{
    capsule_setVertical(&collider->body, position);
}

void actorCollider_set(ActorCollider* collider, Vector3* position, Vector3* rotation)
{
}

void actorContact_clear(ActorContact* contact)
{
    contact->axis_closest_to_contact = (Vector3){0.0f, 0.0f, 0.0f};
    contact->velocity_penetration = (Vector3){0.0f, 0.0f, 0.0f};
    contact->slope = 1000.0f;                                      // Set the slope to an out of range value to indicate no contact
    contact->displacement = 0.0f;
    contact->ground_distance = 1000.0f;
    contactData_init(&contact->data);
}

void actorContact_setAxisClosestPoint(ActorContact* contact, ActorCollider* collider)
{
    contact->axis_closest_to_contact = segment_closestToPoint(&collider->body.start, &collider->body.end, &contact->data.point);
}

void actorContact_setSlope(ActorContact* contact) 
{
    float magnitude = vector3_magnitude(&contact->data.normal);
    float cos_slope = contact->data.normal.z / magnitude;         // Calculate the cosine of the angle between the normal and the z-axis
    float slope = acosf(cos_slope);
    contact->slope = deg(slope);
}

void actorContact_setAngleOfIncidence(ActorContact* contact, const Vector3 *velocity) 
{
    contact->angle_of_incidence = -deg((M_PI * 0.5f) - acosf(vector3_returnDotProduct(velocity, &contact->data.normal) / vector3_magnitude(velocity)));
}

void actorContact_setDisplacement(ActorContact* contact)
{
    contact->displacement = vector3_returnDotProduct(&contact->data.point, &contact->data.normal);
}

void actorContact_setGroundDistance(ActorContact* contact, Vector3* position)
{    
    if (contact->data.normal.z == 0.0f) contact->ground_distance = 1000.0;   // arbitrary large value to indicate no grounding
    else contact->ground_distance = (contact->displacement - vector3_returnDotProduct(position, &contact->data.normal)) / -contact->data.normal.z;
}


void actorContact_setData(ActorContact* contact, ActorCollider* collider){

    actorContact_setSlope(contact);
    actorContact_setDisplacement(contact);
    actorContact_setAxisClosestPoint(contact, collider);
}

bool actorCollision_contactSphere(const ActorCollider* collider, const Sphere* sphere)
{
    return capsule_contactSphere(&collider->body, sphere);
}

void actorCollision_contactSphereSetData(ActorContact* contact, ActorCollider* collider, const Sphere* sphere)
{
    capsule_contactSphereSetData(&contact->data, &collider->body, sphere);
    actorContact_setData(contact, collider);
}

bool actorCollision_contactAABB(const ActorCollider* collider, const AABB* aabb)
{
    return capsule_contactAABB(&collider->body, aabb);
}

void actorCollision_contactAABBsetData(ActorContact* contact, ActorCollider* collider, const AABB* aabb)
{
    capsule_contactAABBSetData(&contact->data, &collider->body, aabb);
    actorContact_setData(contact, collider);
}

bool actorCollision_contactBox(const ActorCollider* collider, const Box* box)
{
    return capsule_contactBox(&collider->body, box);
}

void actorCollision_contactBoxSetData(ActorContact* contact, ActorCollider* collider, const Box* box)
{   
    capsule_contactBoxSetData(&contact->data, &collider->body, box);
    actorContact_setData(contact, collider);
}

bool actorCollision_contactPlane(const ActorCollider* collider, const Plane* plane)
{
    return capsule_contactPlane(&collider->body, plane);
}

void actorCollision_contactPlaneSetData(ActorContact* contact, ActorCollider* collider, const Plane* plane)
{
    capsule_contactPlaneSetData(&contact->data, &collider->body, plane);
    actorContact_setSlope(contact);
    contact->displacement = plane->displacement;
    actorContact_setAxisClosestPoint(contact, collider);
}

bool actorCollision_intersectionRay(const ActorCollider* collider, const Ray* ray)
{
    return capsule_intersectionRay(&collider->body, ray);
}
