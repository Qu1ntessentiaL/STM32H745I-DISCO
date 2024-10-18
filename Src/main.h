#ifndef MAIN_H
#define MAIN_H

#include "stm32h7xx.h"
#include "system.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_fs.h"
#include "stm32h745i_discovery_sdram.h"
#include "Display/Display.h"
#include "IIC/IIC.h"
#include "TouchScreen/TouchScreen.h"

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif /* USE_FULL_ASSERT */

#endif /* MAIN_H */
