/**
 * @file in_game.c
 * @brief C library containing the functions used during gameplay.
 * @author Vasilescu Vlad
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/board.h"

void print_board(struct minesweeper_board *board){
    /**
     * @fn void print_board(struct minesweeper_board *board)
     * @brief Prints the board to standard output.
     * @param *board The board and all it's details contained in a struct.
     *
     * The function prints the board.
     */

    int iterator1;
    int iterator2;

    for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
        for (iterator2 = 0; iterator2 < board->columns; iterator2++) {

            if (board->visibility[iterator1][iterator2] == 1) {
                if (board->base[iterator1][iterator2] >= 10) {
                    printf("B ");
                } else if (board->base[iterator1][iterator2] == 0) {
                    printf("  ");
                } else {
                    printf("%d ", board->base[iterator1][iterator2]);
                }
            } else if (board->visibility[iterator1][iterator2] == 2) {
                printf("F ");
            } else {
                printf("%c ", 'H');
            }
        }

        printf("\n");
    }
}

void reveal(struct minesweeper_board *board, int line, int column) {
    /**
     * @fn void reveal(struct minesweeper_board *board, int line, int col)
     * @brief Opens a square.
     * @param *board The board and all it's details contained in a struct.
     * @param line The line on which the square to be opened is located.
     * @param column The column on which the square to be opened is located.
     *
     * The function opens the square on the given coordinates. If the number on the square
     * is "0" the function calls itself on all adjancet squares.
     */

    if (board->visibility[line][column]) {
        return;
    }
    if (board->visibility[line][column] == 2) {
        return;
    }

    if (board->base[line][column] == 0) {
        board->visibility[line][column] = 1;
        board->open_squares++;

        if (line > 0) {
            reveal(board, line - 1, column);
            if (column > 0) {
                reveal(board, line - 1, column - 1);
            }
            if (column < board->columns - 1) {
                reveal(board, line - 1, column + 1);
            }
        }
        if (line < board->lines - 1) {
            reveal(board, line + 1, column);
            if (column > 0) {
                reveal(board, line + 1, column - 1);
            }
            if (column < board->columns - 1) {
                reveal(board, line + 1, column + 1);
            }
        }
        if (column > 0) {
            reveal(board, line, column - 1);
        }
        if (column < board->columns - 1) {
            reveal(board, line, column + 1);
        }

    } else if (board->base[line][column] >= 10) {
        printf("You hit a bomb!\n");
        board->visibility[line][column] = 1;
        board->bomb_hit = 1;
    } else {
        board->visibility[line][column] = 1;
        board->open_squares++;
    }
}

void flag(struct minesweeper_board *board, int line, int column) {
    /**
     * @fn void flag(struct minesweeper_board *board, int line, int column)
     * @brief Places/Removes a flag on a square.
     * @param *board The board itself.
     * @param line The first coordinate of the square.
     * @param column The second coordinate of the square.
     */

    if (board->visibility[line][column] == 1) {
        printf("Cant place flag on an open square!\n");
        return;
    }
    if (board->visibility[line][column] == 2) {
        board->visibility[line][column] = 1;
    }

    board->visibility[line][column] = 2;
}