cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_C_STANDARD 11)

add_executable(lab1 main.c BackTracking.h BackTracking.c)
add_executable(lab1_rect rects.c BackTracking.h BackTracking.c)
