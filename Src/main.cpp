#include "stm32h7xx.h"
#include "main.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_fs.h"
#include "stm32h745i_discovery_sdram.h"
#include "stm32h745i_discovery_qspi.h"
#include "BSP_Periph/Display.h"
#include "BSP_Periph/TouchScreen.h"
#include "IIC/IIC.h"

extern "C" void SystemClock_Config(void);
extern "C" void Error_Handler(void);

int main() {
    HAL_Init();
    SystemClock_Config();
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    while (1) {
        BSP_LED_Toggle(LED_GREEN);
        HAL_Delay(1000);
    }
}
