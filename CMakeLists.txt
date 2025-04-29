cmake_minimum_required(VERSION 3.11)

project(matrix_multiply LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

find_package(MPI REQUIRED COMPONENTS CXX)

# Настройка компилятора для MSVC
if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    add_compile_options(/W4 /O2 /fp:fast)
endif()

add_library(matrixMultiply SHARED matrixMultiply.cpp)
target_include_directories(matrixMultiply PUBLIC include ${MPI_INCLUDE_PATH})
target_link_libraries(matrixMultiply PRIVATE MPI::MPI_CXX)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE matrixMultiply MPI::MPI_CXX)