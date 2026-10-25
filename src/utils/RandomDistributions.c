#include "RandomDistributions.h"
#include <math.h>
#include <stdlib.h>


float GaussDistribution(float min, float max){
    float x = (float)rand() / (float)RAND_MAX,
         y = (float)rand() / (float)RAND_MAX,
         z = sqrt(-2 * log(x)) * cos(2 * M_PI * y);///(max-min) + min;
    return z;
}

float LinealDistribution(float min, float max){
   return ((float)rand() / ((float)RAND_MAX/(max-min))) + min;

}
