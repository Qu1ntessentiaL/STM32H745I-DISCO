#ifndef LTDC_H
#define LTDC_H

#include "stm32h7xx_hal_ltdc.h"

#define LCD_DISP_Pin GPIO_PIN_15
#define LCD_DISP_GPIO_Port GPIOJ

class Display {
public:
    explicit Display(LTDC_HandleTypeDef ltdcHandle);

    ~Display();

    LTDC_HandleTypeDef hltdc;

private:
    void Error_Handler() {}
};

#endif //LTDC_H
