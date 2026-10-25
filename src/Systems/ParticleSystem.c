#include "Systems.h"

#include "../utils/RandomDistributions.h"

#include <stdlib.h>

void ParticleSystem_Update(Scene* scene, ENTITY e, float dt){

    if (!(scene->components.tags[e] & PARTICLE_SYSTEM)) return;
    if ((int)random() % 100 > 99) return;
    ENTITY particle = FindNewEntitySpace(scene);

    scene->components.tags[particle] |= RENDER | TRANSFORM | LIFE_TIME | PARTICLE;
    scene->components.force_mask[particle] |= scene->components.particle_system.force_masks[e];

    scene->components.transform.position.x[particle] = scene->components.transform.position.x[e];
    scene->components.transform.position.y[particle] = scene->components.transform.position.y[e];
    scene->components.transform.position.z[particle] = scene->components.transform.position.z[e];

    scene->components.velocity.x[particle] = GaussDistribution(-10,10);
    scene->components.velocity.y[particle] = GaussDistribution(-10,10);
    scene->components.velocity.z[particle] = GaussDistribution(-10,10);
    
    scene->components.damping[particle] = 0.95;
    scene->components.life_time[particle] = scene->components.particle_system.life_time[e];
}
