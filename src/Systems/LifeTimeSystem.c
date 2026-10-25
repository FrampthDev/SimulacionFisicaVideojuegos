#include "Systems.h"

void LifeTimeSystem_Update(Scene* scene, ENTITY e, Tags t, float dt){
    if(!(scene->components.tags[e] & t)) return;
    if (scene->components.life_time[e] > 0){
        scene->components.life_time[e] -= dt;
    }
    else{
        FreeEntity(e, scene);
    }
}
