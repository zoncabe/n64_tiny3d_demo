#ifndef COLLISION_H
#define COLLISION_H

#include "physics_core.h"

// structures


typedef struct {
    Vector3 center;
    float radius;
} Sphere;

typedef struct {
    Vector3 min;
    Vector3 max;
    Vector3 center;
} AABB;

typedef struct {
    Vector3 size;
    Vector3 center;
    Vector3 rotation;
} OBB;


// function prototypes

void project_polygon(Vector3 axis, Vector3 corners[8], float* min, float* max);

int intervals_overlap(float minA, float maxA, float minB, float maxB);

int test_axis(Vector3 axis, Vector3 obbCorners[8], Vector3 aabbCorners[8]);

void point_global_to_obb_space(OBB* obb, Vector3 global_point, Vector3* local_point);
void point_obb_to_global_space(OBB* obb, Vector3 local_point, Vector3* global_point);

void get_aabb_corners(AABB aabb, Vector3 corners[8]);
void get_obb_corners(OBB obb, Vector3 corners[8]);

void closest_point_on_segment_to_point(Vector3 line_start, Vector3 line_end, Vector3 point, Vector3* closest);
float squared_distance_point_to_segment(Vector3 point, Vector3 segment_start, Vector3 segment_end);

void reset_collision_data(Entity* entity);
int collision_sphere_sphere(Sphere sphere1, Sphere sphere2);
int collision_aabb_aabb(AABB aabb1, AABB aabb2);
int collision_sphere_aabb(Entity* entity, Sphere sphere, AABB aabb);
int collision_capsule_sphere(Capsule capsule, Sphere sphere);
int collision_sphere_obb(Entity* entity, Sphere sphere, OBB obb);
int collision_obb_aabb(OBB obb, AABB aabb);
int collision_cylinder_aabb(Entity* entity, Cylinder cylinder, AABB aabb);
int collision_cylinder_obb(Entity* entity, Cylinder cylinder, OBB obb);
int collision_capsule_aabb(Entity* entity, AABB aabb);
int collision_capsule_obb(Entity* entity, OBB obb);
int collision_ray_aabb(Vector3 origin, Vector3 target, AABB aabb, Vector3* hit_point);


/* project_polygon
projects a 3D polygon onto an axis */

void project_polygon(Vector3 axis, Vector3 corners[8], float* min, float* max) 
{
    *min = *max = vector3_scalarProduct(&corners[0], &axis);
    for (int i = 1; i < 8; i++) {
        float projection = vector3_scalarProduct(&corners[i], &axis);
        if (projection < *min) *min = projection;
        if (projection > *max) *max = projection;
    }
}


/* intervals_overlap
checks if two scalar intervals overlap */

int intervals_overlap(float minA, float maxA, float minB, float maxB) 
{
    return minA <= maxB && minB <= maxA;
}


/* test_axis
tests if projections of two polygons on an axis overlap */

int test_axis(Vector3 axis, Vector3 obbCorners[8], Vector3 aabbCorners[8])
{
    float minOBB, maxOBB;
    project_polygon(axis, obbCorners, &minOBB, &maxOBB);

    float minAABB, maxAABB;
    project_polygon(axis, aabbCorners, &minAABB, &maxAABB);

    return intervals_overlap(minOBB, maxOBB, minAABB, maxAABB);
}


/* point_global_to_obb_space
transforms a point from global to OBB's local space using Euler angles */

void point_global_to_obb_space(OBB* obb, Vector3 global_point, Vector3* local_point) 
{
    // Translate point by the inverse of OBB's center
    *local_point = vector3_difference(&global_point, &obb->center);

    // Rotate the translated point by the inverse of OBB's rotation
    Vector3 inverse_rotation = {-obb->rotation.x, -obb->rotation.y, -obb->rotation.z};
    rotate_point(local_point, &inverse_rotation);
}


/* point_obb_to_global_space
converts a point from OBB's local space to global space using Euler angles */

void point_obb_to_global_space(OBB* obb, Vector3 local_point, Vector3* global_point) 
{
    // Apply rotation to the local point to get it in the global space orientation
    rotate_point(&local_point, &obb->rotation);

    // Translate the rotated point by adding the OBB's center
    *global_point = vector3_sum(&local_point, &obb->center);
}


