/**
 * @file pre_game.c
 * @brief C library containing the function that generate a randomized minesweeper board.
 * @author Vasilescu Vlad
 */

#include <stdlib.h>
#include <time.h>
#include "headers/board.h"

void set_board(struct minesweeper_board *board, int start_line, int start_col) {
    /**
     * @fn void set_board(struct minesweeper_board *board, int start_line, int start_col)
     * @brief Function that takes as input an empty board and two starting coordinates
     * and generates it such that no bomb is placed close to the starting position.
     * @param *board The board and all it's details contained in a struct.
     * @param start_line The line on which the starting position is located.
     * @param start_col The column on which the starting position is located.
     *
     * The function firstly makes sure it doesn't place the bomb on or adjecent to the starting position,
     * then places it and increases the value of every square around it by one.
     */

    int line_index;
    int col_index;
    int c_nr_bombs = 0;

    srand((unsigned) time(NULL));

    while (c_nr_bombs < board->nr_bombs) {
        line_index = rand() % board->lines;
        col_index = rand() % board->columns;

        if (start_col - 1 == col_index) {
            if (start_line - 1 == line_index) continue;
            else if (start_line == line_index) continue;
            else if (start_line + 1 == line_index) continue;
        } else if (start_col == col_index) {
            if (start_line - 1 == line_index) continue;
            else if (start_line == line_index) continue;
            else if (start_line + 1 == line_index) continue;
        } else if (start_col + 1 == col_index) {
            if (start_line - 1 == line_index) continue;
            else if (start_line == line_index) continue;
            else if (start_line + 1 == line_index) continue;
        } else if (board->base[line_index][col_index] >= 10) {
            continue;
        } else {
            board->base[line_index][col_index] = 10;
            c_nr_bombs++;

            if (line_index > 0) {
                if (col_index > 0) {
                    board->base[line_index - 1][col_index - 1]++;
                }
                board->base[line_index - 1][col_index]++;
                if (col_index < board->columns - 1) {
                    board->base[line_index - 1][col_index + 1]++;
                }
            }
            if (col_index > 0) {
                board->base[line_index][col_index - 1]++;
            }
            if (col_index < board->columns - 1) {
                board->base[line_index][col_index + 1]++;
            }
            if (line_index < board->lines - 1) {
                if (col_index > 0) {
                    board->base[line_index + 1][col_index - 1]++;
                }
                board->base[line_index + 1][col_index]++;
                if (col_index < board->columns - 1) {
                    board->base[line_index + 1][col_index + 1]++;
                }
            }
        }
    }
}
