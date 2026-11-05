#include "Systems.h"

void ParticleRadiusSystem_Update(Scene* scene, ENTITY e, Tags t){
    if (!(scene->components.tags[e] & t)) return;
    if (scene->components.shape[e].type != SPHERE) return;

    scene->components.shape[e].sphere.radius = (scene->components.life_time[e] / scene->components.max_life_time[e]) * SHAPE_TIME_SCALE_FACTOR;

}
