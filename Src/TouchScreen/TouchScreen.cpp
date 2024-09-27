#include "TouchScreen.h"

TouchScreen::TouchScreen() {
    TS_Init_t ts_init;
    ts_init.Width = 480;
    ts_init.Height = 272;
    ts_init.Orientation = TS_SWAP_NONE;
    ts_init.Accuracy = 5;
    if (BSP_TS_Init(TS_INSTANCES_NBR, &ts_init) != BSP_ERROR_NONE) {
        Error_Handler();
    }
    BSP_TS_EnableIT(TS_INSTANCES_NBR);
}

TouchScreen::~TouchScreen() {
    if (BSP_TS_DeInit(TS_INSTANCES_NBR) != BSP_ERROR_NONE) {
        Error_Handler();
    }
}

void TouchScreen::Error_Handler() {

}

void BSP_TS_Callback(uint32_t Instance) {
    TS_State_t TS_State;

    if (BSP_TS_GetState(Instance, &TS_State) == BSP_ERROR_NONE) {
        if (TS_State.TouchDetected) {
            uint16_t x = TS_State.TouchX;
            uint16_t y = TS_State.TouchY;
        }
        if (TS_State.TouchX <= 240){
            BSP_LED_On(LED_GREEN);
        } else {
            BSP_LED_Off(LED_GREEN);
        }
    }
}

