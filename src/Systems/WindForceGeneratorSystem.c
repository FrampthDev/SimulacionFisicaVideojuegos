#include "Systems.h"

void WindForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t){
    if (!(scene->components.tags[e] & t)) return;

    scene->components.force.x[e] += scene->force_generators.wind.strength *
                                    (scene->force_generators.wind.velocity.x -
                                     scene->components.velocity.x[e]);
    scene->components.force.y[e] += scene->force_generators.wind.strength *
                                    (scene->force_generators.wind.velocity.y -
                                     scene->components.velocity.y[e]);
    scene->components.force.z[e] += scene->force_generators.wind.strength *
                                    (scene->force_generators.wind.velocity.z -
                                     scene->components.velocity.z[e]);
}
