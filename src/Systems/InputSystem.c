#include "Systems.h"
#include <raylib.h>

void InputSystem_Update(Scene* scene, bool* cursor, bool* can_move, Camera3D* cam){
    
    if (false){
        // generador de fuerzas de explosión
        ENTITY f_e = FindNewEntitySpace(scene);
        scene->components.tags[f_e] |= TIMER;
        FORCE_GENERATOR_MASK f_e_m = NewForceGenerator(scene, f_e);
        scene->components.force_type[f_e_m] = EXPLOSION;
        scene->components.force_data[f_e_m].explosion.strength = 10;
        scene->components.force_data[f_e_m].explosion.radius = 50;
        scene->components.force_data[f_e_m].explosion.time = 0;
        scene->components.particle_system.force_masks[p_s] |= f_e_m;
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
