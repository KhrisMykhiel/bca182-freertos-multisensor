#include "hardware.h"
#include "rtos_objects.h"
#include "FreeRTOS.h"
#include "task.h"

void TaskA_Handler(void* pvParameters) {
    for (;;) {
        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
            UART_Print("[TASK A] Running - Blocking for 1s\r\n");
            xSemaphoreGive(serialMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void TaskB_Handler(void* pvParameters) {
    for (;;) {
        if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
            UART_Print("[TASK B] Running - Blocking for 2s\r\n");
            xSemaphoreGive(serialMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void HeartbeatTask(void* pvParameters) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    for (;;) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}   

int main(void) {
    Hardware_Init();
    RTOS_InitObjects();

    UART_Print("BCA182 FreeRTOS Multisensor\r\nSystem starting...\r\n");

    xTaskCreate(TaskA_Handler, "TaskA", 128, NULL, 2, NULL);
    xTaskCreate(TaskB_Handler, "TaskB", 128, NULL, 2, NULL);

    xTaskCreate(HeartbeatTask, "Heartbeat", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1) {
        // Unreachable
    }
}