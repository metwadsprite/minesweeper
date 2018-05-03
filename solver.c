/**
 * @file solver.c
 * @brief C library containing the functions used to solve the game.
 * @author Vasilescu Vlad
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/board.h"
#include "headers/in_game.h"

struct solver_helper {
    int marked_squares;

    int **chance;
    int **marked;
};

int adj_hidden_squares(struct minesweeper_board *board, int line, int column) {
    int aux = 0;

    if (line > 0) {
        if (column > 0) {
            if (board->visibility[line - 1][column - 1] == 0) {
                aux++;
            }
        }
        if (board->visibility[line - 1][column] == 0) {
            aux++;
        }
        if (column < board->columns - 1) {
            if (board->visibility[line - 1][column + 1] == 0) {
                aux++;
            }
        }
    }

    if (column > 0) {
        if (board->visibility[line][column - 1] == 0) {
            aux++;
        }
    }
    if (column < board->columns - 1) {
        if (board->visibility[line][column + 1] == 0) {
            aux++;
        }
    }

    if (line < board->lines - 1) {
        if (column > 0) {
            if (board->visibility[line + 1][column - 1] == 0) {
                aux++;
            }
        }
        if (board->visibility[line + 1][column] == 0) {
            aux++;
        }
        if (column < board->columns - 1) {
            if (board->visibility[line + 1][column + 1] == 0) {
                aux++;
            }
        }
    }

    return aux;
}

void increment_chances(struct minesweeper_board *board, int line,
                       int column, int probability, struct solver_helper *solver) {

    if (line > 0) {
        if (column > 0) {
            if (board->visibility[line - 1][column - 1] == 0) {
                solver->chance[line - 1][column - 1] += probability;
            }
        }
        if (board->visibility[line - 1][column] == 0) {
            solver->chance[line - 1][column] += probability;
        }
        if (column < board->columns - 1) {
            if (board->visibility[line - 1][column + 1] == 0) {
                solver->chance[line - 1][column + 1] += probability;
            }
        }
    }

    if (column > 0) {
        if (board->visibility[line][column - 1] == 0) {
            solver->chance[line][column - 1] += probability;
        }
    }
    if (column < board->columns - 1) {
        if (board->visibility[line][column + 1] == 0) {
            solver->chance[line][column + 1] += probability;
        }
    }

    if (line < board->lines - 1) {
        if (column > 0) {
            if (board->visibility[line + 1][column - 1] == 0) {
                solver->chance[line + 1][column - 1] += probability;
            }
        }
        if (board->visibility[line + 1][column] == 0) {
            solver->chance[line + 1][column] += probability;
        }
        if (column < board->columns - 1) {
            if (board->visibility[line + 1][column + 1] == 0) {
                solver->chance[line + 1][column + 1] += probability;
            }
        }
    }
}

void set_chances(struct minesweeper_board *board, struct solver_helper *solver) {
    int iterator1;
    int iterator2;

    int square_prob;
    int hidden_squares;

    for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
        for (iterator2 = 0; iterator2 < board->columns; iterator2++) {

            if (board->visibility[iterator1][iterator2] == 0) {
                continue;
            }
            if (board->base[iterator1][iterator2] == 0) {
                continue;
            }

            hidden_squares = adj_hidden_squares(board, iterator1, iterator2);
            square_prob = (board->base[iterator1][iterator2] * 100) / hidden_squares;
            increment_chances(board, iterator1, iterator2, square_prob, solver);
        }
    }
}

void open_min(struct minesweeper_board *board, struct solver_helper *solver) {
    int iterator1;
    int iterator2;

    int min_prob = 1000;

    int min_line = 0;
    int min_column = 0;

    for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
        for (iterator2 = 0; iterator2 < board->columns; iterator2++) {
            if (solver->chance[iterator1][iterator2] != 0 && solver->chance[iterator1][iterator2] < min_prob) {
                min_prob = solver->chance[iterator1][iterator2];
                min_line = iterator1;
                min_column = iterator2;
            }
        }
    }

    printf("Opening square at (%d, %d)\n", min_line, min_column);
    reveal(board, min_line, min_column);
}

int adj_marked_squares(struct minesweeper_board *board, int line, int column, struct solver_helper *solver) {
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
                        print_board(board);
                    }
                }
                if (board->visibility[iterator1 - 1][iterator2] == 0 &&
                    solver->marked[iterator1 - 1][iterator2] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1 - 1, iterator2);
                    reveal(board, iterator1 - 1, iterator2);
                    print_board(board);
                }
                if (iterator2 < board->columns - 1) {
                    if (board->visibility[iterator1 - 1][iterator2 + 1] == 0 &&
                        solver->marked[iterator1 - 1][iterator2 + 1] == 0) {

                        printf("Opened square at (%d, %d)\n", iterator1 - 1, iterator2 + 1);
                        reveal(board, iterator1 - 1, iterator2 + 1);
                        print_board(board);
                    }
                }
            }

            if (iterator2 > 0) {
                if (board->visibility[iterator1][iterator2 - 1] == 0 &&
                    solver->marked[iterator1][iterator2 - 1] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1, iterator2 - 1);
                    reveal(board, iterator1, iterator2 - 1);
                    print_board(board);
                }
            }
            if (iterator2 < board->columns - 1) {
                if (board->visibility[iterator1][iterator2 + 1] == 0 &&
                    solver->marked[iterator1][iterator2 + 1] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1, iterator2 + 1);
                    reveal(board, iterator1, iterator2 + 1);
                    print_board(board);
                }
            }

            if (iterator1 < board->lines - 1) {
                if (board->columns > 0) {
                    if (board->visibility[iterator1 + 1][iterator2 - 1] == 0 &&
                        solver->marked[iterator1 + 1][iterator2 - 1] == 0) {

                        printf("Opened square at (%d, %d)\n", iterator1 + 1, iterator2 - 1);
                        reveal(board, iterator1 + 1, iterator2 - 1);
                        print_board(board);
                    }
                }
                if (board->visibility[iterator1 + 1][iterator2] == 0 &&
                    solver->marked[iterator1 + 1][iterator2] == 0) {

                    printf("Opened square at (%d, %d)\n", iterator1 + 1, iterator2);
                    reveal(board, iterator1 + 1, iterator2);
                    print_board(board);
                }
                if (iterator2 < board->columns - 1) {
                    if (board->visibility[iterator1 + 1][iterator2 + 1] == 0 &&
                        solver->marked[iterator1 + 1][iterator2 + 1] == 0) {

                        printf("Opened square at (%d, %d)\n", iterator1 + 1, iterator2 + 1);
                        reveal(board, iterator1 + 1, iterator2 + 1);
                        print_board(board);
                    }
                }
            }
        }
    }
}

void solve_game(struct minesweeper_board *board) {
    int iterator1;
    int iterator2;

    struct solver_helper *solver = malloc((size_t) sizeof(struct solver_helper));

    solver->chance = (int **)calloc((size_t) board->lines, sizeof(int *));
    solver->marked = (int **)calloc((size_t) board->lines, sizeof(int *));
    for (int iterator = 0; iterator < board->lines; iterator++) {
        solver->chance[iterator] = (int *)calloc((size_t) board->columns, sizeof(int));
        solver->marked[iterator] = (int *)calloc((size_t) board->columns, sizeof(int));
    }

    while (board->bomb_hit == 0) {
        for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
            for (iterator2 = 0; iterator2 < board->columns; iterator2++) {
                solver->chance[iterator1][iterator2] = 0;
                solver->marked_squares = 0;
            }
        }

        mark_squares(board, solver);

        if (solver->marked_squares != 0) {
            open_unmarked(board, solver);
        } else {
            set_chances(board, solver);
            open_min(board, solver);
            print_board(board);
        }

        if (board->open_squares == board->lines * board->columns - board->nr_bombs) {
            printf("Solver succeeded!\n");
            break;
        }
    }

    for (int iterator = 0; iterator < board->lines; iterator++) {
        free(solver->chance[iterator]);
        free(solver->marked[iterator]);
    }
    free(solver->chance);
    free(solver->marked);
    free(solver);
}
