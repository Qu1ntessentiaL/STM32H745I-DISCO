#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include "stm32h7xx.h"
#include "stm32h745i_discovery_bus.h"
#include "stm32h745i_discovery_lcd.h"
#include "stm32h745i_discovery_ts.h"
#include "BSP_Common.h"

#define TS_INSTANCE (TS_INSTANCES_NBR - 1)

class TouchScreen : public BSP_Common {
public:
    static TouchScreen *m_Instance;

    /// C-структура для инициализации сенсорной панели
    TS_Init_t m_ts_init{};
    /// C-структура одиночного касания
#if (USE_TS_MULTI_TOUCH == 0U)
    TS_State_t m_ts_single{};
    inline void GetLastTouchCoordinates(uint16_t &x, uint16_t &y) const;
    inline void UpdateLastTouchCoordinates(uint16_t x, uint16_t y);
#endif
    /// C-структура множественных касаний
    TS_MultiTouch_State_t m_ts_multi{};

    TouchScreen();

    ~TouchScreen();

    void BSP_TS_Callback_Handler(uint32_t Instance);

    void TS_Config(uint32_t Width, uint32_t Height, uint32_t Orientation, uint32_t Accuracy);

    void HandleDoubleTap(uint16_t x, uint16_t y);
};

#endif //TOUCHSCREEN_H
