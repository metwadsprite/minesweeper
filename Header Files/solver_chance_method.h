/**
 * @file solver_chance_method.h
 * @brief C library containing the functions used by the chance method.
 */

#ifndef MINESWEEPER_SOLVER_CHANCE_METHOD_H
#define MINESWEEPER_SOLVER_CHANCE_METHOD_H

void increment_chances(struct minesweeper_board *board, int line,
                       int column, int probability, struct solver_helper *solver);

void set_chances(struct minesweeper_board *board, struct solver_helper *solver);

void open_min(struct minesweeper_board *board, struct solver_helper *solver);

#endif //MINESWEEPER_SOLVER_CHANCE_METHOD_H
