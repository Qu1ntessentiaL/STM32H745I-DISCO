#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include "stm32h7xx.h"

#define LCD_LAYER_0_ADDRESS 0xD0000000U

void DrawTestPattern(void);

void SDRAM_Test(void);

#endif //TEST_H
