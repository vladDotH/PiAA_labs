cmake_minimum_required(VERSION 3.20)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(kmp kmp.cpp prefixFunc.cpp prefixFunc.h Logger.cpp Logger.h)
add_executable(cycle cycle.cpp prefixFunc.cpp prefixFunc.h Logger.cpp Logger.h)
