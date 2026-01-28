#ifndef ACTOR_ANIMATION_H
#define ACTOR_ANIMATION_H


#define LAND_ANIM_STARTING_HEIGHT 130 // workaround until definitive solution including collision


void actorAnimation_initArmature(ActorArmature* armature, T3DModel *model);
void actorAnimation_initStandingLocomotionSet(ActorArmature* armature, T3DModel *model, ActorAnimationStandingLocomotionSet *set);
void actorAnimation_initJumpSet(ActorArmature* armature, T3DModel *model, ActorAnimationJumpSet *set);
void actorAnimation_initRollSet(ActorArmature* armature, T3DModel *model, ActorAnimationRollSet *set);

void actorAnimation_setLocomotionBlendingRatio(ActorMotionData* motion_data, ActorMotionSettings* motion_settings, ActorAnimationData* animation_data);
void actorAnimation_setFootingBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, float action_time, float action_lenght);
void actorAnimation_setRollingBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationRollSettings* roll_settings, ActorAnimationLocomotionSettings* locomotion_settings, ActorAnimationStandingLocomotionSet* locomotion_set);
void actorAnimation_setJumpBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* animation_settings);
void actorAnimation_setLandingBlendingRatio(ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* animation_settings, ActorAnimationJumpSet* set);

void actorAnimation_setWalkingSpeed(ActorAnimationData* animation_data, ActorAnimationStandingLocomotionSet* set);
void actorAnimation_setRunningSpeed(ActorAnimationData* animation_data, ActorAnimationLocomotionSettings* animation_settings, ActorAnimationStandingLocomotionSet* set);
void actorAnimation_setSprintingSpeed(ActorAnimationData* animation_data, ActorAnimationLocomotionSettings* animation_settings, ActorAnimationStandingLocomotionSet* set);

void actorAnimation_setStandingIdle(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data, ActorAnimationLocomotionSettings* settings);
void actorAnimation_setWalking(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data);
void actorAnimation_setRunning(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data);
void actorAnimation_setSprinting(ActorArmature* armature, ActorAnimationStandingLocomotionSet* set, ActorAnimationData* animation_data);
void actorAnimation_setRunToRoll(ActorArmature* armature, ActorAnimationRollSet* roll_set, ActorAnimationStandingLocomotionSet* locomotion_set, ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationRollSettings* roll_settings, ActorAnimationLocomotionSettings* locomotion_settings);
void actorAnimation_setFallingIdle(ActorArmature *armature, ActorAnimationJumpSet* set, ActorAnimationData* animation_data);
void actorAnimation_setJump(ActorArmature *armature, ActorAnimationJumpSet* set, ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* settings);
void actorAnimation_setLanding(ActorArmature *armature, ActorAnimationJumpSet* set, ActorMotionData* motion_data, ActorAnimationData* animation_data, ActorAnimationJumpSettings* settings);


#endif