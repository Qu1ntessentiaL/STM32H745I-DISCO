#include "main.h"

UART_HandleTypeDef huart3;
I2C_HandleTypeDef hi2c4;

uint16_t meas_value = 0;
//IIC twi(hi2c4);

int main() {
    HAL_Init();
    SystemClock_Config();
    USART3_Init();
    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);
    //twi.SendCMD(IIC::START_GAS, 0);
    //IIC twi(hi2c4);
    TouchScreen ts;
    while (1) {
        //twi.ReadREQ(IIC::GET_STATE, meas_value);
        //USART3_SendNumber(meas_value);

        BSP_LED_Toggle(LED_RED);
        HAL_Delay(1000);
    }
}
