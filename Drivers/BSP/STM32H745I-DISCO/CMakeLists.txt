cmake_minimum_required(VERSION 3.15)

add_definitions(-DSTM32H745xx -DCORE_CM7 -DUSE_HAL_DRIVER)

# Укажите пути к папкам
set(COMPONENTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Components")
set(ADAFRUIT_SHIELD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Adafruit_Shield")

# Рекурсивно найдем все .c и .h файлы в папках Components и Adafruit_Shield
file(GLOB_RECURSE COMPONENTS_SOURCES "${COMPONENTS_DIR}/*.c")
file(GLOB_RECURSE COMPONENTS_HEADERS "${COMPONENTS_DIR}/*.h")
file(GLOB_RECURSE ADAFRUIT_SOURCES "${ADAFRUIT_SHIELD_DIR}/*.c")
file(GLOB_RECURSE ADAFRUIT_HEADERS "${ADAFRUIT_SHIELD_DIR}/*.h")

# Добавьте все найденные файлы в переменные для исходников и заголовков
set(SOURCES ${COMPONENTS_SOURCES} ${ADAFRUIT_SOURCES})
set(HEADERS ${COMPONENTS_HEADERS} ${ADAFRUIT_HEADERS})

#Найти все C-файлы в директории
file(GLOB_RECURSE ALL_C_SOURCES "*.c")

add_library(bsp STATIC
        ${ALL_C_SOURCES}
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(bsp PUBLIC
        "*.h"
        ${COMPONENTS_DIR}
        ${ADAFRUIT_SHIELD_DIR}
)

target_link_libraries(bsp PUBLIC stm32h7xx_hal_driver)