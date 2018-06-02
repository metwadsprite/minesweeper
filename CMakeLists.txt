cmake_minimum_required(VERSION 3.9)
project(minesweeper C)

set(CMAKE_C_STANDARD 99)

add_executable(minesweeper "Code/source/main.c" "Code/source/pre_game.c" "Code/headers/pre_game.h" "Code/source/in_game.c" "Code/headers/in_game.h" "Code/headers/board.h" "Code/source/solver.c" "Code/headers/solver.h" "Code/source/solver_mark_method.c" "Code/headers/solver_mark_method.h" "Code/source/solver_chance_method.c" "Code/headers/solver_chance_method.h" "Code/source/solver_helper.c" "Code/headers/solver_helper.h")