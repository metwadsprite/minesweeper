//
// Created by vladv on 4/19/2018.
//

#ifndef MINESWEEPER_IN_GAME_H
#define MINESWEEPER_IN_GAME_H

void print_board(struct minesweeper_board *board);
int reveal(struct minesweeper_board *board, int line, int col);

#endif //MINESWEEPER_IN_GAME_H
