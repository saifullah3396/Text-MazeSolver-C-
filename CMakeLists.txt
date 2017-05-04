cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(MazeSolver)
file(GLOB Source
    "Src/*.h"
    "Src/*.cpp"
)
add_executable(MazeSolver ${Source})

