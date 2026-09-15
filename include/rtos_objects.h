#ifndef RTOS_OBJECTS_H
#define RTOS_OBJECTS_H

#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t serialMutex;

void RTOS_InitObjects(void);

#endif