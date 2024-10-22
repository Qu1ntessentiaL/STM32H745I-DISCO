#include "BSP_Common.h"

void BSP_Common::CheckState(int32_t state) {
    switch (state) {
        case BSP_ERROR_NONE:
            SendMessage("BSP_ERROR_NONE\n\r");
            break;
        case BSP_ERROR_NO_INIT:
            SendMessage("BSP_ERROR_NO_INIT\n\r");
            // Fall through
        case BSP_ERROR_WRONG_PARAM:
            SendMessage("BSP_ERROR_WRONG_PARAM\n\r");
            // Fall through
        case BSP_ERROR_COMPONENT_FAILURE:
            SendMessage("BSP_ERROR_COMPONENT_FAILURE\n\r");
            BSP_LED_On(LED_RED);
            break;
        default:
            break;
    }
}

void BSP_Common::Error_Handler() {
    BSP_LED_On(LED_RED);
}

BSP_Common::BSP_Common() {
    MX_DMA_Init();
    MX_USART3_UART_Init();
    SendMessage("______________________________Reset MCU!______________________________\n\r");
}

void BSP_Common::SendMessage(const char *str) {
    if (str == nullptr) {
        return;
    }
    uint16_t length = strlen(str);
    HAL_UART_Transmit_DMA(&huart3, (uint8_t *) str, length);
}