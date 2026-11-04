#include <raylib.h>
#define RAYGUI_IMPLEMENTATION

#include "Scenes/Scene.h"
#include "Systems/Systems.h"
#include "assert.h"

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

    // generador de fuerzas gravedad
    ENTITY f_g = FindNewEntitySpace(&scene);
    FORCE_GENERATOR_MASK f_g_m = NewForceGenerator(&scene, f_g);
    scene.components.force_type[f_g_m] = LINEAL;
    scene.components.force_data[f_g_m].lineal.y = -9.8;

    // generador de fuerzas viento
    ENTITY f_w = FindNewEntitySpace(&scene);
    FORCE_GENERATOR_MASK f_w_m = NewForceGenerator(&scene, f_w);
    scene.components.force_type[f_w_m] = WIND;
    scene.components.force_data[f_w_m].wind.strength = 1;
    scene.components.force_data[f_w_m].wind.velocity.z = 5;

    // generador de fuerzas torbellino
    ENTITY f_t = FindNewEntitySpace(&scene);
    FORCE_GENERATOR_MASK f_t_m = NewForceGenerator(&scene, f_t);
    scene.components.force_type[f_t_m] = WHIRLWIND;
    scene.components.force_data[f_t_m].whirlwind.strength = 3;
    scene.components.force_data[f_t_m].whirlwind.vertical_strength= 20;

    // explosión
    ENTITY f_e = FindNewEntitySpace(&scene);
    scene.components.tags[f_e] |= TIMER | LIFE_TIME;
    scene.components.life_time[f_e] = 3;
    FORCE_GENERATOR_MASK f_e_m = NewForceGenerator(&scene, f_e);
    scene.components.force_type[f_e_m] = EXPLOSION;
    scene.components.force_data[f_e_m].explosion.strength = 5;
    scene.components.force_data[f_e_m].explosion.radius = 20;
    scene.components.force_data[f_e_m].explosion.time = 0.5;
 
    // sistema de partículas
    p_s = FindNewEntitySpace(&scene);
    scene.components.tags[p_s] |= PARTICLE_SYSTEM | TRANSFORM | RENDER;
    scene.components.transform.position.x[p_s] = 0;
    scene.components.transform.position.y[p_s] = 0;
    scene.components.transform.position.z[p_s] = 0;
    scene.components.particle_system.life_time[p_s] = 3;
    scene.components.particle_system.force_masks[p_s] |= f_e_m | f_g_m;
    
    // bucle
    while(!WindowShouldClose()){
        //INPUT 
        InputSystem_Update(&scene, &cursor, &can_move, &camera);
        //UPDATE
        if (can_move){
            UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        }
        // Reset profiler
        profiler_data.SemiEulerSystem = 0;
        profiler_data.ParticleSystem= 0;
        profiler_data.LifeTimeSystem= 0;
        profiler_data.ForceGeneratorSystem = 0;

        for (ENTITY e = 1; e <= scene.last_entity; e++){
            if (scene.components.tags[e] & VALID){

                timer = GetTime();
                ForceGeneratorSystem_Update(&scene, e, TRANSFORM);
                profiler_data.ForceGeneratorSystem += GetTime() - timer;

                timer = GetTime();
                SemiEulerSystem_Update(&scene, e,TRANSFORM, D_TIME);
                profiler_data.SemiEulerSystem += GetTime() - timer;

                timer = GetTime();
                ParticleSystem_Update(&scene, e, D_TIME);
                profiler_data.ParticleSystem += GetTime() - timer;

                timer = GetTime();
                LifeTimeSystem_Update(&scene, e, LIFE_TIME, D_TIME);
                profiler_data.LifeTimeSystem += GetTime() -  timer;

                TimerSystem_Update(&scene, e);
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
