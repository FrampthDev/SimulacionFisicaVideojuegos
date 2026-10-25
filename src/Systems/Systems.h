#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <raylib.h>
#include "../Scenes/Scene.h"
#include <stdio.h>

void SemiEulerSystem_Update(Scene* scene, ENTITY e,Tags t, float dt);

void LifeTimeSystem_Update(Scene* scene, ENTITY e, Tags t, float dt);

void ParticleSystem_Update(Scene* scene, ENTITY e, float dt);

void RenderSystem_Update(Scene* scene, Camera3D camera);

//TODO: quitar esto de aqui
typedef struct ProfilerData{
    double SemiEulerSystem;
    double LifeTimeSystem;
    double ParticleSystem;
    double RenderSystem;
    double GuiSystem;
}ProfilerData;

void GuiSystem_Update(Scene* scene, ProfilerData* data);

// TODO: Cambiar estos bools feos
void InputSystem_Update(bool* cursor, bool* can_move);

void ForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t);

#endif
