/*
#include "ParticleSystem.h"
#include "scenes/Scene.h"
#include <immintrin.h>


ParticleSystem::ParticleSystem(Scene* scn) : scn(scn) {
//FIXME: assert algo de la distribucion normal wtf¿?¿?¿
    //lifetime_dist = std::normal_distribution<float>(3.0f, 0.5f);
    //new_particles = std::normal_distribution<float>(n_particles, n_particles_offset);
    //new_vel = std::normal_distribution<float>(initial_velocity, initial_velocity_offset);
}


void ParticleSystem::create_particles(int particles) {

    //float particle_lifetime = lifetime_dist(generator);
    //TODO: terminar esto

    //float s_vel = std::clamp(utils::remap<float>(vel, 0.0f, 500.0f, 0, 150.0f), 0.0f, 150.0f);
    //double s_mass = mass * std::pow((vel / s_vel), 2);
    //Vector3D s_g = g * std::pow((s_vel / vel), 2);
    //Particle* p = new Particle(pos, s_g, 0.98f, dir * s_vel, Particle::EULER_SEMI, s_mass, s_g);
    //particle_pool.push_back(p);
    //render_item_vector.push_back(p->render_item);
    
    for (size_t i = 0; i < particles; ++i){
        size_t p = ++scn->last_particle;
        scn->Particles.pos.x[p] = position.x;
        scn->Particles.pos.y[p] = position.x;
        scn->Particles.pos.z[p] = position.x;
        
        scn->Particles.active[p] = true;

    }


}*/
