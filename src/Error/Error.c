#include "Error.h"
#include "stdio.h"
#include "../Globals.h"
char ErrorMSG[1024];

void LogError(ProfilerData* log){
    log->Error++;
}

