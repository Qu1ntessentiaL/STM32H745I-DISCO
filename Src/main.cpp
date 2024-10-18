#include "main.h"

UART_HandleTypeDef huart3;
I2C_HandleTypeDef hi2c4;

int main() {
    HAL_Init();
    SystemClock_Config();
    USART3_Init();
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);

    lv_init();
    touchpad_init();
    display_init();
    while (1) {
        BSP_LED_Toggle(LED_RED);
        HAL_Delay(1000);
    }
}
