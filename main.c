#include <stdio.h>
#include <stdlib.h>
#include "headers/pre_game.h"
#include "headers/in_game.h"
#include "headers/board.h"

int main() {
    int line;
    int col;

    struct minesweeper_board *board;
    board = malloc((size_t) sizeof(struct minesweeper_board));

    board->open_squares = 0;
    board->bomb_hit = 0;



    printf("Give board height, length and nr. of bombs: \n");
    scanf("%d %d %d", &board->lines, &board->columns, &board->nr_bombs);

    board->base = calloc((size_t) board->lines * board->columns, sizeof(int));
    board->visibility = calloc((size_t) board->lines * board->columns, sizeof(int));

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

    /*
     * We generate the board after the first set of coordinates is given
     * to prevent unsolvable boards.
     */
    set_board(board, line, col);

    board->bomb_hit = reveal(board, line, col);

    print_board(board);

    if (board->open_squares == board->lines * board->columns - board->nr_bombs) {
        printf("You won!\n");
        return 0;
    }

    while(board->bomb_hit == 0) {
        printf("Give new set of coordinates:\n");
        scanf("%d %d", &line, &col);

        while (line >= board->lines || col >= board->columns || line < 0 || col < 0) {
            printf("Invalid coordinates\nTry again:\n");
            scanf("%d %d", &line, &col);
        }

        board->bomb_hit = reveal(board, line, col);
        print_board(board);

        if (board->open_squares == board->lines * board->columns - board->nr_bombs) {
            printf("You won!\n");
            break;
        }
    }

    free(board);
    return 0;
}
