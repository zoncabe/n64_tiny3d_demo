/**
 * @file
 *
 * Holds a ray.
 * This structure represents a 3D ray represented by two points.
 * The ray goes from point1 to point1 + maxFraction * (point2 - point1).
 * The points are specified in world-space coordinates.
 */

#ifndef RAY_H
#define RAY_H


// Ray structure
typedef struct {

    Vector3 point1;       /* First point of the ray (origin) in world-space */
    Vector3 point2;       /* Second point of the ray in world-space */
    float maxFraction;    /* Maximum fraction value */

} Ray;


/* Initializes the ray with given points and an optional max fraction value. */
void ray_set(Ray* ray, Vector3* p1, Vector3* p2, float maxFraction)
{
    vector3_copy(&ray->point1, p1);
    vector3_copy(&ray->point2, p2);
    ray->maxFraction = maxFraction;
}


/* Initializes the ray with given points and a default max fraction value of 1.0. */
void ray_setDefault(Ray* ray, Vector3* p1, Vector3* p2)
{
    ray_set(ray, p1, p2, 1.0f);
}

#endif
