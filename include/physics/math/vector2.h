/**
 * @file
 *
 * holds a vector in 2 dimensions.
 */

#ifndef VECTOR2_H
#define VECTOR2_H


// Vector2 structure
typedef struct {
    float x;
    float y;
}
 Vector2;


// Function prototypes

void vector2_init(Vector2 *v);
void vector2_clear(Vector2 *v);
void vector2_set(Vector2 *v, float x, float y);

void vector2_setValue(Vector2* vector, int index, float value);
float vector2_returnValue(const Vector2* vector, int index);

void vector2_add(Vector2* v, const Vector2* vector2);
void vector2_subtract(Vector2* v, const Vector2* vector2);
void vector2_scale(Vector2* vector, float number);
void vector2_divideByNumber(Vector2* vector, float number);

float vector2_magnitude(const Vector2* vector);
float vector2_squaredMagnitude(const Vector2* vector);

Vector2 vector2_returnUnit(const Vector2* vector);
Vector2 vector2_returnUnitOrthogonalVector(const Vector2* vector);

float vector2_dotProduct(const Vector2* v, const Vector2* vector2);
void vector2_normalize(Vector2* vector);
Vector2 vector2_returnAbsoluteVector(const Vector2* vector);

Vector2 vector2_min(const Vector2* v, const Vector2* vector2);
Vector2 vector2_max(const Vector2* v, const Vector2* vector2);

int vector2_returnMinAxis(const Vector2* vector);
int vector2_returnMaxAxis(const Vector2* vector);

bool vector2_isUnit(const Vector2* vector);
bool vector2_isFinite(const Vector2* vector);
bool vector2_isZero(const Vector2* vector);

bool vector2_equals(const Vector2* v, const Vector2* vector2);
bool vector2_notEquals(const Vector2* v, const Vector2* vector2);
bool vector2_lessThan(const Vector2* v, const Vector2* vector2);
bool vector2_approxEqual(const Vector2* v, const Vector2* w, float epsilon);


#endif
