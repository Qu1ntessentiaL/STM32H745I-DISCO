#include "Display.h"

Display::Display() {
    if (BSP_LCD_Init(LCD_INSTANCE, LCD_ORIENTATION_LANDSCAPE) != BSP_ERROR_NONE) {
        SendMessage("LCD Init failed!\n\r");
        Error_Handler();
    } else {
        SendMessage("LCD successfully initialized!\n\r");
    }

    if (BSP_LCD_DisplayOn(LCD_INSTANCE) != BSP_ERROR_NONE) {
        SendMessage("LCD don't turn on!\n\r");
        Error_Handler();
    } else {
        SendMessage("LCD turn on!\n\r");
    }

    BSP_LCD_SetActiveLayer(0, 0);
}

Display::~Display() {
    if (BSP_LCD_DeInit(LCD_INSTANCE) != BSP_ERROR_NONE) {
        Error_Handler();
    }
}

void Display::DrawObjects() {
    BSP_LCD_FillRect(LCD_INSTANCE, 0, 0, 480, 272, LCD_COLOR_ARGB8888_BROWN);
    BSP_LCD_DrawVLine(LCD_INSTANCE, 10, 15, 200, LCD_COLOR_ARGB8888_ST_PURPLE);
}