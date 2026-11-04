#ifndef GLOBALS_H
#define GLOBALS_H

#define ENTITY unsigned long int
#include <stdio.h>

typedef struct{

}GuiData;

typedef struct{
    //bool cursor;
    //bool can_move;
}ControllerData;

typedef struct{
    double SemiEulerSystem;
    double LifeTimeSystem;
    double ParticleSystem;
    double RenderSystem;
    double GuiSystem;
    double ForceGeneratorSystem;
    int Error;
}ProfilerData;
static ProfilerData pd;

static ENTITY p_s;

#endif
