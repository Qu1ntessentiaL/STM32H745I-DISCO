cmake_minimum_required(VERSION 3.15)

set(STARTUP_LOCATION Device/ST/STM32H7xx/Source/Templates/gcc/startup_stm32h745xx.s)
set(STM32_LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/gcc/linker/stm32h745xx_flash_CM7.ld)
set(STM32_LINKER_OPTION  )

add_library(cmsis STATIC
        ${STARTUP_LOCATION}
        Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.c
)

target_include_directories(cmsis PUBLIC
        Core/Include
        Device/ST/STM32H7xx/Include
        ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
        ${CMAKE_SOURCE_DIR}/Src
)

target_compile_definitions(cmsis PUBLIC
        -DSTM32H745xx
        -DCORE_CM7
        -DUSE_HAL_DRIVER
)

target_link_options(cmsis PUBLIC -T${STM32_LINKER_SCRIPT})
