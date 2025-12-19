#ifndef ACTOR_ANIMATION_H
#define ACTOR_ANIMATION_H


#define LAND_ANIM_STARTING_HEIGHT 130 // workaround until definitive solution including collision


// function prototypes

void playerAnimationSet_init(T3DModel *model, PlayerAnimationSet *set);
void playerAnimationSet_attach(T3DSkeleton *main, T3DSkeleton *blend, T3DSkeleton *blend2, PlayerAnimationSet *set);
void playerAnimation_init(Player* player);

void player_setAnimation(Player* player);


#endif