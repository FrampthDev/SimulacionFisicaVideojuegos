#ifndef PARTICLE_N
#define PARTICLE_N

#include <PxPhysicsAPI.h>
#include "utils/Vector3D.h"
#include "RenderUtils.hpp"


class Particle{
public:
	Particle(Vector3D pos, Vector3D vel);
	~Particle();

	void integrate(double t);

private:
	Vector3D vel;
	Vector3D acceleration = {0,0,0};
	physx::PxTransform pose;
	

public:
	RenderItem* render_item;
};


#endif