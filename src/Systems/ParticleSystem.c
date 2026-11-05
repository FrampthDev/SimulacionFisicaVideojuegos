#include "Systems.h"

#include "../utils/RandomDistributions.h"

#include <stdlib.h>
#include <math.h>

void ParticleSystem_Update(Scene* scene, ENTITY e, Tags t, float dt){
    if (!(scene->components.tags[e] & t)) return;

    if ((int)random() % 100 > 99) return;

    ENTITY particle = FindNewEntitySpace(scene);
    scene->components.tags[particle] |= RENDER | TRANSFORM | LIFE_TIME | SHAPE | PARTICLE |scene->components.particle_system.tags[e];

    if (scene->components.tags[e] & SHAPE){

        switch(scene->components.shape[e].type){
            case SPHERE:
            {
                // recurso: https://www.karlsims.com/random-in-sphere.html

                float y = LinealDistribution(-1 ,1);
                float r = sqrt(1 - y*y) *scene->components.shape[e].sphere.radius;
                y *= scene->components.shape[e].sphere.radius;
                float length = LinealDistribution(-M_PI , M_PI);
                float x = r * sin(length);
                float z = r * cos(length);
                scene->components.transform.position.x[particle] = x * pow(LinealDistribution(0,1), (float)1/3);
                scene->components.transform.position.y[particle] = y * pow(LinealDistribution(0,1), (float)1/3);
                scene->components.transform.position.z[particle] = z * pow(LinealDistribution(0,1), (float)1/3);

                break;
            }
            case BOX:
                scene->components.transform.position.x[particle] = LinealDistribution(
                    scene->components.transform.position.x[e] - scene->components.shape[e].box.width/ 2,
                    scene->components.transform.position.x[e] + scene->components.shape[e].box.width/ 2
                    );
                scene->components.transform.position.y[particle] = LinealDistribution(
                    scene->components.transform.position.y[e] - scene->components.shape[e].box.height/ 2,
                    scene->components.transform.position.y[e] + scene->components.shape[e].box.height/ 2
                    );
                scene->components.transform.position.z[particle] = LinealDistribution(
                    scene->components.transform.position.z[e] - scene->components.shape[e].box.lenght/ 2,
                    scene->components.transform.position.z[e] + scene->components.shape[e].box.lenght/ 2
                    );

                break;
            default: break;
        }
    }
    else{
        scene->components.transform.position.x[particle] = scene->components.transform.position.x[e];
        scene->components.transform.position.y[particle] = scene->components.transform.position.y[e];
        scene->components.transform.position.z[particle] = scene->components.transform.position.z[e];
    }
    if (scene->components.particle_system.initial_movement[e]){
        scene->components.velocity.x[particle] = GaussDistribution();
        scene->components.velocity.y[particle] = GaussDistribution();
        scene->components.velocity.z[particle] = GaussDistribution();
    }
    scene->components.mass[particle] = 0.1; // 100gr
    scene->components.damping[particle] = 0.95;
    scene->components.life_time[particle] = scene->components.particle_system.life_time[e];
    scene->components.max_life_time[particle] = scene->components.particle_system.life_time[e];

    scene->components.shape[particle].type = SPHERE;
    scene->components.shape[particle].sphere.radius = (scene->components.life_time[particle] / scene->components.max_life_time[particle]) * SHAPE_TIME_SCALE_FACTOR;


}
