#include "Systems.h"
#include <math.h>

void ExplosionForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t){
    if (!(scene->components.tags[e] & t)) return;
    if (!scene->force_generators.explosion.exploding) return;
    
   
    float r = sqrt(
        pow((scene->components.transform.position.x[e] - scene->force_generators.explosion.x),2) +
        pow((scene->components.transform.position.y[e] - scene->force_generators.explosion.y),2) +
        pow((scene->components.transform.position.z[e] - scene->force_generators.explosion.z),2));

    if (r > scene->force_generators.explosion.radius) return;
    if (r == 0) return;

    float r_squared = pow(r,2);
    
    scene->components.force.x[e] += (scene->force_generators.explosion.strength / r_squared) *
                                    (scene->components.transform.position.x[e] - scene->force_generators.explosion.x) *
                                    (pow(M_E, (scene->force_generators.explosion.timer / scene->force_generators.explosion.time)));
    scene->components.force.y[e] += (scene->force_generators.explosion.strength / r_squared) *
                                    (scene->components.transform.position.y[e] - scene->force_generators.explosion.y) *
                                    (pow(M_E, (scene->force_generators.explosion.timer / scene->force_generators.explosion.time)));
    scene->components.force.z[e] += (scene->force_generators.explosion.strength / r_squared) *
                                    (scene->components.transform.position.z[e] - scene->force_generators.explosion.z) *
                                    (pow(M_E, (scene->force_generators.explosion.timer / scene->force_generators.explosion.time)));

}
