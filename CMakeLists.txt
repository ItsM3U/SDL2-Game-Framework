cmake_minimum_required(VERSION 3.28)
project(Main C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES
    Source/Main.c

    Source/Engine.h
    Source/Engine.c

    Source/Input.h
    Source/Input.c
)

add_executable(Main ${SOURCES})
target_link_libraries(Main ${SDL2_LIBRARIES})
