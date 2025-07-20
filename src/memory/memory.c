#include <stdint.h>
#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/actor/actor_animation.h"
#include "../../include/actor/actor_motion.h"
#include "../../include/scene/scenery.h"

#include "../../include/memory/memory.h"


Actor actor_create(uint32_t id, const char *model_path)
{
	Actor *actor = malloc(sizeof(Actor));
    
	actor_init(actor);
	
	actor->id = id;
	actor->model = t3d_model_load(model_path);
	actor->t3d_matrix = malloc_uncached(sizeof(T3DMat4FP));

	actorAnimation_init(actor);

    t3d_matrix_set(actor->t3d_matrix, true);
    t3d_mat4fp_identity(actor->t3d_matrix);

	rspq_block_begin();
	t3d_model_draw_skinned(actor->model, &actor->armature.main);
	actor->dl = rspq_block_end();

	return *actor;
}

void actor_delete(Actor *actor) 
{
	rspq_block_free(actor->dl);
	
	t3d_skeleton_destroy(&actor->armature.main);
	t3d_skeleton_destroy(&actor->armature.blend);
	t3d_skeleton_destroy(&actor->armature.blend2);
	
	t3d_anim_destroy(&actor->animation.set.breathing_idle);
	t3d_anim_destroy(&actor->animation.set.transition_left);
	t3d_anim_destroy(&actor->animation.set.transition_right);
	t3d_anim_destroy(&actor->animation.set.standing_idle_left);
	t3d_anim_destroy(&actor->animation.set.standing_idle_right); 
	t3d_anim_destroy(&actor->animation.set.walking);
	t3d_anim_destroy(&actor->animation.set.running);
	t3d_anim_destroy(&actor->animation.set.sprinting);	
	t3d_anim_destroy(&actor->animation.set.run_to_rolling_left);
	t3d_anim_destroy(&actor->animation.set.run_to_rolling_right);
	t3d_anim_destroy(&actor->animation.set.stand_to_rolling_left);
	t3d_anim_destroy(&actor->animation.set.stand_to_rolling_right);
	t3d_anim_destroy(&actor->animation.set.jump_left);
	t3d_anim_destroy(&actor->animation.set.jump_right);
	t3d_anim_destroy(&actor->animation.set.falling_left);
	t3d_anim_destroy(&actor->animation.set.falling_right);	
	t3d_anim_destroy(&actor->animation.set.land_left);
	t3d_anim_destroy(&actor->animation.set.land_right);

	free_uncached(actor->t3d_matrix);
	t3d_model_free(actor->model);

	free(actor);
}



Scenery scenery_create(uint32_t id, const char *model_path)
{
    Scenery *scenery = malloc(sizeof(Scenery));

	scenery_init(scenery);

	scenery->id = id;
	scenery->model = t3d_model_load(model_path);
	scenery->t3d_matrix = malloc_uncached(sizeof(T3DMat4FP));

    t3d_matrix_set(scenery->t3d_matrix, true);
    t3d_mat4fp_identity(scenery->t3d_matrix);

    rspq_block_begin();
    t3d_model_draw(scenery->model);
    scenery->dl = rspq_block_end();

    return *scenery;
}

void scenery_delete(Scenery *scenery)
{	
	free_uncached(scenery->t3d_matrix);
    t3d_model_free(scenery->model);
    rspq_block_free(scenery->dl);

	free(scenery);
}