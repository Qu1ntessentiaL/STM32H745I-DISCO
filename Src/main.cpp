#include "main.h"

UART_HandleTypeDef huart3;
I2C_HandleTypeDef hi2c4;

IIC twi(hi2c4);

int main() {
    HAL_Init();
    SystemClock_Config();
    USART3_Init();
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    while (1) {
        BSP_LED_Toggle(LED_RED);
        BSP_LED_Toggle(LED_GREEN);
        twi.SendCMD(IIC::START_GAS, 0);
        HAL_Delay(2000);
    }
}
