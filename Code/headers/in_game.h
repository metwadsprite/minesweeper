/**
 * @file in_game.h
 * @brief C library for actions used during the game.
 *
 * Implements printing the board and opening a square.
 */

#ifndef MINESWEEPER_IN_GAME_H
#define MINESWEEPER_IN_GAME_H

void print_board(struct minesweeper_board *board);
void reveal(struct minesweeper_board *board, int line, int col);
void flag(struct minesweeper_board *board, int line, int column);

#endif //MINESWEEPER_IN_GAME_H
