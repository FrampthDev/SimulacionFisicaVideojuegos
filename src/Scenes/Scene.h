#ifndef SCENE_H
#define SCENE_H

#include "../utils/Types.h"
#include "../Globals.h"

// NO SE DEBE PODER ESCRIBIR EN LA ENTIDAD 0. Si se escribe en la entidad 0 no pasa nada. Siempre tiene que mantenerse nula.

#define MAX_ENTITIES 10000

#define FORCE_GENERATOR_MASK unsigned long int

typedef struct quaternion_array{
    float x[MAX_ENTITIES];
    float y[MAX_ENTITIES];
    float z[MAX_ENTITIES];
    float w[MAX_ENTITIES];
} quaternion_array;

typedef struct vector3D_array{
    float x[MAX_ENTITIES];   
    float y[MAX_ENTITIES];
    float z[MAX_ENTITIES];
} vector3D_array;

typedef enum Tags{
    VALID           = 1 << 0,
    TRANSFORM       = 1 << 1,
    PARTICLE_SYSTEM = 1 << 2,
    RENDER          = 1 << 3,
    LIFE_TIME       = 1 << 4,
    PARTICLE        = 1 << 5, // For rendering porpouses
} Tags;

// Los valores 1 de los array son valores _Por defecto_. No se deben usar para almacenar entidades.
typedef struct Scene{
    ENTITY num_entities;
    struct{
        struct {
            quaternion_array quaternions;   // 16 bytes * MAX_ENTITIES
            vector3D_array position;        // 12 bytes * MAX_ENTITIES
            vector3D_array scale;           // 12 bytes * MAX_ENTITIES
        } transform;

        vector3D_array velocity;            // 12 bytes * MAX_ENTITIES
        vector3D_array acceleration;        // 12 bytes * MAX_ENTITIES
        vector3D_array force;
        float mass[MAX_ENTITIES];
        float damping[MAX_ENTITIES];

        union{
            //TODO
        } shapes[MAX_ENTITIES];

        // PARTICLE
        float life_time[MAX_ENTITIES];
        FORCE_GENERATOR_MASK force_mask[MAX_ENTITIES];

        // FORCE GENERATOR
        // TODO: gestionar el borrado y la creación dinámica de generadores de fuerza con un stack o una queue
        ENTITY force_generators[64];
        unsigned int num_force_generators;

        // PARTICLE SYSTEM 
        struct{
            float life_time[MAX_ENTITIES];
            FORCE_GENERATOR_MASK force_masks[MAX_ENTITIES];

        } particle_system;

        Tags tags[MAX_ENTITIES];
    } components;
    ENTITY last_entity;                     // = 1

    struct {
        ENTITY stack[MAX_ENTITIES];         // 8 bytes * MAX_ENTITIES
        ENTITY last_free;                   // = 1
    } free_space;

} Scene;

ENTITY FindNewEntitySpace(Scene* scene);
void FreeEntity(ENTITY entity, Scene* scene);

FORCE_GENERATOR_MASK NewForceGenerator(Scene* scene, ENTITY e);
void InitializeScene(Scene* scene);

#endif
