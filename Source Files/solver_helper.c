/**
 * @file solver_helper.c
 * @brief C library containing functions that help the solving process.
 * @author Vasilescu Vlad
 */

#include "../Header Files/board.h"

int adj_hidden_squares(struct minesweeper_board *board, int line, int column) {
    /**
     * @fn int adj_hidden_squares(struct minesweeper_board, int line, int column)
     * @brief Returns the number of hidden squares adjacent to the given coordinates.
     * @param *board The board itself.
     * @param line First coordinate of the square.
     * @param column Second coordinate of the square.
     */
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