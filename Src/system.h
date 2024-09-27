#ifndef SYSTEM_H
#define SYSTEM_H

#define LCD_DISP_Pin GPIO_PIN_15
#define VCP_TX_Pin GPIO_PIN_10
#define VCP_RX_Pin GPIO_PIN_11

#include <string>
#include "stm32h7xx.h"

void SystemClock_Config();

void PeriphCommonClock_Config();

class uart {
public:
    uart(UART_HandleTypeDef uart_handle);

    ~uart();

    UART_HandleTypeDef *get_handler();

    void send_message(const char *str);

private:
    UART_HandleTypeDef huart{};

    void Error_Handler();
};

void UART_VCP_Init();

#endif //SYSTEM_H
