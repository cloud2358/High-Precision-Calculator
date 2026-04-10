cmake_minimum_required(VERSION 3.15)
project(HighPrecisionMath VERSION 0.168)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(MathLib 
    src/calcalg/ArithmeticOperations.cpp
    src/calcalg/HighPrecisionCalculator.cpp
    src/calcalg/InputTokenizer.cpp
    src/calcalg/MathUtils.cpp
)

target_include_directories(MathLib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/calcalg")

include_directories("C:/git/vcpkg/installed/x64-windows/include")

add_executable(test tests/test.cpp)

target_link_libraries(test PRIVATE MathLib)