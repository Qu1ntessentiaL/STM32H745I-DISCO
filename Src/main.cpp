#include "iostream"

#include "stm32h7xx.h"

#include "usart.h"

#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_lcd.h"
#include "stm32h745i_discovery_qspi.h"
#include "stm32h745i_discovery_sdram.h"

#include "lvgl.h"
#include "lvgl_port_lcd.h"
#include "lvgl_port_touchpad.h"
#include "../Drivers/lvgl/demos/lv_demos.h"
#include "../Drivers/lvgl/demos/widgets/lv_demo_widgets.h"

#include "../h7disco/src/ui/ui.h"

//extern "C" void SystemClock_Config(void);
extern "C" void Error_Handler(void);
extern "C" void MPU_Config(void);

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
    MPU_Config();
    SCB_EnableICache();
    SCB_EnableDCache();

    HAL_Init();
    SystemClock_Config();
    MX_USART3_UART_Init();
    HAL_UART_Transmit(&huart3, reinterpret_cast<const uint8_t *>("Started!\n\r"), 4, 1000);
    //BSP_LED_Init(LED_GREEN);
    //BSP_LED_Init(LED_RED);

    BSP_QSPI_Init_t qspi_init;
    qspi_init.InterfaceMode = MT25TL01G_QPI_MODE;
    qspi_init.TransferRate = MT25TL01G_DTR_TRANSFER;
    qspi_init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;
    BSP_QSPI_Init(0, &qspi_init);
    BSP_QSPI_EnableMemoryMappedMode(0);

    BSP_SDRAM_Init(0);

    lv_init();
    LCD_init();
    touchpad_init();
    //lv_demo_widgets();
    ui_init();
    while (1) {
        //BSP_LED_Toggle(LED_GREEN);
        //lv_task_handler();
        HAL_Delay(5);
        ui_tick();
        //printf("abc\n\r");
    }
}

extern "C" void MPU_Config(void) {
    MPU_Region_InitTypeDef MPU_InitStruct = {0};

    /* Disables the MPU */
    HAL_MPU_Disable();
    /** Initializes and configures the Region and the memory to be protected
    */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress = 0x0;
    MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
    MPU_InitStruct.SubRegionDisable = 0x87;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    /** Initializes and configures the Region and the memory to be protected
    */
    MPU_InitStruct.Number = MPU_REGION_NUMBER1;
    MPU_InitStruct.BaseAddress = 0xD0000000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
    MPU_InitStruct.SubRegionDisable = 0x0;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    /** Initializes and configures the Region and the memory to be protected
    */
    MPU_InitStruct.Number = MPU_REGION_NUMBER2;
    MPU_InitStruct.BaseAddress = 0x90000000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_128MB;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);
    /* Enables the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
