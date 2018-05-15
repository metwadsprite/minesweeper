/**
 * @file solver.c
 * @brief C library containing the main solver function.
 * @author Vasilescu Vlad
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/board.h"
#include "../headers/in_game.h"
#include "../headers/solver_helper.h"
#include "../headers/solver_mark_method.h"
#include "../headers/solver_chance_method.h"

void solve_game(struct minesweeper_board *board) {
    /**
     * @fn void solve_game(struct minesweeper_board *board)
     * @brief Function that takes the board as input and decides whether to use
     * the marking or the chances method on each step until the board is solved or
     * a bomb is hit.
     * @param *board the board itself.
     */

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

    free(solver);
}
