cmake_minimum_required(VERSION 3.15)
project(shelly C)

set(CMAKE_C_STANDARD 99)

add_executable(shelly main.c input.c input.h utils.c utils.h process.c process.h)