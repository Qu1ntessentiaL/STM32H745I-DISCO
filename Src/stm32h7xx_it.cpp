#include "main.h"
#include "stm32h7xx_it.h"

extern DMA_HandleTypeDef hdma_i2c4_rx;
extern DMA_HandleTypeDef hdma_i2c4_tx;
extern I2C_HandleTypeDef hi2c4;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef huart3;

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
    lv_tick_inc(1);
}

void DMA1_Stream0_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_usart3_rx);
}


void DMA1_Stream1_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_usart3_tx);
}

void USART3_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart3);
}

/*
void TIM17_IRQHandler(void) {
    HAL_TIM_IRQHandler(&htim17);
}

void BDMA_Channel0_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_i2c4_rx);
}

void BDMA_Channel1_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_i2c4_tx);
}
*/

void MDMA_IRQHandler(void) {
    BSP_SDRAM_IRQHandler(0);
}