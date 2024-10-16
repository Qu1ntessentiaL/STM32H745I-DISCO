#include "main.h"
#include "stm32h7xx_it.h"

extern UART_HandleTypeDef huart3;
extern I2C_HandleTypeDef hi2c4;

void NMI_Handler(void) {
    while (1) {}
}

void HardFault_Handler(void) {
    while (1) {}
}

void MemManage_Handler(void) {
    while (1) {}
}

void BusFault_Handler(void) {
    while (1) {}
}

void UsageFault_Handler(void) {
    while (1) {}
}

void SVC_Handler(void) {}

void DebugMon_Handler(void) {}

void PendSV_Handler(void) {}

void SysTick_Handler(void) {
    HAL_IncTick();
}

void USART3_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart3);
}
