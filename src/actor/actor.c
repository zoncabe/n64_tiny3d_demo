
#include "../../include/physics/physics.h"
#include "../../include/actor/actor.h"


// function implemenations

void actor_draw(Actor *actor)
{	
	for (uint8_t i = 0; i < ACTOR_COUNT; i++) {
				
		t3d_matrix_set(actor->transform_matrix, true);
		t3d_mat4fp_from_srt_euler(actor[i].transform_matrix,
			(float[3]){actor[i].scale.x, actor[i].scale.y, actor[i].scale.z},
			(float[3]){rad(actor[i].body.rotation.x), rad(actor[i].body.rotation.y), rad(actor[i].body.rotation.z)},
			(float[3]){actor[i].body.position.x, actor[i].body.position.y, actor[i].body.position.z}
		);
		rspq_block_run(actor[i].dl);
	};
}

// lol i will finish this someday
void actor_delete(Actor *actor) 
{
	t3d_skeleton_destroy(&actor->armature.main);
	t3d_skeleton_destroy(&actor->armature.blend);
	
	t3d_anim_destroy(&actor->animation.set.breathing_idle);
	t3d_anim_destroy(&actor->animation.set.running);
	t3d_anim_destroy(&actor->animation.set.jump_left);
	t3d_anim_destroy(&actor->animation.set.falling_left);
	t3d_anim_destroy(&actor->animation.set.land_left);
	
	t3d_model_free(actor->model);
	rspq_block_free(actor->dl);
}