#ifndef SPHERE_H
#define SPHERE_H

#include "../../../../include/physics/math/vector3.h"
#include "../../../../include/physics/collision/contact_data.h"


// structures

typedef struct {
    Vector3 center;
    float radius;
} Sphere;



bool sphere_contactSphere(const Sphere* s, const Sphere* t);
void sphere_collisionTestSphere(ContactData* contact, const Sphere* s, const Sphere* t);

#endif