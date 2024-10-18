#include "BSP_Common.h"

void BSP_Common::CheckState(int32_t state) {
    switch (state) {
        case BSP_ERROR_NONE:
            USART3_SendMessage("BSP_ERROR_NONE\n\r");
            break;
        case BSP_ERROR_NO_INIT:
            USART3_SendMessage("BSP_ERROR_NO_INIT\n\r");
            // Fall through
        case BSP_ERROR_WRONG_PARAM:
            USART3_SendMessage("BSP_ERROR_WRONG_PARAM\n\r");
            // Fall through
        case BSP_ERROR_COMPONENT_FAILURE:
            USART3_SendMessage("BSP_ERROR_COMPONENT_FAILURE\n\r");
            BSP_LED_On(LED_RED);
            break;
        default:
            break;
    }
}

void BSP_Common::Error_Handler() {
    BSP_LED_On(LED_RED);
}
