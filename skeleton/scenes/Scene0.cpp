#include "Scene0.h"

#include "../RenderUtils.hpp"
#include "../utils/Vector3D.h"

#include "../Particle.h"

#include <iostream>

Scene0::Scene0(std::string name) : Scene(std::move(name)) {}

void Scene0::new_particle(Vector3D pos, Vector3D acc, Vector3D vel){
    Particle* p = new Particle(pos,acc,0.1,vel, Particle::integrator::EULER_SEMI);
    particle_vector.push_back(p);
    render_item_vector.push_back(p->render_item);
}

void Scene0::init() {    
    new_particle({0,0,0},{1,0,0},{1,0,0});
}
void Scene0::cleanup() {
    for (RenderItem* ri : render_item_vector) {
        if (ri != nullptr)
            ri->release();
    }
    render_item_vector.clear();
    for(Particle* p : particle_vector){
        if (p != nullptr) delete p;
    }
    particle_vector.clear();
}
void Scene0::update(double dt) {
    for(Particle* p : particle_vector){
        p->integrate(dt, *p); // TODO: construir una interfaz por encima para no llamar con la misma partícula como ref
    }
}