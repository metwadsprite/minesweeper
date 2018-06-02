/**
 * @file solver_mark_method.c
 * @brief C library containing the functions used by the marking method.
 * @author Vasilescu Vlad
 */

#include <stdio.h>
#include "../headers/board.h"
#include "../headers/in_game.h"
#include "../headers/solver_helper.h"

int adj_marked_squares(struct minesweeper_board *board, int line, int column, struct solver_helper *solver) {
    /**
     * @fn int adj_marked_squares(struct minesweeper_board *board, int line, int column, struct solver_helper *solver)
     * @brief Function that returns the number of marked squares adjacent
     * to the given square.
     * @param *board The board itself.
     * @param line First coordinate for the square.
     * @param column Second coordinate for the square.
     * @param *solver Contains information about all the marked squares.
     */

    int aux = 0;

    if (line > 0) {
        if (column > 0) {
            if (solver->marked[line - 1][column - 1]) {
                aux++;
            }
        }
        if (solver->marked[line - 1][column]) {
            aux++;
        }
        if (column < board->columns - 1) {
            if (solver->marked[line - 1][column + 1]) {
                aux++;
            }
        }
    }

    if (column > 0) {
        if (solver->marked[line][column - 1]) {
            aux++;
        }
    }
    if (column < board->columns - 1) {
        if (solver->marked[line][column + 1]) {
            aux++;
        }
    }

    if (line < board->lines - 1) {
        if (column > 0) {
            if (solver->marked[line + 1][column - 1]) {
                aux++;
            }
        }
        if (solver->marked[line + 1][column]) {
            aux++;
        }
        if (column < board->columns - 1) {
            if (solver->marked[line + 1][column + 1]) {
                aux++;
            }
        }
    }

    return aux;
}

void mark_squares(struct minesweeper_board *board, struct solver_helper *solver) {
    /**
     * @fn void mark_squares(struct minesweeper_board *board, struct solver_helper *solver)
     * @brief Function that marks the squares.
     * @param *board The board itself.
     * @param *solver Contains information about all the marked squares.
     *
     * A "marked square" represents a square that know the be a bomb for sure
     * (when number of hidden squares around a cell is equal to the number on it).
     */

    int iterator1;
    int iterator2;

    for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
        for (iterator2 = 0; iterator2 < board->columns; iterator2++) {
            if (board->visibility[iterator1][iterator2] == 0) {
                continue;
            }
            if (board->base[iterator1][iterator2] == 0) {
                continue;
            }
            if (adj_hidden_squares(board, iterator1, iterator2) != board->base[iterator1][iterator2]) {
                continue;
            }

            if (iterator1 > 0) {
                if (iterator2 > 0) {
                    if (board->visibility[iterator1 - 1][iterator2 - 1] == 0 &&
                        solver->marked[iterator1 - 1][iterator2 - 1] == 0) {

                        solver->marked[iterator1 - 1][iterator2 - 1] = 1;
                        solver->marked_squares++;
                    }
                }
                if (board->visibility[iterator1 - 1][iterator2] == 0 &&
                    solver->marked[iterator1 - 1][iterator2] == 0) {

                    solver->marked[iterator1 - 1][iterator2] = 1;
                    solver->marked_squares++;
                }
                if (iterator2 < board->columns - 1 && solver->marked[iterator1][iterator2] == 0) {
                    if (board->visibility[iterator1 - 1][iterator2 + 1] == 0 &&
                        solver->marked[iterator1 - 1][iterator2 + 1] == 0) {

                        solver->marked[iterator1 - 1][iterator2 + 1] = 1;
                        solver->marked_squares++;
                    }
                }
            }

            if (iterator2 > 0) {
                if (board->visibility[iterator1][iterator2 - 1] == 0 &&
                    solver->marked[iterator1][iterator2 - 1] == 0) {

                    solver->marked[iterator1][iterator2 - 1] = 1;
                    solver->marked_squares++;
                }
            }
            if (iterator2 < board->columns - 1) {
                if (board->visibility[iterator1][iterator2 + 1] == 0 &&
                    solver->marked[iterator1][iterator2 + 1] == 0) {

                    solver->marked[iterator1][iterator2 + 1] = 1;
                    solver->marked_squares++;
                }
            }

            if (iterator1 < board->lines - 1) {
                if (iterator2 > 0) {
                    if (board->visibility[iterator1 + 1][iterator2 - 1] == 0 &&
                        solver->marked[iterator1 + 1][iterator2 - 1] == 0) {

                        solver->marked[iterator1 + 1][iterator2 - 1] = 1;
                        solver->marked_squares++;
                    }
                }
                if (board->visibility[iterator1 + 1][iterator2] == 0 &&
                    solver->marked[iterator1 + 1][iterator2] == 0) {

                    solver->marked[iterator1 + 1][iterator2] = 1;
                    solver->marked_squares++;
                }
                if (iterator2 < board->columns - 1) {
                    if (board->visibility[iterator1 + 1][iterator2 + 1] == 0 &&
                        solver->marked[iterator1 + 1][iterator2 + 1] == 0) {

                        solver->marked[iterator1 + 1][iterator2 + 1] = 1;
                        solver->marked_squares++;
                    }
                }
            }
        }
    }
}

