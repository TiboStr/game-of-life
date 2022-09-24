cmake_minimum_required(VERSION 3.22)
project(game_of_life C)

set(CMAKE_C_STANDARD 11)

add_executable(game_of_life
        src/main.c src/lib/grid.h src/lib/grid.c src/lib/util/util.c src/lib/util/util.h)
