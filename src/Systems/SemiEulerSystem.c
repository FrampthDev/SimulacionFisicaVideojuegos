#include "Systems.h"
#include <math.h>
void SemiEulerSystem_Update(Scene* scene, ENTITY e,Tags t, float dt){
    if (!(scene->components.tags[e] & t)) return;

    scene->components.acceleration.x[e] = scene->components.force.x[e] * (1 - scene->components.mass[e]);
    scene->components.acceleration.y[e] = scene->components.force.y[e] * (1 - scene->components.mass[e]);
    scene->components.acceleration.z[e] = scene->components.force.z[e] * (1 - scene->components.mass[e]);

    scene->components.velocity.x[e] += scene->components.acceleration.x[e]* dt;
    scene->components.velocity.y[e] += scene->components.acceleration.y[e]* dt;
    scene->components.velocity.z[e] += scene->components.acceleration.z[e]* dt;

    scene->components.transform.position.x[e] += scene->components.velocity.x[e]* dt;
    scene->components.transform.position.y[e] += scene->components.velocity.y[e]* dt;
    scene->components.transform.position.z[e] += scene->components.velocity.z[e]* dt;
    
    scene->components.velocity.x[e] *= pow(scene->components.damping[e], dt);
    scene->components.velocity.y[e] *= pow(scene->components.damping[e], dt);
    scene->components.velocity.z[e] *= pow(scene->components.damping[e], dt);

    scene->components.force.x[e] = 0;
    scene->components.force.y[e] = 0;
    scene->components.force.z[e] = 0;

}
