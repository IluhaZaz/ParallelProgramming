cmake_minimum_required(VERSION 3.11)

project(matrix_multiply CXX)

set(CMAKE_CXX_STANDARD 23)

# Включаем OpenMP
find_package(OpenMP REQUIRED)

# Оптимизации для Release-сборки
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /fp:fast")
    else()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -ffast-math")
    endif()
endif()

# Настройки для MSVC
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_compile_options(/W4 /MP)  # /MP — параллельная компиляция
endif()

# Библиотека
add_library(matrixMultiply SHARED matrixMultiply.cpp)
target_include_directories(matrixMultiply PUBLIC include)
target_link_libraries(matrixMultiply PUBLIC OpenMP::OpenMP_CXX)  # Линкуем OpenMP

# Исполняемый файл
add_executable(main main.cpp)
target_link_libraries(main matrixMultiply)