#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H


const char xmFileNames[1] = {
    "rom:/game/sound/ene.xm64",
};

	actor[0] = actor_create(0, "rom:/male_steroids.t3dm");

	scenery[0] = scenery_create(0, "rom:/room.t3dm");
	scenery[1] = scenery_create(1, "rom:/n64logo.t3dm");

    
#endif