#include "rtos_objects.h"

SemaphoreHandle_t serialMutex = NULL;

void RTOS_InitObjects(void) {
    serialMutex = xSemaphoreCreateMutex();
}