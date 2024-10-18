#include "TouchScreen.h"
#include <cstring>
#include <cstdio>

extern UART_HandleTypeDef huart3;

/// Инициализация статического указателя
TouchScreen *TouchScreen::m_Instance = nullptr;

TouchScreen::TouchScreen() {
    /// Инициализация статического указателя на текущий объект
    m_Instance = this;

    m_ts_init.Width = TS_MAX_WIDTH;
    m_ts_init.Height = TS_MAX_HEIGHT;
    m_ts_init.Orientation = TS_SWAP_XY;
    m_ts_init.Accuracy = 15;
    if (BSP_TS_Init(TS_INSTANCE, &m_ts_init) != BSP_ERROR_NONE) {
        USART3_SendMessage("TS Init failed!\n\r");
        Error_Handler();
    } else {
        USART3_SendMessage("TS successfully initialized!\n\r");
    }

    /// BSP_TS_EnableIT(...) не включает тактирование PG2!
    __HAL_RCC_GPIOG_CLK_ENABLE();

    if (BSP_TS_EnableIT(TS_INSTANCE) != BSP_ERROR_NONE) {
        USART3_SendMessage("TS EnableIT failed!\n\r");
        Error_Handler();
    } else {
        USART3_SendMessage("TS Interrupts enabled!\n\r");
    }
}

TouchScreen::~TouchScreen() {
    if (BSP_TS_DeInit(TS_INSTANCE) != BSP_ERROR_NONE) {
        Error_Handler();
    }
}

#if (USE_TS_MULTI_TOUCH == 0U)
/// Реализация метода для обработки касаний
void TouchScreen::BSP_TS_Callback_Handler(uint32_t Instance) {
    if (BSP_TS_GetState(Instance, &m_ts_single) == BSP_ERROR_NONE) {
        if (m_ts_single.TouchDetected) {
            uint16_t x = m_ts_single.TouchX;
            char buffer[20];
            int length = sprintf(buffer, "x: %hu\r\n", x);
            HAL_UART_Transmit(&huart3, (uint8_t *) buffer, length, 1000);
            uint16_t y = m_ts_single.TouchY;
            length = sprintf(buffer, "y: %hu\r\n", y);
            HAL_UART_Transmit(&huart3, (uint8_t *) buffer, length, 1000);

            if (x <= 240) {
                BSP_LED_On(LED_GREEN);
            } else {
                BSP_LED_Off(LED_GREEN);
            }
        } else {
            USART3_SendMessage("No touch detected\n\r");
        }
    } else {
        USART3_SendMessage("Error getting touch state!\n\r");
    }
}
#endif

/// Реализация метода для обработки касаний
void TouchScreen::BSP_TS_Callback_Handler(uint32_t Instance) {
    CheckState(BSP_TS_Get_MultiTouchState(Instance, &m_ts_multi));
}

/**
 * @brief Обработчик внешнего прерывания по линии EXTI2
 * @note Порядок обработки касания сенсора:
 * Событие -> EXTI2_IRQHandler -> BSP_TS_IRQHandler(...) -> HAL_EXTI_IRQHandler(...) ->
 * -> BSP_TS_Callback(...) -> BSP_TS_Callback_Handler(...)
 */

extern "C" void EXTI2_IRQHandler(void) {
    USART3_SendMessage("EXTI2_IRQHandler has been called!\n\r");
    BSP_TS_IRQHandler(TS_INSTANCE);
}

extern "C" void BSP_TS_Callback(uint32_t Instance) {
    TouchScreen::m_Instance->BSP_TS_Callback_Handler(Instance);
}

/**
 * @brief Метод для изменения параметров инициализации сенсора
 * @param Width Ширина сенсорной панели в пикселях
 * @param Height Высота сенсорной панели в пикселях
 * @param Orientation Ориентация сенсорнй панели
 * @param Accuracy Точность определения касаний к сенсору
 */
void TouchScreen::TS_Config(uint32_t Width = TS_MAX_WIDTH,
                            uint32_t Height = TS_MAX_HEIGHT,
                            uint32_t Orientation = TS_SWAP_XY,
                            uint32_t Accuracy = 5) {

    m_ts_init.Width = Width;
    m_ts_init.Height = Height;
    m_ts_init.Orientation = Orientation;
    m_ts_init.Accuracy = Accuracy;

    CheckState(BSP_TS_Init(TS_INSTANCE, &m_ts_init));
}

#if (USE_TS_MULTI_TOUCH == 0U)
inline void TouchScreen::GetLastTouchCoordinates(uint16_t &x, uint16_t &y) const {
    x = m_ts_single.TouchX;
    y = m_ts_single.TouchY;
}

inline void TouchScreen::UpdateLastTouchCoordinates(uint16_t x, uint16_t y) {
    m_ts_single.TouchX = x;
    m_ts_single.TouchY = y;
}
#endif

void TouchScreen::HandleDoubleTap(uint16_t x, uint16_t y) {}
