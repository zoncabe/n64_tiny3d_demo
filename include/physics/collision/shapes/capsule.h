#ifndef CAPSULE_H
#define CAPSULE_H


#include "../../../../include/physics/math/vector3.h"
#include "../../../../include/physics/collision/contact_data.h"
#include "../../../../include/physics/collision/shapes/sphere.h"
#include "../../../../include/physics/collision/shapes/AABB.h"
#include "../../../../include/physics/collision/shapes/box.h"
#include "../../../../include/physics/collision/shapes/plane.h"
#include "../../../../include/physics/collision/shapes/ray.h"


typedef struct {

    Vector3 start;
    Vector3 end;
    float radius;
    float length;

} Capsule;


// Function prototypes

void capsule_setVertical(Capsule* capsule, const Vector3* position);

bool capsule_contactSphere(const Capsule* capsule, const Sphere* sphere);
void capsule_contactSphereSetData(ContactData* contact, const Capsule* capsule, const Sphere* sphere);

bool capsule_contactAABB(const Capsule* capsule, const AABB* aabb);
void capsule_contactAABBSetData(ContactData* contact, const Capsule* capsule, const AABB* aabb);

bool capsule_contactBox(const Capsule* capsule, const Box* box);
void capsule_contactBoxSetData(ContactData* contact, const Capsule* capsule, const Box* box);

bool capsule_contactPlane(const Capsule* capsule, const Plane* plane);
void capsule_contactPlaneSetData(ContactData* contact, const Capsule* capsule, const Plane* plane);

bool capsule_intersectionRay(const Capsule* capsule, const Ray* ray);


#endif