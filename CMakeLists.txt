cmake_minimum_required(VERSION 3.15)
project(HighPrecisionMath VERSION 0.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MathLib 
    src/math_constants.cpp
    src/arithmetic_operations.cpp
    src/high_precision_calculator.cpp
)

target_include_directories(MathLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("C:/git/vcpkg/installed/x64-windows/include")

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE MathLib)