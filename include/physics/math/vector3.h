#ifndef VECTOR_3_H
#define VECTOR_3_H


// structures

typedef struct Vector3 {
    float x; 
    float y; 
    float z;  
} Vector3;

// function prototypes

void vector3_init(Vector3 *v);
void vector3_clear(Vector3 *v);
void vector3_set(Vector3 *v, float x, float y, float z);
void vector3_setElement(Vector3* v, int index, float value);
float vector3_returnElement(const Vector3* v, int index);

void vector3_invert(Vector3 *v);
Vector3 vector3_getInverse(const Vector3 *v);

void vector3_add(Vector3 *v, const Vector3 *w);
Vector3 vector3_sum(const Vector3 *v, const Vector3 *w);
void vector3_subtract(Vector3 *v, const Vector3 *w);
Vector3 vector3_difference(const Vector3 *v, const Vector3 *w);

void vector3_scale(Vector3 *v, float scalar);
Vector3 vector3_returnScaled(const Vector3 *v, float scalar);
void vector3_divideByNumber(Vector3* v, float number);
Vector3 vector3_returnQuotientByNumber(const Vector3* v, float number);
Vector3 vector3_returnQuotientByVector(const Vector3* v, const Vector3* w);

void vector3_componentProduct(Vector3 *v, const Vector3 *w);
Vector3 vector3_returnComponentProduct(const Vector3 *v, const Vector3 *w);
void vector3_crossProduct(Vector3 *v, const Vector3 *w);
Vector3 vector3_returnCrossProduct(const Vector3 *v, const Vector3 *w);
float vector3_returnDotProduct(const Vector3 *v, const Vector3 *w);
void vector3_addScaledVector(Vector3 *v, const Vector3 *w, float scalar);

float vector3_magnitude(const Vector3 *v);
float vector3_squaredMagnitude(const Vector3 *v);
void vector3_normalize(Vector3 *v);
Vector3 vector3_returnNormalized(const Vector3 *v);
Vector3 vector3_returnAbsoluteVector(const Vector3* v);
Vector3 vector3_lerp(const Vector3* v, const Vector3* w, float t);

Vector3 vector3_min(const Vector3* v, const Vector3* w);
Vector3 vector3_max(const Vector3* v, const Vector3* w);
float vector3_returnMinValue(const Vector3* v);
float vector3_returnMaxValue(const Vector3* v);
int vector3_returnMinAxis(const Vector3* v);
int vector3_returnMaxAxis(const Vector3* v);

bool vector3_isUnit(const Vector3* v);
bool vector3_isFinite(const Vector3* v);
bool vector3_isZero(const Vector3* v);
bool vector3_equals(const Vector3* v, const Vector3* w);
bool vector3_notEquals(const Vector3* v, const Vector3* w);
bool vector3_lessThan(const Vector3* v, const Vector3* w);
bool vector3_approxEquals(const Vector3* v, const Vector3* w);


#endif
