/**
 * @file solver_chance_method.c
 * @brief C library containing the functions used by the chance method.
 * @author Vasilescu Vlad
 */

#include <stdio.h>
#include "headers/board.h"
#include "headers/in_game.h"
#include "headers/solver_helper.h"

void increment_chances(struct minesweeper_board *board, int line,
                       int column, int probability, struct solver_helper *solver) {
    /**
     * @fn void increment_chances(struct minesweeper_board *board, int line, int column, int probability, struct solver_helper *solver)
     * @brief Function that increments the chances around a given square.
     * @param *board The board itself.
     * @param line First coordinate of the square.
     * @param column Second coordinate of the square.
     * @param probability Number by which each cell should be incremented.
     * @param *solver Contains information about all the chances on the board.
     */

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
    /**
     * @fn void set_chances(struct minesweeper_board *board, struct solver_helper *solver)
     * @fn Function that sets the chances on the entire board.
     * @param *board The board itself.
     * @param *solver Contains information about all the chances on the board.
     *
     * A "chance" represents the probability of a given square to be a bomb. It is
     * calculated with the formula: "number on the cell" divided by "number of hidden
     * squares around it", which is multiplied by 100 so it fits in an integer type.
     * The resulting number is then "added" into every adjacent hidden square's previous
     * chance.
     */

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
    /**
     * @fn void open_min(struct minesweeper_board *board, struct solver_helper *solver)
     * @brief Function that opens the square with the smallest chance of it being a bomb.
     * @param *board The board itself.
     * @param *solver Contains information about all the chances on the board.
     */

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