/**
 * @file main.c
 * @brief Main file where all the functions are called from.
 *
 * @author Vasilescu Vlad
 *
 * Generates a playable minesweeper board.
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/board.h"
#include "headers/pre_game.h"
#include "headers/in_game.h"
#include "headers/solver.h"

int main(void) {
    /**
     * @fn int main(void)
     * @brief Main function that takes user input for generating the board
     * and playing the game.
     */

    int line;
    int col;

    struct minesweeper_board *board;
    board = malloc((size_t) sizeof(struct minesweeper_board));

    board->open_squares = 0;
    board->bomb_hit = 0;

    printf("Give board height, length and nr. of bombs: \n");
    scanf("%d %d %d", &board->lines, &board->columns, &board->nr_bombs);

    board->base = (int **)calloc((size_t) board->lines, sizeof(int *));
    board->visibility = (int **)calloc((size_t) board->lines, sizeof(int*));

    for (int iterator = 0; iterator < board->lines; iterator++) {
        board->base[iterator] = (int *)calloc((size_t) board->columns, sizeof(int));
        board->visibility[iterator] = (int *)calloc((size_t) board->columns, sizeof(int));
    }

    if (board->nr_bombs > (board->lines * board->columns) - 4) {
        printf("Invalid board\n");
        return 0;
    }

    print_board(board);

    printf("Give coordinates of square you want to open: \n");
    scanf("%d %d", &line, &col);

    while (line >= board->lines || col >= board->columns || line < 0 || col < 0) {
        printf("Invalid coordinates\nTry again:\n");
        scanf("%d %d", &line, &col);
    }

    set_board(board, line, col);
    reveal(board, line, col);
    print_board(board);

    if (board->open_squares == board->lines * board->columns - board->nr_bombs) {
        printf("You won!\n");
        return 0;
    }

    printf("Type 1 to play the game or 2 to solve it:\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        while(board->bomb_hit == 0) {
            printf("Give new set of coordinates:\n");
            scanf("%d %d", &line, &col);

            while (line >= board->lines || col >= board->columns || line < 0 || col < 0) {
                printf("Invalid coordinates\nTry again:\n");
                scanf("%d %d", &line, &col);
            }

            reveal(board, line, col);
            print_board(board);

            if (board->open_squares == board->lines * board->columns - board->nr_bombs) {
                printf("You won!\n");
                break;
            }
        }
    } else if (choice == 2) {
        solve_game(board);
    }

    for (int iterator = 0; iterator < board->lines; iterator++) {
        free(board->base[iterator]);
        free(board->visibility[iterator]);
    }
    free(board->base);
    free(board->visibility);
    free(board);
    return 0;
}
