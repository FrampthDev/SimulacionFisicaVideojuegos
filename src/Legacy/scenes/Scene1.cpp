/*
#include "Scene1.h"


#include "../utils/Vector3D.h"
#include "../Particle.h"


#include <iostream>

Scene1::Scene1(std::string name) : Scene(std::move(name)) {}

void Scene1::init() {

}
//void Scene1::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
/*
    switch (key) {
        case 'p':
        {
            //shoot_particle(GetCamera()->getTransform().p, GetCamera()->getDir());
            break;
        }
        case 'h': // aumentar masa
        {
            mass+= 0.1;
            std::cout << "La masa es: " << mass << "\n";
            break;
        }
        case 'l': // disminuir masa
        {
            mass-= 0.1;
            std::cout << "La masa es: " << mass << "\n";
            break;
        }
        case 'j':
        {
            vel += 10;
            std::cout << "La velocidad es: " << vel << "\n";
            break;
        }
        case 'k':
        {
            vel -= 10;
            std::cout << "La velocidad es: " << vel << "\n";
            break;
        }
    }
}
void Scene1::cleanup() {
    //for (RenderItem* ri : render_item_vector) {
    //    if (ri != nullptr)
    //        ri->release();
    //}
    //render_item_vector.clear();
    //for (Particle* p : particle_pool) {
    //    if (p != nullptr) delete p;
    //}
    //particle_pool.clear();
}
void Scene1::update(double dt) {
    for (Particle* p : particle_pool) {
        p->integrate(dt, *p); // TODO: construir una interfaz por encima para no llamar con la misma partícula como ref
    }
}*/
