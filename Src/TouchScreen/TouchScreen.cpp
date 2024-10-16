#include "TouchScreen.h"

extern UART_HandleTypeDef huart3;

/// Инициализация статического указателя
TouchScreen *TouchScreen::m_Instance = nullptr;

TouchScreen::TouchScreen() {
    /// Инициализация статического указателя на текущий объект
    m_Instance = this;

    m_ts.Width = TS_MAX_WIDTH;
    m_ts.Height = TS_MAX_HEIGHT;
    m_ts.Orientation = TS_SWAP_NONE;
    m_ts.Accuracy = 5;
    if (BSP_TS_Init(TS_INSTANCE, &m_ts) != BSP_ERROR_NONE) {
        USART3_SendMessage("TS Init failed!\n\r");
        Error_Handler();
    } else {
        USART3_SendMessage("TS successfully initialized!\n\r");
    }
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

void TouchScreen::Error_Handler() {
    USART3_SendMessage("Error_Handler() has been called!\n\r");
}

/// Реализация метода для обработки касаний
void TouchScreen::BSP_TS_Callback_Handler(uint32_t Instance) {
    TS_State_t TS_State;

    if (BSP_TS_GetState(Instance, &TS_State) == BSP_ERROR_NONE) {
        if (TS_State.TouchDetected) {
            uint16_t x = TS_State.TouchX;
            uint16_t y = TS_State.TouchY;

            USART3_SendMessage("Touch detected!\n\r");

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

/**
 * @brief Обработчик внешнего прерывания по линии EXTI2
 * @note Порядок обработки касания сенсора:
 * Событие -> EXTI2_IRQHandler ->
 */

extern "C" void EXTI2_IRQHandler(void) {
    HAL_UART_Transmit(&huart3, (uint8_t *) "EXTI2_IRQHandler has been called!\n\r",
                      sizeof("EXTI2_IRQHandler has been called!\n\r"), 1000);
    BSP_TS_IRQHandler(TS_INSTANCE);
}
