#include "iostream"

#include "stm32h7xx.h"

#include "bdma.h"
#include "dma.h"
#include "eth.h"
#include "fdcan.h"
#include "i2c.h"
#include "quadspi.h"
#include "sai.h"
#include "sdmmc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

#include "stm32h745i_discovery_sdram.h"
#include "stm32h745i_discovery_qspi.h"

#include "BSP_Periph/Display.h"
#include "IIC/IIC.h"

//extern "C" void SystemClock_Config(void);
extern "C" void Error_Handler(void);

extern "C" int __write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart3, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}

void SystemClock_Config() {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 5;  // Делитель: 25 МГц / 5 = 5 МГц
    RCC_OscInitStruct.PLL.PLLN = 96; // Множитель: 5 МГц * 96 = 480 МГц
    RCC_OscInitStruct.PLL.PLLP = 2;  // SYSCLK = 480 МГц
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; // AHB = 480 МГц
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // APB1 = 240 МГц
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  // APB2 = 240 МГц
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
}

int main() {
    HAL_Init();
    SystemClock_Config();
    MX_USART3_UART_Init();
    Display disp;
    disp.DrawObjects();
    HAL_UART_Transmit(&huart3, reinterpret_cast<const uint8_t *>("Ws\n\r"), 4, 1000);
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    while (1) {
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(1000);
    }
}
