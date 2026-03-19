cmake_minimum_required(VERSION 3.15)
project(HighPrecisionMath VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MathLib src/math_constants.cpp)
include_directories("./include")
include_directories("C:/git/vcpkg/installed/x64-windows/include")

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE MathLib)