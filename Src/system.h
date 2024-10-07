#ifndef SYSTEM_H
#define SYSTEM_H

#define LCD_DISP_Pin GPIO_PIN_15
#define VCP_TX_Pin GPIO_PIN_10
#define VCP_RX_Pin GPIO_PIN_11

#include "stm32h7xx.h"

void SystemClock_Config();

void USART3_Init();

void USART3_SendMessage(const char *str);

extern "C" void I2C4_Init();



#endif //SYSTEM_H
