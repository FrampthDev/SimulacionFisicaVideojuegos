#include "Systems.h"

void ForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t){
    if (!(scene->components.tags[e] & t)) return;

    //TODO: el generador de fuerzas no debería ser la posición
    for (int i = 0; i < scene->components.num_force_generators; i++){
        FORCE_GENERATOR_MASK mask = 1 << i;
        if (scene->components.force_mask[e] & mask){
            ENTITY force_generator = scene->components.force_generators[i];
            scene->components.force.x[e] += scene->components.transform.position.x[force_generator];
            scene->components.force.y[e] += scene->components.transform.position.y[force_generator];
            scene->components.force.z[e] += scene->components.transform.position.z[force_generator];
        }
    }   
}