/* get_aabb_corners
calculates the corners of an AABB */

void get_aabb_corners(AABB aabb, Vector3 corners[8]) 
{
    vector3_set(&corners[0], aabb.min.x, aabb.min.y, aabb.min.z);
    vector3_set(&corners[1], aabb.max.x, aabb.min.y, aabb.min.z);
    vector3_set(&corners[2], aabb.max.x, aabb.max.y, aabb.min.z);
    vector3_set(&corners[3], aabb.min.x, aabb.max.y, aabb.min.z);
    vector3_set(&corners[4], aabb.min.x, aabb.min.y, aabb.max.z);
    vector3_set(&corners[5], aabb.max.x, aabb.min.y, aabb.max.z);
    vector3_set(&corners[6], aabb.max.x, aabb.max.y, aabb.max.z);
    vector3_set(&corners[7], aabb.min.x, aabb.max.y, aabb.max.z);
}


/* get_obb_corners
calculates the corners of an OBB */

void get_obb_corners(OBB obb, Vector3 corners[8])
{
    // calculates corners as if no rotation
    Vector3 localCorners[8] = {
        {-obb.size.x / 2, -obb.size.y / 2, -obb.size.z / 2},
        { obb.size.x / 2, -obb.size.y / 2, -obb.size.z / 2},
        { obb.size.x / 2,  obb.size.y / 2, -obb.size.z / 2},
        {-obb.size.x / 2,  obb.size.y / 2, -obb.size.z / 2},
        {-obb.size.x / 2, -obb.size.y / 2,  obb.size.z / 2},
        { obb.size.x / 2, -obb.size.y / 2,  obb.size.z / 2},
        { obb.size.x / 2,  obb.size.y / 2,  obb.size.z / 2},
        {-obb.size.x / 2,  obb.size.y / 2,  obb.size.z / 2}
    };

    // then rotates and translates each one
    for (int i = 0; i < 8; i++) {
        rotate_point(&localCorners[i], &obb.rotation);
        corners[i] = vector3_sum(&localCorners[i], &obb.center);
    }
}


/* closest_point_on_segment_to_point
finds the closest point on a line segment to a point */

void closest_point_on_segment_to_point(Vector3 line_start, Vector3 line_end, Vector3 point, Vector3* closest)
{
    Vector3 line_vector = vector3_difference(&line_end, &line_start);
    Vector3 point_vector = vector3_difference(&point, &line_start);

    float line_length_squared = vector3_squaredMagnitude(&line_vector);
    float t = clamp(vector3_scalarProduct(&point_vector, &line_vector) / line_length_squared, 0.0f, 1.0f);

    *closest = vector3_sum(&line_start, &vector3_scale(&line_vector, t));
}


/* squared_distance_point_to_segment
calculates the squared distance from a point to a line segment */

float squared_distance_point_to_segment(Vector3 point, Vector3 segment_start, Vector3 segment_end)
{
    Vector3 segment_vector = vector3_difference(&segment_end, &segment_start);
    Vector3 point_vector = vector3_difference(&point, &segment_start);

    float segment_length_squared = vector3_squaredMagnitude(&segment_vector);
    float t = clamp(vector3_scalarProduct(&point_vector, &segment_vector) / segment_length_squared, 0.0f, 1.0f);

    Vector3 closest = {
        segment_start.x + t * segment_vector.x,
        segment_start.y + t * segment_vector.y,
        segment_start.z + t * segment_vector.z
    };

    return vector3_squaredMagnitude(&vector3_difference(&point, &closest));
}


/* reset_collision_data
resets collision data in an entity */

void reset_collision_data(Entity* entity)
{
    vector3_init(&entity->collision.normal);
    vector3_init(&entity->collision.point);
}


/* collision_sphere_sphere
detects collision between 2 spheres */

int collision_sphere_sphere(Sphere sphere1, Sphere sphere2) 
{
    float distance_squared = vector3_squaredMagnitude(&vector3_difference(&sphere1.center, &sphere2.center));
    float radius_sum = sphere1.radius + sphere2.radius;
    return distance_squared <= radius_sum * radius_sum ? 1 : 0;
}


