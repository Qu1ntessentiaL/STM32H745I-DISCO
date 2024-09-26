#ifndef MAIN_H
#define MAIN_H

#include "stm32h7xx.h"
#include "Display/Display.h"

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif /* USE_FULL_ASSERT */

#endif /* MAIN_H */
