#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_animation.h"
#include "../../include/light/lighting.h"
#include "../../include/camera/camera.h"
#include "../../include/viewport/viewport.h"


// function implemenations

void actor_init(Actor *actor, T3DSkeleton* armature, const char* model_path)
{
}

void actor_draw(Actor* actor, RigidBody* body)
{
	t3d_mat4fp_from_srt_euler(&actor->t3d_matrix[viewport.fb_index],
		(float[3]){actor->model_scale.x, actor->model_scale.y, actor->model_scale.z},
		(float[3]){rad(body->rotation.x), rad(body->rotation.y), rad(body->rotation.z)},
		(float[3]){body->position.x, body->position.y, body->position.z}
	);
    t3d_matrix_push(&actor->t3d_matrix[viewport.fb_index]);
	rspq_block_run(actor->dl);
    t3d_matrix_pop(1);
}
