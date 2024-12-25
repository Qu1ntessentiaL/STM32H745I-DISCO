#ifndef TEST_H
#define TEST_H

#include "stm32h7xx.h"
#include "stm32h745i_discovery_sdram.h"
#include <stdio.h>

#define SDRAM_START_ADDRESS  0xD0000000
#define SDRAM_SIZE           (16 * 1024 * 1024)
#define SDRAM_TEST_SIZE      (1 * 1024 * 1024)

#define LVGL_BUFFER_ADDR_AT_SDRAM   (0xD007F810)
#define LVGL_BUFFER_2_ADDR_AT_SDRAM (0xD00FF020)

void test_sdram_init(void);

void test_sdram_rw(void);

void test_full_sdram_rw(void);

void test_sdram_with_patterns(void);

void test_lvgl_buffer_addresses(void);

void test_buffer_alignment(void);

void test_sdram(void);

void test_full_sdram(void);

void DrawTestPattern(void);

void SDRAM_Test(void);

#endif //TEST_H
