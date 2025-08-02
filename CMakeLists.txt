cmake_minimum_required(VERSION 3.31)
project(bouncy)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED)
add_executable(bouncy src/main.cpp
        src/sdl.cpp
        src/sdl.h
        src/event.cpp
        src/event.h
        src/game.cpp
        src/game.cpp
        src/game.h
        src/ball.cpp
        src/ball.h
        src/vec.cpp
        src/vec.h
        src/wall.cpp
        src/wall.h
        src/rand.cpp
        src/rand.h)
target_link_libraries(bouncy PRIVATE SDL3::SDL3)
