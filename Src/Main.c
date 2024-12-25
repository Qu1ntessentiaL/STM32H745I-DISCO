#include "stdio.h"

#include "stm32h7xx.h"

#include "usart.h"
#include "fmc.h"

#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_lcd.h"
#include "stm32h745i_discovery_ts.h"
#include "stm32h745i_discovery_qspi.h"
#include "stm32h745i_discovery_sdram.h"

#include "lvgl.h"
#include "lvgl_port_lcd.h"
#include "lvgl_port_touchpad.h"
#include "../Drivers/lvgl/demos/lv_demos.h"
#include "../Drivers/lvgl/demos/widgets/lv_demo_widgets.h"

#include "test.h"

extern void SystemClock_Config(void);
//extern void MPU_Config(void);

int __write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart3, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}

void MPU_Config(void)
{
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
    MPU_InitStruct.Size = MPU_REGION_SIZE_16MB;
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


int main() {
    //MPU_Config();
    SCB_EnableICache();
    SCB_EnableDCache();

    HAL_Init();
    SystemClock_Config();

    //MX_FMC_Init();
    MX_USART3_UART_Init();
    printf("Started!\n\r");

    BSP_QSPI_Init_t qspi_init;
    qspi_init.InterfaceMode = MT25TL01G_QPI_MODE;
    qspi_init.TransferRate = MT25TL01G_DTR_TRANSFER;
    qspi_init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;
    BSP_QSPI_Init(0, &qspi_init);
    BSP_QSPI_EnableMemoryMappedMode(0);

    lcd_init();
    lv_init();
    lv_demo_benchmark();

    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);

    while (1) {
        lv_task_handler();
        BSP_LED_Toggle(LED_RED);
        HAL_Delay(5);
    }
}