void open_unmarked(struct minesweeper_board *board, struct solver_helper *solver) {
    /**
     * @fn void open_unmarked(struct minesweeper_board *board, struct solver_helper *solver)
     * @brief Function that opens unmarked squares around "satisfied" cells.
     * @param *board The board itself.
     * @param *solver Contains information about all the marked squares.
     *
     * A cell is "satisfied" when the number of marked cells around it is equal
     * to the number on the cell. That means every other square that isn't marked
     * is not a bomb.
     */

    int iterator1;
    int iterator2;

    for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
        for (iterator2 = 0; iterator2 < board->columns; iterator2++) {
            if (board->visibility[iterator1][iterator2] == 0) {
                continue;
            }
            if (board->base[iterator1][iterator2] == 0) {
                continue;
            }
            if (adj_marked_squares(board, iterator1, iterator2, solver) == 0) {
                continue;
            }
            if (adj_marked_squares(board, iterator1, iterator2, solver) ==
                adj_hidden_squares(board, iterator1, iterator2)) {

                continue;
            }
            if (adj_marked_squares(board, iterator1, iterator2, solver) !=
                board->base[iterator1][iterator2]) {
                continue;
            }

            if (iterator1 > 0) {
                if (iterator2 > 0) {
                    if (board->visibility[iterator1 - 1][iterator2 - 1] == 0 &&
                        solver->marked[iterator1 - 1][iterator2 - 1] == 0) {

                        printf("Opened square at (%d, %d)\n", iterator1 - 1, iterator2 - 1);
                        reveal(board, iterator1 - 1, iterator2 - 1);
                    }
                }
                if (board->visibility[iterator1 - 1][iterator2] == 0 &&
                    solver->marked[iterator1 - 1][iterator2] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1 - 1, iterator2);
                    reveal(board, iterator1 - 1, iterator2);
                }
                if (iterator2 < board->columns - 1) {
                    if (board->visibility[iterator1 - 1][iterator2 + 1] == 0 &&
                        solver->marked[iterator1 - 1][iterator2 + 1] == 0) {

                        printf("Opened square at (%d, %d)\n", iterator1 - 1, iterator2 + 1);
                        reveal(board, iterator1 - 1, iterator2 + 1);
                    }
                }
            }

            if (iterator2 > 0) {
                if (board->visibility[iterator1][iterator2 - 1] == 0 &&
                    solver->marked[iterator1][iterator2 - 1] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1, iterator2 - 1);
                    reveal(board, iterator1, iterator2 - 1);
                }
            }
            if (iterator2 < board->columns - 1) {
                if (board->visibility[iterator1][iterator2 + 1] == 0 &&
                    solver->marked[iterator1][iterator2 + 1] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1, iterator2 + 1);
                    reveal(board, iterator1, iterator2 + 1);
                }
            }

            if (iterator1 < board->lines - 1) {
                if (board->columns > 0) {
                    if (board->visibility[iterator1 + 1][iterator2 - 1] == 0 &&
                        solver->marked[iterator1 + 1][iterator2 - 1] == 0) {

                        printf("Opened square at (%d, %d)\n", iterator1 + 1, iterator2 - 1);
                        reveal(board, iterator1 + 1, iterator2 - 1);
                    }
                }
                if (board->visibility[iterator1 + 1][iterator2] == 0 &&
                    solver->marked[iterator1 + 1][iterator2] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1 + 1, iterator2);
                    reveal(board, iterator1 + 1, iterator2);
                }
                if (iterator2 < board->columns - 1) {
                    if (board->visibility[iterator1 + 1][iterator2 + 1] == 0 &&
                        solver->marked[iterator1 + 1][iterator2 + 1] == 0) {

                        printf("Opened square at (%d, %d)\n", iterator1 + 1, iterator2 + 1);
                        reveal(board, iterator1 + 1, iterator2 + 1);
                    }
                }
            }
        }
    }
}