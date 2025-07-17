#ifndef ACTOR_COLLISION_RESPONSE_H
#define ACTOR_COLLISION_RESPONSE_H     


void actorCollision_pushTowardsNormal(Actor* actor, ActorContact* contact)
{
    // Calculate the necessary displacement vector in the direction of the contact normal
    Vector3 displacement_vector = vector3_returnScaled(&contact->data.normal, -contact->data.penetration);

    // Apply the displacement to the actor's position
    vector3_subtract(&actor->body.position, &displacement_vector);
}

// lighter solution to use together with the push towards normal function. gives almost same results, for now i will use the correct algorithm
void actorCollision_projectAcceleration(Actor* actor, ActorContact* contact)
{
    float t = vector3_returnDotProduct(&actor->body.acceleration, &contact->data.normal);
    vector3_addScaledVector(&actor->body.acceleration, &contact->data.normal, -t);
}

void actorCollision_projectVelocity(Actor* actor, ActorContact* contact)
{
    float t = vector3_returnDotProduct(&actor->body.velocity, &contact->data.normal);
    vector3_addScaledVector(&actor->body.velocity, &contact->data.normal, -t);
}

void actorCollision_solvePenetration(Actor* actor, ActorContact* contact, ActorCollider* collider)
{
    // Normalize the actor's velocity vector
    Vector3 velocity_normal = vector3_returnNormalized(&actor->body.velocity);

    // Calculate the intersection of the ray (contact point + velocity normal) with the plane
    float denominator = vector3_returnDotProduct(&velocity_normal, &contact->data.normal);
    float numerator = contact->displacement + collider->body.radius - vector3_returnDotProduct(&contact->data.point, &contact->data.normal);

    float t;
    if (fabs(denominator) > 0.0001f) t = numerator / denominator;
    else return;

    Vector3 axis_closest_at_contact = contact->data.point;
    vector3_addScaledVector(&axis_closest_at_contact, &velocity_normal, t);

    Vector3 displacement_vector = axis_closest_at_contact;
    vector3_subtract(&displacement_vector, &contact->axis_closest_to_contact);

    contact->velocity_penetration = displacement_vector;
    vector3_invert(&contact->velocity_penetration);

    vector3_add(&actor->body.position, &displacement_vector);
}

void actorCollision_collideAndSlide(Actor* actor, ActorContact* contact)
{
    float t = vector3_returnDotProduct(&contact->velocity_penetration, &contact->data.normal);
    Vector3 projection = contact->velocity_penetration;
    vector3_addScaledVector(&projection, &contact->data.normal, -t);
    
    vector3_add(&actor->body.position, &projection);
}

void actorCollision_setGroundResponse(Actor* actor)
{
    actor->grounded = true;
    actor->body.acceleration.z = 0;
    actor->body.velocity.z = 0;
    actor->grounding_height = actor->body.position.z;
    actor_setState(actor, actor->previous_state);
}

void actorCollision_setCeilingResponse(Actor* actor, ActorContact* contact)
{   
    if (actor->body.velocity.z > 0){
    vector3_scale(&actor->body.velocity, 1 - (contact->angle_of_incidence * 0.01));           // angle of incidence can be up to 90 degrees
    actor->body.velocity = vector3_reflect(&actor->body.velocity, &contact->data.normal);
    actor->body.velocity.z = 0.0f;
    }
    else {
        actor->body.velocity.x = 0.0f;
        actor->body.velocity.y = 0.0f;
    }
    actor_setState(actor, FALLING);
}

void actorCollision_setResponse(Actor* actor, ActorContact* contact, ActorCollider* collider)
{
    actorContact_setAngleOfIncidence(contact, &actor->body.velocity);
    actorCollision_solvePenetration(actor, contact, collider);

    if (contact->slope > 0 && contact->slope < 50) {
        actorCollision_setGroundResponse(actor);
        actorCollision_collideAndSlide(actor, contact);
    }
    else if (contact->slope > 95 && actor->grounded == false) {
        actorCollision_collideAndSlide(actor, contact);
        actorCollision_setCeilingResponse(actor, contact);    
    }
    else actorCollision_collideAndSlide(actor, contact);

    actorCollider_setVertical(collider, &actor->body.position);
}

void actorCollision_collideWithRoom(Actor* actor) {
    if (actor->body.position.x > 2450) actor->body.position.x = 2450;
    if (actor->body.position.x < -2450) actor->body.position.x = -2450;
    if (actor->body.position.y > 2450) actor->body.position.y = 2450;
    if (actor->body.position.y < -2450) actor->body.position.y = -2450;
    if (actor->body.position.z < 0) actor->body.position.z = 0;
}

/*
void actorCollision_solve()
{
    actorContact_clear(&player_contact);
    actorCollider_setVertical(&player_collider, &player.body.position);
    
    if (player.body.position.z != 0 
        && player.state != JUMP) {

        player.grounding_height = 0.0f;
        actor_setState(&player, FALLING);
    }

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// this part of the code is the prototype for the stick to ground algorithm

    actorCollision_setGroundDistance(&ground_contact, &player.body.position);
    
    float actor_to_ground = (player_collider.body.radius / cosf(rad(ground_contact.slope))) - player_collider.body.radius;
    
    if (actor_to_ground != 0
        && player.state != JUMP
        && ground_contact.slope > 0 && ground_contact.slope < 50
        && player.body.position.z > player.grounding_height
        && ground_contact.ground_distance > (actor_to_ground)
        && ground_contact.ground_distance < (actor_to_ground + 20)) {

        player.body.position.z -= ground_contact.ground_distance - (actor_to_ground);
        player.grounded = true;
        player.grounding_height = player.body.position.z;
        if (vector3_squaredMagnitude(&player.body.velocity) < 100) actor_setState(&player, STAND_IDLE);
        else actor_setState(&player, player.previous_state);
    }
    else actorContact_clear(&ground_contact);

// ends here
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

    if (actorCollision_contactSphere(&player_collider, &black_ball_collider)) {
        actorCollision_contactSphereSetData(&player_contact, &player_collider, &black_ball_collider);
        actorCollision_setResponse(&player, &player_contact, &player_collider);
    }
    
    if (actorCollision_contactAABB(&player_collider, &green_box_collider)) {
        actorCollision_contactAABBsetData(&player_contact, &player_collider, &green_box_collider);
        actorCollision_setResponse(&player, &player_contact, &player_collider);
    }

    if (actorCollision_contactBox(&player_collider, &purple_box_collider)) {
        actorCollision_contactBoxSetData(&player_contact, &player_collider, &purple_box_collider);
        actorCollision_contactBoxSetData(&ground_contact, &player_collider, &purple_box_collider);
        actorCollision_setResponse(&player, &player_contact, &player_collider);
    }
    if (actorCollision_contactBox(&player_collider, &grey_box_collider)) {
        actorCollision_contactBoxSetData(&player_contact, &player_collider, &grey_box_collider);
        actorCollision_setResponse(&player, &player_contact, &player_collider);
    }

    if (actorCollision_contactPlane(&player_collider, &platform_collider)) {
        actorCollision_contactPlaneSetData(&player_contact, &player_collider, &platform_collider);
        actorCollision_contactPlaneSetData(&ground_contact, &player_collider, &platform_collider);
        actorCollision_setResponse(&player, &player_contact, &player_collider);
    }

    actorCollision_collideWithPlayground(&player);
}
*/

#endif