/**
 * @file
 *
 * Holds an Axis Aligned Bounding Box (AABB).
 */

#ifndef AABB_H
#define AABB_H


typedef struct AABB {

    Vector3 minCoordinates;
    Vector3 maxCoordinates;

} AABB;


/* Function prototypes for AABB */

void aabb_init(AABB *aabb);
void aabb_setMin(AABB *aabb, const Vector3 *min);
void aabb_setMax(AABB *aabb, const Vector3 *max);

Vector3 aabb_getCenter(const AABB *aabb);
Vector3 aabb_returnMin(const AABB *aabb);
Vector3 aabb_returnMax(const AABB *aabb);
Vector3 aabb_getExtent(const AABB *aabb);

float aabb_getVolume(const AABB *aabb);

void aabb_scale(AABB *aabb, const Vector3 *scale);

void aabb_inflate(AABB *aabb, float dx, float dy, float dz);
void aabb_inflateWithPoint(AABB *aabb, const Vector3 *point);

void aabb_mergeWithAABB(AABB *aabb, const AABB *other);
AABB aabb_returnMerge(const AABB *aabb1, const AABB *aabb2);

void aabb_createAABBForTriangle(const Vector3 *trianglePoints, AABB *aabb);

bool aabb_containsAABB(const AABB *aabb1, const AABB *aabb2);
bool aabb_containsPoint(const AABB *aabb, const Vector3 *point);

bool aabb_collisionAABB(const AABB *aabb1, const AABB *aabb2);

bool aabb_collisionTriangle(const AABB *aabb, const Vector3 *trianglePoints);

bool aabb_rayIntersect(const AABB *aabb, const Vector3 *rayOrigin, const Vector3 *rayDirectionInverse, float rayMaxFraction);
bool aabb_raycast(const AABB *aabb, const Ray *ray, Vector3 *hitPoint);



/* Initializes the AABB with default values. */
void aabb_init(AABB *aabb) {
    vector3_init(&aabb->minCoordinates);
    vector3_init(&aabb->maxCoordinates);
}

/* Sets the minimum coordinates of the AABB. */
void aabb_setMin(AABB *aabb, const Vector3 *min) {
    aabb->minCoordinates = *min;
}

/* Sets the maximum coordinates of the AABB. */
void aabb_setMax(AABB *aabb, const Vector3 *max) {
    aabb->maxCoordinates = *max;
}

/* Returns the center of the AABB. */
Vector3 aabb_getCenter(const AABB *aabb) {
    Vector3 center = aabb->minCoordinates;
    vector3_add(&center, &aabb->maxCoordinates);
    vector3_scale(&center, 0.5f);
    return center;
}

/* Returns the minimum coordinates of the AABB. */
Vector3 aabb_returnMin(const AABB *aabb) {
    return aabb->minCoordinates;
}

/* Returns the maximum coordinates of the AABB. */
Vector3 aabb_returnMax(const AABB *aabb) {
    return aabb->maxCoordinates;
}

/* Returns the extent (size) of the AABB. */
Vector3 aabb_getExtent(const AABB *aabb) {
    Vector3 extent = aabb->maxCoordinates;
    vector3_subtract(&extent, &aabb->minCoordinates);
    return extent;
}

/* Inflates the AABB by the given dimensions. */
void aabb_inflate(AABB *aabb, float dx, float dy, float dz) {
    Vector3 delta = {dx, dy, dz};
    vector3_add(&aabb->maxCoordinates, &delta);
    vector3_subtract(&aabb->minCoordinates, &delta);
}

/* Inflates the AABB to include the given point if necessary. */
void aabb_inflateWithPoint(AABB *aabb, const Vector3 *point) {
    if (point->x > aabb->maxCoordinates.x) aabb->maxCoordinates.x = point->x;
    if (point->x < aabb->minCoordinates.x) aabb->minCoordinates.x = point->x;
    if (point->y > aabb->maxCoordinates.y) aabb->maxCoordinates.y = point->y;
    if (point->y < aabb->minCoordinates.y) aabb->minCoordinates.y = point->y;
    if (point->z > aabb->maxCoordinates.z) aabb->maxCoordinates.z = point->z;
    if (point->z < aabb->minCoordinates.z) aabb->minCoordinates.z = point->z;
}

/* Tests if two AABBs are colliding. */
bool aabb_collisionAABB(const AABB *aabb1, const AABB *aabb2) {
    if (aabb1->maxCoordinates.x < aabb2->minCoordinates.x || aabb2->maxCoordinates.x < aabb1->minCoordinates.x) return false;
    if (aabb1->maxCoordinates.y < aabb2->minCoordinates.y || aabb2->maxCoordinates.y < aabb1->minCoordinates.y) return false;
    if (aabb1->maxCoordinates.z < aabb2->minCoordinates.z || aabb2->maxCoordinates.z < aabb1->minCoordinates.z) return false;
    return true;
}

