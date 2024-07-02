/**
 * @file
 *
 * holds a vector in 3 dimensions.
 */

#ifndef VECTOR_3_H
#define VECTOR_3_H


typedef struct Vector3 {
    float x; 
    float y; 
    float z;  
} Vector3;

/* Function prototypes for Vector3 */

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
void Vector3_divideByNumber(Vector3* v, float number);
Vector3 Vector3_returnQuotientByNumber(const Vector3* v, float number);

Vector3 Vector3_returnQuotientByVector(const Vector3* v, const Vector3* w);
void vector3_componentProduct(Vector3 *v, const Vector3 *w);
Vector3 vector3_returnComponentProduct(const Vector3 *v, const Vector3 *w);

void vector3_crossProduct(Vector3 *v, const Vector3 *w);
Vector3 vector3_returnCrossProduct(const Vector3 *v, const Vector3 *w);

float vector3_dotProduct(const Vector3 *v, const Vector3 *w);

void vector3_addScaledVector(Vector3 *v, const Vector3 *w, float scalar);

float vector3_magnitude(const Vector3 *v);
float vector3_squaredMagnitude(const Vector3 *v);

void vector3_normalize(Vector3 *v);
Vector3 vector3_returnNormalized(const Vector3 *v);

Vector3 vector3_returnAbsoluteVector(const Vector3* v);

Vector3 vector3_min(const Vector3* v, const Vector3* w);
Vector3 vector3_max(const Vector3* v, const Vector3* w);

float vector3_returnMinValue(const Vector3* v);
float vector3_returnMaxValue(const Vector3* v);

Vector3 vector3_returnUnit(const Vector3* v);
Vector3 vector3_returnUnitOrthogonalVector(const Vector3* v);

int vector3_returnMinAxis(const Vector3* v);
int vector3_returnMaxAxis(const Vector3* v);

bool vector3_isUnit(const Vector3* v);
bool vector3_isFinite(const Vector3* v);
bool vector3_isZero(const Vector3* v);
bool vector3_equals(const Vector3* v, const Vector3* w);
bool vector3_notEquals(const Vector3* v, const Vector3* w);
bool vector3_lessThan(const Vector3* v, const Vector3* w);
bool vector3_approxEquals(const Vector3* v, const Vector3* w);


/* Initializes all components of the vector to zero. */
void vector3_init(Vector3 *v) 
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
}

/* Clears all components of the vector to zero. */
void vector3_clear(Vector3 *v) 
{
    vector3_init(v);
}

