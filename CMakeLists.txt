cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_BUILD_TYPE=Debug)

project(sdl-turing-machine)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(sdl-turing-machine main.cpp)

set_target_properties(sdl-turing-machine PROPERTIES LINKER_LANGUAGE CXX)

# I use globs because I am lazy 
file(GLOB HEADERS headers/models/*.hpp headers/views/*.hpp headers/controllers/*.hpp headers/util/*.hpp)
file(GLOB SOURCES src/models/*.cpp src/views/*.cpp  src/views/ui/*.cpp src/controllers/*.cpp src/util/*.cpp)

TARGET_SOURCES(sdl-turing-machine PUBLIC ${HEADERS} PRIVATE ${SOURCES})
TARGET_INCLUDE_DIRECTORIES(sdl-turing-machine PUBLIC .)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)


# include sdl2 headers
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})


