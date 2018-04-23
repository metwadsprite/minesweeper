//
// Created by vladv on 4/19/2018.
//

#ifndef MINESWEEPER_IN_GAME_H
#define MINESWEEPER_IN_GAME_H

void print_board(int *board, int *is_revealed, int board_he, int board_le);
int reveal(int *board, int *is_revealed, int board_lines, int board_columns, int line, int col);
int win_check(int *board, int *is_revealed, int board_lines, int board_columns);

#endif //MINESWEEPER_IN_GAME_H
