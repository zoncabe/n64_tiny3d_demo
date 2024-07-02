#ifndef ACTOR_COLLISION_RESPONSE_H
#define ACTOR_COLLISION_RESPONSE_H

/* COLLISION_RESPONSE_H
here are all the structures and functions prototypes that involve the collision response */

void set_collision_plane_aabb(Entity* entity, AABB* aabb);
void set_collision_plane_obb(Entity* entity, OBB* obb) ;


void set_capsule_position(Entity* entity, Plane plane);
void collide_and_slide(Entity* entity);
void set_collission_response(Entity* entity, AABB *aabb, OBB *obb);


/* set_collision_plane_aabb
Computes the collision normal for an AABB collision and stores it in the entity's collision normal */

void set_collision_plane_aabb(Entity* entity, AABB* aabb)
{
    null_vector(entity->collision.normal); // Initialize the normal vector to zero

    float distance[6]; // Distances from the entity collision point to each face of the AABB

    // Calculate distance from the collision point to each AABB face
    distance[0] = fabs(entity->collision.point[0] - aabb->min[0]); // Left face
    distance[1] = fabs(entity->collision.point[0] - aabb->max[0]); // Right face
    distance[2] = fabs(entity->collision.point[1] - aabb->min[1]); // Bottom face
    distance[3] = fabs(entity->collision.point[1] - aabb->max[1]); // Top face
    distance[4] = fabs(entity->collision.point[2] - aabb->min[2]); // Front face
    distance[5] = fabs(entity->collision.point[2] - aabb->max[2]); // Back face

    // Find the minimum distance and its corresponding face
    float min_distance = FLT_MAX;
    int face_index = -1;

    for (int i = 0; i < 6; ++i) {
        if (distance[i] < min_distance) {
            min_distance = distance[i];
            face_index = i;
        }
    }

    // Assign the normal based on the closest face and calculate the bottom-left point of the face
    switch (face_index) {
        case 0: entity->collision.normal[0] = -1; break;
        case 1: entity->collision.normal[0] = 1; break;
        case 2: entity->collision.normal[1] = -1; break;
        case 3: entity->collision.normal[1] = 1; break;
        case 4: entity->collision.normal[2] = -1; break;
        case 5: entity->collision.normal[2] = 1; break;
    }

    if (entity->collision.normal[0] != 0) {

        if (entity->position[1] < aabb->min[1] + 1 || entity->position[1] > aabb->max[1] - 1 || entity->position[2] > aabb->max[2] - entity->capsule.radius) {

            set_vector(entity->collision.normal, entity->collision.point, entity->capsule.lower_point); 
            normalize_vector(entity->collision.normal);
        }

    } 
    
    else if (entity->collision.normal[1] != 0) {

        if (entity->position[0] < aabb->min[0] + 1 || entity->position[0] > aabb->max[0] - 1 || entity->position[2] > aabb->max[2] - entity->capsule.radius) {

            set_vector(entity->collision.normal, entity->collision.point, entity->capsule.lower_point);
            normalize_vector(entity->collision.normal);
        }
    } 
    
    else if (entity->collision.normal[2] > 0) {

        entity->grounding_height = entity->collision.point[2];

        if ((entity->position[0] < aabb->min[0] + 1 || entity->position[0] > aabb->max[0] - 1) 
            && (entity->position[1] < aabb->min[1] + 1 || entity->position[1] > aabb->max[1] - 1)) {

            set_vector(entity->collision.normal, entity->collision.point, entity->capsule.lower_point);
            normalize_vector(entity->collision.normal);
        }
    }

    else if (entity->collision.normal[2] < 0) {


        if ((entity->position[0] < aabb->min[0] + 1 || entity->position[0] > aabb->max[0] - 1) 
            && (entity->position[1] < aabb->min[1] + 1 || entity->position[1] > aabb->max[1] - 1)) {

            set_vector(entity->collision.normal, entity->collision.point, entity->capsule.lower_point);
            normalize_vector(entity->collision.normal);
        }
    }


    set_point(aabb->plane.normal, entity->collision.normal);
    set_point(aabb->plane.point, entity->collision.point);

    aabb->plane.displacement = dot_product(aabb->plane.normal, aabb->plane.point);
}


