#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1080


#define ENTITY uint16_t
#define MAX_FORCE_GENERATORS 64
#define SHAPE_TIME_SCALE_FACTOR 0.1
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