/* collision_aabb_aabb
detects collision between 2 boxes */

int collision_aabb_aabb(AABB aabb1, AABB aabb2) 
{
    if (aabb1.max.x < aabb2.min.x || aabb1.min.x > aabb2.max.x)
        return 0;

    if (aabb1.max.y < aabb2.min.y || aabb1.min.y > aabb2.max.y)
        return 0;

    if (aabb1.max.z < aabb2.min.z || aabb1.min.z > aabb2.max.z)
        return 0;

    return 1;
}


/* collision_sphere_aabb
detects collision between a sphere and a box */

int collision_sphere_aabb(Entity* entity, Sphere sphere, AABB aabb) 
{
    // Find the closest point on the AABB to the sphere's center using clamp
    Vector3 closest_point = {
        clamp(sphere.center.x, aabb.min.x, aabb.max.x),
        clamp(sphere.center.y, aabb.min.y, aabb.max.y),
        clamp(sphere.center.z, aabb.min.z, aabb.max.z)
    };

    // Calculate the squared distance from this point to the sphere's center
    float distance_squared = vector3_squaredMagnitude(&vector3_difference(&sphere.center, &closest_point));

    // Check if the distance is less than or equal to the sphere's radius squared
    if (distance_squared <= sphere.radius * sphere.radius) {
        // Assign the closest point to the entity's collision point
        vector3_copy(&entity->collision.point, &closest_point);
        return 1; // Collision detected
    } 
    
    return 0; // No collision
}


/* collision_capsule_sphere
detects collision between a capsule and a sphere */

int collision_capsule_sphere(Capsule capsule, Sphere sphere) 
{
    Vector3 capsule_vector = vector3_difference(&capsule.upper_point, &capsule.lower_point);
    Vector3 sphere_to_start = vector3_difference(&sphere.center, &capsule.lower_point);

    float dot = vector3_scalarProduct(&sphere_to_start, &capsule_vector);
    float length_squared = vector3_squaredMagnitude(&capsule_vector);

    float t = clamp(dot / length_squared, 0.0f, 1.0f);
    Vector3 closest_point = {
        capsule.lower_point.x + t * capsule_vector.x,
        capsule.lower_point.y + t * capsule_vector.y,
        capsule.lower_point.z + t * capsule_vector.z
    };

    float distance_squared = vector3_squaredMagnitude(&vector3_difference(&sphere.center, &closest_point));
    float radius_sum = capsule.radius + sphere.radius;
    return distance_squared <= radius_sum * radius_sum;
}


/* collision_sphere_obb
detects collision between an OBB and a sphere */

int collision_sphere_obb(Entity* entity, Sphere sphere, OBB obb) 
{
    Vector3 local_sphere_center;
    point_global_to_obb_space(&obb, sphere.center, &local_sphere_center);

    // Find the closest point on the OBB to the sphere's center in OBB's local space
    Vector3 closest_point = {
        clamp(local_sphere_center.x, -obb.size.x / 2, obb.size.x / 2),
        clamp(local_sphere_center.y, -obb.size.y / 2, obb.size.y / 2),
        clamp(local_sphere_center.z, -obb.size.z / 2, obb.size.z / 2),
    };

    // Calculate the squared distance from this point to the sphere's center in local space
    float distance_squared = vector3_squaredMagnitude(&vector3_difference(&local_sphere_center, &closest_point));

    // Check if the distance is less than or equal to the sphere's radius squared
    if (distance_squared <= sphere.radius * sphere.radius) {
        // Convert the closest point back to global space before assigning it
        Vector3 global_closest_point;
        point_obb_to_global_space(&obb, closest_point, &global_closest_point);
        
        // Assign the global closest point to the entity's collision point
        vector3_copy(&entity->collision.point, &global_closest_point);
        return 1; // Collision detected
    } 
    
    return 0; // No collision
}


/* collision_obb_aabb
detects collision between an OBB and an AABB */

