cmake_minimum_required(VERSION 3.15)

# Найти все C-файлы в директории
file(GLOB_RECURSE ALL_C_SOURCES
        Src/main.c
        Src/usart.c
        Src/syscalls.c
        Src/sysmem.c
)

# Исключить некоторые файлы
list(REMOVE_ITEM ALL_C_SOURCES
        # ${CMAKE_CURRENT_SOURCE_DIR}/Src/stm32h7xx_it.c
        # ${CMAKE_CURRENT_SOURCE_DIR}/Src/sysmem.c
)

add_library(cubemx STATIC
        ${ALL_C_SOURCES}
)

target_include_directories(cubemx PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Inc/
)

target_link_libraries(cubemx PUBLIC bsp)
