#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include "../../../include/physics/math/matrix3x3.h"
#include "../../../include/physics/math/vector3.h"
#include "../../../include/physics/math/quaternion.h"


// function prototypes


float lerpf(float a, float b, float t);
Vector3 vector3_multiplyByMatrix3x3(const Matrix3x3 *matrix, const Vector3 *vector);
Vector3 vector3_rotateByQuaternion(const Vector3 *v, const Quaternion *q);

Vector3 vector3_transformToLocalSpace(const Vector3 *global_point, Vector3 local_center, Vector3 rotation);
Vector3 vector3_transformToGlobalSpace(const Vector3 *local_point, Vector3 local_center, Vector3 rotation);

Vector3 vector3_reflect(const Vector3* vector, const Vector3* normal);

Vector3 vector3_degToRad(const Vector3 *rotation);
Vector3 vector3_clamp(const Vector3 *vector, float maxLength);

bool vector3_areParallel(const Vector3 *vector1, const Vector3 *vector2);
bool vector3_areOrthogonal(const Vector3 *vector1, const Vector3 *vector2);

void point_rotateZYX(Vector3 *point, const Vector3 *rotation);
void point_rotateXYZ(Vector3 *point, const Vector3 *rotation);
void point_transformToLocalSpace(Vector3* global_point, const Vector3* local_center, const Vector3* local_rotation);
void point_transformToGlobalSpace(Vector3* local_point, const Vector3* local_center, const Vector3* local_rotation);

Vector3 segment_closestToPoint(const Vector3 *seg_a, const Vector3 *seg_b, const Vector3 *point_c);
void segment_closestPointsWithSegment(const Vector3 *seg1_a, const Vector3 *seg1_b, const Vector3 *seg2_a, const Vector3 *seg2_b, Vector3 *closest_seg1, Vector3 *closest_seg2);
float segment_distanceToPoint(const Vector3 *a, const Vector3 *b, const Vector3 *p);

float line_distanceToPoint(const Vector3 *linePointA, const Vector3 *linePointB, const Vector3 *point);

float plane_intersectionWithSegment(const Vector3 *a, const Vector3 *b, float plane_displacement, const Vector3 *planeormal);

void triangle_getBarycentricCoordinates(const Vector3 *a, const Vector3 *b, const Vector3 *c, const Vector3 *p, float *u, float *v, float *w);

Matrix3x3 rotationMatrix_getFromEuler(const Vector3 *rotation);

void rotate_normal(Vector3 *vector, const Vector3 *rotation);



#endif
