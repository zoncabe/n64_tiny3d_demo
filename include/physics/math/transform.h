/**
 * @file
 *
 * Holds the transform matrix.
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "../../../include/physics/math/quaternion.h"


typedef struct {

    Vector3 position;
    Quaternion orientation;

} Transform;

void transform_init(Transform* transform);
void transform_initWithMatrix(Transform* transform, const Vector3* position, const Matrix3x3* orientation);
void transform_initWithQuaternion(Transform* transform, const Vector3* position, const Quaternion* orientation);

Vector3 transform_getPosition(const Transform* transform);
void transform_setPosition(Transform* transform, const Vector3* position);
Quaternion transform_getOrientation(const Transform* transform);
void transform_setOrientation(Transform* transform, const Quaternion* orientation);

void transform_setIdentity(Transform* transform);
Transform transform_returnIdentity();

Transform transform_getInverse(const Transform* transform);
Transform transform_getInterpolated(const Transform* oldTransform, const Transform* newTransform, float factor);

Vector3 transform_getProductVector(const Transform* transform, const Vector3* vector);
Transform transform_product(const Transform* t1, const Transform* t2);

bool transform_isValid(const Transform* transform);
bool transform_equals(const Transform* t1, const Transform* t2);
bool transform_notEquals(const Transform* t1, const Transform* t2);
void transform_toString(const Transform* transform, char* buffer, size_t bufferSize);


#endif
