# src_sources.cmake

# Рекурсивно находим все .cpp и .c файлы в папке Src и её подкаталогах
file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/Src/*.cpp
        ${CMAKE_SOURCE_DIR}/Src/*.c
)

# Исключаем некоторые файлы
list(FILTER SOURCES EXCLUDE REGEX "test.c")

# Добавляем найденные исходники в target_sources
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCES})

# Рекурсивно находим все папки в Src для добавления в target_include_directories
file(GLOB_RECURSE INCLUDES ${CMAKE_SOURCE_DIR}/Src/*)

# Добавляем папки в target_include_directories
foreach(include_dir ${INCLUDES})
    if(IS_DIRECTORY ${include_dir})
        target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${include_dir})
    endif()
endforeach()