#include "stm32h7xx_it.h"

#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_lcd.h"
#include "stm32h745i_discovery_sdram.h"

#include "lvgl.h"

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
    __asm volatile (
            "TST lr, #4 \n"
            "ITE EQ \n"
            "MRSEQ r0, msp \n"
            "MRSNE r0, psp \n"
            "MOV r1, r2 \n"
            "MOV r2, r3 \n"
            "MOV r3, r4 \n"
            "MOV r4, r5 \n"
            "MOV r5, r6 \n"
            "MOV r6, r7 \n"
            "MOV r7, r8 \n"
            "MOV r8, r9 \n"
            "MOV r9, r10 \n"
            "MOV r10, r11 \n"
            "MOV r11, r12 \n"
            "MOV r12, lr \n"
            "MOV lr, r14 \n"
            );
    while (1);
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

/*
void DMA1_Stream0_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_usart3_rx);
}


void DMA1_Stream1_IRQHandler(void) {
    HAL_DMA_IRQHandler(&hdma_usart3_tx);
}
*/
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