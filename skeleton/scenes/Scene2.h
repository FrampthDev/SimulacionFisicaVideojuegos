#pragma once
#include "Scene.h"
#include "../utils/Vector3D.h"

#include "../ParticleSystem.h"


class Scene2 : public Scene
{
private:
    ParticleSystem p_sys;
    //physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.2f));
   
public:
    explicit Scene2(std::string name);
    void init() override;
    void cleanup() override;
    void update(double dt) override;
};