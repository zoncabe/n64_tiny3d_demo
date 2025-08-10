#include <stdint.h>
#include <t3d/t3danim.h>

#include "../../include/physics/physics.h"
#include "../../include/control/control.h"
#include "../../include/actor/actor.h"
#include "../../include/player/player.h"
#include "../../include/control/player_control.h"
#include "../../include/player/player_animation.h"
#include "../../include/player/player_motion.h"
#include "../../include/scene/scenery.h"


Player* player_create(uint32_t id, const char *model_path)
{
	Player *player = malloc(sizeof(Player));
	
	player_init(id, player, model_path);

	return player;
}

void actor_delete(Actor *actor) 
{
}

Scenery* scenery_create(uint32_t id, const char *model_path)
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

    return scenery;
}

void scenery_delete(Scenery *scenery)
{	
    rspq_block_free(scenery->dl);

	free_uncached(scenery->t3d_matrix);
    t3d_model_free(scenery->model);

	free(scenery);
}