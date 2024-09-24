cmake_minimum_required(VERSION 3.15)

add_definitions(-DSTM32H745xx -DCORE_CM7 -DUSE_HAL_DRIVER)

add_library(cmsis STATIC
        Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.c
)

target_include_directories(cmsis PUBLIC
        Core/Include
        Device/ST/STM32H7xx/Include
        ../STM32H7xx_HAL_Driver/Inc
        ../../../../Src
)
