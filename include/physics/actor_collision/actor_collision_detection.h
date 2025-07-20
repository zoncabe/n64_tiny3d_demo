#ifndef ACTOR_COLLISION_H
#define ACTOR_COLLISION_H


// collision types

#define SPHERE 1
#define AABB_ 2
#define BOX 3
#define PLANE 4
#define RAY 5
#define CAPSULE 6
#define TERRAIN 7
#define MESH 8

// structures

typedef struct {
    float body_radius;
    float body_height;
    //float sword_radius;
    //float sword_lenght;
    //float shield_radius;
} ActorColliderSettings;

typedef struct {
    Capsule body;
    //Capsule sword;
    //Sphere shield;
    ActorColliderSettings settings;
} ActorCollider;

typedef struct {
    Vector3 axis_closest_to_contact;     // closest point in the capsule axis to the point of contact
    Vector3 velocity_penetration;      // penetration vector in the direction of the velocity
    float slope;                       // angle of inclination of the the plane of contact
    float angle_of_incidence;          // angle between the velocity vector and the plane of contact
    float displacement;                // distance from the origin to the plane of contact
    float ground_distance;          // vertical distance from the actor's position to the nearest plane of contact
    ContactData data;
} ActorContact;


void actorCollider_init(ActorCollider* collider);
void actorCollider_setVertical(ActorCollider* collider, Vector3* position);
void actorCollider_set(ActorCollider* collider, Vector3* position, Vector3* rotation);

void actorContact_clear(ActorContact* contact);
void actorContact_setAxisClosestPoint(ActorContact* contact, ActorCollider* collider);
void actorContact_setSlope(ActorContact* contact);

void actorContact_setAngleOfIncidence(ActorContact* contact, const Vector3 *velocity);

void actorContact_setDisplacement(ActorContact* contact);

void actorContact_setGroundDistance(ActorContact* contact, Vector3* position);

void actorContact_setData(ActorContact* contact, ActorCollider* collider);

bool actorCollision_contactSphere(const ActorCollider* collider, const Sphere* sphere);
void actorCollision_contactSphereSetData(ActorContact* contact, ActorCollider* collider, const Sphere* sphere);

bool actorCollision_contactAABB(const ActorCollider* collider, const AABB* aabb);
void actorCollision_contactAABBsetData(ActorContact* contact, ActorCollider* collider, const AABB* aabb);

bool actorCollision_contactBox(const ActorCollider* collider, const Box* box);
void actorCollision_contactBoxSetData(ActorContact* contact, ActorCollider* collider, const Box* box);

bool actorCollision_contactPlane(const ActorCollider* collider, const Plane* plane);
void actorCollision_contactPlaneSetData(ActorContact* contact, ActorCollider* collider, const Plane* plane);

bool actorCollision_intersectionRay(const ActorCollider* collider, const Ray* ray);

#endif
