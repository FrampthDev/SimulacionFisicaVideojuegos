#include "Systems.h"
#include <math.h>

void ForceGeneratorSystem_Update(Scene* scene, ENTITY e, Tags t){
    if (!(scene->components.tags[e] & t)) return;

    for (int i = 0; i < scene->components.num_force_generators; i++){
        FORCE_GENERATOR_MASK mask = 1 << i;
        if (scene->components.force_mask[e] & mask){
            ENTITY force_generator = scene->components.force_generators[mask];
            switch(scene->components.force_type[mask]){
                case LINEAL:
                    scene->components.force.x[e] += scene->components.force_data[mask].lineal.x;
                    scene->components.force.y[e] += scene->components.force_data[mask].lineal.y;
                    scene->components.force.z[e] += scene->components.force_data[mask].lineal.z;
                    break;
                case WIND:
                    scene->components.force.x[e] += scene->components.force_data[mask].wind.strength
                                                    * (scene->components.force_data[mask].wind.velocity.x
                                                    - scene->components.velocity.x[e]);
                    scene->components.force.y[e] += scene->components.force_data[mask].wind.strength
                                                    * (scene->components.force_data[mask].wind.velocity.y
                                                    - scene->components.velocity.y[e]);
                    scene->components.force.z[e] += scene->components.force_data[mask].wind.strength
                                                    * (scene->components.force_data[mask].wind.velocity.z
                                                    - scene->components.velocity.z[e]);
                    break;
                case WHIRLWIND:
                    scene->components.force.x[e] += scene->components.force_data[mask].whirlwind.strength                   // K
                                                    * - (scene->components.transform.position.z[e]                          // * -( z
                                                     - scene->components.transform.position.z[force_generator]);            // - z_c)
                    scene->components.force.y[e] += scene->components.force_data[mask].whirlwind.strength                   // K
                                                    * (50 - ( scene->components.transform.position.y[e]                     // * (50-(y //TODO: cambiar este 50 a la propiedad del torbellino
                                                            - scene->components.transform.position.y[force_generator]));    // -y_c)
                    scene->components.force.z[e] += scene->components.force_data[mask].whirlwind.strength                   // K
                                                   *  (scene->components.transform.position.x[e]                            // * (x
                                                     -scene->components.transform.position.x[force_generator]);             // -x_c)
                    break;
                case EXPLOSION:
                {
                    if (!(scene->components.tags[force_generator] & TIMER)) break;
                    //printf("%lu\n", mask);
                    // Distancia de la partícula a la explosión
                    float r = sqrt(
                        pow((scene->components.transform.position.x[e] - scene->components.transform.position.x[force_generator]),2) +
                        pow((scene->components.transform.position.y[e] - scene->components.transform.position.y[force_generator]),2) +
                        pow((scene->components.transform.position.z[e] - scene->components.transform.position.z[force_generator]),2));

                    if (r > scene->components.force_data[mask].explosion.radius) break;

                    //printf("%f\n",scene->components.timer[force_generator]);
                    //printf("%f^%f = %f\n",(scene->components.transform.position.x[e] - scene->components.transform.position.x[force_generator]), 2.0f ,pow((scene->components.transform.position.x[e] - scene->components.transform.position.x[force_generator]),2));
                    //printf("E:%lu - %f\n",e, (scene->components.force_data[mask].explosion.strength / pow(r,2)) *
                                                    //(scene->components.transform.position.x[e] - scene->components.transform.position.x[force_generator]) *
                                                    //- (pow(M_E,(scene->components.timer[force_generator] / scene->components.force_data[mask].explosion.time))));
                    if (r == 0) break;

                    float r_squared = pow(r,2);

                    scene->components.force.x[e] += (scene->components.force_data[mask].explosion.strength / r_squared) *
                                                    (scene->components.transform.position.x[e] - scene->components.transform.position.x[force_generator]) *
                                                    - (pow(M_E,(scene->components.timer[force_generator] / scene->components.force_data[mask].explosion.time))); 
                    scene->components.force.y[e] += (scene->components.force_data[mask].explosion.strength / r_squared) *
                                                    (scene->components.transform.position.y[e] - scene->components.transform.position.y[force_generator]) *
                                                    - (pow(M_E,(scene->components.timer[force_generator] / scene->components.force_data[mask].explosion.time)));
                    scene->components.force.z[e] += (scene->components.force_data[mask].explosion.strength / r_squared) *
                                                    (scene->components.transform.position.z[e] - scene->components.transform.position.z[force_generator]) *
                                                    - (pow(M_E,(scene->components.timer[force_generator] / scene->components.force_data[mask].explosion.time)));
                    if (scene->components.timer[force_generator] > scene->components.force_data[mask].explosion.time){
                        
                    }
                    break;
                }
                default:
                    break;
            }

        }
    }  
}
