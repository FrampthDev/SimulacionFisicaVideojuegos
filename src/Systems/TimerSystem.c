#include "Systems.h"


void TimerSystem_Update(Scene* scene, ENTITY e){
    if (!(scene->components.tags[e] & TIMER)) return;
    scene->components.timer[e] += GetFrameTime();
}