int collision_obb_aabb(OBB obb, AABB aabb) {
    Vector3 obbCorners[8], aabbCorners[8];

    get_obb_corners(obb, obbCorners);
    get_aabb_corners(aabb, aabbCorners);

    // AABB axes
    Vector3 aabbAxes[3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    // Rotated OBB axes
    Vector3 obbAxes[3];

    for (int i = 0; i < 3; i++) {
        Vector3 axis = {0, 0, 0};
        axis[i] = 1;
        rotate_point(&axis, &obb.rotation);
        obbAxes[i].x = axis.x;
        obbAxes[i].y = axis.y;
        obbAxes[i].z = axis.z;
    }

    // Collision checks
    for (int i = 0; i < 3; i++) {
        if (!test_axis(aabbAxes[i], obbCorners, aabbCorners)) return 0;
        if (!test_axis(obbAxes[i], obbCorners, aabbCorners)) return 0;
    }

    // Check collisions on cross products of OBB and AABB axes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Vector3 crossAxis;
            vector3_vectorProductUpdate(&crossAxis, &aabbAxes[i], &obbAxes[j]);
            if (!test_axis(crossAxis, obbCorners, aabbCorners)) return 0;
        }
    }

    return 1; // Collision detected
}


/* collision_cylinder_aabb
Detects collision between a cylinder and an AABB */

int collision_cylinder_aabb(Entity* entity, Cylinder cylinder, AABB aabb) 
{
    // Calculate the closest point on AABB to the cylinder's base center
    Vector3 closest_point = {
        clamp(cylinder.base_center.x, aabb.min.x, aabb.max.x),
        clamp(cylinder.base_center.y, aabb.min.y, aabb.max.y),
        clamp(cylinder.base_center.z, aabb.min.z, aabb.max.z)
    };

    // Check horizontal collision
    float horizontal_distance_squared = vector3_squaredMagnitude(&vector3_difference(&closest_point, &cylinder.base_center));
    if (horizontal_distance_squared > (cylinder.radius * cylinder.radius))
        return 0;  // No horizontal collision

    // Check vertical collision
    if (closest_point.z < cylinder.base_center.z || closest_point.z > cylinder.base_center.z + cylinder.height)
        return 0;  // No vertical collision

    vector3_copy(&entity->collision.point, &closest_point);
    
    return 1; // Collision detected
}


/* collision_cylinder_obb
Detects collision between a cylinder and an OBB */

int collision_cylinder_obb(Entity* entity, Cylinder cylinder, OBB obb) 
{
    // Transform cylinder base center to OBB local space
    Vector3 local_base_center;
    point_global_to_obb_space(&obb, cylinder.base_center, &local_base_center);

    // Calculate the closest point in OBB local space
    Vector3 closest_point = {
        clamp(local_base_center.x, -obb.size.x / 2, obb.size.x / 2),
        clamp(local_base_center.y, -obb.size.y / 2, obb.size.y / 2),
        clamp(local_base_center.z, -obb.size.z / 2, obb.size.z / 2)
    };

    // Check horizontal collision
    float horizontal_distance_squared = vector3_squaredMagnitude(&vector3_difference(&closest_point, &local_base_center));
    if (horizontal_distance_squared > (cylinder.radius * cylinder.radius))
        return 0;  // No horizontal collision

    // Check vertical collision
    if (closest_point.z < local_base_center.z || closest_point.z > local_base_center.z + cylinder.height)
        return 0;  // No vertical collision

    // Convert the closest point back to global space
    Vector3 global_closest_point;
    point_obb_to_global_space(&obb, closest_point, &global_closest_point);
    vector3_copy(&entity->collision.point, &global_closest_point);

    return 1; // Collision detected
}


/* collision_capsule_aabb
Detects collision between a capsule and an AABB */

