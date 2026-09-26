#include <PxPhysicsAPI.h>
#include "particle.h"
#include "utils/Vector3D.h"
#include "RenderUtils.hpp"

#include <iostream>

Particle::Particle(Vector3D pos, Vector3D vel): vel(vel){
	render_item = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), new physx::PxTransform(pos), Vector4(1,1,1,1));
}

Particle::~Particle(){
	delete render_item;
}

void Particle::integrate(double t){
	//EULER
	//pose.transform(pose.p += vel*t);
	//vel += acceleration*t;
	std::cout << pose.p.x << ", " << pose.p.y << ", "<< pose.p.z << "; " << vel.x << ", " << vel.y << ", " << vel.z << "\n";
}