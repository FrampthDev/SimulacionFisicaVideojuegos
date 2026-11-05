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
    
    scene.force_generators.gravity.y = -9.8;

    scene.force_generators.wind.velocity.z = 10;
    scene.force_generators.wind.strength = 3;

    scene.force_generators.whirlwind.strength = 2;
    scene.force_generators.whirlwind.vertical_strength = 2;

    scene.force_generators.explosion.strength = 50;
    scene.force_generators.explosion.max_time = 10;
    scene.force_generators.explosion.time = 0.1;
    scene.force_generators.explosion.radius = 20;
    scene.force_generators.explosion.exploding = false;

    // sistema de partículas
    p_s = FindNewEntitySpace(&scene);
    scene.components.tags[p_s] |= PARTICLE_SYSTEM | TRANSFORM | SHAPE;
    scene.components.shape[p_s].type = SPHERE;
    scene.components.shape[p_s].sphere.radius = 5;
    scene.components.particle_system.initial_movement[p_s] = false;
    scene.components.particle_system.life_time[p_s] = 10;
    scene.components.particle_system.tags[p_s] = GRAVITY| WIND | WHIRLWIND | EXPLOSION;

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

        //Timer explosion
        //Tiene que estar fuera de los sistemas porque solo hay uno
        if (scene.force_generators.explosion.exploding){
            scene.force_generators.explosion.timer += GetFrameTime();
        }
        if (scene.force_generators.explosion.timer > scene.force_generators.explosion.time){
            scene.force_generators.explosion.timer = 0;
            scene.force_generators.explosion.exploding = false;
        }
 

        for (ENTITY e = 1; e <= scene.last_entity; e++){

            if (scene.components.tags[e] & VALID){
                if(scene.force_generators.gravity_active) GravityForceGeneratorSystem_Update(&scene, e, GRAVITY);
                if(scene.force_generators.wind_active) WindForceGeneratorSystem_Update(&scene, e, WIND);
                if(scene.force_generators.whirlwind_active) WhirlwindForceGeneratorSystem_Update(&scene, e, WHIRLWIND);
                ExplosionForceGeneratorSystem_Update(&scene, e, EXPLOSION);

                timer = GetTime();
                SemiEulerSystem_Update(&scene, e,TRANSFORM, D_TIME);
                profiler_data.SemiEulerSystem += GetTime() - timer;

                timer = GetTime();
                ParticleSystem_Update(&scene, e, PARTICLE_SYSTEM, D_TIME);
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
