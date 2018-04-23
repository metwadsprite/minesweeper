//
// Created by vladv on 4/19/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include "headers/pre_game.h"

void print_board(int *board, int *is_revealed, int board_lines, int board_columns){
    int iterator1;
    int iterator2;
    int position;

    printf("   ");
    for (iterator1 = 0; iterator1 < board_columns; iterator1++) {
        printf(" %d", iterator1);
    }
    printf("\n\n");

    for (iterator1 = 0; iterator1 < board_lines; iterator1++) {
        printf("%d   ", iterator1);

        for (iterator2 = 0; iterator2 < board_columns; iterator2++) {
            position = iterator1 * board_columns + iterator2;

            if (is_revealed[position] == 1) {
                if (board[position] >= 10) {
                    printf("B ");
                } else if (board[position] == 0) {
                    printf("  ");
                } else {
                    printf("%d ", board[position]);
                }
            } else {
                printf("%c ", 'H');
            }
        }

        printf("\n");
    }
}

int reveal(int *board, int *is_revealed, int board_lines, int board_columns, int line, int col) {
    int position;
    position = line * board_columns + col;

    if (is_revealed[position]) {
        return 0;
    }

    /*
     * Whenever the player opens a square with 0 bombs around it
     * we use a recursive flood algorithm to open all the non-bombs
     * squares around it.
     */
    if (board[position] == 0) {
        is_revealed[position] = 1;

        if (line > 0) {
            reveal(board, is_revealed, board_lines, board_columns, line - 1, col);
        }
        if (line < board_lines - 1) {
            reveal(board, is_revealed, board_lines, board_columns, line + 1, col);
        }
        if (col > 0) {
            reveal(board, is_revealed, board_lines, board_columns, line, col - 1);
        }
        if (col < board_columns - 1) {
            reveal(board, is_revealed, board_lines, board_columns, line, col + 1);
        }

    } else if (board[position] >= 10) {
        printf("You hit a bomb!\n");
        is_revealed[position] = 1;
        return 1;
    } else {
        is_revealed[position] = 1;
        return 0;
    }
}

int win_check(int *board, int *is_revealed, int board_lines, int board_columns) {
    int iterator1;
    int iterator2;
    int position;

    int won = 1;

    for (iterator1 = 0; iterator1 < board_lines; iterator1++) {
        for (iterator2 = 0; iterator2 < board_columns; iterator2++) {
            position = iterator1 * board_columns + iterator2;

            if (board[position] < 10 && is_revealed[position] == 0) {
                won = 0;
            }
        }
    }

    if (won) {
        return 1;
    } else {
        return 0;
    }
}