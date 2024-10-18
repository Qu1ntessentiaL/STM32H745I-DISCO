#ifndef LTDC_H
#define LTDC_H

#include "stm32h7xx.h"
#include "stm32h745i_discovery_lcd.h"
#include "BSP_Common.h"

#define LCD_INSTANCE (LCD_INSTANCES_NBR - 1)

class Display : public BSP_Common {
public:
    explicit Display();

    ~Display();

    void DrawObjects();
};

#endif //LTDC_H
