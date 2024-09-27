#include "main.h"

UART_HandleTypeDef huart3;

int main() {
    HAL_Init();
    SystemClock_Config();
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    uart uart_debug(huart3);
    TouchScreen ts1;
    while (1) {
        BSP_LED_Toggle(LED_RED);
        uart_debug.send_message("LED_RED_Toggled!\n\r");
        HAL_Delay(1000);
    }
}