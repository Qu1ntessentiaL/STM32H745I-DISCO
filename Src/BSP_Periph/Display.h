#ifndef LTDC_H
#define LTDC_H

#include <cstdio>

#include "stm32h7xx.h"
#include "stm32h745i_discovery_lcd.h"

#define LCD_INSTANCE (LCD_INSTANCES_NBR - 1)

class Display {
public:
    explicit Display();

    ~Display();

    void DrawObjects();
};

#endif //LTDC_H
