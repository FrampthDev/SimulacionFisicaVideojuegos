#include "Systems.h"
#include <raylib.h>
#include "../Scenes/Scene.h"

void RenderSystem_Update(Scene* scene, Camera3D camera){
        BeginMode3D(camera);

        for (ENTITY e = 1; e <= scene->last_entity; e++){
            if (!(scene->components.tags[e] & (RENDER | SHAPE | VALID))) continue; 
            Vector3 position;
            position.x = scene->components.transform.position.x[e];
            position.y = scene->components.transform.position.y[e];
            position.z = scene->components.transform.position.z[e];

            switch(scene->components.shape[e].type){
                case SPHERE:
                    if (scene->components.tags[e] & PARTICLE)
                        DrawSphere(position,scene->components.shape[e].sphere.radius,BLUE);
                    else 
                        DrawSphereWires(position,scene->components.shape[e].sphere.radius,8,8,RED);
                break;
                case BOX:
                    DrawCubeWires(
                            position,
                            scene->components.shape[e].box.width,
                            scene->components.shape[e].box.height,
                            scene->components.shape[e].box.lenght,
                            RED
                            );
                    break;
                default:
                    break;
            }
           
        }
        EndMode3D();
 
}
