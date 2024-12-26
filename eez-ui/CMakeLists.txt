cmake_minimum_required(VERSION 3.15)

# Найти все C-файлы в директории
file(GLOB_RECURSE ALL_C_SOURCES
        src/*.c
)

# Исключить некоторые файлы
list(REMOVE_ITEM ALL_C_SOURCES
        # ${CMAKE_CURRENT_SOURCE_DIR}/src/ui.c
)

add_library(lv_project STATIC
        ${ALL_C_SOURCES}
)

target_include_directories(lv_project PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(lv_project PUBLIC bsp lvgl)
