cmake_minimum_required(VERSION 3.15) # 清单模式建议 3.15+
project(PiCalculator)
include_directories(main PUBLIC "C:/git/vcpkg/installed/x64-windows/include")
add_executable(main src/main.cpp)