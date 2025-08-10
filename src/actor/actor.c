#include <t3d/t3danim.h>

#include "../../include/time/time.h"
#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/player/player_states.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_motion.h"
#include "../../include/player/player_animation.h"


// function implemenations

void actor_init(Actor *actor, T3DSkeleton* armature, const char* model_path)
{
}

void actor_draw(Actor* actor, RigidBody* body)
{
	t3d_matrix_set(actor->render_data.t3d_matrix, true);
	t3d_mat4fp_from_srt_euler(actor->render_data.t3d_matrix,
		(float[3]){actor->render_data.model_scale.x, actor->render_data.model_scale.y, actor->render_data.model_scale.z},
		(float[3]){rad(body->rotation.x), rad(body->rotation.y), rad(body->rotation.z)},
		(float[3]){body->position.x, body->position.y, body->position.z}
	);
	rspq_block_run(actor->render_data.dl);
}
