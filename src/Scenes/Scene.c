#include "Scene.h"
#include "../Error/Error.h"
#include "../Globals.h"

ENTITY FindNewEntitySpace(Scene* scene){
    ENTITY ret = 0;
    if (scene->free_space.last_free > 0){
        scene->free_space.last_free--;
        ret = scene->free_space.stack[scene->free_space.last_free];
        scene->components.tags[ret] = VALID;
        scene->num_entities++;
        return ret;
    }
    else if (scene->last_entity < MAX_ENTITIES){
        ret = scene->last_entity;
        scene->components.tags[ret] = VALID;
        scene->last_entity++;
        scene->num_entities++;
        return ret;
    }
    LogError(&pd);
    return ret;
}

void FreeEntity(ENTITY entity, Scene* scene){
    //TODO: convertir esto a una cola, no un stack
    scene->components.tags[entity] = 0;
    scene->free_space.stack[scene->free_space.last_free] = entity;
    scene->free_space.last_free++;
    scene->num_entities--;
}

void InitializeScene(Scene* scene){
    // Stack initialization
    scene->free_space.last_free = 0;

    // Components initialization
    scene->components.transform.quaternions.x[0] = 0;
    scene->components.transform.quaternions.y[0] = 0;
    scene->components.transform.quaternions.z[0] = 0;
    scene->components.transform.quaternions.w[0] = 0;
    
    scene->components.transform.position.x[0] = 0;
    scene->components.transform.position.y[0] = 0;
    scene->components.transform.position.z[0] = 0;

    scene->components.transform.scale.x[0] = 0;
    scene->components.transform.scale.y[0] = 0;
    scene->components.transform.scale.z[0] = 0;
    
    scene->components.velocity.x[0] = 0;
    scene->components.velocity.y[0] = 0;
    scene->components.velocity.z[0] = 0;

    scene->components.acceleration.x[0] = 0;
    scene->components.acceleration.y[0] = 0;
    scene->components.acceleration.z[0] = 0;

    scene->components.force.x[0] = 0;
    scene->components.force.y[0] = 0;
    scene->components.force.z[0] = 0;

    scene->components.num_force_generators = 0;

    for (ENTITY e = 0; e < MAX_ENTITIES; ++e){
        scene->components.tags[e] = 0;
    }
    scene->last_entity = 1;
    scene->num_entities = 0;
}

FORCE_GENERATOR_MASK NewForceGenerator(Scene* scene, ENTITY e){
    FORCE_GENERATOR_MASK mask = 1 << scene->components.num_force_generators;
    scene->components.force_generators[mask] = e;
    scene->components.num_force_generators++;
    return mask;
}
void EraseForceGenerator(Scene* scene, FORCE_GENERATOR_MASK mask){

}
