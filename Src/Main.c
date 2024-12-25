#include "stdio.h"

#include "stm32h7xx.h"

#include "usart.h"

#include "stm32h745i_discovery.h"
#include "stm32h745i_discovery_lcd.h"
#include "stm32h745i_discovery_ts.h"
#include "stm32h745i_discovery_qspi.h"
#include "stm32h745i_discovery_sdram.h"

//#include "lvgl.h"
//#include "lvgl_port_lcd.h"
//#include "lvgl_port_touchpad.h"
//#include "../Drivers/lvgl/demos/lv_demos.h"
//#include "../Drivers/lvgl/demos/widgets/lv_demo_widgets.h"

//#include "../eez-ui/src/ui/ui.h"

extern void SystemClock_Config(void);


void SDRAM_Test(void);

int __write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart3, (uint8_t *) ptr, len, HAL_MAX_DELAY);
    return len;
}

/*
int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        ITM_SendChar(ptr[i]);
    }
    return len;
}
*/

#define LCD_WIDTH  480    // Ширина экрана
#define LCD_HEIGHT 272    // Высота экрана

void DrawTestPattern(void) {
    uint32_t * framebuffer = (uint32_t *) LCD_LAYER_0_ADDRESS;
    uint32_t color;
    int x, y;

    // Заполнение экрана черным цветом для начала
    for (y = 0; y < LCD_HEIGHT; y++) {
        for (x = 0; x < LCD_WIDTH; x++) {
            framebuffer[y * LCD_WIDTH + x] = 0xFF000000; // Черный цвет (A = 255, R = 0, G = 0, B = 0)
        }
    }

    HAL_Delay(1000);

    // Рисуем вертикальные полосы разного цвета
    for (x = 0; x < LCD_WIDTH; x++) {
        if (x < LCD_WIDTH / 3) {
            color = 0xFFFF0000; // Красный
        } else if (x < 2 * LCD_WIDTH / 3) {
            color = 0xFF00FF00; // Зеленый
        } else {
            color = 0xFF0000FF; // Синий
        }

        // Заполнение полосы
        for (y = 0; y < LCD_HEIGHT; y++) {
            framebuffer[y * LCD_WIDTH + x] = color;
        }
    }

    HAL_Delay(1000);

    // Рисуем горизонтальные полосы
    for (y = 0; y < LCD_HEIGHT; y++) {
        if (y < LCD_HEIGHT / 3) {
            color = 0xFFFFFF00; // Желтый (R + G)
        } else if (y < 2 * LCD_HEIGHT / 3) {
            color = 0xFF00FFFF; // Голубой (G + B)
        } else {
            color = 0xFFFF00FF; // Фиолетовый (R + B)
        }

        // Заполнение полосы
        for (x = 0; x < LCD_WIDTH; x++) {
            framebuffer[y * LCD_WIDTH + x] = color;
        }
    }
}

int main() {
    //MPU_Config();
    SCB_EnableICache();
    SCB_EnableDCache();

    HAL_Init();
    SystemClock_Config();

    MX_USART3_UART_Init();
    printf("Started!\n\r");

    BSP_QSPI_Init_t qspi_init;
    qspi_init.InterfaceMode = MT25TL01G_QPI_MODE;
    qspi_init.TransferRate = MT25TL01G_DTR_TRANSFER;
    qspi_init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;
    BSP_QSPI_Init(0, &qspi_init);
    BSP_QSPI_EnableMemoryMappedMode(0);

    BSP_LED_Init(LED_RED);
    BSP_LED_Init(LED_GREEN);

    //touchpad_init();
    //lcd_init();

    //lv_init();
    //lv_demo_widgets();
    while (1) {
        //lv_task_handler();
        BSP_LED_Toggle(LED_RED);
        HAL_Delay(5);
    }
}

void SDRAM_Test(void) {
    uint32_t * test_addr = (uint32_t *) 0xD0000000;  // Адрес начала SDRAM
    uint32_t test_value = 0xDEADBEEF;

    // Записать тестовое значение в SDRAM
    *test_addr = test_value;

    // Проверить, что оно сохранено
    if (*test_addr != test_value) {
        printf("SDRAM test failed!\n");
    } else {
        printf("SDRAM test passed!\n");
    }
}
