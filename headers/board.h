//
// Created by vladv on 4/26/2018.
//

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

struct minesweeper_board {
    int lines;
    int columns;
    int nr_bombs;
    int open_squares;
    int bomb_hit;

    int *base;
    int *visibility;
};

#endif //MINESWEEPER_BOARD_H
