#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>

#define width 720
#define height 720
#define sqSize 240

int player_turn = 1; // AI PLAYER STARTS FIRST
                     
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
                DrawRectangleLines(i * sqSize, j * sqSize, sqSize, sqSize, BLACK);
            } else if (board[i][j] == 0) {
                DrawRectangle(i  * sqSize, j * sqSize, sqSize, sqSize, BLUE);
                DrawRectangleLines(i * sqSize, j * sqSize, sqSize, sqSize, BLACK);
            } else {
                DrawRectangle(i * sqSize, j * sqSize, sqSize, sqSize, RED);
                DrawRectangleLines(i * sqSize, j * sqSize, sqSize, sqSize, BLACK);
            }
        }
    }
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

// CHECK IF OVER
int checkIfOver(int** board, int player) {
    if(
            hori_check(board, player) ||
            veri_check(board, player) ||
            diag_check1(board, player) ||
            diag_check2(board, player)
      ) {
        return player;
    }

    return -1;

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

int minimax(int** board, int depth, bool isMax) {

    int resultO = checkIfOver(board, 0);
    int resultX = checkIfOver(board, 1);

    if(resultO == 0) {
        return resultO;
    } else if (resultX == 1) {
        return resultX;
    }


    if(isMax == true) {

        int bestScore = -1000;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == -1) {

                    board[i][j] = 1;
                    int score = minimax(board, depth + 1, false);
                    board[i][j] = -1;

                    if(score > bestScore) {
                        bestScore = score;
                    }

                }
            }
        }

        return bestScore;

    } else {

        int bestScore = 1000;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == -1) {

                    board[i][j] = 0;
                    int score = minimax(board, depth + 1, true);
                    board[i][j] = -1;

                    if(score < bestScore) {
                        bestScore = score;
                    }

                }
            }
        }

        return bestScore;

    }

}

int** playerTurn(int mouseOnBoard, int** board) {

    int x = mouseOnBoard % 3;
    int y = mouseOnBoard / 3;

    if(player_turn == 0) {

        if(board[x][y] == -1) {
            board[x][y] = 0;
            player_turn = 1;
        }

    } else if(player_turn == 1) {

        int bestScore = -1000;
        int bestI = -1;
        int bestJ = -1;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == -1) {

                    board[i][j] = 1;
                    int score = minimax(board, 0, false);
                    board[i][j] = -1;

                    if(score > bestScore) {
                        bestScore = score;
                        bestI = i;
                        bestJ = j;
                    }

                }
            }
        }

        board[bestI][bestJ] = 1;
        player_turn = 0;

    }

    return board;

}


int main() {

    // ALLOCATE MEM
    int** board = (int**) malloc(sizeof(int) * 3);

    for(int i = 0; i < 3; i++) {
        board[i] = (int*) malloc(sizeof(int) * 3);
    }

    // INIT BOARD WITH -1
    initBoard(board);

    // RAYLIB
    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(60);

    InitWindow(width, height, "TIC TAC TOE");
    drawBoard(board);

    while(!WindowShouldClose()) {

        int mouseX = GetMouseX() / sqSize;
        int mouseY = GetMouseY() / sqSize;
        int mouseOnBoard = 3 * mouseY + mouseX;

        BeginDrawing();

        if((checkIfOver(board, 1) == -1) && (checkIfOver(board, 0) == -1)) {
            if(IsMouseButtonPressed(0)) {
                board = playerTurn(mouseOnBoard, board);
                drawBoard(board);
            }
            if(player_turn == 1) {
                board = playerTurn(mouseOnBoard, board);
                drawBoard(board);
            }
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
