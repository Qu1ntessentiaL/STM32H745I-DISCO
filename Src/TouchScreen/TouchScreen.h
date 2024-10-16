#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include "stm32h7xx.h"
#include "system.h"
#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_bus.h"
#include "stm32h745i_discovery_lcd.h"
#include "stm32h745i_discovery_ts.h"

#define TS_INSTANCE (TS_INSTANCES_NBR - 1)

class TouchScreen {
public:
    static TouchScreen *m_Instance;

    TouchScreen();

    ~TouchScreen();

    void BSP_TS_Callback_Handler(uint32_t Instance);

    /// Статический callback
    static void BSP_TS_Callback(uint32_t Instance) {
        USART3_SendMessage("BSP_TS_Callback has been called!\n\r");
        if (m_Instance != nullptr) {
            m_Instance->BSP_TS_Callback_Handler(Instance);
        }
    }

private:
    TS_Init_t m_ts{};

    static void Error_Handler();
};

#endif //TOUCHSCREEN_H
