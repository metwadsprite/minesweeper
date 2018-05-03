/**
 * @file in_game.c
 * @brief C library containing the functions used during gameplay.
 * @author Vasilescu Vlad
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/board.h"

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

    printf("   ");
    for (iterator1 = 0; iterator1 < board->columns; iterator1++) {
        printf(" %d", iterator1);
    }
    printf("\n\n");

    for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
        printf("%d   ", iterator1);

        for (iterator2 = 0; iterator2 < board->columns; iterator2++) {

            if (board->visibility[iterator1][iterator2] == 1) {
                if (board->base[iterator1][iterator2] >= 10) {
                    printf("B ");
                } else if (board->base[iterator1][iterator2] == 0) {
                    printf("  ");
                } else {
                    printf("%d ", board->base[iterator1][iterator2]);
                }
            } else {
                printf("%c ", 'H');
            }
        }

        printf("\n");
    }
}

void reveal(struct minesweeper_board *board, int line, int col) {
    /**
     * @fn int reveal(struct minesweeper_board *board, int line, int col)
     * @brief Opens a square.
     * @param *board The board and all it's details contained in a struct.
     * @param line The line on which the square to be opened is located.
     * @param col The column on which the square to be opened is located.
     *
     * The function opens the square on the given coordinates and returns a number
     * based on what is underneath it:
     * -If it finds nothing then it calls itself for all adjecant squares.
     * -If it finds a number it returns a "0".
     * -If it finds a bomb then it returns a "1" so that the program can terminate.
     */

    if (board->visibility[line][col]) {
        return;
    }

    if (board->base[line][col] == 0) {
        board->visibility[line][col] = 1;
        board->open_squares++;

        if (line > 0) {
            reveal(board, line - 1, col);
            if (col > 0) {
                reveal(board, line - 1, col - 1);
            }
            if (col < board->columns - 1) {
                reveal(board, line - 1, col + 1);
            }
        }
        if (line < board->lines - 1) {
            reveal(board, line + 1, col);
            if (col > 0) {
                reveal(board, line + 1, col - 1);
            }
            if (col < board->columns - 1) {
                reveal(board, line + 1, col + 1);
            }
        }
        if (col > 0) {
            reveal(board, line, col - 1);
        }
        if (col < board->columns - 1) {
            reveal(board, line, col + 1);
        }

    } else if (board->base[line][col] >= 10) {
        printf("You hit a bomb!\n");
        board->visibility[line][col] = 1;
        board->bomb_hit = 1;
    } else {
        board->visibility[line][col] = 1;
        board->open_squares++;
    }
}