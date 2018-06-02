cmake_minimum_required(VERSION 3.9)
project(minesweeper C)

set(CMAKE_C_STANDARD 99)

add_executable(minesweeper "source/main.c" "source/pre_game.c" "headers/pre_game.h" "source/in_game.c" "headers/in_game.h" "headers/board.h" "source/solver.c" "headers/solver.h" "source/solver_mark_method.c" "headers/solver_mark_method.h" "source/solver_chance_method.c" "headers/solver_chance_method.h" "source/solver_helper.c" "headers/solver_helper.h")