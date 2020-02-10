cmake_minimum_required(VERSION 3.15)
project(shelly)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall") # NEEDED FOR READLINE

##
### Test definitions ###
##

# CMakeLists.txt.in downloads gtest dependency from github.com
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()

add_subdirectory(test)

##
### Source definitions ###
##

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/src/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")

# Build all source files
add_executable(${PROJECT_NAME} ${sources})

# Link GNU-Readline
target_link_libraries(${PROJECT_NAME} readline)