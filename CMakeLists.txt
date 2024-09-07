cmake_minimum_required(VERSION 3.25.1)

project(sdl-turing-machine)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(sdl-turing-machine main.cpp turing_machine.hpp turing_machine.cpp)

target_link_libraries(sdl-turing-machine ${SDL2_LIBRARIES})
