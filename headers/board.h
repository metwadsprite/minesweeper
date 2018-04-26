/**
 * @file board.h
 * @brief C library containing the board.
 * @author Vasilescu Vlad
 *
 *
 * Definition of the board as data structure that contains all it's properties.
 */

#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

struct minesweeper_board {
    /// How many lines the board has.
    int lines;
    /// How many columns the board has.
    int columns;
    /// How many bombs are placed on the board.
    int nr_bombs;
    /// How many squares have been opened.
    int open_squares;
    /// If a bomb has been hit or not.
    int bomb_hit;

    /// The board itself.
    int *base;
    /// If a square has been opened or not.
    int *visibility;
};

#endif //MINESWEEPER_BOARD_H
