#include "test.h"

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
