#include "Systems.h"


void GravityForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t){
    if (!(scene->components.tags[e] & t)) return;
    scene->components.force.x[e] += scene->force_generators.gravity.x;
    scene->components.force.y[e] += scene->force_generators.gravity.y;
    scene->components.force.z[e] += scene->force_generators.gravity.z;
}
