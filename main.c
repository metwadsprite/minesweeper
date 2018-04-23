#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/pre_game.h"
#include "headers/in_game.h"

int main() {
    int *board;
    int *is_revealed;

    int board_lines;
    int board_columns;
    int nr_bombs;

    int line;
    int col;

    int bomb_hit = 0;

    printf("Give board height, length and nr. of bombs: \n");
    scanf("%d %d %d", &board_lines, &board_columns, &nr_bombs);

    board = calloc((size_t) board_lines * board_columns, sizeof(int));
    is_revealed = calloc((size_t) (board_lines + 2) * board_columns, sizeof(int));

    if (nr_bombs >= (board_lines * board_columns) / 2) {
        printf("Invalid board\n");
        return 0;
    }

    hide_all(is_revealed, board_lines, board_columns);
    print_board(board, is_revealed, board_lines, board_columns);

    printf("Give coordinates of square you want to open: \n");
    scanf("%d %d", &line, &col);

    while (line > board_lines || col > board_columns) {
        printf("Invalid coordinates\n");
        scanf("%d %d", &line, &col);
    }

    set_board(board, nr_bombs, board_lines, board_columns, line, col);

    bomb_hit = reveal(board, is_revealed, board_lines, board_columns, line, col);

    print_board(board, is_revealed, board_lines, board_columns);

    if (win_check(board, is_revealed, board_lines, board_columns)) {
        printf("You won!\n");
        return 0;
    }

    while(bomb_hit == 0) {
        printf("Give new set of coordinates:\n");
        scanf("%d %d", &line, &col);

        bomb_hit = reveal(board, is_revealed, board_lines, board_columns, line, col);
        print_board(board, is_revealed, board_lines, board_columns);

        if (win_check(board, is_revealed, board_lines, board_columns)) {
            printf("You won!\n");
            break;
        }
    }

    printf("Press any key to continue...\n");
    getchar();
    getchar();

    free(board);
    free(is_revealed);

    return 0;
}