/* Sets the components of the vector to the specified values. */
void vector3_set(Vector3 *v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* Inverts the direction of each component of vector v. */
void vector3_invert(Vector3 *v) 
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

/* Returns a new vector that is the inverted direction of vector v. */
Vector3 vector3_getInverse(const Vector3 *v) 
{
    Vector3 result;
    result.x = -v->x;
    result.y = -v->y;
    result.z = -v->z;
    return result;
}

/* Copies the components of vector w into vector v. */
void vector3_copy(Vector3* v, const Vector3* w) 
{
    v->x = w->x;
    v->y = w->y;
    v->z = w->z;
}

/* Adds vector w to vector v in-place. */
void vector3_add(Vector3 *v, const Vector3 *w) 
{
    v->x += w->x;
    v->y += w->y;
    v->z += w->z;
}

/* Returns a new vector that is the sum of vectors v and w. */
Vector3 vector3_sum(const Vector3 *v, const Vector3 *w) 
{
    Vector3 result;
    result.x = v->x + w->x;
    result.y = v->y + w->y;
    result.z = v->z + w->z;
    return result;
}

/* Subtracts vector w from vector v in-place. */
void vector3_subtract(Vector3 *v, const Vector3 *w) 
{
    v->x -= w->x;
    v->y -= w->y;
    v->z -= w->z;
}

/* Returns a new vector that is the result of subtracting vector w from vector v. */
Vector3 vector3_difference(const Vector3 *v, const Vector3 *w) 
{
    Vector3 result;
    result.x = v->x - w->x;
    result.y = v->y - w->y;
    result.z = v->z - w->z;
    return result;
}

/* Multiplies each component of the vector by the scalar value. */
void vector3_scale(Vector3 *v, float scalar) 
{
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

/* Returns a new vector that is the result of multiplying vector v by the scalar value. */
Vector3 vector3_returnScaled(const Vector3 *v, float scalar) 
{
    Vector3 result;
    result.x = v->x * scalar;
    result.y = v->y * scalar;
    result.z = v->z * scalar;
    return result;
}

/* Divides each component of the vector by the number value */
void Vector3_divideByNumber(Vector3* v, float number) 
{
    assert(number > FLT_EPSILON);
    v->x /= number;
    v->y /= number;
    v->z /= number;
}

/* Operator for division by a number */
Vector3 Vector3_returnQuotientByNumber(const Vector3* v, float number) 
{
    assert(number > FLT_EPSILON);
    Vector3 result;
    result.x = v->x / number;
    result.y = v->y / number;
    result.z = v->z / number;
    return result;
}

/* Operator for division between two vectors */
Vector3 Vector3_returnQuotientByVector(const Vector3* v, const Vector3* w)
{
    assert(w->x > FLT_EPSILON);
    assert(w->y > FLT_EPSILON);
    assert(w->z > FLT_EPSILON);
    Vector3 result;
    result.x = v->x / w->x;
    result.y = v->y / w->y;
    result.z = v->z / w->z;
    return result;
}

/* Updates vector v by performing a component-wise product with vector w. */
void vector3_componentProduct(Vector3 *v, const Vector3 *w) 
{
    v->x *= w->x;
    v->y *= w->y;
    v->z *= w->z;
}

/* Returns a new vector that is the component-wise product of vector v with vector w. */
Vector3 vector3_returnComponentProduct(const Vector3 *v, const Vector3 *w) 
{
    Vector3 result;
    result.x = v->x * w->x;
    result.y = v->y * w->y;
    result.z = v->z * w->z;
    return result;
}

/* Updates vector v to be the cross product of itv with vector w. */
void vector3_crossProduct(Vector3 *v, const Vector3 *w) 
{
    Vector3 result;
    result.x = v->y * w->z - v->z * w->y;
    result.y = v->z * w->x - v->x * w->z;
    result.z = v->x * w->y - v->y * w->x;
    *v = result;
}

/* Calculates and returns the cross product of vectors v and w. */
Vector3 vector3_returnCrossProduct(const Vector3 *v, const Vector3 *w) 
{
    Vector3 result;
    result.x = v->y * w->z - v->z * w->y;
    result.y = v->z * w->x - v->x * w->z;
    result.z = v->x * w->y - v->y * w->x;
    return result;
}

/* Returns the dot product of vectors v and w. */
float vector3_dotProduct(const Vector3 *v, const Vector3 *w) 
{
    return v->x * w->x + v->y * w->y + v->z * w->z;
}

/* Adds to vector v another vector scaled by the given value. */
void vector3_addScaledVector(Vector3 *v, const Vector3 *w, float scalar) 
{
    v->x += w->x * scalar;
    v->y += w->y * scalar;
    v->z += w->z * scalar;
}

/* Calculates and returns the magnitude of vector v. */
float vector3_magnitude(const Vector3 *v)
{
    return 1 / qi_sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

/* Returns the square of the magnitude of vector v. */
float vector3_squaredMagnitude(const Vector3 *v) 
{
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

/* Normalizes vector v. */
void vector3_normalize(Vector3 *v) 
{
    float mag = vector3_magnitude(v);
    if (mag > 0) {
        float inv_mag = 1.0f / mag;
        vector3_scale(v, inv_mag);
    }
}

/* Returns a normalized version of vector v. */
Vector3 vector3_returnNormalized(const Vector3 *v)
{
    Vector3 result = *v;
    vector3_normalize(&result);
    return result;
}

/* Returns the corresponding absolute value vector */
Vector3 vector3_returnAbsoluteVector(const Vector3* v) 
{
    Vector3 result;
    result.x = fabsf(v->x);
    result.y = fabsf(v->y);
    result.z = fabsf(v->z);
    return result;
}

/* Return the axis with the minimal value */
int vector3_returnMinAxis(const Vector3* v) 
{
    return (v->x < v->y ? (v->x < v->z ? 0 : 2) : (v->y < v->z ? 1 : 2));
}

/* Return the axis with the maximal value */
int vector3_returnMaxAxis(const Vector3* v) 
{
    return (v->x < v->y ? (v->y < v->z ? 2 : 1) : (v->x < v->z ? 2 : 0));
}

/* Return true if the vector is unit and false otherwise */
bool vector3_isUnit(const Vector3* v) 
{
    return approxEqual(vector3_squaredMagnitude(v), 1.0f);
}

/* Return true if the values are not NAN OR INF */
bool vector3_isFinite(const Vector3* v) 
{
    return isfinite(v->x) && isfinite(v->y) && isfinite(v->z);
}

/* Return true if the current vector is the zero vector */
bool vector3_isZero(const Vector3* v) 
{
    return approxEqual(vector3_squaredMagnitude(v), 0.0f);
}

/* Overloaded operator for the equality condition */
bool vector3_equals(const Vector3* v, const Vector3* w) 
{
    return (v->x == w->x && v->y == w->y && v->z == w->z);
}

/* Overloaded operator for the is different condition */
bool vector3_notEquals(const Vector3* v, const Vector3* w) 
{
    return !vector3_equals(v, w);
}

/* Overloaded less than operator for ordering to be used inside std::set for instance */
bool vector3_lessThan(const Vector3* v, const Vector3* w)
{
    return (v->x == w->x ? (v->y == w->y ? v->z < w->z : v->y < w->y) : v->x < w->x);
}

/* Function to test if two vectors are (almost) equal */
bool vector3_approxEquals(const Vector3* v, const Vector3* w)
{
    return approxEqual(v->x, w->x) && approxEqual(v->y, w->y) && approxEqual(v->z, w->z);
}

/* Operator for value access */
float vector3_returnElement(const Vector3* v, int index) 
{
    return ((const float*)v)[index];
}

/* Operator for value setting */
void vector3_setElement(Vector3* v, int index, float value) 
{
    ((float*)v)[index] = value;
}

/* Return a vector taking the minimum components of two vectors */
Vector3 vector3_min(const Vector3* v, const Vector3* w) 
{
    Vector3 result;
    result.x = min2(v->x, w->x);
    result.y = min2(v->y, w->y);
    result.z = min2(v->z, w->z);
    return result;
}

/* Returns a vector taking the maximum components of two vectors */
Vector3 vector3_max(const Vector3* v, const Vector3* w) 
{
    Vector3 result;
    result.x = max2(v->x, w->x);
    result.y = max2(v->y, w->y);
    result.z = max2(v->z, w->z);
    return result;
}

/* Returns the minimum value among the three components of a vector */
float vector3_returnMinValue(const Vector3* v) 
{
    return min2(min2(v->x, v->y), v->z);
}

/* Returns the maximum value among the three components of a vector */
float vector3_returnMaxValue(const Vector3* v) 
{
    return max3(v->x, v->y, v->z);
}
// Return the corresponding unit vector
Vector3 vector3_returnUnit(const Vector3* v) 
{
    float lengthVector = vector3_magnitude(v);

    if (lengthVector < FLT_EPSILON) {
        return *v;
    }

    // Compute and return the unit vector
    float lengthInv = 1.0f / lengthVector;
    Vector3 unitVector = { v->x * lengthInv, v->y * lengthInv, v->z * lengthInv };
    return unitVector;
}

// Return one unit orthogonal vector of the current vector
Vector3 vector3_returnUnitOrthogonalVector(const Vector3* v) {

    assert(vector3_magnitude(v) > FLT_EPSILON);

    // return the minimum element of the vector
    Vector3 vectorAbs = vector3_returnAbsoluteVector(v);
    int minElement;
    
    if (vectorAbs.x < vectorAbs.y && vectorAbs.x < vectorAbs.z) {
        minElement = 0;
    } else if (vectorAbs.y < vectorAbs.z) {
        minElement = 1;
    } else {
        minElement = 2;
    }

    Vector3 orthogonalVector;
    if (minElement == 0) {
        orthogonalVector.x = 0.0f;
        orthogonalVector.y = -v->z;
        orthogonalVector.z = v->y;
        float length = sqrtf(orthogonalVector.y * orthogonalVector.y + orthogonalVector.z * orthogonalVector.z);
        orthogonalVector.y /= length;
        orthogonalVector.z /= length;
    }
    else if (minElement == 1) {
        orthogonalVector.x = -v->z;
        orthogonalVector.y = 0.0f;
        orthogonalVector.z = v->x;
        float length = sqrtf(orthogonalVector.x * orthogonalVector.x + orthogonalVector.z * orthogonalVector.z);
        orthogonalVector.x /= length;
        orthogonalVector.z /= length;
    }
    else {
        orthogonalVector.x = -v->y;
        orthogonalVector.y = v->x;
        orthogonalVector.z = 0.0f;
        float length = sqrtf(orthogonalVector.x * orthogonalVector.x + orthogonalVector.y * orthogonalVector.y);
        orthogonalVector.x /= length;
        orthogonalVector.y /= length;
    }

    return orthogonalVector;
}

#endif
