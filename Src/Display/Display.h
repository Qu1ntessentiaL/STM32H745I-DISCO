#ifndef LTDC_H
#define LTDC_H

#include "stm32h7xx.h"
#include "system.h"
#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_lcd.h"

#define LCD_INSTANCE (LCD_INSTANCES_NBR - 1)

class Display {
public:
    explicit Display();

    ~Display();

    void DrawObjects();

private:
    void Error_Handler() {}
};

#endif //LTDC_H
