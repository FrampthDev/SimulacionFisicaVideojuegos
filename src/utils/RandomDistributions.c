#include "RandomDistributions.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


float GaussDistribution(){
    float x = (float)rand() / (float)RAND_MAX,
         y = (float)rand() / (float)RAND_MAX,
         z = sqrt(-2 * log(x)) * cos(2 * M_PI * y);///(max-min) + min;
    return z;
}

float LinealDistribution(float min, float max){
    float rnd = (((float)rand() / (float)RAND_MAX) * ((max - min))+ min);
    float x = ((float)rand() / (float)RAND_MAX);
    float y = x * ((max - min) + min);
    return rnd;
}
