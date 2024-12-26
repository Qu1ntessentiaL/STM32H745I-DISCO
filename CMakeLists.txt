cmake_minimum_required(VERSION 3.15)

set(CMAKE_VERBOSE_MAKEFILE OFF CACHE BOOL "" FORCE)

project(stm32h745i_disco LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# include(toolchains/iar/stm32_toolchain_iar.cmake)

# add_subdirectory(CubeMX/CM7/Core)
add_subdirectory(Drivers/BSP)
add_subdirectory(Drivers/CMSIS)
add_subdirectory(Drivers/STM32H7xx_HAL_Driver)
add_subdirectory(Drivers/lvgl)
add_subdirectory(eez-ui)

add_executable(${PROJECT_NAME})

include(Src/sources.cmake)

# ---------------------------------------------------------------------------------------------------------------------
set(FREERTOS_KERNEL_PATH "Drivers/FreeRTOS-LTS/FreeRTOS/FreeRTOS-Kernel")

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config
        INTERFACE
        "Src"
)

if (DEFINED FREERTOS_SMP_EXAMPLE AND FREERTOS_SMP_EXAMPLE STREQUAL "1")
    message(STATUS "Build FreeRTOS SMP example")
    # Adding the following configurations to build SMP template port
    add_compile_options(-DconfigNUMBER_OF_CORES=2 -DconfigUSE_PASSIVE_IDLE_HOOK=0)
endif ()

set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)

set(FREERTOS_PORT "GCC_ARM_CM7" CACHE STRING "" FORCE)

add_subdirectory(${FREERTOS_KERNEL_PATH} FreeRTOS-Kernel)

# ---------------------------------------------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME} PUBLIC bsp lvgl_demos)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Converting ELF to HEX..."
        COMMAND ${CMAKE_COMMAND} -E rename $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.elf
        COMMAND arm-none-eabi-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.hex
)