#include "system.h"
#include <cstring>
#include <cstdio>

extern UART_HandleTypeDef huart3;
I2C_HandleTypeDef hi2c4;

void Error_Handler() {

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