/* set_collision_plane_obb
Computes the collision normal for an OBB collision and stores it in the entity's collision normal */

void set_collision_plane_obb(Entity* entity, OBB* obb) 
{
    float distance[6]; // Distances from the entity collision point to each face of the AABB

    // Convert collision point to OBB's local space
    float local_collision_point[3], 
          local_collision_normal[3], 
          local_plane_point[3], 
          local_entity_position[3],
          local_capsule_start[3];

    null_vector(local_collision_normal); // Normal vector initialized to zero

    point_global_to_obb_space(obb, entity->collision.point, local_collision_point);
    point_global_to_obb_space(obb, entity->position, local_entity_position);
    point_global_to_obb_space(obb, entity->capsule.lower_point, local_capsule_start);

    // Calculate distance from the collision point to each AABB face
    distance[0] = fabs(local_collision_point[0] + obb->size[0] / 2);
    distance[1] = fabs(local_collision_point[0] - obb->size[0] / 2);
    distance[2] = fabs(local_collision_point[1] + obb->size[1] / 2);
    distance[3] = fabs(local_collision_point[1] - obb->size[1] / 2);
    distance[4] = fabs(local_collision_point[2] + obb->size[2] / 2);
    distance[5] = fabs(local_collision_point[2] - obb->size[2] / 2);

    // Find the minimum distance and its corresponding face
    float min_distance = FLT_MAX;
    int face_index = -1;
    for (int i = 0; i < 6; ++i) {
        if (distance[i] < min_distance) {
            min_distance = distance[i];
            face_index = i;
        }
    }

    // Assign the normal based on the closest face
    switch (face_index) {
        case 0: local_collision_normal[0] = -1; break;
        case 1: local_collision_normal[0] = 1; break; 
        case 2: local_collision_normal[1] = -1; break;
        case 3: local_collision_normal[1] = 1; break; 
        case 4: local_collision_normal[2] = -1; break;
        case 5: local_collision_normal[2] = 1; break; 
    }

/*
    if (local_collision_normal[0] != 0) {

        if ((local_entity_position[1] <  (-obb->size[1] / 2 ) + 1 || local_entity_position[1] > (obb->size[1] / 2) - 1)
            && (local_entity_position[0]  <  (-obb->size[2] / 2) + 1 || local_entity_position[0] > (obb->size[2] / 2) - 1)) {

            set_vector(local_collision_normal, local_collision_point, local_capsule_start); 
            normalize_vector(local_collision_normal);
        }
    } 
    
    else if (local_collision_normal[1] != 0) {

        if ((local_entity_position[0]  <  (-obb->size[0] / 2) + 1 || local_entity_position[0] > (obb->size[0] / 2) - 1) 
            && (local_entity_position[0]  <  (-obb->size[2] / 2) + 1 || local_entity_position[0] > (obb->size[2] / 2) - 1)){

            set_vector(local_collision_normal, local_collision_point, local_capsule_start);
            normalize_vector(local_collision_normal);
        }
    } 
    
    else if (local_collision_normal[2] > 0) {
        
        entity->grounding_height = entity->collision.point[2];

        if ((local_entity_position[0]  <  (-obb->size[0] / 2) + 1 || local_entity_position[0] > (obb->size[0] / 2) - 1)
            && (local_entity_position[1] <  (-obb->size[1] / 2 ) + 1 || local_entity_position[1] > (obb->size[1] / 2) - 1)){

            set_vector(local_collision_normal, local_collision_point, local_capsule_start);
            normalize_vector(local_collision_normal);

        }
    }
    else if (local_collision_normal[2] < 0) {
        
        entity->grounding_height = entity->collision.point[2];

        if ((local_entity_position[0]  <  (-obb->size[0] / 2) + 1 || local_entity_position[0] > (obb->size[0] / 2) - 1)
            && (local_entity_position[1] <  (-obb->size[1] / 2 ) + 1 || local_entity_position[1] > (obb->size[1] / 2) - 1)){

            local_capsule_start[2] += 60;

            set_vector(local_collision_normal, local_collision_point, local_capsule_start);
            normalize_vector(local_collision_normal);

        }
    }
*/

    rotate_point(local_collision_normal, obb->rotation);
    
    set_point(entity->collision.normal, local_collision_normal);

    set_point(obb->plane.normal, local_collision_normal);
    set_point(obb->plane.point, entity->collision.point);

    obb->plane.displacement = dot_product(obb->plane.normal, obb->plane.point);
}


