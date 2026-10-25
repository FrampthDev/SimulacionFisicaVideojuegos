#include <raylib.h>
#define RAYGUI_IMPLEMENTATION

#include "Scenes/Scene.h"
#include "Systems/Systems.h"
#include "assert.h"
#include <stdio.h>

#define TARGET_FPS 60
#define D_TIME GetFrameTime()

Scene scene;
ProfilerData profiler_data;

bool cursor;
bool can_move;

int main(void)
{
    InitWindow(1080,1080,"SIM");
    SetTargetFPS(TARGET_FPS);

    // Camera inizalization
    Camera3D camera ={
        {20,0,0},
        {0,0,0},
        {0,1,0},
        90,
        CAMERA_PERSPECTIVE,
    };

    InitializeScene(&scene);

    cursor = false;
    can_move= true;

    DisableCursor();

    double timer = 0;

    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    SetTargetFPS(TARGET_FPS);

    ENTITY f_g = FindNewEntitySpace(&scene);
    scene.components.transform.position.y[f_g] = -9.8;
    FORCE_GENERATOR_MASK f_g_m = NewForceGenerator(&scene, f_g);


    ENTITY p_s = FindNewEntitySpace(&scene);
    scene.components.tags[p_s] |= PARTICLE_SYSTEM | TRANSFORM| RENDER;
    scene.components.velocity.x[p_s] = 0;
    scene.components.velocity.y[p_s] = 0;
    scene.components.velocity.z[p_s] = 0;
    scene.components.particle_system.life_time[p_s] = 10;
    scene.components.particle_system.force_masks[p_s] |= f_g_m;

    while(!WindowShouldClose()){
        //INPUT 
        InputSystem_Update(&cursor, &can_move);
        //UPDATE
        if (can_move){
            UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        }
        
        // Reset profiler
        profiler_data.SemiEulerSystem = 0;
        profiler_data.ParticleSystem= 0;
        profiler_data.LifeTimeSystem= 0;

        for (ENTITY e = 1; e <= scene.last_entity; e++){
            if (scene.components.tags[e] & VALID){

                ForceGeneratorSystem_Update(&scene, e, TRANSFORM);

                timer = GetTime();
                SemiEulerSystem_Update(&scene, e,TRANSFORM, D_TIME);
                profiler_data.SemiEulerSystem += GetTime() - timer;

                timer = GetTime();
                ParticleSystem_Update(&scene, e, D_TIME);
                profiler_data.ParticleSystem += GetTime() - timer;

                timer = GetTime();
                LifeTimeSystem_Update(&scene, e, LIFE_TIME, D_TIME);
                profiler_data.LifeTimeSystem += GetTime() -  timer;
            }
        }

        // RENDER
        BeginDrawing();
        ClearBackground(WHITE);
        
        timer = GetTime();
        RenderSystem_Update(&scene, camera);
        profiler_data.RenderSystem = GetTime() - timer;

        timer = GetTime();
        GuiSystem_Update(&scene, &profiler_data);
        profiler_data.GuiSystem = GetTime() - timer;

        EndDrawing();

    }

    CloseWindow();

    return 0;
}
