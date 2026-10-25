#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../Headers/raygui.h"
#include "../Scenes/Scene.h"
#include "Systems.h"

void GuiSystem_Update(Scene* scene, ProfilerData* data){
    GuiWindowBox((Rectangle){ 0, 40, 217, 292 }, "Profiler");
                GuiLabel((Rectangle){ 16, 80, 150, 24 }, TextFormat("FPS: %d", GetFPS()));
                GuiLabel((Rectangle){ 16, 104, 150, 24 }, TextFormat("Entities: %d", scene->num_entities));
                GuiLabel((Rectangle){ 16, 136, 150, 24 }, TextFormat("SemiEuler: %fms", data->SemiEulerSystem * 1000));
                GuiLabel((Rectangle){ 16, 160, 150, 24 }, TextFormat("Particle Systems: %fms", data->ParticleSystem * 1000));
                GuiLabel((Rectangle){ 16, 208, 150, 24 }, TextFormat("Gui: %fms", data->GuiSystem * 1000));
                GuiLabel((Rectangle){ 16, 184, 150, 24 }, TextFormat("Render: %fms", data->RenderSystem * 1000));
}
