//
// Created by vladv on 4/19/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include "headers/board.h"

void print_board(struct minesweeper_board *board){
    int iterator1;
    int iterator2;
    int position;

    printf("   ");
    for (iterator1 = 0; iterator1 < board->columns; iterator1++) {
        printf(" %d", iterator1);
    }
    printf("\n\n");

    for (iterator1 = 0; iterator1 < board->lines; iterator1++) {
        printf("%d   ", iterator1);

        for (iterator2 = 0; iterator2 < board->columns; iterator2++) {
            position = iterator1 * board->columns + iterator2;

            if (board->visibility[position] == 1) {
                if (board->base[position] >= 10) {
                    printf("B ");
                } else if (board->base[position] == 0) {
                    printf("  ");
                } else {
                    printf("%d ", board->base[position]);
                }
            } else {
                printf("%c ", 'H');
            }
        }

        printf("\n");
    }
}

int reveal(struct minesweeper_board *board, int line, int col) {
    int position;
    position = line * board->columns + col;

    if (board->visibility[position]) {
        return 0;
    }

    /*
     * Whenever the player opens a square with 0 bombs around it
     * we use a recursive flood algorithm to open all the non-bombs
     * squares around it.
     */
    if (board->base[position] == 0) {
        board->visibility[position] = 1;
        board->open_squares++;

        if (line > 0) {
            reveal(board, line - 1, col);
        }
        if (line < board->lines - 1) {
            reveal(board, line + 1, col);
        }
        if (col > 0) {
            reveal(board, line, col - 1);
        }
        if (col < board->columns - 1) {
            reveal(board, line, col + 1);
        }

    } else if (board->base[position] >= 10) {
        printf("You hit a bomb!\n");
        board->visibility[position] = 1;
        return 1;
    } else {
        board->visibility[position] = 1;
        board->open_squares++;
        return 0;
    }
}