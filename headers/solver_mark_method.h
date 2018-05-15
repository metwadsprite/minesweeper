/**
 * @file solver_mark_method.h
 * @brief C library containing the functions used by the marking method.
 */

#ifndef MINESWEEPER_SOLVER_MARK_METHOD_H
#define MINESWEEPER_SOLVER_MARK_METHOD_H

int adj_marked_squares(struct minesweeper_board *board, int line, int column, struct solver_helper *solver);
void mark_squares(struct minesweeper_board *board, struct solver_helper *solver);
void open_unmarked(struct minesweeper_board *board, struct solver_helper *solver);

#endif //MINESWEEPER_SOLVER_MARK_METHOD_H
