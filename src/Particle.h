#ifndef PARTICLE_N
#define PARTICLE_N

//#include <PxPhysicsAPI.h>
#include "utils/Types.h"

class Particle{
public:
	enum integrator {
		EULER,
		EULER_SEMI,
		VERLET,
	};

	Particle(Vector3D pos, Vector3D acc, double damping, Vector3D vel, integrator i, double mass, Vector3D g = {0,-9.8,0});
	~Particle();

	void (*integrate)(double t, Particle& p);
private:
	Vector3D vel;
	Vector3D acceleration;
	double damping = 0;
	//physx::PxTransform pose;
	double mass;
	Vector3D g;
	
	static void euler_integrate(double t, Particle& p);
	static void semi_euler_integrate(double t, Particle& p);
	static void verlet_integrate(double t, Particle& p);

public:
	//TODO: Cambiar esto
	//RenderItem* render_item;
};


#endif