/* Returns the volume of the AABB. */
float aabb_getVolume(const AABB *aabb) {
    Vector3 diff = aabb->maxCoordinates;
    vector3_subtract(&diff, &aabb->minCoordinates);
    return diff.x * diff.y * diff.z;
}

/* Merges another AABB with the current one. */
void aabb_mergeWithAABB(AABB *aabb, const AABB *other) {
    aabb->minCoordinates = vector3_min(&aabb->minCoordinates, &other->minCoordinates);
    aabb->maxCoordinates = vector3_max(&aabb->maxCoordinates, &other->maxCoordinates);
}

/* Returns a new AABB that is the union of two AABBs. */
AABB aabb_returnMerge(const AABB *aabb1, const AABB *aabb2) {
    AABB result;
    result.minCoordinates = vector3_min(&aabb1->minCoordinates, &aabb2->minCoordinates);
    result.maxCoordinates = vector3_max(&aabb1->maxCoordinates, &aabb2->maxCoordinates);
    return result;
}


/* Tests if one AABB contains another AABB. */
bool aabb_containsAABB(const AABB *aabb1, const AABB *aabb2) {
    return (aabb1->minCoordinates.x <= aabb2->minCoordinates.x && aabb1->maxCoordinates.x >= aabb2->maxCoordinates.x &&
            aabb1->minCoordinates.y <= aabb2->minCoordinates.y && aabb1->maxCoordinates.y >= aabb2->maxCoordinates.y &&
            aabb1->minCoordinates.z <= aabb2->minCoordinates.z && aabb1->maxCoordinates.z >= aabb2->maxCoordinates.z);
}

/* Tests if the AABB contains a given point. */
bool aabb_containsPoint(const AABB *aabb, const Vector3 *point) {
    return (point->x >= aabb->minCoordinates.x && point->x <= aabb->maxCoordinates.x &&
            point->y >= aabb->minCoordinates.y && point->y <= aabb->maxCoordinates.y &&
            point->z >= aabb->minCoordinates.z && point->z <= aabb->maxCoordinates.z);
}

/* Tests if the AABB collides with a triangle. */
bool aabb_collisionTriangle(const AABB *aabb, const Vector3 *trianglePoints) {
    if (min3(trianglePoints[0].x, trianglePoints[1].x, trianglePoints[2].x) > aabb->maxCoordinates.x) return false;
    if (min3(trianglePoints[0].y, trianglePoints[1].y, trianglePoints[2].y) > aabb->maxCoordinates.y) return false;
    if (min3(trianglePoints[0].z, trianglePoints[1].z, trianglePoints[2].z) > aabb->maxCoordinates.z) return false;
    if (max3(trianglePoints[0].x, trianglePoints[1].x, trianglePoints[2].x) < aabb->minCoordinates.x) return false;
    if (max3(trianglePoints[0].y, trianglePoints[1].y, trianglePoints[2].y) < aabb->minCoordinates.y) return false;
    if (max3(trianglePoints[0].z, trianglePoints[1].z, trianglePoints[2].z) < aabb->minCoordinates.z) return false;
    return true;
}

/* Tests if a ray intersects the AABB. */
bool aabb_rayIntersect(const AABB *aabb, const Vector3 *rayOrigin, const Vector3 *rayDirectionInverse, float rayMaxFraction) 
{
    float t1 = (aabb->minCoordinates.x - rayOrigin->x) * rayDirectionInverse->x;
    float t2 = (aabb->maxCoordinates.x - rayOrigin->x) * rayDirectionInverse->x;
    float tMin = min2(t1, t2);
    float tMax = max2(t1, t2);
    tMax = min2(tMax, rayMaxFraction);

    float t1_y = (aabb->minCoordinates.y - rayOrigin->y) * rayDirectionInverse->y;
    float t2_y = (aabb->maxCoordinates.y - rayOrigin->y) * rayDirectionInverse->y;
    tMin = max2(tMin, min2(t1_y, t2_y));
    tMax = min2(tMax, max2(t1_y, t2_y));

    float t1_z = (aabb->minCoordinates.z - rayOrigin->z) * rayDirectionInverse->z;
    float t2_z = (aabb->maxCoordinates.z - rayOrigin->z) * rayDirectionInverse->z;
    tMin = max2(tMin, min2(t1_z, t2_z));
    tMax = min2(tMax, max2(t1_z, t2_z));

    return tMax >= max2(tMin, 0.0f);
}


