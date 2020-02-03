cmake_minimum_required(VERSION 3.15)
project(shelly C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall") # READLINE

add_executable(shelly main.c input.c input.h utils.c utils.h process.c process.h parse.c parse.h)

target_link_libraries(shelly readline) # READLINE