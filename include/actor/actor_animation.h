#ifndef ACTOR_ANIMATION_H
#define ACTOR_ANIMATION_H


// convertion ratio between locomotion animation lenghts on the prototype asset

#define RUN_TO_WALK_RATIO 1.347826f
#define WALK_TO_RUN_RATIO 0.741935f

#define SPRINT_TO_RUN_RATIO 1.15f
#define RUN_TO_SPRINT_RATIO 0.869565f

#define SPRINT_TO_WALK_RATIO 1.55f
#define WALK_TO_SPRINT_RATIO 0.645161f

// animation lenghts in seconds on the prototype asset

#define ACTION_IDLE_MAX_BLENDING_RATIO 0.85f

#define WALKING_ANIM_LENGTH 1.033333f
#define WALKING_ANIM_LENGTH_HALF 0.516666f

#define RUNNING_ANIM_LENGTH_HALF 0.4f
#define RUNNING_ANIM_LENGTH 0.766666f

#define SPRINTING_ANIM_LENGTH 0.666666f
#define SPRINTING_ANIM_LENGTH_HALF 0.333333f

#define RUN_TO_ROLLING_ANIM_GROUND 0.3f
#define RUN_TO_ROLLING_ANIM_GRIP 0.9f
#define RUN_TO_ROLLING_ANIM_STAND 0.9f
#define RUN_TO_ROLLING_ANIM_LENGHT 1.166666f

#define STAND_TO_ROLLING_ANIM_GRIP 1.433333f
#define STAND_TO_ROLLING_ANIM_LENGHT 2.066666f

#define JUMP_ANIM_LENGTH 0.633333f
#define JUMP_ANIM_CROUCH 0.1f
#define JUMP_ANIM_AIR 0.233333f
#define JUMP_MAX_BLENDING_RATIO 0.7f
#define JUMP_FOOTING_SPEED 0.5f

#define LAND_ANIM_LENGTH 0.9f
#define LAND_ANIM_GROUND 0.266666f
#define LAND_ANIM_STAND 0.833333f
#define LAND_ANIM_STARTING_HEIGHT 130 // workaround until definitive solution including collision


// function prototypes

void animationSet_init(T3DModel *model, AnimationSet *set);
void animationSet_attach(T3DSkeleton *main, T3DSkeleton *blend, T3DSkeleton *blend2, AnimationSet *set);
void actorAnimation_init(Actor *actor);

void actor_setAnimation(Actor *actor, const float frame_time, rspq_syncpoint_t *syncpoint);


#endif