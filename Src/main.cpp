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

//#include "BSP_Periph/Display.h"
//#include "BSP_Periph/TouchScreen.h"
#include "IIC/IIC.h"

extern "C" void SystemClock_Config(void);
extern "C" void Error_Handler(void);
/*
extern "C" int _write(int file, char *ptr, int len) {
    if (file == 1) {
        HAL_UART_Transmit(&huart3, (uint8_t *) ptr, len, HAL_MAX_DELAY);
        return len;
    }
    return -1;
}
*/
int main() {
    HAL_Init();
    SystemClock_Config();
    //BSP_LED_Init(LED_RED);
    //BSP_LED_Init(LED_GREEN);
    while (1) {
        //printf("Hello!\n\r");
        //BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(1000);
    }
}
