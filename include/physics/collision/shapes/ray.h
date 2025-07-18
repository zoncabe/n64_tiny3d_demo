#ifndef RAY_H
#define RAY_H

#include "../../../../include/physics/math/vector3.h"
#include "../../../../include/physics/collision/contact_data.h"
#include "../../../../include/physics/collision/shapes/sphere.h"
#include "../../../../include/physics/collision/shapes/AABB.h"
#include "../../../../include/physics/collision/shapes/box.h"
#include "../../../../include/physics/collision/shapes/plane.h"


// structures

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

// function prototypes

Vector3 ray_getDirectionFromRotation(const Vector3* rotation);
void ray_setFromRotationAndPoint(Ray* ray, const Vector3* origin, const Vector3* rotation);

bool ray_intersectionSphere(const Ray* ray, const Sphere* sphere);
void raycast_sphere(ContactData* contact, const Ray* ray, const Sphere* sphere);

bool ray_intersectionAABB(const Ray* ray, const AABB* aabb);
void raycast_aabb(ContactData* contact, const Ray* ray, const AABB* aabb);

bool ray_intersectionBox(const Ray* ray, const Box* box);
void raycast_box(ContactData* contact, const Ray* ray, const Box* box);

bool ray_intersectionPlane(const Ray* ray, const Plane* plane);
void raycast_plane(ContactData* contact, const Ray* ray, const Plane* plane);

#endif