int collision_capsule_aabb(Entity* entity, AABB aabb)
{
    // Check collision with spheres at the ends of the capsule
    Sphere lower_sphere = {.center = {entity->capsule.lower_point.x, entity->capsule.lower_point.y, entity->capsule.lower_point.z}, .radius = entity->capsule.radius};
    Sphere upper_sphere = {.center = {entity->capsule.upper_point.x, entity->capsule.upper_point.y, entity->capsule.upper_point.z}, .radius = entity->capsule.radius};

    if (collision_sphere_aabb(entity, lower_sphere, aabb) || collision_sphere_aabb(entity, upper_sphere, aabb))
        return 1;  // Collision with one of the end spheres

    // Check collision with the cylindrical body
    Cylinder cylinder = {
        .base_center = {entity->capsule.lower_point.x, entity->capsule.lower_point.y, entity->capsule.lower_point.z},
        .height = vector3_magnitude(&vector3_difference(&entity->capsule.upper_point, &entity->capsule.lower_point)),
        .radius = entity->capsule.radius
    };

    return collision_cylinder_aabb(entity, cylinder, aabb);
}


/* collision_capsule_obb
Detects collision between a capsule and an OBB */

int collision_capsule_obb(Entity* entity, OBB obb)
{
    // Check collision with spheres at the ends of the capsule
    Sphere lower_sphere = {.center = {entity->capsule.lower_point.x, entity->capsule.lower_point.y, entity->capsule.lower_point.z}, .radius = entity->capsule.radius};
    Sphere upper_sphere = {.center = {entity->capsule.upper_point.x, entity->capsule.upper_point.y, entity->capsule.upper_point.z}, .radius = entity->capsule.radius};

    if (collision_sphere_obb(entity, lower_sphere, obb) || collision_sphere_obb(entity, upper_sphere, obb))
        return 1;  // Collision with one of the end spheres

    // Check collision with the cylindrical body
    Cylinder cylinder = {
        .base_center = {entity->capsule.lower_point.x, entity->capsule.lower_point.y, entity->capsule.lower_point.z},
        .height = vector3_magnitude(&vector3_difference(&entity->capsule.upper_point, &entity->capsule.lower_point)),
        .radius = entity->capsule.radius
    };

    return collision_cylinder_obb(entity, cylinder, obb);
}


/* collision_ray_aabb
checks if a ray intersects with an AABB and calculates the distance of the intersection.
returns 1 if there is an intersection, 0 otherwise.
additionally calculates the precise hit point if an intersection is detected. */

int collision_ray_aabb(Vector3 origin, Vector3 target, AABB aabb, Vector3* hit_point)
{
    Vector3 dir = vector3_difference(&target, &origin);
    float len = vector3_magnitude(&dir);
    vector3_scaleUpdate(&dir, 1.0f / len);

    float t1 = (aabb.min.x - origin.x) / dir.x;
    float t2 = (aabb.max.x - origin.x) / dir.x;
    float t3 = (aabb.min.y - origin.y) / dir.y;
    float t4 = (aabb.max.y - origin.y) / dir.y;
    float t5 = (aabb.min.z - origin.z) / dir.z;
    float t6 = (aabb.max.z - origin.z) / dir.z;

    float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    if (tmax < 0 || tmin > tmax) {
        return 0;int collision_ray_aabb(Vector3 origin, Vector3 target, AABB aabb, Vector3* hit_point)
{
    Vector3 dir = vector3_difference(&target, &origin);
    float len = vector3_magnitude(&dir);
    vector3_scaleUpdate(&dir, 1.0f / len);

    float t1 = (aabb.min.x - origin.x) / dir.x;
    float t2 = (aabb.max.x - origin.x) / dir.x;
    float t3 = (aabb.min.y - origin.y) / dir.y;
    float t4 = (aabb.max.y - origin.y) / dir.y;
    float t5 = (aabb.min.z - origin.z) / dir.z;
    float t6 = (aabb.max.z - origin.z) / dir.z;

    float tmin = fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6));
    float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    if (tmax < 0 || tmin > tmax) {
        return 0;
    }

    float t = (tmin < 0.0f) ? tmax : tmin;
    vector3_copy(hit_point, &origin);
    vector3_addScaledVector(hit_point, &dir, t * len);
    
    return 1;
}
    }

    float t = (tmin < 0.0f) ? tmax : tmin;
    *hit_point = vector3_sum(&origin, &vector3_scale(&dir, t * len));
    
    return 1;
}

#endif
