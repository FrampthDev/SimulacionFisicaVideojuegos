#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <raylib.h>
#include "../Scenes/Scene.h"
#include <stdio.h>

void SemiEulerSystem_Update(Scene* scene, ENTITY e,Tags t, float dt);

void LifeTimeSystem_Update(Scene* scene, ENTITY e, Tags t, float dt);

void ParticleSystem_Update(Scene* scene, ENTITY e, Tags t, float dt);

void ParticleRadiusSystem_Update(Scene* scene, ENTITY e, Tags t);

void RenderSystem_Update(Scene* scene, Camera3D camera);

void GuiSystem_Update(Scene* scene, ProfilerData* data);

// TODO: Cambiar estos bools feos
void InputSystem_Update(Scene* scene, bool* cursor, bool* can_move, Camera3D* cam);

// Generadores de fuerzas
void ForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t);

void GravityForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t);
void WindForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t);
void WhirlwindForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t);
void ExplosionForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t);

void TimerSystem_Update(Scene* scene, ENTITY e);

#endif
