#ifndef PHYSICS_CONFIG_H
#define PHYSICS_CONFIG_H


// ---------- Enumerations ---------- //

/* Position correction technique used in the constraint solver (for joints).
    BAUMGARTE_JOINTS : Faster but can be inaccurate in some situations.
    NON_LINEAR_GAUSS_SEIDEL : Slower but more precise. This is the option used by default. 
*/
typedef enum {

    BAUMGARTE_JOINTS,
    NON_LINEAR_GAUSS_SEIDEL

} JointsPositionCorrectionTechnique;

/* Position correction technique used in the contact solver (for contacts)
    BAUMGARTE_CONTACTS : Faster but can be inaccurate and can lead to unexpected bounciness
                        in some situations (due to error correction factor being added to
                        the bodies momentum).
    SPLIT_IMPULSES : A bit slower but the error correction factor is not added to the
                    bodies momentum. This is the option used by default. 
*/
typedef enum {

    BAUMGARTE_CONTACTS,
    SPLIT_IMPULSES

} ContactsPositionCorrectionTechnique;


// ---------- Constants ---------- //

/* Pi constant */
#define PI 3.141592653589f

/* 2*Pi constant */
#define PI_TIMES_2 6.28318530f

/* A numeric tolerance value used to handle floating-point precision issues. */
#define TOLERANCE 1e-6f

/*In the broad-phase collision detection (dynamic AABB tree), the AABBs are
inflated by a constant percentage of its size to allow the collision shape to move a little bit
without triggering a large modification of the tree each frame which can be costly */
#define DYNAMIC_TREE_FAT_AABB_INFLATE_PERCENTAGE 0.08f

/* Maximum number of contact points in a narrow phase info object */
#define NB_MAX_CONTACT_POINTS_IN_NARROWPHASE_INFO 16

/* Maximum number of contact manifolds in an overlapping pair */
#define NB_MAX_CONTACT_MANIFOLDS 4

/* Maximum number of potential contact manifolds in an overlapping pair */
#define NB_MAX_POTENTIAL_CONTACT_MANIFOLDS 64

/* Maximum number of contact points in potential contact manifold */
#define NB_MAX_CONTACT_POINTS_IN_POTENTIAL_MANIFOLD 255

/* Distance threshold to consider that two contact points in a manifold are the same */
#define SAME_CONTACT_POINT_DISTANCE_THRESHOLD 0.01f

/* Global alignment (in bytes) that all allocators must enforce */
#define GLOBAL_ALIGNMENT 16


#endif
