#ifndef HARDWARE_H
#define HARDWARE_H

#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

void Hardware_Init(void);
void UART_Print(const char* str);

#ifdef __cplusplus
}
#endif

#endif