void set_capsule_position(Entity* entity, Plane plane)
{
    if (entity->collision.normal[2] < 0) {

        entity->capsule.previous_position[2] += entity->capsule.height;
        entity->capsule.position[2] += entity->capsule.height;
    }

    float intended_displacement[3];
    set_vector(intended_displacement, entity->capsule.previous_position, entity->capsule.position);
    
    // Normalize the intended_displacement vector
    normalize_vector(intended_displacement);
    
    // set a displacement for a plane parallel to the original, at radius distance on the normal's direction
    float adjusted_displacement = plane.displacement + entity->capsule.radius;

    // Distance from the initial point to the adjusted plane
    float distance_from_plane = -(dot_product(plane.normal, entity->capsule.previous_position) - adjusted_displacement);
    
    // Calculate the denominator to prevent division by zero
    float denominator = dot_product(plane.normal, intended_displacement);
    
    // Prevent the case where t is -inf or NaN using a small threshold instead of FLT_MIN
    if (fabs(denominator) < 1e-6) { // FLT_MIN could be used, but 1e-6 is more practical for this check
        // The intended_displacement vector is parallel to the plane, handle accordingly
        return; // Choose how to handle this case
    }
    
    // t for the intersection with the plane
    float t = distance_from_plane / denominator;
    
    // Exact intersection point on the plane without adjusting for the radius
    for (int i = 0; i < 3; i++) {
        entity->capsule.previous_position[i] = entity->capsule.previous_position[i] + t * intended_displacement[i];
    }
    
    // Adjust the collision point by the capsule's radius perpendicular to the plane
    for (int i = 0; i < 3; i++) {
        entity->collision.point[i] = entity->capsule.previous_position[i] + plane.normal[i] * entity->capsule.radius;
    }

    if (entity->collision.normal[2] < 0) {

        entity->capsule.previous_position[2] -= entity->capsule.height;
        entity->capsule.position[2] -= entity->capsule.height;
    }
}


void collide_and_slide(Entity* entity)
{
    float intended_displacement[3];   

    set_vector(intended_displacement, entity->capsule.previous_position, entity->capsule.position);

    float dotProduct = dot_product(intended_displacement, entity->collision.normal);
    
    float slideVector[3] = {
        intended_displacement[0] - dotProduct * entity->collision.normal[0],
        intended_displacement[1] - dotProduct * entity->collision.normal[1],
        intended_displacement[2] - dotProduct * entity->collision.normal[2]
    };
    
    entity->capsule.position[0] = entity->capsule.previous_position[0] + slideVector[0];
    entity->capsule.position[1] = entity->capsule.previous_position[1] + slideVector[1];
    entity->capsule.position[2] = entity->capsule.previous_position[2] + slideVector[2];
}

void apply_response(Entity* entity)
{
    entity->position[0] = entity->capsule.position[0];
    entity->position[1] = entity->capsule.position[1];
    entity->position[2] = entity->capsule.position[2] - entity->capsule.radius;
}


void set_collission_response(Entity* entity, AABB* aabb, OBB* obb)
{
    for (int i = 0; i < 2; i++) {

        for (int v = 0; v < AABB_COUNT; v++) {

            if(collision_capsule_aabb(entity, aabb[v])){
                    set_collision_plane_aabb(entity, &aabb[v]);
                    set_capsule_position(entity, aabb[v].plane);
                    collide_and_slide(entity);
                    apply_response(entity);
            }
        }

        for (int v = 0; v < OBB_COUNT; v++) {

            if(collision_capsule_obb(entity, obb[v])){
                    set_collision_plane_obb(entity, &obb[v]);
                    set_capsule_position(entity, obb[v].plane);
                    collide_and_slide(entity);
                    apply_response(entity);
            }
        }
    }

    if (entity->collision.normal[0] == 0 && entity->collision.normal[1] == 0 && entity->collision.normal[2] == 0 && entity->state != JUMP){

        entity->grounding_height = -FLT_MAX;
        set_entity_state(entity, FALL);
    }

}


#endif