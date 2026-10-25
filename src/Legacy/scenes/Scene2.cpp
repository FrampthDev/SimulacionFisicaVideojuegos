/*
#include "Scene2.h"
#include <immintrin.h>


//Scene2::Scene2(std::string name) : Scene(std::move(name)) {
//	p_sys = ParticleSystem(this);
//}
void Scene2::init() {
	for (size_t i = 0; i < MAX_PARTICLES; ++i) Particles.active[i] = false;


}
void Scene2::cleanup() {

}

void Scene2::update(double dt) {
	// Euler semi implícito 
	// TODO: cambiar a SIMD
	

	for (size_t p = 0; p < MAX_PARTICLES; ++p) {
		Particles.vel.x[p] += Particles.acc.x[p] * dt;
		Particles.vel.y[p] += Particles.acc.y[p] * dt;
		Particles.vel.z[p] += Particles.acc.z[p] * dt;

		Particles.pos.x[p] += Particles.vel.x[p] * dt;
		Particles.pos.y[p] += Particles.vel.y[p] * dt;
		Particles.pos.z[p] += Particles.vel.z[p] * dt;

		Particles.vel.x[p] *= pow(Particles.damping[p], dt);
		Particles.vel.y[p] *= pow(Particles.damping[p], dt);
		Particles.vel.z[p] *= pow(Particles.damping[p], dt);
	}
	for (size_t p = 0; p < MAX_PARTICLES; ++p){
		//startRender(GetCamera()->getEye(), GetCamera()->getEye());
		////TODO: Cambiar a raylib y usar un shader para renderizar
		//if (Particles.active[p]) {
		//
		//	physx::PxTransform tr = physx::PxTransform({ Particles.pos.x[p], Particles.pos.y[p], Particles.pos.z[p] });
		//	renderShape(*shape, tr, {1,0,0,1});
		//	
		//
		//}
		//finishRender();
	}
	
	
	p_sys.create_particles(5);

}*/
