#include <PxPhysicsAPI.h>
#include "particle.h"
#include "utils/Vector3D.h"
#include "RenderUtils.hpp"

#include <iostream>

Particle::Particle(Vector3D pos, Vector3D acc, double damping, Vector3D vel, integrator i, double mass, Vector3D g )
	: vel(vel),damping(damping), acceleration(acc), mass(mass), g(g){

	switch (i){
		case integrator::EULER:
		{
			integrate = euler_integrate;
			break;
		}
		case integrator::VERLET:
		{
			integrate = verlet_integrate;
			break;
		}
		default: 
		{
			integrate = semi_euler_integrate;
			break;
		}
	}

	pose = physx::PxTransform(pos);
	render_item = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)),&pose, Vector4(1,1,1,1));
}

Particle::~Particle(){
	delete render_item;
}

void Particle::euler_integrate(double t, Particle& p){
	p.pose.transform(p.pose.p += p.vel * t);
	p.vel += p.acceleration * t;
	p.vel = p.vel * pow(p.damping, t);
}
void Particle::semi_euler_integrate(double t, Particle& p){
	p.vel += p.acceleration * t;
	p.pose.transform(p.pose.p += p.vel * t);
	p.vel = p.vel * pow(p.damping, t);
}
void Particle::verlet_integrate(double t, Particle& p){
	//TODO: hacer esto. Integrar primero con semi-euler para la primera iteracion y luego seguir con verlet
}