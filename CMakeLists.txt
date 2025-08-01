cmake_minimum_required(VERSION 3.31)
project(bouncy)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED)
add_executable(bouncy src/main.cpp
        src/sdl.cpp
        src/sdl.h
        src/event.cpp
        src/event.h)
target_link_libraries(bouncy PRIVATE SDL3::SDL3)
