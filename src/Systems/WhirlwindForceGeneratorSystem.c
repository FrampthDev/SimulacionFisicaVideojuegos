#include "Systems.h"

void WhirlwindForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t){
    if (!(scene->components.tags[e] & t)) return;

    scene->components.force.x[e] += scene->force_generators.whirlwind.strength *
                                    - (scene->components.transform.position.z[e] -
                                    scene->force_generators.whirlwind.z);
    scene->components.force.y[e] += scene->force_generators.whirlwind.strength *
                                    (scene->force_generators.whirlwind.vertical_strength - 
                                    (scene->components.transform.position.y[e] -
                                    scene->force_generators.whirlwind.y));
    scene->components.force.z[e] += scene->force_generators.whirlwind.strength *
                                    (scene->components.transform.position.x[e] -
                                    scene->force_generators.whirlwind.x);
}
