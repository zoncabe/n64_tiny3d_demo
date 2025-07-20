#ifndef BOX_H
#define BOX_H


// structures

typedef struct {
    Vector3 size;
    Vector3 center;
    Vector3 rotation;
} Box;


// function prototypes

AABB box_getLocalAABB(const Box* box);

bool box_contactSphere(const Box* box, const Sphere* sphere);
void box_contactSphereSetData(ContactData* contact, const Box* box, const Sphere* sphere);


#endif 
