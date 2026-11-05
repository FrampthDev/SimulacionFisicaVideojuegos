#ifndef SCENE_H
#define SCENE_H

#include "../Globals.h"
#include <stdio.h>
#include <stdint.h>

// NO SE DEBE PODER ESCRIBIR EN LA ENTIDAD 0. Si se escribe en la entidad 0 no pasa nada. Siempre tiene que mantenerse nula.

#define MAX_ENTITIES 10000

#define FORCE_GENERATOR_MASK uint64_t

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

typedef enum{
    VECTOR3D,
    SPHERE,
    BOX,
}ShapeType;

typedef struct{
    ShapeType type;
    union{
        struct{
            float x; float y; float z;
        }vector3D; 
        struct{
            float radius;
        } sphere;
        struct{
            float lenght;
            float height;
            float width;
        }box;
    };
} Shape;

typedef enum Tags{
    VALID           = 1 << 0,
    TRANSFORM       = 1 << 1,
    PARTICLE_SYSTEM = 1 << 2,
    RENDER          = 1 << 3,
    LIFE_TIME       = 1 << 4,
    SHAPE           = 1 << 5,
    TIMER           = 1 << 6,
    // FORCE GENERATORS
    GRAVITY         = 1 << 8,
    WIND            = 1 << 9,
    WHIRLWIND       = 1 << 10,
    EXPLOSION       = 1 << 11,
    //
    PARTICLE        = 1 << 12,
} Tags;
typedef enum {
    LINEAL,
    NORMAL,
} Distribution;
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

        Shape shape[MAX_ENTITIES];

        // PARTICLE
        float life_time[MAX_ENTITIES];
        float max_life_time[MAX_ENTITIES];

        // PARTICLE SYSTEM 
        struct{
            float life_time[MAX_ENTITIES];
            Tags tags[MAX_ENTITIES];
            bool initial_movement[MAX_ENTITIES];
            struct{
                float x[MAX_ENTITIES];
                float y[MAX_ENTITIES];
                float z[MAX_ENTITIES];
            }initial_velocity;
        } particle_system;

        // TIMER
        float timer[MAX_ENTITIES];

        Tags tags[MAX_ENTITIES];

   } components;

    ENTITY last_entity;                     // = 1

    //FORCE GENERATORS
    struct{
        struct{
            float x,y,z;
        }gravity;
        struct{
            struct{
                float x,y,z;
            }velocity;
            float strength;
        }wind;
        struct{
            float strength, vertical_strength;
            float x, y, z;
        }whirlwind;
        struct{
            float strength, time, timer, max_time, radius;
            float x, y, z;
            bool exploding;
        }explosion;


        bool gravity_active, wind_active, whirlwind_active, explosion_active;
    }force_generators;
       // Free entities memory management
    struct {
        ENTITY stack[MAX_ENTITIES];         // 8 bytes * MAX_ENTITIES
        ENTITY last_free;                   // = 1
    } free_space;

} Scene;

ENTITY FindNewEntitySpace(Scene* scene);
void FreeEntity(ENTITY entity, Scene* scene);

void InitializeScene(Scene* scene);

uint32_t NewRandomID();


#endif
