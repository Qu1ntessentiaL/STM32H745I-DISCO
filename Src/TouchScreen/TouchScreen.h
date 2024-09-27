#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include "stm32h7xx.h"
#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_bus.h"
#include "stm32h745i_discovery_ts.h"

class TouchScreen {
public:
    TouchScreen();

    ~TouchScreen();

private:
    void Error_Handler();
};

#endif //TOUCHSCREEN_H
