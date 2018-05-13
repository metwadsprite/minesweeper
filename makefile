CC = gcc
FILES = "Source Files/main.c" "Source Files/pre_game.c" "Header Files/pre_game.h" "Source Files/in_game.c" "Header Files/in_game.h" "Header Files/board.h" "Source Files/solver.c" "Header Files/solver.h" "Source Files/solver_mark_method.c" "Header Files/solver_mark_method.h" "Source Files/solver_chance_method.c" "Header Files/solver_chance_method.h" "Source Files/solver_helper.c" "Header Files/solver_helper.h"
FLAGS = -o
TARGET = minesweeper

all: build

build:
	$(CC) $(FILES) $(FLAGS) $(TARGET)
	
clean:
	rm $(TARGET)
