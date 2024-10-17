#include "main.h"
#include "lvgl.h"

UART_HandleTypeDef huart3;
I2C_HandleTypeDef hi2c4;

int main() {
    HAL_Init();
    SystemClock_Config();
    USART3_Init();
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    TouchScreen ts;
    lv_init();
    while (1) {
        for (uint8_t i = 0; i < 5; i++) {
            if (ts.m_ts_multi.TouchX[i] > 240) {
                BSP_LED_On(LED_GREEN);
            }
        }
        BSP_LED_Toggle(LED_RED);
        HAL_Delay(1000);

    }
}
