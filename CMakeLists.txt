cmake_minimum_required(VERSION 3.10)
project(minesweeper C)

set(CMAKE_C_STANDARD 99)

add_executable(minesweeper "Source Files/main.c" "Source Files/pre_game.c" "Header Files/pre_game.h" "Source Files/in_game.c" "Header Files/in_game.h" "Header Files/board.h" "Source Files/solver.c" "Header Files/solver.h" "Source Files/solver_mark_method.c" "Header Files/solver_mark_method.h" "Source Files/solver_chance_method.c" "Header Files/solver_chance_method.h" "Source Files/solver_helper.c" "Header Files/solver_helper.h")