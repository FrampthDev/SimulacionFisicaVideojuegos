#include "Systems.h"

void ForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t){
    /*
    if (!(scene->components.tags[e] & t)) return;

    for (int i = 0; i < scene->components.num_force_generators; i++){
        FORCE_GENERATOR_MASK mask = 1 << i;
        force_generator_data force_data = scene->components.force_generator_data[e];
        if (force_data.mask & mask && scene->components.force_valid[force_data.id]){
        printf("%d, %lu, %d \n",force_data.id, force_data.mask, scene->components.force_type[force_data.id]);
            ENTITY force_generator = force_data.id;
            switch(scene->components.force_type[force_data.id]){
                case LINEAL:
                    scene->components.force.x[e] += scene->components.force_data[force_data.id].lineal.x;
                    scene->components.force.y[e] += scene->components.force_data[force_data.id].lineal.y;
                    scene->components.force.z[e] += scene->components.force_data[force_data.id].lineal.z;
                    break;
                case WIND:
                    scene->components.force.x[e] += scene->components.force_data[force_data.id].wind.strength
                                                    * (scene->components.force_data[force_data.id].wind.velocity.x
                                                    - scene->components.velocity.x[e]);
                    scene->components.force.y[e] += scene->components.force_data[force_data.id].wind.strength
                                                    * (scene->components.force_data[force_data.id].wind.velocity.y
                                                    - scene->components.velocity.y[e]);
                    scene->components.force.z[e] += scene->components.force_data[force_data.id].wind.strength
                                                    * (scene->components.force_data[force_data.id].wind.velocity.z
                                                    - scene->components.velocity.z[e]);
                    break;
                case WHIRLWIND:
                    scene->components.force.x[e] += scene->components.force_data[force_data.id].whirlwind.strength
                                                    * - (scene->components.transform.position.z[e]               
                                                     - scene->components.transform.position.z[force_generator]);
                    scene->components.force.y[e] += scene->components.force_data[force_data.id].whirlwind.strength
                                                    * (50 - ( scene->components.transform.position.y[e]          
                                                            - scene->components.transform.position.y[force_generator]));
                    scene->components.force.z[e] += scene->components.force_data[force_data.id].whirlwind.strength     
                                                   *  (scene->components.transform.position.x[e]                   
                                                     -scene->components.transform.position.x[force_generator]);
                    break;
                case EXPLOSION:
                {
                    if (!(scene->components.tags[force_generator] & TIMER)) break;
                    // Distancia de la partícula a la explosión
                    float r = sqrt(
                        pow((scene->components.transform.position.x[e] - scene->components.transform.position.x[force_generator]),2) +
                        pow((scene->components.transform.position.y[e] - scene->components.transform.position.y[force_generator]),2) +
                        pow((scene->components.transform.position.z[e] - scene->components.transform.position.z[force_generator]),2));

                    if (r > scene->components.force_data[force_data.id].explosion.radius) break;

                    if (r == 0) break;

                    float r_squared = pow(r,2);

                    scene->components.force.x[e] += (scene->components.force_data[force_data.id].explosion.strength / r_squared) *
                                                    (scene->components.transform.position.x[e] - scene->components.transform.position.x[force_generator]) *
                                                    - (pow(M_E,(scene->components.timer[force_generator] / scene->components.force_data[force_data.id].explosion.time))); 
                    scene->components.force.y[e] += (scene->components.force_data[force_data.id].explosion.strength / r_squared) *
                                                    (scene->components.transform.position.y[e] - scene->components.transform.position.y[force_generator]) *
                                                    - (pow(M_E,(scene->components.timer[force_generator] / scene->components.force_data[force_data.id].explosion.time)));
                    scene->components.force.z[e] += (scene->components.force_data[force_data.id].explosion.strength / r_squared) *
                                                    (scene->components.transform.position.z[e] - scene->components.transform.position.z[force_generator]) *
                                                    - (pow(M_E,(scene->components.timer[force_generator] / scene->components.force_data[force_data.id].explosion.time)));
                    if (scene->components.timer[force_generator] > scene->components.force_data[force_data.id].explosion.time){
                        EraseForceGenerator(scene,mask);
                    }
                    break;
                }
                default:
                    break;
            }

        }
    }  
*/
}
