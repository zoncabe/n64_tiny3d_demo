/**
 * @file
 *
 * Holds a quaternion.
 */

#ifndef QUATERNION_H
#define QUATERNION_H

#include "../../../include/physics/math/matrix3x3.h"
#include "../../../include/physics/math/vector3.h"


typedef struct {
    float x;
    float y;
    float z;
    float w;
} Quaternion;

// Function prototypes
void quaternion_set(Quaternion* q, float x, float y, float z, float w);
void quaternion_init(Quaternion* q);
void quaternion_clear(Quaternion* q);

void quaternion_setWithVector(Quaternion* q, float w, const Vector3* v);

Quaternion quaternion_sum(const Quaternion* q, const Quaternion* r);
Quaternion quaternion_difference(const Quaternion* q, const Quaternion* r);
Quaternion quaternion_returnScaled(const Quaternion* q, float scalar);
Quaternion quaternion_returnProduct(const Quaternion* q, const Quaternion* r);
Vector3 quaternion_getVectorProduct(const Quaternion* q, const Vector3* vector);

void quaternion_setIdentity(Quaternion* q);
Vector3 quaternion_returnVectorV(const Quaternion* q);
float quaternion_magnitude(const Quaternion* q);
float quaternion_squaredMagnitude(const Quaternion* q);
void quaternion_normalize(Quaternion* q);
void quaternion_invert(Quaternion* q);

Quaternion quaternion_returnUnit(const Quaternion* q);

Quaternion quaternion_getConjugate(const Quaternion* q);
Quaternion quaternion_getInverse(const Quaternion* q);
float quaternion_dotProduct(const Quaternion* q, const Quaternion* r);

bool quaternion_isFinite(const Quaternion* q);
bool quaternion_isUnit(const Quaternion* q);
bool quaternion_isValid(const Quaternion* q);
bool quaternion_equals(const Quaternion* q, const Quaternion* r);

void quaternion_setFromEulerAngles(Quaternion* quaternion, float angleX, float angleY, float angleZ);
Quaternion quaternion_getFromEulerAngles(float angleX, float angleY, float angleZ);
Quaternion quaternion_getFromVector(const Vector3* rotation);
Quaternion quaternion_getFromMatrix(const Matrix3x3* matrix);

void quaternion_setRotationAngleAxis(Quaternion* quaternion, float* angle, Vector3* axis);
Matrix3x3 quaternion_getMatrix(const Quaternion* quaternion);

Quaternion quaternion_slerp(const Quaternion* q, const Quaternion* r, float t);

#endif
