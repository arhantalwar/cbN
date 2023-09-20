#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>

#define width 1024
#define height  720
#define sqSize 240

int player_turn = 0; // BLUE PLAYER STARTS FIRST

int** initBoard(int** board) {

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = -1;
        }
    }

    return board;

}

void drawBoard(int** board) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == -1) {
                DrawRectangle(i * sqSize, j * sqSize, sqSize, sqSize, RAYWHITE);
            } else if (board[i][j] == 0) {
                DrawRectangle(i  * sqSize, j * sqSize, sqSize, sqSize, BLUE);
            } else {
                DrawRectangle(i * sqSize, j * sqSize, sqSize, sqSize, RED);
            }
        }
    }
}

int** playerTurn(int mouseOnBoard, int** board) {

    int x = mouseOnBoard % 3;
    int y = mouseOnBoard / 3;

    if(player_turn == 0) {
        board[x][y] = 0;
        player_turn = 1;
    } else {
        board[x][y] = 1;
        player_turn = 0;
    }

    return board;

}

// GAME OVER CHECKS

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

    // RAYLIB
    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(60);

    InitWindow(width, height, "TIC TAC TOE");

    int diag_check_board[3][3] = {
        {-1, -1, -1},
        {-1, -1, -1},
        {-1, -1, -1},
    };

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = diag_check_board[i][j];
        }
    }

    drawBoard(board);

    while(!WindowShouldClose()) {

        int mouseX = GetMouseX() / sqSize;
        int mouseY = GetMouseY() / sqSize;
        int mouseOnBoard = 3 * mouseY + mouseX;


        BeginDrawing();

        if(IsMouseButtonPressed(0)) {
            board = playerTurn(mouseOnBoard, board);
            drawBoard(board);
        }

        EndDrawing();

    }

    CloseWindow();

    // FREE THE MEM
    for(int i = 0; i < 3; i++) {
        free(board[i]);
    }

    free(board);

    return 0;

}
