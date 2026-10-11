#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H
#include <immintrin.h>
#include <random>

#include "utils/Types.h"

class Scene;



class ParticleSystem
{

private:
    int n_particles = 0;
    int n_particles_offset = 0;
    float initial_velocity = 0;
    float initial_velocity_offset = 0;

    //Vector3D initial_position();

    std::default_random_engine generator;
    std::normal_distribution<float> lifetime_dist;
    std::normal_distribution<float> new_particles;
    std::normal_distribution<float> new_vel;

    Scene* scn = nullptr;
    
    Vector3D position = {0,0,0};
    // TODO: hacer que el generador pueda ser un cuadrado o un círculo
    

public:
    ParticleSystem(){};
    ParticleSystem(Scene* scn);
    ~ParticleSystem() = default;
    void create_particles(int particles);
};

#endif
