cmake_minimum_required(VERSION 3.15)

add_definitions(-DSTM32H745xx -DCORE_CM7 -DUSE_HAL_DRIVER)

#Найти все C-файлы в директории
file(GLOB_RECURSE ALL_C_SOURCES "Src/*.c")

# Исключить некоторые файлы
list(REMOVE_ITEM ALL_C_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/syscalls.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Src/sysmem.c
)

add_library(cubemx STATIC
        ${ALL_C_SOURCES}
)

target_include_directories(cubemx PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Inc/
)

target_link_libraries(cubemx PUBLIC stm32h7xx_hal_driver)
