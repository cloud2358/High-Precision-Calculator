cmake_minimum_required(VERSION 3.15) # 清单模式建议 3.15+
project(PiCalculator)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories("C:/git/vcpkg/installed/x64-windows/include")
add_executable(main src/main.cpp)