cmake_minimum_required(VERSION 3.10)
project(minesweeper C)

set(CMAKE_C_STANDARD 99)

add_executable(minesweeper main.c pre_game.c headers/pre_game.h in_game.c headers/in_game.h headers/board.h solver.c headers/solver.h)