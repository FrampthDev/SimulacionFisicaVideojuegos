#pragma once
#include "./Scene.h"
#include <vector>
#include "../Particle.h"
//#include "../utils/UtilsFunctions.hpp"
#include "../utils/Types.h"
#include "../utils/TypesBindings.h"
#include <cmath>
#include <algorithm>
#define POOL_SIZE 20

class RenderItem;
class Scene1 : public Scene{
public:
    explicit Scene1(std::string name);
    void init() override;
    void cleanup() override;
    void update(double dt) override;
    //void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;

private:
    std::vector<RenderItem*> render_item_vector;
    std::vector<Particle*> particle_pool;

    float mass = 1;
    float vel = 50;
    float damping = 0.98;
    Vector3D g = { 0,-9.8,0 };

    void shoot_particle(Vector3D pos, Vector3D dir) {
        //float s_vel = std::clamp(utils::remap<float>(vel, 0.0f,500.0f,0, 150.0f), 0.0f, 150.0f);
        //float s_mass = mass * std::pow((vel/s_vel), 2);
        //Vector3D s_g = g * (float)std::pow((s_vel/vel),2);
        //Particle* p = new Particle(pos, s_g, 0.98f,dir * s_vel, Particle::EULER_SEMI,s_mass, s_g);
        //particle_pool.push_back(p);
        //render_item_vector.push_back(p->render_item);
    }
};

