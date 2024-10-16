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

        /*
        if (BSP_TS_Get_MultiTouchState(Instance, &m_ts_multi) == BSP_ERROR_NONE) {
            if (m_ts_single.TouchDetected) {
                uint16_t x = m_ts_single.TouchX;
                char buffer[20];
                int length = sprintf(buffer, "x: %hu\r\n", x);
                HAL_UART_Transmit(&huart3, (uint8_t *) buffer, length, 1000);
                uint16_t y = m_ts_single.TouchY;
                length = sprintf(buffer, "y: %hu\r\n", y);
                HAL_UART_Transmit(&huart3, (uint8_t *) buffer, length, 1000);

                if (x <= 240) {
                    BSP_LED_On(LED_GREEN);
                } else {
                    BSP_LED_Off(LED_GREEN);
                }
            } else {
                USART3_SendMessage("No touch detected\n\r");
            }
        } else {
            USART3_SendMessage("Error getting touch state!\n\r");
        }
        */
    }
}
