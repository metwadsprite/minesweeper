/**
 * @file pre_game.h
 * @brief C library for actions performed before playing the game.
 * @author Vasilescu Vlad.
 *
 * Generates the board.
 */

#ifndef MINESWEEPER_PRE_GAME_H
#define MINESWEEPER_PRE_GAME_H

void set_board(struct minesweeper_board *board, int start_line, int start_column);

#endif //MINESWEEPER_PRE_GAME_H
