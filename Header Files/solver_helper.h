/**
 * @file solver_helper.h
 * @brief C library containing a solver helper as a data structure and
 * functions that help the solving process.
 * @author Vasilescu Vlad
 */

#ifndef MINESWEEPER_SOLVER_HELPER_H
#define MINESWEEPER_SOLVER_HELPER_H

struct solver_helper {
    /// Number of marked squares on each step.
    int marked_squares;

    /// Matrix used by the chance method.
    int **chance;
    /// Matrix used by the marking method.
    int **marked;
};

int adj_hidden_squares(struct minesweeper_board *board, int line, int column);

#endif //MINESWEEPER_SOLVER_HELPER_H
