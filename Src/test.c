#include "test.h"

void test_sdram_init() {
    if (BSP_SDRAM_Init(0) != BSP_ERROR_NONE) {
        printf("SDRAM initialization failed!\r\n");
        while (1);
    } else {
        printf("SDRAM initialized successfully.\r\n");
    }
}

void test_sdram_rw() {
    uint32_t * sdram = (uint32_t *) SDRAM_START_ADDRESS;

    // Проверка записи и чтения
    for (uint32_t i = 0; i < 1024; i++) {
        sdram[i] = i; // Записываем значение
    }

    // Проверяем правильность чтения
    for (uint32_t i = 0; i < 1024; i++) {
        if (sdram[i] != i) {
            printf("SDRAM read/write error at address 0x%08X: expected %lu, got %lu\r\n",
                   (uint32_t) &sdram[i], i, sdram[i]);
            while (1); // Останов программы при ошибке
        }
    }

    printf("SDRAM read/write test passed!\r\n");
}

void test_full_sdram_rw() {
    uint32_t * sdram = (uint32_t *) SDRAM_START_ADDRESS;
    uint32_t sdram_size_words = SDRAM_TEST_SIZE / sizeof(uint32_t);

    printf("Writing to SDRAM...\r\n");
    for (uint32_t i = 0; i < sdram_size_words; i++) {
        sdram[i] = i; // Записываем индекс как значение
    }

    printf("Reading and verifying SDRAM...\r\n");
    for (uint32_t i = 0; i < sdram_size_words; i++) {
        if (sdram[i] != i) {
            printf("Error at address 0x%08X: expected %lu, got %lu\r\n",
                   (uint32_t) &sdram[i], i, sdram[i]);
            while (1); // Останавливаем тест при ошибке
        }
    }

    printf("Full SDRAM test passed!\r\n");
}

void test_sdram_with_patterns() {
    uint32_t * sdram = (uint32_t *) SDRAM_START_ADDRESS;
    uint32_t sdram_size_words = SDRAM_TEST_SIZE / sizeof(uint32_t);
    uint32_t patterns[] = {0xAAAAAAAA, 0x55555555, 0xFFFFFFFF, 0x00000000};

    for (uint32_t p = 0; p < sizeof(patterns) / sizeof(patterns[0]); p++) {
        uint32_t pattern = patterns[p];
        printf("Testing pattern 0x%08X...\r\n", pattern);

        // Записываем шаблон
        for (uint32_t i = 0; i < sdram_size_words; i++) {
            sdram[i] = pattern;
        }

        // Проверяем шаблон
        for (uint32_t i = 0; i < sdram_size_words; i++) {
            if (sdram[i] != pattern) {
                printf("Error with pattern 0x%08X at address 0x%08X: got 0x%08X\r\n",
                       pattern, (uint32_t) &sdram[i], sdram[i]);
                while (1); // Останавливаем тест при ошибке
            }
        }
    }

    printf("All patterns tested successfully!\r\n");
}

void test_lvgl_buffer_addresses() {
    if ((LVGL_BUFFER_ADDR_AT_SDRAM < SDRAM_START_ADDRESS) ||
        (LVGL_BUFFER_ADDR_AT_SDRAM >= (SDRAM_START_ADDRESS + SDRAM_SIZE))) {
        printf("LVGL_BUFFER_ADDR_AT_SDRAM is out of SDRAM bounds!\r\n");
        while (1);
    }

    if ((LVGL_BUFFER_2_ADDR_AT_SDRAM < SDRAM_START_ADDRESS) ||
        (LVGL_BUFFER_2_ADDR_AT_SDRAM >= (SDRAM_START_ADDRESS + SDRAM_SIZE))) {
        printf("LVGL_BUFFER_2_ADDR_AT_SDRAM is out of SDRAM bounds!\r\n");
        while (1);
    }

    printf("LVGL buffer addresses are valid.\r\n");
}

void test_buffer_alignment() {
    if (LVGL_BUFFER_ADDR_AT_SDRAM % 4 != 0) {
        printf("LVGL_BUFFER_ADDR_AT_SDRAM is not aligned to 4 bytes!\r\n");
        while (1);
    }

    if (LVGL_BUFFER_2_ADDR_AT_SDRAM % 4 != 0) {
        printf("LVGL_BUFFER_2_ADDR_AT_SDRAM is not aligned to 4 bytes!\r\n");
        while (1);
    }

    printf("LVGL buffer addresses are properly aligned.\r\n");
}

void test_sdram() {
    printf("Testing SDRAM initialization...\r\n");
    test_sdram_init();

    printf("Testing SDRAM read/write...\r\n");
    test_sdram_rw();

    printf("Testing LVGL buffer addresses...\r\n");
    test_lvgl_buffer_addresses();

    printf("Testing LVGL buffer alignment...\r\n");
    test_buffer_alignment();

    printf("All SDRAM tests passed successfully!\r\n");
}

void test_full_sdram() {
    printf("Testing SDRAM initialization...\n");
    test_sdram_init(); // Предполагается, что инициализация SDRAM уже есть в проекте

    printf("Testing full SDRAM read/write...\n");
    test_full_sdram_rw();

    printf("Testing SDRAM with patterns...\n");
    test_sdram_with_patterns();

    printf("All SDRAM tests passed successfully!\n");
}

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