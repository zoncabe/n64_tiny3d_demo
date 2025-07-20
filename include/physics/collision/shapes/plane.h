#ifndef PLANE_H
#define PLANE_H


// structures


typedef struct {

    Vector3 normal;       // Normal vector of the plane
    float displacement;   // Displacement from the origin along the normal

} Plane;


// function prototypes

Vector3 plane_getNormalFromRotation(const Vector3* rotation);
float plane_getDisplacement(const Vector3* normal, const Vector3* point);
void plane_setFromRotationAndPoint(Plane* plane, const Vector3* rotation, const Vector3* point);
void plane_setFromNormalAndPoint(Plane* plane, const Vector3* normal, const Vector3* point);
float plane_distanceToPoint(const Plane* plane, const Vector3* point);
bool plane_contactSphere(const Plane* plane, const Sphere* sphere);
void plane_contactSphereGetData(ContactData* contact, const Plane* plane, const Sphere* sphere);


#endif
