#include <stdio.h>

int i, j;
void initializeBoard(char board[3][3]) {
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[3][3]) {
    printf("\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

int isGameOver(char board[3][3]) {
    for (i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return 1;
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return 1;
    }

    int draw = 1;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                draw = 0;
                break;
            }
        }
        if (!draw) break;
    }
    if (draw) return 2;

    return 0;
}

int makeMove(char board[3][3], char player, int row, int col) {
    if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
        return 0;
    }

    board[row][col] = player;
    return 1;
}

int main() {
    char board[3][3];
    char currentPlayer = 'X';
    int gameOver = 0;

    initializeBoard(board);

    printf("Tic Tac Toe - 2 Players\n");

    while (!gameOver) {
        printBoard(board);
        int row, col;

        printf("Player %c, enter your move (row [0-2] and column [0-2]): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (makeMove(board, currentPlayer, row, col)) {
            gameOver = isGameOver(board);
            if (gameOver == 0) {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        } else {
            printf("Invalid move. Learn to read a grid\n");
        }
    }

    printBoard(board);

    if (gameOver == 1) {
        printf("Player %c wins! No need to be happy its tic tac toe\n", currentPlayer);
    } else {
        printf("It's a draw!Such a disappointing outcome\n");
    }

    return 0;
}
