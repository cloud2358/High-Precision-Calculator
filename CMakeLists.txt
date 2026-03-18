cmake_minimum_required(VERSION 3.15) # 清单模式建议 3.15+
project(PiC)
include_directories("C:/git/vcpkg/installed/x64-windows/include")
add_compile_options(-lgmpxx -lgmp)
add_executable(main src/main.cpp)