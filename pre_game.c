//
// Created by vladv on 4/19/2018.
//
#include <stdlib.h>
#include <time.h>

void set_board(int *board, int nr_bombs, int board_lines, int board_columns, int start_line, int start_col) {
    int line_index;
    int col_index;
    int c_nr_bombs = 0;
    int position;

    srand((unsigned) time(NULL));

    while (c_nr_bombs < nr_bombs) {
        line_index = rand() % board_lines;
        col_index = rand() % board_columns;

        position = line_index * board_columns + col_index;

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
        } else if (board[position] == 10) {
            continue;
        } else {
            board[position] = 10;
            c_nr_bombs++;

            if (line_index > 0) {
                if (col_index > 0) {
                    board[(line_index - 1) * board_columns + col_index - 1]++;
                }
                board[(line_index - 1) * board_columns + col_index]++;
                if (col_index < board_columns - 1) {
                    board[(line_index - 1) * board_columns + col_index + 1]++;
                }
            }
            if (col_index > 0) {
                board[(line_index) * board_columns + col_index - 1]++;
            }
            if (col_index < board_columns - 1) {
                board[(line_index) * board_columns + col_index + 1]++;
            }
            if (line_index < board_lines - 1) {
                if (col_index > 0) {
                    board[(line_index + 1) * board_columns + col_index - 1]++;
                }
                board[(line_index + 1) * board_columns + col_index]++;
                if (col_index < board_columns - 1) {
                    board[(line_index + 1) * board_columns + col_index + 1]++;
                }
            }
        }
    }
}