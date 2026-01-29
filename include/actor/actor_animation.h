#ifndef ACTOR_ANIMATION_H
#define ACTOR_ANIMATION_H

#define LAND_ANIM_STARTING_HEIGHT 130 // workaround until definitive solution including collision

void actorAnimation_initArmature(Actor* actor);
void actorAnimation_initStandingLocomotionSet(Actor* actor);
void actorAnimation_initJumpSet(Actor* actor);
void actorAnimation_initRollSet(Actor* actor);

void actorAnimation_setLocomotionBlendingRatio(Actor* actor);
void actorAnimation_setFootingBlendingRatio(Actor* actor, float action_time, float action_lenght);
void actorAnimation_setRollingBlendingRatio(Actor* actor);
void actorAnimation_setJumpBlendingRatio(Actor* actor);
void actorAnimation_setLandingBlendingRatio(Actor* actor);

void actorAnimation_setWalkingSpeed(Actor* actor);
void actorAnimation_setRunningSpeed(Actor* actor);
void actorAnimation_setSprintingSpeed(Actor* actor);

void actorAnimation_setStandingIdle(Actor* actor);
void actorAnimation_setWalking(Actor* actor);
void actorAnimation_setRunning(Actor* actor);
void actorAnimation_setSprinting(Actor* actor);
void actorAnimation_setRunToRoll(Actor* actor);
void actorAnimation_setFallingIdle(Actor* actor);
void actorAnimation_setJump(Actor* actor);
void actorAnimation_setLanding(Actor* actor);

#endif