/* Computes the intersection of a ray and the AABB. */
bool aabb_raycast(const AABB *aabb, const Ray *ray, Vector3 *hitPoint) 
{
    float tMin = 0.0f;
    float tMax = FLT_MAX;
    const float epsilon = 0.00001f;
    Vector3 rayDirection = ray->point2;
    vector3_subtract(&rayDirection, &ray->point1);

    // For x-axis
    if (fabs(rayDirection.x) < epsilon) {
        if (ray->point1.x < aabb->minCoordinates.x || ray->point1.x > aabb->maxCoordinates.x) return false;
    } else {
        float rayDirectionInverse = 1.0f / rayDirection.x;
        float t1 = (aabb->minCoordinates.x - ray->point1.x) * rayDirectionInverse;
        float t2 = (aabb->maxCoordinates.x - ray->point1.x) * rayDirectionInverse;
        if (t1 > t2) {
            float temp = t2;
            t2 = t1;
            t1 = temp;
        }
        tMin = max2(tMin, t1);
        tMax = min2(tMax, t2);
        if (tMin > tMax) return false;
    }

    // For y-axis
    if (fabs(rayDirection.y) < epsilon) {
        if (ray->point1.y < aabb->minCoordinates.y || ray->point1.y > aabb->maxCoordinates.y) return false;
    } else {
        float rayDirectionInverse = 1.0f / rayDirection.y;
        float t1 = (aabb->minCoordinates.y - ray->point1.y) * rayDirectionInverse;
        float t2 = (aabb->maxCoordinates.y - ray->point1.y) * rayDirectionInverse;
        if (t1 > t2) {
            float temp = t2;
            t2 = t1;
            t1 = temp;
        }
        tMin = max2(tMin, t1);
        tMax = min2(tMax, t2);
        if (tMin > tMax) return false;
    }

    // For z-axis
    if (fabs(rayDirection.z) < epsilon) {
        if (ray->point1.z < aabb->minCoordinates.z || ray->point1.z > aabb->maxCoordinates.z) return false;
    } else {
        float rayDirectionInverse = 1.0f / rayDirection.z;
        float t1 = (aabb->minCoordinates.z - ray->point1.z) * rayDirectionInverse;
        float t2 = (aabb->maxCoordinates.z - ray->point1.z) * rayDirectionInverse;
        if (t1 > t2) {
            float temp = t2;
            t2 = t1;
            t1 = temp;
        }
        tMin = max2(tMin, t1);
        tMax = min2(tMax, t2);
        if (tMin > tMax) return false;
    }

    Vector3 temp = rayDirection;
    vector3_scale(&temp, tMin);
    vector3_add(&temp, &ray->point1);
    *hitPoint = temp;

    return true;
}



/* Scales the AABB by the given factor. */
void aabb_scale(AABB *aabb, const Vector3 *scalar) {
    vector3_componentProduct(&aabb->minCoordinates, scalar);
    vector3_componentProduct(&aabb->maxCoordinates, scalar);
}

/* Creates an AABB for a given triangle. */
void aabb_createAABBForTriangle(const Vector3 *trianglePoints, AABB *aabb) {
    Vector3 minCoords = trianglePoints[0];
    Vector3 maxCoords = trianglePoints[0];
    if (trianglePoints[1].x < minCoords.x) minCoords.x = trianglePoints[1].x;
    if (trianglePoints[1].y < minCoords.y) minCoords.y = trianglePoints[1].y;
    if (trianglePoints[1].z < minCoords.z) minCoords.z = trianglePoints[1].z;
    if (trianglePoints[2].x < minCoords.x) minCoords.x = trianglePoints[2].x;
    if (trianglePoints[2].y < minCoords.y) minCoords.y = trianglePoints[2].y;
    if (trianglePoints[2].z < minCoords.z) minCoords.z = trianglePoints[2].z;
    if (trianglePoints[1].x > maxCoords.x) maxCoords.x = trianglePoints[1].x;
    if (trianglePoints[1].y > maxCoords.y) maxCoords.y = trianglePoints[1].y;
    if (trianglePoints[1].z > maxCoords.z) maxCoords.z = trianglePoints[1].z;
    if (trianglePoints[2].x > maxCoords.x) maxCoords.x = trianglePoints[2].x;
    if (trianglePoints[2].y > maxCoords.y) maxCoords.y = trianglePoints[2].y;
    if (trianglePoints[2].z > maxCoords.z) maxCoords.z = trianglePoints[2].z;
    aabb_setMin(aabb, &minCoords);
    aabb_setMax(aabb, &maxCoords);
}

#endif
