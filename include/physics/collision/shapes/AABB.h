#ifndef AABB_H
#define AABB_H

#include "../../../../include/physics/math/vector3.h"
#include "../../../../include/physics/collision/contact_data.h"
#include "../../../../include/physics/collision/shapes/sphere.h"


// structures

typedef struct AABB {
    Vector3 minCoordinates;
    Vector3 maxCoordinates;
} AABB;

// function prototypes

void aabb_setFromCenterAndSize(AABB *aabb, const Vector3* center, const Vector3* size);
void aabb_getCorners(const AABB* aabb, Vector3 corners[8]);

Vector3 aabb_closestToPoint(const AABB* aabb, const Vector3* point);
Vector3 aabb_closestToSegment(const AABB* aabb, const Vector3* a, const Vector3* b);

bool aabb_containsPoint(const AABB *aabb, const Vector3 *point);
bool aabb_contactAABB(const AABB *a, const AABB *b);
void aabb_contactAABBsetData(ContactData* contact, const AABB* a, const AABB* b);
bool aabb_contactSphere(const AABB* aabb, const Sphere* sphere);
void aabb_contactSphereSetData(ContactData* contact, const AABB* aabb, const Sphere* sphere);


#endif
