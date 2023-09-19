#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int** initBoard(int** board) {

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ((float) rand() / (float) RAND_MAX) * 10.f;
        }
    }

    return board;

}

bool hori_check(int** board, int player) {

    for(int i = 0; i < 3; i++) {
        bool is_over = false;
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == player) {
                is_over = true;
            } else {
                is_over = false;
                break;
            }
        }
        if(is_over == true) {
            return true;
        }
    }

    return false;

}

bool veri_check(int** board, int player) {

    for(int i = 0; i < 3; i++) {
        bool is_over = false;
        for(int j = 0; j < 3; j++) {
            if(board[j][i] == player) {
                is_over = true;
            } else {
                is_over = false;
                break;
            }
        }
        if(is_over == true) {
            return true;
        }
    }

    return false;

}

bool diag_check1(int** board, int player) {

    bool is_over = false;

    for(int i = 0; i < 3; i++) {
        if(board[i][i] == player) {
            is_over = true;
        } else {
            is_over = false;
            break;
        }
    }

    if(is_over == true) {
        return true;
    }

    return false;

}

bool diag_check2(int** board, int player) {

    bool is_over = false;

    for(int i = 0; i < 3; i++) {
        if(board[i][2-i] == player) {
            is_over = true;
        } else {
            is_over = false;
            break;
        }
    }

    if(is_over == true) {
        return true;
    }

    return false;

}


void printBoard(int** board) {

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int main() {

    // ALLOCATE MEM
    int** board = (int**) malloc(sizeof(int) * 3);

    for(int i = 0; i < 3; i++) {
        board[i] = (int*) malloc(sizeof(int) * 3);
    }

    // INIT BOARD WITH ZEROES
    initBoard(board);

    int hori_check_board[3][3] = {
        {1, 1, 1},
        {0, 0, 0},
        {1, 1, 1},
    };

    int veri_check_board[3][3] = {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
    };

    int diag_check_board[3][3] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1},
    };

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = diag_check_board[i][j];
        }
    }

    bool hori_check_ans = hori_check(board, 1);
    bool veri_check_ans = veri_check(board, 1);
    bool diag_check_ans = diag_check2(board, 1);

    printf("%d\n", diag_check_ans);

    // FREE THE MEM
    for(int i = 0; i < 3; i++) {
        free(board[i]);
    }

    free(board);

    return 0;

}
