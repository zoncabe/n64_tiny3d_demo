#ifndef SCENERY_H
#define SCENERY_H


/* SCENERY.H
here are all the structures and functions prototypes that involve the setting up of an entity */

// macros

// structures


typedef struct {

	Mtx	position_mtx;
	Mtx rotation_mtx[3];
	Mtx scale_mtx;

	Gfx *mesh;
    
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

} Scenery;


// function prototypes


void scenery_set_dl(Scenery *scenery);


/* set scenery
handles the system functions that enters a scenery object's position and rotation values */

void scenery_set_dl(Scenery *scenery)
{
    guTranslate(&scenery->position_mtx, scenery->position.x, scenery->position.y, scenery->position.z);
    guRotate(&scenery->rotation_mtx[0], scenery->rotation.x, 1, 0, 0);
    guRotate(&scenery->rotation_mtx[1], scenery->rotation.y, 0, 1, 0);
    guRotate(&scenery->rotation_mtx[2], scenery->rotation.z, 0, 0, 1);
    guScale(&scenery->scale_mtx, scenery->scale.x, scenery->scale.y, scenery->scale.z);

    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&scenery->position_mtx), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&scenery->rotation_mtx[0]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&scenery->rotation_mtx[1]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&scenery->rotation_mtx[2]), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix(glistp++, OS_K0_TO_PHYSICAL(&scenery->scale_mtx), G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    
    gSPDisplayList(glistp++, scenery->mesh);

    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
    gSPPopMatrix(glistp++, G_MTX_MODELVIEW);
}


#endif
