#include "Systems.h"
#include <raylib.h>
#include <math.h>

void InputSystem_Update(Scene* scene, bool* cursor, bool* can_move, Camera3D* cam){
    if (IsKeyPressed(KEY_E) && !scene->force_generators.explosion.exploding){
        scene->force_generators.explosion.exploding = true;
    }

    if(IsKeyPressed(KEY_F1)){
        scene->force_generators.gravity_active = !scene->force_generators.gravity_active;
    }
    if(IsKeyPressed(KEY_F2)){
        scene->force_generators.wind_active = !scene->force_generators.wind_active;
    }
    if(IsKeyPressed(KEY_F3)){
        scene->force_generators.whirlwind_active = !scene->force_generators.whirlwind_active;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        ENTITY bullet = FindNewEntitySpace(scene);
        float mass = 0.030; // 30g
        float real_speed = 110; // 110m/s
        float adjusted_speed = 10; // 1m/s (Las partículas son muy pequeñas y si aumentas la velocidad a 20m/s cuesta verlas)
        
        scene->components.tags[bullet] |= VALID | SHAPE | PARTICLE | LIFE_TIME | TRANSFORM | GRAVITY;

        scene->components.shape[bullet].type = SPHERE;
        //scene->components.shape[bullet].sphere.radius = (scene->components.life_time[bullet] / scene->components.max_life_time[bullet]) * SHAPE_TIME_SCALE_FACTOR;

        scene->components.life_time[bullet] = 10;
        scene->components.max_life_time[bullet] = 10;

        scene->components.transform.position.x[bullet] = cam->position.x; 
        scene->components.transform.position.y[bullet] = cam->position.y; 
        scene->components.transform.position.z[bullet] = cam->position.z; 

        scene->components.mass[bullet] = mass * pow(real_speed / adjusted_speed,2);
        scene->components.damping[bullet] = 0.95;
        
        // HACK: raylib no expone el "eye" o dirección de la cámara, pero se puede conseguir con un ray
        Vector2 pos = {SCREEN_HEIGHT/2,SCREEN_WIDTH/2};
        Ray dir_ray = GetScreenToWorldRay(pos,*cam);
        Vector3 dir = dir_ray.direction;
        scene->components.velocity.x[bullet] = dir.x * adjusted_speed;
        scene->components.velocity.y[bullet] = dir.y * adjusted_speed;
        scene->components.velocity.z[bullet] = dir.z * adjusted_speed;

    }
   
    //TODO: cambiar la velocidad a una constante global
    if (IsKeyDown(KEY_SPACE)){
        cam->position.y += 0.3;
    }
    else if (IsKeyDown(KEY_C)){
        cam->position.y -= 0.3;
    }

    //TODO: arreglar este horror
    if (IsKeyPressed(KEY_P)){
        if (cursor){
            *cursor= false;
            *can_move= true;
            DisableCursor();
        }
        else{
            *cursor= true;
            *can_move= false;
            EnableCursor();
        }
    }
}
