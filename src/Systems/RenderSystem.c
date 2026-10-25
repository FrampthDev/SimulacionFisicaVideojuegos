#include "Systems.h"
#include <raylib.h>
#include "../Scenes/Scene.h"

void RenderSystem_Update(Scene* scene, Camera3D camera){
        BeginMode3D(camera);
        for (ENTITY e = 1; e <= scene->last_entity; e++){
            if (scene->components.tags[e] & (RENDER | VALID) ){
                Vector3 position = {
                        scene->components.transform.position.x[e],
                        scene->components.transform.position.y[e],
                        scene->components.transform.position.z[e],
                };
                if (scene->components.tags[e] & PARTICLE_SYSTEM) DrawSphere(position, 1, RED);
                else if(scene->components.tags[e] & PARTICLE) DrawSphere(position, scene->components.life_time[e] * 0.1, BLUE);
            }

        }
        EndMode3D();
 
}
