cmake_minimum_required(VERSION 3.15)

add_library(bsp STATIC
        Components/ft5336/ft5336.c
        Components/ft5336/ft5336_reg.c
        Components/mt48lc4m32b2/mt48lc4m32b2.c
        STM32H745I-DISCO/stm32h745i_discovery.c
        STM32H745I-DISCO/stm32h745i_discovery_bus.c
        STM32H745I-DISCO/stm32h745i_discovery_lcd.c
        STM32H745I-DISCO/stm32h745i_discovery_ts.c
        STM32H745I-DISCO/stm32h745i_discovery_sdram.c
)

target_include_directories(bsp PUBLIC
        Components/Common
        Components/rk043fn48h
        Components/ft5336
        Components/mt48lc4m32b2
        STM32H745I-DISCO
)

target_link_libraries(bsp PUBLIC stm32h7xx_hal_driver)